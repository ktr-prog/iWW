#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov023_02258ad8;
extern SceneSpawnGroup data_ov023_02258af0[3];
extern SceneSpawnRecord data_ov023_02258ac4[1];
extern SceneWarpList data_ov023_02258aac;
extern SceneWarp data_ov023_02258b38[2];
extern SceneMapInfo data_ov023_02258abc;
extern u32 data_ov023_02258aa4[2];
extern SceneSpawnList data_ov023_02258ab4;
extern u32 data_ov023_02258aa0[1];

SceneInfo data_ov023_02258ad8 = {&data_ov023_02258ab4, 0, &data_ov023_02258abc, &data_ov023_02258aac, -1, -1};

SceneSpawnGroup data_ov023_02258af0[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 2, 0, data_ov023_02258aa4},
    {1, 1, 0, data_ov023_02258ac4},
};

SceneSpawnRecord data_ov023_02258ac4[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneWarpList data_ov023_02258aac = {data_ov023_02258b38, 2};

SceneWarp data_ov023_02258b38[2] = {
    SceneWarp(0x23, VecFx32Copy(0x6000, 0, 0x3000), 0x23800000, 0, 2, 2, 0, 3),
    SceneWarp(0x23, VecFx32Copy(0x1c000, 0, 0x3000), 0x23800000, 0, 2, 2, 0, 3),
};

SceneMapInfo data_ov023_02258abc = {data_ov023_02258aa0, 1, 1};

u32 data_ov023_02258aa4[2] = {0x51, 0x100c3};

SceneSpawnList data_ov023_02258ab4 = {3, 0, data_ov023_02258af0};

u32 data_ov023_02258aa0[1] = {0x101f};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov023_022589e0) {
    HOST_OVERLAY_VAR(data_ov023_02258ad8),
    HOST_OVERLAY_VAR(data_ov023_02258af0),
    HOST_OVERLAY_VAR(data_ov023_02258ac4),
    HOST_OVERLAY_VAR(data_ov023_02258aac),
    HOST_OVERLAY_VAR(data_ov023_02258b38),
    HOST_OVERLAY_VAR(data_ov023_02258abc),
    HOST_OVERLAY_VAR(data_ov023_02258aa4),
    HOST_OVERLAY_VAR(data_ov023_02258ab4),
    HOST_OVERLAY_VAR(data_ov023_02258aa0),
    HOST_OVERLAY_VARS_END
};
