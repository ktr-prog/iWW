#include "types.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "net/WfcPool.h"
#include "net/WfcRect.h"
#include "proto/autoload_2/unk_02101de8.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02226994.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
};

struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
};

struct NNSG2dFont {
    NNSG2dFontInformation *info;
    u32 (*getChar)(const void **);
    u16 hasLeft;
    u16 stride;
};

struct NNSG2dCharCanvas {
    u8 *charBase;
    s32 areaWidth;
    s32 areaHeight;
    u8 colorMode;
    u32 param;
    void *drawGlyph;
    void (*clear)(NNSG2dCharCanvas *, u32);
    void *clearArea;
};

struct NNSG2dTextCanvas {
    NNSG2dCharCanvas *canvas;
    NNSG2dFont *font;
    s32 hSpace;
    s32 vSpace;
};

struct WfcTextCanvas {
    NNSG2dCharCanvas cc;
    NNSG2dTextCanvas tc;
    void *charBuffer;
};

struct WfcObjTextCanvas : WfcTextCanvas {
    u16 charName;
    u8 areaWidth;
    u8 areaHeight;
};

struct WfcBgTextCanvas : WfcTextCanvas {
    void *transferTask;
};

struct WfcTextWork {
    NNSG2dFont fonts[2];
    WfcObjTextCanvas objCanvases[0x20];
    WfcBgTextCanvas bgCanvases[2];
    WfcPool *objCanvasPool;
    void *fontFiles[2];
    u8 bgDirty[2];
};
#if !HOST64
static_assert(sizeof(WfcObjTextCanvas) == 0x38 && sizeof(WfcBgTextCanvas) == 0x38, "DS layout");
static_assert(sizeof(WfcTextWork) == 0x798, "DS layout");
#endif

extern "C" {
extern const u16 sWfcTextBgCharBase[2];
extern const u16 sWfcTextBgSize[4];
extern const WfcRect gWfcScreenRect;

void NNSi_G2dTextCanvasDrawTextRect(NNSG2dTextCanvas *, s32, s32, s32, s32, s32, u32, const u16 *);
u32 NNS_G2dFontFindGlyphIndex(NNSG2dFont *, u32);
NNSG2dCharWidths *NNS_G2dFontGetCharWidthsFromIndex(NNSG2dFont *, u32);
s32 NNS_G2dCharCanvasDrawChar(NNSG2dCharCanvas *, NNSG2dFont *, s32, s32, s32, u16);
void NNSi_G2dTextCanvasDrawText(NNSG2dTextCanvas *, s32, s32, s32, u32, const u16 *);
void MIi_CpuClear16(u32, void *, u32);
void DC_FlushRange(void *, u32);
void GX_LoadBG0Char(void *, u32, u32);
void GXS_LoadBG0Char(void *, u32, u32);
void NNS_G2dCharCanvasInitForBG(NNSG2dCharCanvas *, void *, u32, u32, u32);
void NNS_G2dMapScrToCharText(void *, u32, u32, s32, s32, s32, u32, s32);
void WfcVram_FreeObjChar(WfcVramBlock *p);
void WfcPool_Put(WfcPool *, void *);
void *WfcPool_Get(WfcPool *);
u32 NNSi_G2dCalcRequiredOBJ(u32, u32);
void NNS_G2dCharCanvasInitForOBJ1D(NNSG2dCharCanvas *, u8 *, u32, u32, u32);
void NNS_G2dFontInitUTF16(NNSG2dFont *, void *);
void WfcText_ReleaseBgCanvas(WfcBgTextCanvas *o);
WfcTextWork *sWfcText;
}

extern "C" const u16 sWfcTextBgCharBase[2] = {0x0000, 0x0180};
extern "C" const u16 sWfcTextBgSize[4] = {0x0020, 0x0018, 0x0020, 0x000c};
extern "C" const WfcRect gWfcScreenRect = {0x0000, 0x0000, 0x0100, 0x00c0};
extern "C" void *sWfcFontPaths[2] = {data_ov001_0222b894, data_ov001_0222b8a4};
extern "C" char data_ov001_0222b894[] = "msg/lc_m.NFTR.l";
extern "C" char data_ov001_0222b8a4[] = "msg/lc_s.NFTR.l";

extern "C" {

void WfcText_Init() {
    WfcTextWork *g = (WfcTextWork *)WfcHeap_Alloc(sizeof(WfcTextWork), 4);
    sWfcText = g;
    WfcPool *pool = WfcPool_CreateFrom(0x20, g->objCanvases, sizeof(WfcObjTextCanvas));
    sWfcText->objCanvasPool = pool;
    s32 i;
    for (i = 0; i < 2; i++) {
        void *hh = WfcFs_LoadFile(sWfcFontPaths[i], 0, 4);
        sWfcText->fontFiles[i] = hh;
        WfcTextWork *q = sWfcText;
        NNS_G2dFontInitUTF16(&q->fonts[i], q->fontFiles[i]);
    }
}

void WfcText_Shutdown() {
    s32 i;
    for (i = 0; i < 2; i++) {
        WfcFs_FreeFile(sWfcText->fontFiles[i]);
    }
    WfcPool_Destroy(sWfcText->objCanvasPool);
    WfcHeap_FreeAndClear((void **)&sWfcText);
}

WfcTextCanvas *WfcText_CreateObjCanvas(u32 mode, u32 w, u32 h, u32 a3, u32 *out, u32 slot) {
    WfcObjTextCanvas *e = (WfcObjTextCanvas *)WfcPool_Get(sWfcText->objCanvasPool);
    e->areaWidth = w;
    e->areaHeight = h;
    u32 t;
    e->charBuffer = WfcVram_AllocObjChar(mode, w * h, a3, &t);
    e->charName = t;
    *out = NNSi_G2dCalcRequiredOBJ(w, h);
    u32 tt = t;
    u8 *base = mode == 1 ? (u8 *)HostVram_CpuPtr(0x06600000) : (u8 *)HostVram_CpuPtr(0x06400000);
    NNS_G2dCharCanvasInitForOBJ1D(&e->cc, base + (tt << 7), w, h, 4);
    e->cc.clear(&e->cc, 0);
    NNSG2dFont *ent = &sWfcText->fonts[slot];
    e->tc.canvas = &e->cc;
    e->tc.font = ent;
    e->tc.hSpace = 1;
    e->tc.vSpace = 1;
    return e;
}

void WfcText_DestroyObjCanvas(WfcTextCanvas *o) {
    WfcVram_FreeObjChar((WfcVramBlock *)o->charBuffer);
    WfcPool_Put(sWfcText->objCanvasPool, o);
}

WfcTextCanvas *WfcText_CreateBgCanvas(u32 idx, u32 slot) {
    WfcBgTextCanvas *o;
    u32 h;
    u32 w;
    h = sWfcTextBgSize[idx * 2 + 1];
    w = sWfcTextBgSize[idx * 2];
    o = &sWfcText->bgCanvases[idx];
    o->charBuffer = WfcHeap_Alloc((w * h) << 5, 0x20);
    if (idx == 1) {
        volatile u16 *reg = (volatile u16 *)0x4001008;
        IO_W(reg, IO_R(reg) & ~0x40);
        IO_W(reg, (IO_R(reg) & 0x43) | 0xc00);
    } else {
        volatile u16 *reg = (volatile u16 *)0x4000008;
        IO_W(reg, IO_R(reg) & ~0x40);
        IO_W(reg, (IO_R(reg) & 0x43) | 0xc00);
    }
    NNS_G2dCharCanvasInitForBG(&o->cc, o->charBuffer, w, h, 4);
    NNSG2dFont *ent = &sWfcText->fonts[slot];
    o->tc.canvas = &o->cc;
    o->tc.font = ent;
    o->tc.hSpace = 1;
    o->tc.vSpace = 1;
    void *r;
    if (idx == 1) {
        r = G2S_GetBG0ScrPtr();
    } else {
        r = G2_GetBG0ScrPtr();
    }
    NNS_G2dMapScrToCharText(r, w, h, 0, 0, 0x20, sWfcTextBgCharBase[idx], 0xf);
    WfcText_Clear(o, 0);
    o->transferTask = WfcTask_Add(1, (void *)WfcText_BgTransferTask, &sWfcText->bgDirty[idx], 0xc8);
    return o;
}

void WfcText_BgTransferTask(u32 task, u8 *flag) {
    if (*flag == 0) {
        return;
    }
    WfcTextWork *g = sWfcText;
    if (flag == &g->bgDirty[0]) {
        u32 sz = (sWfcTextBgSize[0] * sWfcTextBgSize[1]) << 5;
        DC_FlushRange(g->bgCanvases[0].charBuffer, sz);
        GX_LoadBG0Char(sWfcText->bgCanvases[0].charBuffer, sWfcTextBgCharBase[0] << 5, sz);
    } else {
        u32 sz = (sWfcTextBgSize[2] * sWfcTextBgSize[3]) << 5;
        DC_FlushRange(g->bgCanvases[1].charBuffer, sz);
        GXS_LoadBG0Char(sWfcText->bgCanvases[1].charBuffer, sWfcTextBgCharBase[1] << 5, sz);
    }
    *flag = 0;
}

void WfcText_ReleaseBgCanvas(WfcBgTextCanvas *o) {
    WfcTask_Delete(1, o->transferTask);
    if (o == &sWfcText->bgCanvases[0]) {
        void *r = G2_GetBG0CharPtr();
        volatile u16 z = 0;
        MIi_CpuClear16(z, r, (sWfcTextBgSize[0] * sWfcTextBgSize[1]) << 5);
    } else {
        void *r = G2_GetBG0CharPtr();
        volatile u16 z = 0;
        MIi_CpuClear16(z, r, (sWfcTextBgSize[2] * sWfcTextBgSize[3]) << 5);
    }
    WfcHeap_FreeAndClear(&o->charBuffer);
}

void WfcText_DestroyBgCanvas(u32 idx) {
    WfcText_ReleaseBgCanvas(&sWfcText->bgCanvases[idx]);
}

void WfcText_DrawText(WfcTextCanvas *o, s32 x, s32 y, s32 color, u32 flags, const u16 *text) {
    NNSi_G2dTextCanvasDrawText(&o->tc, x, y, color, flags, text);
}

void WfcText_DrawChar(WfcTextCanvas *o, s32 x, s32 y, s32 color, u16 c, s32 font) {
    NNS_G2dCharCanvasDrawChar(&o->cc, &sWfcText->fonts[font], x, y, color, c);
}

void WfcText_DrawMonospace(WfcTextCanvas *o, s32 x, s32 y, s32 color, s32 w, u16 *p, s32 font) {
    if (*p == 0) {
        return;
    }
    do {
        NNSG2dFont *e = &sWfcText->fonts[font];
        u32 t = NNS_G2dFontFindGlyphIndex(e, *p);
        if (t == 0xffff) {
            t = e->info->alterCharIndex;
        }
        NNSG2dCharWidths *r = NNS_G2dFontGetCharWidthsFromIndex(e, t);
        s32 v;
        if (e->hasLeft != 0) {
            v = r->left + r->glyphWidth;
        } else {
            v = r->charWidth;
        }
        WfcText_DrawChar(o, x + ((w - v) >> 1), y, color, *p, font);
        p++;
        x += w;
    } while (*p != 0);
}

void WfcText_DrawTextRect(WfcTextCanvas *o, s32 x, s32 y, s32 w, s32 h, s32 color, u32 flags, const u16 *text) {
    NNSi_G2dTextCanvasDrawTextRect(&o->tc, x, y, w, h, color, flags, text);
}

void WfcText_Clear(WfcTextCanvas *o, s32 a) {
    o->cc.clear(&o->cc, a);
}

void WfcText_ArrangeObj(WfcTextCanvas *o, s32 x, s32 y, WfcObjGroup *h, s32 priority) {
    WfcObjTextCanvas *c = static_cast<WfcObjTextCanvas *>(o);
    GXOamAttr *e = WfcObj_GetOam(h, 0);
    WfcObj_SetAffineMode(h, -1, 0, 0);
    WfcObj_SetModePalette(h, -1, 0, 0xf);
    WfcObj_SetPriority(h, -1, priority);
    NNS_G2dArrangeOBJ1D(e, c->areaWidth, c->areaHeight, x, y, 0, c->charName, 2);
}

void WfcText_RequestTransfer(WfcTextCanvas *o) {
    WfcTextWork *g = sWfcText;
    if (o == &g->bgCanvases[0]) {
        g->bgDirty[0] = 1;
    } else {
        g->bgDirty[1] = 1;
    }
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0222516c) {
    HOST_OVERLAY_VAR(sWfcText),
    HOST_OVERLAY_VAR(sWfcFontPaths),
    HOST_OVERLAY_VAR(data_ov001_0222b894),
    HOST_OVERLAY_VAR(data_ov001_0222b8a4),
    HOST_OVERLAY_VARS_END
};
