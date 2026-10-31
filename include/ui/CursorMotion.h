#ifndef UI_CURSORMOTION_H
#define UI_CURSORMOTION_H

#include "types.h"

class CursorMotion {
public:
    CursorMotion();
    virtual ~CursorMotion();

    BOOL isMoving();
    void startEase(s32 x, s32 y, s32 n);
    void startLinear(s32 x, s32 y, s32 n);
    void setPos(s32 x, s32 y);
    void stop();
    s32 getY();
    s32 getX();
    BOOL update();
    void reset();

    /* 0x04 */ s32 posX;
    /* 0x08 */ s32 posY;
    /* 0x0c */ s32 stepX;
    /* 0x10 */ s32 stepY;
    /* 0x14 */ u8 framesLeft;
    /* 0x15 */ u8 mode;
};

#endif
