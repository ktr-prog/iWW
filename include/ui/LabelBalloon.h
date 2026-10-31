#ifndef UI_LABELBALLOON_H
#define UI_LABELBALLOON_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"
#include "talk/LabelBalloonText.h"

class TextLabel;
class StrBuf;

class LabelBalloon : public UiWidget {
public:
    LabelBalloon(s32 flag);
    virtual ~LabelBalloon();
    virtual void draw();
    virtual void update();

    void updateScreenClamp();
    void freeLabels();
    void createLabels();
    void fitToText();
    void initAnims();
    void reset();
    s32 getWidth();
    s32 getPosY();
    s32 getPosX();
    s32 getDrawY();
    s32 getDrawX();
    SpriteAnim *getAnim();
    s32 getState();
    void updateClosing();
    void enterClosing();
    void updateOpen();
    void enterOpen();
    void updateOpening();
    void enterOpening();
    void updateClosed();
    void enterClosed();
    BOOL requestClose();
    BOOL requestOpen();
    void refreshText(s32 flag);
    void setClampToScreen(u8 v);
    void enableCenterText();
    void setText(StrBuf *src);
    void setPos(s32 a, s32 b);
    void hideLayer2();
    void showLayer2();
    void setPopUpward();
    void setPopDownward();
    void disablePopAnim();
    void disableObjWindow();
    void enableObjWindow();

    /* 0x0c */ SpriteAnim layer1;
    /* 0x20 */ SpriteAnim layer2;
    /* 0x34 */ s32 state;
    /* 0x38 */ s32 animTimer;
    /* 0x3c */ s32 x;
    /* 0x40 */ s32 posY;
    /* 0x44 */ s32 priority;
    /* 0x48 */ s32 popOffsetX;
    /* 0x4c */ s32 popOffsetY;
    /* 0x50 */ s32 clampOffsetX;
    /* 0x54 */ u8 openRequest;
    /* 0x55 */ u8 closeRequest;
    /* 0x56 */ u8 onBufferA;
    /* 0x57 */ u8 clampToScreen;
    /* 0x58 */ u8 objWindow;
    /* 0x59 */ u8 noPopAnim;
    /* 0x5a */ u8 popDownward;
    /* 0x5b */ u8 layer2Visible;
    /* 0x5c */ u8 centerText;
    /* 0x60 */ LabelBalloonText text;
    /* 0x88 */ LabelBalloonText text2;
    /* 0xb0 */ TextLabel *label;
    /* 0xb4 */ TextLabel *label2;
    /* 0xb8 */ s32 textMode;
};

#endif
