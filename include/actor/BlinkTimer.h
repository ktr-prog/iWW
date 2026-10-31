#ifndef ACTOR_BLINKTIMER_H
#define ACTOR_BLINKTIMER_H

#include "types.h"

extern "C" void BlinkTimer_Construct();
extern "C" void BlinkTimer_Destruct();
struct BlinkTimer {
    BlinkTimer() { BlinkTimer_Construct(); }
    ~BlinkTimer() { BlinkTimer_Destruct(); }
    /* 0x00 */ u32 unk_00;
};

#endif
