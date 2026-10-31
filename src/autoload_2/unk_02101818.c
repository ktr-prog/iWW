#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_02101818.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
typedef int s32;
typedef int BOOL;

typedef struct FrmPlttMan {
    u32 head;
    u32 tail;
    u32 size;
} FrmPlttMan;
extern FrmPlttMan data_021f5cb4;

typedef struct BinHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} BinHeader;
typedef struct BinBlock { u32 kind; u32 size; } BinBlock;

typedef struct CharWidths { s8 left; u8 glyphWidth; s8 charWidth; } CharWidths;
typedef struct FontWidth {
    u16 indexBegin;
    u16 indexEnd;
    u32 next;
    CharWidths widths[1];
} FontWidth;
typedef struct CodeMapPair { u16 code; u16 index; } CodeMapPair;
typedef struct FontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    u32 next;
    u16 mapInfo[1];
} FontCodeMap;
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
typedef struct TextRect { s32 width; s32 height; } TextRect;

s32 NNS_GfdFreeFrmPlttVram(u32 key);
u32 NNS_GfdAllocFrmPlttVram(u32 szByte, BOOL b4pltt, u32 opt);
extern s32 NNSi_G2dGetUnpackedFont(void *file, Font *font);
extern u32 NNSi_G2dSplitCharUTF16(const void **);

static inline BOOL AllocHead(u32 szByte, BOOL b4pltt, u32 *pAddr) {
    u32 total, pad, head;
    head = data_021f5cb4.head;
    pad = b4pltt ? ((8 - (head & 7)) & 7) : ((16 - (head & 15)) & 15);
    total = szByte + pad;
    if (data_021f5cb4.tail - head >= total) {
        u32 end = head + total;
        if (b4pltt && end > 0x10000) {
            head = 0;
        } else {
            *pAddr = head + pad;
            data_021f5cb4.head += total;
            head = 1;
        }
    } else {
        head = 0;
    }
    return head;
}
static inline BOOL AllocTail(u32 szByte, BOOL b4pltt, u32 *pAddr) {
    u32 total, pad, tail, start;
    tail = data_021f5cb4.tail;
    if (tail >= szByte && (start = tail - szByte, pad = b4pltt ? (start & 7) : (start & 15), total = szByte + pad, tail - data_021f5cb4.head >= total)) {
        if (b4pltt && tail > 0x10000) {
            tail = 0;
        } else {
            data_021f5cb4.tail -= total;
            *pAddr = data_021f5cb4.tail;
            tail = 1;
        }
    } else {
        tail = 0;
    }
    return tail;
}

s32 NNSi_G2dFontGetStringWidth(Font *font, s32 hSpace, const void *txt, const void **next);
CharWidths *NNS_G2dFontGetCharWidthsFromIndex(Font *font, u32 idx);
u32 NNS_G2dFontFindGlyphIndex(Font *font, u32 c);
u32 GetGlyphIndex(FontCodeMap *map, u32 c);

u32 GetGlyphIndex(FontCodeMap *m, u32 c) {
    u16 index = 0xffff;
    switch (m->mappingMethod) {
    case 0:
        index = (u16)(m->mapInfo[0] + (c - m->ccodeBegin));
        break;
    case 1:
        index = m->mapInfo[c - m->ccodeBegin];
        break;
    case 2: {
        u16 *p = m->mapInfo;
        u32 n = *p;
        CodeMapPair *lo, *hi;
        p++;
        lo = (CodeMapPair *)p;
        hi = lo + (n - 1);
        while (lo <= hi) {
            CodeMapPair *mid = lo + (hi - lo) / 2;
            if (mid->code < c) lo = mid + 1;
            else if (c < mid->code) hi = mid - 1;
            else { index = mid->index; break; }
        }
        break;
    }
    }
    return index;
}

void NNS_G2dFontInitUTF16(Font *font, void *file) {
    font->hasLeft = (u16)(NNSi_G2dGetUnpackedFont(file, font) - 1);
    font->stride = font->hasLeft != 0 ? 2 : 3;
    font->getChar = NNSi_G2dSplitCharUTF16;
}

u32 NNS_G2dFontFindGlyphIndex(Font *font, u32 c) {
    FontCodeMap *m = HostPtr32_Get(font->info->pMap);
    while (m != 0) {
        if (m->ccodeBegin <= c && c <= m->ccodeEnd) return GetGlyphIndex(m, c);
        m = HostPtr32_Get(m->next);
    }
    return 0xffff;
}

CharWidths *NNS_G2dFontGetCharWidthsFromIndex(Font *font, u32 idx) {
    FontWidth *w = HostPtr32_Get(font->info->pWidth);
    while (w != 0) {
        if (w->indexBegin <= idx && idx <= w->indexEnd)
            return (CharWidths *)((u8 *)w->widths + (idx - w->indexBegin) * font->stride);
        w = HostPtr32_Get(w->next);
    }
    return &font->info->defaultWidth;
}

s32 NNSi_G2dFontGetStringWidth(Font *font, s32 hSpace, const void *txtIn, const void **next) {
    const void *txt = txtIn;
    s32 width;
    u32 (*getChar)(const void **);
    u32 c;
    getChar = font->getChar;
    width = 0;
    c = getChar(&txt);
    while (c != 0) {
        u32 idx;
        CharWidths *cw;
        s32 w;
        if (c == 10) break;
        idx = NNS_G2dFontFindGlyphIndex(font, c);
        if (idx == 0xffff) idx = font->info->alterCharIndex;
        cw = NNS_G2dFontGetCharWidthsFromIndex(font, idx);
        if (font->hasLeft != 0) w = cw->left + cw->glyphWidth;
        else w = cw->charWidth;
        width += hSpace + w;
        c = getChar(&txt);
    }
    if (next != 0) *next = (c == 10) ? txt : 0;
    if (width > 0) width -= hSpace;
    return width;
}

s32 NNSi_G2dFontGetTextHeight(Font *font, s32 vSpace, const void *txtIn) {
    const void *txt = txtIn;
    TextRect rect = {0, 0};
    s32 lines = 1;
    u32 (*getChar)(const void **) = font->getChar;
    u32 c = getChar(&txt);
    while (c != 0) {
        if (c == 10) lines++;
        c = getChar(&txt);
    }
    return lines * (vSpace + font->info->linefeed) - vSpace;
}

TextRect NNSi_G2dFontGetTextRect(Font *font, s32 hSpace, s32 vSpace, const void *txt) {
    TextRect rect = {0, 0};
    s32 lines = 1;
    while (txt != 0) {
        s32 w = NNSi_G2dFontGetStringWidth(font, hSpace, txt, &txt);
        if (w > rect.width) rect.width = w;
        lines++;
    }
    rect.height = (lines - 1) * (vSpace + font->info->linefeed) - vSpace;
    return rect;
}

void *NNS_G2dFindBinaryBlock(BinHeader *h, u32 kind) {
    BinBlock *b = (BinBlock *)((u8 *)h + h->headerSize);
    u16 i;
    for (i = 0; i < h->dataBlocks; i++) {
        if (b->kind == kind) return b;
        b = (BinBlock *)((u8 *)b + b->size);
    }
    return 0;
}

void NNS_GfdInitFrmPlttVramManager(u32 szByte, BOOL useAsDefault) {
    data_021f5cb4.size = szByte;
    NNS_GfdResetFrmPlttVramState();
    if (useAsDefault) {
        data_0213bc18 = NNS_GfdAllocFrmPlttVram;
        data_0213bc1c = NNS_GfdFreeFrmPlttVram;
    }
}

u32 NNS_GfdAllocFrmPlttVram(u32 szByte, BOOL b4pltt, u32 opt) {
    u32 addr = 0;
    BOOL result;
    if (szByte == 0) szByte = 8;
    else szByte = (szByte + 7) & ~7;
    if (szByte >= 0x7fff8) return 0;
    if (opt == 1) result = AllocHead(szByte, b4pltt, &addr);
    else result = AllocTail(szByte, b4pltt, &addr);
    if (result) return ((szByte >> 3) << 16) | ((addr >> 3) & 0xffff);
    return 0;
}

s32 NNS_GfdFreeFrmPlttVram(u32 key) {
    return 0;
}

void NNS_GfdResetFrmPlttVramState(void) {
    data_021f5cb4.head = 0;
    data_021f5cb4.tail = data_021f5cb4.size;
}

FrmPlttMan data_021f5cb4;
