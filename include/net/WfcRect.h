#ifndef NET_WFCRECT_H
#define NET_WFCRECT_H

#include "types.h"

typedef struct WfcRect WfcRect;
typedef struct WfcPoint WfcPoint;
typedef struct WfcPosSize WfcPosSize;

struct WfcRect {
    /* 0x0 */ u16 left;
    /* 0x2 */ u16 top;
    /* 0x4 */ u16 right;
    /* 0x6 */ u16 bottom;
};

struct WfcPoint {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
};

struct WfcPosSize {
    /* 0x0 */ WfcPoint pos;
    /* 0x4 */ WfcPoint size;
};

#endif
