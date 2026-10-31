#ifndef ITEM_LETTER_H
#define ITEM_LETTER_H

#include "types.h"

#define LETTER_DS_VTABLE 0x020dd458u

class Letter {
public:
    Letter();
    ~Letter();

    /* 0x00 */ u32 dsVtable;
    /* 0x04 */ u8 unk_04[0xec];
    /* 0xf0 */ u16 present;
    /* 0xf2 */ u16 pad_f2;
};

static_assert(sizeof(Letter) == 0xf4, "Letter: DS save layout");
static_assert(__builtin_offsetof(Letter, present) == 0xf0, "Letter::present");

#endif
