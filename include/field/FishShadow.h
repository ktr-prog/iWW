#ifndef FIELD_FISHSHADOW_H
#define FIELD_FISHSHADOW_H
#include "gfx/CachedModel.h"
#include "gfx/AnimModel.h"
#include "game/CollisionState.h"
#include "gfx/ModelSlotPool.h"
#include "snd/CreatureSndChannel.h"
#include "snd/SndSeEmitter.h"

#include "types.h"
#include "gfx/VecFx32.h"

class FishBobber;


struct FishCroak {
    u8 b0, b1, b2, b3;
};

struct FishShadow {
    FishShadow();
    ~FishShadow();
    /* 0x000 */ SndSeEmitter seEmitter;
    /* 0x040 */ CreatureSndChannel envChannel;
    /* 0x04c */ CollisionState collisionState;
    /* 0x07c */ ModelSlotHandle modelSlot;
    /* 0x07e */ s8 fishId;
    /* 0x07f */ u8 hasFin;
    /* 0x080 */ s32 state;
    /* 0x084 */ CachedModel cachedModel;
    /* 0x120 */ VecFx32Ctor position;
    /* 0x12c */ VecFx32 spawnPos;
    /* 0x138 */ s16 rotY;
    /* 0x13a */ u8 pad_13a[2];
    /* 0x13c */ s32 stateTimer;
    /* 0x140 */ u16 cruiseTimer;
    /* 0x142 */ s16 wobblePhase;
    /* 0x144 */ AnimModel model;
    /* 0x1fc */ u8 spawnState;
    /* 0x1fd */ u8 alpha;
    /* 0x1fe */ u8 habitat;
    /* 0x1ff */ u8 sizeClass;
    /* 0x200 */ u8 moveState;
    /* 0x201 */ u8 appearCount;
    /* 0x202 */ u8 pad_202[2];
    /* 0x204 */ s32 effectHandle;
    /* 0x208 */ Vec2 spawnBlock;
    /* 0x210 */ u8 turnDir;
    /* 0x211 */ u8 slotIndex;
    /* 0x212 */ u16 respawnTimer;
    /* 0x214 */ u8 scareDelay;
    /* 0x215 */ u8 pad_215[3];
    /* 0x218 */ VecFx32Ctor prevPosition;
    /* 0x224 */ u8 biteState;
    /* 0x225 */ u8 biteStep;
    /* 0x226 */ u8 pad_226;
    /* 0x227 */ s8 playerIdx;
    /* 0x228 */ u8 pad_228[4];
    /* 0x22c */ FishBobber *bobber;
    /* 0x230 */ VecFx32Ctor hookPos;
    /* 0x23c */ u8 aiMode;
    /* 0x23d */ u8 biteStepTimer;
    /* 0x23e */ u8 pullDir;
    /* 0x23f */ u8 reelGoal;
    /* 0x240 */ u8 biteDelay;
    /* 0x241 */ u8 pad_241[3];
    /* 0x244 */ s32 despawnTimer;
    /* 0x248 */ FishCroak croak;
};

#endif
