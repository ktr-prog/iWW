#ifndef UI_HANDCURSOR_H
#define UI_HANDCURSOR_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"

class HandCursor : public UiWidget {
public:
    HandCursor(BOOL flag);
    virtual ~HandCursor();
    virtual void draw();
    virtual void update();

    BOOL isAnimDone();
    s32 getAnim();
    void setAnimAtEnd(s32 idx);
    void setAnim(s32 idx);
    void setPos(s32 a, s32 b);
    void disableObjWindow();
    void enableObjWindow();

    /* 0x0c */ SpriteAnim layer1;
    /* 0x20 */ s32 posX;
    /* 0x24 */ s32 posY;
    /* 0x28 */ s32 priority;
    /* 0x2c */ SpriteAnim layer2;
    /* 0x40 */ s32 anim;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 onBufferA;
    /* 0x49 */ u8 hasLayer2;
    /* 0x4a */ u8 objWindow;
};

#endif
