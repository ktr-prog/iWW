#ifndef UI_WFCLINKICON_H
#define UI_WFCLINKICON_H

#include "types.h"
#include "nitro/gxoam.h"

struct WfcLinkIcon {
    /* 0x0 */ GXOamAttr *oam;
    /* 0x4 */ void *task;
    /* 0x8 */ s8 iconSet;
};

#endif
