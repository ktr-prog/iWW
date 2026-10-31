#ifndef GFX_EFFECTSPLEMITTER_H
#define GFX_EFFECTSPLEMITTER_H

#include "types.h"


struct P;
struct SPLResource;
class EffectEmitterEntry;
class EffectSplEmitter;

struct Unk_020932bc_V16 {
    /* 0x0 */ s16 x, y, z;
    void Set(s32 a, s32 b, s32 c)
    {
        x = a;
        y = b;
        z = c;
    }
};

struct EffectEmitterTag {
    /* 0x0 */ u8 poolIndex;
    /* 0x1 */ u8 group;
    /* 0x2 */ u8 emitterIndex;
    /* 0x3 */ u8 unk_03;
};

struct EffectEmitterCbs {
    /* 0x0 */ void (*unk_00)(EffectEmitterEntry *);
    /* 0x4 */ s32 (*unk_04)(EffectEmitterEntry *);
};

typedef void (*EffectOneShotCb)(EffectSplEmitter *);

typedef void (*EffectSplEmitterCallback)(EffectSplEmitter *emitter, s32 flag);

class EffectSplEmitter {
public:
    s32 spawnLandingEffects(s32 id1, EffectOneShotCb const *d1, s32 id2, EffectOneShotCb const *d2, s32 id3, EffectOneShotCb const *d3, s32 id4,
        EffectOneShotCb const *d4);
    s32 Effect_SpawnParticleLandings(s32 id1, EffectOneShotCb const *d1, s32 id2, EffectOneShotCb const *d2, s32 id3, EffectOneShotCb const *d3, s32 id4,
        EffectOneShotCb const *d4);
    void initKind02();

#ifdef HOST64
    u8 pad_00[0x10];
    P * particles;
    s32 particleCount;
    u8 hpad_0[0x4];
    u8 pad_10[0x10];
    SPLResource * resource;
    u32 stateFlags;
    s32 posX;
    s32 posY;
    s32 posZ;
    u8 pad_2c[0x10];
    Unk_020932bc_V16 axis;
    u8 pad_42[0x2];
    s32 radius;
    s32 length;
    s32 initVelMagPos;
    s32 initVelMagAxis;
    s32 baseScale;
    u16 particleLife;
    u16 color;
    s32 simpleCollisionY;
    u8 pad_60[0x8];
    u8 genInterval;
    u8 baseAlpha;
    u8 pad_6a[0x12];
    EffectSplEmitterCallback callback;
    u8 pad_7c[0x8];
    u8 tintVariant;
    u8 hpad_1[0x7];
#else
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ P *particles;
    /* 0x0c */ s32 particleCount;
    /* 0x10 */ u8 pad_10[8];
    /* 0x18 */ SPLResource *resource;
    /* 0x1c */ u32 stateFlags;
    /* 0x20 */ s32 posX, posY, posZ;
    /* 0x2c */ u8 pad_2c[0x10];
    /* 0x3c */ Unk_020932bc_V16 axis;
    /* 0x42 */ u8 pad_42[2];
    /* 0x44 */ s32 radius;
    /* 0x48 */ s32 length;
    /* 0x4c */ s32 initVelMagPos;
    /* 0x50 */ s32 initVelMagAxis;
    /* 0x54 */ s32 baseScale;
    /* 0x58 */ u16 particleLife;
    /* 0x5a */ u16 color;
    /* 0x5c */ s32 simpleCollisionY;
    /* 0x60 */ u8 pad_60[8];
    /* 0x68 */ u8 genInterval;
    /* 0x69 */ u8 baseAlpha;
    /* 0x6a */ u8 pad_6a[0xe];
    /* 0x78 */ EffectSplEmitterCallback callback;
    /* 0x7c */ u8 pad_7c[4];
    /* 0x80 */ u8 tintVariant;
#endif
};

class EffectEmitterEntry {
public:
    s32 updateLanding5F();
    s32 updateLanding1F1E();
    s32 updateLanding1F1D();
    s32 updateLanding1F1EB();
    BOOL updateKind59();
    BOOL updateKind56Fade();
    BOOL updateKind56Main();
    s32 updateKind54B();
    void initAxisUpForward();
    s32 updateLanding(s32 id1, EffectOneShotCb const *d1, s32 id2, EffectOneShotCb const *d2, s32 id3, EffectOneShotCb const *d3, s32 id4,
        EffectOneShotCb const *d4);

    /* 0x00 */ s32 resourceId;
    /* 0x04 */ EffectEmitterTag tag;
    /* 0x08 */ u8 isActive;
    /* 0x09 */ u8 emitterIndex;
    /* 0x0a */ u8 userIndex;
    /* 0x0c */ EffectSplEmitter *emitter;
    /* 0x10 */ EffectEmitterCbs callbacks;
};

#endif
