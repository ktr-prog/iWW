#ifndef MENU_INVENTORYGRIDTYPES_H
#define MENU_INVENTORYGRIDTYPES_H

#include "types.h"


struct InvItemStackPad {
    /* 0x00 */ s32 v[2];
    InvItemStackPad() {}
    ~InvItemStackPad() {}
};

struct OamObjTemplate {
    union {
        u8 b[8];
        struct {
            /* 0x00 */ u32 attr01;
            /* 0x04 */ u16 attr2;
            /* 0x06 */ u16 attr3;
        } attr;
    };

    u32 charName() const { return attr.attr2 & 0x3ff; }
    void setCharName(u32 name) { attr.attr2 = (attr.attr2 & 0xfc00) | (name & 0x3ff); }
    void setPalette(u32 pal) { attr.attr2 = (attr.attr2 & 0x0fff) | ((pal & 0xf) << 12); }
};

struct Bitset64 {
    /* 0x00 */ u32 words[2];
};

struct OamAffineMtx {
    /* 0x00 */ s32 v[4];
};

#endif
