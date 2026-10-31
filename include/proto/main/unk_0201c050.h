#ifndef PROTO_PROTO_MAIN_UNK_0201C050_H
#define PROTO_PROTO_MAIN_UNK_0201C050_H


#include "types.h"
#include "save/DramaPart.h"
#include "sys/ClockDateTime.h"
struct TalkChoiceTable;
#ifndef __cplusplus
typedef struct TalkChoiceTable TalkChoiceTable;
#endif
#ifdef __cplusplus
#include "actor/VillagerActor.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "item/LetterView.h"
#include "npc/ErrandRecord.h"
#include "talk/ActorTalkRequest.h"
#include "talk/MsgString.h"
#include "talk/VillagerTalk.h"
#include "talk/VillagerTalkRequestStartTopics.h"
class PlayerData;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiRain1
extern char sTalkKeyAiRain1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFuAct
extern char sTalkKeyTsuFuAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiTire
extern char sTalkKeyAiTire[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Con12
extern char sTalkKeyQ04Con12[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiFall
extern char sTalkKeyAiFall[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Pay
extern char sTalkKeyQ02Pay[8];
#endif
#ifndef PROTO_LOCAL_Talk_CheckAndSetPlayerFlag
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
#endif
#ifndef PROTO_LOCAL_Talk_IsDramaPending
BOOL Talk_IsDramaPending(void *unused, Unk_020874e8_Bits *p, u32 mode);
#endif
#ifndef PROTO_LOCAL_Talk_AdvanceDrama
void Talk_AdvanceDrama(void *unused, Unk_020874e8_Bits *part);
#endif
#ifndef PROTO_LOCAL_Talk_IsInOwnTown
BOOL Talk_IsInOwnTown();
#endif
#ifndef PROTO_LOCAL_Talk_SelectTopicMessage
void Talk_SelectTopicMessage(void *self, void *buf, void *out, s32 a3, u8 s0, const char *s1, u8 s2, s32 s3, u8 s4);
#endif
#ifndef PROTO_LOCAL_Talk_FindFlaggedPocketItem
s32 Talk_FindFlaggedPocketItem(void *p, u16 *q);
#endif
#ifndef PROTO_LOCAL_Talk_PickWeightedIndex
s32 Talk_PickWeightedIndex(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_Talk_PickRandomTradeItem
void Talk_PickRandomTradeItem(u16 *out);
#endif
#ifndef PROTO_LOCAL_InsectPick_GetMissingHabitats
void InsectPick_GetMissingHabitats(s32 *out, s32 *cnt);
#endif
#ifndef PROTO_LOCAL_Talk_ArrayContains
s32 Talk_ArrayContains(s32 v, s32 *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_InsectPick_CountInSlot
s32 InsectPick_CountInSlot(s32 c, u8 *p, s32 n, s32 *arr, s32 cnt);
#endif
#ifndef PROTO_LOCAL_InsectPick_PickInSlot
s32 InsectPick_PickInSlot(u16 *a, s32 *b, s32 c, u8 *p, s32 n, s32 *arr, s32 cnt);
#endif
#ifndef PROTO_LOCAL_InsectPick_PickForMonthAnyHour
s32 InsectPick_PickForMonthAnyHour(u16 *a, s32 lo, s32 hi, u8 kind);
#endif
#ifndef PROTO_LOCAL_InsectPick_PickForMonth
s32 InsectPick_PickForMonth(u16 *a, s32 lo, s32 hi, s32 d, s32 e, u8 kind);
#endif
#ifndef PROTO_LOCAL_InsectPick_PickWeightedRarity
s32 InsectPick_PickWeightedRarity(u16 *a, s32 *idxOut, s32 *b, s32 *c, ClockDateTime *now);
#endif
#ifndef PROTO_LOCAL_InsectPick_PickNow
void InsectPick_PickNow(u16 *p);
#endif
#ifndef PROTO_LOCAL_InsectPick_IsAvailable
s32 InsectPick_IsAvailable(u16 *p, s32 lo, s32 hi, s32 id);
#endif
#ifndef PROTO_LOCAL_FishPick_PickForDate
s32 FishPick_PickForDate(u16 *a, s32 lo, s32 hi, s32 d, u8 e, u8 x, u8 y);
#endif
#ifndef PROTO_LOCAL_FishPick_PickForDateAnyHour
s32 FishPick_PickForDateAnyHour(u16 *a, s32 b, s32 c, s32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_FishPick_PickNow
void FishPick_PickNow(u16 *p);
#endif
#ifndef PROTO_LOCAL_FishPick_IsAvailable
s32 FishPick_IsAvailable(u16 *p, s32 lo, s32 hi, s32 id, u8 e);
#endif
#ifndef PROTO_LOCAL_InsectPick_GetHintVariant
s32 InsectPick_GetHintVariant(s32 v);
#endif
#ifndef PROTO_LOCAL_Talk_FindInS8Array
s32 Talk_FindInS8Array(s32 key, const s8 *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_Talk_PickPocketItemForPlan
void Talk_PickPocketItemForPlan(u16 *out, s32 idx);
#endif
#ifndef PROTO_LOCAL_Talk_RoundBells
s32 Talk_RoundBells(s32 x);
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuSeAct
extern char sTalkKeyTsuSeAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuNoAct
extern char sTalkKeyTsuNoAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiJoy
extern char sTalkKeyAiJoy[7];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pTa
extern char sTalkKey3pTa[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiForeign
extern char sTalkKeyAiForeign[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvCountdown
extern char sTalkKeyEvCountdown[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApBuy
extern char sTalkKeyApBuy[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Con245
extern char sTalkKeyQ01Con245[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiSnow1
extern char sTalkKeyAiSnow1[9];
#endif
#ifndef PROTO_LOCAL_sFishRowFlags
extern u8 sFishRowFlags[2];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuDress
extern char sTalkKeyTsuDress[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuAlways
extern char sTalkKeyTsuAlways[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Nlose
extern char sTalkKeyQ02Nlose[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Miss
extern char sTalkKeyQ04Miss[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFriend
extern char sTalkKeyTsuFriend[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAi30days
extern char sTalkKeyAi30days[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiIndoor
extern char sTalkKeyAiIndoor[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiToday1
extern char sTalkKeyAiToday1[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuSpot
extern char sTalkKeyTsuSpot[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuHappyroom
extern char sTalkKeyTsuHappyroom[14];
#endif
#ifndef PROTO_LOCAL_sFishSlotFlags
extern u8 sFishSlotFlags[3];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiPersis
extern char sTalkKeyAiPersis[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuMemory
extern char sTalkKeyTsuMemory[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApSell
extern char sTalkKeyApSell[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuShome
extern char sTalkKeyTsuShome[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApTrade
extern char sTalkKeyApTrade[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuGhome
extern char sTalkKeyTsuGhome[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvAdmire
extern char sTalkKeyEvAdmire[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ10Req
extern char sTalkKeyQ10Req[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Return
extern char sTalkKeyQ03Return[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApPresent1
extern char sTalkKeyApPresent1[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApPresent2
extern char sTalkKeyApPresent2[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Comp
extern char sTalkKeyQ02Comp[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06End
extern char sTalkKeyQ06End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Return
extern char sTalkKeyQ05Return[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Comp
extern char sTalkKeyQ03Comp[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Payback
extern char sTalkKeyQ06Payback[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEtcPush
extern char sTalkKeyEtcPush[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQItem
extern char sTalkKeyQItem[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Pay
extern char sTalkKeyQ01Pay[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ10Reserve
extern char sTalkKeyQ10Reserve[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ12Thanks
extern char sTalkKeyQ12Thanks[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Over
extern char sTalkKeyQ07Over[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvFmarket1
extern char sTalkKeyEvFmarket1[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Lost
extern char sTalkKeyQ06Lost[9];
#endif
#ifndef PROTO_LOCAL_Talk_IsInsectItem
BOOL Talk_IsInsectItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickInsect
BOOL Talk_FilterPickInsect(u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Talk_IsFishItem
BOOL Talk_IsFishItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickFish
BOOL Talk_FilterPickFish(u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Talk_IsNonFossilFurniture
BOOL Talk_IsNonFossilFurniture(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickNonFossilFurniture
BOOL Talk_FilterPickNonFossilFurniture(u16 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_Talk_IsShirtItem
BOOL Talk_IsShirtItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickShirt
BOOL Talk_FilterPickShirt(u16 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_Talk_IsFossilItem
BOOL Talk_IsFossilItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickFossil
BOOL Talk_FilterPickFossil(u16 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_Talk_GetPocketMaskForItem
u32 Talk_GetPocketMaskForItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuEvent1
extern char sTalkKeyTsuEvent1[11];
#endif
#ifndef PROTO_LOCAL_Talk_FilterPickDeliveryShirt
BOOL Talk_FilterPickDeliveryShirt(u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Talk_GetMoneyItem
void Talk_GetMoneyItem(u16 *out, u32 arg);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickInsectStep0
void VillagerRequest_PickInsectStep0(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickInsectStep1
void VillagerRequest_PickInsectStep1(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickInsectStep3
void VillagerRequest_PickInsectStep3(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickInsectStep4
void VillagerRequest_PickInsectStep4(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickInsectForStep
void VillagerRequest_PickInsectForStep(u16 *p, void *unused, u32 idx);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFishStep0
void VillagerRequest_PickFishStep0(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFishStep1
void VillagerRequest_PickFishStep1(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFishStep3
void VillagerRequest_PickFishStep3(u16 *p, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFishStep4
void VillagerRequest_PickFishStep4(u16 *out, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFishForStep
void VillagerRequest_PickFishForStep(u16 *out, void *unused, u32 idx);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickShirtFromGroups
void VillagerRequest_PickShirtFromGroups(u16 *out, u32 mask, s32 cnt, void *x, u8 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickShirtOtherGroup
void VillagerRequest_PickShirtOtherGroup(u16 *out, u8 *p, u16 *arg);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickShirtOfGroup
void VillagerRequest_PickShirtOfGroup(u16 *out, u8 *p, u16 *arg);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickShirtOfGroupForPlayer
void VillagerRequest_PickShirtOfGroupForPlayer(u16 *out, u8 *p, u16 *arg);
#endif
#ifndef PROTO_LOCAL_Item_GetFossilPartIndexInGroup
s32 Item_GetFossilPartIndexInGroup(u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Item_GetFossilPartIndex
s32 Item_GetFossilPartIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_IsArbeitItem
BOOL Talk_IsArbeitItem(u16 *p, s32 flags);
#endif
#ifndef PROTO_LOCAL_Talk_GetFishHintTimeVariant
s32 Talk_GetFishHintTimeVariant(s32 v);
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuDrama
extern char sTalkKeyTsuDrama[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Req245
extern char sTalkKeyQ01Req245[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuClHint
extern char sTalkKeyTsuClHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuEvent2
extern char sTalkKeyTsuEvent2[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQError3
extern char sTalkKeyQError3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Open1
extern char sTalkKeyQ06Open1[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuStar
extern char sTalkKeyTsuStar[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiBoom
extern char sTalkKeyAiBoom[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Get
extern char sTalkKeyQ06Get[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Scold2
extern char sTalkKeyQ07Scold2[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Read
extern char sTalkKeyQ07Read[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQTimeover
extern char sTalkKeyQTimeover[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQNo
extern char sTalkKeyQNo[5];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEtcCancel
extern char sTalkKeyEtcCancel[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Report
extern char sTalkKeyQ06Report[11];
#endif
#ifndef PROTO_LOCAL_sTsuTopicWeightsWork
extern u8 sTsuTopicWeightsWork[14];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuSeHint
extern char sTalkKeyTsuSeHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Open3
extern char sTalkKeyQ06Open3[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Req1
extern char sTalkKeyQ01Req1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Open2
extern char sTalkKeyQ07Open2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Fin
extern char sTalkKeyQ07Fin[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Con
extern char sTalkKeyQ06Con[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Req3
extern char sTalkKeyQ01Req3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Report
extern char sTalkKeyQ07Report[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Bad
extern char sTalkKeyQ06Bad[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Normal
extern char sTalkKeyQ06Normal[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvSnowfes
extern char sTalkKeyEvSnowfes[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Req3
extern char sTalkKeyQ03Req3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Con
extern char sTalkKeyQ07Con[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Req245
extern char sTalkKeyQ02Req245[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Con3
extern char sTalkKeyQ01Con3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuMove1
extern char sTalkKeyTsuMove1[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Req12
extern char sTalkKeyQ03Req12[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuInAct
extern char sTalkKeyTsuInAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07End
extern char sTalkKeyQ07End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Pwin
extern char sTalkKeyQ01Pwin[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFiAct
extern char sTalkKeyTsuFiAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Req
extern char sTalkKeyQ05Req[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Pwin
extern char sTalkKeyQ02Pwin[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFoAct
extern char sTalkKeyTsuFoAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiFirst
extern char sTalkKeyAiFirst[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Plose
extern char sTalkKeyQ01Plose[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Plose
extern char sTalkKeyQ02Plose[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQStart
extern char sTalkKeyQStart[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Talk35
extern char sTalkKeyQ05Talk35[12];
#endif
#ifndef PROTO_LOCAL_sDeliveryMinutes
extern u8 sDeliveryMinutes[3];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvGardeniing
extern char sTalkKeyEvGardeniing[14];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Pdraw
extern char sTalkKeyQ01Pdraw[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAi7days
extern char sTalkKeyAi7days[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Con45
extern char sTalkKeyQ03Con45[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQTime
extern char sTalkKeyQTime[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Talk67
extern char sTalkKeyQ05Talk67[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiShop2
extern char sTalkKeyAiShop2[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiFlea
extern char sTalkKeyAiFlea[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Con37
extern char sTalkKeyQ04Con37[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiPassword
extern char sTalkKeyAiPassword[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFlAct
extern char sTalkKeyTsuFlAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Con3
extern char sTalkKeyQ03Con3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvKaraoke
extern char sTalkKeyEvKaraoke[11];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pBo
extern char sTalkKey3pBo[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEtcHit
extern char sTalkKeyEtcHit[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQFull
extern char sTalkKeyQFull[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04End
extern char sTalkKeyQ04End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03End
extern char sTalkKeyQ03End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Nlose
extern char sTalkKeyQ01Nlose[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiSnow2
extern char sTalkKeyAiSnow2[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApHabit
extern char sTalkKeyApHabit[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApNickn
extern char sTalkKeyApNickn[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Revenge
extern char sTalkKeyQ02Revenge[12];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pFu
extern char sTalkKey3pFu[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiToday2
extern char sTalkKeyAiToday2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Con245
extern char sTalkKeyQ02Con245[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Comp
extern char sTalkKeyQ01Comp[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Return
extern char sTalkKeyQ02Return[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05End
extern char sTalkKeyQ05End[8];
#endif
#ifndef PROTO_LOCAL_Talk_PickRandomMemory
void *Talk_PickRandomMemory(void *ctx, void **arr, s32 n, BOOL (*cb)(void *, void *));
#endif
#ifndef PROTO_LOCAL_Talk_GetDaysSinceMemoryTime
s32 Talk_GetDaysSinceMemoryTime(void *item);
#endif
#ifndef PROTO_LOCAL_Talk_IsMemoryLikedAndOld
BOOL Talk_IsMemoryLikedAndOld(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_IsMemoryDislikedAndOld
BOOL Talk_IsMemoryDislikedAndOld(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_IsMemoryLetterSender
s32 Talk_IsMemoryLetterSender(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_IsMemoryLetterSenderFromVillagerTown
BOOL Talk_IsMemoryLetterSenderFromVillagerTown(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_MemoryHasCompliment
BOOL Talk_MemoryHasCompliment(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_IsMemoryLetterSenderResident
BOOL Talk_IsMemoryLetterSenderResident(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_MemoryHasTime
BOOL Talk_MemoryHasTime(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_MemoryAny
BOOL Talk_MemoryAny(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_Talk_MemoryHasReceivedItem
BOOL Talk_MemoryHasReceivedItem(void *ctx, void *item);
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02End
extern char sTalkKeyQ02End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Comp
extern char sTalkKeyQ05Comp[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvFishing
extern char sTalkKeyEvFishing[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiSad
extern char sTalkKeyAiSad[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvArbeit
extern char sTalkKeyEvArbeit[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ12Full
extern char sTalkKeyQ12Full[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ12Other
extern char sTalkKeyQ12Other[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiBee
extern char sTalkKeyAiBee[7];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Over
extern char sTalkKeyQ06Over[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Open
extern char sTalkKeyQ06Open[9];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pGe
extern char sTalkKey3pGe[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Mailgo
extern char sTalkKeyQ07Mailgo[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Open
extern char sTalkKeyQ07Open[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQError1
extern char sTalkKeyQError1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvAcorn
extern char sTalkKeyEvAcorn[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFuHint
extern char sTalkKeyTsuFuHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Req
extern char sTalkKeyQ06Req[8];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pHa
extern char sTalkKey3pHa[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ12End
extern char sTalkKeyQ12End[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Joy
extern char sTalkKeyQ07Joy[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFlHint
extern char sTalkKeyTsuFlHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Good
extern char sTalkKeyQ06Good[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ10Con
extern char sTalkKeyQ10Con[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ10Leave
extern char sTalkKeyQ10Leave[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Req1
extern char sTalkKeyQ02Req1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Req3
extern char sTalkKeyQ02Req3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Con1
extern char sTalkKeyQ02Con1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Req45
extern char sTalkKeyQ03Req45[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Req12
extern char sTalkKeyQ04Req12[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuNoHint
extern char sTalkKeyTsuNoHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Pwin2
extern char sTalkKeyQ01Pwin2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Con3
extern char sTalkKeyQ02Con3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvBirth
extern char sTalkKeyEvBirth[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Nwin
extern char sTalkKeyQ02Nwin[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ03Con12
extern char sTalkKeyQ03Con12[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Pwin2
extern char sTalkKeyQ02Pwin2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ02Pdraw
extern char sTalkKeyQ02Pdraw[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Con
extern char sTalkKeyQ05Con[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiShop1
extern char sTalkKeyAiShop1[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiNfirst
extern char sTalkKeyAiNfirst[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Revenge
extern char sTalkKeyQ01Revenge[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuGhint
extern char sTalkKeyTsuGhint[10];
#endif
#ifndef PROTO_LOCAL_sTalkKey3pKo
extern char sTalkKey3pKo[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiFortune
extern char sTalkKeyAiFortune[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01End
extern char sTalkKeyQ01End[8];
#endif
#ifndef PROTO_LOCAL_data_020d7860
extern u8 data_020d7860[2];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvFirework
extern char sTalkKeyEvFirework[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Return
extern char sTalkKeyQ01Return[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Dress
extern char sTalkKeyQ04Dress[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEtcConnect
extern char sTalkKeyEtcConnect[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Fin
extern char sTalkKeyQ06Fin[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Req
extern char sTalkKeyQ07Req[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ12Report
extern char sTalkKeyQ12Report[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFiHint
extern char sTalkKeyTsuFiHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQIcancel
extern char sTalkKeyQIcancel[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ10Reserved
extern char sTalkKeyQ10Reserved[13];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQError2
extern char sTalkKeyQError2[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Con1
extern char sTalkKeyQ01Con1[9];
#endif
#ifndef PROTO_LOCAL_Talk_GetTourneyHourBlock
u32 Talk_GetTourneyHourBlock(u32 x);
#endif
#ifndef PROTO_LOCAL_Talk_IsAcornItem
BOOL Talk_IsAcornItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Talk_AcornPickerFilter
BOOL Talk_AcornPickerFilter(u16 *p, s32 a);
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ01Nwin
extern char sTalkKeyQ01Nwin[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApItem
extern char sTalkKeyApItem[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiAnger
extern char sTalkKeyAiAnger[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiShop3
extern char sTalkKeyAiShop3[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiPoison
extern char sTalkKeyAiPoison[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiRain2
extern char sTalkKeyAiRain2[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuItem
extern char sTalkKeyTsuItem[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiRun
extern char sTalkKeyAiRun[7];
#endif
#ifndef PROTO_LOCAL_VillagerMood_Construct
void *VillagerMood_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_VillagerMood_Destruct
void *VillagerMood_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Scold
extern char sTalkKeyQ07Scold[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ07Show
extern char sTalkKeyQ07Show[9];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQPreitem
extern char sTalkKeyQPreitem[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ04Req37
extern char sTalkKeyQ04Req37[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuClAct
extern char sTalkKeyTsuClAct[11];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQYes
extern char sTalkKeyQYes[6];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuInHint
extern char sTalkKeyTsuInHint[12];
#endif
#ifndef PROTO_LOCAL_sVillagerClothMaterialName
extern char sVillagerClothMaterialName[2];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuMove2
extern char sTalkKeyTsuMove2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyApMail
extern char sTalkKeyApMail[8];
#endif
#ifndef PROTO_LOCAL_sTalkKeyEvInsect
extern char sTalkKeyEvInsect[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyTsuFoHint
extern char sTalkKeyTsuFoHint[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ05Talk12
extern char sTalkKeyQ05Talk12[12];
#endif
#ifndef PROTO_LOCAL_sTalkKeyQ06Open2
extern char sTalkKeyQ06Open2[10];
#endif
#ifndef PROTO_LOCAL_sTalkKeyAiMfirst
extern char sTalkKeyAiMfirst[10];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_020d7c10
extern decltype (& VillagerTalk :: playOwnerIdleAnim) data_020d7c10;
#endif
#ifndef PROTO_LOCAL_TalkChoiceList_SetIndices
void TalkChoiceList_SetIndices(ActorTalkRequest *a, u8 *src, s32 n, s32 m);
#endif
#ifndef PROTO_LOCAL_Npc_GetStateHeldItem
void Npc_GetStateHeldItem(u16 *out, VillagerActor *obj);
#endif
#ifndef PROTO_LOCAL_VillagerTalk_EnsureMemory
void VillagerTalk_EnsureMemory(VillagerTalk *self, void **pa, s32 *pb, void *c, void *d);
#endif
#ifndef PROTO_LOCAL_Talk_FindLetterState7or8
LetterView *Talk_FindLetterState7or8(void *p);
#endif
#ifndef PROTO_LOCAL_Talk_PickItemFromSpecs
void Talk_PickItemFromSpecs(u16 *out, const u32 *tbl, s32 idx, PlayerData *player);
#endif
#ifndef PROTO_LOCAL_Talk_PickErrandItem
void Talk_PickErrandItem(u16 *out, PlayerData *player);
#endif
#ifndef PROTO_LOCAL_Talk_PickClothingItem
void Talk_PickClothingItem(u16 *out, PlayerData *player);
#endif
#ifndef PROTO_LOCAL_Talk_FindNearbyInsectOfKinds
s32 Talk_FindNearbyInsectOfKinds(VecFx32Ctor *a, const s8 *b, s32 c, VecFx32 *d, s32 e);
#endif
#ifndef PROTO_LOCAL_Talk_IsCatchPlanDue
s32 Talk_IsCatchPlanDue(VillagerActor *a, PlanErrand *b, ClockDateTimeWords *y, u32 flag);
#endif
#ifndef PROTO_LOCAL_Talk_UpdateInsectCatchPlan
void Talk_UpdateInsectCatchPlan(VillagerActor *a, PlanErrand *b, u8 *arr, void *c, u8 flag, ClockDateTimeWords *rec);
#endif
#ifndef PROTO_LOCAL_data_020d7ad0
extern decltype (& VillagerMood :: updateMood3Effects) data_020d7ad0;
#endif
#ifndef PROTO_LOCAL_data_020d7c78
extern decltype (& VillagerTalkRequestItemTopics :: clearRequest) data_020d7c78;
#endif
#ifndef PROTO_LOCAL_data_020d7da0
extern decltype (& VillagerTalkRequestItemTopics :: finishRequestChain) data_020d7da0;
#endif
#ifndef PROTO_LOCAL_data_020d7c48
extern decltype (& VillagerTalk :: attrPlayMemoryTune) data_020d7c48;
#endif
#ifndef PROTO_LOCAL_data_020d7a38
extern decltype (& VillagerMood :: beginMood2Effects) data_020d7a38;
#endif
#ifndef PROTO_LOCAL_data_020d7a30
extern decltype (& VillagerTalk :: attrShowLetter) data_020d7a30;
#endif
#ifndef PROTO_LOCAL_data_020d7b28
extern decltype (& VillagerTalk :: attrGiveItem) data_020d7b28;
#endif
#ifndef PROTO_LOCAL_data_020d7aa0
extern decltype (& VillagerTalk :: playOwnerIdleAnim) data_020d7aa0;
#endif
#ifndef PROTO_LOCAL_data_020d79a0
extern decltype (& VillagerTalk :: setConstellationSlots) data_020d79a0;
#endif
#ifndef PROTO_LOCAL_data_020d7c98
extern decltype (& VillagerTalk :: swapItemWithPlayer) data_020d7c98;
#endif
#ifndef PROTO_LOCAL_Talk_MakeRandomNickname
BOOL Talk_MakeRandomNickname(MsgString *a, MsgString *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Talk_GetWantedFossilPocketMask
u32 Talk_GetWantedFossilPocketMask(PlanErrand *h);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickShirtForStep
void VillagerRequest_PickShirtForStep(u16 *out, VillagerTalkRequestStartTopics *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickRandomFossil
void VillagerRequest_PickRandomFossil(u16 *out, PlanErrand *, void *);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFossilOfGroup
void VillagerRequest_PickFossilOfGroup(u16 *out, PlanErrand *a, void *b);
#endif
#ifndef PROTO_LOCAL_VillagerRequest_PickFossilForStep
void VillagerRequest_PickFossilForStep(u16 *out, VillagerTalkRequestStartTopics *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_data_020d7c50
extern decltype (& VillagerTalk :: attrShowLetter) data_020d7c50;
#endif
#ifndef PROTO_LOCAL_data_020d8008
extern decltype (& VillagerTalk :: playOwnerIdleAnim) data_020d8008;
#endif
#ifndef PROTO_LOCAL_data_020d7bd0
extern decltype (& VillagerTalk :: setHiraganaOn) data_020d7bd0;
#endif
#ifndef PROTO_LOCAL_data_020d7f38
extern decltype (& VillagerTalk :: showMoneyItem) data_020d7f38;
#endif
#ifndef PROTO_LOCAL_sHouseVisitTsuTopicTable
extern VillagerTalkTopicFns sHouseVisitTsuTopicTable[3];
#endif
#ifndef PROTO_LOCAL_data_020d7eb0
extern decltype (& VillagerTalkRequestStartTopics :: registerRequestDeclined) data_020d7eb0;
#endif
#ifndef PROTO_LOCAL_data_020d7e80
extern decltype (& VillagerMood :: updateMood1Effects) data_020d7e80;
#endif
#ifndef PROTO_LOCAL_data_020d7b90
extern decltype (& VillagerTalk :: receiveItemB) data_020d7b90;
#endif
#ifndef PROTO_LOCAL_data_020d7d50
extern decltype (& VillagerTalk :: runCustomFn2) data_020d7d50;
#endif
#ifndef PROTO_LOCAL_data_020d7d30
extern decltype (& VillagerTalk :: sellItemToPlayer) data_020d7d30;
#endif
#ifndef PROTO_LOCAL_data_020d7a20
extern decltype (& VillagerTalk :: runCustomFn0) data_020d7a20;
#endif
#ifndef PROTO_LOCAL_data_020d7e08
extern decltype (& VillagerMood :: updateMood2Effects) data_020d7e08;
#endif
#ifndef PROTO_LOCAL_data_020d7cf0
extern decltype (& VillagerTalk :: runCustomFn3) data_020d7cf0;
#endif
#ifndef PROTO_LOCAL_data_020d7940
extern decltype (& VillagerTalk :: playOwnerIdleAnim) data_020d7940;
#endif
#ifndef PROTO_LOCAL_data_020d7fe8
extern decltype (& VillagerTalk :: playOwnerIdleAnim) data_020d7fe8;
#endif
#ifndef PROTO_LOCAL_data_020d7b68
extern decltype (& VillagerMood :: beginMood3Effects) data_020d7b68;
#endif
#ifndef PROTO_LOCAL_data_020d7ee8
extern decltype (& VillagerTalk :: attrShowLetter) data_020d7ee8;
#endif
#ifndef PROTO_LOCAL_sTalkBeginTopics
extern VillagerTalkTopicFns sTalkBeginTopics[17];
#endif
#ifndef PROTO_LOCAL_data_020d7df8
extern decltype (& VillagerTalk :: runCustomFn4) data_020d7df8;
#endif
#ifndef PROTO_LOCAL_data_020d7b00
extern decltype (& VillagerTalk :: attrOpenBirthdayEntry) data_020d7b00;
#endif
#ifndef PROTO_LOCAL_data_020d7ae0
extern decltype (& VillagerTalk :: giveItemToPlayer) data_020d7ae0;
#endif
#ifndef PROTO_LOCAL_data_020d7cf8
extern decltype (& VillagerTalkRequestItemTopics :: gotoQClearOrEnd) data_020d7cf8;
#endif
#ifndef PROTO_LOCAL_data_020d7cb0
extern decltype (& VillagerTalk :: buyItemFromPlayer) data_020d7cb0;
#endif
#ifndef PROTO_LOCAL_TalkChoiceTable_Init
void TalkChoiceTable_Init(void *a, TalkChoiceTable *t);
#endif
#ifndef PROTO_LOCAL_TalkChoiceTable_Set
void TalkChoiceTable_Set(void *a, TalkChoiceTable *t, u32 i, u8 lo, u8 hi, VillagerTalkTopicFns *val);
#endif
#ifndef PROTO_LOCAL_TalkChoiceTable_SetRange
void TalkChoiceTable_SetRange(void *a, TalkChoiceTable *t, u32 i, const u8 *r, VillagerTalkTopicFns *val);
#endif
#ifndef PROTO_LOCAL_data_020d7fd8
extern decltype (& VillagerTalk :: setHiraganaOff) data_020d7fd8;
#endif
#ifndef PROTO_LOCAL_data_020d7bb8
extern decltype (& VillagerTalk :: receiveItem) data_020d7bb8;
#endif
#ifndef PROTO_LOCAL_data_020d7af0
extern decltype (& VillagerTalk :: runCustomFn1) data_020d7af0;
#endif
#ifndef PROTO_LOCAL_data_020d7e68
extern decltype (& VillagerMood :: beginMood1Effects) data_020d7e68;
#endif
#ifndef PROTO_LOCAL_data_020d7bf0
extern decltype (& VillagerMood :: beginMood2Effects) data_020d7bf0;
#endif
#ifndef PROTO_LOCAL_data_020d7ec8
extern decltype (& VillagerTalkRequestStartTopics :: registerRequestDeferred) data_020d7ec8;
#endif
#ifndef PROTO_LOCAL_NpcActor_JointCalcLayer3Cb
void NpcActor_JointCalcLayer3Cb(NNSG3dRS *p);
#endif
}
#endif

#endif
