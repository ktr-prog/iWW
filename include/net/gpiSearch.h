#ifndef NET_GPISEARCH_H
#define NET_GPISEARCH_H

#include "types.h"


struct GPISearchData {
    /* 0x000 */ s32 type;
    /* 0x004 */ s32 sock;
    /* 0x008 */ char *inputBuffer;
    /* 0x00c */ s32 inputBufferCapacity;
    /* 0x010 */ s32 inputBufferLength;
    /* 0x014 */ s32 inputBufferPos;
    /* 0x018 */ char *outputBuffer;
    /* 0x01c */ s32 outputBufferCapacity;
    /* 0x020 */ s32 outputBufferLength;
    /* 0x024 */ s32 outputBufferPos;
    /* 0x028 */ char nick[0x1f];
    /* 0x047 */ char uniquenick[0x15];
    /* 0x05c */ char email[0x33];
    /* 0x08f */ char firstname[0x1f];
    /* 0x0ae */ char lastname[0x1f];
    /* 0x0cd */ char password[0x1f];
    /* 0x0ec */ char cdkey[0x130 - 0xec];
    /* 0x130 */ s32 icquin;
    /* 0x134 */ s32 skip;
    /* 0x138 */ s32 productID;
    /* 0x13c */ s32 processing;
    /* 0x140 */ s32 remove;
};

#endif
