#ifndef NET_HEXTABLE_H
#define NET_HEXTABLE_H

#include "types.h"

struct HexTable {
    /* 0x00 */ u8 c[17];
};

struct HexPair {
    /* 0x0 */ u8 hi;
    /* 0x1 */ u8 lo;
};

#endif
