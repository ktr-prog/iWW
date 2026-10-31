#ifndef NET_GPITRANSFER_H
#define NET_GPITRANSFER_H

#include "types.h"


struct GPITransferID {
    /* 0x0 */ s32 profileid;
    /* 0x4 */ s32 count;
    /* 0x8 */ s32 time;
};

#endif
