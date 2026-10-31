#ifndef TOWN_KATRINATENT_H
#define TOWN_KATRINATENT_H

#include "types.h"
#include "town/BuildingActor.h"

class KatrinaTent : public BuildingActor {
public:
    KatrinaTent();
    virtual ~KatrinaTent();

    virtual void setupTalkMsg();
    virtual BOOL isOpen();
    virtual BOOL onExecute();
    virtual BOOL initBuilding();

    /* 0x2b0 */ u8 createHour;
    /* 0x2b1 */ u8 pad_2b1[3];
};

#endif
