#ifndef PLAYER_HELDTOOLMODEL_H
#define PLAYER_HELDTOOLMODEL_H

#include "types.h"
#include "uptr.h"
#include "npc/NpcResHandle.h"
#include "gfx/Mtx43.h"

class BlendAnimModel;
class NpcActor;

struct HeldToolModel {
    /* 0x00 */ u16 heldItem;
    /* 0x02 */ u8 unk_02[2];
    /* 0x04 */ u8 modelHandle[HOST_SIZED(8, NpcHeldItemModelHandle)] HOST_ALIGN8;
    /* 0x0c */ Mtx43 handMtx;
    /* 0x3c */ u8 visible;
    /* 0x3d */ u8 pad_3d[3];

    ~HeldToolModel() { destroy(); }
    void setModelAnimSpeed(u32 v);
    BlendAnimModel *getModel();
    void setAnimSpeed(u32 v);
    u32 getAnimSpeed();
    void draw(NpcActor *p);
    void update(NpcActor *p);
    void release();
    void playPitfallClimbOutAnim(u32 a, u32 b);
    void playPitfallClimbOutAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playPitfallStuckAnim(u32 a, u32 b);
    void playPitfallStuckAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playPitfallHoleAnim(u32 a, u32 b);
    void playPitfallHoleAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playPitfallFallAnim(u32 a, u32 b);
    void playPitfallFallAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playWalkAnim(u32 a, u32 b);
    void playWalkAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playIdleAnim(u32 a, u32 b);
    void playIdleAnimFor(HeldToolModel *p, u32 a, u32 b);
    void playAnim(u32 a, u32 b, u32 c);
    BOOL attach(NpcActor *a, u16 *b, u32 c, u16 d);
    BOOL load(u16 *item);
    HeldToolModel *destroy();
    HeldToolModel *init();
};

#endif
