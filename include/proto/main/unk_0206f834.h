#ifndef PROTO_PROTO_MAIN_UNK_0206F834_H
#define PROTO_PROTO_MAIN_UNK_0206F834_H


#include "types.h"
#ifdef __cplusplus
#include "talk/MsgString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_String_Load2dMenuByRef
void String_Load2dMenuByRef(void *a, u8 *p);
#endif
#ifndef PROTO_LOCAL_String_Load2dMenu
void String_Load2dMenu(void *a, u8 v);
#endif
#ifndef PROTO_LOCAL_String_LoadByIndex
void String_LoadByIndex(void *a, const char *c, u8 v);
#endif
#ifndef PROTO_LOCAL_String_FormatNumberWrapper
void String_FormatNumberWrapper(void *o, s32 a, s32 b, s32 c, s32 d, u8 e);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_String_FromEncodedBytes
void String_FromEncodedBytes(MsgString *dst, const void *s, s32 len);
#endif
#ifndef PROTO_LOCAL_String_ToEncodedBytes
void String_ToEncodedBytes(MsgString *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_String_FromEncodedBytesEx
void String_FromEncodedBytesEx(MsgString *dst, const void *s, s32 len, BOOL a, u8 b);
#endif
#ifndef PROTO_LOCAL_String_EqualsEncodedBytes
BOOL String_EqualsEncodedBytes(MsgString *a, u8 *b, s32 len);
#endif
}
#endif

#endif
