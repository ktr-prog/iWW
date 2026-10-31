#ifndef ROOM_ROOMITEMDROP_H
#define ROOM_ROOMITEMDROP_H
#include "snd/SndSeEmitter.h"

#include "types.h"
#include "gfx/VecFx32.h"

class RoomItemDrop {
public:
    RoomItemDrop();
    ~RoomItemDrop();

    /* 0x00 */ s32 group;
    /* 0x04 */ s32 state;
    /* 0x08 */ u16 item;
    /* 0x0a */ u16 landItem;
    /* 0x0c */ s32 isStill;
    /* 0x10 */ s32 unitX;
    /* 0x14 */ s32 unitZ;
    /* 0x18 */ VecFx32 landPos;
    /* 0x24 */ VecFx32 pos;
    /* 0x30 */ VecFx32 velocity;
    /* 0x3c */ VecFx32 scale;
    /* 0x48 */ s16 unk_48;
    /* 0x4a */ s16 unk_4a;
    /* 0x4c */ SndSeEmitter seEmitter;
    /* 0x8c */ s8 bounceCount;
    /* 0x8d */ u8 frameCount;
    /* 0x8e */ u8 unk_8e;
    /* 0x8f */ u8 needsSettle;
    /* 0x90 */ u8 onFtrSurface;
    /* 0x91 */ u8 pad_91[3];
};

#endif
