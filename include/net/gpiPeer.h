#ifndef NET_GPIPEER_H
#define NET_GPIPEER_H

#include "types.h"
#include "net/gpiBuffer.h"


struct DArrayImplementation;

struct GPIPeer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 initiated;
    /* 0x08 */ s32 sock;
    /* 0x0c */ s32 profile;
    /* 0x10 */ s32 timeout;
    /* 0x14 */ s32 nackCount;
    /* 0x18 */ GPIBuffer inputBuffer;
    /* 0x28 */ GPIBuffer outputBuffer;
    /* 0x38 */ DArrayImplementation *messages;
    /* 0x3c */ GPIPeer *pnext;
};

struct GPIMessage {
    /* 0x00 */ GPIBuffer buffer;
    /* 0x10 */ s32 type;
    /* 0x14 */ s32 start;
};

#endif
