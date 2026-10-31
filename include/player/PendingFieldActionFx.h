#ifndef PLAYER_PENDINGFIELDACTIONFX_H
#define PLAYER_PENDINGFIELDACTIONFX_H

#include "types.h"


struct PendingFieldActionFx {
    /* 0x0 */ u8 type : 5;
    /* 0x0 */ u8 sub : 2;
    /* 0x0 */ u8 set : 1;
};

#endif
