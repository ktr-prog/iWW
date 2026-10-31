#ifndef NET_GPICALLBACK_H
#define NET_GPICALLBACK_H

#include "types.h"


typedef void (*GPCallback)(void *, void *, void *);

struct GPICallback {
    /* 0x0 */ GPCallback callback;
    /* 0x4 */ void *param;
};

struct GPICallbackCopy {
    /* 0x0 */ GPICallback p;
};

struct GPICallbackData {
    /* 0x00 */ GPCallback callback;
    /* 0x04 */ void *param;
    /* 0x08 */ void *arg;
    /* 0x0c */ s32 type;
    /* 0x10 */ s32 operationID;
    /* 0x14 */ GPICallbackData *pnext;
};

#endif
