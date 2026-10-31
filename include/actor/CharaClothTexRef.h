#ifndef ACTOR_CHARACLOTHTEXREF_H
#define ACTOR_CHARACLOTHTEXREF_H

#include "types.h"

struct CharaClothTexRef {
    /* 0x00 */ u8 v;
    CharaClothTexRef();
    ~CharaClothTexRef();
    void loadItem(u16 *s, void *playerData, s32 b, s32 c);
    void setSlot(u32 x);
    void release();
    void assign(u32 x);
};

#endif
