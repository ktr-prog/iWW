#ifndef PROTO_PROTO_MAIN_UNK_020B2C50_H
#define PROTO_PROTO_MAIN_UNK_020B2C50_H


#include "types.h"
#ifdef __cplusplus
#include "talk/ArticleCacheEntry.h"
#include "talk/MsgString.h"
#include "talk/MsgString256.h"
#include "talk/MsgStringBase.h"
class StringBank;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_String_IsNonNullChar
BOOL String_IsNonNullChar(u32 x);
#endif
#ifndef PROTO_LOCAL_Str_LenN
s32 Str_LenN(const char *s, u32 max);
#endif
#ifndef PROTO_LOCAL_Str_ShiftRight
void Str_ShiftRight(char *s, u32 size, s32 start, s32 shift);
#endif
#ifndef PROTO_LOCAL_Str_WriteDigitsReversed
void Str_WriteDigitsReversed(char *s, u32 size, s32 n, s32 maxDigits);
#endif
#ifndef PROTO_LOCAL_Str_PadFrontSpaces
void Str_PadFrontSpaces(char *s, u32 size, s32 width);
#endif
#ifndef PROTO_LOCAL_Str_PadBackSpaces
void Str_PadBackSpaces(char *s, u32 size, s32 width);
#endif
#ifndef PROTO_LOCAL_Str_PadBackZeros
void Str_PadBackZeros(char *s, u32 size, s32 width);
#endif
#ifndef PROTO_LOCAL_Str_InsertThousandsSeparators
void Str_InsertThousandsSeparators(char *s, u32 size, s32 minRun);
#endif
#ifndef PROTO_LOCAL_Str_Reverse
void Str_Reverse(char *s, u32 size);
#endif
#ifndef PROTO_LOCAL_String_CharEqualsIgnoreCase
BOOL String_CharEqualsIgnoreCase(u32 a, u32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_String_GetTabooScratch
MsgString256 *String_GetTabooScratch(void);
#endif
#ifndef PROTO_LOCAL_String_Load
BOOL String_Load(MsgString *buf, u8 *key, const char *name);
#endif
#ifndef PROTO_LOCAL_String_LoadResolveAltText
BOOL String_LoadResolveAltText(MsgString *buf, u8 *key, const char *name);
#endif
#ifndef PROTO_LOCAL_String_Load2d
BOOL String_Load2d(MsgString *buf, u8 *key, const char *name);
#endif
#ifndef PROTO_LOCAL_String_SetSlot
u8 String_SetSlot(u32 idx, MsgString *other);
#endif
#ifndef PROTO_LOCAL_String_AppendUnitSuffix
BOOL String_AppendUnitSuffix(MsgString *out, s32 val, s32 kind);
#endif
#ifndef PROTO_LOCAL_String_FormatNumber
BOOL String_FormatNumber(MsgString *out, s32 val, s32 width, s32 mode, s32 kind, s32 unused);
#endif
#ifndef PROTO_LOCAL_String_FormatFixedPoint
BOOL String_FormatFixedPoint(MsgString *out, s32 val, s32 digits);
#endif
#ifndef PROTO_LOCAL_String_GetWeekdayName
BOOL String_GetWeekdayName(MsgString *buf, u32 idx, BOOL flag);
#endif
#ifndef PROTO_LOCAL_String_GetMonthName
BOOL String_GetMonthName(MsgString *buf, u8 v);
#endif
#ifndef PROTO_LOCAL_String_GetDayOrdinal
BOOL String_GetDayOrdinal(MsgString *buf, u8 v);
#endif
#ifndef PROTO_LOCAL_String_MakeNickname
BOOL String_MakeNickname(MsgString *buf, MsgStringBase *name, u8 *key);
#endif
#ifndef PROTO_LOCAL_String_CensorTaboo
BOOL String_CensorTaboo(MsgString *buf);
#endif
#ifndef PROTO_LOCAL_String_GetArticle
ArticleCacheEntry *String_GetArticle(u8 *key);
#endif
}
#ifndef PROTO_LOCAL_gStringBank
extern StringBank gStringBank;
#endif
#endif

#endif
