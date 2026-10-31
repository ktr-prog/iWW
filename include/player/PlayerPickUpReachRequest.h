#ifndef PLAYER_PLAYERPICKUPREACHREQUEST_H
#define PLAYER_PLAYERPICKUPREACHREQUEST_H

#include "types.h"
#include "player/PlayerPickUpReachArgs.h"
#include "player/PlayerAct10Args.h"


struct PlayerPickUpReachRequest {
    /* 0x00 */ u32 action, priority, netSeq;
    /* 0x0c */ PlayerPickUpReachArgs args;
    /* 0x14 */ u8 pad_14[8];
};

struct PlayerEmotionRequest {
    /* 0x00 */ u32 action, priority, netSeq;
    /* 0x0c */ PlayerNetPickUpReachArgs args;
    /* 0x14 */ u8 pad_14[0x8];
};

struct PlayerAct10Request {
    /* 0x00 */ u32 action, priority, netSeq;
    /* 0x0c */ PlayerAct10Args args;
    /* 0x0e */ u8 pad_0e[0xe];
};

#endif
