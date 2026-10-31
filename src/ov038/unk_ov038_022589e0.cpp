#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern u32 data_ov038_02258a40[1];
extern SceneMapInfo data_ov038_02258a44;
extern SceneSpawnList data_ov038_02258a4c;
extern SceneSpawnGroup data_ov038_02258a70[3];
extern SceneWarp data_ov038_02258aec[1];
extern SceneSpawnRecord data_ov038_02258aa0[2];
extern SceneSpawnRecord data_ov038_02258a5c[1];
extern SceneInfo data_ov038_02258a88;
extern SceneWarpList data_ov038_02258a54;

u32 data_ov038_02258a40[1] = {0x1015};

SceneMapInfo data_ov038_02258a44 = {data_ov038_02258a40, 1, 1};

SceneSpawnList data_ov038_02258a4c = {3, 0, data_ov038_02258a70};

SceneSpawnGroup data_ov038_02258a70[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov038_02258a5c},
    {0, 2, 0, data_ov038_02258aa0},
};

SceneWarp data_ov038_02258aec[1] = {
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0, 0, 2, 2, 0, 4),
};

SceneSpawnRecord data_ov038_02258aa0[2] = {
    {0xf00076, 0x1a00000, 0, 0, 0xd019},
    {0xb0002c, 0x1b00000, 0x40000000, 0, 0},
};

SceneSpawnRecord data_ov038_02258a5c[1] = {
    {0x1000009, 0x1c00002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov038_02258a88 = {&data_ov038_02258a4c, 0, &data_ov038_02258a44, &data_ov038_02258a54, 0x32, -1};

SceneWarpList data_ov038_02258a54 = {data_ov038_02258aec, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov038_022589e0) {
    HOST_OVERLAY_VAR(data_ov038_02258a40),
    HOST_OVERLAY_VAR(data_ov038_02258a44),
    HOST_OVERLAY_VAR(data_ov038_02258a4c),
    HOST_OVERLAY_VAR(data_ov038_02258a70),
    HOST_OVERLAY_VAR(data_ov038_02258aec),
    HOST_OVERLAY_VAR(data_ov038_02258aa0),
    HOST_OVERLAY_VAR(data_ov038_02258a5c),
    HOST_OVERLAY_VAR(data_ov038_02258a88),
    HOST_OVERLAY_VAR(data_ov038_02258a54),
    HOST_OVERLAY_VARS_END
};
