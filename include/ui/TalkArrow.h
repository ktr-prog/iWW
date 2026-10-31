#ifndef UI_TALKARROW_H
#define UI_TALKARROW_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"

class TalkArrow : public UiWidget {
public:
    TalkArrow(u8 flag);
    virtual ~TalkArrow();
    virtual void draw();
    virtual void update();

    BOOL isAnimDone();
    s32 getState();
    void setState(s32 idx);
    void setOffset(s32 x, s32 y);
    void setAltStyle();

    /* 0x0c */ SpriteAnim anim;
    /* 0x20 */ SpriteAnim subAnim;
    /* 0x34 */ s32 state;
    /* 0x38 */ s32 offsetX;
    /* 0x3c */ s32 offsetY;
    /* 0x40 */ u8 useAltStyle;
    /* 0x41 */ u8 unk_41;
};

#endif
