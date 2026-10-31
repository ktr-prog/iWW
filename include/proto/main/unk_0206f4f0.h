#ifndef PROTO_PROTO_MAIN_UNK_0206F4F0_H
#define PROTO_PROTO_MAIN_UNK_0206F4F0_H


#include "types.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CommSub_RecvBbsPost
void CommSub_RecvBbsPost(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvInsectRelease
void CommSub_RecvInsectRelease(u8 *p, u32 id);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvReleaseOrThrow
void CommSub_RecvReleaseOrThrow(u8 *p, u32 id);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvItemList15
void CommSub_RecvItemList15(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvBottleLetter
void CommSub_RecvBottleLetter(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSub_ClearBottleLetter
void CommSub_ClearBottleLetter();
#endif
#ifndef PROTO_LOCAL_CommSub_GetPostReply
u8 CommSub_GetPostReply();
#endif
#ifndef PROTO_LOCAL_CommSub_SetPostReply
void CommSub_SetPostReply(u8 v);
#endif
#ifndef PROTO_LOCAL_CommSub_Send
void CommSub_Send(u32 a, u32 b, ...);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvPostLetter
void CommSub_RecvPostLetter(u8 *p, u32 code);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvPostReply
void CommSub_RecvPostReply(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvTownTune
void CommSub_RecvTownTune(u8 *p);
#endif
#ifndef PROTO_LOCAL_HudCountdown_StartWithSe
void HudCountdown_StartWithSe(u32 x);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvCountdownRequest
void CommSub_RecvCountdownRequest(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sCommSubPostReply
extern u8 sCommSubPostReply;
#endif
#ifndef PROTO_LOCAL_sCommCountdownKinds
extern u32 sCommCountdownKinds[5];
#endif
#endif

#endif
