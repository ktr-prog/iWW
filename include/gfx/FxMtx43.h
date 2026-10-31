#ifndef GFX_FXMTX43_H
#define GFX_FXMTX43_H

#include "types.h"

extern "C" void MTX_Identity43_(void *p);
class FxMtx43 {
public:
    FxMtx43() { MTX_Identity43_(this); }
    /* 0x00 */ u8 pad_00[0x30];
};

#endif
