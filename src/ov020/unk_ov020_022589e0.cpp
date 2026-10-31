#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern u32 data_ov020_02258a60[1];
extern SceneMapInfo data_ov020_02258a64;
extern SceneSpawnList data_ov020_02258a6c;
extern SceneSpawnGroup data_ov020_02258a90[3];
extern SceneWarp data_ov020_02258b0c[1];
extern SceneSpawnRecord data_ov020_02258ac0[2];
extern SceneSpawnRecord data_ov020_02258a7c[1];
extern SceneInfo data_ov020_02258aa8;
extern SceneWarpList data_ov020_02258a74;

u32 data_ov020_02258a60[1] = {0x1025};

SceneMapInfo data_ov020_02258a64 = {data_ov020_02258a60, 1, 1};

SceneSpawnList data_ov020_02258a6c = {3, 0, data_ov020_02258a90};

SceneSpawnGroup data_ov020_02258a90[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov020_02258a7c},
    {0, 2, 0, data_ov020_02258ac0},
};

SceneWarp data_ov020_02258b0c[1] = {
    SceneWarp(0x20, VecFx32Copy(0x9000, 0, 0x1a000), 0x10c00000, 0x4000, 2, 2, 0x4000, 3),
};

SceneSpawnRecord data_ov020_02258ac0[2] = {
    {0x64, 0, 0, 0, 0},
    {0x1970063, 0x1500000, 0xc0000000, 0, 0xd01f},
};

SceneSpawnRecord data_ov020_02258a7c[1] = {
    {0x1000009, 0x1800002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov020_02258aa8 = {&data_ov020_02258a6c, 0, &data_ov020_02258a64, &data_ov020_02258a74, -1, -1};

SceneWarpList data_ov020_02258a74 = {data_ov020_02258b0c, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov020_022589e0) {
    HOST_OVERLAY_VAR(data_ov020_02258a60),
    HOST_OVERLAY_VAR(data_ov020_02258a64),
    HOST_OVERLAY_VAR(data_ov020_02258a6c),
    HOST_OVERLAY_VAR(data_ov020_02258a90),
    HOST_OVERLAY_VAR(data_ov020_02258b0c),
    HOST_OVERLAY_VAR(data_ov020_02258ac0),
    HOST_OVERLAY_VAR(data_ov020_02258a7c),
    HOST_OVERLAY_VAR(data_ov020_02258aa8),
    HOST_OVERLAY_VAR(data_ov020_02258a74),
    HOST_OVERLAY_VARS_END
};
