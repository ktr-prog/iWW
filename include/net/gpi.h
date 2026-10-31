#ifndef NET_GPI_H
#define NET_GPI_H

#include "types.h"
#include "net/gpiBuffer.h"
#include "net/gpiOperation.h"
#include "net/gpiPeer.h"
#include "net/gpiCallback.h"
#include "net/gp.h"
#include "net/hashtable.h"


struct GPIConnection {
    /* 0x000 */ char errorString[0x100];
    /* 0x100 */ s32 infoCaching;
    /* 0x104 */ s32 infoCachingBuddyOnly;
    /* 0x108 */ s32 simulation;
    /* 0x10c */ s32 firewall;
    /* 0x110 */ char nick[0x1f];
    /* 0x12f */ char uniquenick[0x15];
    /* 0x144 */ char email[0x33];
    /* 0x177 */ char password[0x1f];
    /* 0x196 */ u8 pad_196[0x2];
    /* 0x198 */ s32 sessKey;
    /* 0x19c */ s32 userid;
    /* 0x1a0 */ s32 profileid;
    /* 0x1a4 */ GPICallback callbacks[6];
    /* 0x1d4 */ s32 cmSocket;
    /* 0x1d8 */ s32 connectState;
    /* 0x1dc */ GPIBuffer socketBuffer;
    /* 0x1ec */ char *inputBuffer;
    /* 0x1f0 */ s32 inputBufferSize;
    /* 0x1f4 */ GPIBuffer outputBuffer;
    /* 0x204 */ s32 peerSocket;
    /* 0x208 */ s32 peerPort;
    /* 0x20c */ s32 nextOperationID;
    /* 0x210 */ s32 numSearches;
    /* 0x214 */ s32 lastStatus;
    /* 0x218 */ char lastStatusString[0x100];
    /* 0x318 */ char lastLocationString[0x100];
    /* 0x418 */ s32 errorCode;
    /* 0x41c */ s32 fatalError;
    /* 0x420 */ s32 diskCache;
    /* 0x424 */ GPIOperation *operationList;
    /* 0x428 */ HashImplementation *profileTable;
    /* 0x42c */ s32 numProfiles;
    /* 0x430 */ s32 numBuddies;
    /* 0x434 */ GPIPeer *peerList;
    /* 0x438 */ GPICallbackData *callbackList;
    /* 0x43c */ GPICallbackData *lastCallback;
    /* 0x440 */ GPIBuffer updateproBuffer;
    /* 0x450 */ GPIBuffer updateuiBuffer;
    /* 0x460 */ char *unk_460;
    /* 0x464 */ s32 unk_464;
    /* 0x468 */ s32 unk_468;
    /* 0x46c */ s32 productID;
    /* 0x470 */ s32 namespaceID;
    /* 0x474 */ char loginTicket[0x19];
    /* 0x48d */ u8 pad_48d[3];
};

#endif
