#ifndef PROTO_PROTO_MAIN_UNK_02082D74_H
#define PROTO_PROTO_MAIN_UNK_02082D74_H


#include "types.h"
#include "sys/ProcProfile.h"
struct EventVisitorEntry;
struct NpcNetRecord;
struct Unk_02083314_K;
struct VisitorCheckEntry;
struct VisitorSchedule;
struct VisitorSpawnEntry;
#ifndef __cplusplus
typedef struct EventVisitorEntry EventVisitorEntry;
typedef struct NpcNetRecord NpcNetRecord;
typedef struct Unk_02083314_K Unk_02083314_K;
typedef struct VisitorCheckEntry VisitorCheckEntry;
typedef struct VisitorSchedule VisitorSchedule;
typedef struct VisitorSpawnEntry VisitorSpawnEntry;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "npc/NpcSpawner.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Town_RemoveShipParts
void Town_RemoveShipParts();
#endif
#ifndef PROTO_LOCAL_NpcSpawn_GetSpNpcSlotCount
s32 NpcSpawn_GetSpNpcSlotCount();
#endif
#ifndef PROTO_LOCAL_NpcSpawn_ResetAll
void NpcSpawn_ResetAll();
#endif
#ifndef PROTO_LOCAL_NpcNetRecords_InitVillagers
void NpcNetRecords_InitVillagers();
#endif
#ifndef PROTO_LOCAL_Event_IsActive
BOOL Event_IsActive(s32 a, s32 *p);
#endif
#ifndef PROTO_LOCAL_Visitor_GetTodaysNpc
void Visitor_GetTodaysNpc(u16 *out);
#endif
#ifndef PROTO_LOCAL_NpcSpawner_SpawnVillagers
void NpcSpawner_SpawnVillagers(void *a);
#endif
#ifndef PROTO_LOCAL_NpcSpawner_SpawnPlayerHouseVisitor
void NpcSpawner_SpawnPlayerHouseVisitor(void *a);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetVillagerSlots
BOOL NpcNetRecord_SetVillagerSlots(u16 *p, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_InitVillagerVar
void NpcNetRecord_InitVillagerVar(void *dst, s32 id);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_PackVillager
void NpcNetRecord_PackVillager(void *dst, s32 id);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_GetVillagerVar
u8 *NpcNetRecord_GetVillagerVar(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetSpNpcSlots
BOOL NpcNetRecord_SetSpNpcSlots(u16 *p, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_PackSpNpc
void NpcNetRecord_PackSpNpc(void *dst, s32 id);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_GetSpNpcVar
u8 *NpcNetRecord_GetSpNpcVar(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetSlots
BOOL NpcNetRecord_SetSlots(u16 *p, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_GetVar
u8 *NpcNetRecord_GetVar(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetSlotsAndSync
void NpcNetRecord_SetSlotsAndSync(u32 a, u32 b, u32 c, u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_GetSlots
BOOL NpcNetRecord_GetSlots(s32 *a, s32 *b, u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_ResetTalkSlots
void NpcNetRecord_ResetTalkSlots();
#endif
#ifndef PROTO_LOCAL_RoomFreeUnitMap_Build
BOOL RoomFreeUnitMap_Build(u16 *out);
#endif
#ifndef PROTO_LOCAL_RoomFreeUnitMap_Set
BOOL RoomFreeUnitMap_Set(u16 *arr, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_RoomFreeUnitMap_Clear
BOOL RoomFreeUnitMap_Clear(u16 *arr, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_RoomFreeUnitMap_Test
BOOL RoomFreeUnitMap_Test(u16 *arr, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_RoomFreeUnitMap_TestUpper
BOOL RoomFreeUnitMap_TestUpper(u16 *arr, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Visitor_IsNookJobActive
BOOL Visitor_IsNookJobActive();
#endif
#ifndef PROTO_LOCAL_Visitor_IsTaxiActive
BOOL Visitor_IsTaxiActive();
#endif
#ifndef PROTO_LOCAL_Visitor_CheckResetti
u16 *Visitor_CheckResetti();
#endif
#ifndef PROTO_LOCAL_Visitor_CheckTomNook
u16 *Visitor_CheckTomNook();
#endif
#ifndef PROTO_LOCAL_Visitor_IsTortimerDue
BOOL Visitor_IsTortimerDue();
#endif
#ifndef PROTO_LOCAL_Visitor_FindTortimer
u16 *Visitor_FindTortimer(s32 flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckTortimer
u16 *Visitor_CheckTortimer(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Visitor_IsNookJobErrandActive
BOOL Visitor_IsNookJobErrandActive();
#endif
#ifndef PROTO_LOCAL_Visitor_FindEventHost
u16 *Visitor_FindEventHost(s32 flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckEventHost
u16 *Visitor_CheckEventHost(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Visitor_FindLyle
u16 *Visitor_FindLyle(s32 flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckLyle
u16 *Visitor_CheckLyle(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Visitor_FindJoan
u16 *Visitor_FindJoan(s32 flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckJoan
u16 *Visitor_CheckJoan(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Visitor_FindKatie
u16 *Visitor_FindKatie(s32 flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckKatie
u16 *Visitor_CheckKatie(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_NpcSpawner_RepickKatiePosOnline
void NpcSpawner_RepickKatiePosOnline();
#endif
#ifndef PROTO_LOCAL_Visitor_FindKaitlin
u16 *Visitor_FindKaitlin(BOOL flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckKaitlin
u16 *Visitor_CheckKaitlin();
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Kaitlin
BOOL VisitorPlace_Kaitlin(void *self, void *b);
#endif
#ifndef PROTO_LOCAL_Visitor_FindBlanca
u16 *Visitor_FindBlanca(BOOL flag);
#endif
#ifndef PROTO_LOCAL_Visitor_CheckBlanca
u16 *Visitor_CheckBlanca();
#endif
#ifndef PROTO_LOCAL_Visitor_CheckDateVisitors
u16 *Visitor_CheckDateVisitors();
#endif
#ifndef PROTO_LOCAL_Visitor_CheckPete
u16 *Visitor_CheckPete();
#endif
#ifndef PROTO_LOCAL_Visitor_CanPascalVisit
BOOL Visitor_CanPascalVisit();
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Pete
BOOL VisitorPlace_Pete(void *self, void *b, u16 *out);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_AtVisitorPos
BOOL VisitorPlace_AtVisitorPos(void *self, void *b, u16 *out);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Gulliver
BOOL VisitorPlace_Gulliver(void *self, void *b, u16 *out, void *d);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_NpcSpawner_Create
NpcSpawner *NpcSpawner_Create();
#endif
#ifndef PROTO_LOCAL_NpcSpawner_PickFreeRoomPos
s32 NpcSpawner_PickFreeRoomPos(NpcSpawner *a, VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_NpcSpawn_FixVillagerPos
void NpcSpawn_FixVillagerPos(void *a, VecFx32 *vec);
#endif
#ifndef PROTO_LOCAL_NpcSpawner_SpawnHouseOwner
void NpcSpawner_SpawnHouseOwner(NpcSpawner *a);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetVillagerState
BOOL NpcNetRecord_SetVillagerState(u16 *p, u32 b, VecFx32 *v, u16 c, u8 *d, u8 *e);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetSpNpcState
BOOL NpcNetRecord_SetSpNpcState(u16 *p, u32 b, VecFx32 *v, u16 c, u8 *d, u8 *e);
#endif
#ifndef PROTO_LOCAL_NpcNetRecord_SetState
BOOL NpcNetRecord_SetState(u16 *p, u32 b, VecFx32 *v, u16 c, u8 *d, u8 *e);
#endif
#ifndef PROTO_LOCAL_VisitorSchedule_Set
void VisitorSchedule_Set(VisitorSchedule *out, u16 *idp, u32 b, u32 c, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_VisitorSchedule_Clear
void VisitorSchedule_Clear(VisitorSchedule *g);
#endif
#ifndef PROTO_LOCAL_VisitorSchedule_IsSet
BOOL VisitorSchedule_IsSet(void *p, VisitorSchedule *g);
#endif
#ifndef PROTO_LOCAL_VisitorTable_FindByNpc
u16 *VisitorTable_FindByNpc(const u16 *key, VisitorSpawnEntry *tbl, s32 n);
#endif
#ifndef PROTO_LOCAL_VisitorTable_FindByProfile
u16 *VisitorTable_FindByProfile(const u16 *key, VisitorSpawnEntry *tbl, s32 n);
#endif
#ifndef PROTO_LOCAL_Visitor_ScheduleIfHigher
BOOL Visitor_ScheduleIfHigher(u16 *p, u32 lvl, u32 b, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_Visitor_ScheduleLow
BOOL Visitor_ScheduleLow(u16 *p, u8 b, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_Visitor_FindActiveEventEntry
s32 Visitor_FindActiveEventEntry(const EventVisitorEntry *p, s32 n);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Resetti
BOOL VisitorPlace_Resetti(s32 a, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_TomNook
BOOL VisitorPlace_TomNook(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_NearTownHall
BOOL VisitorPlace_NearTownHall(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_NearPlayerHouse
BOOL VisitorPlace_NearPlayerHouse(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_EventHost
BOOL VisitorPlace_EventHost(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Tortimer
BOOL VisitorPlace_Tortimer(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Origin
BOOL VisitorPlace_Origin(s32 a, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Lyle
BOOL VisitorPlace_Lyle(s32 a, VecFx32 *p, Unk_02083314_K *q);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Katie
BOOL VisitorPlace_Katie(s32 a, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Visitor_FindInEventTable
u16 *Visitor_FindInEventTable(const EventVisitorEntry *tbl, const void *fn, s32 x, BOOL flag);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Beach
BOOL VisitorPlace_Beach(void *self, VecFx32 *p1);
#endif
#ifndef PROTO_LOCAL_VisitorPlace_Gracie
BOOL VisitorPlace_Gracie(void *self, VecFx32 *g, u16 *out, s32 *a);
#endif
}
#ifndef PROTO_LOCAL_sVillagerNetRecords
extern NpcNetRecord sVillagerNetRecords[8];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_FlowerFest
extern void *sVisitorPlacePmf_FlowerFest[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Gulliver
extern void *sVisitorPlacePmf_Gulliver[2];
#endif
#ifndef PROTO_LOCAL_sEventTortimerProfile
extern u16 sEventTortimerProfile[4];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Blanca
extern void *sVisitorPlacePmf_Blanca[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Resetti
extern void *sVisitorCheckPmf_Resetti[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Saharah
extern void *sVisitorPlacePmf_Saharah[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Pascal
extern void *sVisitorPlacePmf_Pascal[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Gracie
extern void *sVisitorPlacePmf_Gracie[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_TomNook
extern void *sVisitorCheckPmf_TomNook[2];
#endif
#ifndef PROTO_LOCAL_sVisitorSchedule
extern VisitorSchedule sVisitorSchedule;
#endif
#ifndef PROTO_LOCAL_sSpNpcNetRecords
extern NpcNetRecord sSpNpcNetRecords[0x26];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Kaitlin
extern void *sVisitorCheckPmf_Kaitlin[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Wendell
extern void *sVisitorPlacePmf_Wendell[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Blanca
extern void *sVisitorCheckPmf_Blanca[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Pete
extern void *sVisitorCheckPmf_Pete[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Fireworks
extern void *sVisitorPlacePmf_Fireworks[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Shrunk
extern void *sVisitorPlacePmf_Shrunk[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Tortimer
extern void *sVisitorPlacePmf_Tortimer[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_BugOff
extern void *sVisitorPlacePmf_BugOff[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Kaitlin
extern void *sVisitorPlacePmf_Kaitlin[2];
#endif
#ifndef PROTO_LOCAL_sNpcSpawnerProfile
extern ProcProfile sNpcSpawnerProfile;
#endif
#ifndef PROTO_LOCAL_sVisitorCheckTable
extern VisitorCheckEntry sVisitorCheckTable[11];
#endif
#ifndef PROTO_LOCAL_sTortimerVisitorProfile
extern u16 sTortimerVisitorProfile[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Joan
extern void *sVisitorPlacePmf_Joan[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Katie
extern void *sVisitorPlacePmf_Katie[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_TomNook
extern void *sVisitorPlacePmf_TomNook[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_BrightNights
extern void *sVisitorPlacePmf_BrightNights[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_EventHost
extern void *sVisitorCheckPmf_EventHost[2];
#endif
#ifndef PROTO_LOCAL_sVillagerNetRecordPacked
extern u8 sVillagerNetRecordPacked;
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_DateVisitors
extern void *sVisitorCheckPmf_DateVisitors[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Lyle
extern void *sVisitorCheckPmf_Lyle[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_FishingTourney
extern void *sVisitorPlacePmf_FishingTourney[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Cornimer
extern void *sVisitorPlacePmf_Cornimer[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_TortimerTti
extern void *sVisitorPlacePmf_TortimerTti[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Pete
extern void *sVisitorPlacePmf_Pete[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Katie
extern void *sVisitorCheckPmf_Katie[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Joan
extern void *sVisitorCheckPmf_Joan[2];
#endif
#ifndef PROTO_LOCAL_sVisitorSpawnTable
extern VisitorSpawnEntry sVisitorSpawnTable[23];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Countdown
extern void *sVisitorPlacePmf_Countdown[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Lyle
extern void *sVisitorPlacePmf_Lyle[2];
#endif
#ifndef PROTO_LOCAL_sVisitorCheckPmf_Tortimer
extern void *sVisitorCheckPmf_Tortimer[2];
#endif
#ifndef PROTO_LOCAL_sVisitorPlacePmf_Resetti
extern void *sVisitorPlacePmf_Resetti[2];
#endif
#endif

#endif
