
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "host_mem.h"
#include "gpu2d/gpu2d.h"
#include "render.h"

void host_vram_control(u32 addr, u8 value);
const u32 *melon_screen(int screen);

static u32 sRng = 0x2545f491, sMask = 0xff;
static u32 sObjMask = 0xff, sObjCount = 128;
enum { O_AFFINE = 1, O_BITMAP = 2, O_8BPP = 4, O_MODES = 8 };
enum { T_WINDOWS = 1, T_EFFECTS = 2, T_MASTER = 4, T_MOSAIC = 8, T_OBJ = 16, T_BG = 32, T_DISPLAY = 64, T_POWER = 128 };
static u32 rnd(void) {
    sRng ^= sRng << 13;
    sRng ^= sRng >> 17;
    sRng ^= sRng << 5;
    return sRng;
}
static u32 rnd_below(u32 n) { return rnd() % n; }
static int chance(u32 percent) { return rnd_below(100) < percent; }

static void fill(u8 *p, u32 n) {
    for (u32 i = 0; i < n; i++) p[i] = chance(33) ? 0 : (u8)rnd();
}

static const u32 kVramCnt[9] = {0x04000240, 0x04000241, 0x04000242, 0x04000243, 0x04000244, 0x04000245, 0x04000246,
                                0x04000248, 0x04000249};
static u8 sCnt[9];
static u8 render_vramcnt(int i) { return sCnt[i]; }
static u8 bank_control(int i) {
    static const u8 kMst[9][5] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 4}, {0, 1, 4}, {0, 1, 2, 4}, {0, 1, 2, 4, 5},
                                  {0, 1, 2, 4, 5}, {0, 1, 2}, {0, 1, 2, 3}};
    static const u8 kCount[9] = {3, 3, 3, 3, 4, 5, 5, 3, 4};
    if (chance(10)) return 0;
    return (u8)(0x80 | kMst[i][rnd_below(kCount[i])] | rnd_below(4) << 3);
}

static void write_engine_registers(u32 base) {
    u8 r[0x70];
    fill(r, sizeof r);
    u32 dispcnt = rnd() & ~0x30080u;
    dispcnt |= (chance(85) || !(sMask & T_DISPLAY) ? 1u : rnd_below(4)) << 16;
    if (chance(5) && (sMask & T_DISPLAY)) dispcnt |= 0x80;
    if (!(sMask & T_WINDOWS)) dispcnt &= ~0xe000u;
    if (!(sMask & T_OBJ)) dispcnt &= ~0x1000u;
    if (!(sMask & T_BG)) dispcnt &= ~0xf00u;
    dispcnt &= ~8u;
    if (base == 0x04001000) {
        dispcnt &= ~(1u << 17 | 1u << 22 | 0x3fu << 24);
        if ((dispcnt & 7) > 5) dispcnt &= ~7u;
    } else if ((dispcnt & 7) == 7) {
        dispcnt &= ~7u;
    }
    memcpy(r, &dispcnt, 4);
    for (u32 a = 0x28; a < 0x40; a += 4) {
        if (a == 0x30 || a == 0x34) continue;
        r[a + 3] = (u8)((r[a + 3] & 0x0f) | (r[a + 3] & 0x08 ? 0xf0 : 0));
    }
    memset(r + 0x60, 0, 0x0c);
    if (!(sMask & T_EFFECTS)) memset(r + 0x50, 0, 6);
    if ((r[0x50] >> 6 & 3) == 1) r[0x50] &= ~0x20;
    if (!(sMask & T_MOSAIC)) for (int n = 0; n < 4; n++) r[0x08 + 2 * n] &= ~0x40;
    u16 master = chance(30) && (sMask & T_MASTER) ? (u16)(rnd() & 0xc01f) : 0;
    memcpy(r + 0x6c, &master, 2);
    for (u32 a = 0; a < 0x70; a += 2) render_write16(base + a, (u16)(r[a] | r[a + 1] << 8));
}

static void scene(void) {
    for (int i = 0; i < 9; i++) { host_vram_control(kVramCnt[i], 0x80); render_write8(kVramCnt[i], 0x80); }
    fill(HostVram_CpuPtr(0x06800000), 0xa4000);
    for (int i = 0; i < 9; i++) {
        u8 c = bank_control(i);
        if (i == 6 && (c & 0x87) == 0x85 && (sCnt[5] & 0x87) == 0x85) c = 0x80;
        sCnt[i] = c;
        host_vram_control(kVramCnt[i], c);
        render_write8(kVramCnt[i], c);
    }
    fill(gHostPltt, sizeof gHostPltt);
    fill(gHostOam, sizeof gHostOam);
    for (u32 i = 0; i < sizeof gHostOam; i += 8) {
        u8 *o = gHostOam + i;
        if ((o[1] >> 6) == 3) o[1] &= 0x3f;
        if (!(sMask & T_MOSAIC)) o[1] &= ~0x10;
        if (!(sObjMask & O_AFFINE)) o[1] &= ~0x01;
        if (!(sObjMask & O_8BPP)) o[1] &= ~0x20;
        int mode = o[1] >> 2 & 3;
        if ((mode == 3 && !(sObjMask & O_BITMAP)) || ((mode == 1 || mode == 2) && !(sObjMask & O_MODES))) o[1] &= ~0x0c;
        if ((i & 0x3ff) / 8 >= sObjCount) o[1] = (u8)((o[1] & ~0x01) | 0x02);
    }
    write_engine_registers(0x04000000);
    write_engine_registers(0x04001000);
    int power = sMask & T_POWER;
    render_write16(0x04000304, (u16)(0x020f | (chance(50) && power ? 0 : 0x8000) | (chance(5) && power ? 0 : 0x200)));
}

static void write_shots(const char *prefix, long n) {
    for (int r = 0; r < 2; r++) {
        char name[512];
        snprintf(name, sizeof name, "%s-%ld-%s.ppm", prefix, n, r ? "melon" : "own");
        FILE *f = fopen(name, "wb");
        if (!f) return;
        fprintf(f, "P6\n256 384\n255\n");
        for (int s = 0; s < 2; s++) {
            const u32 *px = r ? melon_screen(s) : gpu2d_screen(s);
            for (int i = 0; i < 256 * 192; i++) {
                u8 rgb[3] = {(u8)(px[i] >> 16), (u8)(px[i] >> 8), (u8)px[i]};
                fwrite(rgb, 1, 3, f);
            }
        }
        fclose(f);
    }
}

void render_selftest(long scenes) {
    if (getenv("ACWW_RENDER_SELFTEST_SEED")) sRng = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_SEED"), 0, 0) | 1;
    if (getenv("ACWW_RENDER_SELFTEST_MASK")) sMask = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_MASK"), 0, 0);
    if (getenv("ACWW_RENDER_SELFTEST_OBJ")) sObjMask = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_OBJ"), 0, 0);
    if (getenv("ACWW_RENDER_SELFTEST_OBJS")) sObjCount = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_OBJS"), 0, 0);
    long bad = 0;
    scene();
    render_frame();
    render_frame();
    for (long n = 0; n < scenes; n++) {
        scene();
        int differs = 0;
        for (int f = 0; f < 2; f++) {
            render_frame();
            differs |= render_compare(f ? "self-test (2nd frame) scene" : "self-test (1st frame) scene", (u64)n);
        }
        if (differs && getenv("ACWW_RENDER_SELFTEST_SHOTS")) write_shots(getenv("ACWW_RENDER_SELFTEST_SHOTS"), n);
        if (differs) {
            fprintf(stderr, "render-selftest: scene %ld: vramcnt", n);
            for (int i = 0; i < 9; i++) fprintf(stderr, " %02x", (unsigned)(render_vramcnt(i)));
            fprintf(stderr, " powcnt %04x; affine (A, B):", gpu2d_read32(0x04000304));
            for (u32 e = 0x04000000; e <= 0x04001000; e += 0x1000)
                for (u32 r = 0x20; r < 0x40; r += 4) fprintf(stderr, " %08x", gpu2d_read32(e + r));
            fprintf(stderr, "; oam (first entries, A, B):");
            for (u32 e = 0; e < 0x800; e += 0x400)
                for (u32 i = 0; i < sObjCount && i < 8; i++)
                    fprintf(stderr, " %04x.%04x.%04x", gHostOam[e + i * 8] | gHostOam[e + i * 8 + 1] << 8,
                            gHostOam[e + i * 8 + 2] | gHostOam[e + i * 8 + 3] << 8, gHostOam[e + i * 8 + 4] | gHostOam[e + i * 8 + 5] << 8);
            fprintf(stderr, "\n");
        }
        bad += differs;
    }
    fprintf(stderr, "render-selftest: %ld scenes, %ld differ\n", scenes, bad);
    render_exit_report();
    exit(bad ? 1 : 0);
}

void render_selftest_gpu2d(long scenes) {
    if (getenv("ACWW_RENDER_SELFTEST_SEED")) sRng = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_SEED"), 0, 0) | 1;
    if (getenv("ACWW_RENDER_SELFTEST_MASK")) sMask = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_MASK"), 0, 0);
    if (getenv("ACWW_RENDER_SELFTEST_OBJ")) sObjMask = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_OBJ"), 0, 0);
    if (getenv("ACWW_RENDER_SELFTEST_OBJS")) sObjCount = (u32)strtoul(getenv("ACWW_RENDER_SELFTEST_OBJS"), 0, 0);
    long bad = 0;
    for (long n = 0; n < scenes; n++) {
        scene();
        int differs = 0;
        for (int f = 0; f < 2; f++) {
            render_frame();
            differs |= render_check_gpu2d();
        }
        if (differs) {
            fprintf(stderr, "gpu2d-selftest: scene %ld differs: vramcnt", n);
            for (int i = 0; i < 9; i++) fprintf(stderr, " %02x", (unsigned)(render_vramcnt(i)));
            fprintf(stderr, " dispcnt %08x %08x\n", gpu2d_read32(0x04000000), gpu2d_read32(0x04001000));
        }
        bad += differs;
    }
    fprintf(stderr, "gpu2d-selftest: %ld scenes, %ld differ\n", scenes, bad);
    exit(bad ? 1 : 0);
}
