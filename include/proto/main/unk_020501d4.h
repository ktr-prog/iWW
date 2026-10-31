#ifndef PROTO_PROTO_MAIN_UNK_020501D4_H
#define PROTO_PROTO_MAIN_UNK_020501D4_H


#include "types.h"
#include "sys/ProcProfile.h"
struct GameFont;
#ifndef __cplusplus
typedef struct GameFont GameFont;
#endif
#ifdef __cplusplus
#include "text/Unk_02050288.h"
class TextSystemModule;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Text_InitSystem
void Text_InitSystem(void);
#endif
#ifndef PROTO_LOCAL_Text_ShutdownSystem
void Text_ShutdownSystem(void);
#endif
#ifndef PROTO_LOCAL_TextLabel_FlushGroup1
void TextLabel_FlushGroup1(void);
#endif
#ifndef PROTO_LOCAL_Text_ResetLabels
void Text_ResetLabels(void);
#endif
#ifndef PROTO_LOCAL_TextLabel_FlushGroup
void TextLabel_FlushGroup(s32 arg0);
#endif
#ifndef PROTO_LOCAL_TextLabel_FlushGroup0
void TextLabel_FlushGroup0(void);
#endif
#ifndef PROTO_LOCAL_TextLabel_DestroyAll
void TextLabel_DestroyAll(void);
#endif
#ifndef PROTO_LOCAL_Text_GameCharToAscii
BOOL Text_GameCharToAscii(char *out, u32 index);
#endif
#ifndef PROTO_LOCAL_Text_AsciiToGameCharPtr
BOOL Text_AsciiToGameCharPtr(u8 *out, const u8 *c);
#endif
#ifndef PROTO_LOCAL_Text_AsciiToGameChar
BOOL Text_AsciiToGameChar(u8 *out, u32 c);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr1
const u8 *Text_GetSpecialCharStr1(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr4
const u8 *Text_GetSpecialCharStr4(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr6
const u8 *Text_GetSpecialCharStr6(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr7
const u8 *Text_GetSpecialCharStr7(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr5
const u8 *Text_GetSpecialCharStr5(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr2
const u8 *Text_GetSpecialCharStr2(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr3
const u8 *Text_GetSpecialCharStr3(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr9
const u8 *Text_GetSpecialCharStr9(void);
#endif
#ifndef PROTO_LOCAL_Text_GetSpecialCharStr10
const u8 *Text_GetSpecialCharStr10(void);
#endif
#ifndef PROTO_LOCAL_Text_ToUpper
u32 Text_ToUpper(u32 key);
#endif
#ifndef PROTO_LOCAL_Text_GetCharSortKey
u16 Text_GetCharSortKey(u32 index);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TextSystemModule_Create
TextSystemModule *TextSystemModule_Create(void);
#endif
#ifndef PROTO_LOCAL_StrBuf_Clear
void StrBuf_Clear(StrBuf *buf);
#endif
#ifndef PROTO_LOCAL_StrBuf_SetCString
BOOL StrBuf_SetCString(StrBuf *buf, const char *src);
#endif
#ifndef PROTO_LOCAL_StrBuf_Copy
BOOL StrBuf_Copy(StrBuf *dst, StrBuf *src);
#endif
#ifndef PROTO_LOCAL_StrBuf_GameToAscii
BOOL StrBuf_GameToAscii(StrBuf *out, StrBuf *in);
#endif
#ifndef PROTO_LOCAL_StrBuf_ClearAlt
void StrBuf_ClearAlt(StrBuf *buf);
#endif
#ifndef PROTO_LOCAL_StrBuf_SetBytes
BOOL StrBuf_SetBytes(StrBuf *buf, const void *src, s32 len);
#endif
#ifndef PROTO_LOCAL_StrBuf_AsciiToGame
BOOL StrBuf_AsciiToGame(StrBuf *dst, StrBuf *src);
#endif
#ifndef PROTO_LOCAL_StrBuf_GetBytes
BOOL StrBuf_GetBytes(StrBuf *obj, u8 *dst, s32 size);
#endif
#ifndef PROTO_LOCAL_GameFont_Load
void GameFont_Load(GameFontDesc *font, const char *name, void *arg2, GameFontDesc *ext, u8 arg4);
#endif
#ifndef PROTO_LOCAL_GameFont_Free
void GameFont_Free(GameFontDesc *font);
#endif
#ifndef PROTO_LOCAL_GameFont_GetGlyphWidth
u32 GameFont_GetGlyphWidth(GameFontDesc *font, u32 c);
#endif
#ifndef PROTO_LOCAL_GameFont_GetGlyphBitmap
const u8 *GameFont_GetGlyphBitmap(GameFontDesc *font, u32 c);
#endif
#ifndef PROTO_LOCAL_GameFont_FindGlyph
s32 GameFont_FindGlyph(GameFontDesc *font, s32 c);
#endif
}
#ifndef PROTO_LOCAL_sGameFontPartAttr
extern char sGameFontPartAttr[];
#endif
#ifndef PROTO_LOCAL_sCharSortKeyTable
extern u16 sCharSortKeyTable[0xe0];
#endif
#ifndef PROTO_LOCAL_gFontASub
extern GameFont gFontASub;
#endif
#ifndef PROTO_LOCAL_gTextTileBuffer
extern u8 gTextTileBuffer[0x400];
#endif
#ifndef PROTO_LOCAL_gFontA
extern GameFont gFontA;
#endif
#ifndef PROTO_LOCAL_gFontB
extern GameFont gFontB;
#endif
#ifndef PROTO_LOCAL_gFontC
extern GameFont gFontC;
#endif
#ifndef PROTO_LOCAL_sGameFontPartHead
extern char sGameFontPartHead[];
#endif
#ifndef PROTO_LOCAL_gTextLabelList
extern u8 gTextLabelList[2 *sizeof (void *) + 4];
#endif
#ifndef PROTO_LOCAL_gTextHeap
extern void *gTextHeap;
#endif
#ifndef PROTO_LOCAL_sTextSystemModuleProfile
extern ProcProfile sTextSystemModuleProfile;
#endif
#ifndef PROTO_LOCAL_sGameFontPartImg
extern char sGameFontPartImg[];
#endif
#ifndef PROTO_LOCAL_gFontD
extern GameFont gFontD;
#endif
#endif

#endif
