
#include "gpu2d_internal.h"

static const u8 kObjW[3][4] = {{8, 16, 32, 64}, {16, 32, 32, 64}, {8, 8, 16, 32}};
static const u8 kObjH[3][4] = {{8, 16, 32, 64}, {8, 8, 16, 32}, {16, 32, 32, 64}};

static u32 obj_texel(const Engine *e, u32 dispcnt, u16 a0, u16 a2, u32 u, u32 v, u32 w) {
    u32 tile = a2 & 0x3ffu;
    if ((a0 >> 10 & 3) == 3) {
        u32 addr;
        if (dispcnt & 0x40) {
            u32 step = e->num == 0 && (dispcnt & 1u << 22) ? 256 : 128;
            addr = tile * step + (v * w + u) * 2;
        } else if (dispcnt & 0x20) {
            addr = (tile & 0x1f) * 0x10 + (tile & 0x3e0) * 0x80 + v * 512 + u * 2;
        } else {
            addr = (tile & 0xf) * 0x10 + (tile & 0x3f0) * 0x80 + v * 256 + u * 2;
        }
        u16 c = obj16(e, addr);
        return c & 0x8000 ? (u32)OBJ_SRC_DIRECT << 16 | (c & 0x7fffu) : 0;
    }
    int color256 = a0 & 0x2000;
    u32 addr;
    if (dispcnt & 0x10) {
        addr = tile * (32u << (dispcnt >> 20 & 3)) + (v / 8 * (w / 8) + u / 8) * (color256 ? 64 : 32);
    } else {
        addr = tile * 32 + v / 8 * 1024 + u / 8 * (color256 ? 64 : 32);
    }
    if (color256) {
        u8 idx = obj8(e, addr + (v & 7) * 8 + (u & 7));
        if (!idx) return 0;
        if (dispcnt & 1u << 31) return (u32)OBJ_SRC_EXTPAL << 16 | ((a2 >> 12) * 256u + idx);
        return (u32)OBJ_SRC_PALETTE << 16 | idx;
    }
    u8 b = obj8(e, addr + (v & 7) * 4 + (u & 7) / 2);
    u8 idx = u & 1 ? b >> 4 : b & 15;
    return idx ? (u32)OBJ_SRC_PALETTE << 16 | ((a2 >> 12) * 16u + idx) : 0;
}

void gpu2d_render_obj_line(Engine *e, int line, ObjLine *dst) {
    memset(dst, 0, sizeof *dst);
    u32 dispcnt = reg32(e, REG_DISPCNT);
    if (line == 0) e->objMosaicLine = e->objMosaicCount = 0;
    if (!(dispcnt & 0x1000)) return;
    for (int i = 0; i < 128; i++) {
        const u8 *o = e->oam + i * 8;
        u16 a0 = (u16)(o[0] | o[1] << 8), a1 = (u16)(o[2] | o[3] << 8), a2 = (u16)(o[4] | o[5] << 8);
        int affine = a0 & 0x100, mode = a0 >> 10 & 3, shape = a0 >> 14;
        if ((!affine && (a0 & 0x200)) || shape == 3) continue;
        s32 w = kObjW[shape][a1 >> 14], h = kObjH[shape][a1 >> 14];
        s32 bw = w, bh = h;
        if (affine && (a0 & 0x200)) { bw *= 2; bh *= 2; }
        s32 rel = (line - (a0 & 0xff)) & 0xff;
        if (rel >= bh) continue;
        int mosaic = (a0 & 0x1000) && mode != 2;
        if (mosaic) {
            gpu2d_feature(e, F_OBJ_MOSAIC);
            rel = (e->objMosaicLine - (a0 & 0xff)) & 0xff;
        }
        s32 x0 = a1 & 0x1ff;
        if (x0 >= 256) x0 -= 512;
        u32 prio = a2 >> 10 & 3;
        gpu2d_feature(e, F_OBJ);
        if (mode == 1) gpu2d_feature(e, F_OBJ_SEMI);
        if (mode == 2) gpu2d_feature(e, F_OBJ_WINDOW);
        if (mode == 3) {
            gpu2d_feature(e, F_OBJ_BITMAP);
            if (!(a2 >> 12)) continue;
            if ((dispcnt & 0x60) == 0x60) continue;
        } else if (a0 & 0x2000) {
            gpu2d_feature(e, (dispcnt & 1u << 31) ? F_OBJ_EXTPAL : F_OBJ_8BPP);
        }
        if (!(dispcnt & 0x10) && mode != 3) gpu2d_feature(e, F_OBJ_2D);
        s32 pa = 0x100, pb = 0, pc = 0, pd = 0x100;
        if (affine) {
            const u8 *g = e->oam + (a1 >> 9 & 31) * 32;
            pa = (s16)(g[6] | g[7] << 8);
            pb = (s16)(g[14] | g[15] << 8);
            pc = (s16)(g[22] | g[23] << 8);
            pd = (s16)(g[30] | g[31] << 8);
            gpu2d_feature(e, (a0 & 0x200) ? F_OBJ_DOUBLE : F_OBJ_AFFINE);
        }
        for (s32 px = 0; px < bw; px++) {
            s32 sx = x0 + px;
            if (sx < 0 || sx >= SCREEN_W) continue;
            s32 tx = px;
            s32 u, v;
            if (affine) {
                s32 dx = tx - bw / 2, dy = rel - bh / 2;
                u = ((pa * dx + pb * dy) >> 8) + w / 2;
                v = ((pc * dx + pd * dy) >> 8) + h / 2;
                if (u < 0 || u >= w || v < 0 || v >= h) continue;
            } else {
                u = (a1 & 0x1000) ? w - 1 - tx : tx;
                v = (a1 & 0x2000) ? h - 1 - rel : rel;
                if (u < 0) continue;
            }
            u32 c = obj_texel(e, dispcnt, a0, a2, (u32)u, (u32)v, (u32)w);
            if (mode != 2) {
                u16 key = (u16)(prio * 128 + (u32)i + 1);
                if (key > dst->coverKey[sx]) {
                    dst->coverKey[sx] = key;
                    if (!dst->source[sx]) dst->mosaic[sx] = (u8)mosaic;
                }
            }
            if (!c) continue;
            if (mode == 2) { dst->window[sx] = 1; continue; }
            if (dst->source[sx] && prio >= dst->prio[sx]) continue;
            dst->value[sx] = (u16)c;
            dst->source[sx] = (u8)(c >> 16);
            dst->prio[sx] = (u8)prio;
            dst->kind[sx] = mode == 1 ? OBJ_SEMI_TRANSPARENT : mode == 3 ? OBJ_BITMAP : OBJ_NORMAL;
            dst->alpha[sx] = (u8)(a2 >> 12);
            dst->index[sx] = (u8)i;
            dst->mosaic[sx] = (u8)mosaic;
        }
    }
}
