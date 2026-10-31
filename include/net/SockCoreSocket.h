#ifndef NET_SOCKCORESOCKET_H
#define NET_SOCKCORESOCKET_H

#include "types.h"
#include "sys/OSThread.h"
#include "sys/OSMessageQueue.h"
#include "net/IpSocket.h"


struct SockThreadParams {
    /* 0x0 */ u16 stackSize;
    /* 0x2 */ u8 priority;
    /* 0x3 */ u8 msgQueueSize;
};

struct SockCreateParams {
    /* 0x00 */ s8 sockType;
    /* 0x01 */ s8 blocking;
    /* 0x02 */ u16 rxBufSize;
    /* 0x04 */ u16 rxConsumeLimit;
    /* 0x06 */ u16 txBufSize;
    /* 0x08 */ u16 rxAuxBufSize;
    /* 0x0a */ u16 pendingTxBufSize;
    /* 0x0c */ u16 sendRingSize;
    /* 0x0e */ u16 udpQueueCap;
    /* 0x10 */ SockThreadParams recvThread;
    /* 0x14 */ SockThreadParams sendThread;
};

struct SockBuffer {
    /* 0x0 */ s32 size;
    /* 0x4 */ u8 *buf;
};

struct SockUdpRecvNode {
    /* 0x0 */ SockUdpRecvNode *next;
    /* 0x4 */ u16 len;
    /* 0x6 */ u16 remotePort;
    /* 0x8 */ u32 remoteAddr;
    /* 0xc */ u8 data[4];
};

struct SockCoreSocket;

struct SockRecvPipe {
    /* 0x000 */ OSMessageQueue msgQueue;
    /* 0x020 */ OSThread thread;
    /* 0x0e0 */ OSMutex mutex;
    /* 0x0f8 */ s32 pos;
    /* 0x0fc */ u16 limit;
    /* 0x0fe */ s8 lock;
    /* 0x0ff */ u8 pad_ff;
    /* 0x100 */ SockUdpRecvNode *volatile tail;
    /* 0x104 */ SockUdpRecvNode *head;
    /* 0x108 */ u16 used;
    /* 0x10a */ u16 cap;
    /* 0x10c */ OSThreadQueue waitQueue;
};

struct SockSendPipe {
    /* 0x000 */ OSMessageQueue msgQueue;
    /* 0x020 */ OSThread thread;
    /* 0x0e0 */ OSMutex mutex;
    /* 0x0f8 */ SockBuffer ring;
    /* 0x100 */ u16 ringWrite;
    /* 0x102 */ u16 ringRead;
    /* 0x104 */ OSThreadQueue spaceWaitQueue;
    /* 0x10c */ SockCoreSocket *owner;
};

struct SockCoreSocket : IpSocket {
    /* 0x64 */ SockRecvPipe *recvPipe;
    /* 0x68 */ SockSendPipe *sendPipe;
    /* 0x6c */ s32 result;
    /* 0x70 */ volatile s16 flags;
    /* 0x72 */ s8 blocking;
    /* 0x73 */ s8 sockType;
    /* 0x74 */ u16 boundPort;
    /* 0x76 */ u16 peerPort;
    /* 0x78 */ u32 peerAddr;
    /* 0x7c */ SockCoreSocket *next;
};

extern "C" SockCoreSocket *sSockDefaultSocket;

#endif
