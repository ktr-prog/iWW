#ifndef NET_WFCOBJGROUP_H
#define NET_WFCOBJGROUP_H

#include "types.h"
#include "nitro/gxoam.h"

typedef struct WfcObjGroup WfcObjGroup;
struct WfcObjGroup {
    /* 0x0 */ WfcObjGroup *prev;
    /* 0x4 */ WfcObjGroup *next;
    /* 0x8 */ GXOamAttr *oams;
    /* 0xc */ u8 numOams;
};

#endif
