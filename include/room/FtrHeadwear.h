#ifndef ROOM_FTRHEADWEAR_H
#define ROOM_FTRHEADWEAR_H

#include "types.h"
#include "room/FtrActor.h"

class FtrHeadwear : public FtrActor {
public:
    FtrHeadwear();
    virtual ~FtrHeadwear();
    virtual BOOL onDelete();
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();
    virtual BOOL isVisible();

    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();
    s32 syncAct1();
    s32 syncAct0();

    /* 0x840 */ u8 ftrAct;
    /* 0x841 */ u8 alwaysVisible;
};

#endif
