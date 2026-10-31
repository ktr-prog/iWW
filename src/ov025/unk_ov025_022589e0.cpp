#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnRecord data_ov025_02258a80[1];
extern SceneInfo data_ov025_02258a94;
extern SceneSpawnGroup data_ov025_02258aac[3];
extern u32 data_ov025_02258a64[1];
extern u32 data_ov025_02258a60[1];
extern SceneWarp data_ov025_02258aec[1];
extern SceneSpawnList data_ov025_02258a68;
extern SceneWarpList data_ov025_02258a78;
extern SceneMapInfo data_ov025_02258a70;

SceneSpawnRecord data_ov025_02258a80[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov025_02258a94 = {&data_ov025_02258a68, 0, &data_ov025_02258a70, &data_ov025_02258a78, -1, -1};

SceneSpawnGroup data_ov025_02258aac[3] = {
    {2, 1, 0, data_ov025_02258a64},
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov025_02258a80},
};

u32 data_ov025_02258a64[1] = {0x52};

u32 data_ov025_02258a60[1] = {0x1023};

SceneWarp data_ov025_02258aec[1] = {
    SceneWarp(0x25, VecFx32Copy(0x12000, 0, 0x3000), 0x23800000, 0, 2, 2, 0, 3),
};

SceneSpawnList data_ov025_02258a68 = {3, 0, data_ov025_02258aac};

SceneWarpList data_ov025_02258a78 = {data_ov025_02258aec, 1};

SceneMapInfo data_ov025_02258a70 = {data_ov025_02258a60, 1, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov025_022589e0) {
    HOST_OVERLAY_VAR(data_ov025_02258a80),
    HOST_OVERLAY_VAR(data_ov025_02258a94),
    HOST_OVERLAY_VAR(data_ov025_02258aac),
    HOST_OVERLAY_VAR(data_ov025_02258a64),
    HOST_OVERLAY_VAR(data_ov025_02258a60),
    HOST_OVERLAY_VAR(data_ov025_02258aec),
    HOST_OVERLAY_VAR(data_ov025_02258a68),
    HOST_OVERLAY_VAR(data_ov025_02258a78),
    HOST_OVERLAY_VAR(data_ov025_02258a70),
    HOST_OVERLAY_VARS_END
};
