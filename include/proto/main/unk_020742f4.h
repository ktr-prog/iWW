#ifndef PROTO_PROTO_MAIN_UNK_020742F4_H
#define PROTO_PROTO_MAIN_UNK_020742F4_H


#include "types.h"
#include "types64.h"
struct OverlayHandleView;
#ifndef __cplusplus
typedef struct OverlayHandleView OverlayHandleView;
#endif
#ifdef __cplusplus
#include "net/FriendEntry.h"
#include "save/BbsPost.h"
#include "sys/OverlayHandle.h"
#include "talk/MsgString.h"
class ChatBalloon;
class MsgString193;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CommVillager_PackHeader
void CommVillager_PackHeader(u8 *p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackHeader
void CommVillager_UnpackHeader(s32 *a, s32 *b, u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerMemoryInit
void CommSend_VillagerMemoryInit(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_MemoryInit
void VillagerSync_MemoryInit(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerMemorySetPlayer
void CommSend_VillagerMemorySetPlayer(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_MemorySetPlayer
void VillagerSync_MemorySetPlayer(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerImpression
void CommSend_VillagerImpression(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Impression
void VillagerSync_Impression(void *villager, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerFriendship
void CommSend_VillagerFriendship(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Friendship
void VillagerSync_Friendship(void *villager, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommVillager_PackReceivedItem
void CommVillager_PackReceivedItem(u8 *out, s32 a, s32 b, u16 *c);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackReceivedItem
void CommVillager_UnpackReceivedItem(s32 *o0, s32 *o1, u16 *o2, u8 *src);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerReceivedItem
void CommSend_VillagerReceivedItem(u32 a, u32 b, u16 *c);
#endif
#ifndef PROTO_LOCAL_VillagerSync_ReceivedItem
void VillagerSync_ReceivedItem(void *villager, u32 b, u16 *c);
#endif
#ifndef PROTO_LOCAL_CommVillager_PackAct3C
void CommVillager_PackAct3C(u8 *out, s32 a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackAct3C
void CommVillager_UnpackAct3C(s32 *o0, u8 *o1, u8 *o2, u8 *src);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerAct3C
void CommSend_VillagerAct3C(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C
void VillagerSync_Act3C(void *villager, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C00
void VillagerSync_Act3C00(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C01
void VillagerSync_Act3C01(void *villager);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C02
void VillagerSync_Act3C02(void *villager);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C03
void VillagerSync_Act3C03(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C04
void VillagerSync_Act3C04(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3C05
void VillagerSync_Act3C05(void *villager, u32 b);
#endif
#ifndef PROTO_LOCAL_CommVillager_PackAct3D
void CommVillager_PackAct3D(u8 *out, s32 a, u32 b, u16 *c, s32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackAct3D
void CommVillager_UnpackAct3D(s32 *o0, u8 *o1, u16 *o2, s32 *o3, u8 *o4, u8 *src);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerAct3D
void CommSend_VillagerAct3D(u32 a, u32 b, u16 *c, u32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3D
void VillagerSync_Act3D(void *villager, u32 b, u16 *c, u32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerAct3F
void CommSend_VillagerAct3F(u32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Act3F
void VillagerSync_Act3F(void *villager, u16 *b);
#endif
#ifndef PROTO_LOCAL_CommVillager_PackItem
void CommVillager_PackItem(u8 *out, s32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackItem
void CommVillager_UnpackItem(s32 *out, u16 *dst, u8 *src);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerShirt
void CommSend_VillagerShirt(u32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Shirt
void VillagerSync_Shirt(void *villager, u16 *b);
#endif
#ifndef PROTO_LOCAL_CommVillager_PackItems
void CommVillager_PackItems(u8 *out, s32 a, u16 *src);
#endif
#ifndef PROTO_LOCAL_CommVillager_UnpackItems
void CommVillager_UnpackItems(s32 *out, u16 *dst, u8 *src);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerItems
void CommSend_VillagerItems(u32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_VillagerSync_Items
void VillagerSync_Items(void *villager, u16 *b);
#endif
#ifndef PROTO_LOCAL_Bbs_PostMsgDated
void Bbs_PostMsgDated(u32 a, const char *b, u32 c, u32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_Bbs_PostMsgToday
void Bbs_PostMsgToday(u32 a, const char *b);
#endif
#ifndef PROTO_LOCAL_Bbs_AddPost
void Bbs_AddPost(void *dst);
#endif
#ifndef PROTO_LOCAL_Bbs_GetPostCount
u8 Bbs_GetPostCount(void);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_Copy
void *DwcFriendData_Copy(void *p, void *q);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_Clear
void DwcFriendData_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_IsValid
BOOL DwcFriendData_IsValid(void *p);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_IsFriendKey
BOOL DwcFriendData_IsFriendKey(void *p);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_FromCodeDigits
BOOL DwcFriendData_FromCodeDigits(void *out, u8 *data, void *userData);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_ToCodeDigits
BOOL DwcFriendData_ToCodeDigits(void *friendData, u8 *buf);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_IsNotFriendKey
BOOL DwcFriendData_IsNotFriendKey(void *p);
#endif
#ifndef PROTO_LOCAL_DwcFriendData_GetBytes
void *DwcFriendData_GetBytes(void *p);
#endif
#ifndef PROTO_LOCAL_FriendList_Construct
void *FriendList_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_FriendList_Destruct
void *FriendList_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_FriendList_SetChecksum
void FriendList_SetChecksum(u8 *p, u16 v);
#endif
#ifndef PROTO_LOCAL_FriendList_GetChecksum
u16 FriendList_GetChecksum(u8 *p);
#endif
#ifndef PROTO_LOCAL_FriendEntry_Construct
void *FriendEntry_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_FriendEntry_Destruct
void *FriendEntry_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_FriendEntry_Copy
void *FriendEntry_Copy(void *p, void *q);
#endif
#ifndef PROTO_LOCAL_FriendEntry_Clear
void FriendEntry_Clear(void *pp);
#endif
#ifndef PROTO_LOCAL_FriendEntry_GetFriendData
void *FriendEntry_GetFriendData(void *p);
#endif
#ifndef PROTO_LOCAL_FriendEntry_GetPlayerName
u8 *FriendEntry_GetPlayerName(u8 *p);
#endif
#ifndef PROTO_LOCAL_FriendEntry_GetTownName
u8 *FriendEntry_GetTownName(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_Construct
u8 *PlayerWifiData_Construct(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_Destruct
u8 *PlayerWifiData_Destruct(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_Create
void PlayerWifiData_Create(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_GetFriendCode
s64 PlayerWifiData_GetFriendCode(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_HasUserId
s32 PlayerWifiData_HasUserId(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_IsConfigValid
s32 PlayerWifiData_IsConfigValid(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_GetDwcUserData
void *PlayerWifiData_GetDwcUserData(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_GetOwnFriendData
u8 *PlayerWifiData_GetOwnFriendData(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_SetChecksum
void PlayerWifiData_SetChecksum(u8 *p, u16 v);
#endif
#ifndef PROTO_LOCAL_PlayerWifiData_GetChecksum
u16 PlayerWifiData_GetChecksum(u8 *p);
#endif
#ifndef PROTO_LOCAL_Comm_AidToPeerIndex
s32 Comm_AidToPeerIndex(s32 x);
#endif
#ifndef PROTO_LOCAL_CommPacket_SetAckHeader
void CommPacket_SetAckHeader(u8 *p, s32 a);
#endif
#ifndef PROTO_LOCAL_CommPacket_SetHeader
void CommPacket_SetHeader(u8 *p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommPacket_IsControl
BOOL CommPacket_IsControl(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommPacket_GetAck
u32 CommPacket_GetAck(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommPacket_GetType
u32 CommPacket_GetType(u8 *p);
#endif
#ifndef PROTO_LOCAL_NetHeap_Alloc
void *NetHeap_Alloc(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NetHeap_Free
void NetHeap_Free(void *a);
#endif
#ifndef PROTO_LOCAL_Comm_HasSendCredit
BOOL Comm_HasSendCredit(u32 mask);
#endif
#ifndef PROTO_LOCAL_Comm_HasSendCreditAll
BOOL Comm_HasSendCreditAll(void);
#endif
#ifndef PROTO_LOCAL_Comm_IsWifi
BOOL Comm_IsWifi(void);
#endif
#ifndef PROTO_LOCAL_CommRecord_PackSource
void CommRecord_PackSource(u8 *p, s32 v, s32 w);
#endif
#ifndef PROTO_LOCAL_CommRecord_UnpackSource
void CommRecord_UnpackSource(u8 *p, u8 *a, u8 *out);
#endif
#ifndef PROTO_LOCAL_NetBuf_Pack20
void NetBuf_Pack20(u8 *p, s32 v, u8 hi);
#endif
#ifndef PROTO_LOCAL_NetBuf_Unpack20
void NetBuf_Unpack20(u8 *p, u32 *out, u8 *out2);
#endif
#ifndef PROTO_LOCAL_NetBuf_PackPair20
void NetBuf_PackPair20(u8 *p, s32 v, s32 x);
#endif
#ifndef PROTO_LOCAL_NetBuf_UnpackPair20
void NetBuf_UnpackPair20(u8 *p, u32 *out, u32 *x);
#endif
#ifndef PROTO_LOCAL_NetBuf_PackTriple20
void NetBuf_PackTriple20(u8 *p, s32 a, s32 x, s32 y, u8 z);
#endif
#ifndef PROTO_LOCAL_NetBuf_UnpackTriple20
void NetBuf_UnpackTriple20(u8 *p, u32 *out, s32 *x, u32 *y, u8 *z);
#endif
#ifndef PROTO_LOCAL_NetBuf_WriteS16B
void NetBuf_WriteS16B(void *dst, s16 v);
#endif
#ifndef PROTO_LOCAL_NetBuf_ReadS16B
s16 NetBuf_ReadS16B(void *src);
#endif
#ifndef PROTO_LOCAL_NetBuf_WriteS16
void NetBuf_WriteS16(void *dst, s16 v);
#endif
#ifndef PROTO_LOCAL_NetBuf_ReadS16
s16 NetBuf_ReadS16(void *src);
#endif
#ifndef PROTO_LOCAL_NetBuf_WriteU16
void NetBuf_WriteU16(void *dst, u16 v);
#endif
#ifndef PROTO_LOCAL_NetBuf_ReadU16
u16 NetBuf_ReadU16(void *src);
#endif
#ifndef PROTO_LOCAL_CommRecord_SetLength
void CommRecord_SetLength(void *dst, u16 v);
#endif
#ifndef PROTO_LOCAL_CommRecord_GetLength
u16 CommRecord_GetLength(void *src);
#endif
#ifndef PROTO_LOCAL_CommBlock_WriteAct00
void CommBlock_WriteAct00(void);
#endif
#ifndef PROTO_LOCAL_CommBlock_WriteAct01
void CommBlock_WriteAct01(void);
#endif
#ifndef PROTO_LOCAL_CommBlock_ReadAct00
void CommBlock_ReadAct00(void);
#endif
#ifndef PROTO_LOCAL_CommBlock_ReadAct01
void CommBlock_ReadAct01(u8 *buf);
#endif
#ifndef PROTO_LOCAL_CommBlock_BuildPacket
s32 CommBlock_BuildPacket(u32 a);
#endif
#ifndef PROTO_LOCAL_CommBlock_ParseAll
void CommBlock_ParseAll(u8 *p, u32 n);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_GetVarSize
u32 CommSyncVar_GetVarSize(u32 i);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_GetVarOffset
u32 CommSyncVar_GetVarOffset(u32 i);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager0
void CommSyncVar_InitVillager0(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager1
void CommSyncVar_InitVillager1(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager2
void CommSyncVar_InitVillager2(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager3
void CommSyncVar_InitVillager3(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager4
void CommSyncVar_InitVillager4(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager5
void CommSyncVar_InitVillager5(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager6
void CommSyncVar_InitVillager6(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVillager7
void CommSyncVar_InitVillager7(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_InitVar
void CommSyncVar_InitVar(u32 i);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPos
void CommSyncVar_PackPos(u8 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerPos0
void CommSyncVar_PackPlayerPos0(u8 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerPos1
void CommSyncVar_PackPlayerPos1(u8 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerPos2
void CommSyncVar_PackPlayerPos2(u8 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerPos3
void CommSyncVar_PackPlayerPos3(u8 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackAngle
void CommSyncVar_PackAngle(void *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerAngle0
void CommSyncVar_PackPlayerAngle0(void *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerAngle1
void CommSyncVar_PackPlayerAngle1(void *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerAngle2
void CommSyncVar_PackPlayerAngle2(void *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerAngle3
void CommSyncVar_PackPlayerAngle3(void *a, s16 *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar08
void CommSyncVar_PackVar08(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar09
void CommSyncVar_PackVar09(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar0A
void CommSyncVar_PackVar0A(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar0B
void CommSyncVar_PackVar0B(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager0
void CommSyncVar_PackVillager0(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager1
void CommSyncVar_PackVillager1(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager2
void CommSyncVar_PackVillager2(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager3
void CommSyncVar_PackVillager3(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager4
void CommSyncVar_PackVillager4(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager5
void CommSyncVar_PackVillager5(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager6
void CommSyncVar_PackVillager6(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVillager7
void CommSyncVar_PackVillager7(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar18
void CommSyncVar_PackVar18(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar19
void CommSyncVar_PackVar19(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1A
void CommSyncVar_PackVar1A(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1B
void CommSyncVar_PackVar1B(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1C
void CommSyncVar_PackVar1C(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1D
void CommSyncVar_PackVar1D(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1E
void CommSyncVar_PackVar1E(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackVar1F
void CommSyncVar_PackVar1F(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc00
void CommSyncVar_PackSpNpc00(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc01
void CommSyncVar_PackSpNpc01(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc02
void CommSyncVar_PackSpNpc02(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc03
void CommSyncVar_PackSpNpc03(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc04
void CommSyncVar_PackSpNpc04(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc05
void CommSyncVar_PackSpNpc05(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc06
void CommSyncVar_PackSpNpc06(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc07
void CommSyncVar_PackSpNpc07(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc08
void CommSyncVar_PackSpNpc08(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc09
void CommSyncVar_PackSpNpc09(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0A
void CommSyncVar_PackSpNpc0A(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0B
void CommSyncVar_PackSpNpc0B(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0C
void CommSyncVar_PackSpNpc0C(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0D
void CommSyncVar_PackSpNpc0D(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0E
void CommSyncVar_PackSpNpc0E(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc0F
void CommSyncVar_PackSpNpc0F(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc10
void CommSyncVar_PackSpNpc10(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc11
void CommSyncVar_PackSpNpc11(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc12
void CommSyncVar_PackSpNpc12(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc13
void CommSyncVar_PackSpNpc13(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc14
void CommSyncVar_PackSpNpc14(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc15
void CommSyncVar_PackSpNpc15(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc16
void CommSyncVar_PackSpNpc16(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc17
void CommSyncVar_PackSpNpc17(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc18
void CommSyncVar_PackSpNpc18(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc19
void CommSyncVar_PackSpNpc19(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1A
void CommSyncVar_PackSpNpc1A(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1B
void CommSyncVar_PackSpNpc1B(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1C
void CommSyncVar_PackSpNpc1C(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1D
void CommSyncVar_PackSpNpc1D(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1E
void CommSyncVar_PackSpNpc1E(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc1F
void CommSyncVar_PackSpNpc1F(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc20
void CommSyncVar_PackSpNpc20(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc21
void CommSyncVar_PackSpNpc21(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc22
void CommSyncVar_PackSpNpc22(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc23
void CommSyncVar_PackSpNpc23(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc24
void CommSyncVar_PackSpNpc24(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackSpNpc25
void CommSyncVar_PackSpNpc25(void *a);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_SetVar
void CommSyncVar_SetVar(u32 a, void *b, u32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_Init
void CommSyncVar_Init();
#endif
#ifndef PROTO_LOCAL_CommRecv_RoomWallFloor
void CommRecv_RoomWallFloor(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_PatternMove
void CommRecv_PatternMove(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_SubCommand
void CommRecv_SubCommand(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_CharInteract
void CommRecv_CharInteract(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_FurnitureState
void CommRecv_FurnitureState(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_HouseRoomFlag
void CommRecv_HouseRoomFlag(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_RoomItemSet
void CommRecv_RoomItemSet(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommRecv_FurnitureRemove
void CommRecv_FurnitureRemove(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommRecv_FurniturePlace
void CommRecv_FurniturePlace(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_CommRecv_FurnitureUseRequest
void CommRecv_FurnitureUseRequest(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_SpotReserveRequest
void CommRecv_SpotReserveRequest(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_SpotReserveGranted
void CommRecv_SpotReserveGranted();
#endif
#ifndef PROTO_LOCAL_CommRecv_SpotReserveDenied
void CommRecv_SpotReserveDenied();
#endif
#ifndef PROTO_LOCAL_CommRecv_SpotRelease
void CommRecv_SpotRelease(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_BuildingState
void CommRecv_BuildingState(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_BuildingEnter
void CommRecv_BuildingEnter(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_BuildingLeave
void CommRecv_BuildingLeave(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act25
void CommRecv_Act25(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_ShopPurchase
void CommRecv_ShopPurchase(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_ShopPurchaseAck
void CommRecv_ShopPurchaseAck(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_FieldActorClaimRequest
void CommRecv_FieldActorClaimRequest(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_FieldActorClaimResult
void CommRecv_FieldActorClaimResult(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_FieldActorRelease
void CommRecv_FieldActorRelease(u32 a);
#endif
#ifndef PROTO_LOCAL_CommRecv_FieldActorRemove
void CommRecv_FieldActorRemove(u32 n);
#endif
#ifndef PROTO_LOCAL_CommRecv_FishDisplay
void CommRecv_FishDisplay(s32 n, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_ClothesChange
void CommRecv_ClothesChange(s32 n, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_HairChange
void CommRecv_HairChange(s32 n, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_FaceChange
void CommRecv_FaceChange(s32 n, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_TanChange
void CommRecv_TanChange(s32 n, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_ItemActionRequest
void CommRecv_ItemActionRequest(s32 a, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_ItemActionResult
void CommRecv_ItemActionResult(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommRecv_ObjectUseRequest
void CommRecv_ObjectUseRequest(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_ObjectUseReply
void CommRecv_ObjectUseReply();
#endif
#ifndef PROTO_LOCAL_CommRecv_ObjectUseRelease
void CommRecv_ObjectUseRelease(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerMemoryInit
void CommRecv_VillagerMemoryInit(s32 n, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerMemorySetPlayer
void CommRecv_VillagerMemorySetPlayer(s32 n, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerImpression
void CommRecv_VillagerImpression();
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerFriendship
void CommRecv_VillagerFriendship();
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerReceivedItem
void CommRecv_VillagerReceivedItem();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act3C
void CommRecv_Act3C();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act3D
void CommRecv_Act3D();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act3F
void CommRecv_Act3F();
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerShirt
void CommRecv_VillagerShirt();
#endif
#ifndef PROTO_LOCAL_CommRecv_VillagerItems
void CommRecv_VillagerItems();
#endif
#ifndef PROTO_LOCAL_CommRecv_PeerNetState
void CommRecv_PeerNetState(s32 a, s32 b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_OwnNetState
void CommRecv_OwnNetState();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act02
void CommRecv_Act02(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act03
void CommRecv_Act03();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act04
void CommRecv_Act04(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_PlayerLeft
void CommRecv_PlayerLeft();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act06
void CommRecv_Act06(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act07
void CommRecv_Act07();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act08
void CommRecv_Act08(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_SlotStatus
void CommRecv_SlotStatus();
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0A
void CommRecv_Act0A(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0B
void CommRecv_Act0B(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0C
void CommRecv_Act0C(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0D
void CommRecv_Act0D(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0E
void CommRecv_Act0E(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act0F
void CommRecv_Act0F(u32 n);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act10
void CommRecv_Act10(u32 n);
#endif
#ifndef PROTO_LOCAL_CommRecv_Act11
void CommRecv_Act11();
#endif
#ifndef PROTO_LOCAL_CommRecv_ItemSet
void CommRecv_ItemSet(u32 n);
#endif
#ifndef PROTO_LOCAL_CommRecv_ItemSetRequest
void CommRecv_ItemSetRequest(u32 n);
#endif
#ifndef PROTO_LOCAL_CommRecv_Dispatch
void CommRecv_Dispatch(u32 idx, u8 *x, u32 a, u32 b, u8 c, u32 d);
#endif
#ifndef PROTO_LOCAL_CommSend_MemberInfo
BOOL CommSend_MemberInfo(u32 a);
#endif
#ifndef PROTO_LOCAL_CommSend_Chunked
BOOL CommSend_Chunked(u8 *p, void *data, u32 size, u32 type, u32 maskw);
#endif
#ifndef PROTO_LOCAL_CommSend_TownChunk
BOOL CommSend_TownChunk(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerTransfer
BOOL CommSend_VillagerTransfer(u8 *p);
#endif
#ifndef PROTO_LOCAL_CommSend_VillagerTransferReply
BOOL CommSend_VillagerTransferReply(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
#endif
#ifndef PROTO_LOCAL_CommSend_PlayerData
BOOL CommSend_PlayerData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_CommSend_SyncVarChunk
BOOL CommSend_SyncVarChunk(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_CommSend_BuiltPacket
BOOL CommSend_BuiltPacket(u32 a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct08
BOOL CommCtrl_SendAct08();
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct07
BOOL CommCtrl_SendAct07();
#endif
#ifndef PROTO_LOCAL_CommSend_JoinDone
BOOL CommSend_JoinDone(u32 a);
#endif
#ifndef PROTO_LOCAL_CommSend_JoinReady
BOOL CommSend_JoinReady();
#endif
#ifndef PROTO_LOCAL_CommSend_DateTime
s32 CommSend_DateTime(u32 a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct0E
s32 CommCtrl_SendAct0E(u8 a, u32 b);
#endif
#ifndef PROTO_LOCAL_CommSend_SlotStatusAll
s32 CommSend_SlotStatusAll(s32 a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct10
s32 CommCtrl_SendAct10();
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct11
s32 CommCtrl_SendAct11();
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct12
s32 CommCtrl_SendAct12(u32 a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct13
s32 CommCtrl_SendAct13();
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct14
s32 CommCtrl_SendAct14();
#endif
#ifndef PROTO_LOCAL_CommSend_PlayerDataToHost
s32 CommSend_PlayerDataToHost(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommSend_LetterStorageToHost
s32 CommSend_LetterStorageToHost(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_SendAct17
s32 CommCtrl_SendAct17();
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvMemberInfo
void CommCtrl_RecvMemberInfo(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvTownChunk
void CommCtrl_RecvTownChunk(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvVillagerTransfer
void CommCtrl_RecvVillagerTransfer(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvVillagerTransferReply
void CommCtrl_RecvVillagerTransferReply(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvVisitorPlayerData
void CommCtrl_RecvVisitorPlayerData(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvNetState
void CommCtrl_RecvNetState(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act06
void CommCtrl_Act06(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act07
void CommCtrl_Act07();
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act08
void CommCtrl_Act08(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvJoinReady
void CommCtrl_RecvJoinReady();
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvDateTime
void CommCtrl_RecvDateTime(void *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvJoinDone
void CommCtrl_RecvJoinDone();
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvSyncVarChunk
void CommCtrl_RecvSyncVarChunk(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvStateBlocks
void CommCtrl_RecvStateBlocks(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act0E
void CommCtrl_Act0E(u8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvSlotStatusAll
void CommCtrl_RecvSlotStatusAll(u8 *a);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act10
void CommCtrl_Act10(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act11
void CommCtrl_Act11(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act12
void CommCtrl_Act12();
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act13
void CommCtrl_Act13(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act14
void CommCtrl_Act14(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvPlayerDataToHost
void CommCtrl_RecvPlayerDataToHost(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommCtrl_RecvLetterStorageToHost
void CommCtrl_RecvLetterStorageToHost(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_CommCtrl_Act17
void CommCtrl_Act17();
#endif
#ifndef PROTO_LOCAL_CommCtrl_Dispatch
void CommCtrl_Dispatch(void *a, s32 b, s32 c, u32 idx);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BbsPost_GetText
u8 *BbsPost_GetText(BbsPost *p);
#endif
#ifndef PROTO_LOCAL_Bbs_LoadMsg
void Bbs_LoadMsg(MsgString *a, u32 b, const char *c);
#endif
#ifndef PROTO_LOCAL_BbsPost_SetTextFromMsg
BOOL BbsPost_SetTextFromMsg(BbsPost *self, MsgString193 *r1);
#endif
#ifndef PROTO_LOCAL_FriendList_Clear
void FriendList_Clear(FriendEntry *base);
#endif
#ifndef PROTO_LOCAL_OverlayHandle_Load
void OverlayHandle_Load(OverlayHandleView *s, s32 v);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerMsg0
void CommSyncVar_PackPlayerMsg0(u8 *a, ChatBalloon *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerMsg1
void CommSyncVar_PackPlayerMsg1(u8 *a, ChatBalloon *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerMsg2
void CommSyncVar_PackPlayerMsg2(u8 *a, ChatBalloon *b);
#endif
#ifndef PROTO_LOCAL_CommSyncVar_PackPlayerMsg3
void CommSyncVar_PackPlayerMsg3(u8 *a, ChatBalloon *b);
#endif
}
#ifndef PROTO_LOCAL_sBbsDefaultKey
extern char *sBbsDefaultKey;
#endif
#ifndef PROTO_LOCAL_data_020e0548
extern char data_020e0548[];
#endif
#ifndef PROTO_LOCAL_gOverlayHandle
extern OverlayHandle gOverlayHandle;
#endif
#endif

#endif
