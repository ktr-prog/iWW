#ifndef PLAYER_FISHBOBBER_H
#define PLAYER_FISHBOBBER_H

#include "types.h"
#include "gfx/VecFx32.h"

class Character;


class FishBobber {
public:
    void update();
    void setState(s32 state);
    void setPos(VecFx32 *v);
    void setTargetPos(VecFx32 *v);
    void startCatchLift();
    void endCatch();
    BOOL isCatchLanded();
    void nudge();
    BOOL checkReelResult();
    BOOL tryHook();
    BOOL isInWater();
    void *getFish();
    void setFish(void *p);
    void setOwnerAid(s32 v);
    u8 getSlot();
    void detach();
    void attach(u32 id, Character *actor, u32 n);
    void destruct();
    void construct();

    /* 0x00 */ u8 slot;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ s32 curState;
    /* 0x08 */ VecFx32 pos;
    /* 0x14 */ s32 gravity;
    /* 0x18 */ s32 ySpeed;
    /* 0x1c */ VecFx32 targetPos;
    /* 0x28 */ Character *ownerActor;
    /* 0x2c */ void *fish;
    /* 0x30 */ s32 stateTimer;
    /* 0x34 */ s32 effect;
    /* 0x38 */ u8 justLanded;
    /* 0x39 */ u8 pad_39[3];
    /* 0x3c */ s32 ownerAid;
};

#endif
