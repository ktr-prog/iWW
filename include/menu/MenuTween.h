#ifndef MENU_MENUTWEEN_H
#define MENU_MENUTWEEN_H

#include "types.h"

class MenuTween {
public:
    MenuTween();
    virtual ~MenuTween();
    /* 0x04 */ s32 stepSize;
    /* 0x08 */ s32 progress;
    s32 scaleLinear(s32 v);
    s32 scaleQuadratic(s32 v);
    BOOL step();
    void start(u32 n);
};

#endif
