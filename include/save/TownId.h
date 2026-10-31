#ifndef SAVE_TOWNID_H
#define SAVE_TOWNID_H

#include "types.h"

class TownId {
public:
    /* 0x00 */ u16 townId;
    /* 0x02 */ u8 townName[8];

    s32 getTownRelation();
    void setTown(TownId *o);
};

#endif
