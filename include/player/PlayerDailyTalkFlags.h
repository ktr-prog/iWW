#ifndef PLAYER_PLAYERDAILYTALKFLAGS_H
#define PLAYER_PLAYERDAILYTALKFLAGS_H

#include "types.h"

class PlayerDailyTalkFlags {
public:
    void clear(u32 i);
    void set(u32 i);
    BOOL test(u32 i);
    void setDate(u8 *src);
    void clearAll();
    void stampToday();

    u8 date[3];
    u32 flags[2];
};

#endif
