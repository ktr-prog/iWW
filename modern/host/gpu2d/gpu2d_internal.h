
#ifndef GPU2D_INTERNAL_H
#define GPU2D_INTERNAL_H

#include <stdint.h>
#include <string.h>

#include "gpu2d.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t s16;
typedef int32_t s32;

enum { SCREEN_W = 256, SCREEN_H = 192, FRAME_LINES = 263 };
enum { GRANULE_SHIFT = 14, GRANULE = 1 << GRANULE_SHIFT };

enum {
    REG_DISPCNT = 0x00, REG_BGCNT = 0x08, REG_BGHOFS = 0x10, REG_BGVOFS = 0x12, REG_BG2PA = 0x20,
    REG_WIN0H = 0x40, REG_WIN1H = 0x42, REG_WIN0V = 0x44, REG_WIN1V = 0x46, REG_WININ = 0x48, REG_WINOUT = 0x4a,
    REG_MOSAIC = 0x4c, REG_BLDCNT = 0x50, REG_BLDALPHA = 0x52, REG_BLDY = 0x54, REG_DISPCAPCNT = 0x64,
    REG_MASTER_BRIGHT = 0x6c, REG_SIZE = 0x70,
};

enum { LAYER_BG0 = 0, LAYER_OBJ = 4, LAYER_BACKDROP = 5, LAYER_NONE = 7 };

enum { PIX_OPAQUE = 0x8000 };

enum { OBJ_NORMAL = 0, OBJ_SEMI_TRANSPARENT = 1, OBJ_BITMAP = 2 };

enum { OBJ_SRC_NONE = 0, OBJ_SRC_DIRECT = 1, OBJ_SRC_PALETTE = 2, OBJ_SRC_EXTPAL = 3 };

typedef struct ObjLine {
    u16 value[SCREEN_W];
    u8 source[SCREEN_W];
    u8 prio[SCREEN_W];
    u8 kind[SCREEN_W];
    u8 alpha[SCREEN_W];
    u8 index[SCREEN_W];
    u8 mosaic[SCREEN_W];
    u16 coverKey[SCREEN_W];
    u8 window[SCREEN_W];
} ObjLine;

typedef struct Engine {
    int num;
    u8 regs[REG_SIZE];
    const u8 *bgGran[32], *objGran[16];
    u32 bgMask, objMask;
    const u8 *bgExtPal[4];
    const u8 *objExtPal;
    const u8 *palette;
    const u8 *oam;
    s32 refX[2], refY[2];
    int refLine;
    u8 refWritten[2];
    u8 winActive[2];
    u16 bg[4][SCREEN_W];
    ObjLine obj;
    ObjLine objNextLine0;
    int haveNextLine0;
    int objMosaicLine, objMosaicCount;
    u32 out[SCREEN_W * SCREEN_H];
    u32 defer[SCREEN_W * SCREEN_H];
    u32 lineInfo[SCREEN_H];
    u8 dbgTop[SCREEN_W * SCREEN_H], dbgBelow[SCREEN_W * SCREEN_H], dbgEffect[SCREEN_W * SCREEN_H];
    u8 dbgObj[SCREEN_W * SCREEN_H], dbgAlpha[SCREEN_W * SCREEN_H];
    u32 dbgTopColor[SCREEN_W * SCREEN_H], dbgBelowColor[SCREEN_W * SCREEN_H];
} Engine;

static inline u16 reg16(const Engine *e, u32 off) { return (u16)(e->regs[off] | e->regs[off + 1] << 8); }
static inline u32 reg32(const Engine *e, u32 off) { return reg16(e, off) | (u32)reg16(e, off + 2) << 16; }

static inline u8 vram8(const u8 *const *gran, u32 mask, u32 addr) {
    addr &= mask;
    return gran[addr >> GRANULE_SHIFT][addr & (GRANULE - 1)];
}
static inline u16 vram16(const u8 *const *gran, u32 mask, u32 addr) {
    addr &= mask & ~1u;
    const u8 *p = gran[addr >> GRANULE_SHIFT] + (addr & (GRANULE - 1));
    return (u16)(p[0] | p[1] << 8);
}
static inline u8 bg8(const Engine *e, u32 a) { return vram8(e->bgGran, e->bgMask, a); }
static inline u16 bg16(const Engine *e, u32 a) { return vram16(e->bgGran, e->bgMask, a); }
static inline u8 obj8(const Engine *e, u32 a) { return vram8(e->objGran, e->objMask, a); }
static inline u16 obj16(const Engine *e, u32 a) { return vram16(e->objGran, e->objMask, a); }
static inline u16 pal16(const u8 *p, u32 index) { return (u16)(p[index * 2] | p[index * 2 + 1] << 8); }

enum Feature {
    F_MODE0, F_MODE1, F_MODE2, F_MODE3, F_MODE4, F_MODE5, F_MODE6, F_MODE7,
    F_3D, F_TEXT4, F_TEXT8, F_TEXT8_EXTPAL, F_AFFINE, F_EXT_TILES, F_EXT_TILES_EXTPAL, F_EXT_BITMAP8,
    F_EXT_DIRECT, F_LARGE_BITMAP, F_BG_MOSAIC, F_OBJ, F_OBJ_AFFINE, F_OBJ_DOUBLE, F_OBJ_8BPP, F_OBJ_EXTPAL,
    F_OBJ_BITMAP, F_OBJ_SEMI, F_OBJ_WINDOW, F_OBJ_MOSAIC, F_OBJ_2D, F_WIN0, F_WIN1, F_WINOBJ, F_ALPHA,
    F_BRIGHT_UP, F_BRIGHT_DOWN, F_MASTER_UP, F_MASTER_DOWN, F_FORCED_BLANK, F_DISPLAY_OFF, F_DISPLAY_VRAM,
    F_DISPLAY_FIFO, F_CAPTURE, F_ENGINE_B_OFF, F_ENGINE_A_OFF, F_COUNT
};
void gpu2d_feature(const Engine *e, enum Feature f);

void gpu2d_render_bg_line(Engine *e, int n, int line);
void gpu2d_render_obj_line(Engine *e, int line, ObjLine *dst);

#endif
