
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__x86_64__) && defined(__linux__)
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#include "host.h"
#include "host_mem.h"
#include "plat.h"
#include "savestate.h"
#include "guards.h"
#include "render.h"

static unsigned long long sGxWrites;
static u64 sIoCount;

#define IO0 0x04000000u
#define IOB 0x04001000u
#define IO1 0x04100000u
#define PAGE 0x1000u

static u8 sIo0[PAGE] __attribute__((aligned(8)));
static u8 sIoB[PAGE] __attribute__((aligned(8)));
static u8 sIo1[PAGE] __attribute__((aligned(8)));
u8 *host_io(u32 a) { return a >= IO1 ? sIo1 + (a - IO1) : a >= IOB ? sIoB + (a - IOB) : sIo0 + (a - IO0); }
static int is_io(u32 a) { return (a >= IO0 && a < IOB + PAGE) || (a >= IO1 && a < IO1 + PAGE); }

void host_vram_control(u32 addr, u8 value);
#define R16(a) (*(u16 *)host_io(a))
#define R32(a) (*(u32 *)host_io(a))

#define LINE_CYCLES 2130u
#define FRAME_LINES 263u
#define FRAME_CYCLES (LINE_CYCLES * FRAME_LINES)
static u64 sCycles;
static u32 sTimeless;
u64 host_frame(void) { return sCycles / FRAME_CYCLES; }

void host_note(const char *what, int a, int b, int c) {
    static int n;
    if (n >= 400) return;
    if (++n == 400) fprintf(stderr, "game: (no more notes this run)\n");
    fprintf(stderr, "game: %s %d %d %d (frame %llu)\n", what, a, b, c, (unsigned long long)host_frame());
}
u64 host_cycles(void) { return sCycles; }
u64 pxi7_next_due(void);
void pxi7_run_due(void);

static u32 sIF;
void host_irq_raise(u32 m) { sIF |= m; }
void host_irq_ack(u32 m) { sIF &= ~m; }
u32 host_irq_pending(void) {
    u32 lines = sIF | (render_gx_fifo_irq_level() ? 1u << 21 : 0);
    return (R32(0x04000208) & 1) ? (R32(0x04000210) & lines) : 0;
}

typedef struct { u64 start; u16 reload; int shift; int on; int irq; int cascade; } Timer;
static Timer sTm[4];
static const int kTmShift[4] = {0, 6, 8, 10};
static u32 tm_period(Timer *t) { return (0x10000u - t->reload) << t->shift; }
static u16 tm_counter(Timer *t) {
    if (!t->on) return t->reload;
    u64 ticks = (sCycles - t->start) >> t->shift;
    return (u16)(t->reload + ticks % (0x10000u - t->reload));
}
static u64 tm_next_overflow(Timer *t) {
    u64 p = tm_period(t), done = (sCycles - t->start) / p;
    return t->start + (done + 1) * p;
}

static int sFast = -1;
static u64 sNextFrame;
static int sPaused;
static void host_pace_frame(void) {
    {
        static u64 last, limit;
        static int reports, maxReports;
        if (!maxReports) maxReports = getenv("ACWW_SLOW_FRAME_MAX") ? atoi(getenv("ACWW_SLOW_FRAME_MAX")) : 100;
        if (!limit) limit = (getenv("ACWW_SLOW_FRAME_MS") ? (u64)atoi(getenv("ACWW_SLOW_FRAME_MS")) : 100) * 1000000u;
        u64 t = host_plat_time_ns();
        if (last && t - last > limit && reports < maxReports && !__atomic_load_n(&sPaused, __ATOMIC_RELAXED)) {
            reports++;
            fprintf(stderr, "host: frame %llu took %llu ms\n", (unsigned long long)host_frame(), (unsigned long long)((t - last) / 1000000));
        }
        last = t;
    }
    if (sFast < 0) sFast = getenv("ACWW_FAST") ? (atoi(getenv("ACWW_FAST")) > 1 ? atoi(getenv("ACWW_FAST")) : 1) : 0;
    if (sFast == 1 || host_frame() < (u64)sFast) return;
    u64 now = host_plat_time_ns();
    if (sNextFrame == 0) sNextFrame = now;
    sNextFrame += 16715000;
    if (now > sNextFrame + 1000000000u) sNextFrame = now;
    host_plat_sleep_until_ns(sNextFrame);
}

static u32 sHeartbeat, sHeartbeatFrame;
static int sPaused;
void host_set_paused(int paused) {
    if (!paused && __atomic_load_n(&sPaused, __ATOMIC_RELAXED)) sNextFrame = 0;
    __atomic_store_n(&sPaused, paused, __ATOMIC_RELAXED);
}
static void watchdog(void *arg) {
    u32 limit = (u32)(uintptr_t)arg, still = 0, last = 0;
    int reported = 0;
    for (;;) {
        host_plat_sleep_ms(100);
        u32 hb = __atomic_load_n(&sHeartbeat, __ATOMIC_RELAXED);
        if (hb != last || __atomic_load_n(&sPaused, __ATOMIC_RELAXED)) { last = hb; still = 0; reported = 0; continue; }
        still += 100;
        if (still >= limit && !reported) {
            reported = 1;
            fprintf(stderr, "host: watchdog: virtual time hasn't moved for %u ms (frame %u): the game spins without a "
                    "register access or a wait (break in with a debugger; SIGINT lists the threads)\n", still,
                    __atomic_load_n(&sHeartbeatFrame, __ATOMIC_RELAXED));
        }
    }
}
static void watchdog_start(void) {
    const char *e = getenv("ACWW_WATCHDOG");
    long ms = e ? strtol(e, 0, 10) : 2000;
    if (ms <= 0) return;
    if (!host_plat_thread_start(watchdog, (void *)(uintptr_t)ms)) fprintf(stderr, "host: no watchdog thread\n");
}

static const char *sShotSpec;
HOST_STATE_KEEP(sShotSpec)
static void host_screenshot(void) {
    if (!sShotSpec) sShotSpec = getenv("ACWW_SHOT") ? getenv("ACWW_SHOT") : "";
    const char *spec = sShotSpec;
    u32 f = (u32)host_frame();
    for (const char *p = spec; *p;) {
        unsigned fr; char path[512];
        if (sscanf(p, "%u:%511[^;]", &fr, path) == 2 && fr == f) {
            FILE *o = fopen(path, "wb");
            if (o) {
                extern const uint32_t *gpu2d_canvas(int *rows);
                int rows = 0;
                const u32 *cv = gpu2d_canvas(&rows);
                if (cv && rows > 0) {
                    fprintf(o, "P6\n256 %d\n255\n", rows);
                    for (int i = 0; i < 256 * rows; i++) { u8 rgb[3] = {cv[i] >> 16, cv[i] >> 8, cv[i]}; fwrite(rgb, 1, 3, o); }
                } else {
                    fprintf(o, "P6\n256 384\n255\n");
                    for (int s = 0; s < 2; s++) {
                        const u32 *px = render_screen(s);
                        for (int i = 0; i < 256 * 192; i++) { u8 rgb[3] = {px[i] >> 16, px[i] >> 8, px[i]}; fwrite(rgb, 1, 3, o); }
                    }
                }
                fclose(o);
            }
        }
        p = strchr(p, ';');
        if (!p) break;
        p++;
    }
}

static void ram_image_put(u8 *img, u32 *at, const char *lo, const char *end, u32 limit) {
    size_t n = (size_t)(end - lo);
    static int warned;
    if (*at + n > limit) {
        if (!warned++) fprintf(stderr, "host: RAM image: the game's data and bss don't fit, %zu bytes cut\n", *at + n - limit);
        n = *at < limit ? limit - *at : 0;
    }
    memcpy(img + *at, lo, n);
    *at += (u32)n;
}
static const u8 *host_ram_image(void) {
    static u8 *img;
    if (!img && !(img = malloc(0x400000))) host_fatal("no memory for the RAM image");
    memset(img, 0, 0x400000);
    const u32 arena = HOST_MAIN_RAM_LO - 0x02000000;
    u32 at = 0x1000;
    ram_image_put(img, &at, gHostGameDataBegin, gHostGameDataEnd + 1, arena);
    at = at <= 0x40000 ? 0x40000 : (at + 0xfff) & ~0xfffu;
    ram_image_put(img, &at, gHostGameBssBegin, gHostGameBssEnd + 1, arena);
    memcpy(img + arena, gHostMainRam, sizeof gHostMainRam);
    memcpy(img + 0x3ff000, &gHostSysWork, 0x1000);
    return img;
}

u32 host_irq_state(void);
static u64 sNextVblank = 192u * LINE_CYCLES;
static void run_events(void);
static void io_trace_frame(void);
static u32 sStatWaits;
void host_advance_to_next_event(void) {
    sStatWaits++;
    u64 next = sNextVblank;
    if (pxi7_next_due() < next) next = pxi7_next_due();
    extern u64 wm7_next_due(void);
    if (wm7_next_due() < next) next = wm7_next_due();
    extern u64 snd7_next_due(void);
    if (snd7_next_due() < next) next = snd7_next_due();
    for (int i = 0; i < 4; i++) {
        if (sTm[i].on && sTm[i].irq && !sTm[i].cascade) {
            u64 o = tm_next_overflow(&sTm[i]);
            if (o < next) next = o;
        }
    }
    if (next > sCycles) sCycles = next;
    run_events();
}
static u64 sLastTimerCheck[4];
static void dma_on_vblank(void);
static int sInEvents;
static void run_events_body(void);
static void run_events(void) {
    if (sInEvents) return;
    sInEvents = 1;
    sTimeless = 0;
    run_events_body();
    __atomic_store_n(&sHeartbeat, (u32)sCycles, __ATOMIC_RELAXED);
    sInEvents = 0;
}
void snd7_run(u64 now);
static void run_events_body(void) {
    snd7_run(sCycles);
    pxi7_run_due();
    extern void wm7_run(u64 now);
    wm7_run(sCycles);
    while (sCycles >= sNextVblank) {
        static int watchdogOn;
        if (!watchdogOn) { watchdogOn = 1; watchdog_start(); }
        __atomic_store_n(&sHeartbeatFrame, (u32)host_frame(), __ATOMIC_RELAXED);
        u16 st = R16(0x04000004);
        if (st & 8) host_irq_raise(1);
        if (st & 16) host_irq_raise(2);
        dma_on_vblank();
        render_frame();
        host_pace_frame();
        extern void frontend_frame(void);
        frontend_frame();
        extern void host_heap_check(void);
        host_heap_check();
        host_guards_frame();
        host_screenshot();
        io_trace_frame();
        {
            static long every = -2;
            if (every == -2) every = getenv("ACWW_POSLOG") ? strtol(getenv("ACWW_POSLOG"), 0, 10) : 0;
            if (every > 0 && host_frame() % (u64)every == 0) {
                extern struct VecFx32 *PlayerActor_GetBodyPos(u32 idx);
                const s32 *p = (const s32 *)PlayerActor_GetBodyPos(4);
                if (p) fprintf(stderr, "pos %llu %.2f %.2f %.2f\n", (unsigned long long)host_frame(), p[0] / 4096.0,
                               p[1] / 4096.0, p[2] / 4096.0);
            }
        }
        {
            static int jobDone = -1;
            if (jobDone < 0) jobDone = getenv("ACWW_TEST_JOB_DONE") != 0;
            extern void *PlayerData_GetCurrent(void);
            u32 *pd = jobDone ? PlayerData_GetCurrent() : 0;
            if (pd) pd[0x21fc / 4] &= ~2u;
        }
        {
            static long exitAt = -2;
            if (exitAt == -2) exitAt = getenv("ACWW_EXIT_FRAME") ? strtol(getenv("ACWW_EXIT_FRAME"), 0, 10) : -1;
            if (exitAt >= 0 && (long)host_frame() >= exitAt) {
                fprintf(stderr, "host: exit at frame %llu (ACWW_EXIT_FRAME)\n", (unsigned long long)host_frame());
                host_quit();
            }
        }
        {
            static FILE *hf; static int hinit; static const char *ramList, *ramTo;
            if (!hinit) {
                hinit = 1;
                if (getenv("ACWW_RAMHASH")) hf = fopen(getenv("ACWW_RAMHASH"), "wb");
                ramList = getenv("ACWW_RAMDUMP");
                ramTo = ramList && strchr(ramList, ':') ? strchr(ramList, ':') + 1 : 0;
            }
            if (hf) {
                const u64 *p = (const u64 *)host_ram_image();
                u64 h = 0x9e3779b97f4a7c15ull;
                for (u32 i = 0; i < 0x400000 / 8; i++) h = (h ^ p[i]) * 0x100000001b3ull;
                for (u32 i = 0; i < sizeof gHostDtcm / 8; i++) h = (h ^ ((const u64 *)gHostDtcm)[i]) * 0x100000001b3ull;
                for (u32 i = 0; i < sizeof gHostSysWork / 8; i++) h = (h ^ ((const u64 *)&gHostSysWork)[i]) * 0x100000001b3ull;
                fprintf(hf, "%llu %016llx\n", (unsigned long long)host_frame(), (unsigned long long)h);
                fflush(hf);
            }
            if (ramTo) {
                for (const char *q = ramList; q && q < ramTo; ) {
                    char *end;
                    long at = strtol(q, &end, 10);
                    if (end == q) break;
                    if ((long)host_frame() == at) {
                        char name[512];
                        snprintf(name, sizeof name, "%s-%ld.bin", ramTo, at);
                        FILE *df = fopen(name, "wb");
                        if (df) { fwrite(host_ram_image(), 1, 0x400000, df); fclose(df); }
                    }
                    q = end + (*end == ',');
                }
            }
        }
        {
            static long dumpAt = -2; static const char *dumpTo;
            if (dumpAt == -2) {
                const char *e = getenv("ACWW_VRAMDUMP");
                dumpAt = e ? strtol(e, 0, 10) : -1;
                dumpTo = e && strchr(e, ':') ? strchr(e, ':') + 1 : 0;
            }
            if (dumpAt >= 0 && dumpTo && (long)host_frame() == dumpAt) {
                extern u8 *host_vram_bank(int i);
                extern u32 host_vram_bank_size(int i);
                extern void host_vram_flush(void);
                host_vram_flush();
                FILE *df = fopen(dumpTo, "wb");
                if (df) {
                    for (int b = 0; b < 9; b++) fwrite(host_vram_bank(b), 1, host_vram_bank_size(b), df);
                    fwrite(gHostPltt, 1, sizeof gHostPltt, df);
                    fwrite(gHostOam, 1, sizeof gHostOam, df);
                    for (u32 w = 0x04000000; w < 0x04001100; w += 4) { u32 v = R32(w); fwrite(&v, 4, 1, df); }
                    fclose(df);
                }
            }
        }
        static int statsEvery = -1;
        if (statsEvery < 0) statsEvery = getenv("ACWW_STATS") ? (atoi(getenv("ACWW_STATS")) > 1 ? atoi(getenv("ACWW_STATS")) : 300) : 0;
        if (statsEvery && host_frame() % statsEvery == 0) {
            extern u8 *host_vram_bank(int i);
            extern u32 host_vram_bank_size(int i);
            extern void host_vram_flush(void);
            host_vram_flush();
            int pal = 0; for (int i = 0; i < 0x800; i++) pal += gHostPltt[i] != 0;
            fprintf(stderr, "stats: frame %llu dispcnt %08x/%08x bright %04x/%04x pal %d banks", (unsigned long long)host_frame(),
                    R32(0x04000000), R32(0x04001000), R16(0x0400006c), R16(0x0400106c), pal);
            for (int b = 0; b < 9; b++) { int nz = 0; u8 *p = host_vram_bank(b); for (u32 i = 0; i < host_vram_bank_size(b); i++) nz += p[i] != 0; fprintf(stderr, " %d", nz); }
            fprintf(stderr, " game bld %08x %08x/%08x %08x bg %08x %08x", R32(0x04000050), R32(0x04000054), R32(0x04001050), R32(0x04001054), R32(0x04000008), R32(0x0400000c));
            extern u32 gScreenTransition[];
            fprintf(stderr, " transition");
            for (int i = 0; i < 12; i++) fprintf(stderr, " %x", gScreenTransition[i]);
            render_debug();
            fprintf(stderr, " gx %llu", sGxWrites);
            sGxWrites = 0;
            { static unsigned long long lastIo; fprintf(stderr, " io %llu", (unsigned long long)sIoCount - lastIo); lastIo = sIoCount; }
            fprintf(stderr, " vramcnt %08x %08x ime %x ie %08x if %08x cpu %x\n", R32(0x04000240), R32(0x04000244), R32(0x04000208), R32(0x04000210), sIF, host_irq_state());
        }
        if (getenv("ACWW_FPS") && host_frame() % 120 == 0) {
            static u64 last;
            u64 now = host_plat_time_ns();
            if (last) fprintf(stderr, "fps: frame %llu %.1f\n", (unsigned long long)host_frame(), 120 / ((double)(now - last) * 1e-9));
            last = now;
        }
        extern void pxi7_vblank(void);
        pxi7_vblank();
        sNextVblank += FRAME_CYCLES;
    }
    for (int i = 0; i < 4; i++) {
        Timer *t = &sTm[i];
        if (!t->on || t->cascade) continue;
        u64 p = tm_period(t);
        u64 before = (sLastTimerCheck[i] > t->start ? sLastTimerCheck[i] - t->start : 0) / p;
        u64 now = (sCycles - t->start) / p;
        if (now > before && t->irq) host_irq_raise(1u << (3 + i));
        sLastTimerCheck[i] = sCycles;
    }
}

static void update_display(void) {
    u32 line = (u32)(sCycles % FRAME_CYCLES) / LINE_CYCLES, dot = (u32)(sCycles % LINE_CYCLES);
    u16 st = R16(0x04000004) & ~7u;
    if (line >= 192) st |= 1;
    if (dot >= 1606) st |= 2;
    if (line == ((R16(0x04000004) >> 8) | ((R16(0x04000004) & 0x80) << 1))) st |= 4;
    R16(0x04000004) = st;
    R16(0x04000006) = (u16)line;
}

static void divide(void) {
    u16 cnt = R16(0x04000280);
    int64_t n = (cnt & 3) == 0 ? (int32_t)R32(0x04000290) : *(int64_t *)host_io(0x04000290);
    int64_t d = (cnt & 3) == 2 ? *(int64_t *)host_io(0x04000298) : (int32_t)R32(0x04000298);
    int64_t q, r;
    if (d == 0) { q = n < 0 ? 1 : -1; r = n; R16(0x04000280) = cnt | 0x4000; }
    else { q = n / d; r = n % d; R16(0x04000280) = cnt & ~0x4000; }
    *(int64_t *)host_io(0x040002a0) = q;
    *(int64_t *)host_io(0x040002a8) = r;
}
static void square_root(void) {
    u64 v = (R16(0x040002b0) & 1) ? *(u64 *)host_io(0x040002b8) : R32(0x040002b8);
    u64 r = 0, bit = 1ull << 62;
    while (bit > v) bit >>= 2;
    while (bit) { if (v >= r + bit) { v -= r + bit; r = (r >> 1) + bit; } else r >>= 1; bit >>= 2; }
    R32(0x040002b4) = (u32)r;
}

static void io_write(u32 a, u32 old);

static uintptr_t sDmaSrc[4], sDmaDst[4];
void HostDma_Addresses(unsigned int ch, uintptr_t src, uintptr_t dst) {
    if (ch < 4) { sDmaSrc[ch] = src; sDmaDst[ch] = dst; }
}
static uintptr_t dma_address(u32 reg, uintptr_t full) { return (u32)full == reg ? full : reg; }
static int dma_is_io(uintptr_t a) { return a <= 0xffffffffu && is_io((u32)a); }
void gx_fifo_write(u32 addr, u32 value);
static void dma_run(int ch) {
    u32 base = 0x040000b0 + ch * 12, cnt = R32(base + 8);
    uintptr_t src = dma_address(R32(base), sDmaSrc[ch]), dst = dma_address(R32(base + 4), sDmaDst[ch]);
    u32 n = cnt & 0x1fffff, w = (cnt >> 26 & 1) ? 4 : 2;
    int dc = cnt >> 21 & 3, sc = cnt >> 23 & 3;
    if (n == 0) n = 0x200000;
    if (src < 0x10000 || dst < 0x10000) {
        fprintf(stderr, "host: DMA%d from %08llx to %08llx, control %08x: bad address\n", ch, (unsigned long long)src,
                (unsigned long long)dst, cnt);
        R32(base + 8) = cnt & ~0x80000000u;
        return;
    }
    for (u32 i = 0; i < n; i++) {
        u32 v;
        if (src == IO1 + 0x10) v = card_read_data();
        else if (dma_is_io(src)) v = w == 4 ? R32((u32)src) : R16((u32)src);
        else v = w == 4 ? *(volatile u32 *)src : *(volatile u16 *)src;
        if (dma_is_io(dst)) {
            u32 old = R32((u32)dst & ~3u);
            if (w == 4) R32((u32)dst) = v; else R16((u32)dst) = (u16)v;
            io_write((u32)dst, old);
        } else if (w == 4) *(volatile u32 *)dst = v;
        else *(volatile u16 *)dst = (u16)v;
        if (sc == 0) src += w; else if (sc == 1) src -= w;
        if (dc == 0 || dc == 3) dst += w; else if (dc == 1) dst -= w;
    }
    if (dc != 3) { R32(base + 4) = (u32)dst; sDmaDst[ch] = dst; }
    R32(base) = (u32)src;
    sDmaSrc[ch] = src;
    if (!(cnt >> 25 & 1) || ((cnt >> 27 & 7) == 0)) R32(base + 8) = cnt & ~0x80000000u;
    if (cnt >> 30 & 1) host_irq_raise(1u << (8 + ch));
}
static void dma_control_written(int ch) {
    u32 cnt = R32(0x040000b0 + ch * 12 + 8);
    if (!(cnt >> 31)) return;
    u32 mode = cnt >> 27 & 7;
    if (mode == 0 || mode == 7) dma_run(ch);
}
static void dma_on_vblank(void) {
    for (int ch = 0; ch < 4; ch++) {
        u32 cnt = R32(0x040000b0 + ch * 12 + 8);
        if (cnt >> 31 && ((cnt >> 27 & 7) == 1 || (cnt >> 27 & 7) == 2)) dma_run(ch);
    }
}
void host_card_dma(void) {
    for (int ch = 0; ch < 4; ch++) {
        u32 cnt = R32(0x040000b0 + ch * 12 + 8);
        if (cnt >> 31 && (cnt >> 27 & 7) == 5) dma_run(ch);
    }
}

void gx_fifo_write(u32 addr, u32 value) { sGxWrites++; render_write32(addr, value); }

static int sTimingLegacy = -1;
static u32 sPollAddr = ~0u, sPollRepeat;
static u32 sStatPolls, sStatClockReads;
static void io_spin_check(void);
static uintptr_t io_last_caller(void);
static u32 io_read_cost(u32 a) {
    u32 w = a & ~3u;
    if (sTimingLegacy) {
        static u32 last, repeat;
        repeat = a == last ? repeat + 1 : 0;
        last = a;
        return repeat > 4 ? 4096 : 64;
    }
    sPollRepeat = a == sPollAddr ? sPollRepeat + 1 : 0;
    sPollAddr = a;
    if (sPollRepeat > 4) { sStatPolls++; return 4096; }
    if (w == 0x04000004 || (w >= 0x04000100 && w < 0x04000110)) { sStatClockReads++; return 64; }
    return 0;
}
void host_spend_cycles(u64 n) {
    if (sTimingLegacy) return;
    sCycles += n;
    run_events();
}
static int sHBlankLine = -1;
static u32 sPollAddr, sPollRepeat;
void host_hblank(int line) {
    if (!(R16(0x04000004) & 0x10) || !(R32(0x04000208) & 1) || !(R32(0x04000210) & 2)) return;
    u16 st = R16(0x04000004), vcount = R16(0x04000006);
    u32 pollAddr = sPollAddr, pollRepeat = sPollRepeat, timeless = sTimeless;
    sHBlankLine = line;
    host_irq_call(1);
    sHBlankLine = -1;
    sPollAddr = pollAddr, sPollRepeat = pollRepeat, sTimeless = timeless;
    R16(0x04000004) = st;
    R16(0x04000006) = vcount;
}
static void io_read(u32 a) {
    if (sHBlankLine >= 0 && (a & ~3u) == 0x04000004) {
        R16(0x04000004) = (u16)((R16(0x04000004) & ~7u) | 2);
        R16(0x04000006) = (u16)sHBlankLine;
        return;
    }
    u32 cost = io_read_cost(a);
    if (cost) {
        sCycles += cost;
        run_events();
    } else io_spin_check();
    u32 w = a & ~3u;
    if (w == 0x04000004) update_display();
    else if (w >= 0x04000100 && w < 0x04000110) {
        int i = (w - 0x04000100) / 4;
        R16(w) = tm_counter(&sTm[i]);
    } else if (w == 0x04000214) R32(w) = sIF;
    else if ((w >= 0x04000600 && w < 0x040006a4) || w == 0x04000320) R32(w) = render_read32(w);
    else if (w == 0x04000184 || w == 0x04000180 || w == IO1) {
        extern void pxi7_prepare_read(u32 a);
        pxi7_prepare_read(w);
    } else if (w == 0x040001a4) {
    } else if (w == IO1 + 0x10) R32(w) = card_read_data();
}

static void forward_display(u32 w, u32 old) {
    u32 v = R32(w);
    if ((w >= 0x04000400 && w < 0x04000600) || w == 0x04000600) { sGxWrites++; render_write32(w, v); return; }
    if (w >= 0x04000240 && w < 0x0400024c) {
        for (int i = 0; i < 4; i++) {
            u8 b = v >> (8 * i), o = old >> (8 * i);
            if (b != o) { host_vram_control(w + i, b); render_write8(w + i, b); }
        }
        return;
    }
    for (int h = 0; h < 2; h++) {
        u16 n = v >> (16 * h), o = old >> (16 * h);
        if (n != o) render_write16(w + 2 * h, n);
    }
}
static int is_display(u32 w) {
    return (w < 0x04000070 && w != 0x04000004) || (w >= IOB && w < IOB + 0x70) || (w >= 0x04000240 && w < 0x0400024c) ||
           w == 0x04000304 || (w >= 0x04000320 && w < 0x040006a4);
}

static void io_spin_check(void) {
    if (++sTimeless < 1000000) return;
    static int reported;
    if (!reported++)
        fprintf(stderr, "host: %u register accesses without time passing (frame %llu, last from %p): the game spins; "
                "virtual time moves to the next event\n", sTimeless, (unsigned long long)host_frame(),
                (void *)io_last_caller());
    sTimeless = 0;
    host_advance_to_next_event();
}

static void io_write(u32 a, u32 old) {
    u32 w = a & ~3u;
    if (!sTimingLegacy) {
        sPollAddr = ~0u;
        io_spin_check();
    }
    static long logw = -2;
    if (logw == -2) logw = getenv("ACWW_IOLOG") ? strtol(getenv("ACWW_IOLOG"), 0, 16) : -1;
    if ((long)w == logw) fprintf(stderr, "io: frame %llu [%08x] %08x -> %08x\n", (unsigned long long)host_frame(), w, old, R32(w));
    if (is_display(w)) { forward_display(w, old); return; }
    switch (w) {
    case 0x04000214: { u32 v = R32(w); sIF &= ~v; R32(w) = sIF; break; }
    case 0x040000b8: dma_control_written(0); break;
    case 0x040000c4: dma_control_written(1); break;
    case 0x040000d0: dma_control_written(2); break;
    case 0x040000dc: dma_control_written(3); break;
    case 0x04000100: case 0x04000104: case 0x04000108: case 0x0400010c: {
        Timer *tm = &sTm[(w - 0x04000100) / 4];
        int i = (int)(tm - sTm);
        if ((a & 3) < 2) tm->reload = R16(w);
        u16 c = R16(w + 2);
        int on = c >> 7 & 1;
        if (on && !tm->on) { tm->start = sCycles; sLastTimerCheck[i] = sCycles; }
        tm->on = on; tm->irq = c >> 6 & 1; tm->shift = kTmShift[c & 3]; tm->cascade = i && (c >> 2 & 1);
        break;
    }
    case 0x04000180: pxi7_sync_written(R32(w)); break;
    case 0x04000184: break;
    case 0x04000188: pxi7_receive(R32(w)); break;
    case 0x040001a4: card_control_written(R32(w)); break;
    case 0x04000280: case 0x04000290: case 0x04000294: case 0x04000298: case 0x0400029c: divide(); break;
    case 0x040002b0: case 0x040002b8: case 0x040002bc: square_root(); break;
    default: break;
    }
}

static int sIoHist = -1;
static struct { u32 addr, write, n; uintptr_t pc; } sHist[4096];
struct IoLog { u32 addr, write; uintptr_t pc; };
static struct IoLog sRing[16];
static u32 sRingPos;
static void io_hist(u32 a, uintptr_t pc, int write) {
    u32 h = (a * 2654435761u ^ (u32)pc * 40503u ^ (u32)(pc >> 16 >> 16) ^ (u32)write) & 4095;
    for (u32 i = 0; i < 4096; i++, h = (h + 1) & 4095) {
        if (sHist[h].n && (sHist[h].addr != a || sHist[h].pc != pc || sHist[h].write != (u32)write)) continue;
        sHist[h].addr = a; sHist[h].pc = pc; sHist[h].write = (u32)write; sHist[h].n++;
        return;
    }
}
static void io_hist_dump(void) {
    static int done;
    if (sIoHist <= 0 || done) return;
    done = 1;
    FILE *f = fopen("acww_iohist.txt", "wb");
    if (!f) return;
    for (int i = 0; i < 4096; i++)
        if (sHist[i].n) fprintf(f, "%u %08x %08llx %c\n", sHist[i].n, sHist[i].addr, (unsigned long long)sHist[i].pc, sHist[i].write ? 'w' : 'r');
    fclose(f);
}
void host_io_ring_dump(void) {
    fprintf(stderr, "host: %llu I/O accesses; last ones:\n", (unsigned long long)sIoCount);
    for (int i = 0; i < 16; i++) {
        struct IoLog *l = &sRing[(sRingPos + i) & 15];
        fprintf(stderr, "  %s %08x from %08llx\n", l->write ? "write" : "read ", l->addr, (unsigned long long)l->pc);
    }
}
static uintptr_t io_last_caller(void) { return sRing[(sRingPos - 1) & 15].pc; }

void host_quit(void) {
    extern void snd7_output_close(void);
    snd7_output_close();
    extern void frontend_shutdown(void);
    frontend_shutdown();
    host_exit_dumps();
    fflush(NULL);
    _Exit(0);
}

void host_reset_system(void) {
    fprintf(stderr, "host: the game reset the system (frame %llu)%s\n", (unsigned long long)host_frame(),
            getenv("ACWW_HEADLESS") ? ": the run ends" : ": starting again");
    if (getenv("ACWW_HEADLESS")) host_quit();
    extern void snd7_output_close(void);
    snd7_output_close();
    extern void frontend_shutdown(void);
    frontend_shutdown();
    host_exit_dumps();
    fflush(NULL);
#if HOST_IOS
    extern void ios_fatal_message(const char *text);
    ios_fatal_message("The game restarted itself (this happens after a broken wireless connection). Open the app "
                      "again to go on playing.");
    exit(0);
#else
    extern char **gHostArgv;
    host_plat_restart(gHostArgv);
    host_fatal("the program couldn't start again");
#endif
}

void host_exit_dumps(void) {
    io_hist_dump();
    render_exit_report();
    host_guards_exit();
    host_debug_exit_dumps();
}

static u32 io_load(u32 a, u32 size) {
    io_read(a);
    return size == 1 ? *host_io(a) : size == 2 ? *(u16 *)host_io(a) : *(u32 *)host_io(a);
}
static void io_store(u32 a, u32 size, u32 v) {
    u32 old = R32(a & ~3u);
    if (size == 1) *host_io(a) = (u8)v;
    else if (size == 2) *(u16 *)host_io(a) = (u16)v;
    else *(u32 *)host_io(a) = v;
    io_write(a, old);
}
int host_irq_ready(void);
static inline void io_access_done(void) {
    if (host_irq_ready()) host_deliver_irqs();
}
static int sIoTrace = -1;
static FILE *sIoTraceFile;
HOST_STATE_KEEP(sIoTraceFile)
static u64 sTrHash = 0xcbf29ce484222325ull, sTrReads, sTrWrites;
static long sTrFrom = -1, sTrTo = -1;
static uintptr_t sTrCaller;
static void io_trace_init(void) {
    const char *e = getenv("ACWW_IOTRACE");
    sIoTrace = e && *e;
    if (!sIoTrace) return;
    if (!(sIoTraceFile = fopen(e, "wb"))) { sIoTrace = 0; return; }
    const char *r = getenv("ACWW_IOTRACE_FRAMES");
    if (r) sscanf(r, "%ld-%ld", &sTrFrom, &sTrTo);
}
static void io_trace_mix(u64 v) { sTrHash = (sTrHash ^ v) * 0x100000001b3ull; }
static void io_trace(u32 a, int write, void *caller) {
    io_trace_mix(a | (u64)write << 32);
    if (write) sTrWrites++; else sTrReads++;
    sTrCaller = (uintptr_t)caller;
}
static void io_trace_value(u32 a, int write, unsigned long long v) {
    int addrReg = (a >= 0x040000b0 && a < 0x040000e0 && (a - 0x040000b0) % 12 < 8) || (a & ~3u) == 0x04000188;
    if (!write || !addrReg) io_trace_mix(v);
    long f = (long)host_frame();
    if (f >= sTrFrom && f <= sTrTo)
        fprintf(sIoTraceFile, "%c %08x %llx %llu %llx\n", write ? 'w' : 'r', a, v, (unsigned long long)sCycles,
                (unsigned long long)(sTrCaller - (uintptr_t)&host_frame));
}
static void io_trace_frame(void) {
    if (sIoTrace < 0) io_trace_init();
    if (!sIoTrace) return;
    fprintf(sIoTraceFile, "frame %llu reads %llu writes %llu hash %016llx cycles %llu clock %u polls %u waits %u\n",
            (unsigned long long)host_frame(), (unsigned long long)sTrReads, (unsigned long long)sTrWrites,
            (unsigned long long)sTrHash, (unsigned long long)sCycles, sStatClockReads, sStatPolls, sStatWaits);
    fflush(sIoTraceFile);
    sTrReads = sTrWrites = 0;
    sStatClockReads = sStatPolls = sStatWaits = 0;
}

static void io_note(uintptr_t a, int write, void *caller) {
    if (a > 0xffffffffu || !is_io((u32)a)) {
        fprintf(stderr, "host: register access to %08llx (not an I/O register) from %p\n", (unsigned long long)a, caller);
        host_fatal("bad register address");
    }
    sIoCount++;
    if (sIoTrace > 0) io_trace((u32)a, write, caller);
    sRing[sRingPos++ & 15] = (struct IoLog){(u32)a, (u32)write, (uintptr_t)caller};
    if (sIoHist < 0) sIoHist = getenv("ACWW_IOHIST") != NULL;
    if (sIoHist) io_hist((u32)a, (uintptr_t)caller, write);
}
unsigned long long HostIo_Read(uintptr_t addr, unsigned int size) {
    u32 a = (u32)addr;
    if (sHBlankLine >= 0)
        return size == 8 ? io_load(a, 4) | (unsigned long long)io_load(a + 4, 4) << 32 : io_load(a, size);
    io_note(addr, 0, __builtin_return_address(0));
    unsigned long long v = size == 8 ? io_load(a, 4) | (unsigned long long)io_load(a + 4, 4) << 32 : io_load(a, size);
    if (sIoTrace > 0) io_trace_value(a, 0, v);
    io_access_done();
    return v;
}
unsigned long long HostIo_Write(uintptr_t addr, unsigned int size, unsigned long long v) {
    u32 a = (u32)addr;
    int traced = sHBlankLine < 0;
    if (traced) io_note(addr, 1, __builtin_return_address(0));
    if (traced && sIoTrace > 0) io_trace_value(a, 1, v);
    if (size == 8) {
        io_store(a, 4, (u32)v);
        io_store(a + 4, 4, (u32)(v >> 32));
    } else {
        io_store(a, size, (u32)v);
    }
    if (traced) io_access_done();
    return v;
}

int host_highmem(void) {
    static int on = -1;
    if (on < 0) {
#if defined(__x86_64__) && defined(__linux__)
        const char *e = getenv("ACWW_HIGHMEM");
        on = e && *e && strcmp(e, "0") ? 1 : 0;
#else
        on = 0;
#endif
    }
    return on;
}

static void highmem_poison(void) {
#if defined(__x86_64__) && defined(__linux__)
    static char maps[1 << 16];
    int fd = open("/proc/self/maps", O_RDONLY);
    if (fd < 0) host_fatal("ACWW_HIGHMEM: /proc/self/maps");
    size_t len = 0;
    for (ssize_t r; len < sizeof maps - 1 && (r = read(fd, maps + len, sizeof maps - 1 - len)) > 0;) len += (size_t)r;
    close(fd);
    maps[len] = 0;
    uintptr_t at = 0x10000;
    const uintptr_t top = 0x100000000ull;
    u64 reserved = 0;
    int ranges = 0;
    for (char *l = maps; at < top;) {
        unsigned long lo, hi;
        uintptr_t end = top;
        int last = sscanf(l, "%lx-%lx", &lo, &hi) != 2;
        if (!last) end = lo < top ? lo : top;
        if (end > at) {
            if (mmap((void *)at, end - at, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED_NOREPLACE,
                     -1, 0) != (void *)at)
                fprintf(stderr, "host: ACWW_HIGHMEM: can't reserve %08lx-%08lx\n", (unsigned long)at, (unsigned long)end);
            else { reserved += end - at; ranges++; }
        }
        if (last) break;
        if (lo < top) fprintf(stderr, "host: ACWW_HIGHMEM: mapped below 4 GB: %lx-%lx\n", lo, hi);
        if (hi > at) at = hi;
        char *nl = strchr(l, '\n');
        l = nl ? nl + 1 : l + strlen(l);
    }
    fprintf(stderr, "host: ACWW_HIGHMEM: %d ranges below 4 GB reserved (%llu MB of %llu MB)\n", ranges,
            (unsigned long long)(reserved >> 20), (unsigned long long)((top - 0x10000) >> 20));
#endif
}

void host_highmem_init(void) {
    if (host_highmem()) highmem_poison();
}

void host_map_memory(void) {
    {
        const char *e = getenv("ACWW_TIMING");
        sTimingLegacy = e && !strcmp(e, "legacy");
        if (sTimingLegacy) fprintf(stderr, "host: ACWW_TIMING=legacy: every register read takes time\n");
    }
    HostMem_Check();
    host_debug_init();
    R16(0x04000130) = 0x3ff;
    if (getenv("ACWW_IOHIST")) atexit(io_hist_dump);
}
