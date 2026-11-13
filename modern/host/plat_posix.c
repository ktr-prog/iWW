#ifndef _WIN32

#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#if HOST_VITA
// VitaSDK's newlib has no <sys/mman.h>: the Vita can't reserve/guard pages, so the stack and page allocators
// below use aligned malloc instead (the 64-bit pointer arena is already compiled out on this 32-bit target)
#include <malloc.h>
#include <stdint.h>
#include <psp2/kernel/threadmgr.h>
#else
#include <sys/mman.h>
#endif
#if defined(__GLIBC__) || defined(__APPLE__)
#include <execinfo.h>
#define HAVE_EXECINFO 1
#endif
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#endif

#include "plat.h"
#include "savestate.h"

uint64_t host_plat_time_ns(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)t.tv_sec * 1000000000u + (uint64_t)t.tv_nsec;
}

void host_plat_sleep_until_ns(uint64_t t) {
#if defined(__linux__)
    struct timespec ts = {(time_t)(t / 1000000000u), (long)(t % 1000000000u)};
    while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, 0) == EINTR) {}
#else
    for (;;) {
        uint64_t now = host_plat_time_ns();
        if (now >= t) return;
        uint64_t d = t - now;
        struct timespec ts = {(time_t)(d / 1000000000u), (long)(d % 1000000000u)};
        nanosleep(&ts, 0);
    }
#endif
}

void host_plat_sleep_ms(unsigned ms) { host_plat_sleep_until_ns(host_plat_time_ns() + (uint64_t)ms * 1000000u); }

int host_plat_localtime(struct tm *out) {
    time_t now = time(0);
    return localtime_r(&now, out) != 0;
}

struct Start { void (*fn)(void *); void *arg; };
static void *thread_main(void *p) {
    struct Start s = *(struct Start *)p;
    free(p);
    s.fn(s.arg);
    return 0;
}
void host_plat_restart(char **argv) {
#if HOST_VITA
    (void)argv;  // no process restart on the Vita
#else
#ifdef __linux__
    execv("/proc/self/exe", argv);
#endif
    execvp(argv[0], argv);
#endif
}

int host_plat_thread_start(void (*fn)(void *), void *arg) {
    struct Start *s = malloc(sizeof *s);
    if (!s) return 0;
    s->fn = fn;
    s->arg = arg;
#if !HOST_VITA
    sigset_t all, old;
    sigfillset(&all);
    pthread_sigmask(SIG_SETMASK, &all, &old);
#endif
    pthread_t t;
    int err = pthread_create(&t, 0, thread_main, s);
#if !HOST_VITA
    pthread_sigmask(SIG_SETMASK, &old, 0);
#endif
    if (err) { free(s); return 0; }
    pthread_detach(t);
    return 1;
}

static size_t page_size(void) {
#if HOST_VITA
    return 4096;
#else
    static size_t page;
    if (!page) page = (size_t)sysconf(_SC_PAGESIZE);
    return page;
#endif
}

#if UINTPTR_MAX > 0xffffffffu
static const uintptr_t kArenaAt[] = {0x380000000ull, 0x2b0000000ull, 0x400000000ull};
#define ARENA_SIZE ((size_t)512 << 20)
static unsigned char *sArena;
static size_t sArenaUsed, sArenaTop;
static int sArenaTried;
static void arena_reserve(void) {
    sArenaTried = 1;
    for (size_t i = 0; i < sizeof kArenaAt / sizeof *kArenaAt && !sArena; i++) {
        void *p = mmap((void *)kArenaAt[i], ARENA_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
        if (p == MAP_FAILED) continue;
        if ((uintptr_t)p == kArenaAt[i]) sArena = p;
        else munmap(p, ARENA_SIZE);
    }
    if (!sArena) {
        void *p = mmap(0, ARENA_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
        sArena = p == MAP_FAILED ? 0 : p;
        if (sArena) fprintf(stderr, "host: the memory arena is at %p, none of its fixed places free\n", (void *)sArena);
    }
}
static unsigned char *arena_take(size_t n) {
    if (!sArenaTried) arena_reserve();
    if (!sArena || n > ARENA_SIZE - sArenaTop - sArenaUsed) return 0;
    unsigned char *p = sArena + sArenaUsed;
    if (mprotect(p, n, PROT_READ | PROT_WRITE) != 0) return 0;
    sArenaUsed += n;
    return p;
}
void *host_plat_arena_top(size_t n) {
    if (!sArenaTried) arena_reserve();
    n = (n + page_size() - 1) & ~(page_size() - 1);
    if (!sArena || n > ARENA_SIZE - sArenaTop - sArenaUsed) return 0;
    unsigned char *p = sArena + ARENA_SIZE - sArenaTop - n;
    if (mprotect(p, n, PROT_READ | PROT_WRITE) != 0) return 0;
    sArenaTop += n;
    return p;
}
int host_plat_arena(uintptr_t *base, size_t *used) {
    if (!sArenaTried) arena_reserve();
    if (!sArena) return 0;
    *base = (uintptr_t)sArena, *used = sArenaUsed;
    return 1;
}
int host_plat_arena_set_used(size_t used) {
    if (!sArena || used > ARENA_SIZE - sArenaTop) return 0;
    if (used > sArenaUsed && mprotect(sArena + sArenaUsed, used - sArenaUsed, PROT_READ | PROT_WRITE) != 0) return 0;
    sArenaUsed = used;
    return 1;
}
int host_plat_commit(void *p, size_t n) {
    size_t page = page_size();
    uintptr_t a = (uintptr_t)p & ~(page - 1), e = ((uintptr_t)p + n + page - 1) & ~(page - 1);
    if (!sArena || a < (uintptr_t)sArena || e > (uintptr_t)sArena + ARENA_SIZE) return 0;
    return mprotect((void *)a, e - a, PROT_READ | PROT_WRITE) == 0;
}
#else
static unsigned char *arena_take(size_t n) { (void)n; return 0; }
void *host_plat_arena_top(size_t n) { (void)n; return 0; }
int host_plat_arena(uintptr_t *base, size_t *used) { (void)base; (void)used; return 0; }
int host_plat_arena_set_used(size_t used) { (void)used; return 0; }
int host_plat_commit(void *p, size_t n) { (void)p; (void)n; return 0; }
#endif

#if HOST_VITA
// Coroutine stacks must live inside the main thread's KERNEL-REGISTERED stack. The Vita routes syscalls through
// a gate that faults unless the caller's sp is within the current thread's registered stack, and the game, the
// SDL frontend and the DS-SDK threads all run as coroutines on the one (main) OS thread. The main thread's stack
// is enlarged via sceUserMainThreadStackSize (vita_glue.c); here we hand coroutine stacks out of its low end so
// every coroutine's sp stays in range and any syscall it makes (file I/O, pthread/GXM mutexes, ...) passes.
static unsigned char *sVPoolNext, *sVPoolEnd, *sVPoolLo, *sVPoolHi;
static void vstack_pool_init(void) {
    SceKernelThreadInfo info;
    memset(&info, 0, sizeof info);
    info.size = sizeof info;
    if (sceKernelGetThreadInfo(sceKernelGetThreadId(), &info) != 0 || !info.stack || info.stackSize <= 0) return;
    unsigned char *a = (unsigned char *)info.stack;
    unsigned char *b = a + info.stackSize;
    unsigned char here[16];  // a current main-stack address, to tell which end info.stack is
    if (!((uintptr_t)here >= (uintptr_t)a && (uintptr_t)here < (uintptr_t)b)) {
        // info.stack is the high end: the region is [stack - size, stack)
        b = a;
        a = b - info.stackSize;
        if (!((uintptr_t)here >= (uintptr_t)a && (uintptr_t)here < (uintptr_t)b)) return;  // can't locate it
    }
    sVPoolLo = sVPoolNext = a;             // carve coroutine stacks up from the low end
    sVPoolEnd = sVPoolHi = b - (2u << 20);  // leave 2 MB at the top for the main thread itself
    if (sVPoolEnd < sVPoolNext) sVPoolEnd = sVPoolNext;
}
#endif

void *host_plat_stack_alloc(size_t n, int flags) {
    size_t page = page_size();
    n = (n + page - 1) & ~(page - 1);
    (void)flags;
#if HOST_VITA
    // no guard page (the Vita can't PROT_NONE). Prefer a slice of the main thread's registered stack so syscalls
    // from this coroutine pass the kernel's stack-bounds gate; fall back to the heap only if the pool is spent.
    static int inited;
    if (!inited) { inited = 1; vstack_pool_init(); }
    if (sVPoolNext && sVPoolNext + n <= sVPoolEnd) {
        void *p = sVPoolNext;
        sVPoolNext += n;
        host_state_track_stack(p, n);
        return p;
    }
    fprintf(stderr, "host: stack pool spent, %lu bytes from the heap (syscalls from this stack may fault)\n",
            (unsigned long)n);
    void *p = memalign(page, n);
    if (!p) return 0;
    host_state_track_stack(p, n);
    return p;
#else
    unsigned char *p = arena_take(n + page);
    if (!p) p = mmap(0, n + page, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED || !p) return 0;
    mprotect(p, page, PROT_NONE);
    host_state_track_stack(p + page, n);
    return p + page;
#endif
}

void host_plat_stack_free(void *stack, size_t n) {
    if (!stack) return;
    host_state_untrack(stack);
#if HOST_VITA
    (void)n;
    if ((unsigned char *)stack >= sVPoolLo && (unsigned char *)stack < sVPoolHi) return;  // pooled: not heap, don't free
    free(stack);
#else
#if UINTPTR_MAX > 0xffffffffu
    if (sArena && (unsigned char *)stack >= sArena && (unsigned char *)stack < sArena + ARENA_SIZE) return;
#endif
    size_t page = page_size();
    n = (n + page - 1) & ~(page - 1);
    munmap((unsigned char *)stack - page, n + page);
#endif
}

void *host_plat_pages_alloc(size_t n) {
    size_t page = page_size();
#if HOST_VITA
    size_t rounded = (n + page - 1) & ~(page - 1);
    void *p = memalign(page, rounded);
    if (!p) return 0;
    memset(p, 0, rounded);  // mmap hands back zeroed pages on other hosts; the DS RAM/VRAM blocks rely on that
    host_state_track(p, n);
    return p;
#else
    void *p = arena_take((n + page - 1) & ~(page - 1));
    if (!p) p = mmap(0, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED || !p) return 0;
    host_state_track(p, n);
    return p;
#endif
}

int host_plat_image_bounds(uintptr_t *lo, uintptr_t *hi) {
#if defined(__APPLE__)
    const struct mach_header_64 *mh = (const struct mach_header_64 *)_dyld_get_image_header(0);
    intptr_t slide = _dyld_get_image_vmaddr_slide(0);
    if (!mh || mh->magic != MH_MAGIC_64) return 0;
    const unsigned char *c = (const unsigned char *)(mh + 1);
    uintptr_t l = UINTPTR_MAX, h = 0;
    for (uint32_t i = 0; i < mh->ncmds; i++) {
        const struct load_command *lc = (const struct load_command *)c;
        if (lc->cmd == LC_SEGMENT_64) {
            const struct segment_command_64 *sg = (const struct segment_command_64 *)c;
            if (strcmp(sg->segname, "__PAGEZERO") && strcmp(sg->segname, "__LINKEDIT") && sg->vmsize) {
                if (sg->vmaddr + slide < l) l = sg->vmaddr + slide;
                if (sg->vmaddr + slide + sg->vmsize > h) h = sg->vmaddr + slide + sg->vmsize;
            }
        }
        c += lc->cmdsize;
    }
    if (l >= h) return 0;
    *lo = l, *hi = h;
    return 1;
#elif defined(__ELF__) && !HOST_VITA
    extern char __executable_start[], _end[];
    *lo = (uintptr_t)__executable_start;
    *hi = (uintptr_t)_end;
    return 1;
#else
    (void)lo; (void)hi;
    return 0;
#endif
}

int host_plat_backtrace(void **pcs, int n) {
#if HAVE_EXECINFO
    return backtrace(pcs, n);
#else
    (void)pcs; (void)n;
    return 0;
#endif
}

void host_plat_print_backtrace(void) {
#if HAVE_EXECINFO
    void *bt[32];
    int n = backtrace(bt, 32);
    backtrace_symbols_fd(bt, n, 2);
#endif
}

#endif
