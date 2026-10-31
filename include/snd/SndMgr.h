#ifndef SND_SNDMGR_H
#define SND_SNDMGR_H

#include "types.h"

#include "snd/SndSeqHandle.h"

class SndSceneBase;
class BgmBeatSync;
struct MelodyPlayer;

struct SndRamp {
    /* 0x00 */ s16 target;
    /* 0x02 */ u16 frames;
    /* 0x04 */ s32 value;
    /* 0x08 */ s32 step;
};

class SndMgr {
public:
    SndMgr();
    void init(void *heap, u32 size, const char *arcPath);
    void update();
    void volumeOff();
    void volumeOn();
    void setOutputMode(u32 v);
    void startOutputEffect();
    void stopAll();

    /* 0x00 */ BgmBeatSync *beatSync;
    /* 0x04 */ SndRamp fadeRamp;
    /* 0x10 */ SndRamp mainRamp;
    /* 0x1c */ SndRamp subRamp;
    /* 0x28 */ void *subHeap;
    /* 0x2c */ SndSceneBase *scene;
    /* 0x30 */ MelodyPlayer *melody;
    /* 0x34 */ SndSeqHandle strmHandle;
    /* 0x38 */ SndSeqHandle seHandle;
    /* 0x3c */ SndSeqHandle bgmHandle;
    /* 0x40 */ SndSeqHandle auxSeHandle;
    /* 0x44 */ u32 voiceType;
    /* 0x48 */ SndSeqHandle voiceHandle;
    /* 0x4c */ u8 unk_4c;
    /* 0x4d */ u8 seDisabled;
    /* 0x4e */ u8 unk_4e[2];
    /* 0x50 */ u32 outputMode;
    /* 0x54 */ u32 randState;
    /* 0x58 */ u32 randMul;
    /* 0x5c */ u32 randAdd;
    /* 0x60 */ u8 menuDuck;
    /* 0x61 */ u8 subDucked;
    /* 0x62 */ u8 keepHeap;
    /* 0x63 */ u8 unk_63;
    /* 0x64 */ u16 trackMask;
    /* 0x66 */ u16 unk_66;
    /* 0x68 */ s32 strmTotalTime;
    /* 0x6c */ s16 variantTimer;
    /* 0x6e */ u16 crossTrackMask;
    /* 0x70 */ u8 pan;
    /* 0x71 */ u8 keySeMode;
    /* 0x72 */ u8 curveDelay;
    /* 0x73 */ u8 trackVariant;
    /* 0x74 */ u8 pendingVariant;
    /* 0x75 */ u8 variantDirty;
    /* 0x76 */ u8 unk_76[2];
};

#endif
