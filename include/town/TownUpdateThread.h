#ifndef TOWN_TOWNUPDATETHREAD_H
#define TOWN_TOWNUPDATETHREAD_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "sys/OSThread.h"

class Heap;


struct TownUpdateThread {
    union {
        /* 0x0000 */ OSThread thread;
        struct {
            /* 0x0000 */ u8 pad00[0x64];
            /* 0x0064 */ s32 threadState;
        };
    };
    /* 0x00c0 */ OSThread *callerThread;
    /* 0x00c4 */ Heap *heap;
    /* 0x00c8 */ u8 lastDate[8];
    /* 0x00d0 */ u8 curDate[8];
    /* 0x00d8 */ u32 elapsedDays;
    /* 0x00dc */ u8 prevDayRain;
    /* 0x00dd */ u8 paddd[3];
    /* 0x00e0 */ u32 stackGuardLow;
    /* 0x00e4 */ u8 pade4[0x10e4 - 0xe4];
    /* 0x10e4 */ u32 stackGuardHigh;
    /* 0x10e8 */ u8 hasArgs;
    /* 0x10e9 */ u8 done;
    /* 0x10ea */ u8 started;
};

struct FlowerFxParams {
    /* 0x00 */ s32 mode;
    /* 0x04 */ u8 species;
    /* 0x05 */ u8 color;
    /* 0x06 */ u8 unk_06;
    /* 0x08 */ VecFx32 pos;
    /* 0x14 */ s16 angle;
};

struct TownUpdater {
    /* 0x00 */ u16 seashellTime;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ FlowerFxParams flowerFx;
    /* 0x1c */ u8 beesReleased;
    /* 0x1d */ u8 pad_1d[3];
    /* 0x20 */ TownUpdateThread *updateThread;
    ~TownUpdater() {}
};

#endif
