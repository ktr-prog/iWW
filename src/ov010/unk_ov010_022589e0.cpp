#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern SceneWarpList sRoomSceneEntryList;
extern u32 sRoomCommonProfiles[];

extern SceneSpawnGroup data_ov010_02258a58[4];
extern SceneSpawnRecord data_ov010_02258a18[1];
extern SceneSpawnList data_ov010_02258a08;
extern u32 data_ov010_02258a00[1];
extern SceneSpawnRecord data_ov010_02258a2c[1];
extern SceneMapInfo data_ov010_02258a10;
extern SceneInfo data_ov010_02258a40;
extern u32 data_ov010_02258a04[1];

SceneSpawnGroup data_ov010_02258a58[4] = {
    {2, 1, 0, data_ov010_02258a00},
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov010_02258a18},
    {0, 1, 0, data_ov010_02258a2c},
};

SceneSpawnRecord data_ov010_02258a18[1] = {
    {0x1000009, 0x1400002, 0, 0, 0x800000},
};

SceneSpawnList data_ov010_02258a08 = {4, 0, data_ov010_02258a58};

u32 data_ov010_02258a00[1] = {0x2b};

SceneSpawnRecord data_ov010_02258a2c[1] = {
    {0x2d, 0, 0, 0, 0},
};

SceneMapInfo data_ov010_02258a10 = {data_ov010_02258a04, 1, 1};

SceneInfo data_ov010_02258a40 = {&data_ov010_02258a08, 0, &data_ov010_02258a10, &sRoomSceneEntryList, -1, -1};

u32 data_ov010_02258a04[1] = {0x1003};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov010_022589e0) {
    HOST_OVERLAY_VAR(data_ov010_02258a58),
    HOST_OVERLAY_VAR(data_ov010_02258a18),
    HOST_OVERLAY_VAR(data_ov010_02258a08),
    HOST_OVERLAY_VAR(data_ov010_02258a00),
    HOST_OVERLAY_VAR(data_ov010_02258a2c),
    HOST_OVERLAY_VAR(data_ov010_02258a10),
    HOST_OVERLAY_VAR(data_ov010_02258a40),
    HOST_OVERLAY_VAR(data_ov010_02258a04),
    HOST_OVERLAY_VARS_END
};
