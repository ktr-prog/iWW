#ifndef GAME_ROOSTGUESTROLL_H
#define GAME_ROOSTGUESTROLL_H

#include "types.h"

class RoostGuestRoll {
public:
    BOOL hasLateGuest();
    u32 getAfternoonGuest();
    u32 getNoonGuest();
    BOOL hasMorningGuest();
    void roll();
    void clear();
    u8 morningGuest : 1;
    u8 noonGuest : 3;
    u8 afternoonGuest : 3;
    u8 lateGuest : 1;
};

#endif
