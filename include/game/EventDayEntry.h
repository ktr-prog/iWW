#ifndef GAME_EVENTDAYENTRY_H
#define GAME_EVENTDAYENTRY_H

#include "types.h"


struct EventDayEntry {
    /* 0x00 */ u16 eventId;
    /* 0x02 */ u16 kind;
    /* 0x04 */ u32 start;
    /* 0x08 */ u32 end;
};

#endif
