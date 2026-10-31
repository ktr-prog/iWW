#ifndef ROOM_FTRVISNODES_H
#define ROOM_FTRVISNODES_H

#include "types.h"

class FtrVisNodes {
public:
    u8 isVisible();
    BOOL hasNode(s32 v);
    void setVisible(u32 v);
    void init(void *p, u32 v);

    /* 0x00 */ s8 nodeIds[4];
    /* 0x04 */ u8 visible;
};

#endif
