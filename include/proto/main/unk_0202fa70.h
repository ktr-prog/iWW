#ifndef PROTO_PROTO_MAIN_UNK_0202FA70_H
#define PROTO_PROTO_MAIN_UNK_0202FA70_H


#include "types.h"
struct CollisionVisitor;
struct ShapeCylinder;
struct WallEdgeListWriter;
#ifndef __cplusplus
typedef struct CollisionVisitor CollisionVisitor;
typedef struct ShapeCylinder ShapeCylinder;
typedef struct WallEdgeListWriter WallEdgeListWriter;
#endif
#ifdef __cplusplus
#include "game/BoxCollider.h"
#include "game/CollisionMap.h"
#include "game/CollisionVec2.h"
#include "game/FxVec3.h"
#include "game/SegmentHitResult.h"
#include "game/TriangleTrigger.h"
#include "game/UnitShapeQueryX.h"
#include "gfx/VecFx32.h"
class BoxColliderListOwner;
class CollisionWorld;
class FloorTriangleList;
class WallEdge;
struct CollisionState;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_GroundInfo_Destruct
void GroundInfo_Destruct(void *obj);
#endif
#ifndef PROTO_LOCAL_CollisionTag_Construct
void* CollisionTag_Construct(void* p);
#endif
#ifndef PROTO_LOCAL_CollisionTag_Destruct
void* CollisionTag_Destruct(void* p);
#endif
#ifndef PROTO_LOCAL_TriangleTrigger_ClearList
void TriangleTrigger_ClearList(void *p);
#endif
#ifndef PROTO_LOCAL_BoxCollider_ClearList
void BoxCollider_ClearList(void *p);
#endif
#ifndef PROTO_LOCAL_CollisionMap_IsFullyBound
u32 CollisionMap_IsFullyBound(s32 i);
#endif
#ifndef PROTO_LOCAL_Vec3_MaxInPlace
void Vec3_MaxInPlace(s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_Vec3_MinInPlace
void Vec3_MinInPlace(s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr0Q3
u32 GroundAttr_GetQuadAttr0Q3(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr0Q2
u32 GroundAttr_GetQuadAttr0Q2(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr0Q1
u32 GroundAttr_GetQuadAttr0Q1(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr0Q0
u32 GroundAttr_GetQuadAttr0Q0(s32 t);
#endif
#ifndef PROTO_LOCAL_Ground_GetQuadAttr0
u32 Ground_GetQuadAttr0(s32 x, s32 y, u32 c);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr1Q3
u32 GroundAttr_GetQuadAttr1Q3(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr1Q2
u32 GroundAttr_GetQuadAttr1Q2(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr1Q1
u32 GroundAttr_GetQuadAttr1Q1(s32 t);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetQuadAttr1Q0
u32 GroundAttr_GetQuadAttr1Q0(s32 t);
#endif
#ifndef PROTO_LOCAL_Ground_GetQuadAttr1
u32 Ground_GetQuadAttr1(s32 x, s32 y, u32 c);
#endif
#ifndef PROTO_LOCAL_GroundAttr_IsWater
BOOL GroundAttr_IsWater(s32 t, s32 k);
#endif
#ifndef PROTO_LOCAL_Ground_IsPond
BOOL Ground_IsPond(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsGrassUnit
BOOL Ground_IsGrassUnit(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_GetWaterKind
s32 Ground_GetWaterKind(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_CanPlaceItem
s32 Ground_CanPlaceItem(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsGrassSurface
s32 Ground_IsGrassSurface(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsWalkable
s32 Ground_IsWalkable(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_GetDigKind
s32 Ground_GetDigKind(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_GetPlantFlag
s32 Ground_GetPlantFlag(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsShore
BOOL Ground_IsShore(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsSandAboveSea
BOOL Ground_IsSandAboveSea(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Ground_GetWalkLinks
u32 Ground_GetWalkLinks(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Ground_IsFreeGrassOffPath
BOOL Ground_IsFreeGrassOffPath(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Ground_IsFreeGrass
BOOL Ground_IsFreeGrass(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Ground_GetMapColors
BOOL Ground_GetMapColors(u8 *out, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetFootstepSe
u16 GroundAttr_GetFootstepSe(s32 i);
#endif
#ifndef PROTO_LOCAL_GroundAttr_GetDragSe
u16 GroundAttr_GetDragSe(s32 i);
#endif
#ifndef PROTO_LOCAL_Ground_IsNeighbourReachable
BOOL Ground_IsNeighbourReachable(s32 a, s32 b, s32 c, s32 d, u8 flag);
#endif
#ifndef PROTO_LOCAL_CollisionMap_IsBound
u32 CollisionMap_IsBound(s32 a);
#endif
#ifndef PROTO_LOCAL_Ground_FindTerrainMarker
s32 Ground_FindTerrainMarker(s32 *a, s32 *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_Ground_GetSpecialPieceKind
s32 Ground_GetSpecialPieceKind(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Collision_ClampToRect
BOOL Collision_ClampToRect(s32 *p, s32 a, s32 *c, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Ground_GetDefaultY
s32 Ground_GetDefaultY(void);
#endif
#ifndef PROTO_LOCAL_Collision_GetUnitShape
BOOL Collision_GetUnitShape(s32 x, s32 z, s32 *p, s32 *q, s32 *r);
#endif
#ifndef PROTO_LOCAL_Collision_HasUnitShape
s32 Collision_HasUnitShape(s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_CollisionMap_Select
void CollisionMap_Select(s32 v);
#endif
#ifndef PROTO_LOCAL_Collision_UpdateDigHoles
void Collision_UpdateDigHoles(void);
#endif
#ifndef PROTO_LOCAL_Collision_AddDigHole
void Collision_AddDigHole(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Ground_SetWalkLinks
void Ground_SetWalkLinks(s32 x, s32 z, s32 v);
#endif
#ifndef PROTO_LOCAL_Ground_ClearWalkLinks
void Ground_ClearWalkLinks(s32 x, s32 z, s32 mask);
#endif
#ifndef PROTO_LOCAL_CollisionMap_SetBlock
BOOL CollisionMap_SetBlock(s32 x, s32 y, void *bcl, s32 idx);
#endif
#ifndef PROTO_LOCAL_CollisionMap_Reset
void CollisionMap_Reset(s32 idx);
#endif
#ifndef PROTO_LOCAL_CollisionMap_ClearBlocks
void CollisionMap_ClearBlocks(s32 idx);
#endif
#ifndef PROTO_LOCAL_CollisionMap_Release
void CollisionMap_Release(s32 idx);
#endif
#ifndef PROTO_LOCAL_Ground_SetWaveLevel
void Ground_SetWaveLevel(s32 v);
#endif
#ifndef PROTO_LOCAL_Ground_ClearPlantFlag
BOOL Ground_ClearPlantFlag(s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_Ground_SetQuadrantsBlocked
BOOL Ground_SetQuadrantsBlocked(s32 x, s32 z, s32 mask);
#endif
#ifndef PROTO_LOCAL_Ground_UnlinkUnit
void Ground_UnlinkUnit(s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_Ground_GetExitAt
s32 Ground_GetExitAt(s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_Ground_LockExit
BOOL Ground_LockExit(s32 v);
#endif
#ifndef PROTO_LOCAL_Ground_UnlockExit
BOOL Ground_UnlockExit(void);
#endif
#ifndef PROTO_LOCAL_Ground_GetFloorBounds
BOOL Ground_GetFloorBounds(s32 *a, s32 *b, s32 *c, s32 *d);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WallEdge_GetMidpoint
void WallEdge_GetMidpoint(CollisionVec2 *out, WallEdge *e);
#endif
#ifndef PROTO_LOCAL_TriangleTrigger_Register
s32 TriangleTrigger_Register(TriangleTrigger* node);
#endif
#ifndef PROTO_LOCAL_TriangleTrigger_Unregister
s32 TriangleTrigger_Unregister(TriangleTrigger* node);
#endif
#ifndef PROTO_LOCAL_TriangleTrigger_CheckAll
void TriangleTrigger_CheckAll(VecFx32* a, s32 b, Actor *c);
#endif
#ifndef PROTO_LOCAL_BoxCollider_Register
BOOL BoxCollider_Register(BoxCollider *n, s32 a, s32 b, s32 c, VecFx32 *pos, s16 e, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_BoxCollider_Unregister
BOOL BoxCollider_Unregister(BoxCollider *n);
#endif
#ifndef PROTO_LOCAL_Collision_IsSegmentOutsideBox
BOOL Collision_IsSegmentOutsideBox(VecFx32 *a, VecFx32 *b, VecFx32 *c, VecFx32 *d);
#endif
#ifndef PROTO_LOCAL_BoxCollider_GatherAll
void BoxCollider_GatherAll(BoxColliderListOwner *unused, VecFx32 *pos, VecFx32 *size, WallEdgeListWriter *walls, FloorTriangleList *floors, u32 flags, s32 mode);
#endif
#ifndef PROTO_LOCAL_Ground_GetUnitQuadrant
s32 Ground_GetUnitQuadrant(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Collision_GetShapeQuery
UnitShapeQueryX *Collision_GetShapeQuery();
#endif
#ifndef PROTO_LOCAL_Ground_IsRaisedOrOccupied
BOOL Ground_IsRaisedOrOccupied(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Ground_IsWaterAround
BOOL Ground_IsWaterAround(VecFx32 *pos, s32 r, s32 *out, s32 flags);
#endif
#ifndef PROTO_LOCAL_Ground_FindWaterAlongDir
BOOL Ground_FindWaterAlongDir(VecFx32 *out, VecFx32 *pos, u32 dist, s32 dir, u32 count, s32 r, s32 flags);
#endif
#ifndef PROTO_LOCAL_Ground_FindWaterAhead
BOOL Ground_FindWaterAhead(VecFx32 *out, VecFx32 *pos, s32 dir, u32 dist, u32 s5, s32 s6);
#endif
#ifndef PROTO_LOCAL_Ground_IsWaterAt
BOOL Ground_IsWaterAt(VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_Collision_Move
void Collision_Move(CollisionState *self, VecFx32 *pos, VecFx32 *tgt, u16 hh, s32 arg5, Actor *actor, u32 flags);
#endif
#ifndef PROTO_LOCAL_Collision_TestSegment
u8 Collision_TestSegment(SegmentHitResult *out, VecFx32 *pos, VecFx32 *tgt, u32 flags);
#endif
#ifndef PROTO_LOCAL_Ground_GetHeightAt
s32 Ground_GetHeightAt(VecFx32 *p, u32 *out, u32 flags0);
#endif
#ifndef PROTO_LOCAL_Collision_HasUnitShapeAt
s32 Collision_HasUnitShapeAt(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Collision_Query
void Collision_Query(VecFx32 *a, VecFx32 *b, CollisionVisitor *visitor, u32 flags, u8 p5, u8 p6);
#endif
#ifndef PROTO_LOCAL_CollisionMap_Bind
BOOL CollisionMap_Bind(u32 a, u32 b, UnitShapeQueryX *o, s32 idx);
#endif
#ifndef PROTO_LOCAL_Ground_GetExitAtPos
s32 Ground_GetExitAtPos(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Ground_IsOnLockedExit
BOOL Ground_IsOnLockedExit(VecFx32 *p);
#endif
}
#ifndef PROTO_LOCAL_sTriangleTriggerList
extern TriangleTrigger *sTriangleTriggerList;
#endif
#ifndef PROTO_LOCAL_data_021bf9a0
extern s32 data_021bf9a0;
#endif
#ifndef PROTO_LOCAL_sCollisionUpVector
extern FxVec3 sCollisionUpVector;
#endif
#ifndef PROTO_LOCAL_sBoxColliderList
extern BoxCollider *sBoxColliderList;
#endif
#ifndef PROTO_LOCAL_sCollisionQueryMargin
extern FxVec3 sCollisionQueryMargin;
#endif
#ifndef PROTO_LOCAL_gCurCollisionMap
extern CollisionMap *gCurCollisionMap;
#endif
#ifndef PROTO_LOCAL_sCollisionWorld
extern CollisionWorld sCollisionWorld;
#endif
#ifndef PROTO_LOCAL_ShapeCylinder_AddLinkWall
BOOL ShapeCylinder_AddLinkWall(ShapeCylinder *a, WallEdgeListWriter *out, ShapeCylinder *b);
#endif
#endif

#endif
