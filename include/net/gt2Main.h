#ifndef NET_GT2MAIN_H
#define NET_GT2MAIN_H

#include "types.h"
#include "net/darray.h"
#include "net/hashtable.h"


struct GTI2Socket;
struct GTI2Connection;
struct DArrayImplementation;
struct HashImplementation;

struct GTI2Buffer {
    /* 0x00 */ u8 *buffer;
    /* 0x04 */ s32 size;
    /* 0x08 */ s32 len;
};

struct GTI2OutgoingBufferMessage {
    /* 0x00 */ s32 start;
    /* 0x04 */ s32 len;
    /* 0x08 */ u16 serialNumber;
    /* 0x0a */ u16 pad_0a;
    /* 0x0c */ s32 lastSend;
};

struct GTI2IncomingBufferMessage {
    /* 0x00 */ s32 start;
    /* 0x04 */ s32 len;
    /* 0x08 */ s32 type;
    /* 0x0c */ u16 serialNumber;
    /* 0x0e */ u16 pad_0e;
};

typedef s32 (*gt2ConnectAttemptCallback)(GTI2Socket *, GTI2Connection *, s32, s32, s32, u8 *, s32);
typedef s32 (*gt2SocketErrorCallback)(GTI2Socket *);
typedef s32 (*gt2DumpCallback)(GTI2Socket *, GTI2Connection *, s32, s32, s32, u8 *, s32);
typedef s32 (*gt2UnrecognizedMessageCallback)(GTI2Socket *, s32, s32, u8 *, s32);

typedef s32 (*gt2ConnectedCallback)(GTI2Connection *, s32, u8 *, s32);
typedef s32 (*gt2ReceivedCallback)(GTI2Connection *, u8 *, s32, s32);
typedef s32 (*gt2ClosedCallback)(GTI2Connection *, s32);
typedef s32 (*gt2PingCallback)(GTI2Connection *, s32);

struct GTI2Socket {
    /* 0x00 */ s32 socket;
    /* 0x04 */ u32 ip;
    /* 0x08 */ u16 port;
    /* 0x0a */ u8 pad_0a[2];
    /* 0x0c */ HashImplementation *connections;
    /* 0x10 */ DArrayImplementation *closedConnections;
    /* 0x14 */ s32 close;
    /* 0x18 */ s32 error;
    /* 0x1c */ s32 callbackLevel;
    /* 0x20 */ gt2ConnectAttemptCallback connectAttemptCallback;
    /* 0x24 */ gt2SocketErrorCallback socketErrorCallback;
    /* 0x28 */ gt2DumpCallback sendDumpCallback;
    /* 0x2c */ gt2DumpCallback receiveDumpCallback;
    /* 0x30 */ gt2UnrecognizedMessageCallback unrecognizedMessageCallback;
    /* 0x34 */ u8 pad_34[4];
    /* 0x38 */ u32 outgoingBufferSize;
    /* 0x3c */ u32 incomingBufferSize;
    /* 0x40 */ u8 pad_40[4];
};

struct GsTransportConnCallbacks {
    /* 0x00 */ gt2ConnectedCallback connected;
    /* 0x04 */ gt2ReceivedCallback received;
    /* 0x08 */ gt2ClosedCallback closed;
    /* 0x0c */ gt2PingCallback ping;
};

typedef s32 (*GsTransportFilterCallback)(GTI2Connection *, s32, u8 *, u32, u32);

struct GsTransportChallengeBuf {
    /* 0x00 */ u8 bytes[0x24];
};

struct GTI2Connection {
    /* 0x00 */ u32 ip;
    /* 0x04 */ u16 port;
    /* 0x06 */ u8 pad_06[2];
    /* 0x08 */ GTI2Socket *socket;
    /* 0x0c */ s32 state;
    /* 0x10 */ s32 initiated;
    /* 0x14 */ s32 freeAtAcceptReject;
    /* 0x18 */ s32 connectionResult;
    /* 0x1c */ u32 startTime;
    /* 0x20 */ u32 timeout;
    /* 0x24 */ s32 callbackLevel;
    /* 0x28 */ gt2ConnectedCallback connectedCallback;
    /* 0x2c */ gt2ReceivedCallback receivedCallback;
    /* 0x30 */ gt2ClosedCallback closedCallback;
    /* 0x34 */ gt2PingCallback pingCallback;
    /* 0x38 */ u8 *initialMessage;
    /* 0x3c */ s32 initialMessageLen;
    /* 0x40 */ void *data;
    /* 0x44 */ GTI2Buffer incomingBuffer;
    /* 0x50 */ GTI2Buffer outgoingBuffer;
    /* 0x5c */ DArrayImplementation *incomingBufferMessages;
    /* 0x60 */ DArrayImplementation *outgoingBufferMessages;
    /* 0x64 */ u16 serialNumber;
    /* 0x66 */ u16 expectedSerialNumber;
    /* 0x68 */ u8 response[0x20];
    /* 0x88 */ u32 lastSend;
    /* 0x8c */ s32 challengeTime;
    /* 0x90 */ s32 pendingAck;
    /* 0x94 */ u32 pendingAckTime;
    /* 0x98 */ DArrayImplementation *sendFilters;
    /* 0x9c */ DArrayImplementation *receiveFilters;
};

#endif
