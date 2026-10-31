#ifndef MENU_NUMBERPAD_H
#define MENU_NUMBERPAD_H

#include "types.h"
#include "gfx/BgVramTask.h"
#include "ui/LabelString.h"

class NumberPad {
public:
    NumberPad();
    ~NumberPad();

    void flushScreens();
    void update();
    void shutdown();
    void loadObj();
    void loadBg();
    void init(u32 mode, u32 a, u32 b);

    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 repeatTimer;
    /* 0x03 */ u8 highlightTimer;
    /* 0x04 */ u8 pressedKey;
    /* 0x05 */ u8 cursorKey;
    /* 0x06 */ u8 labelCount;
    /* 0x07 */ u8 entryMode;
    /* 0x08 */ u8 layout;
    /* 0x09 */ u8 objVariant;
    /* 0x0a */ u8 mainLayer;
    /* 0x0b */ u8 keyLayer;
    /* 0x0c */ s32 value;
    /* 0x10 */ s32 maxValue;
    /* 0x14 */ s32 topAmount;
    /* 0x18 */ s32 bottomAmount;
    /* 0x1c */ s32 shownTopAmount;
    /* 0x20 */ s32 shownBottomAmount;
    /* 0x24 */ u8 unk_24[8];
    /* 0x2c */ LabelString labels[5];
    /* 0x16c */ BgVramTask screenTasks[2];
    /* 0x1b4 */ u16 mainScreen[0x400];
    /* 0x9b4 */ u16 keyScreen[0x400];
};

#endif
