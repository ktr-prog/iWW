#ifndef PROTO_PROTO_MAIN_UNK_02085940_H
#define PROTO_PROTO_MAIN_UNK_02085940_H


#include "types.h"
#include "save/DramaPart.h"
#include "sys/ClockDate.h"
#ifdef __cplusplus
#include "town/BlockMap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Cell_HitTest
BOOL Cell_HitTest(void *p, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_Cell_HitTestList
s32 Cell_HitTestList(void *p, s32 n, s32 c, s32 d, s32 e, s32 f);
#endif
#ifndef PROTO_LOCAL_Oam_AllocAffine
s32 Oam_AllocAffine(u8 *self, s32 *cnt, s32 *v);
#endif
#ifndef PROTO_LOCAL_Oam_UseBufferA
BOOL Oam_UseBufferA(s32 t);
#endif
#ifndef PROTO_LOCAL_PlayerSpNpcRecord_Construct
void PlayerSpNpcRecord_Construct();
#endif
#ifndef PROTO_LOCAL_PlayerSpNpcRecord_Destruct
void PlayerSpNpcRecord_Destruct();
#endif
#ifndef PROTO_LOCAL_PlayerSpNpcRecord_InitNop
void PlayerSpNpcRecord_InitNop();
#endif
#ifndef PROTO_LOCAL_PlayerSpNpcRecord_GetInsuranceDate
void *PlayerSpNpcRecord_GetInsuranceDate(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerSpNpcRecord_SendMissingLetter
void PlayerSpNpcRecord_SendMissingLetter();
#endif
#ifndef PROTO_LOCAL_PlayerDailyTalkFlags_Construct
void PlayerDailyTalkFlags_Construct();
#endif
#ifndef PROTO_LOCAL_PlayerDailyTalkFlags_Destruct
void PlayerDailyTalkFlags_Destruct();
#endif
#ifndef PROTO_LOCAL_DramaRecord_Construct
void DramaRecord_Construct();
#endif
#ifndef PROTO_LOCAL_DramaRecord_Destruct
void DramaRecord_Destruct();
#endif
#ifndef PROTO_LOCAL_DramaRecord_Clear
void DramaRecord_Clear(DramaRecord *a);
#endif
#ifndef PROTO_LOCAL_DramaRecord_GetLastPart
void DramaRecord_GetLastPart(DramaRecord *a, Unk_020874e8_Bits *b);
#endif
#ifndef PROTO_LOCAL_DramaRecord_SetLastPart
void DramaRecord_SetLastPart(DramaRecord *a, Unk_020874e8_Bits *b);
#endif
#ifndef PROTO_LOCAL_DramaRecord_GetDate
ClockDate *DramaRecord_GetDate(DramaRecord *p);
#endif
#ifndef PROTO_LOCAL_Drama_FindScheduledPart
BOOL Drama_FindScheduledPart(s32 lim, s32 b, s32 c, Unk_020874e8_Bits *out);
#endif
#ifndef PROTO_LOCAL_Drama_GetAvailablePart
BOOL Drama_GetAvailablePart(s32 a, s32 b, s32 c, Unk_020874e8_Bits *d);
#endif
#ifndef PROTO_LOCAL_LostChildRecord_Construct
void *LostChildRecord_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_LostChildRecord_Destruct
void *LostChildRecord_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_LostChild_AdvanceDays
void LostChild_AdvanceDays(s32 n);
#endif
#ifndef PROTO_LOCAL_LostChild_IsKatieDue
BOOL LostChild_IsKatieDue();
#endif
#ifndef PROTO_LOCAL_LostChild_IsKaitlinDue
BOOL LostChild_IsKaitlinDue();
#endif
#ifndef PROTO_LOCAL_LostChild_SaveToTown
void LostChild_SaveToTown();
#endif
#ifndef PROTO_LOCAL_LostChild_LoadFromTown
void LostChild_LoadFromTown();
#endif
#ifndef PROTO_LOCAL_VisitorPos_Construct
void VisitorPos_Construct();
#endif
#ifndef PROTO_LOCAL_VisitorPos_Destruct
void VisitorPos_Destruct();
#endif
#ifndef PROTO_LOCAL_VisitorPos_Clear
void VisitorPos_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_TurnipMarket_Construct
void TurnipMarket_Construct();
#endif
#ifndef PROTO_LOCAL_TurnipMarket_Destruct
void TurnipMarket_Destruct();
#endif
#ifndef PROTO_LOCAL_ReddLastSale_GetBuyer
void *ReddLastSale_GetBuyer(void *p);
#endif
#ifndef PROTO_LOCAL_GulliverQuest_Construct
void GulliverQuest_Construct();
#endif
#ifndef PROTO_LOCAL_GulliverQuest_Destruct
void GulliverQuest_Destruct();
#endif
#ifndef PROTO_LOCAL_GulliverQuest_Clear
void GulliverQuest_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_GulliverQuest_Init
void GulliverQuest_Init(void *p);
#endif
#ifndef PROTO_LOCAL_RoostGuestRoll_Construct
void RoostGuestRoll_Construct();
#endif
#ifndef PROTO_LOCAL_RoostGuestRoll_Destruct
void RoostGuestRoll_Destruct();
#endif
#ifndef PROTO_LOCAL_RoostGuestRoll_Init
void RoostGuestRoll_Init(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Field_IsClearSpot
BOOL Field_IsClearSpot(s32 x, s32 y, BlockMap *map);
#endif
#ifndef PROTO_LOCAL_Field_IsClearSpotYX
BOOL Field_IsClearSpotYX(s32 x, s32 y, BlockMap *map);
#endif
#ifndef PROTO_LOCAL_Field_IsClearSpotXY
BOOL Field_IsClearSpotXY(s32 x, s32 y, BlockMap *map);
#endif
#ifndef PROTO_LOCAL_Field_PickRandomInLine
s32 Field_PickRandomInLine(s32 *out, BOOL (*cb)(s32, s32, BlockMap *), s32 arg, s32 cur, s32 limit, BlockMap *m, u16 *buf, s32 n);
#endif
}
#ifndef PROTO_LOCAL_data_020e0c88
extern char data_020e0c88[];
#endif
#ifndef PROTO_LOCAL_data_020e0c7c
extern char data_020e0c7c[];
#endif
#ifndef PROTO_LOCAL_data_020e0c4c
extern u8 data_020e0c4c[4];
#endif
#ifndef PROTO_LOCAL_sKatieSpotRows
extern u32 sKatieSpotRows[0x20];
#endif
#ifndef PROTO_LOCAL_data_020e0c50
extern u8 data_020e0c50[4];
#endif
#ifndef PROTO_LOCAL_data_020e0c58
extern char data_020e0c58[];
#endif
#ifndef PROTO_LOCAL_data_020e0c98
extern char data_020e0c98[];
#endif
#ifndef PROTO_LOCAL_sContestResultBbsFiles
extern char *sContestResultBbsFiles[4];
#endif
#ifndef PROTO_LOCAL_sContestResultMailFiles
extern char *sContestResultMailFiles[4];
#endif
#ifndef PROTO_LOCAL_data_020e0c70
extern char data_020e0c70[];
#endif
#ifndef PROTO_LOCAL_data_020e0c48
extern u8 data_020e0c48[4];
#endif
#ifndef PROTO_LOCAL_data_020e0c64
extern char data_020e0c64[];
#endif
#ifndef PROTO_LOCAL_data_020e0c54
extern u8 data_020e0c54[4];
#endif
#ifndef PROTO_LOCAL_data_020e0c44
extern u8 data_020e0c44[4];
#endif
#endif

#endif
