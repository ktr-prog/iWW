#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneWarpList data_ov022_02258afc;
extern SceneSpawnGroup data_ov022_02258b30[3];
extern SceneWarp data_ov022_02258b84[3];
extern u32 data_ov022_02258ae0[1];
extern SceneSpawnRecord data_ov022_02258b04[1];
extern u32 data_ov022_02258aec[2];
extern SceneSpawnList data_ov022_02258af4;
extern SceneMapInfo data_ov022_02258ae4;
extern SceneInfo data_ov022_02258b18;

SceneWarpList data_ov022_02258afc = {data_ov022_02258b84, 3};

SceneSpawnGroup data_ov022_02258b30[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 2, 0, data_ov022_02258aec},
    {1, 1, 0, data_ov022_02258b04},
};

SceneWarp data_ov022_02258b84[3] = {
    SceneWarp(0x20, VecFx32Copy(0x17000, 0, 0x1a000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
    SceneWarp(0x24, VecFx32Copy(0x6000, 0, 0x1d000), 0x23800000, -0x8000, 2, 2, -0x8000, 3),
    SceneWarp(0x24, VecFx32Copy(0x1c000, 0, 0x1d000), 0x23800000, -0x8000, 2, 2, -0x8000, 3),
};

u32 data_ov022_02258ae0[1] = {0x101e};

SceneSpawnRecord data_ov022_02258b04[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

u32 data_ov022_02258aec[2] = {0x51, 0xc3};

SceneSpawnList data_ov022_02258af4 = {3, 0, data_ov022_02258b30};

SceneMapInfo data_ov022_02258ae4 = {data_ov022_02258ae0, 1, 1};

SceneInfo data_ov022_02258b18 = {&data_ov022_02258af4, 0, &data_ov022_02258ae4, &data_ov022_02258afc, -1, -1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov022_022589e0) {
    HOST_OVERLAY_VAR(data_ov022_02258afc),
    HOST_OVERLAY_VAR(data_ov022_02258b30),
    HOST_OVERLAY_VAR(data_ov022_02258b84),
    HOST_OVERLAY_VAR(data_ov022_02258ae0),
    HOST_OVERLAY_VAR(data_ov022_02258b04),
    HOST_OVERLAY_VAR(data_ov022_02258aec),
    HOST_OVERLAY_VAR(data_ov022_02258af4),
    HOST_OVERLAY_VAR(data_ov022_02258ae4),
    HOST_OVERLAY_VAR(data_ov022_02258b18),
    HOST_OVERLAY_VARS_END
};
