#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnList data_ov035_02258ab0;
extern SceneInfo data_ov035_02258ad4;
extern SceneSpawnGroup data_ov035_02258aec[3];
extern u32 data_ov035_02258aa4[1];
extern SceneMapInfo data_ov035_02258aa8;
extern u32 data_ov035_02258aa0[1];
extern SceneWarpList data_ov035_02258ab8;
extern SceneSpawnRecord data_ov035_02258ac0[1];
extern SceneWarp data_ov035_02258b38[2];

SceneSpawnList data_ov035_02258ab0 = {3, 0, data_ov035_02258aec};

SceneInfo data_ov035_02258ad4 = {&data_ov035_02258ab0, 0, &data_ov035_02258aa8, &data_ov035_02258ab8, -1, -1};

SceneSpawnGroup data_ov035_02258aec[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 1, 0, data_ov035_02258aa0},
    {1, 1, 0, data_ov035_02258ac0},
};

u32 data_ov035_02258aa4[1] = {0x1000};

SceneMapInfo data_ov035_02258aa8 = {data_ov035_02258aa4, 1, 1};

u32 data_ov035_02258aa0[1] = {0x100d0};

SceneWarpList data_ov035_02258ab8 = {data_ov035_02258b38, 2};

SceneSpawnRecord data_ov035_02258ac0[1] = {
    {0x1000009, 0x1c00002, 0x80000000, 0, 0x800000},
};

SceneWarp data_ov035_02258b38[2] = {
    SceneWarp(7, VecFx32Copy(0x11000, 0x200, 0x1d000), 0x10c00000, -0x4000, 2, 2, 0x4000, 1),
    SceneWarp(1, VecFx32Copy(0xf000, 0x200, 0x1d000), 0x11000000, 0x4000, 2, 2, -0x4000, 2),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov035_022589e0) {
    HOST_OVERLAY_VAR(data_ov035_02258ab0),
    HOST_OVERLAY_VAR(data_ov035_02258ad4),
    HOST_OVERLAY_VAR(data_ov035_02258aec),
    HOST_OVERLAY_VAR(data_ov035_02258aa4),
    HOST_OVERLAY_VAR(data_ov035_02258aa8),
    HOST_OVERLAY_VAR(data_ov035_02258aa0),
    HOST_OVERLAY_VAR(data_ov035_02258ab8),
    HOST_OVERLAY_VAR(data_ov035_02258ac0),
    HOST_OVERLAY_VAR(data_ov035_02258b38),
    HOST_OVERLAY_VARS_END
};
