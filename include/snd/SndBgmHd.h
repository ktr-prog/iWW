#ifndef SND_SNDBGMHD_H
#define SND_SNDBGMHD_H

#include "types.h"

struct Hd {
    /* 0x00 */ u8 pad[0x38];
    /* 0x38 */ u16 id;
};

#endif
