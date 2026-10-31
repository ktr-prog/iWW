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

extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern u32 NNSi_G2dBitReaderRead(BitReader *r, u32 nbits);

void ClearChar(u8 *base, u32 x, u32 y, u32 w, u32 h, u32 clr, s32 mode);
void ClearContinuous(CharCanvas *cc, u32 clr);
void ClearAreaLine(CharCanvas *cc, u32 clr, s32 x, s32 y, s32 w, s32 h);

void ClearContinuous(CharCanvas *cc, u32 clr) {
    volatile u32 data;
    u32 size;
    if (cc->colorMode == 4) {
        clr |= clr << 4;
        clr |= clr << 8;
        clr |= clr << 16;
    } else {
        clr |= clr << 8;
        clr |= clr << 16;
    }
    data = clr;
    size = cc->areaWidth * cc->areaHeight;
    size = size * (cc->colorMode * 64 / 8);
    MIi_CpuClearFast(data, cc->charBase, size);
}

void ClearAreaLine(CharCanvas *cc, u32 clr, s32 x, s32 y, s32 w, s32 h) {
    s32 yy, xe, ye, ye8;
    u8 *rowPtr;
    s32 x0, mode, tileBytes, rowStride;
    s32 xx, xe8, top, left, hIn, wIn;
    u8 *p;
    mode = cc->colorMode;
    xe = x + w;
    ye = y + h;
    if (mode == 4) {
        clr |= clr << 4;
        clr |= clr << 8;
        clr |= clr << 16;
    } else {
        clr |= clr << 8;
        clr |= clr << 16;
    }
    yy = y & ~7;
    x0 = x & ~7;
    tileBytes = mode * 64 / 8;
    xe8 = (xe + 7) & ~7;
    ye8 = (ye + 7) & ~7;
    rowPtr = cc->charBase + tileBytes * ((yy / 8) * cc->param + x0 / 8);
    rowStride = cc->param * tileBytes;
    for (; yy < ye8; yy += 8) {
        top = yy < y ? y - yy : 0;
        hIn = ((ye - yy) > 8 ? 8 : (ye - yy)) - top;
        p = rowPtr;
        for (xx = x0; xx < xe8; xx += 8) {
            left = xx < x ? x - xx : 0;
            wIn = ((xe - xx) > 8 ? 8 : (xe - xx)) - left;
            ClearChar(p, left, top, wIn, hIn, clr, mode);
            p += tileBytes;
        }
        rowPtr += rowStride;
    }
}

