#ifndef MENU_KEYBOARD_H
#define MENU_KEYBOARD_H

#include "types.h"
#include "nitro/gxoam.h"
#include "gfx/BgVramTask.h"
#include "ui/LabelString.h"

class Keyboard {
public:
    Keyboard() : bgTasks(), labels() {}
    ~Keyboard() {}

    /* 0x0000 */ u16 flags;
    /* 0x0002 */ u8 page;
    /* 0x0003 */ u8 selectedEmotion;
    /* 0x0004 */ u8 emotionCount;
    /* 0x0005 */ u8 copyKeyPalette;
    /* 0x0006 */ u8 pasteKeyPalette;
    /* 0x0007 */ u8 mode;
    /* 0x0008 */ u8 pressTimer;
    /* 0x0009 */ u8 unk_09[3];
    /* 0x000c */ s32 disabledSlots;
    /* 0x0010 */ s32 pressedKey;
    /* 0x0014 */ s32 cursorKey;
    /* 0x0018 */ s32 cursorX;
    /* 0x001c */ s32 cursorY;
    /* 0x0020 */ s32 knobGripX;
    /* 0x0024 */ s32 knobGripY;
    /* 0x0028 */ u8 emotionSlots[4];
    /* 0x002c */ u8 keyRepeatTimer;
    /* 0x002d */ u8 typedRunLength;
    /* 0x002e */ u8 layout;
    /* 0x002f */ u8 cursorWrap;
    /* 0x0030 */ GXOamAttr *tabCells;
    /* 0x0034 */ u8 keyChars[0x22c0];
    /* 0x22f4 */ BgVramTask bgTasks[2];
    /* 0x233c */ LabelString labels[2];
    /* 0x23bc */ u8 screenBuf[0x800];
    /* 0x2bbc */ u8 emotionIconBuf[0x1000];
};

#endif
