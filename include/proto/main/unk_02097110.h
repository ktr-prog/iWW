#ifndef PROTO_PROTO_MAIN_UNK_02097110_H
#define PROTO_PROTO_MAIN_UNK_02097110_H


#include "types.h"
#include "player/PlayerBank.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Startup_OnCardPulledOut
s32 Startup_OnCardPulledOut();
#endif
#ifndef PROTO_LOCAL_Startup_SetCardPulledOutCallback
void Startup_SetCardPulledOutCallback();
#endif
#ifndef PROTO_LOCAL_PlayerBank_Construct
void PlayerBank_Construct();
#endif
#ifndef PROTO_LOCAL_PlayerBank_Destruct
void PlayerBank_Destruct();
#endif
#ifndef PROTO_LOCAL_Donation_GetTotal
s32 Donation_GetTotal();
#endif
#ifndef PROTO_LOCAL_Donation_SetTotal
void Donation_SetTotal(s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerBank_PayInterest
void PlayerBank_PayInterest(s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerBank_SendMilestoneLetter
void PlayerBank_SendMilestoneLetter(s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerBank_SendDonationLetter
void PlayerBank_SendDonationLetter(s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerBank_Clear
void PlayerBank_Clear(PlayerBank *p);
#endif
#ifndef PROTO_LOCAL_PlayerBank_GetBalance
u32 PlayerBank_GetBalance(PlayerBank *p);
#endif
#ifndef PROTO_LOCAL_PlayerBank_SetBalance
void PlayerBank_SetBalance(PlayerBank *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerBank_GetDonationLevel
u32 PlayerBank_GetDonationLevel(PlayerBank *p);
#endif
#ifndef PROTO_LOCAL_PlayerBank_SetDonationLevel
void PlayerBank_SetDonationLevel(PlayerBank *p, u32 v);
#endif
}
#ifndef PROTO_LOCAL_data_020e1e08
extern s32 data_020e1e08;
#endif
#ifndef PROTO_LOCAL_data_020e1e04
extern s32 data_020e1e04;
#endif
#ifndef PROTO_LOCAL_data_020e1e00
extern s32 data_020e1e00;
#endif
#ifndef PROTO_LOCAL_data_020e1dfc
extern s32 data_020e1dfc;
#endif
#ifndef PROTO_LOCAL_data_020e1df8
extern s32 data_020e1df8;
#endif
#ifndef PROTO_LOCAL_data_020e1e0c
extern s32 data_020e1e0c;
#endif
#endif

#endif
