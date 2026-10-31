#include "types.h"
#include "town/BuildingActor.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov009/unk_ov009_0225b880_switch.h"

extern "C" {
}

void BuildingActor::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 6:
        BuildingOccupancy_Leave(itemId, 0);
        HouseVisitor_ClearPresent();
        Scene_ResetTownReturnPos(Scene_GetWarpRequest());
        exitDelay = 1;
        break;
    case 0:
    case 1:
        setEntryState(1);
        break;
    case 8:
        setEntryState(0);
        break;
    }
}
