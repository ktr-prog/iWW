#ifndef NET_NETSTATEBLOCKHEADER_H
#define NET_NETSTATEBLOCKHEADER_H

#include "types.h"


struct NetStateBlockHeader {
    /* 0x00 */ u16 total;
    /* 0x02 */ u16 len;
    /* 0x04 */ u8 id;
};

#endif
