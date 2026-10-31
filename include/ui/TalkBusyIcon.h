#ifndef UI_TALKBUSYICON_H
#define UI_TALKBUSYICON_H

#include "types.h"
#include "ui/UiWidget.h"

class TalkBusyIcon : public UiWidget {
public:
    TalkBusyIcon();
    virtual ~TalkBusyIcon();
    virtual void draw();
    virtual void update();
    void stopSe();
    void startSe();
    void updateShown();
    void enterShown();
    void updateHidden();
    void enterHidden();
    void setPos(s32 a, s32 b);
    void callDraw();
    void callUpdate();
    void exit();
    void init();
    void requestHide();
    void requestShow(u32 v);

    /* 0x0c */ s32 state;
    /* 0x10 */ u16 rotation;
    /* 0x12 */ u8 objWindow;
    /* 0x13 */ u8 showRequested;
    /* 0x14 */ s32 posX;
    /* 0x18 */ s32 posY;
    /* 0x1c */ s32 seIndex;
    /* 0x20 */ u8 sePlaying;
};

#endif
