#ifndef NPC_NPCMOVEANIMSET_H
#define NPC_NPCMOVEANIMSET_H

#include "types.h"


struct NpcMoveAnimSet {
    NpcMoveAnimSet();
    ~NpcMoveAnimSet() { func_0201ad38(); }
    s32 standAnim;
    s32 walkAnim;
    s32 runAnim;

    s32 getRunAnim();
    s32 getWalkAnim();
    s32 getStandAnim();
    void setRunAnim(s32 v);
    void setWalkAnim(s32 v);
    void setStandAnim(s32 v);
    void func_0201ad38();
};

#endif
