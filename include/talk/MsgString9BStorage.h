#ifndef TALK_MSGSTRING9BSTORAGE_H
#define TALK_MSGSTRING9BSTORAGE_H

#include "types.h"
#include "talk/MsgString9B.h"


struct MsgString9BStorage {
    alignas(MsgString9B) u8 v[sizeof(MsgString9B)];
};

#endif
