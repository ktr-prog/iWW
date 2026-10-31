#ifndef PROTO_PROTO_OV001_UNK_OV001_02220AD8_H
#define PROTO_PROTO_OV001_UNK_OV001_02220AD8_H


#include "types.h"
#ifdef __cplusplus
#include "net/WfcMoveMbWork.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_SetWork
void WfcMoveMb_SetWork(void *p);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_Init
void WfcMoveMb_Init(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_AcceptChild
void WfcMoveMb_AcceptChild(u32 n);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_KickChild
void WfcMoveMb_KickChild(u32 n);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_StartDownload
void WfcMoveMb_StartDownload(u32 id);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_StartDownloadAll
void WfcMoveMb_StartDownloadAll();
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_IsAllBootable
u32 WfcMoveMb_IsAllBootable();
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_StartRebootAll
void WfcMoveMb_StartRebootAll();
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_Cancel
void WfcMoveMb_Cancel();
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_ParentStateCallback
void WfcMoveMb_ParentStateCallback(u32 id, u32 cmd, u8 *data);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_SetState
void WfcMoveMb_SetState(u32 v);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_GetState
u32 WfcMoveMb_GetState();
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_GetChildMask
u32 WfcMoveMb_GetChildMask(u32 i);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_GetChildState
u32 WfcMoveMb_GetChildState(u32 id);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_GetChildInfo
u8 *WfcMoveMb_GetChildInfo(u32 id);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_FindAidByMac
u32 WfcMoveMb_FindAidByMac(u8 *mac);
#endif
#ifndef PROTO_LOCAL_sWfcMoveMbMaskPtrs
extern u16 *sWfcMoveMbMaskPtrs[6];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WfcMoveMb_StartParent
void WfcMoveMb_StartParent(MBGameRegistry *a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcMoveMb_RegisterFile
s32 WfcMoveMb_RegisterFile(MBGameRegistry *p);
#endif
#ifndef PROTO_LOCAL_sWfcMoveMb
extern WfcMoveMbWork *sWfcMoveMb;
#endif
}
#endif

#endif
