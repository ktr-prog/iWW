#ifndef PROTO_PROTO_MAIN_UNK_020A6974_H
#define PROTO_PROTO_MAIN_UNK_020A6974_H


#include "types.h"
#include "sys/ProcProfile.h"
struct TalkMsgIndex;
#ifndef __cplusplus
typedef struct TalkMsgIndex TalkMsgIndex;
#endif
#ifdef __cplusplus
#include "talk/BmgMsgAttr.h"
#include "talk/MsgCopyProcessor.h"
#include "talk/MsgQuery.h"
#include "talk/MsgRenderProcessor.h"
#include "talk/MsgString.h"
#include "talk/MsgTextLabel.h"
#include "text/Unk_02050288.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MsgUiProc_ShowObjPlane
void MsgUiProc_ShowObjPlane();
#endif
#ifndef PROTO_LOCAL_MsgUiProc_HideObjPlane
void MsgUiProc_HideObjPlane();
#endif
#ifndef PROTO_LOCAL_Bmg_ReadMagic
u32 Bmg_ReadMagic(void *p);
#endif
#ifndef PROTO_LOCAL_Bmg_ReadU32
u32 Bmg_ReadU32(void *p);
#endif
#ifndef PROTO_LOCAL_Bmg_ReadU16
u16 Bmg_ReadU16(void *p);
#endif
#ifndef PROTO_LOCAL_Bmg_ReadU8
u8 Bmg_ReadU8(void *p);
#endif
#ifndef PROTO_LOCAL_Bmg_GetMsgAttr
u8 *Bmg_GetMsgAttr(u8 *p);
#endif
#ifndef PROTO_LOCAL_MsgRunner_DtorStub
void MsgRunner_DtorStub(void);
#endif
#ifndef PROTO_LOCAL_Msg_MeasureWidth
u32 Msg_MeasureWidth(u8 *text);
#endif
#ifndef PROTO_LOCAL_Msg_ReadU8
u8 Msg_ReadU8(u8 *p, u32 i);
#endif
#ifndef PROTO_LOCAL_Msg_ReadU16
u16 Msg_ReadU16(u8 *p, u32 i);
#endif
#ifndef PROTO_LOCAL_MsgTag_DtorStub
void MsgTag_DtorStub();
#endif
#ifndef PROTO_LOCAL_Msg_GetColorTag
u8 *Msg_GetColorTag(s32 i);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_Fini
void BmgMsgAttr_Fini();
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_Get
void *BmgMsgAttr_Get(void *p);
#endif
#ifndef PROTO_LOCAL_Input_IsTouchTrig
BOOL Input_IsTouchTrig();
#endif
#ifndef PROTO_LOCAL_Input_IsTouchTrigInRect
BOOL Input_IsTouchTrigInRect(s32 x0, s32 x1, s32 y0, s32 y1);
#endif
#ifndef PROTO_LOCAL_Input_GetTouchTrigPos
BOOL Input_GetTouchTrigPos(u32 *x, u32 *y);
#endif
#ifndef PROTO_LOCAL_Input_GetTouchHeldPos
BOOL Input_GetTouchHeldPos(u32 *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_Input_IsAnyKeyTrig
BOOL Input_IsAnyKeyTrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsATrig
BOOL Input_IsATrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsBTrig
BOOL Input_IsBTrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsUpTrig
BOOL Input_IsUpTrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsDownTrig
BOOL Input_IsDownTrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsStartTrig
BOOL Input_IsStartTrig(void);
#endif
#ifndef PROTO_LOCAL_Input_IsAHeld
BOOL Input_IsAHeld(void);
#endif
#ifndef PROTO_LOCAL_Input_IsBHeld
BOOL Input_IsBHeld(void);
#endif
#ifndef PROTO_LOCAL_Input_IsUpHeld
BOOL Input_IsUpHeld(void);
#endif
#ifndef PROTO_LOCAL_Input_IsDownHeld
BOOL Input_IsDownHeld(void);
#endif
#ifndef PROTO_LOCAL_Input_Lock
void Input_Lock(void);
#endif
#ifndef PROTO_LOCAL_Input_Unlock
void Input_Unlock(void);
#endif
#ifndef PROTO_LOCAL_Input_SetTouchMode
void Input_SetTouchMode(void);
#endif
#ifndef PROTO_LOCAL_Input_SetButtonMode
void Input_SetButtonMode(void);
#endif
#ifndef PROTO_LOCAL_Input_IsTouchMode
BOOL Input_IsTouchMode(void);
#endif
#ifndef PROTO_LOCAL_Input_IsButtonMode
u8 Input_IsButtonMode(void);
#endif
#ifndef PROTO_LOCAL_Input_ResetMode
void Input_ResetMode(void);
#endif
#ifndef PROTO_LOCAL_Input_LoadMode
void Input_LoadMode(void);
#endif
#ifndef PROTO_LOCAL_Input_StoreMode
void Input_StoreMode(void);
#endif
#ifndef PROTO_LOCAL_Input_IsKeyBlocked
BOOL Input_IsKeyBlocked(void);
#endif
#ifndef PROTO_LOCAL_Input_IsTouchBlocked
BOOL Input_IsTouchBlocked(void);
#endif
#ifndef PROTO_LOCAL_Msg_FindTag
u8 *Msg_FindTag(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Msg_GetCharAt
u32 Msg_GetCharAt(u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Msg_GetCharFromEnd
u32 Msg_GetCharFromEnd(u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Msg_CountChars
u32 Msg_CountChars(u8 *a);
#endif
#ifndef PROTO_LOCAL_Msg_SkipLines
u8 *Msg_SkipLines(u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Msg_DecodeGameChar
BOOL Msg_DecodeGameChar(char *out, u8 c);
#endif
#ifndef PROTO_LOCAL_Msg_EncodeGameChar
BOOL Msg_EncodeGameChar(u8 *out, const u8 *src);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MsgTextLabel_CreateVram
MsgTextLabel *MsgTextLabel_CreateVram(u32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_MsgTextLabel_CreateBuffer
MsgTextLabel *MsgTextLabel_CreateBuffer(void *buf, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_MsgTextLabel_Destroy
void MsgTextLabel_Destroy(MsgTextLabel *obj);
#endif
#ifndef PROTO_LOCAL_TextLabel_MeasureMsgWidth
u32 TextLabel_MeasureMsgWidth(MsgString *s);
#endif
#ifndef PROTO_LOCAL_EncodedString_SetRaw
BOOL EncodedString_SetRaw(StrBuf *buf, const void *src, s32 len);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_Init
BmgMsgAttr *BmgMsgAttr_Init(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_Copy
void BmgMsgAttr_Copy(BmgMsgAttr *d, BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_Clear
void BmgMsgAttr_Clear(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte04
u8 BmgMsgAttr_GetByte04(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte05
u8 BmgMsgAttr_GetByte05(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte06
u8 BmgMsgAttr_GetByte06(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte07
u8 BmgMsgAttr_GetByte07(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte09
u8 BmgMsgAttr_GetByte09(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_GetByte08
void BmgMsgAttr_GetByte08(u8 *out, BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_LookupUnkA
u32 BmgMsgAttr_LookupUnkA(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_LookupUnkB
u32 BmgMsgAttr_LookupUnkB(BmgMsgAttr *s);
#endif
#ifndef PROTO_LOCAL_BmgMsgAttr_LookupUnkC
u32 BmgMsgAttr_LookupUnkC(BmgMsgAttr *s);
#endif
}
#ifndef PROTO_LOCAL_gU8None
extern TalkMsgIndex gU8None;
#endif
#ifndef PROTO_LOCAL_sInputLocked
extern u8 sInputLocked;
#endif
#ifndef PROTO_LOCAL_sInputButtonMode
extern u8 sInputButtonMode;
#endif
#ifndef PROTO_LOCAL_gTalkMsgIndexNone
extern TalkMsgIndex gTalkMsgIndexNone;
#endif
#ifndef PROTO_LOCAL_gTalkMsgIndexEnd
extern TalkMsgIndex gTalkMsgIndexEnd;
#endif
#ifndef PROTO_LOCAL_sMsgUiProcProfile
extern ProcProfile sMsgUiProcProfile;
#endif
#ifndef PROTO_LOCAL_gMsgRenderProcessor
extern MsgRenderProcessor gMsgRenderProcessor;
#endif
#ifndef PROTO_LOCAL_gMsgCopyProcessor
extern MsgCopyProcessor gMsgCopyProcessor;
#endif
#ifndef PROTO_LOCAL_gMsgQuery
extern MsgQuery gMsgQuery;
#endif
#endif

#endif
