#ifndef NPC_VILLAGERID_H
#define NPC_VILLAGERID_H

#include "types.h"

class MsgString;

class VillagerId {
public:
    BOOL getName(MsgString *buf);
    void makeFileName(void *buf, u32 size, const char *key);
    u32 getGender();
    void set(u32 id, u32 type, void *s);
    u32 isValid();

    /* 0x00 */ u16 townId;
    /* 0x02 */ u8 townName[8];
    /* 0x0a */ u8 personality;
    /* 0x0b */ u8 species;
};

#endif
