#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"
#include "menu/StaffRoll.h"


#include "sys/Heap.h"
#include "sys/new.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/ov004/unk_ov004_0223f2c8.h"

extern "C" {

void KkShowFx_Start(void) {
    OverlayMgr_Acquire(93 /* the staff roll's overlay */);
    sKkShowFx = (StaffRoll *)Heap_Alloc(gMenuHeap, sizeof(StaffRoll));
    if (sKkShowFx) {
        new (sKkShowFx) StaffRoll;
    }
    sKkShowFx->init();
    sKkShowFxActive = 1;
}

void KkShowFx_Update(void) {
    if (sKkShowFxActive & 1) {
        sKkShowFx->update();
    }
}

void KkShowFx_CallUnk1f70(void) {
    if (sKkShowFxActive & 1) {
        sKkShowFx->uploadScreens();
    }
}

void KkShowFx_Stop() {
    if (sKkShowFxActive & 1) {
        sKkShowFx->stop();
        Heap *heap = gMenuHeap;
        sKkShowFx->~StaffRoll();
        Heap_Free(heap, sKkShowFx);
        sKkShowFx = 0;
        OverlayMgr_Release(93 /* the staff roll's overlay */);
    }
    sKkShowFxActive = 0;
}

void KkShowFx_SetParam(s32 a) {
    if (sKkShowFxActive & 1) {
        if (a <= 0) a = 0x1400;
        sKkShowFx->start(a);
    }
}

void KkShowFx_CallUnk1de4() {
    if (sKkShowFxActive & 1) sKkShowFx->startLogo();
}

s32 KkShowFx_GetState() {
    if (sKkShowFxActive & 1) return sKkShowFx->isFinished();
    return 0;
}

}


u8 sKkShowFxActive;
StaffRoll *sKkShowFx;
SceneWarp sRoomSceneEntries[3] = {
    SceneWarp(1, VecFx32Copy(0xf000, 0x200, 0x1d000), 0x11000000, 0x4000, 2, 2, -0x4000, 2),
    SceneWarp(5, VecFx32Copy(0x11000, 0x200, 0x1d000), 0x11000000, -0x4000, 2, 2, 0x4000, 2),
    SceneWarp(0x3e, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};
SceneWarpList sRoomSceneEntryList = {sRoomSceneEntries, sizeof sRoomSceneEntries / sizeof sRoomSceneEntries[0]};
extern "C" u32 data_ov004_0224f2d0 = 3;
u32 sRoomCommonProfileCount = ROOM_COMMON_PROFILE_COUNT;
u32 sRoomCommonProfiles[17] = {0xc9, 0xca, 0xe, 0x7, 0x8c, 0x8e, 0xc6, 0x8b, 0xd6, 0xc5, 0x89, 0xd5, 0xbf, 0xd1, 0xd2, 0x8d, 0x2a};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0223f2c8) {
    HOST_OVERLAY_VAR(sKkShowFxActive),
    HOST_OVERLAY_VAR(sKkShowFx),
    HOST_OVERLAY_VAR(sRoomSceneEntries),
    HOST_OVERLAY_VAR(sRoomSceneEntryList),
    HOST_OVERLAY_VAR(data_ov004_0224f2d0),
    HOST_OVERLAY_VAR(sRoomCommonProfileCount),
    HOST_OVERLAY_VAR(sRoomCommonProfiles),
    HOST_OVERLAY_VARS_END
};
