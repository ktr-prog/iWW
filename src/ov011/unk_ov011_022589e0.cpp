#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern SceneWarpList sRoomSceneEntryList;
extern u32 sRoomCommonProfiles[];

extern SceneMapInfo data_ov011_02258a04;
extern u32 data_ov011_02258a00[1];
extern SceneSpawnGroup data_ov011_02258a4c[4];
extern SceneSpawnList data_ov011_02258a0c;
extern SceneSpawnRecord data_ov011_02258a20[1];
extern SceneSpawnRecord data_ov011_02258a6c[4];
extern u32 data_ov011_02258a14[3];
extern SceneInfo data_ov011_02258a34;

SceneMapInfo data_ov011_02258a04 = {data_ov011_02258a00, 1, 1};

u32 data_ov011_02258a00[1] = {0x1003};

SceneSpawnGroup data_ov011_02258a4c[4] = {
    {2, 3, 0, data_ov011_02258a14},
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 4, 0, data_ov011_02258a6c},
    {0, 1, 0, data_ov011_02258a20},
};

SceneSpawnList data_ov011_02258a0c = {4, 0, data_ov011_02258a4c};

SceneSpawnRecord data_ov011_02258a20[1] = {
    {0x2d, 0, 0, 0, 0},
};

SceneSpawnRecord data_ov011_02258a6c[4] = {
    {0xd00009, 0x1400002, 0, 0, 0x2000000},
    {0x1300009, 0x1400002, 0, 0, 0x2000000},
    {0xd00009, 0x1a00002, 0, 0, 0x2000000},
    {0x1300009, 0x1a00002, 0, 0, 0x2000000},
};

u32 data_ov011_02258a14[3] = {0x2b, 0xd3, 0xc7};

SceneInfo data_ov011_02258a34 = {&data_ov011_02258a0c, 0, &data_ov011_02258a04, &sRoomSceneEntryList, -1, -1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov011_022589e0) {
    HOST_OVERLAY_VAR(data_ov011_02258a04),
    HOST_OVERLAY_VAR(data_ov011_02258a00),
    HOST_OVERLAY_VAR(data_ov011_02258a4c),
    HOST_OVERLAY_VAR(data_ov011_02258a0c),
    HOST_OVERLAY_VAR(data_ov011_02258a20),
    HOST_OVERLAY_VAR(data_ov011_02258a6c),
    HOST_OVERLAY_VAR(data_ov011_02258a14),
    HOST_OVERLAY_VAR(data_ov011_02258a34),
    HOST_OVERLAY_VARS_END
};
