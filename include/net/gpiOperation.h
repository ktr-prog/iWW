#ifndef NET_GPIOPERATION_H
#define NET_GPIOPERATION_H

#include "types.h"
#include "net/gpiCallback.h"


struct GPIOperation {
    /* 0x00 */ s32 type;
    /* 0x04 */ void *data;
    /* 0x08 */ s32 blocking;
    /* 0x0c */ GPICallbackCopy callback;
    /* 0x14 */ s32 state;
    /* 0x18 */ s32 id;
    /* 0x1c */ s32 result;
    /* 0x20 */ GPIOperation *pnext;
};


struct GPIConnectData {
    /* 0x000 */ char serverChallenge[0x80];
    /* 0x080 */ char userChallenge[0x21];
    /* 0x0a1 */ char passwordHash[0x21];
    /* 0x0c2 */ char authtoken[0x100];
    /* 0x1c2 */ char partnerchallenge[0x100];
    /* 0x2c2 */ char cdkey[0x42];
    /* 0x304 */ s32 newuser;
};

#endif
