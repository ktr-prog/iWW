#ifndef PROTO_PROTO_MAIN_UNK_02037734_H
#define PROTO_PROTO_MAIN_UNK_02037734_H


#include "types.h"
#ifdef __cplusplus
class CautionMsgString256;
class CautionMsgString64;
class CommCautionWindow;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Comm_SetShutdownErrorFlag
void Comm_SetShutdownErrorFlag();
#endif
#ifndef PROTO_LOCAL_CommCaution_SaveErrorCode
void CommCaution_SaveErrorCode();
#endif
#ifndef PROTO_LOCAL_CommCaution_CopyString
void CommCaution_CopyString(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommCaution_FormatErrorCode
u8 *CommCaution_FormatErrorCode();
#endif
#ifndef PROTO_LOCAL_CommCaution_ArePlanesHidden
u8 CommCaution_ArePlanesHidden();
#endif
#ifndef PROTO_LOCAL_CommCaution_IsShutDown
BOOL CommCaution_IsShutDown();
#endif
#ifndef PROTO_LOCAL_CommCaution_Init
void CommCaution_Init();
#endif
#ifndef PROTO_LOCAL_CommCaution_Release
void CommCaution_Release();
#endif
#ifndef PROTO_LOCAL_CommCaution_Update
void CommCaution_Update(u8 a);
#endif
#ifndef PROTO_LOCAL_CommCaution_Draw
void CommCaution_Draw();
#endif
#ifndef PROTO_LOCAL_CommCaution_UpdateBlendRegs
void CommCaution_UpdateBlendRegs();
#endif
#ifndef PROTO_LOCAL_CommCaution_LoadMessages
void CommCaution_LoadMessages();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sCommCautionErrorCode
extern u32 sCommCautionErrorCode;
#endif
#ifndef PROTO_LOCAL_sCommCautionWindow
extern CommCautionWindow sCommCautionWindow;
#endif
#ifndef PROTO_LOCAL_sCommCautionNumberGap
extern u8 sCommCautionNumberGap[4];
#endif
#ifndef PROTO_LOCAL_sCommCautionShowErrorCode
extern u8 sCommCautionShowErrorCode;
#endif
#ifndef PROTO_LOCAL_sCommCautionErrorCodeText
extern u8 sCommCautionErrorCodeText[0x20];
#endif
#ifndef PROTO_LOCAL_sCommCautionLagMsg
extern CautionMsgString256 sCommCautionLagMsg;
#endif
#ifndef PROTO_LOCAL_sCommCautionSecondsMsg
extern CautionMsgString64 sCommCautionSecondsMsg;
#endif
#ifndef PROTO_LOCAL_sCommCautionEndedMsg
extern CautionMsgString256 sCommCautionEndedMsg;
#endif
#endif

#endif
