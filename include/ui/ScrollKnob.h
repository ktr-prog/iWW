#ifndef UI_SCROLLKNOB_H
#define UI_SCROLLKNOB_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"

class ScrollKnob : public UiWidget {
public:
    ScrollKnob(u32 flag);
    virtual ~ScrollKnob();
    virtual void draw();
    virtual void update();

    BOOL areAnimsDone();
    s32 getState();
    void setState(s32 idx);
    void getAnimOffset(s32 *a, s32 *b);
    void setPriority(s32 v);
    void moveTo(s32 x, s32 y);

    /* 0x0c */ s32 layer1;
    /* 0x10 */ s32 posY;
    /* 0x14 */ SpriteAnim layerAnim1;
    /* 0x28 */ SpriteAnim priority;
    /* 0x3c */ s32 state;
    /* 0x40 */ u8 anim;
    /* 0x44 */ s32 drawPriority;
};

#endif
