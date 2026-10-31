#ifndef NPC_NPCEMOTIONFX_H
#define NPC_NPCEMOTIONFX_H

#include "types.h"
#include "gfx/VecFx32.h"

class SndSeEmitter;

struct NpcEmotionFxSlot {
    /* 0x0 */ s16 effectId;
    /* 0x2 */ u8 triggerFrame;
    /* 0x3 */ u8 repeat;
};

struct NpcEmotionPhase {
    /* 0x0 */ s32 animId;
    /* 0x4 */ const void *fxSlots;
    /* 0x8 */ u8 numFxSlots;
    /* 0x9 */ u8 killPrevFx;
    /* 0xa */ s16 seFrame;
};

struct NpcEmotionFx {
    /* 0x00 */ s32 effects[4];
    /* 0x10 */ NpcEmotionFxSlot slots[2];
    /* 0x18 */ SndSeEmitter *seEmitter;
    /* 0x1c */ s32 slotAnimId;
    /* 0x20 */ s32 entryPart;
    /* 0x24 */ u8 seMode;
    /* 0x25 */ u8 emotionId;
    /* 0x26 */ u8 useGlobalSe;
    /* 0x27 */ u8 effectParam;

    NpcEmotionFx();
    ~NpcEmotionFx();
    void stop();
    void update(VecFx32 *a, s16 b, s32 c, u16 d);
    void killEffects();
    void updateSlot(VecFx32 *a, s16 b, s32 c, u16 d, s32 j);
    void stopSound();
    void keepSound();
    void playSound(NpcEmotionFxSlot *s);
    void startEntry(const NpcEmotionPhase *tbl, s32 idx);
    void setSlots(const void *a, u32 b, s32 c);
    s32 findFreeHandle();
    void copySlots(void *dst, const void *src, s32 n);
    void clearSlots(void *p, s32 n);
    void reset();
};

#endif
