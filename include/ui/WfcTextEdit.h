#ifndef UI_WFCTEXTEDIT_H
#define UI_WFCTEXTEDIT_H

#include "types.h"
#include "nitro/gxoam.h"

struct WfcTextCanvas;

struct WfcTextEdit {
    /* 0x00 */ WfcTextCanvas *textCanvas;
    /* 0x04 */ GXOamAttr *caretOam;
    /* 0x08 */ u8 text[0x20];
    /* 0x28 */ u8 unk_28;
    /* 0x29 */ u8 textLen;
    /* 0x2a */ u8 result;
};

#endif
