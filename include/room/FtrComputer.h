#ifndef ROOM_FTRCOMPUTER_H
#define ROOM_FTRCOMPUTER_H

#include "types.h"
#include "room/FtrActor.h"
#include "room/FtrGlowMatSet.h"

class FtrComputer : public FtrActor {
public:
    FtrComputer();
    virtual ~FtrComputer();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ FtrGlowMatSet glowMats;
    /* 0x898 */ u8 ftrAct;
};

#endif
