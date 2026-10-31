#ifndef PLAYER_HELDITEMMODEL_H
#define PLAYER_HELDITEMMODEL_H

#include "types.h"
#include "gfx/ModelAnim.h"
#include "player/FishBobber.h"

class HeldItemTexAnim : public ModelAnim {
public:
    HeldItemTexAnim();
    virtual ~HeldItemTexAnim();
};

class HeldItemModel {
public:
    /* 0x00 */ u8 slot;
    /* 0x04 */ u32 scale;
    /* 0x08 */ HeldItemTexAnim texAnim;
    /* 0x28 */ FishBobber bobber;
    HeldItemModel();
    ~HeldItemModel();
};

#endif
