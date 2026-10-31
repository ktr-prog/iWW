#ifndef TOWN_TOWNSESSIONSTATE_H
#define TOWN_TOWNSESSIONSTATE_H

#include "types.h"
#include "town/KatieVisitState.h"
#include "town/ShopClosingTime.h"
#include "town/TownTravelState.h"
#include "town/PeteFallState.h"
#include "town/ResettiVisitFlag.h"
#include "town/VisitorSpawnFlags.h"

class TownSessionState {
public:
    TownSessionState();
    ~TownSessionState();

    /* 0x00 */ u32 flags;
    /* 0x04 */ u8 visitorPos[8];
    /* 0x0c */ KatieVisitState katie;
    /* 0x18 */ ShopClosingTime closingTime;
    /* 0x20 */ TownTravelState travel;
    /* 0x24 */ PeteFallState peteFall;
    /* 0x30 */ ResettiVisitFlag resetti;
    /* 0x31 */ VisitorSpawnFlags visitorFlags;
};

static_assert(sizeof(TownSessionState) == 0x34, "TownSessionState");

#endif
