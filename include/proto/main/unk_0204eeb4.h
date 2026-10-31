#ifndef PROTO_PROTO_MAIN_UNK_0204EEB4_H
#define PROTO_PROTO_MAIN_UNK_0204EEB4_H


#include "types.h"
#include "sys/OverlaySlot.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FishTable_GetHourSlot
u32 FishTable_GetHourSlot(u32 r);
#endif
#ifndef PROTO_LOCAL_FishTable_IsLateMonth
BOOL FishTable_IsLateMonth(u8 v);
#endif
#ifndef PROTO_LOCAL_FishTable_GetPeriod
u8 FishTable_GetPeriod(u8 x);
#endif
#ifndef PROTO_LOCAL_Fish_GetWaterKind
s32 Fish_GetWaterKind(s32 r);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_GetInfo
void OverlayMgr_GetInfo(void *p, u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_LoadOverlay
void OverlayMgr_LoadOverlay(u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_UnloadOverlay
void OverlayMgr_UnloadOverlay(u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_LoadSlot
void OverlayMgr_LoadSlot(OverlaySlot *e, u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_UnloadSlot
void OverlayMgr_UnloadSlot(OverlaySlot *e);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_Acquire
void OverlayMgr_Acquire(u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_Release
void OverlayMgr_Release(u32 id);
#endif
#ifndef PROTO_LOCAL_OverlayMgr_Init
void OverlayMgr_Init();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sOverlaySlots
extern OverlaySlot sOverlaySlots[12];
#endif
#endif

#endif
