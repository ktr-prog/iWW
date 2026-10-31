
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coro.h"
#include "host.h"
#include "render.h"
#include "host_mem.h"
#include "overlay.h"
#include "plat.h"
#include "host_features.h"
#include "savestate.h"

int gHostVerbose;
const char *gHostRomPath;

#if HOST_IOS
void ios_fatal_message(const char *text);
#endif

void host_fatal(const char *msg) {
    fprintf(stderr, "host: fatal: %s (frame %llu)\n", msg, (unsigned long long)host_frame());
#if HOST_IOS
    {
        char text[512];
        snprintf(text, sizeof text, "The game stopped: %s.", msg);
        ios_fatal_message(text);
    }
#endif
    extern void frontend_shutdown(void);
    frontend_shutdown();
    exit(2);
}

void host_log_proc(u32 profile, void *create, void *obj) {
    static int on = -1;
    if (on < 0) on = getenv("ACWW_PROCLOG") != 0;
    if (on) fprintf(stderr, "proc: frame %llu profile %u create %p -> %p\n", (unsigned long long)host_frame(), profile, create, obj);
}

int host_in_program_image(const void *p) {
    uintptr_t lo, hi;
    if (!host_plat_image_bounds(&lo, &hi)) return 1;
    return (uintptr_t)p >= lo && (uintptr_t)p < hi;
}

void host_bad_object(u32 profile, void *create, void *obj) {
    fprintf(stderr, "host: profile %u: create %p returned %p without a vtable\n", profile, create, obj);
}

void host_panic(const char *file, u32 line, const char *fmt, void *args) {
    char buf[512];
#if defined(__aarch64__) && !defined(__APPLE__)
    (void)args;
    snprintf(buf, sizeof buf, "%s", fmt);
#else
    vsnprintf(buf, sizeof buf, fmt, *(va_list *)&args);
#endif
    fprintf(stderr, "host: game panic: %s (%s:%u)\n", buf, file ? file : "", line);
    host_fatal("panic");
}

void host_panic_v(const char *file, u32 line, const char *fmt, va_list *args) {
    char buf[512];
    vsnprintf(buf, sizeof buf, fmt, *args);
    fprintf(stderr, "host: game panic: %s (%s:%u)\n", buf, file ? file : "", line);
    host_fatal("panic");
}

void host_unimplemented(const char *what) {
    fprintf(stderr, "host: unimplemented: %s\n", what);
}

const u8 *host_rom(u32 *size);
void NitroMain(void);
void NitroStartUp(void);


static void game_main(void *arg) {
    (void)arg;
    NitroStartUp();
    NitroMain();
    host_fatal("NitroMain returned");
}

char **gHostArgv;
void *gHostMainSp;
HOST_STATE_KEEP(gHostMainSp)
#if HOST_IOS
#define main host_main
void frontend_backend_main_loop(void);
#endif
int main(int argc, char **argv) {
    gHostArgv = argv;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-v")) gHostVerbose = 1;
        else gHostRomPath = argv[i];
    }
    if (!gHostRomPath) { fprintf(stderr, "usage: %s [-v] <rom.nds>\n", argv[0]); return 1; }
    HostOverlay_Init();
    card_init(gHostRomPath);
    u32 size;
    const u8 *rom = host_rom(&size);
    _Static_assert(sizeof gHostSysWork.romHeader + sizeof gHostSysWork.isdReserved >= 0x170, "ROM header");
    memcpy(gHostSysWork.romHeader, rom, sizeof gHostSysWork.romHeader);
    memcpy(gHostSysWork.isdReserved, rom + sizeof gHostSysWork.romHeader, 0x170 - sizeof gHostSysWork.romHeader);
    memcpy(gHostSysWork.bootCheckInfo, rom + 0x0c, 4);
    *(volatile u16 *)gHostSysWork.wmBootBuf = 1;
    pxi7_init();
    render_init();
    host_debug_crash_handlers();
    extern void frontend_init(const char *argv0);
    extern void frontend_shutdown(void);
    frontend_init(argv[0]);
    atexit(frontend_shutdown);
    enum { MAIN_STACK = 1024 * 1024 };
    void *stack = host_stack_alloc(MAIN_STACK);
    if (!stack) host_fatal("no memory for the main thread's stack");
    host_coro_switch(&gHostMainSp, host_coro_prepare(stack, MAIN_STACK, game_main, 0));
#if HOST_IOS
    frontend_backend_main_loop();
#endif
    host_fatal("the game's main thread returned");
}

struct HeapCheckLink { void *prev, *next; };
struct HeapCheckBlock { u16 sig, attr; u32 size; struct HeapCheckBlock *prev, *next; };
struct HeapCheckHead {
    u32 sig;
    struct HeapCheckLink link;
    struct { void *head, *tail; u16 num, offset; } childList;
    uintptr_t start, end;
    u32 attr;
    struct HeapCheckBlock *freeHead, *freeTail, *usedHead, *usedTail;
};
static uintptr_t sRootHeapLo, sRootHeapHi;
static int heap_check_range(const u8 *lo, const u8 *hi, int *heaps) {
    for (const u8 *a = lo; a + sizeof(struct HeapCheckHead) <= hi; a += 4) {
        const struct HeapCheckHead *h = (const void *)a;
        if (h->sig != 0x45585048 || h->start < (uintptr_t)lo || h->start >= h->end || h->end > (uintptr_t)hi) continue;
        (*heaps)++;
        struct HeapCheckBlock *lists[2] = {h->freeHead, h->usedHead};
        for (int l = 0; l < 2; l++) {
            struct HeapCheckBlock *prev = 0;
            u32 n = 0;
            for (struct HeapCheckBlock *m = lists[l]; m && n < 100000; n++) {
                if ((uintptr_t)m < h->start || (uintptr_t)m >= h->end || m->sig != (l ? 0x5544 : 0x4652) || m->prev != prev) {
                    fprintf(stderr, "heapcheck: frame %llu heap %p %s block %p bad (sig %04x prev %p want %p)\n",
                            (unsigned long long)host_frame(), (const void *)h, l ? "used" : "free", (void *)m,
                            ((uintptr_t)m >= h->start && (uintptr_t)m < h->end) ? m->sig : 0,
                            ((uintptr_t)m >= h->start && (uintptr_t)m < h->end) ? (void *)m->prev : 0, (void *)prev);
                    return 1;
                }
                prev = m;
                m = m->next;
            }
        }
    }
    return 0;
}
void host_heap_check(void) {
    static int on = -1, reported;
    if (on < 0) on = getenv("ACWW_HEAPCHECK") != 0;
    if (!on || reported) return;
    int heaps = 0;
    reported = heap_check_range(gHostMainRam, gHostMainRam + sizeof gHostMainRam, &heaps) ||
               (sRootHeapHi > sRootHeapLo && heap_check_range((const u8 *)sRootHeapLo, (const u8 *)sRootHeapHi, &heaps));
    if (!reported && host_frame() % 600 == 0)
        fprintf(stderr, "heapcheck: frame %llu: %d heaps fine\n", (unsigned long long)host_frame(), heaps);
}


int host_is_game_heap(const void *p) {
    return HostMem_IsGameRam(p, 1);
}
void host_root_heap_bounds(uintptr_t *lo, uintptr_t *hi) {
    *lo = sRootHeapLo;
    *hi = sRootHeapHi;
}

void *host_root_heap_region(unsigned int *size) {
    const unsigned int kSize = 8u << 20;
    void *p = host_plat_pages_alloc(kSize);
    if (!p) return 0;
    *size = kSize;
    sRootHeapLo = (uintptr_t)p;
    sRootHeapHi = (uintptr_t)p + kSize;
    return p;
}
