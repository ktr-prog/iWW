#ifndef PROTO_PROTO_MAIN_UNK_02095CDC_H
#define PROTO_PROTO_MAIN_UNK_02095CDC_H


#include "types.h"
#include "item/MotherLetterDate.h"
#ifdef __cplusplus
#include "item/Letter.h"
class PlayerData;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_LetterDelivery_DeliverOutgoing
s32 LetterDelivery_DeliverOutgoing(void);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_IsMailboxFull
BOOL LetterDelivery_IsMailboxFull(s32 idx);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_PostOfficeClosedNop
void LetterDelivery_PostOfficeClosedNop(void);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_HasFreeOutgoingSlot
s32 LetterDelivery_HasFreeOutgoingSlot(void);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_Update
void LetterDelivery_Update(void);
#endif
#ifndef PROTO_LOCAL_LetterPaper_PickRandom
u8 LetterPaper_PickRandom(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LetterPaper_PickForPersonality
u8 LetterPaper_PickForPersonality(u32 i);
#endif
#ifndef PROTO_LOCAL_LetterPaper_PickForMonth
u8 LetterPaper_PickForMonth(u32 x);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_DeliverReceivedLetter
void LetterDelivery_DeliverReceivedLetter(void);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetMonthFirst
u32 MotherLetter_GetMonthFirst(u8 v);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetMonthCount
u8 MotherLetter_GetMonthCount(u8 v);
#endif
#ifndef PROTO_LOCAL_MotherLetter_ResetOtherMonths
void MotherLetter_ResetOtherMonths(s32 x);
#endif
#ifndef PROTO_LOCAL_MotherLetter_CountUnsent
s32 MotherLetter_CountUnsent(s32 a, s32 n);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetNthUnsent
s32 MotherLetter_GetNthUnsent(s32 a, s32 n, s32 k);
#endif
#ifndef PROTO_LOCAL_MotherLetter_ClearSent
void MotherLetter_ClearSent(s32 a, s32 n);
#endif
#ifndef PROTO_LOCAL_MotherLetter_SendRandomUnsent
s32 MotherLetter_SendRandomUnsent(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_MotherLetter_Send
s32 MotherLetter_Send(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetFileName
const char *MotherLetter_GetFileName(s32 a);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetPresent
u16 MotherLetter_GetPresent(s32 code);
#endif
#ifndef PROTO_LOCAL_MotherLetter_GetMsgIndex
u8 MotherLetter_GetMsgIndex(s32 x);
#endif
#ifndef PROTO_LOCAL_BottleLetter_Open
s32 BottleLetter_Open();
#endif
#ifndef PROTO_LOCAL_BottleLetter_CreateGameLetter
s32 BottleLetter_CreateGameLetter(u8 *p);
#endif
#ifndef PROTO_LOCAL_BottleLetter_PlaceBottle
s32 BottleLetter_PlaceBottle();
#endif
#ifndef PROTO_LOCAL_BottleLetter_IsBottleInTown
s32 BottleLetter_IsBottleInTown();
#endif
#ifndef PROTO_LOCAL_BottleLetter_OnNewDay
void BottleLetter_OnNewDay(s32 a);
#endif
#ifndef PROTO_LOCAL_BottleLetter_WashUpThrownBottle
void BottleLetter_WashUpThrownBottle();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_LetterDelivery_PutInMailbox
BOOL LetterDelivery_PutInMailbox(Letter *e, s32 idx, u32 flag);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_PutInAddresseeMailbox
BOOL LetterDelivery_PutInAddresseeMailbox(Letter *e);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_SendToVillager
void LetterDelivery_SendToVillager(Letter *e);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_QueueOutgoing
BOOL LetterDelivery_QueueOutgoing(Letter *e, BOOL flag);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_HasKnownAddressee
BOOL LetterDelivery_HasKnownAddressee(Letter *e);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_FindAddresseePlayer
s32 LetterDelivery_FindAddresseePlayer(Letter *letter);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_FindAddresseeVillager
s32 LetterDelivery_FindAddresseeVillager(Letter *letter);
#endif
#ifndef PROTO_LOCAL_LetterList_Compact
s32 LetterList_Compact(Letter *base, s32 n);
#endif
#ifndef PROTO_LOCAL_LetterList_CountUsed
s32 LetterList_CountUsed(Letter *base, s32 n);
#endif
#ifndef PROTO_LOCAL_LetterDelivery_HasFutureLetter
s32 LetterDelivery_HasFutureLetter(PlayerData *p);
#endif
#ifndef PROTO_LOCAL_MotherLetter_OnNewDay
void MotherLetter_OnNewDay(Unk_02096354_Arg *p, s32 n);
#endif
#ifndef PROTO_LOCAL_MotherLetter_TrySendBirthday
s32 MotherLetter_TrySendBirthday(Unk_02096354_Arg *p);
#endif
#ifndef PROTO_LOCAL_MotherLetter_TrySendHoliday
s32 MotherLetter_TrySendHoliday(Unk_02096354_Arg *p);
#endif
#ifndef PROTO_LOCAL_MotherLetter_TrySendRandom
s32 MotherLetter_TrySendRandom(Unk_02096354_Arg *p);
#endif
}
#ifndef PROTO_LOCAL_sMotherMonthLetterCount
extern u8 sMotherMonthLetterCount[0xc];
#endif
#ifndef PROTO_LOCAL_sMotherMonthLetterFirst
extern u8 sMotherMonthLetterFirst[0xc];
#endif
#endif

#endif
