#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern SceneSpawnRecord data_ov041_02258b40[3];
extern u32 data_ov041_02258ae0[1];
extern SceneSpawnGroup data_ov041_02258b28[3];
extern SceneSpawnList data_ov041_02258aec;
extern SceneMapInfo data_ov041_02258af4;
extern SceneWarpList data_ov041_02258ae4;
extern SceneWarp data_ov041_02258ba4[3];
extern SceneSpawnRecord data_ov041_02258afc[1];
extern SceneInfo data_ov041_02258b10;

SceneSpawnRecord data_ov041_02258b40[3] = {
    {0x1100076, 0x1a00000, 0, 0, 0xd01c},
    {0x150002c, 0x1900000, 0xc0000000, 0, 0},
    {0x16, 0, 0xc0000000, 0, 0},
};

u32 data_ov041_02258ae0[1] = {0x1018};

SceneSpawnGroup data_ov041_02258b28[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov041_02258afc},
    {0, 3, 0, data_ov041_02258b40},
};

SceneSpawnList data_ov041_02258aec = {3, 0, data_ov041_02258b28};

SceneMapInfo data_ov041_02258af4 = {data_ov041_02258ae0, 1, 1};

SceneWarpList data_ov041_02258ae4 = {data_ov041_02258ba4, 3};

SceneWarp data_ov041_02258ba4[3] = {
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0, 0, 2, 2, 0, 4),
    SceneWarp(0x1e, VecFx32Copy(0x10000, 0x200, 0x9000), 0x10c00000, 0, 2, 2, -0x8000, 1),
    SceneWarp(0x1f, VecFx32Copy(0x10000, 0x200, 0x1d000), 0x23800000, -0x8000, 2, 2, -0x8000, 3),
};

SceneSpawnRecord data_ov041_02258afc[1] = {
    {0x1000009, 0x1c00002, 0x80000000, 0, 0x800000},
};

SceneInfo data_ov041_02258b10 = {&data_ov041_02258aec, 0, &data_ov041_02258af4, &data_ov041_02258ae4, 0x32, -1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov041_022589e0) {
    HOST_OVERLAY_VAR(data_ov041_02258b40),
    HOST_OVERLAY_VAR(data_ov041_02258ae0),
    HOST_OVERLAY_VAR(data_ov041_02258b28),
    HOST_OVERLAY_VAR(data_ov041_02258aec),
    HOST_OVERLAY_VAR(data_ov041_02258af4),
    HOST_OVERLAY_VAR(data_ov041_02258ae4),
    HOST_OVERLAY_VAR(data_ov041_02258ba4),
    HOST_OVERLAY_VAR(data_ov041_02258afc),
    HOST_OVERLAY_VAR(data_ov041_02258b10),
    HOST_OVERLAY_VARS_END
};
