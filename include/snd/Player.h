#ifndef SND_PLAYER_H
#define SND_PLAYER_H

#include "types.h"
#include "sys/FndList.h"
#include "snd/SndSeBytes4.h"
#include "snd/SndSeqHandle.h"

struct Player {
    /* 0x00 */ FndList list;
    /* 0x0c */ u32 active;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ Bytes4 groupParams;
    /* 0x1c */ u32 heapLevel;
    /* 0x20 */ SndSeqHandle unk_20;
    /* 0x24 */ SndSeqHandle unk_24;
};

#endif
