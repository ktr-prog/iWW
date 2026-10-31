#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnRecord data_ov042_02258b00[2];
extern SceneWarpList data_ov042_02258ab4;
extern u32 data_ov042_02258aa0[1];
extern SceneSpawnGroup data_ov042_02258ae8[3];
extern SceneInfo data_ov042_02258ad0;
extern SceneMapInfo data_ov042_02258aa4;
extern SceneSpawnRecord data_ov042_02258abc[1];
extern SceneWarp data_ov042_02258b58[2];
extern SceneSpawnList data_ov042_02258aac;

SceneSpawnRecord data_ov042_02258b00[2] = {
    {0xf00075, 0xc00000, 0x80000000, 0, 0xd010},
    {0x1100074, 0xc00000, 0x80000000, 0, 0xd00f},
};

SceneWarpList data_ov042_02258ab4 = {data_ov042_02258b58, 2};

u32 data_ov042_02258aa0[1] = {0x1019};

SceneSpawnGroup data_ov042_02258ae8[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov042_02258abc},
    {0, 2, 0, data_ov042_02258b00},
};

SceneInfo data_ov042_02258ad0 = {&data_ov042_02258aac, 0, &data_ov042_02258aa4, &data_ov042_02258ab4, 0x32, -1};

SceneMapInfo data_ov042_02258aa4 = {data_ov042_02258aa0, 1, 1};

SceneSpawnRecord data_ov042_02258abc[1] = {
    {0x1000009, 0x1ae0002, 0x80000000, 0, 0x800000},
};

SceneWarp data_ov042_02258b58[2] = {
    SceneWarp(0x1d, VecFx32Copy(0x10000, 0x200, 0x9000), 0x11000000, 0, 2, 2, -0x8000, 2),
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0, 0, 2, 2, 0, 0),
};

SceneSpawnList data_ov042_02258aac = {3, 0, data_ov042_02258ae8};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov042_022589e0) {
    HOST_OVERLAY_VAR(data_ov042_02258b00),
    HOST_OVERLAY_VAR(data_ov042_02258ab4),
    HOST_OVERLAY_VAR(data_ov042_02258aa0),
    HOST_OVERLAY_VAR(data_ov042_02258ae8),
    HOST_OVERLAY_VAR(data_ov042_02258ad0),
    HOST_OVERLAY_VAR(data_ov042_02258aa4),
    HOST_OVERLAY_VAR(data_ov042_02258abc),
    HOST_OVERLAY_VAR(data_ov042_02258b58),
    HOST_OVERLAY_VAR(data_ov042_02258aac),
    HOST_OVERLAY_VARS_END
};
