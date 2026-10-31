#ifndef ROOM_FTRKIND25_H
#define ROOM_FTRKIND25_H

#include "types.h"
#include "room/FtrActor.h"

class FtrKind25 : public FtrActor {
public:
    FtrKind25();
    virtual ~FtrKind25();
    virtual BOOL onDelete();
    virtual BOOL initModel();
    virtual BOOL updateActive();

    /* 0x840 */ u16 sampleIndex;
};

#endif
