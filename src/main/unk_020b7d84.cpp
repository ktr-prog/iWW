#include "types.h"
#include "host_tick.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/main/unk_020b7d84.h"

extern "C" {
}

extern "C" {
}


extern "C" void Touch_Init(void) {
    TouchPanel_Init();
    gTouchHoldFrames = 0;
    sTouchReleaseFrames = 0xc8;
    sTouchPrevHoldFrames = 0;
    sTouchPrevReleaseFrames = 0xc8;
}

extern "C" void Touch_Update(void) {
    sTouchPrevPressX = gTouchPressX;
    sTouchPrevPressY = gTouchPressY;
    sTouchPrevCurX = gTouchCurX;
    sTouchPrevCurY = gTouchCurY;
    sTouchPrevHoldFrames = gTouchHoldFrames;
    sTouchPrevReleaseFrames = sTouchReleaseFrames;
    u8 t = gTouchHeld;
    gTouchPrevHeld = t;
    gTouchPrevChanged = gTouchChanged ? 1 : 0;
    sTouchPrevRawX = (u8)gTouchX;
    sTouchPrevRawY = (u8)gTouchY;
    if ((s32)(*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15) {
        gTouchChanged = t;
        gTouchHeld = 0;
        gTouchX = 0;
        gTouchY = 0;
    } else {
        TouchPanel_Update();
    }
    if (gTouchHeld != 0) {
        BOOL p = (gTouchHeld != 0 && gTouchChanged != 0) ? TRUE : FALSE;
        if (p) {
            gTouchPressX = gTouchX;
            gTouchPressY = gTouchY;
            gTouchHoldFrames = 0;
        }
        if (gTouchHoldFrames < 0xc8) {
            gTouchHoldFrames += TICK_STEP_ENDS() ? 1 : 0;
        }
        u8 v = gTouchX;
        gTouchCurX = v;
        gTouchCurY = gTouchY;
        Snd_SetPan(v);
    } else {
        BOOL p = (gTouchHeld == 0 && gTouchChanged != 0) ? TRUE : FALSE;
        if (p) {
            sTouchReleaseFrames = 0;
        }
        if (sTouchReleaseFrames < 0xc8) {
            sTouchReleaseFrames += TICK_STEP_ENDS() ? 1 : 0;
        }
    }
}


u8 sTouchPrevHoldFrames;

u8 sTouchReleaseFrames;

u8 gTouchPressX;

u8 gTouchPressY;

u8 gTouchCurX;

u8 gTouchCurY;

u8 sTouchPrevPressX;

u8 sTouchPrevPressY;

u8 sTouchPrevCurX;

u16 sTouchPrevRawY;

u16 sTouchPrevRawX;

u8 sTouchPrevCurY;

u8 sTouchPrevReleaseFrames;
