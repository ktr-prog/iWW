#ifndef TOWN_COUNTDOWNDIGIT_H
#define TOWN_COUNTDOWNDIGIT_H

#include "types.h"
#include "town/BuildingActor.h"
#include "gfx/ModelAnim.h"

class CountdownDigit : public BuildingActor {
public:
    virtual BOOL needsMatrixUpdate();
    CountdownDigit();
    virtual ~CountdownDigit();
    virtual BOOL onExecute();
    virtual BOOL initBuilding();
    static void *operator new(size_t size);
    static void operator delete(void *p);

    /* 0x2b0 */ u8 digitIndex;
    /* 0x2b1 */ u8 digit;
    /* 0x2b2 */ u8 prevDigit;
    /* 0x2b3 */ u8 pad_2b3;
    /* 0x2b4 */ ModelAnim matAnim;
    /* 0x2d4 */ u8 isCounting;
    /* 0x2d5 */ u8 skipSe;
    /* 0x2d6 */ u8 pad_2d6[2];
};

#endif
