#ifndef PROTO_PROTO_OV004_UNK_OV004_02237440_H
#define PROTO_PROTO_OV004_UNK_OV004_02237440_H


#include "types.h"
#include "sys/ProcProfile.h"
struct MuseumInsectBehavior;
struct MuseumInsectParam;
#ifndef __cplusplus
typedef struct MuseumInsectBehavior MuseumInsectBehavior;
typedef struct MuseumInsectParam MuseumInsectParam;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
class MuseumInsect;
class MuseumInsectRoom;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sMuseumScorpionSlot
extern s8 sMuseumScorpionSlot;
#endif
#ifndef PROTO_LOCAL_sMuseumDungBallSlot
extern s8 sMuseumDungBallSlot;
#endif
#ifndef PROTO_LOCAL_sMuseumInsectFrame
extern u8 sMuseumInsectFrame;
#endif
#ifndef PROTO_LOCAL_MuseumInsect_CheckFloorAhead
u8 MuseumInsect_CheckFloorAhead(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_CheckWallsAhead
u8 MuseumInsect_CheckWallsAhead(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MakeStepDir
void MuseumInsect_MakeStepDir(void *v_, s32 a);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RandHeading
s16 MuseumInsect_RandHeading();
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PointAtAngle
void MuseumInsect_PointAtAngle(void *out_, void *base_, u32 ang, s32 rad);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FlapWings
void MuseumInsect_FlapWings(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RevertIfOffFloor
BOOL MuseumInsect_RevertIfOffFloor(void *o_, void *v_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ClampToBounds
u8 MuseumInsect_ClampToBounds(void *o_, void *v_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ApproachHome
void MuseumInsect_ApproachHome(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_StateRest
void MuseumInsect_StateRest(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_TickTimer
s32 MuseumInsect_TickTimer(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PlaySe
BOOL MuseumInsect_PlaySe(void *self_, s32 b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_GetSe
s32 MuseumInsect_GetSe(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_Wander
void MuseumInsect_Wander(void *self_, s32 a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_BobHeight
void MuseumInsect_BobHeight(void *self_, u32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_CheckScared
s32 MuseumInsect_CheckScared(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_GetEscapeHeading
s32 MuseumInsect_GetEscapeHeading(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_TurnToTarget
void MuseumInsect_TurnToTarget(void *self_, u32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_TickAlert
s32 MuseumInsect_TickAlert(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateAlertLevel
s32 MuseumInsect_UpdateAlertLevel(void *self_, void *out_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunButterfly
void MuseumInsect_RunButterfly(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunDragonfly
void MuseumInsect_RunDragonfly(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunHopper
void MuseumInsect_RunHopper(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunPondSkater
void MuseumInsect_RunPondSkater(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PondSkaterGlide
void MuseumInsect_PondSkaterGlide(void *self_, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RandTurn8
s32 MuseumInsect_RandTurn8(s32 n);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunMosquito
void MuseumInsect_RunMosquito(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunFirefly
void MuseumInsect_RunFirefly(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunFlyingInsect
void MuseumInsect_RunFlyingInsect(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunFlea
void MuseumInsect_RunFlea(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunMoleCricket
void MuseumInsect_RunMoleCricket(void *self_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SteerFromEdges
s32 MuseumInsect_SteerFromEdges(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunPillBug
void MuseumInsect_RunPillBug(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PillBugNextWaypoint
void MuseumInsect_PillBugNextWaypoint(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_GetPillBugWaypoint
void MuseumInsect_GetPillBugWaypoint(void *v_, s32 k);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunMoth
void MuseumInsect_RunMoth(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunArachnid
void MuseumInsect_RunArachnid(void *o_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_WiggleHeading
void MuseumInsect_WiggleHeading(void *o_, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FightSkirmish
void MuseumInsect_FightSkirmish(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FightCircleOther
void MuseumInsect_FightCircleOther(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FightCircleSelf
void MuseumInsect_FightCircleSelf(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FightPause
void MuseumInsect_FightPause(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FightClash
void MuseumInsect_FightClash(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ArachnidWalk
void MuseumInsect_ArachnidWalk(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ArachnidFacePlayer
BOOL MuseumInsect_ArachnidFacePlayer(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunDungBeetle
void MuseumInsect_RunDungBeetle(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RunCockroach
void MuseumInsect_RunCockroach(void *r_);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ClampStep
void MuseumInsect_ClampStep(void *out_, void *in_, s32 lim);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RandTurn
s32 MuseumInsect_RandTurn(s32 n);
#endif
#ifndef PROTO_LOCAL_MuseumInsectRoom_Create
void *MuseumInsectRoom_Create();
#endif
#ifndef PROTO_LOCAL_MuseumInsectRoom_FindFreeSlot
s32 MuseumInsectRoom_FindFreeSlot();
#endif
#ifndef PROTO_LOCAL_MuseumInsect_GetTimeOfDayBit
u32 MuseumInsect_GetTimeOfDayBit();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sMuseumInsectRoomProfile
extern ProcProfile sMuseumInsectRoomProfile;
#endif
#ifndef PROTO_LOCAL_sMuseumInsectParams
extern MuseumInsectParam sMuseumInsectParams[57];
#endif
#ifndef PROTO_LOCAL_sMuseumInsectBehaviors
extern MuseumInsectBehavior sMuseumInsectBehaviors[57];
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ProbeFloor
u8 MuseumInsect_ProbeFloor(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ProbeWalls
u8 MuseumInsect_ProbeWalls(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetProbePoints
void MuseumInsect_SetProbePoints(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_GetHomeDelta
void MuseumInsect_GetHomeDelta(MuseumInsect *self, s16 *a, s32 *b, VecFx32 *c);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ButterflyFly
void MuseumInsect_ButterflyFly(MuseumInsect *self);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_ButterflyFlapHeight
void MuseumInsect_ButterflyFlapHeight(MuseumInsect *self, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_DragonflyLand
void MuseumInsect_DragonflyLand(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_DragonflyHover
void MuseumInsect_DragonflyHover(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_DragonflyFlyTo
void MuseumInsect_DragonflyFlyTo(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_DragonflyAvoidWall
void MuseumInsect_DragonflyAvoidWall(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_DragonflyPickPerch
s32 MuseumInsect_DragonflyPickPerch(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_HopperHop
void MuseumInsect_HopperHop(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_HopperAvoidWall
s32 MuseumInsect_HopperAvoidWall(MuseumInsect *o, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_HopperChirp
void MuseumInsect_HopperChirp(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PondSkaterStartGlide
void MuseumInsect_PondSkaterStartGlide(MuseumInsect *o, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MosquitoChase
void MuseumInsect_MosquitoChase(MuseumInsect *self, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FireflyWander
void MuseumInsect_FireflyWander(MuseumInsect *self);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FlyingInsectFly
void MuseumInsect_FlyingInsectFly(MuseumInsect *self);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FleaJump
void MuseumInsect_FleaJump(MuseumInsect *self);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MoleCricketCheckEmerge
void MuseumInsect_MoleCricketCheckEmerge(MuseumInsect *self);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MoleCricketJump
void MuseumInsect_MoleCricketJump(MuseumInsect *self, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MoleCricketCrawl
void MuseumInsect_MoleCricketCrawl(MuseumInsect *self, s16 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PillBugCheckCurl
BOOL MuseumInsect_PillBugCheckCurl(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_PillBugWalk
void MuseumInsect_PillBugWalk(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_MothHover
void MuseumInsect_MothHover(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FaceEachOther
BOOL MuseumInsect_FaceEachOther(MuseumInsect *a, MuseumInsect *b);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateFight
BOOL MuseumInsect_UpdateFight(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupHopper
void MuseumInsect_SetupHopper(MuseumInsect *o, s32 a, s32 b, s32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateHopper
void MuseumInsect_UpdateHopper(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupGrasshopper
void MuseumInsect_SetupGrasshopper(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupCricket
void MuseumInsect_SetupCricket(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupLongLocust
void MuseumInsect_SetupLongLocust(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupMigratoryLocust
void MuseumInsect_SetupMigratoryLocust(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupBellCricket
void MuseumInsect_SetupBellCricket(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupCockroach
void MuseumInsect_SetupCockroach(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateCockroach
void MuseumInsect_UpdateCockroach(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateDragonfly
void MuseumInsect_UpdateDragonfly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupDragonfly
void MuseumInsect_SetupDragonfly(MuseumInsect *o, s32 a, s32 b, s32 c, u8 d, u8 e, s32 f);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupRedDragonfly
void MuseumInsect_SetupRedDragonfly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupDarnerDragonfly
void MuseumInsect_SetupDarnerDragonfly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupBandedDragonfly
void MuseumInsect_SetupBandedDragonfly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupPondSkater
void MuseumInsect_SetupPondSkater(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdatePondSkater
void MuseumInsect_UpdatePondSkater(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateWalker
void MuseumInsect_UpdateWalker(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupSnail
void MuseumInsect_SetupSnail(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupLadybug
void MuseumInsect_SetupLadybug(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupMantis
void MuseumInsect_SetupMantis(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupOrchidMantis
void MuseumInsect_SetupOrchidMantis(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupMoleCricket
void MuseumInsect_SetupMoleCricket(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateMoleCricket
void MuseumInsect_UpdateMoleCricket(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupPillBug
void MuseumInsect_SetupPillBug(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdatePillBug
void MuseumInsect_UpdatePillBug(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupHoneybee
void MuseumInsect_SetupHoneybee(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateHoneybee
void MuseumInsect_UpdateHoneybee(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupFly
void MuseumInsect_SetupFly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateFly
void MuseumInsect_UpdateFly(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupSpider
void MuseumInsect_SetupSpider(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateSpider
void MuseumInsect_UpdateSpider(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateArachnid
void MuseumInsect_UpdateArachnid(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupTarantula
void MuseumInsect_SetupTarantula(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupScorpion
void MuseumInsect_SetupScorpion(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupBee
void MuseumInsect_SetupBee(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateBee
void MuseumInsect_UpdateBee(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupFlea
void MuseumInsect_SetupFlea(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateFlea
void MuseumInsect_UpdateFlea(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupAnt
void MuseumInsect_SetupAnt(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateAnt
void MuseumInsect_UpdateAnt(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_SetupDungBeetle
void MuseumInsect_SetupDungBeetle(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_UpdateDungBeetle
void MuseumInsect_UpdateDungBeetle(MuseumInsect *o);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_InitPlacement
void MuseumInsect_InitPlacement(MuseumInsectRoom *m, MuseumInsect *s);
#endif
#ifndef PROTO_LOCAL_MuseumInsectRoom_AddInsect
BOOL MuseumInsectRoom_AddInsect(MuseumInsectRoom *m, s8 v);
#endif
#ifndef PROTO_LOCAL_MuseumInsectRoom_LoadInsect
void MuseumInsectRoom_LoadInsect(MuseumInsectRoom *m, MuseumInsect *s);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_RevertOutOfBounds
void MuseumInsect_RevertOutOfBounds(MuseumInsectRoom *m, MuseumInsect *s, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FindScorpion
MuseumInsect *MuseumInsect_FindScorpion();
#endif
#ifndef PROTO_LOCAL_MuseumInsect_FindDungBall
MuseumInsect *MuseumInsect_FindDungBall();
#endif
}
#ifndef PROTO_LOCAL_sMuseumInsects
extern MuseumInsect sMuseumInsects[0x20];
#endif
#endif

#endif
