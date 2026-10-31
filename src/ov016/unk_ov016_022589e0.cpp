#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov016_02258ab4;
extern SceneMapInfo data_ov016_02258a88;
extern SceneSpawnRecord data_ov016_02258aa0[1];
extern SceneSpawnList data_ov016_02258a90;
extern SceneWarpList data_ov016_02258a98;
extern SceneSpawnRecord data_ov016_02258aec[5];
extern u32 data_ov016_02258a80[1];
extern SceneSpawnGroup data_ov016_02258acc[4];
extern u32 data_ov016_02258a84[1];
extern SceneWarp data_ov016_02258b78[2];

SceneInfo data_ov016_02258ab4 = {&data_ov016_02258a90, 0, &data_ov016_02258a88, &data_ov016_02258a98, 0x30, -1};

SceneMapInfo data_ov016_02258a88 = {data_ov016_02258a84, 1, 1};

SceneSpawnRecord data_ov016_02258aa0[1] = {
    {0x1000009, 0x500002, 0, 0, 0x800000},
};

SceneSpawnList data_ov016_02258a90 = {4, 0, data_ov016_02258acc};

SceneWarpList data_ov016_02258a98 = {data_ov016_02258b78, 2};

SceneSpawnRecord data_ov016_02258aec[5] = {
    {0x11, 0, 0, 0, 0},
    {0x1400072, 0x1100000, 0, 0, 0xd000},
    {0xc00073, 0x1100000, 0, 0, 0xd001},
    {0xe0007e, 0x400000, 0, 0, 0xd022},
    {0xf0007f, 0x1680000, 0x80000000, 0, 0xd023},
};

u32 data_ov016_02258a80[1] = {0xc7};

SceneSpawnGroup data_ov016_02258acc[4] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 1, 0, data_ov016_02258a80},
    {1, 1, 0, data_ov016_02258aa0},
    {0, 5, 0, data_ov016_02258aec},
};

u32 data_ov016_02258a84[1] = {0x101a};

SceneWarp data_ov016_02258b78[2] = {
    SceneWarp(0x3d, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 4),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov016_022589e0) {
    HOST_OVERLAY_VAR(data_ov016_02258ab4),
    HOST_OVERLAY_VAR(data_ov016_02258a88),
    HOST_OVERLAY_VAR(data_ov016_02258aa0),
    HOST_OVERLAY_VAR(data_ov016_02258a90),
    HOST_OVERLAY_VAR(data_ov016_02258a98),
    HOST_OVERLAY_VAR(data_ov016_02258aec),
    HOST_OVERLAY_VAR(data_ov016_02258a80),
    HOST_OVERLAY_VAR(data_ov016_02258acc),
    HOST_OVERLAY_VAR(data_ov016_02258a84),
    HOST_OVERLAY_VAR(data_ov016_02258b78),
    HOST_OVERLAY_VARS_END
};
