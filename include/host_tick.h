#ifndef HOST_TICK_H
#define HOST_TICK_H

#include "types.h"

#ifdef HOST
extern "C" s32 HostTick_Steps(void);
extern "C" s32 HostTick_Part(s32 x);
extern "C" s32 HostTick_Rate(s32 r);
extern "C" s32 HostTick_Div(s32 x);
extern "C" BOOL HostTick_StepEnds(void);
#define TICK_STEPS() HostTick_Steps()
#define TICK_PART(x) HostTick_Part(x)
#define TICK_RATE(r) HostTick_Rate(r)
#define TICK_DIV(x) HostTick_Div(x)
#define TICK_STEP_ENDS() HostTick_StepEnds()
#else
#define TICK_STEPS() 1
#define TICK_PART(x) (x)
#define TICK_RATE(r) (r)
#define TICK_DIV(x) (x)
#define TICK_STEP_ENDS() TRUE
#endif

#endif
