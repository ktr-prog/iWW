#ifndef NPC_NPCMOVECTRL_H
#define NPC_NPCMOVECTRL_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "npc/NpcLookAt.h"


class NpcMoveCtrl {
public:
    NpcMoveCtrl();
    ~NpcMoveCtrl() { func_0201acc8(); }
    /* 0x00 */ VecFx32 curSpeedPreset;
    /* 0x0c */ VecFx32 speedPresets[3];
    /* 0x30 */ s32 moveMode;
    /* 0x34 */ s16 targetAngle;
    /* 0x36 */ s16 turnSpeed;
    /* 0x38 */ VecFx32 waypoint;
    /* 0x44 */ VecFx32 destination;
    /* 0x50 */ s32 arriveDistance;
    /* 0x54 */ u8 keepAnimFrame;
    /* 0x55 */ u8 turnMode;

    void setTurnMode(u8 v);
    void getCurSpeedPreset();
    void setSpeedPreset(s32 idx, s32 x, s32 y, s32 z);
    void resetDestination();
    s32 hasNextLeg();
    VecFx32 *getDestination();
    void setDestination(VecFx32 *v);
    s32 getTurnSpeed();
    s32 getTargetAngle();
    void setTargetAngle(s16 v);
    BOOL hasArrived(Character *scene, s32 which);
    VecFx32 *getDestinationB();
    void setWaypoint(VecFx32 *v);
    void updateTurn(Character *scene);
    s32 stepAngle(s16 *p, s16 target, s16 step, u8 mode);
    void aimAtDestination(Character *scene);
    s32 getMoveMode();
    void setMoveMode(Character *scene, s32 mode, s16 ang, u16 extra);
    void applyMovement(Character *scene);
    void reset();
    void func_0201acc8();
};

#endif
