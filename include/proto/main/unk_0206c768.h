#ifndef PROTO_PROTO_MAIN_UNK_0206C768_H
#define PROTO_PROTO_MAIN_UNK_0206C768_H


#include "types.h"
#ifdef __cplusplus
#include "item/LetterView.h"
#include "talk/MsgString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MailCheck_LoadWordList
void MailCheck_LoadWordList();
#endif
#ifndef PROTO_LOCAL_MailCheck_IsSeparator
BOOL MailCheck_IsSeparator(u32 c);
#endif
#ifndef PROTO_LOCAL_MailCheck_MatchWord
BOOL MailCheck_MatchWord(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_MailCheck_MatchWordAt
BOOL MailCheck_MatchWordAt(u8 *p, s32 n, s32 off);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_String_LoadByIndexB
BOOL String_LoadByIndexB(MsgString *buf, const char *name, u32 key);
#endif
#ifndef PROTO_LOCAL_MailCheck_GradeLetter
s32 MailCheck_GradeLetter(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetBodyLength
s32 Letter_GetBodyLength(LetterView *self);
#endif
}
#ifndef PROTO_LOCAL_sMailCheckWords
extern u8 sMailCheckWords[0x8fc];
#endif
#ifndef PROTO_LOCAL_sMailCheckWordEnds
extern s16 sMailCheckWordEnds[0x1a];
#endif
#ifndef PROTO_LOCAL_sMailCheckWordUses
extern u8 sMailCheckWordUses[0xc0];
#endif
#endif

#endif
