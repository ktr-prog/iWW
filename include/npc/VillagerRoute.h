#ifndef NPC_VILLAGERROUTE_H
#define NPC_VILLAGERROUTE_H

#include "types.h"
#include "gfx/VecFx32.h"

class BlockMap;
class NpcActor;
struct VillagerRouteType;
struct RouteGridPosCopy;
struct RouteJunction;

struct RouteGridPos {
    u32 x, z;
};

struct VillagerRoute {
    /* 0x00 */ u32 stepMode;
    /* 0x04 */ u32 stepPhase;
    /* 0x08 */ u32 routeType;
    /* 0x0c */ Vec2 targetUnit;
    /* 0x14 */ s32 targetBlockX;
    /* 0x18 */ s32 targetBlockZ;
    /* 0x1c */ RouteGridPos waypoint;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ VillagerRouteType *typeTable;
    /* 0x2c */ u8 junctions[90];
    /* 0x86 */ u8 pad_86[2];
    /* 0x88 */ u32 pathDir;
    /* 0x8c */ u32 pathMode;
    /* 0x90 */ u32 approachDir;
    /* 0x94 */ u32 lastUnitX;
    /* 0x98 */ u32 lastUnitZ;

    BOOL isInBlock(VecFx32 *v);
    BOOL isInBlockT4(VecFx32 *v);
    BOOL isInBlockT2(VecFx32 *v);
    BOOL stepToDoor(VecFx32 *p);
    BOOL isAtDoorT3(VecFx32 *p);
    BOOL isAtDoorT1(VecFx32 *p);
    BOOL stepCheckArrived(VecFx32 *p);
    BOOL stepWander(VecFx32 *p);
    BOOL stepAdjacentUnit(VecFx32 *p);
    BOOL pickAdjacent(VecFx32 *p, BlockMap *w);
    BOOL stepAlongPath(VecFx32 *p);
    BOOL advanceOnPath(VecFx32 *p, BlockMap *w);
    BOOL stepFollowPath(VecFx32 *p);
    BOOL followPathDir(VecFx32 *p, Vec2 *lim, BlockMap *w);
    BOOL isInAttr200Block(VecFx32 *v);

    s32 oppositeDirs(s32 v);
    s32 runStep(VecFx32 *v);
    u32 getStage();
    s32 findJunction(RouteGridPos *p);
    RouteJunction popJunction(RouteGridPos *p);
    void pushJunction(u32 hi, u32 lo, RouteGridPos *p);
    s32 scanDir(RouteGridPos *out, RouteGridPosCopy pos, u32 mask, RouteGridPos *lim, BlockMap *obj);
    u32 pickAdjacentUnit(VecFx32 *v, BlockMap *o);
    s32 scanForPath(VecFx32 *cand, RouteGridPos *p, VecXZ *d, s32 limit, RouteGridPos *q, s32 flag, BlockMap *o);
    u32 findNearestPath(RouteGridPos *out, VecFx32 *pos);
    void planStep(VecFx32 *pos);
    s32 countJunctions();
    void clearJunctions();
    s32 firstDir(s32 v);
    s32 isArrived(VecFx32 *v);

    BOOL isActive();
    void setStepMode(u32 v);
    void checkUnitChanged(VecFx32 *v);
    void markUnitUnset();
    void rememberUnit(VecFx32 *v);
    void start(VecFx32 *pos, u32 idx, u32 b, NpcActor *owner);
    void reset();
    VillagerRoute* resetTarget();
};

#endif
