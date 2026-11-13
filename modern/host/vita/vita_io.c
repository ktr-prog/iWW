// File-I/O marshaling for the PS Vita port.
//
// Why this exists: the game runs in a cooperative coroutine with its own stack (modern/host/main.c allocates an
// 8 MB stack and host_coro_switch()es into it; the DS-SDK threads in modern/host/os.c are coroutines too). The
// Vita kernel routes filesystem calls (sceIoOpen/Read/Write/...) through an IPC gate to sceIofilemgr, and that
// gate validates that the caller's stack pointer lies inside the thread's *kernel-registered* stack. A coroutine
// stack is an ordinary heap allocation, far outside that range, so every file syscall made from the game
// coroutine faults inside sceIoWrite (data abort). GPU/audio syscalls don't do this check, which is why SDL came
// up fine while the first log write or save write from the game crashed.
//
// Fix: run every file syscall on a dedicated worker thread whose stack IS kernel-registered. We intercept
// newlib's reentrant syscall layer with the linker's --wrap (see tools/configure_host.py): references to
// _open_r/_write_r/etc. become __wrap__*; the originals are __real__*. Each wrapper packages its call into a job,
// hands it to the worker, and blocks; the worker runs the genuine __real__* function (so VitaSDK keeps doing the
// POSIX->SCE flag translation, fd table and errno) from its own registered stack, then wakes us. Only one job is
// in flight at a time (a mutex serializes submitters), and before the worker is up calls run inline - startup
// runs on the real main thread, which is already registered.

#include <errno.h>
#include <reent.h>
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

static SceUID g_req, g_done, g_mtx;
static volatile struct iojob *g_job;
static int g_ready;

static int worker(SceSize args, void *argp) {
    (void)args;
    (void)argp;
    for (;;) {
        sceKernelWaitSema(g_req, 1, NULL);
        struct iojob *j = (struct iojob *)g_job;
        j->run(j);
        sceKernelSignalSema(g_done, 1);
    }
    return 0;
}

static void submit(struct iojob *j) {
    if (!g_ready) {  // early boot: still on the registered main-thread stack, so just do it here
        j->run(j);
        return;
    }
    sceKernelLockMutex(g_mtx, 1, NULL);
    g_job = j;
    sceKernelSignalSema(g_req, 1);
    sceKernelWaitSema(g_done, 1, NULL);
    sceKernelUnlockMutex(g_mtx, 1);
}

void vita_io_init(void) {
    g_req = sceKernelCreateSema("acww_io_req", 0, 0, 1, NULL);
    g_done = sceKernelCreateSema("acww_io_done", 0, 0, 1, NULL);
    g_mtx = sceKernelCreateMutex("acww_io_mtx", 0, 0, NULL);
    SceUID th = sceKernelCreateThread("acww_io_worker", worker, 0x10000100, 0x10000, 0, 0, NULL);
    if (th < 0 || g_req < 0 || g_done < 0 || g_mtx < 0) return;  // leave g_ready 0: fall back to inline calls
    sceKernelStartThread(th, 0, NULL);
    g_ready = 1;
}

#define JOB(init) \
    struct iojob j = {0}; \
    init; \
    submit(&j)

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
