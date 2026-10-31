#ifndef ITEM_LETTERVIEW_H
#define ITEM_LETTERVIEW_H

#include "types.h"

struct LetterParty {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk_04[0x12];
    /* 0x16 */ u8 partyType;
    /* 0x17 */ u8 pad_17;
};

class LetterView {
public:
    void loadDefaultGreeting();
    BOOL isToFutureSelf();
    void setState(u32 v);
    u8 getState();
    u32 setPresent(u16 v, u32 w);
    void setPresentFlags(u32 v);
    u8 getPresentFlags();
    u16 getPresent();

    /* 0x00 */ u32 vtable;
    /* 0x04 */ LetterParty recipient;
    /* 0x1c */ LetterParty sender;
    /* 0x34 */ u8 greeting[0x18];
    /* 0x4c */ u8 body[0x80];
    /* 0xcc */ u8 signature[0x20];
    /* 0xec */ u8 namePos;
    /* 0xed */ u8 paper;
    /* 0xee */ u8 status;
    /* 0xef */ u8 kind;
    /* 0xf0 */ u16 present;
    /* 0xf2 */ u16 pad_f2;
};

static_assert(sizeof(LetterView) == 0xf4, "LetterView: the bytes of a Letter");

#endif
