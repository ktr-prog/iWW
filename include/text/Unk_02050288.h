#ifndef TEXT_UNK_02050288_H
#define TEXT_UNK_02050288_H

#include "types.h"

struct GameFontHeader {
    /* 0x00 */ u32 glyphCount;
    /* 0x04 */ u16 cellWidth;
    /* 0x06 */ u16 cellHeight;
};

struct GameFontGlyph {
    /* 0x00 */ u16 code;
    /* 0x02 */ u8 width;
    /* 0x03 */ u8 unk_03;
};

struct GameFontDesc {
    /* 0x00 */ GameFontHeader *header;
    /* 0x04 */ GameFontGlyph *glyphs;
    /* 0x08 */ u8 *bitmaps;
    /* 0x0c */ GameFontDesc *subFont;
    /* 0x10 */ u8 unk_10;
    MWCC_LAYOUT
};

class StrBuf {
public:
    virtual ~StrBuf();
    virtual u32 size();
    virtual u8 *data();
};

struct Unk_02050288_08 {
    uptr unk_00[2];
};

class TextLabel {
public:
    TextLabel(u8 *buf, s32 widthTiles, s32 heightTiles);
    TextLabel(u32 tileIndex, s32 widthTiles, s32 heightTiles);
    virtual ~TextLabel();
    virtual void draw() = 0;
    virtual u32 measureWidth() = 0;

    u32 drawGlyph();
    void drawLetterSpacing();
    void drawUnderline(u32 x);
    void clear();
    BOOL isInHighlightA();
    BOOL isInHighlightB();
    u8 getFgColor();
    u8 getBgColor();
    void flushRow();
    void drawChar(u32 c);
    void beginRow();
    void render();
    void clearTileBuffer();
    void endMeasure();
    void measureChar(u32 c);
    void beginMeasure();
    u32 getWidthInTiles();
    void setHighlights(u8 arg1, u8 arg2, u32 arg3, u32 arg4, u8 arg5, u8 arg6, u32 arg7, u32 arg8);
    void setHighlight(u8 arg1, u8 arg2, u32 arg3, u32 arg4);
    void alignRight();
    void alignCenter();
    void requestClear(s32 arg1);
    void requestRedraw();

    /* 0x04 */ u32 unk_04;
    /* 0x08 */ Unk_02050288_08 listLink;
    /* 0x10 */ u8 *textStart;
    /* 0x14 */ u8 *textEnd;
    /* 0x18 */ s32 tileIndex;
    /* 0x1c */ u8 *destBuffer;
    /* 0x20 */ s32 widthTiles;
    /* 0x24 */ s32 heightTiles;
    /* 0x28 */ GameFontDesc *font;
    /* 0x2c */ u32 vramLoader;
    /* 0x30 */ u32 xOffset;
    /* 0x34 */ u32 letterSpacing;
    /* 0x38 */ u8 fgColor;
    /* 0x39 */ u8 bgColor;
    /* 0x3a */ u8 highlightAFg;
    /* 0x3b */ u8 highlightABg;
    /* 0x3c */ u8 highlightBFg;
    /* 0x3d */ u8 highlightBBg;
    /* 0x40 */ u32 highlightAStart;
    /* 0x44 */ u32 highlightALen;
    /* 0x48 */ u32 highlightBStart;
    /* 0x4c */ u32 highlightBLen;
    /* 0x50 */ u32 copyMode;
    /* 0x54 */ u8 redrawPending;
    /* 0x55 */ u8 rowStride1K;
    /* 0x56 */ u8 blendOverBg;
    /* 0x57 */ u8 underline;
    /* 0x58 */ u32 group;
    /* 0x5c */ s32 clearRequest;
    /* 0x60 */ s32 rowBytes;
    /* 0x64 */ s32 curGlyph;
    /* 0x68 */ u32 curX;
    /* 0x6c */ u32 curRowY;
    /* 0x70 */ u32 destOffset;
    /* 0x74 */ u8 savedFgColor;
    /* 0x75 */ u8 isLastRow;
    /* 0x78 */ u32 charIndex;
};

#endif
