typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
typedef int s32;

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
typedef struct Font { FontInfo *info; } Font;
typedef struct Glyph {
    CharWidths *pWidths;
    u8 *pBitmap;
} Glyph;
typedef struct BlitArgs {
    u8 *dst;
    const u8 *src;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 rowStep;
    s32 pixBits;
    s32 mode;
    u32 colorOfs;
} BlitArgs;
typedef struct CharCanvas {
    u8 *charBase;
    s32 areaWidth;
    s32 areaHeight;
    u8 colorMode;
    u32 param;
} CharCanvas;

extern void LetterChar(BlitArgs *a);

void DrawGlyphLine(CharCanvas *cc, Font *font, s32 x, s32 y, s32 clr, Glyph *glyph)
{
    s32 xx;
    s32 gw;
    BlitArgs args;
    s32 xEnd;
    s32 yEnd;
    s32 yy;
    s32 cw;
    s32 areaW;
    s32 areaH;
    const GlyphBlock *pGlyph;
    s32 cy0;
    s32 cx0;
    s32 ch;
    s32 cx1;
    u8 *charBase;
    u8 *dst;
    s32 gh;
    s32 tileBytes;
    s32 rowSkip;
    s32 cy1;
    tileBytes = cc->colorMode * 64 / 8;
    gw = glyph->pWidths->glyphWidth;
    pGlyph = HostPtr32_Get(font->info->pGlyph);
    areaW = cc->areaWidth;
    areaH = cc->areaHeight;
    charBase = cc->charBase;
    gh = pGlyph->cellHeight;
    if (gw == 0) return;
    if (x + gw < 0) return;
    if (y + gh < 0) return;
    cx0 = (x <= 0) ? 0 : (u32)x >> 3;
    cy0 = (y <= 0) ? 0 : (u32)y >> 3;
    cx1 = (u32)(x + gw + 7) >> 3;
    if ((u32)cx1 >= (u32)areaW) cx1 = areaW;
    cy1 = (u32)(y + gh + 7) >> 3;
    if ((u32)cy1 >= (u32)areaH) cy1 = areaH;
    cw = cx1 - cx0;
    ch = cy1 - cy0;
    if (cw < 0) return;
    if (ch < 0) return;
    dst = charBase + tileBytes * (cc->param * cy0 + cx0);
    rowSkip = (cc->param - cw) * tileBytes;
    if (x >= 0) x &= 7;
    if (y >= 0) y &= 7;
    args.src = glyph->pBitmap;
    args.w = gw;
    args.h = gh;
    args.colorOfs = clr - 1;
    args.pixBits = pGlyph->bpp;
    args.mode = cc->colorMode;
    args.rowStep = args.pixBits * pGlyph->cellWidth;
    xEnd = x - cw * 8;
    yEnd = y - ch * 8;
    for (yy = y; yy > yEnd; yy -= 8) {
        args.y = yy;
        for (xx = x; xx > xEnd; xx -= 8) {
            args.dst = dst;
            args.x = xx;
            LetterChar(&args);
            dst += tileBytes;
        }
        dst += rowSkip;
    }
}
