#ifndef NET_SB_INTERNAL_H
#define NET_SB_INTERNAL_H

#include "types.h"
#include "net/sb_crypt.h"
#include "net/SockAddrIn.h"
#include "net/darray.h"


struct _SBServer {
    /* 0x00 */ u32 publicip;
    /* 0x04 */ u16 publicport;
    /* 0x06 */ u16 pad_06;
    /* 0x08 */ u32 privateip;
    /* 0x0c */ u16 privateport;
    /* 0x0e */ u16 pad_0e;
    /* 0x10 */ s32 icmpip;
    /* 0x14 */ u8 state;
    /* 0x15 */ u8 flags;
    /* 0x16 */ u16 pad_16;
    /* 0x18 */ void *keyvals;
    /* 0x1c */ u32 updatetime;
    /* 0x20 */ _SBServer *next;
};

struct SBServerFIFO {
    /* 0x00 */ _SBServer *first;
    /* 0x04 */ _SBServer *last;
    /* 0x08 */ s32 count;
};

struct SBQueryEngine;
typedef void (*SBEngineCallbackFn)(SBQueryEngine *m, s32 code, void *arg, void *user);

struct SBQueryEngine {
    /* 0x00 */ s32 queryversion;
    /* 0x04 */ s32 maxupdates;
    /* 0x08 */ SBServerFIFO querylist;
    /* 0x14 */ SBServerFIFO pendinglist;
    /* 0x20 */ s32 querysock;
    /* 0x24 */ s32 icmpsock;
    /* 0x28 */ u32 mypublicip;
    /* 0x2c */ u8 serverkeys[0x14];
    /* 0x40 */ s32 numserverkeys;
    /* 0x44 */ SBEngineCallbackFn ListCallback;
    /* 0x48 */ void *instance;
};

struct GsSrvQueryBasicInfoStr {
    /* 0x00 */ u8 b[13];
};

struct GsSrvQueryStatusStr {
    /* 0x00 */ u8 b[8];
};

struct GsSrvSortStackPad {
    /* 0x00 */ s32 v[1];
    GsSrvSortStackPad() {}
    ~GsSrvSortStackPad() {}
};

struct SBKeyValuePair {
    /* 0x00 */ char *key;
    /* 0x04 */ char *value;
};

struct SBRefString {
    /* 0x00 */ char *str;
    /* 0x04 */ s32 refcount;
};

struct GsServerIgnoredKeys {
    /* 0x00 */ char *v[2];
};

struct KeyInfo {
    /* 0x00 */ char *keyName;
    /* 0x04 */ s32 keyType;
};

struct SBServerList;

typedef void (*SBListCallBackFn)(SBServerList *, s32, _SBServer *, void *);
typedef void (*SBMaploopCallbackFn)(SBServerList *, void *, u32, s32, void *, void *);
typedef void (*SBPlayerSearchCallbackFn)(SBServerList *, void *, u32, u32, u32, void *, void *);

struct SBServerList {
    /* 0x000 */ s32 state;
    /* 0x004 */ DArrayImplementation *servers;
    /* 0x008 */ DArrayImplementation *keylist;
    /* 0x00c */ char queryforgamename[0x24];
    /* 0x030 */ char queryfromgamename[0x24];
    /* 0x054 */ char queryfromkey[0x20];
    /* 0x074 */ char mychallenge[8];
    /* 0x07c */ u8 *inbuffer;
    /* 0x080 */ s32 inbufferlen;
    /* 0x084 */ char *popularvalues[0xff];
    /* 0x480 */ s32 numpopularvalues;
    /* 0x484 */ s32 expectedelements;
    /* 0x488 */ SBListCallBackFn ListCallback;
    /* 0x48c */ SBMaploopCallbackFn MaploopCallback;
    /* 0x490 */ SBPlayerSearchCallbackFn PlayerSearchCallback;
    /* 0x494 */ void *instance;
    /* 0x498 */ char *sortkey;
    /* 0x49c */ s32 sortascending;
    /* 0x4a0 */ s32 mypublicip;
    /* 0x4a4 */ u32 srcip;
    /* 0x4a8 */ u16 defaultport;
    /* 0x4aa */ u16 pad_4aa;
    /* 0x4ac */ const char *lasterror;
    /* 0x4b0 */ s32 slsocket;
    /* 0x4b4 */ u32 lanstarttime;
    /* 0x4b8 */ s32 fromgamever;
    /* 0x4bc */ GOACryptState cryptkey;
    /* 0x5c1 */ u8 pad_5c1[3];
    /* 0x5c4 */ u32 queryoptions;
    /* 0x5c8 */ s32 pstate;
    /* 0x5cc */ s32 unk_5cc;
    /* 0x5d0 */ _SBServer *deadlist;
};

struct _ServerBrowser;

typedef void (*ServerBrowserCallback)(_ServerBrowser *, s32, void *, void *);

struct _ServerBrowser {
    /* 0x000 */ SBQueryEngine engine;
    /* 0x04c */ SBServerList list;
    /* 0x620 */ s32 disconnectFlag;
    /* 0x624 */ s32 dontUpdate;
    /* 0x628 */ u32 triggerIP;
    /* 0x62c */ u16 triggerPort;
    /* 0x62e */ u8 pad_62e[2];
    /* 0x630 */ ServerBrowserCallback BrowserCallback;
    /* 0x634 */ void *instance;
};

#endif
