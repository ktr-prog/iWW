#ifndef NET_DWCNETCHANNELTABLE_H
#define NET_DWCNETCHANNELTABLE_H

#include "types.h"
#include "net/DwcNetChannel.h"


struct DwcNetChannelTable {
    /* 0x000 */ DwcNetChannel channels[32];
    /* 0x600 */ void (*sendDoneCallback)(u32 size, u32 aid);
    /* 0x604 */ void (*recvCallback)(u32 aid, u8 *data, u32 size);
    /* 0x608 */ void (*recvTimeoutCallback)(u32 aid);
    /* 0x60c */ void (*pingCallback)(u32 latency, u32 aid);
    /* 0x610 */ u16 maxChunkSize;
    /* 0x612 */ u16 unk_612;
};

#endif
