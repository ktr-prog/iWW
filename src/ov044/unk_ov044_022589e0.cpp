#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern u32 data_ov044_02258a40[1];
extern SceneMapInfo data_ov044_02258a44;
extern SceneSpawnList data_ov044_02258a4c;
extern SceneSpawnGroup data_ov044_02258a70[3];
extern SceneWarp data_ov044_02258aec[1];
extern SceneSpawnRecord data_ov044_02258aa0[2];
extern SceneSpawnRecord data_ov044_02258a5c[1];
extern SceneInfo data_ov044_02258a88;
extern SceneWarpList data_ov044_02258a54;

u32 data_ov044_02258a40[1] = {0x1027};

SceneMapInfo data_ov044_02258a44 = {data_ov044_02258a40, 1, 1};

SceneSpawnList data_ov044_02258a4c = {3, 0, data_ov044_02258a70};

SceneSpawnGroup data_ov044_02258a70[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov044_02258a5c},
    {0, 2, 0, data_ov044_02258aa0},
};

SceneWarp data_ov044_02258aec[1] = {
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

SceneSpawnRecord data_ov044_02258aa0[2] = {
    {0x100007b, 0x1980000, 0x80000000, 0, 0xd014},
    {0x13, 0, 0, 0, 0},
};

SceneSpawnRecord data_ov044_02258a5c[1] = {
    {0x1200009, 0x1c00002, 0x80000000, 0, 0x400000},
};

SceneInfo data_ov044_02258a88 = {&data_ov044_02258a4c, 0, &data_ov044_02258a44, &data_ov044_02258a54, 0x33, -1};

SceneWarpList data_ov044_02258a54 = {data_ov044_02258aec, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov044_022589e0) {
    HOST_OVERLAY_VAR(data_ov044_02258a40),
    HOST_OVERLAY_VAR(data_ov044_02258a44),
    HOST_OVERLAY_VAR(data_ov044_02258a4c),
    HOST_OVERLAY_VAR(data_ov044_02258a70),
    HOST_OVERLAY_VAR(data_ov044_02258aec),
    HOST_OVERLAY_VAR(data_ov044_02258aa0),
    HOST_OVERLAY_VAR(data_ov044_02258a5c),
    HOST_OVERLAY_VAR(data_ov044_02258a88),
    HOST_OVERLAY_VAR(data_ov044_02258a54),
    HOST_OVERLAY_VARS_END
};
