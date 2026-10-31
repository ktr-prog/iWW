#ifndef PROTO_PROTO_MAIN_UNK_02089FBC_H
#define PROTO_PROTO_MAIN_UNK_02089FBC_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "ui/HudController.h"
#include "ui/HudProc.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Hud_GetBells
s32 Hud_GetBells();
#endif
#ifndef PROTO_LOCAL_Hud_Init
void Hud_Init();
#endif
#ifndef PROTO_LOCAL_Hud_Exit
void Hud_Exit();
#endif
#ifndef PROTO_LOCAL_Hud_Update
void Hud_Update();
#endif
#ifndef PROTO_LOCAL_Hud_Draw
void Hud_Draw();
#endif
#ifndef PROTO_LOCAL_Hud_Hide
void Hud_Hide();
#endif
#ifndef PROTO_LOCAL_Hud_Show
void Hud_Show();
#endif
#ifndef PROTO_LOCAL_Hud_ClearHideB
void Hud_ClearHideB();
#endif
#ifndef PROTO_LOCAL_Hud_GetCountdown
void *Hud_GetCountdown();
#endif
#ifndef PROTO_LOCAL_Hud_GetWallet
void *Hud_GetWallet();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HudProc_Create
HudProc *HudProc_Create();
#endif
}
#ifndef PROTO_LOCAL_sHudColonStr
extern char sHudColonStr[];
#endif
#ifndef PROTO_LOCAL_sHudAmStr
extern char sHudAmStr[];
#endif
#ifndef PROTO_LOCAL_sHudPmStr
extern char sHudPmStr[];
#endif
#ifndef PROTO_LOCAL_sHudProcProfile
extern ProcProfile sHudProcProfile;
#endif
#ifndef PROTO_LOCAL_gHud
extern HudController gHud;
#endif
#endif

#endif
