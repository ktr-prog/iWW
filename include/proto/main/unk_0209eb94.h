#ifndef PROTO_PROTO_MAIN_UNK_0209EB94_H
#define PROTO_PROTO_MAIN_UNK_0209EB94_H


#include "types.h"
#include "sys/ProcProfile.h"
struct GuestSlotTriple;
#ifndef __cplusplus
typedef struct GuestSlotTriple GuestSlotTriple;
#endif
#ifdef __cplusplus
#include "save/BlancaFaceRecord.h"
#include "save/SaveManager.h"
#include "save/SaveRecord4.h"
#include "save/TownCompress.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Save_StoreCurrentPlayerToResident
void Save_StoreCurrentPlayerToResident(void);
#endif
#ifndef PROTO_LOCAL_Save_LoadSync
s32 Save_LoadSync(void);
#endif
#ifndef PROTO_LOCAL_Save_CheckSlot
s32 Save_CheckSlot(s32 idx);
#endif
#ifndef PROTO_LOCAL_Save_ReadAndCheckSlot
s32 Save_ReadAndCheckSlot(s32 idx, s32 flag);
#endif
#ifndef PROTO_LOCAL_Save_ReadSlot
BOOL Save_ReadSlot(u32 idx);
#endif
#ifndef PROTO_LOCAL_Save_ReadSlotSync
BOOL Save_ReadSlotSync(u32 idx, s32 flag);
#endif
#ifndef PROTO_LOCAL_Save_ReadSlotAsyncStep
s32 Save_ReadSlotAsyncStep(s32 idx, u8 *buf);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct01
void SaveManager_RequestAct01(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct02
void SaveManager_RequestAct02(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct06
void SaveManager_RequestAct06(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct05
void SaveManager_RequestAct05(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct03
void SaveManager_RequestAct03(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct12
void SaveManager_RequestAct12(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct13
void SaveManager_RequestAct13(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct14
void SaveManager_RequestAct14(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct15
void SaveManager_RequestAct15(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct16
void SaveManager_RequestAct16(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct17
void SaveManager_RequestAct17(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct18
void SaveManager_RequestAct18(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct19
void SaveManager_RequestAct19(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct1A
void SaveManager_RequestAct1A(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct1B
void SaveManager_RequestAct1B(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct1F
void SaveManager_RequestAct1F(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_RequestAct1C
void SaveManager_RequestAct1C(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_IsIdle
BOOL SaveManager_IsIdle(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_HasAct12Failed
BOOL SaveManager_HasAct12Failed(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_IsIdleForRoom
BOOL SaveManager_IsIdleForRoom(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_IsIdleAfterAct13
BOOL SaveManager_IsIdleAfterAct13();
#endif
#ifndef PROTO_LOCAL_SaveManager_HasAct13Failed
BOOL SaveManager_HasAct13Failed();
#endif
#ifndef PROTO_LOCAL_SaveManager_IsIdleAfterAct1F
BOOL SaveManager_IsIdleAfterAct1F();
#endif
#ifndef PROTO_LOCAL_SaveManager_HasAct1FFailed
BOOL SaveManager_HasAct1FFailed();
#endif
#ifndef PROTO_LOCAL_Save_CheckFooterReadError
BOOL Save_CheckFooterReadError(s32 idx);
#endif
#ifndef PROTO_LOCAL_Save_CheckBackupError
BOOL Save_CheckBackupError();
#endif
#ifndef PROTO_LOCAL_Save_SlotStampsMatch
BOOL Save_SlotStampsMatch();
#endif
#ifndef PROTO_LOCAL_Save_InvalidateLetterStorage
BOOL Save_InvalidateLetterStorage();
#endif
#ifndef PROTO_LOCAL_Save_InvalidateAll
BOOL Save_InvalidateAll();
#endif
#ifndef PROTO_LOCAL_Save_WritePlayerWifiData
BOOL Save_WritePlayerWifiData();
#endif
#ifndef PROTO_LOCAL_Save_WritePlayerFriendList
BOOL Save_WritePlayerFriendList();
#endif
#ifndef PROTO_LOCAL_Save_WriteVillagerTransfer
BOOL Save_WriteVillagerTransfer();
#endif
#ifndef PROTO_LOCAL_GameStart_SetupSave
void GameStart_SetupSave();
#endif
#ifndef PROTO_LOCAL_SaveManager_SetEraseResidentSlot
void SaveManager_SetEraseResidentSlot(s32 v);
#endif
#ifndef PROTO_LOCAL_Net_GetJoiningAid
u32 Net_GetJoiningAid();
#endif
#ifndef PROTO_LOCAL_Net_SetJoiningAid
void Net_SetJoiningAid(u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_GetTownTransferBuf
void *SaveManager_GetTownTransferBuf();
#endif
#ifndef PROTO_LOCAL_SaveManager_IsGatePassed
u32 SaveManager_IsGatePassed();
#endif
#ifndef PROTO_LOCAL_SaveManager_SetGatePassed
void SaveManager_SetGatePassed();
#endif
#ifndef PROTO_LOCAL_SaveManager_IsSessionJoined
u32 SaveManager_IsSessionJoined();
#endif
#ifndef PROTO_LOCAL_SaveManager_GetLetterStorage
u8 *SaveManager_GetLetterStorage();
#endif
#ifndef PROTO_LOCAL_GameStart_SetNewTown
void GameStart_SetNewTown();
#endif
#ifndef PROTO_LOCAL_GameStart_SetNewResident
void GameStart_SetNewResident();
#endif
#ifndef PROTO_LOCAL_GameStart_SetMode3
void GameStart_SetMode3();
#endif
#ifndef PROTO_LOCAL_GameStart_SetMode4
void GameStart_SetMode4();
#endif
#ifndef PROTO_LOCAL_GameStart_IsActive
BOOL GameStart_IsActive();
#endif
#ifndef PROTO_LOCAL_GameStart_IsNewTown
BOOL GameStart_IsNewTown();
#endif
#ifndef PROTO_LOCAL_GameStart_IsNewResident
BOOL GameStart_IsNewResident();
#endif
#ifndef PROTO_LOCAL_GameStart_IsMode3
BOOL GameStart_IsMode3();
#endif
#ifndef PROTO_LOCAL_GameStart_IsMode4
BOOL GameStart_IsMode4();
#endif
#ifndef PROTO_LOCAL_GameStart_Clear
void GameStart_Clear();
#endif
#ifndef PROTO_LOCAL_SaveManager_SetRecvAct03
void SaveManager_SetRecvAct03(u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct14Aid
void SaveManager_SetCtrlAct14Aid(u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_GetCtrlAct14Aid
u32 SaveManager_GetCtrlAct14Aid();
#endif
#ifndef PROTO_LOCAL_NetSession_ReturnToSolo
void NetSession_ReturnToSolo(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_VillagerTransfer_PlanSwap
void VillagerTransfer_PlanSwap(void *a);
#endif
#ifndef PROTO_LOCAL_VillagerTransfer_PlanRotate
void VillagerTransfer_PlanRotate(void *a);
#endif
#ifndef PROTO_LOCAL_Wifi_StoreFriendList
void Wifi_StoreFriendList(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_IsEndSessionSave
u8 SaveManager_IsEndSessionSave(void);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetEndSessionSave
void SaveManager_SetEndSessionSave(u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetSaveCorrupted
void SaveManager_SetSaveCorrupted(u32 v);
#endif
#ifndef PROTO_LOCAL_NetOverlay_LoadWireless
void NetOverlay_LoadWireless(void);
#endif
#ifndef PROTO_LOCAL_NetOverlay_LoadWifi
void NetOverlay_LoadWifi(void);
#endif
#ifndef PROTO_LOCAL_NetOverlay_Restore
void NetOverlay_Restore(void);
#endif
#ifndef PROTO_LOCAL_TownCompressThread_Main
void TownCompressThread_Main(void *arg);
#endif
#ifndef PROTO_LOCAL_Wifi_EndSession
s32 Wifi_EndSession(void);
#endif
#ifndef PROTO_LOCAL_GameStats_Upload
BOOL GameStats_Upload(void);
#endif
#ifndef PROTO_LOCAL_GameStats_Download
BOOL GameStats_Download(void);
#endif
#ifndef PROTO_LOCAL_AxMail_DownloadMail
BOOL AxMail_DownloadMail(void);
#endif
#ifndef PROTO_LOCAL_AxMail_DownloadBbs
BOOL AxMail_DownloadBbs(void);
#endif
#ifndef PROTO_LOCAL_GameStats_PollDownload
BOOL GameStats_PollDownload(void);
#endif
#ifndef PROTO_LOCAL_AxMail_PollMail
BOOL AxMail_PollMail(void);
#endif
#ifndef PROTO_LOCAL_AxMail_PollBbs
BOOL AxMail_PollBbs(void);
#endif
#ifndef PROTO_LOCAL_GameStats_PollUpload
BOOL GameStats_PollUpload(void);
#endif
#ifndef PROTO_LOCAL_GameStats_ApplyDownload
void GameStats_ApplyDownload(void);
#endif
#ifndef PROTO_LOCAL_AxMail_ApplyMail
void AxMail_ApplyMail(void);
#endif
#ifndef PROTO_LOCAL_AxMail_ApplyBbs
void AxMail_ApplyBbs();
#endif
#ifndef PROTO_LOCAL_JoinHistory_Push
void JoinHistory_Push(u32 v);
#endif
#ifndef PROTO_LOCAL_JoinHistory_Remove
void JoinHistory_Remove(u32 v);
#endif
#ifndef PROTO_LOCAL_JoinHistory_Clear
void JoinHistory_Clear();
#endif
#ifndef PROTO_LOCAL_JoinHistory_GetLatest
u32 JoinHistory_GetLatest();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SaveManager_Create
SaveManager *SaveManager_Create();
#endif
#ifndef PROTO_LOCAL_Save_ReadSlotFooter
s32 Save_ReadSlotFooter(s32 idx, SaveRecord4 *d);
#endif
#ifndef PROTO_LOCAL_SaveManager_GetTownCompressBuf
TownCompressBuffer *SaveManager_GetTownCompressBuf();
#endif
#ifndef PROTO_LOCAL_SaveManager_GetTownCompressThread
TownCompressThread *SaveManager_GetTownCompressThread();
#endif
#ifndef PROTO_LOCAL_SaveManager_Get
SaveManager *SaveManager_Get();
#endif
#ifndef PROTO_LOCAL_SaveManager_SetHostMemberMask
void SaveManager_SetHostMemberMask(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetHostDataIndex
void SaveManager_SetHostDataIndex(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetJoinDone
void SaveManager_SetJoinDone(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct12
void SaveManager_SetCtrlAct12(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetRecvAct07
void SaveManager_SetRecvAct07(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetJoinReady
void SaveManager_SetJoinReady(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetDateTimeReceived
void SaveManager_SetDateTimeReceived(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_GetHostDateTime
u8 *SaveManager_GetHostDateTime(SaveManager *p);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetRecvAct04
void SaveManager_SetRecvAct04(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetRecvAct02
void SaveManager_SetRecvAct02(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct0E
void SaveManager_SetCtrlAct0E(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_ClearCtrlAct0E
void SaveManager_ClearCtrlAct0E(SaveManager *p);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetRecvAct06
void SaveManager_SetRecvAct06(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct10
void SaveManager_SetCtrlAct10(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct11
void SaveManager_SetCtrlAct11(SaveManager *p, s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_SaveManager_SetCtrlAct17
void SaveManager_SetCtrlAct17(SaveManager *p, u32 v);
#endif
#ifndef PROTO_LOCAL_LostChild_ResetAndPairLast
void LostChild_ResetAndPairLast(SaveManager *a);
#endif
#ifndef PROTO_LOCAL_LostChild_ResetAndPairAll
void LostChild_ResetAndPairAll(SaveManager *self);
#endif
#ifndef PROTO_LOCAL_LostChild_DebugPrint
void LostChild_DebugPrint(SaveManager *p, void *q);
#endif
#ifndef PROTO_LOCAL_LostChild_TryPair
void LostChild_TryPair(SaveManager *self, s32 idx);
#endif
#ifndef PROTO_LOCAL_Wifi_IsInFriendList
BOOL Wifi_IsInFriendList(SaveManager *self, void *a, void *b);
#endif
#ifndef PROTO_LOCAL_LostChild_ApplyReceived
void LostChild_ApplyReceived(SaveManager *self);
#endif
#ifndef PROTO_LOCAL_VillagerTransfer_SendReplies
BOOL VillagerTransfer_SendReplies(SaveManager *self);
#endif
#ifndef PROTO_LOCAL_SaveManager_RunSessionEnd
s32 SaveManager_RunSessionEnd(SaveManager *self, u8 *st, s32 base, s32 base2, u32 mask, u8 a6);
#endif
#ifndef PROTO_LOCAL_SaveManager_RunSyncedSaveHost
s32 SaveManager_RunSyncedSaveHost(SaveManager *self, u8 *st, s32 a2, s32 base, u8 a5, u8 a6, s32 a7, u8 a8, u32 a9);
#endif
#ifndef PROTO_LOCAL_SaveManager_StartGatekeeperTalk
void SaveManager_StartGatekeeperTalk(SaveManager *a, u32 b);
#endif
#ifndef PROTO_LOCAL_SaveManager_StartSequence2Talk
void SaveManager_StartSequence2Talk(SaveManager *a);
#endif
}
#ifndef PROTO_LOCAL_sAxMailBuf
extern AxMail sAxMailBuf;
#endif
#ifndef PROTO_LOCAL_sAxBbsBuf
extern AxBbsNotice sAxBbsBuf;
#endif
#ifndef PROTO_LOCAL_sGameStatsBuf
extern BlancaFaceRecord sGameStatsBuf;
#endif
#ifndef PROTO_LOCAL_sSaveManagerStates
extern SaveManagerActEntry sSaveManagerStates[32];
#endif
#ifndef PROTO_LOCAL_data_021ed390
extern u8 data_021ed390;
#endif
#ifndef PROTO_LOCAL_gSaveManager
extern SaveManager *gSaveManager;
#endif
#ifndef PROTO_LOCAL_sJoiningAid
extern u8 sJoiningAid;
#endif
#ifndef PROTO_LOCAL_sNetRegion
extern char *sNetRegion;
#endif
#ifndef PROTO_LOCAL_data_020e2790
extern char data_020e2790[];
#endif
#ifndef PROTO_LOCAL_data_020e24f0
extern char data_020e24f0[];
#endif
#ifndef PROTO_LOCAL_sSaveManagerRequest
extern s32 sSaveManagerRequest;
#endif
#ifndef PROTO_LOCAL_sRecentJoinAids
extern u8 sRecentJoinAids[3];
#endif
#ifndef PROTO_LOCAL_sGameStatsReceived
extern u8 sGameStatsReceived;
#endif
#ifndef PROTO_LOCAL_sAxBbsReceived
extern u8 sAxBbsReceived;
#endif
#ifndef PROTO_LOCAL_gTownTransferBuf
extern void *gTownTransferBuf;
#endif
#ifndef PROTO_LOCAL_data_020e2770
extern GuestSlotTriple data_020e2770;
#endif
#ifndef PROTO_LOCAL_data_020e277c
extern char data_020e277c[];
#endif
#ifndef PROTO_LOCAL_sAxMailFileName
extern char *sAxMailFileName;
#endif
#ifndef PROTO_LOCAL_sGameStartMode
extern s32 sGameStartMode;
#endif
#ifndef PROTO_LOCAL_sEraseResidentSlot
extern s32 sEraseResidentSlot;
#endif
#ifndef PROTO_LOCAL_data_020e2764
extern GuestSlotTriple data_020e2764;
#endif
#ifndef PROTO_LOCAL_data_021ed3a4
extern u8 data_021ed3a4;
#endif
#ifndef PROTO_LOCAL_sAxBbsFileName
extern char *sAxBbsFileName;
#endif
#ifndef PROTO_LOCAL_sAxMailReceived
extern u8 sAxMailReceived;
#endif
#ifndef PROTO_LOCAL_data_020e252c
extern u8 data_020e252c[8];
#endif
#ifndef PROTO_LOCAL_sSaveManagerProfile
extern ProcProfile sSaveManagerProfile;
#endif
#ifndef PROTO_LOCAL_sSessionResidentIndex
extern u8 sSessionResidentIndex;
#endif
#ifndef PROTO_LOCAL_data_020e27a4
extern char data_020e27a4[];
#endif
#ifndef PROTO_LOCAL_sAxMailBaseUrl
extern char *sAxMailBaseUrl;
#endif
#ifndef PROTO_LOCAL_data_021ed398
extern u8 data_021ed398;
#endif
#endif

#endif
