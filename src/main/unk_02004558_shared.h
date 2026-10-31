#ifndef UNK_02004558_SHARED_H
#define UNK_02004558_SHARED_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/NNSG3dRS.h"
#include "player/PlayerActor.h"
#include "player/PlayerData.h"
#include "player/Unk_02007694.h"
#include "player/Unk_0200f070_V3.h"
#include "proto/main/unk_02004558.h"
#include "game/Unk_0200f6d4_V2.h"
#include "sys/PadState.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_0203d4d8.h"
#define PROTO_LOCAL_FieldAction_RequestPlaceAtPendingForAid
#include "proto/main/unk_02041e00.h"
#include "proto/main/unk_0204a780.h"
#include "proto/main/unk_02055200.h"

extern "C" {
extern u8 gFieldSceneKind;
u32 Scene_GetCurrent();
void PendingUnit_ApplyAt(Vec2 *pos, s32 flag);
s32 Math_ApproachS32(s32 *p, s32 target, s32 ratio, s32 max, s32 min);
s32 PlayerActor_RequestAct66(PlayerActor *o, Unk_0200f6d4_V2 *p, u32 c, s32 b, s16 d);
s32 FieldAction_RequestPlaceAtPendingForAid(s32 aid, u16 item);

void PlayerActor_ApproachValue(s32 *p, s32 target, s32 rate, s32 maxstep, s32 minstep);
s32 PlayerActor_ApproachAngle(s16 *p, s32 target, s32 rate, s32 maxstep, s32 minstep);
s32 PlayerActor_TurnAngle(s16 *p, s32 target);
PlayerData *PlayerActor_GetPlayerData(PlayerActor *p);
s32 PlayerActor_GetHairStyle(PlayerActor *p);
s32 PlayerActor_GetHairColor(PlayerActor *p);
s32 PlayerActor_GetTan(PlayerActor *p);
void PlayerActor_GetHeldItem(u16 *out, PlayerActor *x);
void PlayerActor_StepTowardPose(PlayerActor *o, s32 a, s32 b, s32 c);
void PlayerActor_GetFrontUnitCenter(VecFx32 *a, PlayerActor *b);
void PlayerActor_GetFrontPoint(VecFx32 *out, PlayerActor *o);
void PlayerActor_SetLastPlayDate(PlayerActor *o, PlayerData *a, Unk_0200f17c_Date *d);

extern const u8 data_020c6190[4];
extern const u8 data_020c6194[4];
extern const u8 data_020c6198[4];
extern const u8 data_020c619c[4];
extern const u8 data_020c61a0[4];
extern const u8 data_020c61a4[4];
extern const u8 data_020c61a8[4];
extern const u8 data_020c61ac[4];
extern const u8 data_020c61b0[4];
extern const u8 data_020c61b4[4];
extern const u8 data_020c61b8[8];
extern const u16 data_020c61c0[8];
extern const u8 data_020c61d0[32];
extern const u32 sPlayerAct76Anims[8];
extern const u32 data_020c6210[11];
extern const u32 sPlayerReachDist[15];
extern const u8 sPlayerActionStopsMovement[148];
extern const u8 sPlayerActionResetsRotX[148];
extern const u8 sPlayerActionLevelsTilt[148];
extern const u8 data_020c6434[148];
extern const u8 data_020c64c8[148];
extern const u8 sPlayerActionColliderFlag2[148];
extern const u8 sPlayerActionTalkable[148];
extern const u8 sPlayerActionIsLocomotion[148];
extern const u8 sPlayerActionKeepsBgCheckWork[148];
extern const u8 sPlayerActionPriority[148];
extern const u8 sPlayerActionDonePriority[148];
extern const u16 sPlayerAnimResIndex[162];
extern const u32 data_020c6a18[147];
extern const s32 sPlayerFrontPointDist;
}

#endif
