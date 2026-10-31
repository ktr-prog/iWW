#ifndef PROTO_PROTO_OV004_UNK_OV004_0221E7A8_H
#define PROTO_PROTO_OV004_UNK_OV004_0221E7A8_H


#include "types.h"
#ifdef __cplusplus
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d4a4
extern u32 data_ov004_0224d4a4;
#endif
#ifndef PROTO_LOCAL_sRoomPlayerMsgFile
extern char sRoomPlayerMsgFile[16];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d4a8
extern u32 data_ov004_0224d4a8;
#endif
#ifndef PROTO_LOCAL_sFtrPullDist
extern s32 sFtrPullDist;
#endif
#ifndef PROTO_LOCAL_sSeatApproachDist
extern s32 sSeatApproachDist;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d4b0
extern u32 data_ov004_0224d4b0;
#endif
#ifndef PROTO_LOCAL_sRoomInteractDist
extern s32 sRoomInteractDist;
#endif
#ifndef PROTO_LOCAL_sRoomErrorMsgFile
extern char sRoomErrorMsgFile[16];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d4b4
extern u32 data_ov004_0224d4b4;
#endif
#ifndef PROTO_LOCAL_RoomObj_ActivateSe
void RoomObj_ActivateSe(void *a);
#endif
#ifndef PROTO_LOCAL_RoomObj_DeactivateSe
void RoomObj_DeactivateSe(void *a);
#endif
#ifndef PROTO_LOCAL_RoomObj_PlaySe
void RoomObj_PlaySe(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_RoomObj_PlaySeHeld
void RoomObj_PlaySeHeld(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TestLocalFlag0F
s32 PlayerActor_TestLocalFlag0F(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TestLocalFlag02
s32 PlayerActor_TestLocalFlag02(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalSetHeadwearHidden
s32 PlayerActor_LocalSetHeadwearHidden(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestBedApproach
s32 PlayerActor_LocalRequestBedApproach(const s32 *a, const s32 *b, const s16 *c, s32 d, s32 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestGetOutOfBed
s32 PlayerActor_LocalRequestGetOutOfBed(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestSeatApproach
s32 PlayerActor_LocalRequestSeatApproach(const s32 *a, const s32 *b, const s16 *c, const u8 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestStandUp
s32 PlayerActor_LocalRequestStandUp(s32 t);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestStorageOpen
s32 PlayerActor_LocalRequestStorageOpen(const s32 *a, const s32 *b, const s32 *c, const s16 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestStorageClose
s32 PlayerActor_LocalRequestStorageClose(const s32 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestLeaveRoom
s32 PlayerActor_LocalRequestLeaveRoom(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestAct37
s32 PlayerActor_LocalRequestAct37(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestHaircutStart
s32 PlayerActor_LocalRequestHaircutStart(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestPhonePickUp
s32 PlayerActor_LocalRequestPhonePickUp(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestPhoneHangUp
s32 PlayerActor_LocalRequestPhoneHangUp(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestSit
s32 PlayerActor_LocalRequestSit(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestAct12
s32 PlayerActor_LocalRequestAct12(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestDrinkCoffee
s32 PlayerActor_LocalRequestDrinkCoffee(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalPlayAnim98
BOOL PlayerActor_LocalPlayAnim98(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LieInBedSetArgs
void PlayerActor_LieInBedSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LieInBedSetWork
void PlayerActor_LieInBedSetWork(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetOutOfBedCheckSetArgs
void PlayerActor_GetOutOfBedCheckSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetGetOutOfBedCheck
void PlayerActor_NetGetOutOfBedCheck(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetOutOfBedSetArgs
void PlayerActor_GetOutOfBedSetArgs(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetOutOfBedSetNetData
void PlayerActor_GetOutOfBedSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetOutOfBedGetNetData
void PlayerActor_GetOutOfBedGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollCheckSetArgs
void PlayerActor_BedRollCheckSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollCheckSetWork
void PlayerActor_BedRollCheckSetWork(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollCheckSetNetData
void PlayerActor_BedRollCheckSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollCheckGetNetData
void PlayerActor_BedRollCheckGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollBlockedSetArgs
void PlayerActor_BedRollBlockedSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollBlockedSetNetData
void PlayerActor_BedRollBlockedSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollBlockedGetNetData
void PlayerActor_BedRollBlockedGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollSetArgs
void PlayerActor_BedRollSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollSetWork
void PlayerActor_BedRollSetWork(s32 *p, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollSetNetData
void PlayerActor_BedRollSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedRollGetNetData
void PlayerActor_BedRollGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedApproachSetNetData
void PlayerActor_BedApproachSetNetData(u8 *dst, s32 x, s32 z, s32 h, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BedApproachGetNetData
void PlayerActor_BedApproachGetNetData(u8 *src, s32 *x, s32 *z, s16 *h, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetIntoBedSetArgs
void PlayerActor_GetIntoBedSetArgs(void *out, u8 b, s32 x, s32 z, u8 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetIntoBedSetNetData
void PlayerActor_GetIntoBedSetNetData(u8 *dst, u32 k, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetIntoBedGetNetData
void PlayerActor_GetIntoBedGetNetData(u8 *src, u8 *out, s32 *x, s32 *z);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetAct12
void PlayerActor_NetAct12(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_PickUpItemSetArgs
void PlayerActor_PickUpItemSetArgs(void *out, s32 *in, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetPickUpItem
void PlayerActor_NetPickUpItem(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrGrabApproachSetNetData
void PlayerActor_FtrGrabApproachSetNetData(u8 *p, s32 x, s32 z, s16 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrGrabApproachGetNetData
void PlayerActor_FtrGrabApproachGetNetData(u8 *p, s32 *x, s32 *z, s16 *h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrHoldSetArgs
void PlayerActor_FtrHoldSetArgs(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrHoldSetWork
void PlayerActor_FtrHoldSetWork(u8 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrHoldSetNetData
void PlayerActor_FtrHoldSetNetData(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrHoldGetNetData
void PlayerActor_FtrHoldGetNetData(u8 *src, u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrRotateSetArgs
void PlayerActor_FtrRotateSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FtrRotateSetStickFlag
void PlayerActor_FtrRotateSetStickFlag(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetFtrRotate
void PlayerActor_NetFtrRotate(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetFtrPushMove
void PlayerActor_NetFtrPushMove(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetFtrPullMove
void PlayerActor_NetFtrPullMove(void);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SeatApproachSetNetData
void PlayerActor_SeatApproachSetNetData(u8 *self, s32 x, s32 z, s16 h, u8 d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SeatApproachGetNetData
void PlayerActor_SeatApproachGetNetData(u8 *self, s32 *x, s32 *z, s16 *h, u8 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownFrontSetNetData
void PlayerActor_SitDownFrontSetNetData(u8 *p, s32 x, s32 z, s16 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownFrontGetNetData
void PlayerActor_SitDownFrontGetNetData(u8 *p, s32 *x, s32 *z, s16 *h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownSide2SetNetData
void PlayerActor_SitDownSide2SetNetData(u8 *p, s32 x, s32 z, s16 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownSide2GetNetData
void PlayerActor_SitDownSide2GetNetData(u8 *p, s32 *x, s32 *z, s16 *h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownSide1SetNetData
void PlayerActor_SitDownSide1SetNetData(u8 *p, s32 x, s32 z, s16 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SitDownSide1GetNetData
void PlayerActor_SitDownSide1GetNetData(u8 *p, s32 *x, s32 *z, s16 *h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StandUpCheckSetArgs
void PlayerActor_StandUpCheckSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetStandUpCheck
void PlayerActor_NetStandUpCheck();
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageOpenSetArgs
void PlayerActor_StorageOpenSetArgs(void *r, u8 d, u32 a, u32 b, s16 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageOpenSetNetData
void PlayerActor_StorageOpenSetNetData(u8 *self, u8 b, s32 x, s32 y, s16 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageOpenGetNetData
void PlayerActor_StorageOpenGetNetData(u8 *self, u8 *o1, s32 *o2, s32 *o3, u16 *o4);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageHoldSetArgs
void PlayerActor_StorageHoldSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageHoldSetWork
void PlayerActor_StorageHoldSetWork(u32 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageHoldSetNetData
void PlayerActor_StorageHoldSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageHoldGetNetData
void PlayerActor_StorageHoldGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageCloseSetArgs
void PlayerActor_StorageCloseSetArgs(u32 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageCloseSetWork
void PlayerActor_StorageCloseSetWork(u32 *a, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageCloseSetNetData
void PlayerActor_StorageCloseSetNetData(u8 *a, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StorageCloseGetNetData
void PlayerActor_StorageCloseGetNetData(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LeaveRoomSetArgs
void PlayerActor_LeaveRoomSetArgs(void *p, s32 a, s16 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetDrinkCoffee
void PlayerActor_NetDrinkCoffee();
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorWalkInSetNetData
void PlayerActor_DoorWalkInSetNetData(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorWalkInGetNetData
void PlayerActor_DoorWalkInGetNetData(u8 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorWalkOutSetNetData
void PlayerActor_DoorWalkOutSetNetData(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorWalkOutGetNetData
void PlayerActor_DoorWalkOutGetNetData(u8 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ExitWalkOutSetNetData
void PlayerActor_ExitWalkOutSetNetData(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ExitWalkOutGetNetData
void PlayerActor_ExitWalkOutGetNetData(u8 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ExitWalkInSetNetData
void PlayerActor_ExitWalkInSetNetData(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ExitWalkInGetNetData
void PlayerActor_ExitWalkInGetNetData(u8 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetSendHair
void PlayerActor_NetSendHair(void *unused, s32 a, s32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_RoomObj_LoadResources
void RoomObj_LoadResources(char *a, char *b, AnimModel *m, RoomObjRes *aa, RoomObjTexHandle *bb);
#endif
#ifndef PROTO_LOCAL_RoomObj_LoadResourcesByName
void RoomObj_LoadResourcesByName(char *name, AnimModel *m, RoomObjRes *a, RoomObjTexHandle *b);
#endif
#ifndef PROTO_LOCAL_RoomObj_ReleaseResources
void RoomObj_ReleaseResources(RoomObjRes *a, RoomObjTexHandle *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestAct36
s32 PlayerActor_LocalRequestAct36(u16 *a, u32 *b, u8 *c, u32 *d, Character *e);
#endif
}
#endif

#endif
