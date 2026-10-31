#ifndef PLAYER_ANIMSLOTREF_H
#define PLAYER_ANIMSLOTREF_H

#include "types.h"


class AnimSlotRef;
extern "C" void AnimSlotRef_Init(AnimSlotRef *p);
extern "C" void AnimSlotRef_Destruct();
class AnimSlotRef {
public:
    /* 0x00 */ u8 slot;
    AnimSlotRef() { AnimSlotRef_Init(this); }
    ~AnimSlotRef() { AnimSlotRef_Destruct(); }
};

#endif
