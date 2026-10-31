#ifndef NET_GHTTPCONNECTION_H
#define NET_GHTTPCONNECTION_H

#include "types.h"
#include "net/ghttpBuffer.h"


struct DArrayImplementation;
struct GHIConnection;
#ifndef __cplusplus
typedef struct DArrayImplementation DArrayImplementation;
typedef struct GHIPostData GHIPostData;
typedef struct GHIPost GHIPost;
typedef struct GHIPostState GHIPostState;
typedef struct GHIPostingState GHIPostingState;
#endif

typedef void (*ghttpPostCallback)(u32, u32, u32, u32, u32, void *);
typedef void (*ghttpProgressCallback)(u32, u32, char *, u32, u32, u32, void *);
typedef s32 (*ghttpCompletedCallback)(u32, u32, char *, u32, void *);
typedef s32 (*GsHttpEncryptStartFn)(GHIConnection *, void *);
typedef s32 (*GsHttpEncryptFn)(GHIConnection *, void *, const char *, s32 *, char *, s32 *);
typedef s32 (*GsHttpDecryptFn)(GHIConnection *, void *, u8 *, s32 *, u8 *, s32 *);
typedef void (*GsHttpEncryptCleanupFn)(GHIConnection *, void *);

struct GHIPostData {
    /* 0x00 */ s32 type;
    /* 0x04 */ char *name;
    union {
        struct {
            /* 0x08 */ char *string;
            /* 0x0c */ s32 len;
            /* 0x10 */ s32 invalidChars;
            /* 0x14 */ s32 extendedChars;
        } string;
        struct {
            /* 0x08 */ char *filename;
            /* 0x0c */ char *reportFilename;
            /* 0x10 */ char *contentType;
        } fileDisk;
        struct {
            /* 0x08 */ char *buffer;
            /* 0x0c */ s32 len;
            /* 0x10 */ char *reportFilename;
            /* 0x14 */ char *contentType;
        } fileMemory;
    } data;
};

struct GHIPost {
    /* 0x00 */ DArrayImplementation *data;
    /* 0x04 */ ghttpPostCallback callback;
    /* 0x08 */ void *param;
    /* 0x0c */ s32 hasFiles;
    /* 0x10 */ s32 autoFree;
};

struct GHIPostState {
    /* 0x0 */ GHIPostData *data;
    /* 0x4 */ s32 pos;
    /* 0x8 */ u32 file;
    /* 0xc */ s32 fileLength;
};

struct GHIPostingState {
    /* 0x00 */ DArrayImplementation *states;
    /* 0x04 */ s32 index;
    /* 0x08 */ s32 bytesPosted;
    /* 0x0c */ s32 totalBytes;
    /* 0x10 */ ghttpPostCallback callback;
    /* 0x14 */ void *param;
};

struct GHIConnection {
    /* 0x000 */ s32 inUse;
    /* 0x004 */ s32 request;
    /* 0x008 */ s32 uniqueID;
    /* 0x00c */ s32 type;
    /* 0x010 */ s32 state;
    /* 0x014 */ char *URL;
    /* 0x018 */ char *serverAddress;
    /* 0x01c */ s32 serverIP;
    /* 0x020 */ u16 serverPort;
    /* 0x024 */ char *requestPath;
    /* 0x028 */ char *sendHeaders;
    /* 0x02c */ s32 saveFile;
    /* 0x030 */ s32 blocking;
    /* 0x034 */ s32 persistConnection;
    /* 0x038 */ s32 result;
    /* 0x03c */ ghttpProgressCallback progressCallback;
    /* 0x040 */ ghttpCompletedCallback completedCallback;
    /* 0x044 */ void *callbackParam;
    /* 0x048 */ s32 socket;
    /* 0x04c */ s32 socketError;
    /* 0x050 */ GHIBuffer sendBuffer;
    /* 0x074 */ GHIBuffer recvBuffer;
    /* 0x098 */ GHIBuffer decodeBuffer;
    /* 0x0bc */ GHIBuffer getFileBuffer;
    /* 0x0e0 */ s32 userBufferSupplied;
    /* 0x0e4 */ s32 statusMajorVersion;
    /* 0x0e8 */ s32 statusMinorVersion;
    /* 0x0ec */ s32 statusCode;
    /* 0x0f0 */ s32 statusStringIndex;
    /* 0x0f4 */ s32 headerStringIndex;
    /* 0x0f8 */ s32 headersEnd;
    /* 0x0fc */ s32 completed;
    /* 0x100 */ s32 fileBytesReceived;
    /* 0x104 */ s32 totalSize;
    /* 0x108 */ char *redirectURL;
    /* 0x10c */ s32 redirectCount;
    /* 0x110 */ s32 chunkedTransfer;
    /* 0x114 */ char chunkHeader[12];
    /* 0x120 */ s32 chunkHeaderLen;
    /* 0x124 */ s32 chunkBytesLeft;
    /* 0x128 */ s32 chunkReadingState;
    /* 0x12c */ s32 processing;
    /* 0x130 */ s32 connectionClosed;
    /* 0x134 */ u32 throttle;
    /* 0x138 */ u32 lastThrottleRecv;
    /* 0x13c */ GHIPost *post;
    /* 0x140 */ GHIPostingState postingState;
    /* 0x158 */ u32 maxRecvTime;
    /* 0x15c */ char *proxyOverrideServer;
    /* 0x160 */ u16 proxyOverridePort;
    /* 0x164 */ u32 encryptor;
    /* 0x168 */ u32 encryptEnabled;
    /* 0x16c */ u32 encryptInitialized;
    /* 0x170 */ u32 encryptSessionReady;
    /* 0x174 */ GsHttpEncryptStartFn encryptStartFn;
    /* 0x178 */ GsHttpEncryptCleanupFn encryptCleanupFn;
    /* 0x17c */ GsHttpEncryptFn encryptFn;
    /* 0x180 */ GsHttpDecryptFn decryptFn;
};

#endif
