// File-I/O marshaling for the PS Vita port.
//
// Why this exists: the game and the SDL frontend run as cooperative coroutines, each on its own stack allocated
// from the heap (modern/host/main.c switches into game_main; modern/host/frontend_sdl.c runs fe_main; the DS-SDK
// threads in modern/host/os.c are coroutines too). The one real OS thread - the process main thread - parks
// forever inside host_coro_switch at main.c and never runs game/frontend code directly.
//
// The Vita kernel routes syscalls through a gate that validates the caller's stack pointer lies inside the
// current thread's KERNEL-REGISTERED stack. A coroutine stack is an ordinary heap allocation, far outside that
// range, so a syscall made from a coroutine faults (data abort inside e.g. sceIoWrite - and likewise inside
// sceKernelLockMutex, which is why an earlier worker-thread design crashed in its own sema call). GPU/audio
// paths don't hit this check, which is why SDL came up but the first log write and every save write crashed.
//
// Fix: when a file syscall is made from a coroutine, briefly switch the stack pointer to the main thread's
// registered stack and run the real call there. The main thread is parked at gHostMainSp with everything below
// it unused, so the region just below gHostMainSp is a safe scratch stack that passes the gate's check (the
// current OS thread is still the main thread - only its sp was borrowed). We intercept newlib's reentrant
// syscall layer with the linker's --wrap (see tools/configure_host.py): __wrap__* package the call, and the
// genuine __real__* (which keeps doing VitaSDK's flag translation, fd table and errno) runs on the scratch
// stack. Calls made on the main thread itself (early startup) run inline.

#include <reent.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <psp2/kernel/threadmgr.h>

#include "vita.h"

// the real libc implementations, renamed by --wrap
extern int __real__open_r(struct _reent *, const char *, int, int);
extern int __real__close_r(struct _reent *, int);
extern _ssize_t __real__read_r(struct _reent *, int, void *, size_t);
extern _ssize_t __real__write_r(struct _reent *, int, const void *, size_t);
extern _off_t __real__lseek_r(struct _reent *, int, _off_t, int);
extern int __real__fstat_r(struct _reent *, int, struct stat *);
extern int __real__isatty_r(struct _reent *, int);
extern int __real_rename(const char *, const char *);
extern int __real_remove(const char *);
extern int __real_unlink(const char *);

// modern/host/main.c: the main OS thread's sp, saved when it switched into the game coroutine (0 until then).
// modern/host/coro_switch.S: read sp, and run a function on a different stack.
extern void *gHostMainSp;
extern void *host_get_sp(void);
extern long host_call_on_stack(void *new_sp, void *fn, void *arg);

static uintptr_t g_main_lo, g_main_hi;  // the main thread's registered stack bounds

void vita_io_init(void) {
    SceKernelThreadInfo info;
    memset(&info, 0, sizeof info);
    info.size = sizeof info;
    if (sceKernelGetThreadInfo(sceKernelGetThreadId(), &info) == 0 && info.stack && info.stackSize > 0) {
        g_main_lo = (uintptr_t)info.stack;
        g_main_hi = g_main_lo + (uintptr_t)info.stackSize;
    }
}

struct iojob {
    void (*run)(struct iojob *);
    struct _reent *r;
    int fd, flags, mode, whence;
    const char *p1, *p2;
    void *buf;
    const void *cbuf;
    size_t n;
    _off_t off;
    struct stat *st;
    long long ret;
};

// run j->run(j): inline when we are already on the main thread's registered stack (startup), otherwise on a
// scratch stack carved just below the parked main thread's sp so the syscall passes the kernel's stack check.
static void dispatch(struct iojob *j) {
    uintptr_t cur = (uintptr_t)host_get_sp();
    if (!gHostMainSp || (g_main_lo && cur >= g_main_lo && cur < g_main_hi)) {
        j->run(j);
        return;
    }
    uintptr_t scratch = ((uintptr_t)gHostMainSp - 4096) & ~(uintptr_t)15u;
    host_call_on_stack((void *)scratch, (void *)j->run, j);
}

#define JOB(init) \
    struct iojob j = {0}; \
    init; \
    dispatch(&j)

static void do_open(struct iojob *j) { j->ret = __real__open_r(j->r, j->p1, j->flags, j->mode); }
int __wrap__open_r(struct _reent *r, const char *path, int flags, int mode) {
    JOB((j.run = do_open, j.r = r, j.p1 = path, j.flags = flags, j.mode = mode));
    return (int)j.ret;
}

static void do_close(struct iojob *j) { j->ret = __real__close_r(j->r, j->fd); }
int __wrap__close_r(struct _reent *r, int fd) {
    JOB((j.run = do_close, j.r = r, j.fd = fd));
    return (int)j.ret;
}

static void do_read(struct iojob *j) { j->ret = __real__read_r(j->r, j->fd, j->buf, j->n); }
_ssize_t __wrap__read_r(struct _reent *r, int fd, void *buf, size_t n) {
    JOB((j.run = do_read, j.r = r, j.fd = fd, j.buf = buf, j.n = n));
    return (_ssize_t)j.ret;
}

static void do_write(struct iojob *j) { j->ret = __real__write_r(j->r, j->fd, j->cbuf, j->n); }
_ssize_t __wrap__write_r(struct _reent *r, int fd, const void *buf, size_t n) {
    JOB((j.run = do_write, j.r = r, j.fd = fd, j.cbuf = buf, j.n = n));
    return (_ssize_t)j.ret;
}

static void do_lseek(struct iojob *j) { j->ret = __real__lseek_r(j->r, j->fd, j->off, j->whence); }
_off_t __wrap__lseek_r(struct _reent *r, int fd, _off_t off, int whence) {
    JOB((j.run = do_lseek, j.r = r, j.fd = fd, j.off = off, j.whence = whence));
    return (_off_t)j.ret;
}

static void do_fstat(struct iojob *j) { j->ret = __real__fstat_r(j->r, j->fd, j->st); }
int __wrap__fstat_r(struct _reent *r, int fd, struct stat *st) {
    JOB((j.run = do_fstat, j.r = r, j.fd = fd, j.st = st));
    return (int)j.ret;
}

static void do_isatty(struct iojob *j) { j->ret = __real__isatty_r(j->r, j->fd); }
int __wrap__isatty_r(struct _reent *r, int fd) {
    JOB((j.run = do_isatty, j.r = r, j.fd = fd));
    return (int)j.ret;
}

static void do_rename(struct iojob *j) { j->ret = __real_rename(j->p1, j->p2); }
int __wrap_rename(const char *a, const char *b) {
    JOB((j.run = do_rename, j.p1 = a, j.p2 = b));
    return (int)j.ret;
}

static void do_remove(struct iojob *j) { j->ret = __real_remove(j->p1); }
int __wrap_remove(const char *p) {
    JOB((j.run = do_remove, j.p1 = p));
    return (int)j.ret;
}

static void do_unlink(struct iojob *j) { j->ret = __real_unlink(j->p1); }
int __wrap_unlink(const char *p) {
    JOB((j.run = do_unlink, j.p1 = p));
    return (int)j.ret;
}
