#ifndef NPC_VILLAGERMOOD_H
#define NPC_VILLAGERMOOD_H

#include "types.h"
#include "uptr.h"
#include "snd/SndSeEmitter.h"

class VillagerMood;
class VillagerActor;

typedef void (VillagerMood::*Unk_0201c078_State)(VillagerActor *s);

extern "C" void *VillagerMood_Construct(void *p);
extern "C" void *VillagerMood_Destruct(void *p);
class VillagerMood {
public:
    VillagerMood() { VillagerMood_Construct(this); }
    ~VillagerMood() { VillagerMood_Destruct(this); }
    void update(VillagerActor *s);
    void updateMoodAnim(VillagerActor *s, s32 next);
    BOOL startMoodAnim(VillagerActor *s, u32 idx);
    BOOL isMoodAnimStart(VillagerActor *s);
    void updateMood3Effects(VillagerActor *s);
    BOOL beginMood3Effects(VillagerActor *s);
    void playMood3Effect(VillagerActor *s);
    void updateMood2Effects(VillagerActor *s);
    BOOL beginMood2Effects(VillagerActor *s);
    void playMood2Effect(VillagerActor *s);
    void updateMood1Effects(VillagerActor *s);
    BOOL beginMood1Effects(VillagerActor *s);
    void playMood1EffectB(VillagerActor *s);
    void playMood1EffectA(VillagerActor *s);
    BOOL isMoodAnim(VillagerActor *s);
    BOOL effectsEnabled();
    void disableEffects();
    void enableEffects();
    void updateSoundPos(VillagerActor *s);
    void playMoodEffect(VillagerActor *s, u32 a, u32 b);
    void requestApply();
    void addMood(u32 a, s32 b);
    void clearPending();
    void setMoodAnimation(VillagerActor *s, u32 mode);
    BOOL isActive();
    void stop();
    void start();
    void reset();

    /* 0x00 */ u8 pad_00[HOST_SIZED(0x40, SndSeEmitter)] HOST_ALIGN8;
    /* 0x40 */ u8 currentMood;
    /* 0x44 */ s32 effectMood;
    /* 0x48 */ u8 effectFrame;
    /* 0x4c */ Unk_0201c078_State effectFn;
    /* 0x54 */ u8 pendingMood;
    /* 0x56 */ u16 pendingTime;
    /* 0x58 */ u8 applyRequested;
    /* 0x59 */ u8 active;
    /* 0x5a */ u8 effectsOn;
    /* 0x5b */ u8 severeSickness;
};

#endif
