#ifndef PROTO_PROTO_MAIN_UNK_02065330_H
#define PROTO_PROTO_MAIN_UNK_02065330_H


#include "types.h"
struct LetterDefaults;
#ifndef __cplusplus
typedef struct LetterDefaults LetterDefaults;
#endif
#ifdef __cplusplus
#include "item/LetterView.h"
#include "npc/VillagerId.h"
#include "player/PlayerId.h"
#include "talk/MsgString.h"
#include "talk/MsgString129.h"
#include "talk/MsgString25B.h"
#include "talk/MsgString33B.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Letter_LoadTemplate2d
void Letter_LoadTemplate2d(u8 *code, u8 *dst, u8 *lenOut, u8 *extra);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Letter_Copy
LetterView *Letter_Copy(LetterView *self, const LetterView *src);
#endif
#ifndef PROTO_LOCAL_LetterParty_GetNameBytes
void LetterParty_GetNameBytes(LetterParty *self, u8 *out);
#endif
#ifndef PROTO_LOCAL_LetterParty_GetName
void LetterParty_GetName(LetterParty *self, MsgString *out);
#endif
#ifndef PROTO_LOCAL_LetterParty_AsPlayer
LetterParty *LetterParty_AsPlayer(LetterParty *self);
#endif
#ifndef PROTO_LOCAL_LetterParty_AsVillager
LetterParty *LetterParty_AsVillager(LetterParty *self);
#endif
#ifndef PROTO_LOCAL_LetterParty_SetVillager
void LetterParty_SetVillager(LetterParty *self, VillagerId *src);
#endif
#ifndef PROTO_LOCAL_LetterParty_SetPlayer
void LetterParty_SetPlayer(LetterParty *self, PlayerId *src);
#endif
#ifndef PROTO_LOCAL_LetterParty_SetFutureSelf
void LetterParty_SetFutureSelf(LetterParty *self, PlayerId *src);
#endif
#ifndef PROTO_LOCAL_LetterParty_SetBottle
void LetterParty_SetBottle(LetterParty *self);
#endif
#ifndef PROTO_LOCAL_LetterParty_SetType
void LetterParty_SetType(LetterParty *self, u32 v);
#endif
#ifndef PROTO_LOCAL_LetterParty_IsType
u32 LetterParty_IsType(LetterParty *self, u32 t);
#endif
#ifndef PROTO_LOCAL_Letter_Clear
void Letter_Clear(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetPaper
u32 Letter_GetPaper(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_InitDraft
void Letter_InitDraft(LetterView *self, u32 v);
#endif
#ifndef PROTO_LOCAL_Letter_InitBottleDraft
void Letter_InitBottleDraft(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_SetRecipientVillager
void Letter_SetRecipientVillager(LetterView *self, s32 idx);
#endif
#ifndef PROTO_LOCAL_Letter_SetRecipientResident
void Letter_SetRecipientResident(LetterView *self, s32 idx);
#endif
#ifndef PROTO_LOCAL_Letter_SetRecipientFutureSelf
void Letter_SetRecipientFutureSelf(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_MarkSent
void Letter_MarkSent(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_MarkRead
void Letter_MarkRead(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_MarkReceived
void Letter_MarkReceived(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_SetTexts
void Letter_SetTexts(LetterView *self, s32 *pv, MsgString *a, MsgString *b, MsgString *c);
#endif
#ifndef PROTO_LOCAL_Letter_FillFromVillager
void Letter_FillFromVillager(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const u8 *ped, VillagerId *s1, PlayerId *s2);
#endif
#ifndef PROTO_LOCAL_Letter_ComposeVillagerMail
void Letter_ComposeVillagerMail(LetterView *self, const u8 *a1, const char *a2, const u8 *a3, VillagerId *a4, PlayerId *a5, s32 a6);
#endif
#ifndef PROTO_LOCAL_Letter_ComposeVillagerMailZ
void Letter_ComposeVillagerMailZ(LetterView *self, u8 *a1, u8 *a2, u8 *a3, u8 *a4, const char *a5, const u8 *a6, VillagerId *a7, PlayerId *a8, s32 a9);
#endif
#ifndef PROTO_LOCAL_Letter_FillVillagerToVillager
void Letter_FillVillagerToVillager(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const u8 *ped, VillagerId *s1, VillagerId *s2);
#endif
#ifndef PROTO_LOCAL_Letter_ComposeVillagerToVillagerZ
void Letter_ComposeVillagerToVillagerZ(LetterView *self, u8 *a1, u8 *a2, u8 *a3, u8 *a4, const char *a5, const u8 *a6, VillagerId *a7, VillagerId *a8, s32 a9);
#endif
#ifndef PROTO_LOCAL_Letter_FillSystemMail
void Letter_FillSystemMail(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const void *kind, const void *paper, PlayerId *player);
#endif
#ifndef PROTO_LOCAL_Letter_ComposeFromMail
void Letter_ComposeFromMail(LetterView *self, const u8 *msgIndex, const char *fileName, const void *kind, const void *paper, PlayerId *player);
#endif
#ifndef PROTO_LOCAL_Letter_FillBottleMail
void Letter_FillBottleMail(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v);
#endif
#ifndef PROTO_LOCAL_Letter_ComposeBottleMail
void Letter_ComposeBottleMail(LetterView *self, const u8 *a, const char *b);
#endif
#ifndef PROTO_LOCAL_Letter_GetSenderPlayer
LetterParty *Letter_GetSenderPlayer(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetRecipientPlayer
LetterParty *Letter_GetRecipientPlayer(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetRecipientVillager
LetterParty *Letter_GetRecipientVillager(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetSenderNameBytes
void Letter_GetSenderNameBytes(LetterView *self, u8 *out);
#endif
#ifndef PROTO_LOCAL_Letter_GetRecipientNameBytes
void Letter_GetRecipientNameBytes(LetterView *self, u8 *out);
#endif
#ifndef PROTO_LOCAL_Letter_GetKind
u32 Letter_GetKind(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_GetSenderName
void Letter_GetSenderName(LetterView *self, MsgString *out);
#endif
#ifndef PROTO_LOCAL_Letter_GetRecipientName
void Letter_GetRecipientName(LetterView *self, MsgString *out);
#endif
#ifndef PROTO_LOCAL_Letter_IsBottle
u32 Letter_IsBottle(LetterView *self);
#endif
#ifndef PROTO_LOCAL_Letter_SetSignature
void Letter_SetSignature(LetterView *o, u8 *p);
#endif
#ifndef PROTO_LOCAL_LetterDefaults_Store
void LetterDefaults_Store(LetterDefaults *a, LetterView *b);
#endif
}
#ifndef PROTO_LOCAL_sMailGreeting
extern MsgString25B sMailGreeting;
#endif
#ifndef PROTO_LOCAL_sMailBody
extern MsgString129 sMailBody;
#endif
#ifndef PROTO_LOCAL_sMailSignature
extern MsgString33B sMailSignature;
#endif
#endif

#endif
