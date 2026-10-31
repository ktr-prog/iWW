#ifndef ROOM_FTRNOOKWAY_H
#define ROOM_FTRNOOKWAY_H

#include "types.h"
#include "room/FtrActor.h"

class FtrNookway : public FtrActor {
public:
    FtrNookway();
    virtual BOOL onDelete();
    virtual ~FtrNookway();
    virtual BOOL initModel();
    virtual BOOL updateActive();

    /* 0x840 */ u32 startFrame;
};

#endif
