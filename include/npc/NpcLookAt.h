#ifndef NPC_NPCLOOKAT_H
#define NPC_NPCLOOKAT_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"


class Character;
class NpcActor;

class NpcLookAt {
public:
    NpcLookAt();
    ~NpcLookAt() { clearTargetActor(); }
    u8 lookType;
    u8 pad_01[3];
    Character *targetActor;
    VecFx32 targetPos;
    s32 priority;
    u8 disabled;
    u8 pad_19;
    s16 pitch;
    s16 pitchStep;
    s16 manualPitch;
    s16 pitchLimit;
    s16 yaw;
    s16 yawStep;
    s16 manualYaw;
    s16 yawLimit;
    u8 onTarget;
    u8 pad_2b;
    Mtx43 headMtx;
    s32 maxDistance;
    u8 useYawLimit;
    u8 pad_61[3];
    s32 targetPlayer;

    void lookAtTargetActor(Character *scene);
    void lookAtLocalPlayer(Character *scene);
    void lookAtTargetPlayer(Character *scene);
    void lookAtPlayer(Character *scene, s32 h, s32 limit, u8 flag);
    void relax(Character *);
    void lookAtActor(Character *scene, Character *tgt, VecFx32 *v, s32 limit, u8 flag);
    s32 clampPitch(s32 v);
    s32 calcClampedPitch(VecFx32 *a, VecFx32 *b, s32 c);
    s32 clampYaw(s32 v);
    s32 calcClampedYaw(VecFx32 *a, VecFx32 *b, s32 c);
    s32 calcPitch(VecFx32 *a, VecFx32 *b, s32 c);
    s32 calcYaw(VecFx32 *a, VecFx32 *b, s32 c);
    BOOL canSeeTarget(Character *scene);
    void setManualAngles(s32 pri, s16 a, s16 b, s16 c, s16 d);
    void setTarget(u8 type, s32 pri, Character *tgt, VecFx32 *v, s32 h, s32 lim, u8 flag);
    void setTargetPos(VecFx32 *v);
    void setPitchLimit(s16 v);
    void disable();
    void clearTargetActor();
    u8 getObstacleBits();
    BOOL isOnTarget();
    BOOL isWithinYawLimit(s32 v);
    void update(NpcActor *base);
    void approachManualAngles(Character *);
    void lookAtPoint(Character *o);
    void storeHeadMtx(NpcActor *npc);
};


#endif
