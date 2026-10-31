#ifndef MENU_WFCCONNSELECTWORK_H
#define MENU_WFCCONNSELECTWORK_H

#include "types.h"
#include "net/WfcObjGroup.h"

struct WfcConnSelectWork {
    /* 0x00 */ void *paletteFile;
    /* 0x04 */ WfcObjGroup *slotButtons[3];
    /* 0x10 */ WfcObjGroup *eraseButtons[3];
    /* 0x1c */ u8 lastColumn;
    /* 0x1d */ u8 exitAction;
    /* 0x1e */ u8 pad_1e[2];
};

#endif
