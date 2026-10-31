#ifndef TOWN_COUNTDOWNSIGN_H
#define TOWN_COUNTDOWNSIGN_H

#include "types.h"
#include "town/BuildingActor.h"
#include "gfx/ModelAnim.h"

class CountdownDigit;

class CountdownSign : public BuildingActor {
public:
    CountdownSign();
    virtual ~CountdownSign();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL postDraw(s32 a);
    virtual s32 setDoorState(s32 a);
    virtual BOOL initBuilding();
    virtual void updateDoorState();
    virtual char *getArcPath();
    virtual char *getTexPath();
    virtual char *getLightTexPath();

    void execNewYear();
    BOOL enterNewYear();
    void execCountdown();
    BOOL enterCountdown();

    /* 0x2b0 */ ModelAnim matAnim;
    /* 0x2d0 */ s8 alphaMatIdx;
    /* 0x2d1 */ u8 matAlpha;
    /* 0x2d2 */ u8 pad_2d2[2];
    /* 0x2d4 */ CountdownDigit *digits[6];
};

#endif
