#ifndef ROOM_PHONECHOICESET_H
#define ROOM_PHONECHOICESET_H

#include "types.h"

struct PhoneChoiceSet {
    /* 0x0 */ const u8 *choiceMsgs;
    /* 0x4 */ u8 numChoices;
};

#endif
