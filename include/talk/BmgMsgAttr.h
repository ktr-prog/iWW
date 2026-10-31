#ifndef TALK_BMGMSGATTR_H
#define TALK_BMGMSGATTR_H

#include "types.h"

struct BmgMsgAttr;
extern "C" BmgMsgAttr *BmgMsgAttr_Init(BmgMsgAttr *s);
extern "C" void BmgMsgAttr_Fini();
struct BmgMsgAttr {
    BmgMsgAttr() { BmgMsgAttr_Init(this); }
    ~BmgMsgAttr() { BmgMsgAttr_Fini(); }
    /* 0x00 */ u32 textOffset;
    /* 0x04 */ u8 windowStyle;
    /* 0x05 */ u8 friendshipDelta;
    /* 0x06 */ u8 startEvent;
    /* 0x07 */ u8 endEvent;
    /* 0x08 */ u8 nextMsg;
    /* 0x09 */ u8 msgSe;
    /* 0x0a */ u8 unk_0a;
    /* 0x0b */ u8 unk_0b;
};

#endif
