#ifndef ACTOR_CHARAFACEANIMWORKREF_H
#define ACTOR_CHARAFACEANIMWORKREF_H

#include "types.h"

struct CharaFaceAnimWorkRef {
    /* 0x00 */ u8 v;
    CharaFaceAnimWorkRef();
    ~CharaFaceAnimWorkRef();
    void *getHeap();
    void assign(u32 x);
};

#endif
