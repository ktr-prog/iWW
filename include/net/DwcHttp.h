#ifndef NET_DWCHTTP_H
#define NET_DWCHTTP_H

#include "types.h"
#include "net/IpSocket.h"
#include "net/SslConnection.h"
#include "sys/OSThread.h"


typedef void *(*DwcAllocFunc)(const char *, u32);
typedef void (*DwcFreeFunc)(const char *, void *, u32);

typedef struct DwcHttpBuffer DwcHttpBuffer;
struct DwcHttpBuffer {
    /* 0x0 */ u8 *base;
    /* 0x4 */ u8 *cur;
    /* 0x8 */ u8 *limit;
    /* 0xc */ s32 capacity;
};

typedef struct DwcHttpParams DwcHttpParams;
struct DwcHttpParams {
    /* 0x00 */ char *url;
    /* 0x04 */ s32 method;
    /* 0x08 */ u8 *userRecvBuffer;
    /* 0x0c */ s32 rxBufSize;
    /* 0x10 */ DwcAllocFunc allocFunc;
    /* 0x14 */ DwcFreeFunc freeFunc;
    /* 0x18 */ s32 useTestServer;
    /* 0x1c */ s32 timeoutMs;
};

typedef struct DwcHttp DwcHttp;
struct DwcHttp {
    /* 0x000 */ u8 initFlag;
    /* 0x001 */ u8 unk_01[3];
    /* 0x004 */ char *url;
    /* 0x008 */ s32 method;
    /* 0x00c */ u8 *userRecvBuffer;
    /* 0x010 */ s32 rxBufSize;
    /* 0x014 */ DwcAllocFunc allocFunc;
    /* 0x018 */ DwcFreeFunc freeFunc;
    /* 0x01c */ s32 useTestServer;
    /* 0x020 */ s32 timeoutMs;
    /* 0x024 */ s32 result;
    /* 0x028 */ char urlBuffer[0xa8 - 0x28];
    /* 0x0a8 */ char *hostName;
    /* 0x0ac */ char *path;
    /* 0x0b0 */ s32 isHttps;
    /* 0x0b4 */ IpSocket ipSocket;
    /* 0x118 */ SslConnection sslCtx;
    /* 0x91c */ void *lowRecvBuf;
    /* 0x920 */ void *lowSendBuf;
    /* 0x924 */ s32 numFormParams;
    /* 0x928 */ DwcHttpBuffer requestBuffer;
    /* 0x938 */ DwcHttpBuffer responseBuffer;
    /* 0x948 */ OSMutex responseMutex;
    /* 0x960 */ s32 contentLength;
    /* 0x964 */ char *bodyStart;
    /* 0x968 */ OSThread thread;
    /* 0xa28 */ OSMutex abortMutex;
    /* 0xa40 */ s32 isAbortRequested;
    /* 0xa44 */ u8 unk_a44[0x1c];
    /* 0xa60 */ u8 stack[0x1000];
};

typedef struct DwcHttpField DwcHttpField;
struct DwcHttpField {
    /* 0x0 */ const char *key;
    /* 0x4 */ char *value;
};

typedef struct DwcHttpFieldList DwcHttpFieldList;
struct DwcHttpFieldList {
    /* 0x0 */ DwcHttpField *entries;
    /* 0x4 */ s32 capacity;
    /* 0x8 */ s32 count;
};

#endif
