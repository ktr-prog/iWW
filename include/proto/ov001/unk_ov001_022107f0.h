#ifndef PROTO_PROTO_OV001_UNK_OV001_022107F0_H
#define PROTO_PROTO_OV001_UNK_OV001_022107F0_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTransferConfirmAccepted
extern u8 sWfcTransferConfirmAccepted;
#endif
#ifndef PROTO_LOCAL_sWfcTransferConfirmError
extern u8 sWfcTransferConfirmError;
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_Enter
void WfcTransferConfirm_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_LoadBg
void WfcTransferConfirm_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_FadeIn
void WfcTransferConfirm_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_OpenDialog
void WfcTransferConfirm_OpenDialog();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_WaitDialogOpen
void WfcTransferConfirm_WaitDialogOpen();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_HandleResult
void WfcTransferConfirm_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_Nop1
void WfcTransferConfirm_Nop1();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_Nop2
void WfcTransferConfirm_Nop2();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_WaitDialogClosed
void WfcTransferConfirm_WaitDialogClosed();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_StartSendOrEnd
void WfcTransferConfirm_StartSendOrEnd();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_Exit
void WfcTransferConfirm_Exit();
#endif
#ifndef PROTO_LOCAL_WfcTransferConfirm_OnTransferError
void WfcTransferConfirm_OnTransferError(u32 event);
#endif
#ifdef __cplusplus
}
#endif

#endif
