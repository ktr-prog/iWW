typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
typedef int s32;
typedef int BOOL;

typedef struct CharWidths { s8 left; u8 glyphWidth; s8 charWidth; } CharWidths;
typedef struct GlyphBlock { u8 cellWidth; u8 cellHeight; u16 cellSize; u8 baseLine; u8 maxCharWidth; u8 bpp; u8 flags; } GlyphBlock;
typedef struct FontInfo {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    CharWidths defaultWidth;
    u8 encoding;
    u32 pGlyph;
    u32 pWidth;
    u32 pMap;
} FontInfo;
typedef struct Font {
    FontInfo *info;
    u32 (*getChar)(const void **);
    u16 hasLeft;
    u16 stride;
} Font;
typedef struct Glyph {
    CharWidths *pWidths;
    u8 *pBitmap;
} Glyph;

struct CharCanvas;
typedef struct BitReader { u8 *p; s8 left; u8 cur; } BitReader;
typedef struct BlitArgs {
    u8 *dst;
    u8 *src;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 rowStep;
    s32 pixBits;
    s32 mode;
    u32 colorOfs;
} BlitArgs;
typedef s32 (*DrawGlyphFunc)(struct CharCanvas *, Font *, s32, s32, s32, Glyph *);
typedef void (*ClearFunc)(struct CharCanvas *, u32);
typedef void (*ClearAreaFunc)(struct CharCanvas *, u32, s32, s32, s32, s32);
typedef struct CharCanvas {
    u8 *charBase;
    s32 areaWidth;
    s32 areaHeight;
    u8 colorMode;
    u32 param;
    DrawGlyphFunc drawGlyph;
    ClearFunc clear;
    ClearAreaFunc clearArea;
} CharCanvas;

extern u32 NNS_G2dFontFindGlyphIndex(Font *font, u32 c);
extern CharWidths *NNS_G2dFontGetCharWidthsFromIndex(Font *font, u32 idx);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern u32 NNSi_G2dBitReaderRead(BitReader *r, u32 nbits);

void DrawGlyphLine(CharCanvas *cc, Font *font, s32 x, s32 y, s32 clr, Glyph *glyph);
void ClearContinuous(CharCanvas *cc, u32 clr);
void ClearAreaLine(CharCanvas *cc, u32 clr, s32 x, s32 y, s32 w, s32 h);
void InitCharCanvas(CharCanvas *cc, u8 *charBase, s32 w, s32 h, s32 mode, DrawGlyphFunc dg, ClearFunc cl, ClearAreaFunc ca, u32 param);

void InitCharCanvas(CharCanvas *cc, u8 *charBase, s32 w, s32 h, s32 mode, DrawGlyphFunc dg, ClearFunc cl, ClearAreaFunc ca, u32 param) {
    cc->areaWidth = w;
    cc->areaHeight = h;
    cc->colorMode = mode;
    cc->charBase = charBase;
    cc->drawGlyph = dg;
    cc->clear = cl;
    cc->clearArea = ca;
    cc->param = param;
}

s32 NNS_G2dCharCanvasDrawChar(CharCanvas *cc, Font *font, s32 x, s32 y, s32 clr, u16 ch) {
    Glyph glyph;
    u32 idx = NNS_G2dFontFindGlyphIndex(font, ch);
    GlyphBlock *g;
    if (idx == 0xffff) idx = font->info->alterCharIndex;
    glyph.pWidths = NNS_G2dFontGetCharWidthsFromIndex(font, idx);
    g = HostPtr32_Get(font->info->pGlyph);
    glyph.pBitmap = (u8 *)(idx * g->cellSize + ((u8 *)g + 8));
    cc->drawGlyph(cc, font, x + glyph.pWidths->left, y, clr, &glyph);
    if (font->hasLeft != 0) return glyph.pWidths->left + glyph.pWidths->glyphWidth;
    return glyph.pWidths->charWidth;
}

void NNS_G2dCharCanvasInitForBG(CharCanvas *cc, u8 *charBase, s32 w, s32 h, s32 mode) {
    InitCharCanvas(cc, charBase, w, h, mode, (DrawGlyphFunc)DrawGlyphLine, ClearContinuous, ClearAreaLine, w);
}

