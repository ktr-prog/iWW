#ifndef FIELD_INSECT_H
#define FIELD_INSECT_H

#include "types.h"
#include "gfx/ModelAnim.h"
#include "game/CollisionState.h"
#include "gfx/AnimModel.h"
#include "game/BugNetTarget.h"
#include "gfx/PooledModel.h"
#include "snd/CreatureSndChannel.h"
#include "gfx/Mtx43.h"
#include "gfx/ModelSlotPool.h"
#include "game/FxVec3.h"
#include "gfx/VecFx32.h"

class InsectMatAnim : public ModelAnim {
public:
    InsectMatAnim();
    virtual ~InsectMatAnim();
    static void *operator new(size_t, void *p) { return p; }
};

class Insect {
public:
    Insect();
    ~Insect();

    void antsAppear();
    void insectFleeFrom(VecFx32 *p);
    BOOL insectFindFlowerTarget(s16 *out, s32 *dist, VecFx32 *pos);
    void insectWanderSteer(s16 *p, s32 a, s32 b, u8 thr, s32 sc);
    void beeChasePlayer();
    void beeSwarmDescend();
    void beeEnterSwarm();
    void mosquitoChase(s16 *p);
    BOOL spiderSway();
    BOOL spiderCheckPlayerHit();
    void dungBeetlePushSnowball();
    void dungBeetleWalk();
    void hovererFly();

    /* 0x000 */ InsectMatAnim matAnim;
    /* 0x020 */ CollisionState collisionState;
    /* 0x050 */ AnimModel model;
    /* 0x108 */ BugNetTarget bugNetTarget;
    /* 0x130 */ PooledModel pooledModel;
    /* 0x170 */ void (*updateFn)(Insect *);
    /* 0x174 */ CreatureSndChannel seEmitter;
    /* 0x180 */ Mtx43 handMtx;
    /* 0x1b0 */ VecFx32Ctor wanderBoxMin;
    /* 0x1bc */ VecFx32Ctor wanderBoxMax;
    /* 0x1c8 */ VecFx32Ctor homePos;
    /* 0x1d4 */ VecFx32Ctor targetPos;
    /* 0x1e0 */ VecFx32Ctor perchPos;
    /* 0x1ec */ FxVec3 feelers[2];
    /* 0x204 */ VecFx32Ctor position;
    /* 0x210 */ VecFx32Ctor scale;
    /* 0x21c */ s32 behaviorWork;
    /* 0x220 */ s32 targetHeight;
    /* 0x224 */ s32 disturbRadius;
    /* 0x228 */ s32 baseHeight;
    /* 0x22c */ s32 effectHandle;
    /* 0x230 */ ModelSlotHandle modelSlot;
    /* 0x232 */ s16 auxTimer;
    /* 0x234 */ s16 outOfViewTimer;
    /* 0x236 */ s16 despawnTimer;
    /* 0x238 */ s16 rotX;
    /* 0x23a */ s16 rotY;
    /* 0x23c */ s16 rotZ;
    /* 0x23e */ s16 unk_23e;
    /* 0x240 */ s16 turnAngle;
    /* 0x242 */ s16 stateTimer;
    /* 0x244 */ s16 waitTimer;
    /* 0x246 */ u8 canSing;
    /* 0x247 */ u8 playerHoldsNet;
    /* 0x248 */ u8 inUse;
    /* 0x249 */ u8 inView;
    /* 0x24a */ u8 isAlarmed;
    /* 0x24b */ u8 unk_24b;
    /* 0x24c */ u8 unk_24c;
    /* 0x24d */ s8 kind;
    /* 0x24e */ s8 hitCountdown;
    /* 0x24f */ u8 frameCounter;
    /* 0x250 */ u8 lifeState;
    /* 0x251 */ u8 state;
    /* 0x252 */ u8 cooldownTimer;
    /* 0x253 */ u8 turnDelay;
    /* 0x254 */ u8 alarm;
    /* 0x255 */ u8 alarmThreshold;
    /* 0x256 */ u8 unk_256;
    /* 0x257 */ u8 moveSpeed;
    /* 0x258 */ u8 inViewMask;
    /* 0x259 */ u8 moveTargetDist;
    /* 0x25a */ u8 pad_25a[2];
};

#endif
