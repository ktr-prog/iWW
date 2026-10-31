#ifndef PROTO_PROTO_MAIN_UNK_020594DC_H
#define PROTO_PROTO_MAIN_UNK_020594DC_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/HBlankTask.h"
#include "npc/VillagerId.h"
#include "player/PlayerId.h"
#include "town/BlockMap.h"
class HappyRoomFtrBitset;
class HappyRoomSeriesScores;
class HappyRoomUnk06Masks;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_Construct
void HappyRoomDate_Construct();
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_Destruct
void HappyRoomDate_Destruct();
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_SetToday
void HappyRoomDate_SetToday(u8 *out);
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_Reset
void HappyRoomDate_Reset(u8 *out);
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_IsNewWeek
s32 HappyRoomDate_IsNewWeek(u8 *out);
#endif
#ifndef PROTO_LOCAL_HappyRoomDate_SetEvalDay
void HappyRoomDate_SetEvalDay(u8 *out);
#endif
#ifndef PROTO_LOCAL_FengShui_GetTotal
u32 FengShui_GetTotal();
#endif
#ifndef PROTO_LOCAL_FengShui_GetWestTotal
u8 FengShui_GetWestTotal();
#endif
#ifndef PROTO_LOCAL_FengShui_GetSouthTotal
u8 FengShui_GetSouthTotal();
#endif
#ifndef PROTO_LOCAL_FengShui_GetEastTotal
u8 FengShui_GetEastTotal();
#endif
#ifndef PROTO_LOCAL_FengShui_UpdateHouse
void FengShui_UpdateHouse();
#endif
#ifndef PROTO_LOCAL_HappyRoom_CalcLuckyBonus
u32 HappyRoom_CalcLuckyBonus(u32 *p);
#endif
#ifndef PROTO_LOCAL_RoomScoreEvaluator_Destruct
void RoomScoreEvaluator_Destruct();
#endif
#ifndef PROTO_LOCAL_HappyRoom_EvaluateHouse
void HappyRoom_EvaluateHouse(void *evaluator);
#endif
#ifndef PROTO_LOCAL_HappyRoom_EvaluateVillagerRoom
s32 HappyRoom_EvaluateVillagerRoom(void *evaluator, s32 b, u16 *c, s32 *d, s32 *e, s32 *f);
#endif
#ifndef PROTO_LOCAL_HappyRoom_SendScoreLetters
BOOL HappyRoom_SendScoreLetters(void *self, s32 a, s32 b, s32 c, s32 n);
#endif
#ifndef PROTO_LOCAL_HappyRoom_SendPrizeLetter
void HappyRoom_SendPrizeLetter(void *self, s32 n);
#endif
#ifndef PROTO_LOCAL_HappyRoom_SendWelcomeLetter
BOOL HappyRoom_SendWelcomeLetter();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HBlank_Replace
BOOL HBlank_Replace(HBlankTask *t, void (*a)(), void (*b)());
#endif
#ifndef PROTO_LOCAL_RoomMap_GetFloorBounds
BOOL RoomMap_GetFloorBounds(s32 *a, s32 *b, s32 *c, s32 *d, BlockMap *grid);
#endif
#ifndef PROTO_LOCAL_Villager_SendLetterWithPaper
BOOL Villager_SendLetterWithPaper(const char *r0, u8 r1, PlayerId *r2, VillagerId *r3, u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Villager_SendBirthdayNoticeLetter
BOOL Villager_SendBirthdayNoticeLetter(PlayerId *a, VillagerId *b);
#endif
#ifndef PROTO_LOCAL_Villager_SendHouseVisitLetter
s32 Villager_SendHouseVisitLetter(u32 a, PlayerId *b, VillagerId *c);
#endif
}
#ifndef PROTO_LOCAL_data_020dc07c
extern u32 data_020dc07c[1];
#endif
#ifndef PROTO_LOCAL_data_020dc080
extern u32 data_020dc080[1];
#endif
#ifndef PROTO_LOCAL_data_020dc084
extern u32 data_020dc084[1];
#endif
#ifndef PROTO_LOCAL_data_020dc088
extern u32 data_020dc088[1];
#endif
#ifndef PROTO_LOCAL_data_020dc08c
extern u32 data_020dc08c[1];
#endif
#ifndef PROTO_LOCAL_data_020dc090
extern u32 data_020dc090[1];
#endif
#ifndef PROTO_LOCAL_sFengShuiEastTotal
extern u8 sFengShuiEastTotal;
#endif
#ifndef PROTO_LOCAL_sFengShuiWestTotal
extern u8 sFengShuiWestTotal;
#endif
#ifndef PROTO_LOCAL_sFengShuiSouthTotal
extern u8 sFengShuiSouthTotal;
#endif
#ifndef PROTO_LOCAL_sHappyRoomVillagerMap
extern void *sHappyRoomVillagerMap;
#endif
#ifndef PROTO_LOCAL_sVillagerLetterWithPaperPath
extern char sVillagerLetterWithPaperPath[0x28];
#endif
#ifndef PROTO_LOCAL_sHappyRoomSeriesScores
extern HappyRoomSeriesScores sHappyRoomSeriesScores;
#endif
#ifndef PROTO_LOCAL_sHappyRoomLuckyFtr
extern HappyRoomFtrBitset sHappyRoomLuckyFtr;
#endif
#ifndef PROTO_LOCAL_sHappyRoomUnk06Masks
extern HappyRoomUnk06Masks sHappyRoomUnk06Masks;
#endif
#endif

#endif
