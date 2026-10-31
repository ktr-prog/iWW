#ifndef UI_LABELBUTTON_H
#define UI_LABELBUTTON_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"
#include "talk/MsgString.h"

class TextLabel;

class LabelButtonText : public MsgString {
public:
    LabelButtonText();
    virtual ~LabelButtonText();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x12 */ u8 unk_12[9];
};

class LabelButton : public UiWidget {
public:
    LabelButton(u8 a, s32 b);
    virtual ~LabelButton();
    virtual void draw();
    virtual void update();

    void syncTextColor();
    void freeLabel();
    void createLabel();
    BOOL isAnimDone();
    s32 getState();
    void setState(s32 v);
    void getAnimOffset(s32 *x, s32 *y);
    void setPos(s32 x, s32 y);
    void setLabelText(MsgString *src);
    void showLayer2();
    void hideLayer2();
    void enableObjWindow();

    /* 0x0c */ s32 posX;
    /* 0x10 */ s32 posY;
    /* 0x14 */ s32 palette;
    /* 0x18 */ s32 kind;
    /* 0x1c */ SpriteAnim layer1;
    /* 0x30 */ SpriteAnim layer2;
    /* 0x44 */ s32 state;
    /* 0x48 */ TextLabel *label;
    /* 0x4c */ LabelButtonText text;
    /* 0x68 */ u16 textColor;
    /* 0x6a */ u8 onBufferA;
    /* 0x6b */ u8 objWindow;
    /* 0x6c */ u8 layer2Hidden;
    /* 0x6d */ u8 textColorDirty;
};

#endif
