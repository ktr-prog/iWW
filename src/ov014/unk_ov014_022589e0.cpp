#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnList data_ov014_02258a4c;
extern SceneSpawnRecord data_ov014_02258a70[1];
extern u32 data_ov014_02258a40[1];
extern SceneSpawnRecord data_ov014_02258a5c[1];
extern SceneInfo data_ov014_02258a84;
extern SceneMapInfo data_ov014_02258a54;
extern SceneWarpList data_ov014_02258a44;
extern SceneSpawnGroup data_ov014_02258a9c[3];
extern SceneWarp data_ov014_02258acc[1];

SceneSpawnList data_ov014_02258a4c = {3, 0, data_ov014_02258a9c};

SceneSpawnRecord data_ov014_02258a70[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

u32 data_ov014_02258a40[1] = {0x101c};

SceneSpawnRecord data_ov014_02258a5c[1] = {
    {0x1000055, 0x1700000, 0, 0, 0xd00e},
};

SceneInfo data_ov014_02258a84 = {&data_ov014_02258a4c, 0, &data_ov014_02258a54, &data_ov014_02258a44, 0x34, -1};

SceneMapInfo data_ov014_02258a54 = {data_ov014_02258a40, 1, 1};

SceneWarpList data_ov014_02258a44 = {data_ov014_02258acc, 1};

SceneSpawnGroup data_ov014_02258a9c[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov014_02258a70},
    {0, 1, 0, data_ov014_02258a5c},
};

SceneWarp data_ov014_02258acc[1] = {
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 4),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov014_022589e0) {
    HOST_OVERLAY_VAR(data_ov014_02258a4c),
    HOST_OVERLAY_VAR(data_ov014_02258a70),
    HOST_OVERLAY_VAR(data_ov014_02258a40),
    HOST_OVERLAY_VAR(data_ov014_02258a5c),
    HOST_OVERLAY_VAR(data_ov014_02258a84),
    HOST_OVERLAY_VAR(data_ov014_02258a54),
    HOST_OVERLAY_VAR(data_ov014_02258a44),
    HOST_OVERLAY_VAR(data_ov014_02258a9c),
    HOST_OVERLAY_VAR(data_ov014_02258acc),
    HOST_OVERLAY_VARS_END
};
