#ifndef UI_TOUCHPROMPTBALLOON_H
#define UI_TOUCHPROMPTBALLOON_H

#include "types.h"
#include "ui/LabelBalloon.h"

class TouchPromptBalloon : public LabelBalloon {
public:
    TouchPromptBalloon();
    virtual ~TouchPromptBalloon();

    BOOL isOpenOrOpening();
    void setAutoCloseTimer(u8 v);
    void setPriority(s32 v);
    void cancelQueuedOpen();
    void queueOpen();
    void commitOpen();
    BOOL hide(s32 a);
    s32 updatePrompt();

    /* 0xbc */ u8 promptState;
    /* 0xbd */ u8 openQueued;
    /* 0xbe */ volatile u8 autoCloseTimer;
};

#endif
