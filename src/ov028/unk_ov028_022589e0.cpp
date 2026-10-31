#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnList data_ov028_02258a78;
extern SceneSpawnRecord data_ov028_02258a94[1];
extern u32 data_ov028_02258a64[1];
extern SceneSpawnGroup data_ov028_02258ac0[4];
extern SceneMapInfo data_ov028_02258a68;
extern SceneSpawnRecord data_ov028_02258a80[1];
extern u32 data_ov028_02258a60[1];
extern SceneWarpList data_ov028_02258a70;
extern SceneWarp data_ov028_02258aec[1];
extern SceneInfo data_ov028_02258aa8;

SceneSpawnList data_ov028_02258a78 = {4, 0, data_ov028_02258ac0};

SceneSpawnRecord data_ov028_02258a94[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

u32 data_ov028_02258a64[1] = {0x53};

SceneSpawnGroup data_ov028_02258ac0[4] = {
    {2, 1, 0, data_ov028_02258a64},
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov028_02258a94},
    {0, 1, 0, data_ov028_02258a80},
};

SceneMapInfo data_ov028_02258a68 = {data_ov028_02258a60, 1, 1};

SceneSpawnRecord data_ov028_02258a80[1] = {
    {0x14, 0, 0, 0, 0},
};

u32 data_ov028_02258a60[1] = {0x1024};

SceneWarpList data_ov028_02258a70 = {data_ov028_02258aec, 1};

SceneWarp data_ov028_02258aec[1] = {
    SceneWarp(0x20, VecFx32Copy(0x9000, 0, 0x14000), 0x23800000, 0x4000, 2, 2, 0x4000, 3),
};

SceneInfo data_ov028_02258aa8 = {&data_ov028_02258a78, 0, &data_ov028_02258a68, &data_ov028_02258a70, -1, -1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov028_022589e0) {
    HOST_OVERLAY_VAR(data_ov028_02258a78),
    HOST_OVERLAY_VAR(data_ov028_02258a94),
    HOST_OVERLAY_VAR(data_ov028_02258a64),
    HOST_OVERLAY_VAR(data_ov028_02258ac0),
    HOST_OVERLAY_VAR(data_ov028_02258a68),
    HOST_OVERLAY_VAR(data_ov028_02258a80),
    HOST_OVERLAY_VAR(data_ov028_02258a60),
    HOST_OVERLAY_VAR(data_ov028_02258a70),
    HOST_OVERLAY_VAR(data_ov028_02258aec),
    HOST_OVERLAY_VAR(data_ov028_02258aa8),
    HOST_OVERLAY_VARS_END
};
