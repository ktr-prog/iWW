
#include <stdio.h>
#include <stdlib.h>

#include "gpu2d_internal.h"

static Engine sEngine[2];
static int sSingle, sSingleBlank, sA3dNow, sA3dPrev;
static u8 sSkyA[SCREEN_W * SCREEN_H];
int gHostSingleScreen;
static u16 sPowCnt;
static u8 sVramCnt[9];
static u32 sScreen[2][SCREEN_W * SCREEN_H];
static u32 sFrame;
static int sDefer3d;
static int sGpu;
static Gpu2dGpuFrame sGpuFrame;
static u8 sPalettes[GPU2D_MAX_VERSIONS][0x800], sOams[GPU2D_MAX_VERSIONS][0x800];
static u32 sDeferred[2][SCREEN_W * SCREEN_H * 2], sDeferredLines[2][SCREEN_H];
static int sDiagnostics;

void gpu2d_set_diagnostics(int on) { sDiagnostics = on; }

static u32 sFeatureFrame[2][F_COUNT];
static const char *const kFeatureNames[F_COUNT] = {
    "BG mode 0", "BG mode 1", "BG mode 2", "BG mode 3", "BG mode 4", "BG mode 5", "BG mode 6", "BG mode 7",
    "3D layer", "text BG 16 colours", "text BG 256 colours", "text BG extended palette", "affine BG",
    "extended BG 16-bit tiles", "extended BG tiles, extended palette", "extended BG 256-colour bitmap",
    "extended BG direct-colour bitmap", "large bitmap BG", "BG mosaic", "OBJ", "affine OBJ", "double-size OBJ",
    "256-colour OBJ", "OBJ extended palette", "bitmap OBJ", "semi-transparent OBJ", "OBJ window", "OBJ mosaic",
    "OBJ 2D tile mapping", "window 0", "window 1", "OBJ window enabled", "alpha blending", "brightness up",
    "brightness down", "master brightness up", "master brightness down", "forced blank", "display off",
    "VRAM display", "main memory display (not shown)", "display capture (not done)", "engine B off (POWCNT1)",
    "engine A off (POWCNT1)",
};
void gpu2d_feature(const Engine *e, enum Feature f) {
    if (!sFeatureFrame[e->num][f]) sFeatureFrame[e->num][f] = sFrame + 1;
}
void gpu2d_print_features(void) {
    for (int n = 0; n < 2; n++)
        for (int f = 0; f < F_COUNT; f++)
            if (sFeatureFrame[n][f])
                fprintf(stderr, "gpu2d: engine %c: %s (first in frame %u)\n", 'A' + n, kFeatureNames[f],
                        sFeatureFrame[n][f] - 1);
}

void gpu2d_reset(void) {
    memset(sEngine, 0, sizeof sEngine);
    sEngine[1].num = 1;
    sPowCnt = 0;
    memset(sVramCnt, 0, sizeof sVramCnt);
    memset(sScreen, 0, sizeof sScreen);
    sFrame = 0;
}

static void engine_write8(Engine *e, u32 off, u8 value) {
    e->regs[off] = value;
    if ((off & ~0x17u) == 0x28) e->refWritten[off >> 4 & 1] |= (u8)(1 << (off >> 2 & 1));
}
void gpu2d_write8(uint32_t addr, uint8_t value) {
    if (addr >= 0x04000000 && addr < 0x04000000 + REG_SIZE) engine_write8(&sEngine[0], addr - 0x04000000, value);
    else if (addr >= 0x04001000 && addr < 0x04001000 + REG_SIZE) engine_write8(&sEngine[1], addr - 0x04001000, value);
    else if (addr == 0x04000304) sPowCnt = (u16)((sPowCnt & 0xff00) | value);
    else if (addr == 0x04000305) sPowCnt = (u16)((sPowCnt & 0x00ff) | value << 8);
    else if (addr >= 0x04000240 && addr <= 0x04000246) sVramCnt[addr - 0x04000240] = value;
    else if (addr == 0x04000248 || addr == 0x04000249) sVramCnt[addr - 0x04000248 + 7] = value;
}
void gpu2d_write16(uint32_t addr, uint16_t value) {
    gpu2d_write8(addr, (u8)value);
    gpu2d_write8(addr + 1, (u8)(value >> 8));
}
void gpu2d_write32(uint32_t addr, uint32_t value) {
    gpu2d_write16(addr, (u16)value);
    gpu2d_write16(addr + 2, (u16)(value >> 16));
}
uint32_t gpu2d_read32(uint32_t addr) {
    if (addr >= 0x04000000 && addr + 4 <= 0x04000000 + REG_SIZE) return reg32(&sEngine[0], addr - 0x04000000);
    if (addr >= 0x04001000 && addr + 4 <= 0x04001000 + REG_SIZE) return reg32(&sEngine[1], addr - 0x04001000);
    if (addr == 0x04000304) return sPowCnt;
    if (addr == 0x04000240) return sVramCnt[0] | sVramCnt[1] << 8 | sVramCnt[2] << 16 | (u32)sVramCnt[3] << 24;
    if (addr == 0x04000244) return sVramCnt[4] | sVramCnt[5] << 8 | sVramCnt[6] << 16;
    if (addr == 0x04000248) return sVramCnt[7] | sVramCnt[8] << 8;
    return 0;
}

static const u32 kBankSize[9] = {0x20000, 0x20000, 0x20000, 0x20000, 0x10000, 0x4000, 0x4000, 0x8000, 0x4000};
static const u8 kZeroGranule[GRANULE];
enum { AREA_A_BG, AREA_A_OBJ, AREA_B_BG, AREA_B_OBJ, AREA_A_BGEXT, AREA_A_OBJEXT, AREA_B_BGEXT, AREA_B_OBJEXT,
       AREA_NONE };
static u8 sOverlap[32 + 16 + 8 + 8 + 10][GRANULE];
static int sOverlapUsed;

static void map_piece(const u8 **slot, const u8 *src, u32 size) {
    if (!*slot) { *slot = src; return; }
    if (sOverlapUsed == (int)(sizeof sOverlap / sizeof sOverlap[0])) return;
    u8 *c = sOverlap[sOverlapUsed++];
    for (u32 i = 0; i < size; i++) c[i] = (*slot)[i] | src[i];
    *slot = c;
}

static const u32 kMirrorFG[] = {0x8000, 0}, kMirrorH[] = {0x10000, 0}, kMirrorIBg[] = {0x4000, 0x10000, 0x14000, 0},
                 kMirrorIObj[] = {0x4000, 0x8000, 0xc000, 0x10000, 0x14000, 0x18000, 0x1c000, 0}, kMirrorNone[] = {0};

static int bank_target(int i, u8 c, u32 *ofs, const u32 **mirrors) {
    if (!(c & 0x80)) return AREA_NONE;
    u32 o = c >> 3 & 3, mst = c & ((i < 2 || i > 6) ? 3 : 7);
    *ofs = 0;
    *mirrors = kMirrorNone;
    if ((i == 5 || i == 6) && (mst == 1 || mst == 2)) *mirrors = kMirrorFG;
    else if (i == 7 && mst == 1) *mirrors = kMirrorH;
    else if (i == 8 && mst == 1) *mirrors = kMirrorIBg;
    else if (i == 8 && mst == 2) *mirrors = kMirrorIObj;
    switch (i) {
    case 0: case 1:
        if (mst == 1) { *ofs = 0x20000 * o; return AREA_A_BG; }
        if (mst == 2) { *ofs = 0x20000 * (o & 1); return AREA_A_OBJ; }
        break;
    case 2: case 3:
        if (mst == 1) { *ofs = 0x20000 * o; return AREA_A_BG; }
        if (mst == 4) return i == 2 ? AREA_B_BG : AREA_B_OBJ;
        break;
    case 4:
        if (mst == 1) return AREA_A_BG;
        if (mst == 2) return AREA_A_OBJ;
        if (mst == 4) return AREA_A_BGEXT;
        break;
    case 5: case 6:
        if (mst == 1 || mst == 2) { *ofs = 0x4000 * (o & 1) + 0x10000 * (o >> 1); return mst == 1 ? AREA_A_BG : AREA_A_OBJ; }
        if (mst == 4) { *ofs = 0x4000 * (o & 1); return AREA_A_BGEXT; }
        if (mst == 5) return AREA_A_OBJEXT;
        break;
    case 7:
        if (mst == 1) return AREA_B_BG;
        if (mst == 2) return AREA_B_BGEXT;
        break;
    case 8:
        if (mst == 1) { *ofs = 0x8000; return AREA_B_BG; }
        if (mst == 2) return AREA_B_OBJ;
        if (mst == 3) return AREA_B_OBJEXT;
        break;
    }
    return AREA_NONE;
}

static void map_vram(const Gpu2dFrameInput *in) {
    Engine *a = &sEngine[0], *b = &sEngine[1];
    const u8 *gran[4][32] = {{0}};
    const u8 *ext[4][4] = {{0}};
    static const u32 kAreaSize[4] = {0x80000, 0x40000, 0x20000, 0x20000};
    sOverlapUsed = 0;
    for (int i = 0; i < 9; i++) {
        u32 ofs;
        const u32 *mirrors;
        int area = bank_target(i, sVramCnt[i], &ofs, &mirrors);
        if (area == AREA_NONE) continue;
        const u8 *bank = in->bank[i];
        if (area <= AREA_B_OBJ) {
            for (int k = -1; k < 0 || mirrors[k]; k++)
                for (u32 o = 0; o < kBankSize[i]; o += GRANULE) {
                    u32 at = ofs + (k < 0 ? 0 : mirrors[k]) + o;
                    if (at < kAreaSize[area]) map_piece(&gran[area][at >> GRANULE_SHIFT], bank + o, GRANULE);
                }
        } else if (area == AREA_A_BGEXT || area == AREA_B_BGEXT) {
            u32 first = ofs / 0x2000, n = kBankSize[i] >= 0x8000 ? 4 : 2;
            for (u32 s = 0; s < n && first + s < 4; s++)
                map_piece(&ext[area - AREA_A_BGEXT][first + s], bank + s * 0x2000, 0x2000);
        } else {
            map_piece(&ext[area - AREA_A_BGEXT][0], bank, 0x2000);
        }
    }
    for (int n = 0; n < 32; n++) {
        a->bgGran[n] = gran[0][n] ? gran[0][n] : kZeroGranule;
        if (n < 16) a->objGran[n] = gran[1][n] ? gran[1][n] : kZeroGranule;
        if (n < 16) b->bgGran[n] = gran[2][n & 7] ? gran[2][n & 7] : kZeroGranule;
        if (n < 16) b->objGran[n] = gran[3][n & 7] ? gran[3][n & 7] : kZeroGranule;
    }
    a->bgMask = 0x7ffff; a->objMask = 0x3ffff;
    b->bgMask = 0x1ffff; b->objMask = 0x1ffff;
    for (int s = 0; s < 4; s++) { a->bgExtPal[s] = ext[0][s]; b->bgExtPal[s] = ext[2][s]; }
    a->objExtPal = ext[1][0];
    b->objExtPal = ext[3][0];
}

static const u8 *lcdc_bank(const Gpu2dFrameInput *in, int i) {
    return (sVramCnt[i] & 0x87) == 0x80 ? in->bank[i] : NULL;
}

static void window_vertical(Engine *e, int line) {
    for (int w = 0; w < 2; w++) {
        u16 v = reg16(e, w ? REG_WIN1V : REG_WIN0V);
        if ((line & 0xff) == (v & 0xff)) e->winActive[w] &= ~1;
        else if ((line & 0xff) == v >> 8) e->winActive[w] |= 1;
    }
}
static void window_line(Engine *e, const ObjLine *obj, u8 *mask) {
    u32 dispcnt = reg32(e, REG_DISPCNT);
    if (!(dispcnt & 0xe000)) { memset(mask, 0x3f, SCREEN_W); return; }
    u16 winin = reg16(e, REG_WININ), winout = reg16(e, REG_WINOUT);
    memset(mask, winout & 0x3f, SCREEN_W);
    if (dispcnt & 0x8000) {
        gpu2d_feature(e, F_WINOBJ);
        for (int x = 0; x < SCREEN_W; x++)
            if (obj->window[x]) mask[x] = winout >> 8 & 0x3f;
    }
    for (int w = 1; w >= 0; w--) {
        if (!(dispcnt & 0x2000u << w)) continue;
        gpu2d_feature(e, w ? F_WIN1 : F_WIN0);
        u16 h = reg16(e, w ? REG_WIN1H : REG_WIN0H);
        int x1 = h >> 8, x2 = h & 0xff;
        u8 in = (u8)(winin >> (8 * w) & 0x3f);
        for (int x = 0; x < SCREEN_W; x++) {
            if (x == x2 && !(sSingle && x1 == 0 && x2 == 0xff)) e->winActive[w] &= ~2;
            else if (x == x1) e->winActive[w] |= 2;
            if (e->winActive[w] == 3) mask[x] = in;
        }
    }
}

static void window_advance(Engine *e) {
    u32 dispcnt = reg32(e, REG_DISPCNT);
    if (!(dispcnt & 0xe000)) return;
    for (int w = 0; w < 2; w++) {
        if (!(dispcnt & 0x2000u << w)) continue;
        u16 h = reg16(e, w ? REG_WIN1H : REG_WIN0H);
        if ((h & 0xff) >= h >> 8) e->winActive[w] &= ~2;
        else e->winActive[w] |= 2;
    }
}

static inline u32 rgb6(u16 c) {
    return (u32)(c & 0x1f) << 1 | (u32)(c >> 5 & 0x1f) << 9 | (u32)(c >> 10 & 0x1f) << 17;
}
static inline u32 chan(u32 c, int i) { return c >> (8 * i) & 0x3f; }
static inline u32 pack(u32 r, u32 g, u32 b) { return r | g << 8 | b << 16; }
static u32 blend(u32 a, u32 b, u32 eva, u32 evb) {
    u32 o[3];
    for (int i = 0; i < 3; i++) {
        u32 v = (chan(a, i) * eva + chan(b, i) * evb + 8) >> 4;
        o[i] = v > 63 ? 63 : v;
    }
    return pack(o[0], o[1], o[2]);
}
static u32 blend3d(u32 a, u32 b, u32 alpha) {
    u32 eva = alpha + 1, evb = 31 - alpha, o[3];
    for (int i = 0; i < 3; i++) o[i] = (chan(a, i) * eva + chan(b, i) * evb + 16) >> 5;
    return pack(o[0], o[1], o[2]);
}
static u32 brighten(u32 c, u32 ev, u32 bias) {
    u32 o[3];
    for (int i = 0; i < 3; i++) o[i] = chan(c, i) + (((63 - chan(c, i)) * ev + bias) >> 4);
    return pack(o[0], o[1], o[2]);
}
static u32 darken(u32 c, u32 ev, u32 bias) {
    u32 o[3];
    for (int i = 0; i < 3; i++) o[i] = chan(c, i) - ((chan(c, i) * ev + bias) >> 4);
    return pack(o[0], o[1], o[2]);
}

static void obj_mosaic_x(const Engine *e, ObjLine *obj) {
    int w = (reg16(e, REG_MOSAIC) >> 8 & 15) + 1;
    if (w == 1) return;
    int last = 0;
    for (int x = 1; x < SCREEN_W; x++) {
        if (!(obj->mosaic[last] && obj->mosaic[x]) || x % w == 0) { last = x; continue; }
        obj->value[x] = obj->value[last];
        obj->source[x] = obj->source[last];
        obj->prio[x] = obj->prio[last];
        obj->kind[x] = obj->kind[last];
        obj->alpha[x] = obj->alpha[last];
        obj->index[x] = obj->index[last];
    }
}
static void obj_mosaic_y(Engine *e, int line) {
    int h = reg16(e, REG_MOSAIC) >> 12 & 15;
    if (e->objMosaicCount == h) { e->objMosaicCount = 0; e->objMosaicLine = line + 1; }
    else e->objMosaicCount = (e->objMosaicCount + 1) & 15;
}

static u16 obj_color(const Engine *e, u32 dispcnt, const ObjLine *obj, int x) {
    switch (obj->source[x]) {
    case OBJ_SRC_DIRECT: return obj->value[x];
    case OBJ_SRC_EXTPAL:
        if (dispcnt & 1u << 31) return e->objExtPal ? pal16(e->objExtPal, obj->value[x] & 0xfffu) : 0;
        /* fall through */
    case OBJ_SRC_PALETTE: return pal16(e->palette + 0x200, obj->value[x] & 0xffu);
    }
    return 0;
}

enum { DBG_3D = 6 };
enum { EFF_NONE, EFF_ALPHA, EFF_UP, EFF_DOWN, EFF_SEMI_OBJ, EFF_BITMAP_OBJ, EFF_3D };

static inline u32 pack18(u32 c) { return (c & 0x3f) | (c >> 8 & 0x3f) << 6 | (c >> 16 & 0x3f) << 12; }
static u32 deferred_3d(const ObjLine *obj, int x, int at, u32 col0, u8 lay0, int effOk, u32 first, u32 second,
                       u32 effect, u32 eva, u32 evb, u32 evy) {
    enum { KIND_C = 1u << 30, KIND_BLEND = 2u << 30, KIND_TOP = 3u << 30 };
    int below3d = second & 1;
    if (at == 1) {
        if (lay0 == LAYER_OBJ && obj->kind[x] != OBJ_NORMAL) {
            if (!below3d) return KIND_C | pack18(col0);
            u32 a = obj->kind[x] == OBJ_BITMAP ? obj->alpha[x] + 1u : eva, b = obj->kind[x] == OBJ_BITMAP ? 15u - obj->alpha[x] : evb;
            return KIND_BLEND | pack18(col0) | a << 18 | b << 23;
        }
        if (effOk && ((first >> lay0) & 1)) {
            if (effect == 1 && below3d) return KIND_BLEND | pack18(col0) | eva << 18 | evb << 23;
            if (effect == 2) return KIND_C | pack18(brighten(col0, evy, 8));
            if (effect == 3) return KIND_C | pack18(darken(col0, evy, 7));
        }
        return KIND_C | pack18(col0);
    }
    if ((second >> lay0) & 1) return KIND_TOP | pack18(col0) | 1u << 28;
    if (effOk && (first & 1) && (effect == 2 || effect == 3)) return KIND_TOP | evy << 18 | effect << 28;
    return KIND_TOP;
}

int gpu2d_tall_3d_ok(void) {
    u32 d = reg32(&sEngine[0], REG_DISPCNT);
    return !(sPowCnt & 0x8000) && (d & 8) && (d & 0x100) && !(d & 0x80);
}

static void compose_line(Engine *e, int line, const u32 *line3d, u32 *dst) {
    u32 dispcnt = reg32(e, REG_DISPCNT);
    const ObjLine *obj = &e->obj;
    u8 mask[SCREEN_W];
    window_line(e, obj, mask);
    obj_mosaic_x(e, &e->obj);
    int top3d = e->num == 1 && sSingle && line3d && sA3dPrev;
    int has3d = e->num == 0 && (dispcnt & 8) && (dispcnt & 0x100) && line3d;
    int defer3d = e->num == 0 && (dispcnt & 8) && (dispcnt & 0x100) && sDefer3d;
    if (has3d || defer3d) gpu2d_feature(e, F_3D);
    u32 *defer = e->defer + line * SCREEN_W;
    s32 hofs3d = reg16(e, REG_BGHOFS) & 0x1ff;
    if (hofs3d & 0x100) hofs3d -= 0x200;
    enum { OBJ_ORDER = 4 + 4, TOP3D = 7 };
    u8 order[4 * 5 + 1];
    int layers = 0;
    for (u32 p = 0; p < 4; p++) {
        if (dispcnt & 0x1000) order[layers++] = (u8)(OBJ_ORDER + p);
        for (int n = 0; n < 4; n++)
            if ((reg16(e, REG_BGCNT + 2 * n) & 3) == p && (dispcnt & 0x100u << n)) order[layers++] = (u8)n;
    }
    if (top3d) {
        u32 back = 0;
        for (int k = 0; k < layers; k++)
            if (order[k] < 4 && (reg16(e, REG_BGCNT + 2 * order[k]) & 3) > back) back = reg16(e, REG_BGCNT + 2 * order[k]) & 3;
        u8 o2[4 * 5 + 1];
        int m2 = 0;
        for (int k = 0; k < layers; k++)
            if (order[k] < 4 && (reg16(e, REG_BGCNT + 2 * order[k]) & 3) < back) o2[m2++] = order[k];
        o2[m2++] = TOP3D;
        for (int k = 0; k < layers; k++)
            if (order[k] >= OBJ_ORDER) o2[m2++] = order[k];
        for (int k = 0; k < layers; k++)
            if (order[k] < 4 && (reg16(e, REG_BGCNT + 2 * order[k]) & 3) >= back) o2[m2++] = order[k];
        memcpy(order, o2, (size_t)m2);
        layers = m2;
    }
    u16 bldcnt = reg16(e, REG_BLDCNT), bldalpha = reg16(e, REG_BLDALPHA);
    u32 effect = bldcnt >> 6 & 3, first = bldcnt & 0x3f, second = bldcnt >> 8 & 0x3f;
    u32 eva = bldalpha & 0x1f, evb = bldalpha >> 8 & 0x1f, evy = reg16(e, REG_BLDY) & 0x1f;
    if (eva > 16) eva = 16;
    if (evb > 16) evb = 16;
    if (evy > 16) evy = 16;
    u32 backdrop = rgb6(pal16(e->palette, 0));
    u32 effectsUsed = 0;
    for (int x = 0; x < SCREEN_W; x++) {
        u32 col[2] = {backdrop, backdrop};
        u8 lay[2] = {LAYER_BACKDROP, LAYER_BACKDROP};
        int is3d[2] = {0, 0}, found = 0, at3d = -1;
        u32 alpha3d = 0;
        u8 m = mask[x];
        for (int k = 0; k < layers && found < 2; k++) {
            int n = order[k];
            if (n >= OBJ_ORDER) {
                if ((m & 0x10) && obj->source[x] && obj->prio[x] == n - OBJ_ORDER) {
                    col[found] = rgb6(obj_color(e, dispcnt, obj, x));
                    lay[found++] = LAYER_OBJ;
                }
            } else if (n == TOP3D) {
                if (!(m & 1)) continue;
                u32 c = line3d[x];
                if (!(c >> 24 & 0x1f)) continue;
                if (!found) alpha3d = c >> 24 & 0x1f;
                is3d[found] = 1;
                col[found] = c & 0x3f3f3f;
                lay[found++] = LAYER_BG0;
            } else if (!(m & 1 << n)) {
                continue;
            } else if (n == 0 && defer3d) {
                s32 sx = x + hofs3d;
                if (sx >= 0 && sx < SCREEN_W && at3d < 0) at3d = found;
            } else if (n == 0 && has3d) {
                s32 sx = x + hofs3d;
                if (sx < 0 || sx >= SCREEN_W) continue;
                u32 c = line3d[sx];
                if (!(c >> 24 & 0x1f)) continue;
                if (!found) alpha3d = c >> 24 & 0x1f;
                is3d[found] = 1;
                col[found] = c & 0x3f3f3f;
                lay[found++] = LAYER_BG0;
            } else if (e->bg[n][x] & PIX_OPAQUE) {
                col[found] = rgb6(e->bg[n][x]);
                lay[found++] = (u8)n;
            }
        }
        if (sSingle && e->num == 0 && is3d[0]) sA3dNow = 1;
        if (sSingle && e->num == 0) sSkyA[line * SCREEN_W + x] = (u8)(is3d[0] && (line3d[x + hofs3d] >> 31));
        if (!found) lay[1] = LAYER_NONE;
        u32 out = col[0], eff = EFF_NONE;
        int effOk = m & 0x20, below2nd = (second >> lay[1]) & 1;
        if (lay[0] == LAYER_OBJ && obj->kind[x] != OBJ_NORMAL && below2nd) {
            if (obj->kind[x] == OBJ_BITMAP) {
                out = blend(col[0], col[1], obj->alpha[x] + 1u, 15u - obj->alpha[x]);
                eff = EFF_BITMAP_OBJ;
            } else {
                out = blend(col[0], col[1], eva, evb);
                eff = EFF_SEMI_OBJ;
            }
        } else if (is3d[0] && below2nd) {
            out = blend3d(col[0], col[1], alpha3d);
            eff = EFF_3D;
        } else if (effOk && ((first >> lay[0]) & 1)) {
            if (effect == 1 && below2nd) { out = blend(col[0], col[1], eva, evb); eff = EFF_ALPHA; }
            else if (effect == 2) { out = brighten(col[0], evy, 8); eff = EFF_UP; }
            else if (effect == 3) { out = darken(col[0], evy, 7); eff = EFF_DOWN; }
        }
        effectsUsed |= 1u << eff;
        dst[x] = out;
        if (defer3d) defer[x] = at3d < 0 ? 0 : deferred_3d(obj, x, at3d, col[0], lay[0], effOk, first, second, effect,
                                                         eva, evb, evy);
        if (sDiagnostics) {
            int at = line * SCREEN_W + x;
            e->dbgTop[at] = is3d[0] ? DBG_3D : lay[0];
            e->dbgBelow[at] = is3d[1] ? DBG_3D : lay[1];
            e->dbgEffect[at] = (u8)eff;
            e->dbgObj[at] = obj->index[x];
            e->dbgAlpha[at] = (u8)(is3d[0] ? alpha3d : obj->alpha[x]);
            e->dbgTopColor[at] = col[0];
            e->dbgBelowColor[at] = col[1];
        }
    }
    if (effectsUsed & (1u << EFF_ALPHA | 1u << EFF_SEMI_OBJ | 1u << EFF_BITMAP_OBJ | 1u << EFF_3D)) gpu2d_feature(e, F_ALPHA);
    if (effectsUsed & 1u << EFF_UP) gpu2d_feature(e, F_BRIGHT_UP);
    if (effectsUsed & 1u << EFF_DOWN) gpu2d_feature(e, F_BRIGHT_DOWN);
}

static void render_line(Engine *e, const Gpu2dFrameInput *in, int line) {
    u32 dispcnt = reg32(e, REG_DISPCNT), *dst = e->out + line * SCREEN_W;
    if (sGpu == 1) {
        e->lineInfo[line] = reg16(e, REG_MASTER_BRIGHT) | (u32)(reg16(e, REG_BGHOFS) & 0x1ff) << 16;
        if (e->num == 1 && !(sPowCnt & 0x200)) return;
        if (!(dispcnt & 0x80)) window_advance(e);
        obj_mosaic_y(e, line);
        return;
    }
    if (sDiagnostics) {
        memset(e->dbgTop + line * SCREEN_W, LAYER_NONE, SCREEN_W);
        memset(e->dbgEffect + line * SCREEN_W, EFF_NONE, SCREEN_W);
    }
    u32 *defer = e->defer + line * SCREEN_W;
    if (sDefer3d) {
        memset(defer, 0, SCREEN_W * sizeof *defer);
        e->lineInfo[line] = 0;
    }
    if (e->num == 1 && !(sPowCnt & 0x200)) {
        gpu2d_feature(e, F_ENGINE_B_OFF);
        if (sSingle) {
            const u32 *l3 = in->lines3dTop ? in->lines3dTop + line * SCREEN_W : NULL;
            for (int x = 0; x < SCREEN_W; x++) {
                u32 c = l3 ? l3[x] : 0, al = c >> 24 & 31;
                dst[x] = !al ? 0 : al == 31 ? c & 0x3f3f3f : blend3d(c & 0x3f3f3f, 0, al);
            }
            return;
        }
        for (int x = 0; x < SCREEN_W; x++) dst[x] = 0x3f3f3f;
        return;
    }
    if (e->num == 0 && !(sPowCnt & 2)) gpu2d_feature(e, F_ENGINE_A_OFF);
    if (e->num == 0 && (reg32(e, REG_DISPCAPCNT) & 1u << 31)) gpu2d_feature(e, F_CAPTURE);
    gpu2d_feature(e, (enum Feature)(F_MODE0 + (dispcnt & 7)));
    u32 composed[SCREEN_W];
    if (dispcnt & 0x80) {
        gpu2d_feature(e, F_FORCED_BLANK);
        for (int x = 0; x < SCREEN_W; x++) composed[x] = 0x3f3f3f;
    } else {
        for (int n = 0; n < 4; n++) gpu2d_render_bg_line(e, n, line);
        const u32 *l3 = e->num == 0 && in->lines3d ? in->lines3d + line * SCREEN_W
                      : e->num == 1 && sSingle && in->lines3dTop ? in->lines3dTop + line * SCREEN_W : NULL;
        compose_line(e, line, l3, composed);
    }
    obj_mosaic_y(e, line);
    u32 mode = dispcnt >> 16 & (e->num ? 1 : 3);
    if (sDefer3d && mode != 1) memset(defer, 0, SCREEN_W * sizeof *defer);
    if (mode == 1) {
        memcpy(dst, composed, sizeof composed);
    } else if (mode == 0) {
        gpu2d_feature(e, F_DISPLAY_OFF);
        for (int x = 0; x < SCREEN_W; x++) dst[x] = 0x3f3f3f;
        return;
    } else if (mode == 2) {
        gpu2d_feature(e, F_DISPLAY_VRAM);
        const u8 *bank = lcdc_bank(in, dispcnt >> 18 & 3);
        for (int x = 0; x < SCREEN_W; x++) dst[x] = bank ? rgb6(pal16(bank, (u32)(line * SCREEN_W + x))) : 0;
    } else {
        gpu2d_feature(e, F_DISPLAY_FIFO);
        memset(dst, 0, SCREEN_W * sizeof *dst);
    }
    u16 mb = reg16(e, REG_MASTER_BRIGHT);
    if (sSingle && e->num == 1) {
        const Engine *a = &sEngine[0];
        u32 da = reg32(a, REG_DISPCNT);
        mb = reg16(a, REG_MASTER_BRIGHT);
        if ((da & 0x80) || !(da >> 16 & 3))
            for (int x = 0; x < SCREEN_W; x++) dst[x] = 0x3f3f3f;
    }
    u32 f = mb & 0x1f;
    if (f > 16) f = 16;
    if (sDefer3d) {
        s32 hofs3d = reg16(e, REG_BGHOFS) & 0x1ff;
        e->lineInfo[line] = mb | (u32)hofs3d << 16;
        for (int x = 0; x < SCREEN_W; x++)
            if (defer[x]) composed[x] = dst[x];
    }
    if ((mb >> 14) == 1 && f) {
        gpu2d_feature(e, F_MASTER_UP);
        for (int x = 0; x < SCREEN_W; x++) dst[x] = brighten(dst[x], f, 0);
    } else if ((mb >> 14) == 2 && f) {
        gpu2d_feature(e, F_MASTER_DOWN);
        for (int x = 0; x < SCREEN_W; x++) dst[x] = darken(dst[x], f, 15);
    }
    if (sDefer3d)
        for (int x = 0; x < SCREEN_W; x++)
            if (defer[x]) dst[x] = composed[x];
}

static s32 ref28(const Engine *e, u32 off) { return (s32)(reg32(e, off) << 4) >> 4; }

static u32 gpu_offset(const Gpu2dFrameInput *in, const u8 *p) {
    static const u32 kOffset[9] = GPU2D_BANK_OFFSET;
    if (!p) return GPU2D_VRAM_ZERO;
    for (int i = 0; i < 9; i++)
        if (p >= in->bank[i] && p < in->bank[i] + kBankSize[i]) return kOffset[i] + (u32)(p - in->bank[i]);
    if (p >= sOverlap[0] && p < sOverlap[0] + sizeof sOverlap) return GPU2D_VRAM_OVERLAP + (u32)(p - sOverlap[0]);
    return GPU2D_VRAM_ZERO;
}
static void gpu_tables(const Gpu2dFrameInput *in) {
    Gpu2dGpuFrame *f = &sGpuFrame;
    for (int n = 0; n < 2; n++) {
        const Engine *e = &sEngine[n];
        u32 *t = f->tables[n];
        memset(t, 0, 64 * sizeof *t);
        for (int k = 0; k < 32; k++) t[G2T_BG + k] = gpu_offset(in, n == 0 || k < 16 ? e->bgGran[k] : NULL);
        for (int k = 0; k < 16; k++) t[G2T_OBJ + k] = gpu_offset(in, e->objGran[k]);
        for (int k = 0; k < 4; k++) t[G2T_BGEXT + k] = gpu_offset(in, e->bgExtPal[k]);
        t[G2T_OBJEXT] = gpu_offset(in, e->objExtPal);
        for (int k = 0; k < 4; k++) t[G2T_LCDC + k] = lcdc_bank(in, k) ? gpu_offset(in, in->bank[k]) : ~0u;
    }
    f->overlap = sOverlap[0];
    f->overlapSize = (u32)sOverlapUsed * GRANULE;
}
static u32 pack_obj(const ObjLine *o, int x) {
    return o->value[x] | (u32)o->source[x] << 16 | (u32)o->prio[x] << 18 | (u32)o->kind[x] << 20 |
           (u32)o->alpha[x] << 22 | (u32)(o->mosaic[x] & 1) << 26 | (u32)(o->window[x] & 1) << 27;
}
static void gpu_line(int n, int line) {
    const Engine *e = &sEngine[n];
    u32 *l = sGpuFrame.lines[n][line];
    memset(l, 0, GPU2D_LINE_WORDS * sizeof *l);
    for (int k = 0; k < REG_SIZE / 4; k++) l[G2L_REGS + k] = reg32(e, (u32)k * 4);
    for (int i = 0; i < 2; i++) l[G2L_REF + 2 * i] = (u32)e->refX[i], l[G2L_REF + 2 * i + 1] = (u32)e->refY[i];
    l[G2L_WIN] = (u32)(e->winActive[0] & 3) | (u32)(e->winActive[1] & 3) << 2;
    l[G2L_OBJMOSAIC] = (u32)e->objMosaicLine;
    l[G2L_PALETTE] = sGpuFrame.paletteCount - 1;
    l[G2L_OAM] = sGpuFrame.oamCount - 1;
    l[G2L_POWCNT] = sPowCnt;
}
static void gpu_versions(const Gpu2dFrameInput *in) {
    Gpu2dGpuFrame *f = &sGpuFrame;
    if (memcmp(sPalettes[f->paletteCount - 1], in->palette, 0x800) && f->paletteCount < GPU2D_MAX_VERSIONS)
        memcpy(sPalettes[f->paletteCount++], in->palette, 0x800);
    if (memcmp(sOams[f->oamCount - 1], in->oam, 0x800) && f->oamCount < GPU2D_MAX_VERSIONS)
        memcpy(sOams[f->oamCount++], in->oam, 0x800);
}
const Gpu2dGpuFrame *gpu2d_gpu_frame(void) { return &sGpuFrame; }

static void single_compose(const Gpu2dFrameInput *in) {
    (void)in;
    static u32 ref[SCREEN_W];
    static int haveRef;
    if (!(reg32(&sEngine[1], REG_DISPCNT) & 0xe000) || !haveRef) {
        memcpy(ref, sEngine[1].out + (SCREEN_H - 1) * SCREEN_W, sizeof ref);
        haveRef = 1;
    }
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++)
        if (sSkyA[i]) sEngine[0].out[i] = ref[i % SCREEN_W];
}

void gpu2d_render_frame(const Gpu2dFrameInput *in) {
    sGpu = in->gpu;
    sDefer3d = in->defer3d || sGpu;
    static int off = -1;
    if (off < 0) off = getenv("ACWW_SINGLE") && atoi(getenv("ACWW_SINGLE")) == 0;
    {
        static int hold, swapped;
        int now = !off && !sGpu && !sDefer3d && in->lines3d && gpu2d_tall_3d_ok();
        swapped = (sPowCnt & 0x8000) ? swapped + 1 : 0;
        if (now) hold = 120;
        else if (hold && swapped > 8) hold = 0;
        else if (hold) hold--;
        sSingle = now || (hold && !off && !sGpu && !sDefer3d);
        sSingleBlank = sSingle && !now;
    }
    gHostSingleScreen = sSingle;
    sA3dPrev = sA3dNow;
    sA3dNow = 0;
    map_vram(in);
    if (sGpu) {
        gpu_tables(in);
        sGpuFrame.palettes = sPalettes[0];
        sGpuFrame.oams = sOams[0];
        memcpy(sPalettes[0], in->palette, 0x800);
        memcpy(sOams[0], in->oam, 0x800);
        sGpuFrame.paletteCount = sGpuFrame.oamCount = 1;
        sGpuFrame.tables[0][G2T_SCREEN_A] = 0;
    }
    for (int n = 0; n < 2; n++) {
        Engine *e = &sEngine[n];
        e->palette = in->palette + 0x400 * n;
        e->oam = in->oam + 0x400 * n;
        for (int i = 0; i < 2; i++) {
            e->refX[i] = ref28(e, 0x28 + 0x10 * (u32)i);
            e->refY[i] = ref28(e, 0x2c + 0x10 * (u32)i);
            e->refWritten[i] = 0;
        }
        e->refLine = 0;
    }
    for (int n = 0; n < 2; n++) {
        Engine *e = &sEngine[n];
        for (int line = SCREEN_H + 1; line < FRAME_LINES; line++) window_vertical(e, line);
        gpu2d_render_obj_line(e, 0, &e->objNextLine0);
        e->haveNextLine0 = 1;
        if (sGpu)
            for (int x = 0; x < SCREEN_W; x++) sGpuFrame.obj0[n][x] = pack_obj(&e->objNextLine0, x);
    }
    for (int line = 0; line < SCREEN_H; line++) {
        for (int n = 0; n < 2; n++) {
            Engine *e = &sEngine[n];
            window_vertical(e, line);
            if (sGpu) gpu_line(n, line);
            if (sGpu == 1) {}
            else if (line == 0 && e->haveNextLine0) e->obj = e->objNextLine0;
            else if (line == 0) memset(&e->obj, 0, sizeof e->obj);
            else gpu2d_render_obj_line(e, line, &e->obj);
            render_line(e, in, line);
        }
        if (in->hblank) in->hblank(line, in->hblankContext);
        if (sGpu) gpu_versions(in);
        for (int n = 0; n < 2; n++) {
            Engine *e = &sEngine[n];
            for (int i = 0; i < 2; i++) {
                u32 r = REG_BG2PA + 0x10 * (u32)i;
                e->refX[i] = e->refWritten[i] & 1 ? ref28(e, 0x28 + 0x10 * (u32)i)
                                                  : e->refX[i] + (s16)reg16(e, r + 2) * (line + 1 - e->refLine);
                e->refY[i] = e->refWritten[i] & 2 ? ref28(e, 0x2c + 0x10 * (u32)i)
                                                  : e->refY[i] + (s16)reg16(e, r + 6) * (line + 1 - e->refLine);
                e->refWritten[i] = 0;
            }
            e->refLine = line + 1;
        }
    }
    for (int n = 0; n < 2; n++) {
        Engine *e = &sEngine[n];
        window_vertical(e, SCREEN_H);
    }
    if (sGpu) sGpuFrame.tables[0][G2T_SCREEN_A] = (sPowCnt & 0x8000) ? 0 : 1;
    if (sSingleBlank) {
        const Engine *a = &sEngine[0];
        u32 c = 0;
        u16 mb = reg16(a, REG_MASTER_BRIGHT);
        u32 f = mb & 0x1f;
        if (f > 16) f = 16;
        if ((mb >> 14) == 1 && f) c = brighten(c, f, 0);
        else if ((mb >> 14) == 2 && f) c = darken(c, f, 15);
        for (int n = 0; n < 2; n++)
            for (int i = 0; i < SCREEN_W * SCREEN_H; i++) sEngine[n].out[i] = c;
    } else if (sSingle) single_compose(in);
    for (int n = 0; n < 2; n++) {
        int screen = (sPowCnt & 0x8000) ? n : 1 - n;
        if (sGpu == 1) {
            memcpy(sDeferredLines[screen], sEngine[n].lineInfo, sizeof sEngine[n].lineInfo);
            continue;
        }
        if (sDefer3d) {
            const Engine *e = &sEngine[n];
            u32 *d = sDeferred[screen];
            for (int i = 0; i < SCREEN_W * SCREEN_H; i++) d[2 * i] = pack18(e->out[i]), d[2 * i + 1] = e->defer[i];
            memcpy(sDeferredLines[screen], e->lineInfo, sizeof e->lineInfo);
            continue;
        }
        u32 *s = sScreen[screen];
        const u32 *src = sEngine[n].out;
        for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
            u32 c = src[i], r = c & 0x3f, g = c >> 8 & 0x3f, b = c >> 16 & 0x3f;
            r = r << 2 | r >> 4; g = g << 2 | g >> 4; b = b << 2 | b >> 4;
            s[i] = 0xff000000u | r << 16 | g << 8 | b;
        }
    }
    sFrame++;
}

const uint32_t *gpu2d_screen(int screen) { return sScreen[screen & 1]; }
const uint32_t *gpu2d_deferred(int screen) { return sDeferred[screen & 1]; }
const uint32_t *gpu2d_deferred_lines(int screen) { return sDeferredLines[screen & 1]; }

void gpu2d_describe_pixel(int screen, int x, int y, char *buf, size_t size) {
    int n = (sPowCnt & 0x8000) ? screen : 1 - screen;
    const Engine *e = &sEngine[n];
    static const char *const kLayer[8] = {"BG0", "BG1", "BG2", "BG3", "OBJ", "backdrop", "3D", "none"};
    static const char *const kEffect[7] = {"none", "alpha", "brightness up", "brightness down",
                                           "semi-transparent OBJ", "bitmap OBJ alpha", "3D alpha"};
    int at = y * SCREEN_W + x;
    char top[16];
    if (e->dbgTop[at] == LAYER_OBJ) snprintf(top, sizeof top, "OBJ#%u", e->dbgObj[at]);
    else snprintf(top, sizeof top, "%s", kLayer[e->dbgTop[at] & 7]);
    u32 dispcnt = reg32(e, REG_DISPCNT);
    snprintf(buf, size, "engine %c (mode %u, dispcnt %08x, bldcnt %04x %04x %04x, master %04x): %s %06x (alpha %u) "
             "over %s %06x, effect %s", 'A' + n, dispcnt & 7, dispcnt, reg16(e, REG_BLDCNT), reg16(e, REG_BLDALPHA),
             reg16(e, REG_BLDY), reg16(e, REG_MASTER_BRIGHT), top, e->dbgTopColor[at], e->dbgAlpha[at],
             kLayer[e->dbgBelow[at] & 7], e->dbgBelowColor[at], kEffect[e->dbgEffect[at] % 7]);
    size_t used = strlen(buf);
    if (e->dbgTop[at] == LAYER_OBJ && e->oam) {
        const u8 *o = e->oam + e->dbgObj[at] * 8;
        used += (size_t)snprintf(buf + used, size - used, "; OBJ attributes %04x %04x %04x", o[0] | o[1] << 8,
                                 o[2] | o[3] << 8, o[4] | o[5] << 8);
        if (o[1] & 1) {
            const u8 *g = e->oam + ((o[2] | o[3] << 8) >> 9 & 31) * 32;
            used += (size_t)snprintf(buf + used, size - used, " (matrix %04x %04x %04x %04x)", g[6] | g[7] << 8,
                                     g[14] | g[15] << 8, g[22] | g[23] << 8, g[30] | g[31] << 8);
        }
    }
    used += (size_t)snprintf(buf + used, size - used, "; bgcnt %04x %04x %04x %04x", reg16(e, REG_BGCNT),
                             reg16(e, REG_BGCNT + 2), reg16(e, REG_BGCNT + 4), reg16(e, REG_BGCNT + 6));
    if (dispcnt & 0xe000)
        snprintf(buf + used, size - used, "; windows %04x %04x / %04x %04x in %04x out %04x", reg16(e, REG_WIN0H),
                 reg16(e, REG_WIN0V), reg16(e, REG_WIN1H), reg16(e, REG_WIN1V), reg16(e, REG_WININ),
                 reg16(e, REG_WINOUT));
}
