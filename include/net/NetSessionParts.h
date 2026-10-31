#ifndef NET_NETSESSIONPARTS_H
#define NET_NETSESSIONPARTS_H

#include "types.h"


struct NetSlotStatus {
    /* 0x00 */ u8 sceneId;
    /* 0x01 */ u8 isOwner;
    /* 0x02 */ u8 isMoving;
    NetSlotStatus();
    ~NetSlotStatus();
    void reset();
    void get(u8 *a, u8 *b, u8 *c);
    void set(u8 a, u8 b, u8 c);
};

struct NetMoveRequest {
    /* 0x00 */ u32 slot;
    /* 0x04 */ u8 targetScene;
    NetMoveRequest();
    ~NetMoveRequest();
    void reset();
    void get(s32 *a, u8 *b);
    void set(u32 a, u8 b);
};

struct NetMoveReady {
    /* 0x00 */ u32 readyFlag;
    NetMoveReady();
    ~NetMoveReady();
    void reset();
    void get(u32 *out);
    void set(u32 v);
};

struct NetPendingStatus {
    /* 0x00 */ u8 sceneId;
    /* 0x01 */ u8 isOwner;
    /* 0x02 */ u8 isMoving;
    /* 0x04 */ u32 dirtyMask;
    NetPendingStatus();
    ~NetPendingStatus();
    void reset();
    void get(u8 *a, u8 *b, u8 *c, u32 *d);
    void setMasked(u8 a, u8 b, u8 c, u32 mask);
};

#endif
