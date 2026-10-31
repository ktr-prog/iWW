#ifndef NET_DWCNETCHANNEL_H
#define NET_DWCNETCHANNEL_H

#include "types.h"
#include "nitro/math.h"


struct DwcNetChannel {
    /* 0x00 */ u8 *sendData;
    /* 0x04 */ u8 *recvBuffer;
    /* 0x08 */ s32 recvBufSize;
    /* 0x0c */ s32 sentBytes;
    /* 0x10 */ s32 recvBytes;
    /* 0x14 */ s32 sendSize;
    /* 0x18 */ s32 recvSize;
    /* 0x1c */ u8 isSending;
    /* 0x1d */ u8 recvState;
    /* 0x1e */ u8 prevRecvState;
    /* 0x1f */ u8 unk_1f;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 recvType;
    /* 0x24 */ u32 lastRecvTick;
    /* 0x28 */ u32 lastRecvTickHi;
    /* 0x2c */ u32 timeoutMs;
};

struct DwcNetFrameHeader {
    /* 0x0 */ u32 dataSize;
    /* 0x4 */ u16 frameType;
    /* 0x6 */ u8 magic[2];
};

#endif
