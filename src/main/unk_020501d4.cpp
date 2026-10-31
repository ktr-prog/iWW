#include "text/Unk_02050288.h"
#include "Unk_020d8c7c.h"
#include "sys/ProcProfile.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206c768.h"


typedef void (*GxLoadCharFunc)(void *src, u32 offset, u32 size);

extern "C" {
void *NNS_FndGetNextListObject(void *list, void *prev);
void NNS_FndRemoveListObject(void *list, void *obj);
void NNS_FndInitList(void *list, u32 offset);
void DC_FlushRange(void *ptr, u32 size);
void MI_CpuFill8(void *dst, u32 value, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
char *strncpy(char *dst, const char *src, u32 n);

void GX_LoadBG0Char(void *src, u32 offset, u32 size);
void GX_LoadBG1Char(void *src, u32 offset, u32 size);
void GX_LoadBG2Char(void *src, u32 offset, u32 size);
void GX_LoadBG3Char(void *src, u32 offset, u32 size);
void GX_LoadOBJ(void *src, u32 offset, u32 size);
void GXS_LoadBG0Char(void *src, u32 offset, u32 size);
void GXS_LoadBG1Char(void *src, u32 offset, u32 size);
void GXS_LoadBG2Char(void *src, u32 offset, u32 size);
void GXS_LoadBG3Char(void *src, u32 offset, u32 size);
void GXS_LoadOBJ(void *src, u32 offset, u32 size);

}

struct GameFont : GameFontDesc {
    GameFont();
    ~GameFont();
};

class TextSystemModule : public GameProc {
public:
    TextSystemModule();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual ~TextSystemModule();
};


extern "C" {

extern const u16 sSpecialCharStr6;
extern const u16 sSpecialCharStr2;
extern const u16 sCharSortKeyZero;
extern const u16 sSpecialCharStr4;
extern const u16 sSpecialCharStr5;
extern const u16 sSpecialCharStr1;
extern const u16 sSpecialCharStr3;
extern const u16 sSpecialCharStr7;
extern const char *const sGameFontFileParts[3];
extern const GxLoadCharFunc sTextVramLoadFuncsA[6];
extern const GxLoadCharFunc sTextVramLoadFuncsB[6];
extern const u8 sToUpperPairs[0x7a];
extern const u8 sGameCharToAsciiTable[0xe0];
extern const u32 data_020ca638;
}

char sGameFontPartAttr[] = "attr";

const u8 sGameCharToAsciiTable[0xe0] = {
    0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x61, 0x62, 0x63, 0x64, 0x65,
    0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
    0x76, 0x77, 0x78, 0x79, 0x7a, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x83,
    0x8a, 0x8c, 0x8e, 0x9a, 0x9c, 0x9e, 0x9f, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
    0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd8, 0xd9,
    0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
    0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf8, 0xf9, 0xfa,
    0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0x20, 0x0a, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
    0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x5b, 0x5c, 0x5d,
    0x5e, 0x5f, 0x60, 0x7b, 0x7c, 0x7d, 0x7e, 0x80, 0x82, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8b,
    0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9b, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5,
    0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xd7, 0xf7, 0x01, 0x04, 0x06, 0x07,
};

u16 sCharSortKeyTable[0xe0] = {
    sCharSortKeyZero, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21,
    0x22, 0x23, 0x24, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x2a, 0x2b, 0x29,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, 0x25, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, 0x25, sCharSortKeyZero, 0x25, 0x26, 0x25, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, 0x28, 0x25, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, 0x25, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, 0x25, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero, sCharSortKeyZero,
    sCharSortKeyZero, sCharSortKeyZero, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
};

GameFont gFontASub;

u8 gTextTileBuffer[0x400];

GameFont gFontA;

const char *const sGameFontFileParts[3] = {sGameFontPartHead, sGameFontPartAttr, sGameFontPartImg};

const u16 sCharSortKeyZero = 0;

GameFont gFontB;

const u16 sSpecialCharStr4 = 4;

GameFont gFontC;

char sGameFontPartHead[] = "head";

const u16 sSpecialCharStr7 = 7;

const u16 sSpecialCharStr1 = 1;

u8 gTextLabelList[2 * sizeof(void *) + 4] HOST_ALIGN8;

void *gTextHeap;

const u16 sSpecialCharStr2 = 2;

ProcProfile sTextSystemModuleProfile = {(void *(*)())TextSystemModule_Create, 0xce, 0xca};

char sGameFontPartImg[] = "img";

const u16 sSpecialCharStr3 = 3;

const u8 sToUpperPairs[0x7a] = {
    0x61, 0x41, 0x62, 0x42, 0x63, 0x43, 0x64, 0x44, 0x65, 0x45, 0x66, 0x46, 0x67, 0x47,
    0x68, 0x48, 0x69, 0x49, 0x6a, 0x4a, 0x6b, 0x4b, 0x6c, 0x4c, 0x6d, 0x4d, 0x6e, 0x4e,
    0x6f, 0x4f, 0x70, 0x50, 0x71, 0x51, 0x72, 0x52, 0x73, 0x53, 0x74, 0x54, 0x75, 0x55,
    0x76, 0x56, 0x77, 0x57, 0x78, 0x58, 0x79, 0x59, 0x7a, 0x5a, 0x9a, 0x8a, 0x9c, 0x8c,
    0x9a, 0x8a, 0xe0, 0xc0, 0xe1, 0xc1, 0xe2, 0xc2, 0xe3, 0xc3, 0xe4, 0xc4, 0xe5, 0xc5,
    0xe6, 0xc6, 0xe7, 0xc7, 0xe8, 0xc8, 0xe9, 0xc9, 0xea, 0xca, 0xeb, 0xcb, 0xec, 0xcc,
    0xed, 0xcd, 0xee, 0xce, 0xef, 0xcf, 0xf0, 0xd0, 0xf1, 0xd1, 0xf2, 0xd2, 0xf3, 0xd3,
    0xf4, 0xd4, 0xf5, 0xd5, 0xf6, 0xd6, 0xf8, 0xd8, 0xf9, 0xd9, 0xfa, 0xda, 0xfb, 0xdb,
    0xfc, 0xdc, 0xfd, 0xdd, 0xfe, 0xde, 0xff, 0x9f, 0x00, 0x00,
};

GameFont gFontD;

const GxLoadCharFunc sTextVramLoadFuncsB[6] = {
    GXS_LoadBG0Char, GXS_LoadBG1Char, GXS_LoadBG2Char, GXS_LoadBG3Char, GXS_LoadOBJ, NULL,
};

const u16 sSpecialCharStr5 = 5;

const u16 sSpecialCharStr6 = 6;

const GxLoadCharFunc sTextVramLoadFuncsA[6] = {
    GX_LoadBG0Char, GX_LoadBG1Char, GX_LoadBG2Char, GX_LoadBG3Char, GX_LoadOBJ, NULL,
};


extern "C" TextSystemModule *TextSystemModule_Create(void) {
    return new TextSystemModule;
}

TextSystemModule::TextSystemModule() {}

TextSystemModule::~TextSystemModule() {}

BOOL TextSystemModule::onCreate() {
    Text_InitSystem();
    MailCheck_LoadWordList();
    return TRUE;
}

BOOL TextSystemModule::onExecute() {
    TextLabel_FlushGroup1();
    return TRUE;
}

BOOL TextSystemModule::onDelete() {
    Text_ShutdownSystem();
    return TRUE;
}

extern "C" {

void StrBuf_Clear(StrBuf *buf) {
    u32 size = buf->size();
    MI_CpuFill8(buf->data(), 0, size);
}

BOOL StrBuf_SetCString(StrBuf *buf, const char *src) {
    u32 size = buf->size();
    char *data = (char *)buf->data();
    s32 last = size - 1;
    char *end = data + last;
    BOOL ok;
    data[last] = 0;
    strncpy(data, src, size);
    ok = data[last] == 0;
    if (!ok) {
        *end = 0;
    }
    return ok;
}

BOOL StrBuf_Copy(StrBuf *dst, StrBuf *src) {
    return StrBuf_SetCString(dst, (const char *)src->data());
}

BOOL StrBuf_GameToAscii(StrBuf *out, StrBuf *in) {
    s32 inLen = in->size();
    const u8 *s = in->data();
    char *o = (char *)out->data();
    u32 outLen = out->size();
    u32 pos = 0;
    BOOL overflow = FALSE;
    BOOL terminated = FALSE;
    s32 i;

    for (i = 0; i < inLen; i++, s++) {
        char tmp[4];
        char *p = o + pos;
        s32 n = Text_GameCharToAscii(tmp, *s);
        if (pos + n <= outLen) {
            if (n == 1) {
                *p = tmp[0];
                if (tmp[0] == 0) {
                    terminated = TRUE;
                }
            } else if (n == 2) {
                p[0] = tmp[0];
                p[1] = tmp[1];
            }
        } else {
            overflow = TRUE;
            break;
        }
        pos += n;
        if (terminated) {
            break;
        }
    }
    if (!overflow && pos < outLen) {
        terminated = TRUE;
        while (pos < outLen) {
            o[pos++] = 0;
        }
    }
    if (!terminated) {
        *(o + outLen - 1) = 0;
    }
    return !overflow && terminated;
}

void StrBuf_ClearAlt(StrBuf *buf) {
    u32 size = buf->size();
    MI_CpuFill8(buf->data(), 0, size);
}

BOOL StrBuf_SetBytes(StrBuf *buf, const void *src, s32 len) {
    s32 size = buf->size();
    u8 *data = buf->data();
    s32 rest = size - len;
    BOOL ok = rest >= 0;
    if (!ok) {
        len = size;
    }
    MI_CpuCopy8(src, data, len);
    if (rest > 0) {
        MI_CpuFill8(data + len, 0, rest);
    }
    return ok;
}

BOOL StrBuf_AsciiToGame(StrBuf *dst, StrBuf *src) {
    const u8 *s = src->data();
    u32 srcLen = src->size();
    u32 i = 0;
    u8 *d = dst->data();
    u32 dstLen = dst->size();
    u32 j = 0;
    BOOL result = TRUE;
    u8 c;

    while (i < srcLen && j < dstLen) {
        s32 n;
        if (*s == 0) {
            break;
        }
        n = Text_AsciiToGameCharPtr(&c, s);
        if (n == 0) {
            n = 1;
            result = FALSE;
        } else {
            *d++ = c;
            j++;
        }
        s += n;
        i += n;
    }
    if (j >= dstLen && *s != 0) {
        result = FALSE;
    }
    while (j < dstLen) {
        *d = 0;
        j++;
        d++;
    }
    return result;
}

BOOL StrBuf_GetBytes(StrBuf *obj, u8 *dst, s32 size) {
    const u8 *src = obj->data();
    s32 len = obj->size();
    BOOL fits = size >= len;
    s32 i;
    if (!fits) {
        len = size;
    }
    for (i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    for (; i < size; i++) {
        dst[i] = 0;
    }
    return fits;
}

}

GameFont::GameFont() {
    header = NULL;
    glyphs = NULL;
    bitmaps = NULL;
}

GameFont::~GameFont() {
    GameFont_Free(this);
}

extern "C" {

void GameFont_Load(GameFontDesc *font, const char *name, void *arg2, GameFontDesc *ext, u8 arg4) {
    void *files[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        files[i] = arg2 != NULL ? File_LoadF("/font/%s_%s_%s.bin", name, sGameFontFileParts[i], arg2)
                                : File_LoadF("/font/%s_%s.bin", name, sGameFontFileParts[i]);
    }
    font->header = (GameFontHeader *)files[0];
    font->glyphs = (GameFontGlyph *)files[1];
    font->bitmaps = (u8 *)files[2];
    font->subFont = ext;
    font->unk_10 = arg4;
}

void GameFont_Free(GameFontDesc *font) {
    if (font->header != NULL) {
        Mem_Free(font->header);
        font->header = NULL;
    }
    if (font->glyphs != NULL) {
        Mem_Free(font->glyphs);
        font->glyphs = NULL;
    }
    if (font->bitmaps != NULL) {
        Mem_Free(font->bitmaps);
        font->bitmaps = NULL;
    }
}

u32 GameFont_GetGlyphWidth(GameFontDesc *font, u32 c) {
    u32 width = 0;
    if (c & 0x80000000) {
        width = GameFont_GetGlyphWidth(font->subFont, c & 0x7fffffff);
    } else if (c < font->header->glyphCount) {
        width = font->glyphs[c].width;
    }
    return width;
}

const u8 *GameFont_GetGlyphBitmap(GameFontDesc *font, u32 c) {
    const u8 *glyph = NULL;
    if (c & 0x80000000) {
        glyph = GameFont_GetGlyphBitmap(font->subFont, c & 0x7fffffff);
    } else {
        GameFontHeader *info = font->header;
        if (c < info->glyphCount) {
            u32 size = (u32)(info->cellWidth * info->cellHeight) >> 3;
            glyph = font->bitmaps + size * c;
        }
    }
    return glyph;
}

}

extern "C" {
s32 GameFont_FindGlyph(GameFontDesc *font, s32 c) {
    BOOL ok = FALSE; s32 result = ~ok;
    u32 i;
    u32 idx;
    s32 v;
    s32 neg;
    u32 count;
    if (font->subFont != NULL && c <= 7 && c >= 1) {
        ok = TRUE;
    }
    if (ok) {
        result = GameFont_FindGlyph(font->subFont, c + 0x20);
        if (result != -1) {
            result |= data_020ca638;
        }
    } else {
        count = font->header->glyphCount;
        i = 0;
        neg = ~i;
        for (; i < count; i++) {
            v = neg;
            if ((i & 0x80000000) != 0) {
                GameFontDesc *sec = ((volatile GameFontDesc *)font)->subFont;
                idx = i & 0x7fffffff;
                if (idx < sec->header->glyphCount) {
                    v = sec->glyphs[idx].code;
                }
            } else if (i < count) {
                v = font->glyphs[i].code;
            }
            if (v == c) {
                result = i;
                break;
            }
        }
    }
    return result;
}
}

void TextLabel::requestRedraw() {
    redrawPending = 1;
    if (group == 2) {
        render();
        redrawPending = 0;
    }
}

void TextLabel::requestClear(s32 arg1) {
    clearRequest = arg1;
    if (group == 2 && clearRequest != -1) {
        clear();
        clearRequest = -1;
    }
}

void TextLabel::alignCenter() {
    u32 width = measureWidth();
    u32 total = widthTiles * 8;
    if (total > width) {
        xOffset = (total - width) / 2;
    } else {
        xOffset = 0;
    }
}

void TextLabel::alignRight() {
    u32 width = measureWidth();
    u32 total = widthTiles * 8;
    if (total > width) {
        xOffset = total - width;
    } else {
        xOffset = 0;
    }
}

void TextLabel::setHighlight(u8 arg1, u8 arg2, u32 arg3, u32 arg4) {
    highlightAFg = arg1;
    highlightABg = arg2;
    highlightAStart = arg3;
    highlightALen = arg4;
}

void TextLabel::setHighlights(u8 arg1, u8 arg2, u32 arg3, u32 arg4, u8 arg5, u8 arg6, u32 arg7, u32 arg8) {
    highlightAFg = arg1;
    highlightABg = arg2;
    highlightAStart = arg3;
    highlightALen = arg4;
    highlightBFg = arg5;
    highlightBBg = arg6;
    highlightBStart = arg7;
    highlightBLen = arg8;
}

u32 TextLabel::getWidthInTiles() {
    return (measureWidth() + 7) >> 3;
}

void TextLabel::beginMeasure() {
    curX = 0;
    curGlyph = -1;
}

void TextLabel::measureChar(u32 c) {
    curGlyph = GameFont_FindGlyph(font, c);
    if (curGlyph == -1) {
        curGlyph = GameFont_FindGlyph(font, 0x40);
    }
    curX += GameFont_GetGlyphWidth(font, curGlyph);
    curX += letterSpacing;
}

void TextLabel::endMeasure() {}

extern "C" void Text_InitSystem(void) {
    void *heap;

    GameFont_Load(&gFontASub, "fontASub", 0, 0, 1);
    GameFont_Load(&gFontA, "fontA", 0, &gFontASub, 0);
    GameFont_Load(&gFontB, "fontB", 0, 0, 0);
    GameFont_Load(&gFontC, "fontC", 0, 0, 0);
    GameFont_Load(&gFontD, "fontD", 0, 0, 0);
    heap = ExpHeap_Create(0x1800, gCurrentHeap);
    gTextHeap = heap;
    if (heap != NULL) {
        NNS_FndInitList(gTextLabelList, __builtin_offsetof(TextLabel, listLink));
    }
}

extern "C" void Text_ShutdownSystem(void) {
    if (gTextHeap != NULL) {
        TextLabel_DestroyAll();
        static_cast<Heap *>(gTextHeap)->destroy2();
        gTextHeap = NULL;
    }
    GameFont_Free(&gFontASub);
    GameFont_Free(&gFontA);
    GameFont_Free(&gFontB);
    GameFont_Free(&gFontC);
    GameFont_Free(&gFontD);
}

extern "C" void TextLabel_FlushGroup1(void) {
    TextLabel_FlushGroup(1);
}

extern "C" void Text_ResetLabels(void) {
    TextLabel_DestroyAll();
}

void TextLabel::clearTileBuffer() {
    MI_CpuFill8(gTextTileBuffer, (u8)(bgColor | (bgColor << 4)), 0x400);
}

extern "C" void TextLabel_FlushGroup(s32 arg0) {
    TextLabel *obj = NULL;
    for (;;) {
        obj = (TextLabel *)NNS_FndGetNextListObject(gTextLabelList, obj);
        if (obj == NULL) {
            break;
        }
        if (obj->group != arg0) {
            continue;
        }
        if (obj->clearRequest != -1) {
            obj->clear();
            obj->clearRequest = -1;
        }
        if (obj->redrawPending) {
            obj->render();
            obj->redrawPending = 0;
        }
    }
}

void TextLabel::render() {
    u32 height = font->header->cellHeight;
    u32 limit = heightTiles << 3;

    savedFgColor = fgColor;
    if (tileIndex != -1) {
        destOffset = tileIndex << 5;
    } else if (destBuffer != 0) {
        destOffset = 0;
    }
    isLastRow = 0;
    for (curRowY = 0; curRowY < height && curRowY < limit; curRowY += 8) {
        u32 next = curRowY + 8;
        isLastRow = (next >= height || next >= limit) ? 1 : 0;
        draw();
        if (rowStride1K) {
            destOffset += 0x400;
        } else {
            destOffset += rowBytes;
        }
    }
}

void TextLabel::beginRow() {
    clearTileBuffer();
    fgColor = savedFgColor;
    curGlyph = -1;
    curX = xOffset;
    charIndex = 0;
}

void TextLabel::drawChar(u32 c) {
    u32 start;

    curGlyph = GameFont_FindGlyph(font, c);
    if (curGlyph == -1) {
        curGlyph = GameFont_FindGlyph(font, 0x40);
    }
    start = curX;
    curX += drawGlyph();
    drawLetterSpacing();
    curX += letterSpacing;
    if (isLastRow && underline) {
        drawUnderline(start);
    }
    charIndex++;
}

void TextLabel::flushRow() {
    u32 size;
    u8 *dst;
    u8 *src;
    u8 *end;
    u8 bg;
    u8 bgHigh;

    size = rowBytes;
    if (size > 0x400) {
        size = 0x400;
    }
    DC_FlushRange(gTextTileBuffer, size);
    if (copyMode == 2 || copyMode == 3) {
        sTextVramLoadFuncsA[vramLoader](gTextTileBuffer, destOffset, size);
    }
    if (copyMode == 1 || copyMode == 3) {
        sTextVramLoadFuncsB[vramLoader](gTextTileBuffer, destOffset, size);
    }
    if (copyMode == 0) {
        if (blendOverBg) {
            dst = (u8 *)(destBuffer + destOffset);
            src = gTextTileBuffer;
            end = src + size;
            bg = bgColor;
            bgHigh = bg << 4;
            for (; src < end; src++, dst++) {
                if ((*dst & 0xf0) == bgHigh) {
                    *dst &= 0xf;
                    *dst |= *src & 0xf0;
                }
                if ((*dst & 0xf) == bg) {
                    *dst &= 0xf0;
                    *dst |= *src & 0xf;
                }
            }
        } else {
            MI_CpuCopy8(gTextTileBuffer, (void *)(destBuffer + destOffset), size);
        }
    }
}

u32 TextLabel::drawGlyph() {
    u32 glyphWidth;
    const u8 *glyph;
    u8 mask;
    u8 fg;
    u8 bg;
    u32 width;
    u32 row;
    u32 x;
    u32 pos;
    u32 tile;
    u32 index;
    u32 bit;
    u32 color;
    BOOL drawBackground;
    u8 *pixel;
    u32 start = 0;

    width = font->header->cellWidth;
    glyphWidth = GameFont_GetGlyphWidth(font, curGlyph);
    glyph = GameFont_GetGlyphBitmap(font, curGlyph);
    mask = 0x80;
    pos = (curRowY * width) >> 3;

    drawBackground = TRUE;
    if (!isInHighlightA() && !isInHighlightB()) {
        drawBackground = FALSE;
    }
    fg = getFgColor();
    bg = getBgColor();

    for (row = 0; row < 8; row++) {
        for (x = start; x < width; x++) {
            if (x < glyphWidth) {
                bit = glyph[pos] & mask;
                color = bit ? fg : bg;
                if (bit || drawBackground) {
                    u32 px = curX + x;
                    tile = px >> 3;
                    index = (row * 8 + (px - tile * 8)) >> 1;
                    if (tile < 0x20) {
                        pixel = &gTextTileBuffer[tile * 32] + index;
                        if (px & 1) {
                            *pixel &= ~0xf0;
                            *pixel |= (u8)(color << 4);
                        } else {
                            *pixel &= ~0xf;
                            *pixel |= (u8)color;
                        }
                    }
                }
            }
            mask >>= 1;
            if (mask == 0) {
                mask = 0x80;
                pos++;
            }
        }
    }
    return glyphWidth;
}

void TextLabel::drawLetterSpacing() {
    u32 color;
    u32 row;
    u32 x;
    u32 px;
    u32 tile;
    u32 index;
    u8 *pixel;

    if (isInHighlightA() || isInHighlightB()) {
        color = getBgColor();
        for (row = 0; row < 8; row++) {
            for (x = 0; x < letterSpacing; x++) {
                px = curX + x;
                tile = px >> 3;
                index = (row * 8 + (px - tile * 8)) >> 1;
                if (tile < 0x20) {
                    pixel = &gTextTileBuffer[tile * 32] + index;
                    if (px & 1) {
                        *pixel &= ~0xf0;
                        *pixel |= (u8)(color << 4);
                    } else {
                        *pixel &= ~0xf;
                        *pixel |= (u8)color;
                    }
                }
            }
        }
    }
}

void TextLabel::drawUnderline(u32 x) {
    u32 high;
    u32 color;
    u32 tile;
    u32 index;
    u8 *pixel;

    color = getFgColor();
    high = color << 4;
    for (; x < curX; x++) {
        tile = x >> 3;
        index = ((x - tile * 8) + 0x30) >> 1;
        if (tile < 0x20) {
            pixel = &gTextTileBuffer[tile * 32] + index;
            if (x & 1) {
                *pixel &= ~0xf0;
                *pixel |= (u8)high;
            } else {
                *pixel &= ~0xf;
                *pixel |= (u8)color;
            }
        }
    }
}

void TextLabel::clear() {
    u32 size;
    u32 offset;
    u32 i;

    clearTileBuffer();

    if (clearRequest == 0) {
        size = rowBytes;
    } else {
        size = clearRequest << 5;
    }
    if (size > 0x400) {
        size = 0x400;
    }

    offset = 0;
    if (tileIndex != -1) {
        offset = tileIndex << 5;
    } else if (destBuffer != 0) {
        offset = 0;
    }

    for (i = 0; i < heightTiles; i++) {
        DC_FlushRange(gTextTileBuffer, size);
        if (copyMode == 2 || copyMode == 3) {
            sTextVramLoadFuncsA[vramLoader](gTextTileBuffer, offset, size);
        }
        if (copyMode == 1 || copyMode == 3) {
            sTextVramLoadFuncsB[vramLoader](gTextTileBuffer, offset, size);
        }
        if (copyMode == 0) {
            MI_CpuCopy8(gTextTileBuffer, (void *)(destBuffer + offset), size);
        }
        if (rowStride1K) {
            offset += 0x400;
        } else {
            offset += rowBytes;
        }
    }
}

BOOL TextLabel::isInHighlightA() {
    BOOL result = FALSE;
    if (charIndex >= highlightAStart && charIndex < highlightAStart + highlightALen) {
        result = TRUE;
    }
    return result;
}

BOOL TextLabel::isInHighlightB() {
    BOOL result = FALSE;
    if (charIndex >= highlightBStart && charIndex < highlightBStart + highlightBLen) {
        result = TRUE;
    }
    return result;
}

u8 TextLabel::getFgColor() {
    u8 result = fgColor;
    if (isInHighlightA()) {
        result = highlightAFg;
    } else if (isInHighlightB()) {
        result = highlightBFg;
    }
    return result;
}

u8 TextLabel::getBgColor() {
    u8 result = bgColor;
    if (isInHighlightA()) {
        result = highlightABg;
    } else if (isInHighlightB()) {
        result = highlightBBg;
    }
    return result;
}

extern "C" void TextLabel_FlushGroup0(void) {
    TextLabel_FlushGroup(0);
}

extern "C" void TextLabel_DestroyAll(void) {
    TextLabel *obj;
    for (;;) {
        obj = (TextLabel *)NNS_FndGetNextListObject(gTextLabelList, NULL);
        if (obj == NULL) {
            break;
        }
        NNS_FndRemoveListObject(gTextLabelList, obj);
        obj->~TextLabel();
        Heap_Free(static_cast<Heap *>(gTextHeap), obj);
    }
}

TextLabel::TextLabel(u32 arg1, s32 arg2, s32 arg3) {
    Unk_02050288_08 zero;

    unk_04 = 0;
    listLink = *(Unk_02050288_08 *)func_02133ef8(&zero, sizeof(zero));
    textStart = 0;
    tileIndex = arg1;
    destBuffer = 0;
    widthTiles = arg2;
    heightTiles = arg3;
    font = &gFontA;
    vramLoader = 2;
    xOffset = 0;
    letterSpacing = 1;
    fgColor = 1;
    bgColor = 0xf;
    highlightAFg = 0;
    highlightABg = 0;
    highlightBFg = 0;
    highlightBBg = 0;
    highlightAStart = 0;
    highlightALen = 0;
    highlightBStart = 0;
    highlightBLen = 0;
    copyMode = 1;
    redrawPending = 0;
    rowStride1K = 0;
    blendOverBg = 0;
    underline = 0;
    group = 0;
    clearRequest = -1;
    rowBytes = arg2 << 5;
    curGlyph = -1;
    curX = 0;
    curRowY = 0;
    destOffset = 0;
    savedFgColor = 1;
    isLastRow = 0;
    charIndex = 0;
}

TextLabel::TextLabel(u8 *arg1, s32 arg2, s32 arg3) {
    Unk_02050288_08 zero;

    unk_04 = 0;
    listLink = *(Unk_02050288_08 *)func_02133ef8(&zero, sizeof(zero));
    textStart = 0;
    tileIndex = -1;
    destBuffer = arg1;
    widthTiles = arg2;
    heightTiles = arg3;
    font = &gFontA;
    vramLoader = 5;
    xOffset = 0;
    letterSpacing = 1;
    fgColor = 1;
    bgColor = 0xf;
    highlightAFg = 0;
    highlightABg = 0;
    highlightBFg = 0;
    highlightBBg = 0;
    highlightAStart = 0;
    highlightALen = 0;
    highlightBStart = 0;
    highlightBLen = 0;
    copyMode = 0;
    redrawPending = 0;
    rowStride1K = 0;
    blendOverBg = 0;
    underline = 0;
    group = 0;
    clearRequest = -1;
    rowBytes = arg2 << 5;
    curGlyph = -1;
    curX = 0;
    curRowY = 0;
    destOffset = 0;
    savedFgColor = 1;
    isLastRow = 0;
    charIndex = 0;
}

TextLabel::~TextLabel() {}

extern "C" {

BOOL Text_GameCharToAscii(char *out, u32 index) {
    *out = sGameCharToAsciiTable[index];
    return TRUE;
}


BOOL Text_AsciiToGameCharPtr(u8 *out, const u8 *c) {
    return Text_AsciiToGameChar(out, *c);
}

BOOL Text_AsciiToGameChar(u8 *out, u32 c) {
    const u8 *entry = sGameCharToAsciiTable;
    u32 i = 0;
    while (i < 0xe0) {
        if (*entry == c) {
            *out = i;
            return TRUE;
        }
        i++;
        entry++;
    }
    return (BOOL)(uptr)out;
}

const u8 *Text_GetSpecialCharStr1(void) { return (const u8 *)&sSpecialCharStr1; }
const u8 *Text_GetSpecialCharStr4(void) { return (const u8 *)&sSpecialCharStr4; }
const u8 *Text_GetSpecialCharStr6(void) { return (const u8 *)&sSpecialCharStr6; }
const u8 *Text_GetSpecialCharStr7(void) { return (const u8 *)&sSpecialCharStr7; }
const u8 *Text_GetSpecialCharStr5(void) { return (const u8 *)&sSpecialCharStr5; }
const u8 *Text_GetSpecialCharStr2(void) { return (const u8 *)&sSpecialCharStr2; }
const u8 *Text_GetSpecialCharStr3(void) { return (const u8 *)&sSpecialCharStr3; }
const u8 *Text_GetSpecialCharStr9(void) { return NULL; }
const u8 *Text_GetSpecialCharStr10(void) { return NULL; }

u32 Text_ToUpper(u32 key) {
    const u8 *entry = sToUpperPairs;
    while (*entry != 0) {
        if (key == *entry) {
            return entry[1];
        }
        entry += 2;
    }
    return key;
}

u16 Text_GetCharSortKey(u32 index) {
    u16 result = 0;
    if (index < 0xe0) {
        result = sCharSortKeyTable[index];
    }
    return result;
}

}
