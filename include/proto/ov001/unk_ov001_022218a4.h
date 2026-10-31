#ifndef PROTO_PROTO_OV001_UNK_OV001_022218A4_H
#define PROTO_PROTO_OV001_UNK_OV001_022218A4_H


#include "types.h"
#include "nitro/wm.h"
struct WfcMoveWhWork;
#ifndef __cplusplus
typedef struct WfcMoveWhWork WfcMoveWhWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_ChangeSysState
void WfcMoveWh_ChangeSysState(s32 n);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_SetError
void WfcMoveWh_SetError(u32 v);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInSetParentParam
s32 WfcMoveWh_StateInSetParentParam();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutSetParentParam
void WfcMoveWh_StateOutSetParentParam(u16 *p);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInSetWepKey
s32 WfcMoveWh_StateInSetWepKey();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutSetWepKey
void WfcMoveWh_StateOutSetWepKey(u16 *p);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInStartParent
s32 WfcMoveWh_StateInStartParent();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutStartParent
void WfcMoveWh_StateOutStartParent(u16 *p);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInStartParentMp
s32 WfcMoveWh_StateInStartParentMp();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutStartParentMp
void WfcMoveWh_StateOutStartParentMp(u16 *p);
#endif
#ifndef PROTO_LOCAL_DWCi_MOV_WH_StateInStartParentKeyShare
s32 DWCi_MOV_WH_StateInStartParentKeyShare();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_EndKeySharing
s32 WfcMoveWh_EndKeySharing();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInEndParentMp
s32 WfcMoveWh_StateInEndParentMp();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutEndParentMp
void WfcMoveWh_StateOutEndParentMp(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_DWCi_MOV_WH_StateInEndParent
s32 DWCi_MOV_WH_StateInEndParent();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutEndParent
void WfcMoveWh_StateOutEndParent(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInEndChildKeyShare
s32 WfcMoveWh_StateInEndChildKeyShare();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInEndChildMp
s32 WfcMoveWh_StateInEndChildMp();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutEndChildMp
void WfcMoveWh_StateOutEndChildMp(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInEndChild
s32 WfcMoveWh_StateInEndChild();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutEndChild
void WfcMoveWh_StateOutEndChild(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInReset
s32 WfcMoveWh_StateInReset();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutReset
void WfcMoveWh_StateOutReset(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutEnd
void WfcMoveWh_StateOutEnd(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_SetGgid
void WfcMoveWh_SetGgid(s32 x);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_GetConnectedBitmap
u16 WfcMoveWh_GetConnectedBitmap();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_GetSysState
s32 WfcMoveWh_GetSysState();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StartMeasureChannel
s32 WfcMoveWh_StartMeasureChannel();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_MeasureNextChannel
u16 WfcMoveWh_MeasureNextChannel(u16 x);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutMeasureChannel
void WfcMoveWh_StateOutMeasureChannel(WMMeasureChannelCallback *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInMeasureChannel
s32 WfcMoveWh_StateInMeasureChannel(void *cb, s32 x);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_DecideChannel
u16 WfcMoveWh_DecideChannel();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_PickRandomChannel
s16 WfcMoveWh_PickRandomChannel(u16 mask);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_Initialize
BOOL WfcMoveWh_Initialize();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_IndicationCallback
void WfcMoveWh_IndicationCallback(WMMsg *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateInInitialize
s32 WfcMoveWh_StateInInitialize();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_StateOutInitialize
void WfcMoveWh_StateOutInitialize(u16 *p);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_ParentConnect
s32 WfcMoveWh_ParentConnect(s32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_SetJudgeCallback
void WfcMoveWh_SetJudgeCallback(void *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_GetSharedData
void *WfcMoveWh_GetSharedData(s32 a);
#endif
#ifndef PROTO_LOCAL_DWCi_MOV_WH_StepDataSharing
s32 DWCi_MOV_WH_StepDataSharing(void *a);
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_Reset
void WfcMoveWh_Reset();
#endif
#ifndef PROTO_LOCAL_DWCi_MOV_WH_Finalize
void DWCi_MOV_WH_Finalize();
#endif
#ifndef PROTO_LOCAL_WfcMoveWh_End
s32 WfcMoveWh_End();
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b4ec
extern char data_ov001_0222b4ec[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b508
extern char data_ov001_0222b508[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b524
extern char data_ov001_0222b524[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b540
extern char data_ov001_0222b540[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b55c
extern char data_ov001_0222b55c[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b57c
extern char data_ov001_0222b57c[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b59c
extern char data_ov001_0222b59c[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b5bc
extern char data_ov001_0222b5bc[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b5e0
extern char data_ov001_0222b5e0[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b604
extern char data_ov001_0222b604[];
#endif
#ifndef PROTO_LOCAL_sWfcMoveWhSysStateNames
extern char *sWfcMoveWhSysStateNames[10];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WfcMoveWh_SetWork
void WfcMoveWh_SetWork(WfcMoveWhWork *p);
#endif
#ifndef PROTO_LOCAL_sWfcMoveWh
extern WfcMoveWhWork *sWfcMoveWh;
#endif
}
#endif

#endif
