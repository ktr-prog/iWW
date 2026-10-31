#include "types.h"
#include "sys/DebugText.h"
#include "sys/OSThread.h"
#include "sys/QNode.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_020b7f7c.h"
#include "proto/main/unk_020e0408.h"

typedef volatile u16 vu16;
typedef volatile u32 vu32;


extern "C" {
void GX_LoadBG1Char(void *a, u32 b, u32 c);
void GXS_LoadBG1Char(void *a, u32 b, u32 c);
void GX_LoadBGPltt(void *a, u32 b, u32 c);
void GXS_LoadBGPltt(void *a, u32 b, u32 c);
void G2x_SetBlendBrightnessExt_(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
}


struct Gfx2dWindowRect {
    u8 left, top, right, bottom, planes;
};

struct Gfx2dAffine {
    s32 mtx[4];
    s32 centerX, centerY, offsetX, offsetY;
};

struct Gfx2dOffset {
    u16 x, y;
};

struct Gfx2dState {
    Gfx2dOffset mainBg0, mainBg1;
    Gfx2dAffine mainBg2, mainBg3;
    Gfx2dOffset subBg0, subBg1;
    Gfx2dAffine subBg2, subBg3;
    u8 affineMask, offsetDirty;
    u16 windowDirty;
    u8 mainPlanes, subPlanes, mainBgMode, subBgMode, mainWindows, subWindows, mainWinOutPlanes, subWinOutPlanes,
        mainObjWinPlanes, subObjWinPlanes;
    Gfx2dWindowRect mainWin0, mainWin1, subWin0, subWin1;
    u8 blendRequest, blendPlane1;
    s8 blendPlane2;
    u8 blendEv1;
};

extern "C" {
u32 GXS_SetGraphicsMode(u32 a);
u32 GX_SetGraphicsMode(u32 a, u32 b, u32 c);
void G3X_SetHOffset(u32 a);
void G2x_SetBGyAffine_(u32 reg, void* mtx, s32 a, s32 b, s32 c, s32 d);
void G2x_SetBlendBrightnessExt_(u32 reg, u32 a, u32 b, u32 c, u32 d, u32 e);
void G2x_SetBlendAlpha_(u32 reg, u32 a, s32 b, u32 c, u32 d);
void G2x_SetBlendBrightness_(u32 reg, u32 a, s32 b);
void GX_LoadBGPltt(void *p, u32 a, u32 b);
void GXS_LoadBGPltt(void *p, u32 a, u32 b);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void DC_FlushRange(void *p, u32 size);
void GX_LoadBG2Char(void *a, u32 b, u32 c);
void GX_LoadBG3Char(void *a, u32 b, u32 c);
void GXS_LoadBG0Char(void *a, u32 b, u32 c);
void GXS_LoadBG2Char(void *a, u32 b, u32 c);
void GXS_LoadBG3Char(void *a, u32 b, u32 c);
void GX_LoadOBJ(void *a, u32 b, u32 c);
void GXS_LoadOBJ(void *a, u32 b, u32 c);
void GX_LoadBG1Scr(void *a, u32 b, u32 c);
void GX_LoadBG2Scr(void *a, u32 b, u32 c);
void GX_LoadBG3Scr(void *a, u32 b, u32 c);
void GXS_LoadBG0Scr(void *a, u32 b, u32 c);
void GXS_LoadBG1Scr(void *a, u32 b, u32 c);
void GXS_LoadBG2Scr(void *a, u32 b, u32 c);
void GXS_LoadBG3Scr(void *a, u32 b, u32 c);
void GX_LoadOBJPltt(void *a, u32 b, u32 c);
void GXS_LoadOBJPltt(void *a, u32 b, u32 c);
}

u8 sGfx2dBackdropColor[4];
Gfx2dState sGfx2d;

extern "C" void Gfx2d_InitBgOffset(Gfx2dOffset* p);
extern "C" void Gfx2d_InitBgAffine(Gfx2dAffine* p);
extern "C" void Gfx2d_InitWindowRect(Gfx2dWindowRect* p);

extern "C" s32 Gfx2d_GetLayerBgIndex(u32 n) {
    switch (n) {
    case 3: return 0;
    case 0: case 4: return 1;
    case 1: case 5: return 2;
    case 2: case 6: return 3;
    case 7: case 8: return 4;
    default: return 0;
    }
}

extern "C" s32 Gfx2d_GetLayerPlaneMask(u32 n) {
    switch (n) {
    case 3: return 1;
    case 0: case 4: return 2;
    case 1: case 5: return 4;
    case 2: case 6: return 8;
    case 7: case 8: return 0x10;
    default: return 1;
    }
}

extern "C" s32 Gfx2d_GetLayerBlendMask(u32 n) {
    switch (n) {
    case 3: return 1;
    case 0: case 4: return 2;
    case 1: case 5: return 4;
    case 2: case 6: return 8;
    case 7: case 8: return 0x10;
    default: return 1;
    }
}

extern "C" s32 Gfx2d_LoadPaletteFile(const char *p0, void *p1, u32 p2, s32 p3, u8 e, u8 f) {
    u8 *buf = (u8 *)File_LoadAlloc(p0, p1, -4, 0);
    s32 r = Gfx2d_LoadPaletteRange(buf, p2, p3, e, f);
    Heap_Free((Heap *)p1, buf);
    return r;
}

extern "C" s32 Gfx2d_LoadPaletteFileSlot(const char *p0, void *p1, u32 p2, s32 p3, u8 e) {
    u32 out;
    u8 *buf = (u8 *)File_LoadAlloc(p0, p1, -4, &out);
    u8 *q = buf;
    q += p3 * 32;
    s32 r = Gfx2d_LoadPaletteRange(q, p2, e, e, e);
    Heap_Free((Heap *)p1, buf);
    return r;
}

extern "C" s32 Gfx2d_LoadScreenFile(const char *p0, void *p1, u32 p2) {
    u32 out;
    u8 *buf = (u8 *)File_LoadAlloc(p0, p1, -4, &out);
    s32 r = Gfx2d_LoadScreen(buf, p2, out, 0);
    Heap_Free((Heap *)p1, buf);
    return r;
}

extern "C" s32 Gfx2d_LoadCharFile(const char *p0, void *p1, u32 p2, s32 p3, s32 e, s32 f) {
    u32 out;
    u8 *buf = (u8 *)File_LoadAlloc(p0, p1, -4, &out);
    s32 r = Gfx2d_LoadCharRange(buf, p2, p3, e, f);
    Heap_Free((Heap *)p1, buf);
    return r;
}

extern "C" s32 Gfx2d_LoadCharFile8bpp(const char *p0, void *p1, u32 p2, s32 p3, s32 a, s32 b) {
    return Gfx2d_LoadCharFile(p0, p1, p2, p3 << 1, a << 1, (b << 1) + 1);
}

extern "C" s32 Gfx2d_LoadPaletteRange(u8 *dst, u32 n, s32 a, s32 b, u8 c) {
    u8 *p = dst + (b - a) * 32;
    s32 off, len;
    len = (c - b + 1) * 32;
    off = b * 32;
    DC_FlushRange(p, len);
    if (n == 7) {
        GX_LoadOBJPltt(p, off, len);
    } else if (n == 8) {
        GXS_LoadOBJPltt(p, off, len);
    } else if (n <= 2) {
        if (off == 0) {
            off = 2;
            len -= 2;
            p += 2;
        }
        GX_LoadBGPltt(p, off, len);
    } else if (n <= 6) {
        if (off == 0) {
            off = 2;
            len -= 2;
            p += 2;
        }
        GXS_LoadBGPltt(p, off, len);
    }
    return 1;
}

extern "C" s32 Gfx2d_LoadScreen(u8 *dst, u32 n, s32 size, s32 x) {
    DC_FlushRange(dst, size);
    switch (n) {
    case 0: GX_LoadBG1Scr(dst, x, size); break;
    case 1: GX_LoadBG2Scr(dst, x, size); break;
    case 2: GX_LoadBG3Scr(dst, x, size); break;
    case 3: GXS_LoadBG0Scr(dst, x, size); break;
    case 4: GXS_LoadBG1Scr(dst, x, size); break;
    case 5: GXS_LoadBG2Scr(dst, x, size); break;
    case 6: GXS_LoadBG3Scr(dst, x, size); break;
    }
    return 1;
}

extern "C" s32 Gfx2d_LoadCharRange(u8 *dst, u32 n, s32 a, s32 b, s32 c) {
    u8 *p = dst + (b - a) * 32;
    s32 off, len;
    len = (*(volatile s32 *)&c - b + 1) * 32;
    off = b * 32;
    DC_FlushRange(p, len);
    switch (n) {
    case 0: GX_LoadBG1Char(p, off, len); break;
    case 1: GX_LoadBG2Char(p, off, len); break;
    case 2: GX_LoadBG3Char(p, off, len); break;
    case 3: GXS_LoadBG0Char(p, off, len); break;
    case 4: GXS_LoadBG1Char(p, off, len); break;
    case 5: GXS_LoadBG2Char(p, off, len); break;
    case 6: GXS_LoadBG3Char(p, off, len); break;
    case 7: GX_LoadOBJ(p, off, len); break;
    case 8: GXS_LoadOBJ(p, off, len); break;
    }
    return 1;
}

extern "C" void Gfx2d_SetLayerPriority(u32 n, u32 v) {
    switch (n) {
    case 0: IO_W((vu16 *)0x0400000a, (IO_R((vu16 *)0x0400000a) & ~3) | v); break;
    case 1: IO_W((vu16 *)0x0400000c, (IO_R((vu16 *)0x0400000c) & ~3) | v); break;
    case 2: IO_W((vu16 *)0x0400000e, (IO_R((vu16 *)0x0400000e) & ~3) | v); break;
    case 3: IO_W((vu16 *)0x04001008, (IO_R((vu16 *)0x04001008) & ~3) | v); break;
    case 4: IO_W((vu16 *)0x0400100a, (IO_R((vu16 *)0x0400100a) & ~3) | v); break;
    case 5: IO_W((vu16 *)0x0400100c, (IO_R((vu16 *)0x0400100c) & ~3) | v); break;
    case 6: IO_W((vu16 *)0x0400100e, (IO_R((vu16 *)0x0400100e) & ~3) | v); break;
    }
}

extern "C" void Gfx2d_SetLayerControl(u32 n, u32 a, u32 b, u32 c) {
    switch (n) {
    case 0: IO_W((vu16 *)0x0400000a, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400000a) & 0x43) | (a << 14)) | 0x500)); break;
    case 1: IO_W((vu16 *)0x0400000c, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400000c) & 0x43) | (a << 14)) | 0x600)); break;
    case 2: IO_W((vu16 *)0x0400000e, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400000e) & 0x43) | (a << 14)) | 0x700)); break;
    case 3: IO_W((vu16 *)0x04001008, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x04001008) & 0x43) | (a << 14)) | 0xc00)); break;
    case 4: IO_W((vu16 *)0x0400100a, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400100a) & 0x43) | (a << 14)) | 0xd00)); break;
    case 5: IO_W((vu16 *)0x0400100c, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400100c) & 0x43) | (a << 14)) | 0xe00)); break;
    case 6: IO_W((vu16 *)0x0400100e, (c << 2) | ((b << 7) | ((IO_R((vu16 *)0x0400100e) & 0x43) | (a << 14)) | 0xf00)); break;
    }
}

extern "C" void Gfx2d_SetLayerOffset(u32 n, u32 a, u32 b) {
    switch (n) {
    case 0: Gfx2d_SetMainBg1Offset(a, b); break;
    case 1: Gfx2d_SetMainBg2Offset(a, b); break;
    case 2: Gfx2d_SetMainBg3Offset(a, b); break;
    case 3: Gfx2d_SetSubBg0Offset(a, b); break;
    case 4: Gfx2d_SetSubBg1Offset(a, b); break;
    case 5: Gfx2d_SetSubBg2Offset(a, b); break;
    case 6: Gfx2d_SetSubBg3Offset(a, b); break;
    }
}

extern "C" void Gfx2d_SetWindowRect(u32 n, u32 a, u32 b, u32 c, u32 d) {
    switch (n) {
    case 0: Gfx2d_SetMainWin0Rect(a, b, c, d); break;
    case 1: Gfx2d_SetMainWin1Rect(a, b, c, d); break;
    case 2: Gfx2d_SetSubWin0Rect(a, b, c, d); break;
    case 3: Gfx2d_SetSubWin1Rect(a, b, c, d); break;
    }
}

extern "C" void Gfx2d_ResetLayer(u32 n) {
    Gfx2d_HideLayer(n);
    Gfx2d_SetLayerOffset(n, 0, 0);
}

extern "C" void Gfx2d_HideLayer(u32 n) {
    switch (n) {
    case 0: Gfx2d_HideMainPlanes(2); break;
    case 1: Gfx2d_HideMainPlanes(4); break;
    case 2: Gfx2d_HideMainPlanes(8); break;
    case 7: Gfx2d_HideMainPlanes(0x10); break;
    case 3: Gfx2d_HideSubPlanes(1); break;
    case 4: Gfx2d_HideSubPlanes(2); break;
    case 5: Gfx2d_HideSubPlanes(4); break;
    case 6: Gfx2d_HideSubPlanes(8); break;
    case 8: Gfx2d_HideSubPlanes(0x10); break;
    }
}

extern "C" void Gfx2d_ShowLayer(u32 n) {
    switch (n) {
    case 0: Gfx2d_ShowMainPlanes(2); break;
    case 1: Gfx2d_ShowMainPlanes(4); break;
    case 2: Gfx2d_ShowMainPlanes(8); break;
    case 7: Gfx2d_ShowMainPlanes(0x10); break;
    case 3: Gfx2d_ShowSubPlanes(1); break;
    case 4: Gfx2d_ShowSubPlanes(2); break;
    case 5: Gfx2d_ShowSubPlanes(4); break;
    case 6: Gfx2d_ShowSubPlanes(8); break;
    case 8: Gfx2d_ShowSubPlanes(0x10); break;
    }
}

extern "C" void Gfx2d_LinearToTiles4bppBytes(u8 *src, u8 *dst, s32 w, s32 h) {
    s32 k, col, row, j, base, p, q;
    k = 0;
    base = 0;
    for (row = 0; row < h; row++) {
        p = base;
        for (col = 0; col < w; col++) {
            q = p;
            for (j = 0; j < 8; j++) {
                MI_CpuCopy8(src + q, dst + k, 4);
                k += 4;
                q += w * 4;
            }
            p += 4;
        }
        base += w << 5;
    }
}

extern "C" void Gfx2d_TilesInRow32ToLinear(u32 *src, u32 *dst, s32 x, s32 w, s32 h) {
    s32 k, row, s, j, c, base, idx;
    k = 0; base = x * 8;
    for (row = 0; row < h; row++) {
        s = base;
        for (j = 0; j < 8; j++) {
            idx = s;
            for (c = 0; c < w; c++) {
                dst[k] = src[idx];
                k++;
                idx += 8;
            }
            s++;
        }
        base += 0x100;
    }
}

extern "C" void Gfx2d_LinearToTilesInRow32(u32 *src, u32 *dst, s32 x, s32 w, s32 h) {
    s32 k, row, s, j, c, base, idx;
    k = 0;
    base = x * 8;
    for (row = 0; row < h; row++) {
        s = base;
        for (j = 0; j < 8; j++) {
            idx = s;
            for (c = 0; c < w; c++) {
                dst[idx] = src[k];
                k++;
                idx += 8;
            }
            s++;
        }
        base += 0x100;
    }
}

extern "C" void Gfx2d_LinearToTiles4bpp(u32 *src, u32 *dst, s32 w, s32 h) {
    s32 k, row, s, j, c, base, idx;
    k = 0; base = 0;
    for (row = 0; row < h; row++) {
        s = base;
        for (j = 0; j < 8; j++) {
            idx = s;
            for (c = 0; c < w; c++) {
                dst[idx] = src[k];
                k++;
                idx += 8;
            }
            s++;
        }
        base += w * 8;
    }
}

extern "C" void Gfx2d_TilesToLinear4bpp(u32 *src, u32 *dst, s32 w, s32 h) {
    s32 k, row, s, j, c, base, idx;
    k = 0; base = 0;
    for (row = 0; row < h; row++) {
        s = base;
        for (j = 0; j < 8; j++) {
            idx = s;
            for (c = 0; c < w; c++) {
                u32 t = src[idx];
                dst[k] = t;
                k++;
                idx += 8;
            }
            s++;
        }
        base += w * 8;
    }
}

extern "C" void Gfx2d_LoadBackdropColor(void) {
    GX_LoadBGPltt(sGfx2dBackdropColor, 0, 2);
    GXS_LoadBGPltt(sGfx2dBackdropColor, 0, 2);
}

extern "C" void Gfx2d_ResetState() {
    sGfx2d.mainPlanes = 0;
    sGfx2d.subPlanes = 0;
    sGfx2d.mainWindows = 0;
    sGfx2d.subWindows = 0;
    sGfx2d.mainWinOutPlanes = 0;
    sGfx2d.subWinOutPlanes = 0;
    sGfx2d.mainObjWinPlanes = 0;
    sGfx2d.subObjWinPlanes = 0;
    sGfx2d.mainBgMode = 0;
    sGfx2d.subBgMode = 1;
    Gfx2d_InitBgOffset(&sGfx2d.mainBg0);
    Gfx2d_InitBgOffset(&sGfx2d.mainBg1);
    Gfx2d_InitBgAffine(&sGfx2d.mainBg2);
    Gfx2d_InitBgAffine(&sGfx2d.mainBg3);
    Gfx2d_InitBgOffset(&sGfx2d.subBg0);
    Gfx2d_InitBgOffset(&sGfx2d.subBg1);
    Gfx2d_InitBgAffine(&sGfx2d.subBg2);
    Gfx2d_InitBgAffine(&sGfx2d.subBg3);
    Gfx2d_InitWindowRect(&sGfx2d.mainWin0);
    Gfx2d_InitWindowRect(&sGfx2d.mainWin1);
    Gfx2d_InitWindowRect(&sGfx2d.subWin0);
    Gfx2d_InitWindowRect(&sGfx2d.subWin1);
    sGfx2d.affineMask = 0;
    sGfx2d.offsetDirty = 0xff;
    sGfx2d.windowDirty = 0xff;
    sGfx2d.blendRequest = 0;
    sGfx2d.blendPlane2 = 0;
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetMainBgModeState(1);
}

extern "C" void Gfx2d_BeginFrame() {}

extern "C" void Gfx2d_ApplyDisplayControl() {
    GX_SetGraphicsMode(1, sGfx2d.mainBgMode, 1);
    GXS_SetGraphicsMode(sGfx2d.subBgMode);
    IO_W((volatile u32*)0x4000000, (IO_R((volatile u32*)0x4000000) & 0xffffe0ff) | (sGfx2d.mainPlanes << 8));
    IO_W((volatile u32*)0x4001000, (IO_R((volatile u32*)0x4001000) & 0xffffe0ff) | (sGfx2d.subPlanes << 8));
    IO_W((volatile u32*)0x4000000, (IO_R((volatile u32*)0x4000000) & 0xffff1fff) | (sGfx2d.mainWindows << 13));
    IO_W((volatile u32*)0x4001000, (IO_R((volatile u32*)0x4001000) & 0xffff1fff) | (sGfx2d.subWindows << 13));
    IO_W((volatile u16*)0x400004a, (IO_R((volatile u16*)0x400004a) & ~0x3f) | sGfx2d.mainWinOutPlanes | 0x20);
    IO_W((volatile u16*)0x400104a, (IO_R((volatile u16*)0x400104a) & ~0x3f) | sGfx2d.subWinOutPlanes | 0x20);
    IO_W((volatile u16*)0x400004a, (IO_R((volatile u16*)0x400004a) & 0xffffc0ff) | (sGfx2d.mainObjWinPlanes << 8));
    IO_W((volatile u16*)0x400104a, (IO_R((volatile u16*)0x400104a) & 0xffffc0ff) | (sGfx2d.subObjWinPlanes << 8));
}

extern "C" void Gfx2d_FlushRegisters() {
    if (sGfx2d.offsetDirty != 0) {
        if (sGfx2d.offsetDirty & 1) {
            if ((IO_R((volatile u32*)0x4000000) & 8) == 0) {
                IO_W((volatile u32*)0x4000010, (sGfx2d.mainBg0.x & 0x1ff) | ((sGfx2d.mainBg0.y << 16) & 0x1ff0000));
            } else {
                G3X_SetHOffset(sGfx2d.mainBg0.x);
            }
        }
        if (sGfx2d.offsetDirty & 2) {
            IO_W((volatile u32*)0x4000014, (sGfx2d.mainBg1.x & 0x1ff) | ((sGfx2d.mainBg1.y << 16) & 0x1ff0000));
        }
        if (sGfx2d.offsetDirty & 4) {
            if (sGfx2d.affineMask & 1) {
                G2x_SetBGyAffine_(0x4000020, &sGfx2d.mainBg2, sGfx2d.mainBg2.centerX, sGfx2d.mainBg2.centerY,
                              sGfx2d.mainBg2.offsetX, sGfx2d.mainBg2.offsetY);
            } else {
                IO_W((volatile u32*)0x4000018, (sGfx2d.mainBg2.offsetX & 0x1ff) | ((sGfx2d.mainBg2.offsetY << 16) & 0x1ff0000));
            }
        }
        if (sGfx2d.offsetDirty & 8) {
            if (sGfx2d.affineMask & 2) {
                G2x_SetBGyAffine_(0x4000030, &sGfx2d.mainBg3, sGfx2d.mainBg3.centerX, sGfx2d.mainBg3.centerY,
                              sGfx2d.mainBg3.offsetX, sGfx2d.mainBg3.offsetY);
            } else {
                IO_W((volatile u32*)0x400001c, (sGfx2d.mainBg3.offsetX & 0x1ff) | ((sGfx2d.mainBg3.offsetY << 16) & 0x1ff0000));
            }
        }
        if (sGfx2d.offsetDirty & 0x10) {
            IO_W((volatile u32*)0x4001010, (sGfx2d.subBg0.x & 0x1ff) | ((sGfx2d.subBg0.y << 16) & 0x1ff0000));
        }
        if (sGfx2d.offsetDirty & 0x20) {
            IO_W((volatile u32*)0x4001014, (sGfx2d.subBg1.x & 0x1ff) | ((sGfx2d.subBg1.y << 16) & 0x1ff0000));
        }
        if (sGfx2d.offsetDirty & 0x40) {
            if (sGfx2d.affineMask & 4) {
                G2x_SetBGyAffine_(0x4001020, &sGfx2d.subBg2, sGfx2d.subBg2.centerX, sGfx2d.subBg2.centerY,
                              sGfx2d.subBg2.offsetX, sGfx2d.subBg2.offsetY);
            } else {
                IO_W((volatile u32*)0x4001018, (sGfx2d.subBg2.offsetX & 0x1ff) | ((sGfx2d.subBg2.offsetY << 16) & 0x1ff0000));
            }
        }
        if (sGfx2d.offsetDirty & 0x80) {
            if (sGfx2d.affineMask & 8) {
                G2x_SetBGyAffine_(0x4001030, &sGfx2d.subBg3, sGfx2d.subBg3.centerX, sGfx2d.subBg3.centerY,
                              sGfx2d.subBg3.offsetX, sGfx2d.subBg3.offsetY);
            } else {
                IO_W((volatile u32*)0x400101c, (sGfx2d.subBg3.offsetX & 0x1ff) | ((sGfx2d.subBg3.offsetY << 16) & 0x1ff0000));
            }
        }
        sGfx2d.offsetDirty = 0;
    }
    if (sGfx2d.windowDirty != 0) {
        if (sGfx2d.windowDirty & 0x1) {
            IO_W((volatile u16*)0x4000048, (IO_R((volatile u16*)0x4000048) & ~0x3f) | sGfx2d.mainWin0.planes | 0x20);
        }
        if (sGfx2d.windowDirty & 0x2) {
            IO_W((volatile u16*)0x4000048, (IO_R((volatile u16*)0x4000048) & 0xffffc0ff) | (sGfx2d.mainWin1.planes << 8) | 0x2000);
        }
        if (sGfx2d.windowDirty & 0x4) {
            IO_W((volatile u16*)0x4001048, (IO_R((volatile u16*)0x4001048) & ~0x3f) | sGfx2d.subWin0.planes | 0x20);
        }
        if (sGfx2d.windowDirty & 0x100) {
            IO_W((volatile u16*)0x4001048, (IO_R((volatile u16*)0x4001048) & ~0x3f) | sGfx2d.subWin0.planes);
        }
        if (sGfx2d.windowDirty & 0x8) {
            IO_W((volatile u16*)0x4001048, (IO_R((volatile u16*)0x4001048) & 0xffffc0ff) | (sGfx2d.subWin1.planes << 8) | 0x2000);
        }
        if (sGfx2d.windowDirty & 0x200) {
            IO_W((volatile u16*)0x4001048, (IO_R((volatile u16*)0x4001048) & 0xffffc0ff) | (sGfx2d.subWin1.planes << 8));
        }
        if (sGfx2d.windowDirty & 0x10) {
            u32 d = sGfx2d.mainWin0.bottom;
            u32 b = sGfx2d.mainWin0.top;
            u32 a = sGfx2d.mainWin0.left;
            IO_W((volatile u16*)0x4000040, ((a << 8) & 0xff00) | (sGfx2d.mainWin0.right & 0xff));
            IO_W((volatile u16*)0x4000044, ((b << 8) & 0xff00) | (d & 0xff));
        }
        if (sGfx2d.windowDirty & 0x20) {
            u32 d = sGfx2d.mainWin1.bottom;
            u32 b = sGfx2d.mainWin1.top;
            u32 a = sGfx2d.mainWin1.left;
            IO_W((volatile u16*)0x4000042, ((a << 8) & 0xff00) | (sGfx2d.mainWin1.right & 0xff));
            IO_W((volatile u16*)0x4000046, ((b << 8) & 0xff00) | (d & 0xff));
        }
        if (sGfx2d.windowDirty & 0x40) {
            u32 d = sGfx2d.subWin0.bottom;
            u32 b = sGfx2d.subWin0.top;
            u32 a = sGfx2d.subWin0.left;
            IO_W((volatile u16*)0x4001040, ((a << 8) & 0xff00) | (sGfx2d.subWin0.right & 0xff));
            IO_W((volatile u16*)0x4001044, ((b << 8) & 0xff00) | (d & 0xff));
        }
        if (sGfx2d.windowDirty & 0x80) {
            u32 d = sGfx2d.subWin1.bottom;
            u32 b = sGfx2d.subWin1.top;
            u32 a = sGfx2d.subWin1.left;
            IO_W((volatile u16*)0x4001042, ((a << 8) & 0xff00) | (sGfx2d.subWin1.right & 0xff));
            IO_W((volatile u16*)0x4001046, ((b << 8) & 0xff00) | (d & 0xff));
        }
        sGfx2d.windowDirty = 0;
    }
    u32 t = sGfx2d.blendRequest;
    if (t & 0x20) {
        G2x_SetBlendBrightnessExt_(0x4000050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if (t & 0x10) {
        G2x_SetBlendAlpha_(0x4000050, sGfx2d.blendPlane1, sGfx2d.blendPlane2, sGfx2d.blendEv1,
                      0x10 - sGfx2d.blendEv1);
    } else if (t & 0x2) {
        G2x_SetBlendBrightnessExt_(0x4001050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if (t & 0x8) {
        G2x_SetBlendAlpha_(0x4001050, sGfx2d.blendPlane1, sGfx2d.blendPlane2, sGfx2d.blendEv1,
                      0x10 - sGfx2d.blendEv1);
    } else if (t != 0) {
        G2x_SetBlendBrightness_(0x4001050, sGfx2d.blendPlane1, sGfx2d.blendPlane2);
    }
    sGfx2d.blendRequest = 0;
}

extern "C" void Gfx2d_InitBgOffset(Gfx2dOffset* p) {
    p->x = 0;
    p->y = 0;
}

extern "C" void Gfx2d_InitBgAffine(Gfx2dAffine* p) {
    p->mtx[0] = 0x1000;
    p->mtx[1] = 0;
    p->mtx[2] = 0;
    p->mtx[3] = 0x1000;
    p->centerX = 0;
    p->centerY = 0;
    p->offsetX = 0;
    p->offsetY = 0;
}

extern "C" void Gfx2d_InitWindowRect(Gfx2dWindowRect* p) {
    p->left = 0;
    p->top = 0;
    p->right = 0xff;
    p->bottom = 0xc0;
    p->planes = 0;
}

extern "C" void Gfx2d_SetMainBg1Offset(u32 a, u32 b) {
    sGfx2d.offsetDirty |= 0x2;
    sGfx2d.mainBg1.x = a;
    sGfx2d.mainBg1.y = b;
}

extern "C" void Gfx2d_SetMainBg2Offset(s32 a, s32 b) {
    sGfx2d.offsetDirty |= 0x4;
    sGfx2d.mainBg2.offsetX = a;
    sGfx2d.mainBg2.offsetY = b;
}

extern "C" void Gfx2d_SetMainBg3Offset(s32 a, s32 b) {
    sGfx2d.offsetDirty |= 0x8;
    sGfx2d.mainBg3.offsetX = a;
    sGfx2d.mainBg3.offsetY = b;
}

extern "C" void Gfx2d_SetSubBg0Offset(u32 a, u32 b) {
    sGfx2d.offsetDirty |= 0x10;
    sGfx2d.subBg0.x = a;
    sGfx2d.subBg0.y = b;
}

extern "C" void Gfx2d_SetSubBg1Offset(u32 a, u32 b) {
    sGfx2d.offsetDirty |= 0x20;
    sGfx2d.subBg1.x = a;
    sGfx2d.subBg1.y = b;
}

extern "C" void Gfx2d_SetSubBg2Offset(s32 a, s32 b) {
    sGfx2d.offsetDirty |= 0x40;
    sGfx2d.subBg2.offsetX = a;
    sGfx2d.subBg2.offsetY = b;
}

extern "C" void Gfx2d_SetSubBg3Offset(s32 a, s32 b) {
    sGfx2d.offsetDirty |= 0x80;
    sGfx2d.subBg3.offsetX = a;
    sGfx2d.subBg3.offsetY = b;
}

extern "C" void Gfx2d_SetMainWin0Planes(u32 a) {
    sGfx2d.mainWin0.planes = a;
    sGfx2d.windowDirty |= 0x1;
}

extern "C" void Gfx2d_SetMainWin1Planes(u32 a) {
    sGfx2d.mainWin1.planes = a;
    sGfx2d.windowDirty |= 0x2;
}

extern "C" void Gfx2d_SetSubWin0Planes(u32 a, BOOL b) {
    sGfx2d.subWin0.planes = a;
    Gfx2d_MarkSubWin0PlanesDirty(b);
}

extern "C" void Gfx2d_SetSubWin1Planes(u32 a, BOOL b) {
    sGfx2d.subWin1.planes = a;
    Gfx2d_MarkSubWin1PlanesDirty(b);
}

extern "C" void Gfx2d_MarkSubWin0PlanesDirty(BOOL a) {
    u32 v;
    if (a) {
        v = 0x4;
    } else {
        v = 0x100;
    }
    sGfx2d.windowDirty |= v;
}

extern "C" void Gfx2d_MarkSubWin1PlanesDirty(BOOL a) {
    u32 v;
    if (a) {
        v = 0x8;
    } else {
        v = 0x200;
    }
    sGfx2d.windowDirty |= v;
}

extern "C" void Gfx2d_SetMainWinOutPlanes(u32 a) { sGfx2d.mainWinOutPlanes = a; }

extern "C" void Gfx2d_RemoveMainWinOutPlanes(u32 a) { sGfx2d.mainWinOutPlanes &= ~a; }

extern "C" void Gfx2d_SetSubWinOutPlanes(u32 a) { sGfx2d.subWinOutPlanes = a; }

extern "C" void Gfx2d_SetMainObjWinPlanes(u32 a) { sGfx2d.mainObjWinPlanes = a; }

extern "C" void Gfx2d_SetSubObjWinPlanes(u32 a) { sGfx2d.subObjWinPlanes = a; }

extern "C" void Gfx2d_SetMainWin0Rect(u32 a, u32 b, u32 c, u32 d) {
    sGfx2d.mainWin0.left = a;
    sGfx2d.mainWin0.top = b;
    sGfx2d.mainWin0.right = c;
    sGfx2d.mainWin0.bottom = d;
    sGfx2d.windowDirty |= 0x10;
}

extern "C" void Gfx2d_SetMainWin1Rect(u32 a, u32 b, u32 c, u32 d) {
    sGfx2d.mainWin1.left = a;
    sGfx2d.mainWin1.top = b;
    sGfx2d.mainWin1.right = c;
    sGfx2d.mainWin1.bottom = d;
    sGfx2d.windowDirty |= 0x20;
}

extern "C" void Gfx2d_SetSubWin0Rect(u32 a, u32 b, u32 c, u32 d) {
    sGfx2d.subWin0.left = a;
    sGfx2d.subWin0.top = b;
    sGfx2d.subWin0.right = c;
    sGfx2d.subWin0.bottom = d;
    sGfx2d.windowDirty |= 0x40;
}

extern "C" void Gfx2d_SetSubWin1Rect(u32 a, u32 b, u32 c, u32 d) {
    sGfx2d.subWin1.left = a;
    sGfx2d.subWin1.top = b;
    sGfx2d.subWin1.right = c;
    sGfx2d.subWin1.bottom = d;
    sGfx2d.windowDirty |= 0x80;
}

extern "C" void Gfx2d_SetMainBgModeState(u32 a) {
    sGfx2d.mainBgMode = a;
    sGfx2d.affineMask = (sGfx2d.affineMask & ~0x3) | ((0xf78u >> (a * 2)) & 0x3);
}

extern "C" void Gfx2d_SetSubBgModeState(u32 a) {
    sGfx2d.subBgMode = a;
    sGfx2d.affineMask = (sGfx2d.affineMask & ~0xc) | ((0x3de0u >> (a * 2)) & 0xc);
}

extern "C" void Gfx2d_SetMainBgMode(u32 a) {
    Gfx2d_SetMainBgModeState(a);
    GX_SetGraphicsMode(1, a, 1);
}

extern "C" void Gfx2d_SetSubBgMode(u32 a) {
    Gfx2d_SetSubBgModeState(a);
    GXS_SetGraphicsMode(a);
}

extern "C" u32 Gfx2d_GetMainWindows() { return sGfx2d.mainWindows; }

extern "C" void Gfx2d_SetMainWindows(u32 a) { sGfx2d.mainWindows = a; }

extern "C" void Gfx2d_EnableMainWindows(u32 a) { sGfx2d.mainWindows |= a; }

extern "C" void Gfx2d_DisableMainWindows(u32 a) { sGfx2d.mainWindows &= ~a; }

extern "C" u32 Gfx2d_GetSubWindows() { return sGfx2d.subWindows; }

extern "C" void Gfx2d_SetSubWindows(u32 a) { sGfx2d.subWindows = a; }

extern "C" void Gfx2d_EnableSubWindows(u32 a) { sGfx2d.subWindows |= a; }

extern "C" void Gfx2d_DisableSubWindows(u32 a) { sGfx2d.subWindows &= ~a; }

extern "C" u8 Gfx2d_GetMainPlanes(void) { return sGfx2d.mainPlanes; }

extern "C" void Gfx2d_SetMainPlanes(u8 a) { sGfx2d.mainPlanes = a; }

extern "C" void Gfx2d_ShowMainPlanes(u8 a) { sGfx2d.mainPlanes |= a; }

extern "C" void Gfx2d_HideMainPlanes(u8 a) { sGfx2d.mainPlanes &= ~a; }

extern "C" u8 Gfx2d_GetSubPlanes(void) { return sGfx2d.subPlanes; }

extern "C" void Gfx2d_SetSubPlanes(u8 a) { sGfx2d.subPlanes = a; }

extern "C" void Gfx2d_ShowSubPlanes(u8 a) { sGfx2d.subPlanes |= a; }

extern "C" void Gfx2d_HideSubPlanes(u8 a) { sGfx2d.subPlanes &= ~a; }

extern "C" void Gfx2d_SetBrightness(u32 a) {
    if (a != 0) {
        G2x_SetBlendBrightness_(0x4000050, 0x3f, a);
        G2x_SetBlendBrightness_(0x4001050, 0x3f, a);
    } else {
        G2x_SetBlendBrightnessExt_(0x4000050, 0x1f, 0x20, 0x10, 0x10, a);
        G2x_SetBlendBrightnessExt_(0x4001050, 0x1f, 0x20, 0x10, 0x10, a);
    }
}

extern "C" void Gfx2d_BeginSubObjWinBrightness(void) {
    Gfx2d_SetSubBrightnessAllPlanes();
    Gfx2d_SetSubWinOutPlanes(0x1f);
    Gfx2d_SetSubObjWinPlanes(0x10);
    Gfx2d_EnableSubWindows(4);
    sGfx2d.blendRequest |= 1;
}

extern "C" void Gfx2d_EndSubObjWinBrightness(void) {
    Gfx2d_DisableSubWindows(4);
    sGfx2d.blendRequest |= 2;
}

extern "C" void Gfx2d_SetSubBrightnessAllPlanes(void) {
    sGfx2d.blendPlane1 = 0x1f;
    sGfx2d.blendRequest |= 4;
}

extern "C" void Gfx2d_ExcludeSubBrightnessPlanes(u8 a) {
    sGfx2d.blendPlane1 &= ~a;
    sGfx2d.blendRequest |= 4;
}

extern "C" void Gfx2d_SetSubBrightness(u8 a) {
    sGfx2d.blendPlane2 = a;
    sGfx2d.blendRequest |= 4;
}

extern "C" void Gfx2d_SetSubAlphaBlend(u8 a, u8 b, u8 c) {
    sGfx2d.blendPlane1 = a;
    sGfx2d.blendPlane2 = b;
    sGfx2d.blendEv1 = c;
    sGfx2d.blendRequest |= 8;
}

extern "C" void Gfx2d_ResetSubBlend(void) { sGfx2d.blendRequest |= 2; }

extern "C" void Gfx2d_SetMainAlphaBlend(u8 a, u8 b, u8 c) {
    sGfx2d.blendPlane1 = a;
    sGfx2d.blendPlane2 = b;
    sGfx2d.blendEv1 = c;
    sGfx2d.blendRequest |= 0x10;
}

extern "C" void Gfx2d_ResetMainBlend(void) { sGfx2d.blendRequest |= 0x20; }


