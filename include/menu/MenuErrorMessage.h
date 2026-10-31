#ifndef MENU_MENUERRORMESSAGE_H
#define MENU_MENUERRORMESSAGE_H

#include "types.h"
#include "ui/TouchPromptBalloon.h"
#include "talk/TalkMsgRequest.h"

class MenuErrorMessage {
public:
    MenuErrorMessage();
    ~MenuErrorMessage();

    void restoreBrightness();
    void dimSubScreen();
    BOOL finishTalk();
    void advanceTalk();
    BOOL isTalkWaiting();
    void undim();
    void hidePromptBalloon();
    void updatePromptBalloon();
    void showPromptOnly();
    BOOL stepClose();
    void beginClose();
    BOOL stepOpen();
    void startTalk(u8 *a, s32 b);
    BOOL update(s32 a);
    void openHigh(u8 *a, s32 b, u32 c);
    void open(u8 *a, s32 b, u32 c);

    /* 0x00 */ TouchPromptBalloon prompt;
    /* 0xc0 */ TalkMsgRequest talk;
    /* 0x104 */ u8 state;
    /* 0x105 */ u8 isFatal;
};

#endif
