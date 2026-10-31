#ifndef NET_GPIPROFILE_H
#define NET_GPIPROFILE_H

#include "types.h"


struct GPIInfoCache;

struct GPIBuddyStatus {
    /* 0x00 */ s32 buddyIndex;
    /* 0x04 */ s32 status;
    /* 0x08 */ char *statusString;
    /* 0x0c */ char *locationString;
    /* 0x10 */ s32 ip;
    /* 0x14 */ s32 port;
};

struct GPIProfile {
    /* 0x00 */ s32 profileId;
    /* 0x04 */ s32 userId;
    /* 0x08 */ GPIBuddyStatus *buddyStatus;
    /* 0x0c */ GPIInfoCache *cache;
    /* 0x10 */ char *authSig;
    /* 0x14 */ s32 requestCount;
    /* 0x18 */ char *peerSig;
};

struct GPIFindProfileData {
    /* 0x0 */ s32 index;
    /* 0x4 */ GPIProfile *profile;
};

#endif
