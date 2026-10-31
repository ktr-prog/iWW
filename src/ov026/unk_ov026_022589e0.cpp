#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov026_02258b1c;
extern SceneWarpList data_ov026_02258ae4;
extern SceneSpawnGroup data_ov026_02258b34[3];
extern SceneMapInfo data_ov026_02258af4;
extern SceneSpawnList data_ov026_02258aec;
extern SceneWarp data_ov026_02258b84[3];
extern u32 data_ov026_02258afc[3];
extern SceneSpawnRecord data_ov026_02258b08[1];
extern u32 data_ov026_02258ae0[1];

SceneInfo data_ov026_02258b1c = {&data_ov026_02258aec, 0, &data_ov026_02258af4, &data_ov026_02258ae4, -1, -1};

SceneWarpList data_ov026_02258ae4 = {data_ov026_02258b84, 3};

SceneSpawnGroup data_ov026_02258b34[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 3, 0, data_ov026_02258afc},
    {1, 1, 0, data_ov026_02258b08},
};

SceneMapInfo data_ov026_02258af4 = {data_ov026_02258ae0, 1, 1};

SceneSpawnList data_ov026_02258aec = {3, 0, data_ov026_02258b34};

SceneWarp data_ov026_02258b84[3] = {
    SceneWarp(0x20, VecFx32Copy(0x16000, 0, 0x11000), 0x23800000, 0, 2, 2, 0, 3),
    SceneWarp(0x28, VecFx32Copy(0x1b000, 0, 0x1a000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
    SceneWarp(0x28, VecFx32Copy(0x1b000, 0, 0x8000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
};

u32 data_ov026_02258afc[3] = {0x51, 0xbe, 0xbf};

SceneSpawnRecord data_ov026_02258b08[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

u32 data_ov026_02258ae0[1] = {0x1020};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov026_022589e0) {
    HOST_OVERLAY_VAR(data_ov026_02258b1c),
    HOST_OVERLAY_VAR(data_ov026_02258ae4),
    HOST_OVERLAY_VAR(data_ov026_02258b34),
    HOST_OVERLAY_VAR(data_ov026_02258af4),
    HOST_OVERLAY_VAR(data_ov026_02258aec),
    HOST_OVERLAY_VAR(data_ov026_02258b84),
    HOST_OVERLAY_VAR(data_ov026_02258afc),
    HOST_OVERLAY_VAR(data_ov026_02258b08),
    HOST_OVERLAY_VAR(data_ov026_02258ae0),
    HOST_OVERLAY_VARS_END
};
