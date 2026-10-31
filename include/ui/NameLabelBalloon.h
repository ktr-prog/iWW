#ifndef UI_NAMELABELBALLOON_H
#define UI_NAMELABELBALLOON_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"
#include "talk/ChatBalloonText.h"

class TextLabel;

class NameLabelBalloon : public UiWidget {
public:
    typedef void (NameLabelBalloon::*Fn)();

    NameLabelBalloon();
    virtual ~NameLabelBalloon();
    virtual void draw();
    virtual void update();

    void fitToLabel();
    void applyKindAnim();
    void updateHiding();
    void enterHiding();
    void updateShown();
    void enterShown();
    void updateAppearing();
    void enterAppearing();
    void updateHidden();
    void enterHidden();
    static void loadKind4Palette();
    BOOL requestHide();
    BOOL requestShow();
    void setText(void *p);
    void setOffset(s32 a, s32 b);
    void release();
    void setKind(s32 a);
    void freeLabel();
    void createLabel();

    /* 0x0c */ s32 kind;
    /* 0x10 */ s32 seqIndex;
    /* 0x14 */ SpriteAnim anim;
    /* 0x28 */ s32 offsetX;
    /* 0x2c */ s32 offsetY;
    /* 0x30 */ s32 slideY;
    /* 0x34 */ s32 alignX;
    /* 0x38 */ ChatBalloonText text;
    /* 0x6c */ TextLabel *textLabel;
    /* 0x70 */ s32 state;
    /* 0x74 */ s32 showRequested;
    /* 0x78 */ s32 stateTimer;
    /* 0x7c */ u8 isVisible;
};

#endif
