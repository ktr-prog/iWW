#ifndef NET_NATNEG_H
#define NET_NATNEG_H

#include "types.h"
#include "net/SockAddrIn.h"


typedef void (*NegotiateProgressFunc)(s32 state, void *user);
typedef void (*NegotiateCompletedFunc)(s32 code, s32 fd, void *arg, void *user);

struct _NATNegotiator {
    /* 0x00 */ s32 negotiateSock;
    /* 0x04 */ s32 gameSock;
    /* 0x08 */ u32 cookie;
    /* 0x0c */ s32 clientindex;
    /* 0x10 */ s32 state;
    /* 0x14 */ s32 initAckRecv[3];
    /* 0x20 */ s32 retryCount;
    /* 0x24 */ s32 maxRetryCount;
    /* 0x28 */ u32 retryTime;
    /* 0x2c */ u32 guessedIP;
    /* 0x30 */ u16 guessedPort;
    /* 0x32 */ u8 gotRemoteData;
    /* 0x33 */ u8 sendGotRemoteData;
    /* 0x34 */ NegotiateProgressFunc progressCallback;
    /* 0x38 */ NegotiateCompletedFunc completedCallback;
    /* 0x3c */ void *userdata;
};

struct GsNatNegPacket {
    /* 0x00 */ u8 magic[6];
    /* 0x06 */ u8 version;
    /* 0x07 */ u8 type;
    /* 0x08 */ u32 cookie;
    /* 0x0c */ u8 peerIp;
    /* 0x0d */ u8 clientIndex;
    /* 0x0e */ u8 unk_0e;
    /* 0x0f */ u8 unk_0f;
    /* 0x10 */ u8 peerPort;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 gotPeerPing;
    /* 0x13 */ u8 finished;
    /* 0x14 */ u8 unk_14;
};

struct GsNatNegInitPacket {
    /* 0x00 */ u8 magic[6];
    /* 0x06 */ u8 version;
    /* 0x07 */ u8 type;
    /* 0x08 */ u32 cookie;
    /* 0x0c */ u8 portType;
    /* 0x0d */ u8 clientIndex;
    /* 0x0e */ u8 useGamePort;
    /* 0x0f */ u8 localIp0;
    /* 0x10 */ u8 localIp1;
    /* 0x11 */ u8 localIp2;
    /* 0x12 */ u8 localIp3;
    /* 0x13 */ u8 localPortHi;
    /* 0x14 */ u8 localPortLo;
    /* 0x15 */ char name[0x43];
};

struct GsNatNegConnectPktBuf {
    /* 0x00 */ u8 b[0x14];
};

struct GsNatNegReplyPktBuf {
    /* 0x00 */ u8 b[0x15];
};

#endif
