#ifndef NET_UNK_OV001_02221734_D_H
#define NET_UNK_OV001_02221734_D_H

#include "types.h"

struct WfcMoveMbStateCopy {
    /* 0x0 */ u16 v[7];
};

struct Unk_ov001_02221734_D {
    /* 0x00 */ u8 lo : 4;
    /* 0x00 */ u8 hi : 4;
    /* 0x01 */ u8 b1;
    /* 0x02 */ u8 data[0x14];
    /* 0x16 */ WfcMoveMbStateCopy z;
};

#endif
