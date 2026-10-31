#ifndef ITEM_PLAYERMAILBOX_H
#define ITEM_PLAYERMAILBOX_H

#include "types.h"
#include "item/Letter.h"

class PlayerMailbox {
public:
    PlayerMailbox();
    ~PlayerMailbox();
    Letter *getLetter(s32 i);
    void setLastWifiMailId(u32 v);
    u32 getLastWifiMailId();
    void clear();

    /* 0x000 */ Letter letters[10];
    /* 0x988 */ u16 lastWifiMailId;
    /* 0x98a */ u16 pad_98a;
};

static_assert(sizeof(PlayerMailbox) == 0x98c, "PlayerMailbox: SaveData::mailboxes[i]");

#endif
