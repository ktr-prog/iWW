#ifndef MENU_INVENTORYBG_H
#define MENU_INVENTORYBG_H

#include "types.h"
#include "gfx/BgVramTask.h"
#include "ui/LabelString.h"

class InventoryBg {
public:
    InventoryBg();
    ~InventoryBg();

    /* 0x000 */ s32 shownBells;
    /* 0x004 */ s32 bellStep;
    /* 0x008 */ u16 dirtyFlags;
    /* 0x00a */ u16 bellsColorA;
    /* 0x00c */ u16 bellsColorB;
    /* 0x00e */ u8 bgId;
    /* 0x00f */ u8 paintedHighlight;
    /* 0x010 */ u8 highlight;
    /* 0x011 */ u8 blinkHighlight;
    /* 0x012 */ u8 blinkTimer;
    /* 0x013 */ u8 bellRollTimer;
    /* 0x014 */ u8 pictureIndex;
    /* 0x015 */ u8 unk_15;
    /* 0x016 */ u8 palette[0x1c];
    /* 0x032 */ u16 bellsColor;
    /* 0x034 */ u8 unk_34[4];
    /* 0x038 */ BgVramTaskPair vramTasks[3];
    /* 0x0e0 */ LabelString textWindows[2];
    /* 0x160 */ u16 screen[0x400];
    /* 0x960 */ u8 picture[0xc80];
};

#endif
