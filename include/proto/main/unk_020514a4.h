#ifndef PROTO_PROTO_MAIN_UNK_020514A4_H
#define PROTO_PROTO_MAIN_UNK_020514A4_H


#include "types.h"
struct Unk_0205242c_Item;
#ifndef __cplusplus
typedef struct Unk_0205242c_Item Unk_0205242c_Item;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "room/RoomFtrState.h"
class FtrActor;
class FtrPlaceRecord;
class SpotReservationTable;
class Unk_02051fcc_W;
class Unk_020520a8_W;
class Unk_02052134_W;
class Unk_0205218c_B;
class Unk_0205242c_Self;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_RoomFtrState_ResetAll
void RoomFtrState_ResetAll();
#endif
#ifndef PROTO_LOCAL_RoomFtrState_ResetScene
BOOL RoomFtrState_ResetScene(u32 v);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_ResetVillagerHouse
BOOL RoomFtrState_ResetVillagerHouse(u32 idx);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_GetSwitch
s32 RoomFtrState_GetSwitch(s32 a, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_SetSwitch
void RoomFtrState_SetSwitch(s32 a, s32 b, s32 c, u8 d, u8 e);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_GetGyroidBeat
s32 RoomFtrState_GetGyroidBeat(s32 a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_SetGyroidBeat
s32 RoomFtrState_SetGyroidBeat(s32 a, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_RoomFtrState_RemoveGyroidBeat
s32 RoomFtrState_RemoveGyroidBeat(s32 a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnStateRecord
void FtrSync_OnStateRecord(u32 *pp);
#endif
#ifndef PROTO_LOCAL_FtrSync_ToggleGyroidAt
void FtrSync_ToggleGyroidAt(u8 a, s32 b, s32 c, u8 d, u8 e);
#endif
#ifndef PROTO_LOCAL_SpotSync_OnReserveRequest
void SpotSync_OnReserveRequest(u8 *p, s32 q);
#endif
#ifndef PROTO_LOCAL_SpotSync_OnReserveReply
void SpotSync_OnReserveReply(s32 x);
#endif
#ifndef PROTO_LOCAL_SpotSync_OnRelease
s32 SpotSync_OnRelease(s32 x);
#endif
#ifndef PROTO_LOCAL_FtrSync_SendState
s32 FtrSync_SendState(u32 a, u32 b, u32 c, u32 d, u8 e, u8 f, s32 g);
#endif
#ifndef PROTO_LOCAL_FtrSync_ChangeActAt
s32 FtrSync_ChangeActAt(s32 a, s32 b, s32 c, s32 d, u8 e, u8 f, u8 g);
#endif
#ifndef PROTO_LOCAL_FtrSync_RequestActAt
s32 FtrSync_RequestActAt(s32 a, s32 b, s32 c, s32 d, u8 e, u8 f, u8 g);
#endif
#ifndef PROTO_LOCAL_FtrSync_PlaceFurniture
void FtrSync_PlaceFurniture(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, u16 *h, u8 i);
#endif
#ifndef PROTO_LOCAL_FtrSync_RemoveFurniture
void FtrSync_RemoveFurniture(s32 a, s32 b, s32 c, s32 d, s32 e, u16 *f, s32 g, u8 h);
#endif
#ifndef PROTO_LOCAL_FtrSync_SetTopItem
void FtrSync_SetTopItem(s32 a, s32 b, s32 c, u16 *d, u8 f);
#endif
#ifndef PROTO_LOCAL_FtrSync_SendRoomLight
void FtrSync_SendRoomLight(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_FtrSync_ApplyRoomLight
void FtrSync_ApplyRoomLight(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrSync_SetRoomLight
void FtrSync_SetRoomLight(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrSync_RequestToggleGyroidAt
void FtrSync_RequestToggleGyroidAt(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_SpotSync_RequestReserve
void SpotSync_RequestReserve(s32 *p);
#endif
#ifndef PROTO_LOCAL_SpotSync_GetReserveResult
u32 SpotSync_GetReserveResult();
#endif
#ifndef PROTO_LOCAL_SpotSync_RequestStandUpSpot
void SpotSync_RequestStandUpSpot(s32 *p);
#endif
#ifndef PROTO_LOCAL_SpotSync_GetStandUpSpotResult
u32 SpotSync_GetStandUpSpotResult();
#endif
#ifndef PROTO_LOCAL_SpotSync_Release
void SpotSync_Release(s32 aid);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_RoomFtrState_GetForScene
RoomFtrState *RoomFtrState_GetForScene(u32 id);
#endif
#ifndef PROTO_LOCAL_FtrFootprint_Init
Unk_0205242c_Self *FtrFootprint_Init(Unk_0205242c_Self *p, u16 *q);
#endif
#ifndef PROTO_LOCAL_FtrFootprint_GetTileCount
s32 FtrFootprint_GetTileCount(Unk_0205242c_Self *p);
#endif
#ifndef PROTO_LOCAL_FtrFootprint_GetTileOffset
Unk_0205242c_Item *FtrFootprint_GetTileOffset(Unk_0205242c_Self *p, u32 idx);
#endif
#ifndef PROTO_LOCAL_FtrSync_ApplyState
s32 FtrSync_ApplyState(u8 a, s32 b, s32 c, s32 d, u8 e, bool f, bool g, bool h, volatile u8 i);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnRoomLightRecord
void FtrSync_OnRoomLightRecord(Unk_0205218c_B *p);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnRemoveRecord
void FtrSync_OnRemoveRecord(s32 a, Unk_02052134_W *w);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnPlaceRecord
void FtrSync_OnPlaceRecord(s32 a, FtrPlaceRecord *w);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnTopItemRecord
void FtrSync_OnTopItemRecord(s32 a, Unk_020520a8_W *w);
#endif
#ifndef PROTO_LOCAL_FtrSync_OnToggleRecord
void FtrSync_OnToggleRecord(Unk_02051fcc_W *p);
#endif
#ifndef PROTO_LOCAL_FtrSync_ChangeAct
s32 FtrSync_ChangeAct(FtrActor *a, s32 b, u8 c, u8 d);
#endif
#ifndef PROTO_LOCAL_FtrSync_RequestAct
s32 FtrSync_RequestAct(FtrActor *a, s32 b, u8 c, u8 d);
#endif
#ifndef PROTO_LOCAL_FtrSync_RequestToggleGyroid
void FtrSync_RequestToggleGyroid(s32 a, VecFx32 *b, s32 c);
#endif
}
#ifndef PROTO_LOCAL_sVillagerHouseFtrStates
extern RoomFtrState sVillagerHouseFtrStates[8];
#endif
#ifndef PROTO_LOCAL_sNookShopFtrStates
extern RoomFtrState sNookShopFtrStates[6];
#endif
#ifndef PROTO_LOCAL_sScene10FtrState
extern RoomFtrState sScene10FtrState;
#endif
#ifndef PROTO_LOCAL_sSpotReservations
extern SpotReservationTable sSpotReservations;
#endif
#ifndef PROTO_LOCAL_data_021c4e34
extern Unk_0205242c_Item data_021c4e34;
#endif
#ifndef PROTO_LOCAL_data_021c4e3c
extern Unk_0205242c_Item data_021c4e3c[2];
#endif
#ifndef PROTO_LOCAL_data_021c4e44
extern Unk_0205242c_Item data_021c4e44[2];
#endif
#ifndef PROTO_LOCAL_data_021c4e54
extern Unk_0205242c_Item data_021c4e54[2];
#endif
#ifndef PROTO_LOCAL_sSpotReserveResult
extern s32 sSpotReserveResult;
#endif
#ifndef PROTO_LOCAL_data_021c4e4c
extern Unk_0205242c_Item data_021c4e4c[2];
#endif
#ifndef PROTO_LOCAL_data_021c4e8c
extern Unk_0205242c_Item data_021c4e8c[4];
#endif
#endif

#endif
