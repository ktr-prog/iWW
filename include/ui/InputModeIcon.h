#ifndef UI_INPUTMODEICON_H
#define UI_INPUTMODEICON_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"

class InputModeIcon : public UiWidget {
public:
    InputModeIcon();
    virtual ~InputModeIcon();
    virtual void draw();
    virtual void update();

    void startModeAnim();
    BOOL isDrawBlocked();
    void exit();
    void init();

    /* 0x0c */ s32 inputMode;
    /* 0x10 */ s32 shownMode;
    /* 0x14 */ SpriteAnim anim;
    /* 0x28 */ u8 isVisible;
};

#endif
