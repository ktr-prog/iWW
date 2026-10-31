#ifndef TOWN_RESETTIVISITFLAG_H
#define TOWN_RESETTIVISITFLAG_H

#include "types.h"

class ResettiVisitFlag {
public:
    void set(u32 v);
    BOOL isSet();
    void clear();
    void destruct();
    void construct();

    u8 isPending;
};

#endif
