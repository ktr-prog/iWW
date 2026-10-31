#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnRecord data_ov033_02258a80[1];
extern SceneInfo data_ov033_02258a94;
extern SceneSpawnGroup data_ov033_02258aac[3];
extern u32 data_ov033_02258a64[1];
extern u32 data_ov033_02258a60[1];
extern SceneWarp data_ov033_02258aec[1];
extern SceneWarpList data_ov033_02258a68;
extern SceneSpawnList data_ov033_02258a78;
extern SceneMapInfo data_ov033_02258a70;

SceneSpawnRecord data_ov033_02258a80[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov033_02258a94 = {&data_ov033_02258a78, 0, &data_ov033_02258a70, &data_ov033_02258a68, -1, -1};

SceneSpawnGroup data_ov033_02258aac[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 1, 0, data_ov033_02258a64},
    {1, 1, 0, data_ov033_02258a80},
};

u32 data_ov033_02258a64[1] = {0x100d0};

u32 data_ov033_02258a60[1] = {0x1000};

SceneWarp data_ov033_02258aec[1] = {
    SceneWarp(1, VecFx32Copy(0x7000, 0x200, 0x1a000), 0x23800000, 0x4000, 2, 2, 0x4000, 3),
};

SceneWarpList data_ov033_02258a68 = {data_ov033_02258aec, 1};

SceneSpawnList data_ov033_02258a78 = {3, 0, data_ov033_02258aac};

SceneMapInfo data_ov033_02258a70 = {data_ov033_02258a60, 1, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov033_022589e0) {
    HOST_OVERLAY_VAR(data_ov033_02258a80),
    HOST_OVERLAY_VAR(data_ov033_02258a94),
    HOST_OVERLAY_VAR(data_ov033_02258aac),
    HOST_OVERLAY_VAR(data_ov033_02258a64),
    HOST_OVERLAY_VAR(data_ov033_02258a60),
    HOST_OVERLAY_VAR(data_ov033_02258aec),
    HOST_OVERLAY_VAR(data_ov033_02258a68),
    HOST_OVERLAY_VAR(data_ov033_02258a78),
    HOST_OVERLAY_VAR(data_ov033_02258a70),
    HOST_OVERLAY_VARS_END
};
