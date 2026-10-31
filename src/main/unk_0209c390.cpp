#include "types.h"
#include "game/NibblePair.h"
#include "room/Unk_0209c41c_Actor.h"
#include "proto/autoload_2/unk_020e8208.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_0209c3e0.h"


extern "C" {

}


u8 gSoftResetRequested;
u8 sSoftResetHeld;

extern "C" BOOL RoomObjSync_OnRecv(NibblePair *p) {
    return RoomObjSync_SetState(p->lo, p->hi);
}

extern "C" void SoftReset_Update() {
    if (gSoftResetRequested == 0) {
        if (sSoftResetHeld != 0) {
            if (data_021f47d0 == 0) sSoftResetHeld = 0;
        } else if (data_021f47d0 != 0) {
            gSoftResetRequested = 1;
            sSoftResetHeld = 1;
        }
    }
}
