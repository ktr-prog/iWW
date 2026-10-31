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
typedef struct ObjShift { u8 w; u8 h; } ObjShift;
typedef union CanvasParam { u32 u; ObjShift s; } CanvasParam;
typedef struct CharCanvas {
    u8 *charBase;
    s32 areaWidth;
    s32 areaHeight;
    u8 colorMode;
    CanvasParam param;
} CharCanvas;

extern void LetterChar(BlitArgs *a);
extern u32 GetCharIndex1D(u32 x, u32 y, s32 w, s32 h, s32 sw, s32 sh);

void DrawGlyph1D(CharCanvas *cc, Font *font, s32 x, s32 y, s32 clr, Glyph *glyph)
{
    s32 yEnd;
    s32 cx1;
    s32 cy0;
    s32 aw;
    s32 gw;
    s32 cw;
    s32 areaH;
    s32 ch;
    s32 gh;
    s32 yy;
    s32 cx0;
    s32 cy;
    s32 xx;
    s32 xEnd;
    s32 cx;
    s32 areaW;
    u8 *charBase;
    const GlyphBlock *pGlyph;
    s32 tileBytes;
    s32 ah;
    s32 objH;
    s32 objW;
    CanvasParam param;
    BlitArgs args;
    s32 cy1;
    tileBytes = cc->colorMode * 64 / 8;
    gw = glyph->pWidths->glyphWidth;
    pGlyph = HostPtr32_Get(font->info->pGlyph);
    aw = cc->areaWidth;
    ah = cc->areaHeight;
    gh = pGlyph->cellHeight;
    if (gw == 0) return;
    if (x + gw < 0) return;
    if (y + gh < 0) return;
    cx0 = (x <= 0) ? 0 : (u32)x >> 3;
    cy0 = (y <= 0) ? 0 : (u32)y >> 3;
    cx1 = (u32)(x + gw + 7) >> 3;
    cy1 = (u32)(y + gh + 7) >> 3;
    if ((u32)cx1 >= (u32)aw) cx1 = aw;
    if ((u32)cy1 >= (u32)ah) cy1 = ah;
    cw = cx1 - cx0;
    ch = cy1 - cy0;
    if (cw < 0) return;
    if (ch < 0) return;
    charBase = cc->charBase;
    if (x >= 0) x &= 7;
    if (y >= 0) y &= 7;
    xEnd = x - cw * 8;
    yEnd = y - ch * 8;
    args.src = glyph->pBitmap;
    args.colorOfs = clr - 1;
    args.h = gh;
    args.w = gw;
    args.pixBits = pGlyph->bpp;
    args.mode = cc->colorMode;
    args.rowStep = args.pixBits * pGlyph->cellWidth;
    param = cc->param;
    areaW = cc->areaWidth;
    areaH = cc->areaHeight;
    objW = param.s.w;
    objH = param.s.h;
    cy = cy0;
    for (yy = y; yy > yEnd; yy -= 8) {
        args.y = yy;
        cx = cx0;
        for (xx = x; xx > xEnd; xx -= 8) {
            const u32 idx = GetCharIndex1D(cx, cy, areaW, areaH, objW, objH);
            args.x = xx;
            args.dst = charBase + idx * tileBytes;
            LetterChar(&args);
            cx++;
        }
        cy++;
    }
}
