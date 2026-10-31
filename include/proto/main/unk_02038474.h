#ifndef PROTO_PROTO_MAIN_UNK_02038474_H
#define PROTO_PROTO_MAIN_UNK_02038474_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "talk/MsgString.h"
#include "text/Unk_02050288.h"
class ChatBalloon;
class ChatBalloonList;
class ChatBalloonProc;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ChatBalloon_Dismiss
void ChatBalloon_Dismiss(s32 idx);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_DismissAll
void ChatBalloon_DismissAll(void);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_IsRemoteBusy
BOOL ChatBalloon_IsRemoteBusy(void);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_IsOwnBusy
BOOL ChatBalloon_IsOwnBusy(void);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_RefreshLabelsUnk
void ChatBalloon_RefreshLabelsUnk(void);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_ClearAll
void ChatBalloon_ClearAll(void);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_ReceiveRemote
void ChatBalloon_ReceiveRemote();
#endif
#ifndef PROTO_LOCAL_ChatBalloon_ReadSyncVar
u8 ChatBalloon_ReadSyncVar(s32 idx);
#endif
#ifndef PROTO_LOCAL_ChatQuickMsg_PostWantToSave
void ChatQuickMsg_PostWantToSave();
#endif
#ifndef PROTO_LOCAL_ChatQuickMsg_CheckButtons
void ChatQuickMsg_CheckButtons(void *self);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ChatBalloon_Post
void ChatBalloon_Post(s32 idx, StrBuf *a, MsgString *b);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_SendSyncVar
void ChatBalloon_SendSyncVar(s32 i, ChatBalloon *x);
#endif
#ifndef PROTO_LOCAL_ChatBalloon_PackSyncVar
void ChatBalloon_PackSyncVar(u8 *a, u32 b, ChatBalloon *c);
#endif
#ifndef PROTO_LOCAL_ChatBalloonProc_Create
ChatBalloonProc *ChatBalloonProc_Create();
#endif
}
#ifndef PROTO_LOCAL_sChatBalloonSyncBuf
extern u8 sChatBalloonSyncBuf[0x29];
#endif
#ifndef PROTO_LOCAL_sChatBalloonProcProfile
extern ProcProfile sChatBalloonProcProfile;
#endif
#ifndef PROTO_LOCAL_sChatBalloonList
extern ChatBalloonList *sChatBalloonList;
#endif
#ifndef PROTO_LOCAL_sChatQuickMsgCooldown
extern s32 sChatQuickMsgCooldown;
#endif
#endif

#endif
