#ifndef PLAYER_FIELDACTIONFXEVENT_H
#define PLAYER_FIELDACTIONFXEVENT_H

#include "types.h"


struct FieldActionFxEvent {
    /* 0x0 */ u8 type;
    /* 0x1 */ u8 sub;
    /* 0x2 */ volatile u16 pos;
};

#endif
