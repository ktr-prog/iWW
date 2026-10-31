#ifndef NPC_NPCFOOTSTEPFX_H
#define NPC_NPCFOOTSTEPFX_H

#include "types.h"

class NpcActor;

struct NpcFootstepFx {
    /* 0x0 */ u8 footstepsEnabled;
    /* 0x1 */ u8 pad_01[3];
    /* 0x4 */ u32 prevMoveMode;
    NpcFootstepFx();
    ~NpcFootstepFx() { func_020135e0(); }
    void updateFootsteps(NpcActor* p);
    void playFootstepSe(NpcActor* p);
    void disableFootsteps();
    void enableFootsteps();
    void resetFootsteps();
    void func_020135e0();
};

#endif
