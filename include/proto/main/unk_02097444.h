#ifndef PROTO_PROTO_MAIN_UNK_02097444_H
#define PROTO_PROTO_MAIN_UNK_02097444_H


#include "types.h"
#ifdef __cplusplus
#include "player/PlayerInventory.h"
class GuestPlayerArray;
class PlayerData;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerInventory_GetBellsRoom
s32 PlayerInventory_GetBellsRoom(u8 *p, s32 mode, s32 arg);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_FindSmallestBag
s32 PlayerInventory_FindSmallestBag(u8 *p, s32 mode);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_FindBagSlot
s32 PlayerInventory_FindBagSlot(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_StoreExcessInBags
s32 PlayerInventory_StoreExcessInBags(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_PayWithBags
s32 PlayerInventory_PayWithBags(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_CanAddBells
BOOL PlayerInventory_CanAddBells(u8 *p, s32 v, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerInventory_AddBells
void PlayerInventory_AddBells(u8 *p, s32 v, s32 mode);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetLetterStorage
u8 *PlayerData_GetLetterStorage(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetMailbox
u8 *PlayerData_GetMailbox(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetDresser
u8 *PlayerData_GetDresser(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetLastWifiMailId
s32 PlayerData_GetLastWifiMailId(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_SetLastWifiMailId
void PlayerData_SetLastWifiMailId(void *p, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_Construct
void *PlayerDataArray_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_Destruct
void *PlayerDataArray_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_IsResidentIndex
s32 PlayerData_IsResidentIndex(u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_IsUsed
s32 PlayerDataArray_IsUsed(u8 *base, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_CountUsed
u32 PlayerDataArray_CountUsed(u8 *base);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_GetById
u8 *PlayerDataArray_GetById(u8 *base, u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetResident
u8 *PlayerData_GetResident(u8 *base, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_GetRandomOther
u8 *PlayerDataArray_GetRandomOther(u8 *base, u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_ResetAll
void PlayerDataArray_ResetAll(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_FindUnused
s32 PlayerDataArray_FindUnused(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_FindById
s32 PlayerDataArray_FindById(u8 *base, u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerDataArray_CreateResident
u8 *PlayerDataArray_CreateResident(u8 *base, void *name, s32 a2, u32 idx);
#endif
#ifndef PROTO_LOCAL_GuestPlayers_ResetAll
void GuestPlayers_ResetAll();
#endif
#ifndef PROTO_LOCAL_PlayerData_IsGuestIndex
s32 PlayerData_IsGuestIndex(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetGuestSlot
s32 PlayerData_GetGuestSlot(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetCurrentIndex
u32 PlayerData_GetCurrentIndex();
#endif
#ifndef PROTO_LOCAL_PlayerData_IsUsedByIndex
s32 PlayerData_IsUsedByIndex(s32 idx);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerInventory_SetWallet
void PlayerInventory_SetWallet(PlayerInventory *p, s32 v, s32 mode);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetFutureLetter
u8 *PlayerData_GetFutureLetter(PlayerData *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetMotherLetterState
u8 *PlayerData_GetMotherLetterState(PlayerData *p);
#endif
#ifndef PROTO_LOCAL_GuestPlayers_Get
PlayerData *GuestPlayers_Get();
#endif
#ifndef PROTO_LOCAL_GuestPlayers_Reset
void GuestPlayers_Reset(PlayerData *p);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetBySessionSlot
PlayerData *PlayerData_GetBySessionSlot(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerData_GetCurrent
PlayerData *PlayerData_GetCurrent();
#endif
#ifndef PROTO_LOCAL_PlayerData_Get
PlayerData *PlayerData_Get(s32 idx);
#endif
}
#ifndef PROTO_LOCAL_gGuestPlayers
extern GuestPlayerArray gGuestPlayers;
#endif
#endif

#endif
