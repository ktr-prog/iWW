#ifndef PROTO_PROTO_OV004_UNK_OV004_0222BED0_H
#define PROTO_PROTO_OV004_UNK_OV004_0222BED0_H


#include "types.h"
#include "sys/ProcProfile.h"
struct RoomItemDropList;
struct Unk_ov004_0222bf34_P2;
#ifndef __cplusplus
typedef struct RoomItemDropList RoomItemDropList;
typedef struct Unk_ov004_0222bf34_P2 Unk_ov004_0222bf34_P2;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "room/RoomItemDrop.h"
#include "town/BlockMap.h"
class RoomItemIcons;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Room_SetItemAtUnit
void Room_SetItemAtUnit(s32 x, s32 y, u16 v, s32 z);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sRoomItemIconsProfile
extern ProcProfile sRoomItemIconsProfile;
#endif
#ifndef PROTO_LOCAL_sRoomItemIcons
extern RoomItemIcons *sRoomItemIcons;
#endif
#ifndef PROTO_LOCAL_sRoomItemDrops
extern RoomItemDropList sRoomItemDrops;
#endif
#ifndef PROTO_LOCAL_RoomItemIcons_Create
RoomItemIcons *RoomItemIcons_Create();
#endif
#ifndef PROTO_LOCAL_ItemDrop_StartFromLocalPlayer
BOOL ItemDrop_StartFromLocalPlayer(u16 *p, VecFx32Copy *v);
#endif
#ifndef PROTO_LOCAL_RoomItemIcons_DrawIcon
void RoomItemIcons_DrawIcon(u32 id, VecFx32Copy *a, VecFx32Copy *b, s32 c, s16 d, s16 e);
#endif
#ifndef PROTO_LOCAL_RoomItemIcons_DrawItem
void RoomItemIcons_DrawItem(u32 id, VecFx32Copy *a, VecFx32Copy *b, s32 c, s16 d, s16 e);
#endif
#ifndef PROTO_LOCAL_ItemDrop_Settle
void ItemDrop_Settle(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDrop_Init
void ItemDrop_Init(RoomItemDrop *e, s32 idx, Unk_ov004_0222bf34_P2 *p, VecFx32Copy *a, VecFx32Copy *b, s32 flag, u32 idv, BlockMap *unused, s32 s16v, u32 u8v);
#endif
#ifndef PROTO_LOCAL_ItemDrop_Clear
void ItemDrop_Clear(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDrop_SetTrajectory
void ItemDrop_SetTrajectory(RoomItemDrop *e, Unk_ov004_0222bf34_P2 *p, VecFx32Copy *from, VecFx32Copy *to, u32 v32);
#endif
#ifndef PROTO_LOCAL_ItemDrop_Update
void ItemDrop_Update(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDropList_Init
void ItemDropList_Init(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDropList_Update
void ItemDropList_Update(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDropList_Draw
void ItemDropList_Draw(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDropList_Release
void ItemDropList_Release(RoomItemDrop *e);
#endif
#ifndef PROTO_LOCAL_ItemDropList_Add
s32 ItemDropList_Add(void *base, s32 idx, Unk_ov004_0222bf34_P2 *p, VecFx32Copy *a, VecFx32Copy *b, s32 flag, u32 idv, s32 s16v, u32 u8v);
#endif
#ifndef PROTO_LOCAL_ItemDrop_StartToUnit
s32 ItemDrop_StartToUnit(s32 idx, u32 v, Unk_ov004_0222bf34_P2 *p, VecFx32Copy *b, u32 f);
#endif
#ifndef PROTO_LOCAL_ItemDrop_Start
s32 ItemDrop_Start(s32 idx, u32 v, VecFx32Copy *a, VecFx32Copy *b, u32 f);
#endif
}
#endif

#endif
