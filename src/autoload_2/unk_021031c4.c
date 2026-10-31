#include "proto/autoload_2/unk_021031c4.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
typedef signed char s8;
typedef int s32;
typedef int BOOL;
#define NULL 0

typedef struct FontInfo { u8 pad0; s8 height; } FontInfo;
typedef struct Font { FontInfo *info; u32 (*getChar)(const u16 **); } Font;
typedef struct TextCanvas { void *cc; Font *font; s32 hSpace; s32 vSpace; } TextCanvas;
typedef struct Rect { s32 w, h; } Rect;
typedef struct BinHdr { u32 sig; u16 bom; u16 ver; u32 size; u16 hdrSize; u16 nBlocks; } BinHdr;
typedef struct BlockHdr { u32 kind; u32 size; } BlockHdr;
typedef struct FInfo { u8 pad[6]; s8 f6; s8 f7; } FInfo;

extern u8 *NNS_G2dFindBinaryBlock(BinHdr *, u32);
extern Rect NNSi_G2dFontGetTextRect(Font *, s32, s32, const u16 *);
extern s32 NNSi_G2dFontGetTextHeight(Font *, s32, const u16 *);
extern s32 NNSi_G2dFontGetStringWidth(Font *, s32, const u16 *, const u16 **);
extern s32 NNS_G2dCharCanvasDrawChar(void *, Font *, s32, s32, s32, u32);
void NNSi_G2dUnpackNFT(BinHdr *h);

static inline BOOL IsSig(BinHdr *h) { if (h != NULL) { if (h->sig == 0x4e465452) return 1; } return 0; }
static inline BOOL IsVer(BinHdr *h, u16 v) { if (h != NULL) { if (h->ver == v) return 1; } return 0; }
static inline BOOL IsFont(BinHdr *h, u16 v)
{
    BOOL r;
    if (h != NULL) {
        r = IsSig(h) && IsVer(h, v);
    } else {
        r = 0;
    }
    return r;
}

s32 NNSi_G2dGetUnpackedFont(BinHdr *h, FInfo **out)
{
    s32 kind;
    u8 *blk;
    if (IsFont(h, 0x100)) {
        kind = 0;
    } else if (IsFont(h, 1)) {
        kind = 1;
    } else {
        Fatal_Trap();
    }
    NNSi_G2dUnpackNFT(h);
    blk = NNS_G2dFindBinaryBlock(h, 0x46494e46);
    if (blk == NULL) {
        *out = NULL;
        return 0;
    }
    *out = (FInfo *)(blk + 8);
    if (kind != 0) {
        (*out)->f7 = (*out)->f6;
        (*out)->f6 = 0;
    }
    return kind + 1;
}

static inline void Relocate(u32 *slot, u8 *base) { *slot = HostPtr32_Of(base + *slot); }
void NNSi_G2dUnpackNFT(BinHdr *h)
{
    u8 *base = (u8 *)h;
    BlockHdr *blk = (BlockHdr *)(base + h->hdrSize);
    s32 i;
    for (i = 0; i < h->nBlocks; i++) {
        switch (blk->kind) {
        case 0x46494e46: {
            u32 *p = (u32 *)(blk + 1);
            Relocate(&p[2], base);
            if (p[3] != 0) Relocate(&p[3], base);
            if (p[4] != 0) Relocate(&p[4], base);
            break;
        }
        case 0x43574448: {
            u32 *p = (u32 *)(blk + 1);
            if (p[1] != 0) Relocate(&p[1], base);
            break;
        }
        case 0x434d4150: {
            u32 *p = (u32 *)(blk + 1);
            if (p[2] != 0) Relocate(&p[2], base);
            break;
        }
        case 0x43474c50:
            break;
        }
        blk = (BlockHdr *)((u8 *)blk + blk->size);
    }
}

void NNSi_G2dTextCanvasDrawString(TextCanvas *c, s32 x, s32 y, s32 cl, const u16 *txt, const u16 **pEnd)
{
    s32 hs = c->hSpace;
    Font *font = c->font;
    const u16 *t = txt;
    u32 (*get)(const u16 **) = font->getChar;
    u32 ch;
    for (ch = get(&t); ch != 0; ch = get(&t)) {
        if (ch == 10) break;
        x += NNS_G2dCharCanvasDrawChar(c->cc, font, x, y, cl, ch);
        x += hs;
    }
    if (pEnd != NULL) {
        *pEnd = (ch == 10) ? t : NULL;
    }
}

void NNSi_G2dTextCanvasDrawTextAlign(TextCanvas *c, s32 x, s32 y, s32 w, s32 cl, u32 flags, const u16 *txt)
{
    s32 lh = c->vSpace + c->font->info->height;
    const u16 *t = txt;
    s32 lx;
    if (txt == NULL) return;
    do {
        lx = x;
        if (flags & 0x800) {
            lx = x + (w - NNSi_G2dFontGetStringWidth(c->font, c->hSpace, t, NULL));
        } else if (flags & 0x400) {
            lx = x + (((w + 1) / 2) - (NNSi_G2dFontGetStringWidth(c->font, c->hSpace, t, NULL) + 1) / 2);
        }
        NNSi_G2dTextCanvasDrawString(c, lx, y, cl, t, &t);
        y += lh;
    } while (t != NULL);
}

void NNSi_G2dTextCanvasDrawText(TextCanvas *c, s32 x, s32 y, s32 cl, u32 flags, const u16 *txt)
{
    Rect r;
    r = NNSi_G2dFontGetTextRect(c->font, c->hSpace, c->vSpace, txt);
    if (flags & 0x10) {
        x -= (r.w + 1) / 2;
    } else if (flags & 0x20) {
        x -= r.w;
    }
    if (flags & 0x2) {
        y -= (r.h + 1) / 2;
    } else if (flags & 0x4) {
        y -= r.h;
    }
    NNSi_G2dTextCanvasDrawTextAlign(c, x, y, r.w, cl, flags, txt);
}

void NNSi_G2dTextCanvasDrawTextRect(TextCanvas *c, s32 x, s32 y, s32 w, s32 h, s32 cl, u32 flags, const u16 *txt)
{
    if (flags & 0x100) {
        y += h - NNSi_G2dFontGetTextHeight(c->font, c->vSpace, txt);
    } else if (flags & 0x80) {
        y += (h + 1) / 2 - (NNSi_G2dFontGetTextHeight(c->font, c->vSpace, txt) + 1) / 2;
    }
    NNSi_G2dTextCanvasDrawTextAlign(c, x, y, w, cl, flags, txt);
}
