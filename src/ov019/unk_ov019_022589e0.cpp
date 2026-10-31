#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnList data_ov019_02258a6c;
extern SceneSpawnRecord data_ov019_02258a90[1];
extern u32 data_ov019_02258a60[1];
extern SceneSpawnRecord data_ov019_02258a7c[1];
extern SceneInfo data_ov019_02258aa4;
extern SceneMapInfo data_ov019_02258a74;
extern SceneWarpList data_ov019_02258a64;
extern SceneSpawnGroup data_ov019_02258abc[3];
extern SceneWarp data_ov019_02258aec[1];

SceneSpawnList data_ov019_02258a6c = {3, 0, data_ov019_02258abc};

SceneSpawnRecord data_ov019_02258a90[1] = {
    {0xe0006d, 0x15c0000, 0, 0, 0xd018},
};

u32 data_ov019_02258a60[1] = {0x1026};

SceneSpawnRecord data_ov019_02258a7c[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov019_02258aa4 = {&data_ov019_02258a6c, 0, &data_ov019_02258a74, &data_ov019_02258a64, 0x2e, -1};

SceneMapInfo data_ov019_02258a74 = {data_ov019_02258a60, 1, 1};

SceneWarpList data_ov019_02258a64 = {data_ov019_02258aec, 1};

SceneSpawnGroup data_ov019_02258abc[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov019_02258a7c},
    {0, 1, 0, data_ov019_02258a90},
};

SceneWarp data_ov019_02258aec[1] = {
    SceneWarp(0x20, VecFx32Copy(0xa000, 0, 0x11000), 0x11000000, 0, 2, 2, 0, 3),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov019_022589e0) {
    HOST_OVERLAY_VAR(data_ov019_02258a6c),
    HOST_OVERLAY_VAR(data_ov019_02258a90),
    HOST_OVERLAY_VAR(data_ov019_02258a60),
    HOST_OVERLAY_VAR(data_ov019_02258a7c),
    HOST_OVERLAY_VAR(data_ov019_02258aa4),
    HOST_OVERLAY_VAR(data_ov019_02258a74),
    HOST_OVERLAY_VAR(data_ov019_02258a64),
    HOST_OVERLAY_VAR(data_ov019_02258abc),
    HOST_OVERLAY_VAR(data_ov019_02258aec),
    HOST_OVERLAY_VARS_END
};
