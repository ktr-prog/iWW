#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/FxVec3.h"
#include "game/SceneInfo.h"





extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov032_02258c34;
extern SceneSpawnGroup data_ov032_02258c4c[3];
extern SceneSpawnRecord data_ov032_02258c20[1];
extern SceneSpawnList data_ov032_02258c08;
extern SceneWarpList data_ov032_02258c18;
extern SceneMapInfo data_ov032_02258c10;
extern const FxVec3 data_ov032_02258ca4;
extern SceneWarp data_ov032_02258cec[7];
extern u32 data_ov032_02258c04[1];
extern u32 data_ov032_02258c00[1];

SceneInfo data_ov032_02258c34 = {&data_ov032_02258c08, 0, &data_ov032_02258c10, &data_ov032_02258c18, -1, -1};

SceneSpawnGroup data_ov032_02258c4c[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 1, 0, data_ov032_02258c00},
    {1, 1, 0, data_ov032_02258c20},
};

SceneSpawnRecord data_ov032_02258c20[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneSpawnList data_ov032_02258c08 = {3, 0, data_ov032_02258c4c};

SceneWarpList data_ov032_02258c18 = {data_ov032_02258cec, 7};

SceneMapInfo data_ov032_02258c10 = {data_ov032_02258c04, 1, 1};

constexpr FxVec3 data_ov032_02258ca4(0x10000, 0, 0x1d000);

SceneWarp data_ov032_02258cec[7] = {
    SceneWarp(0x3e, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 4),
    SceneWarp(7, VecFx32Copy(0xf000, 0, 0x1d000), 0x10c00000, 0x4000, 2, 2, -0x4000, 1),
    SceneWarp(5, VecFx32Copy(0xf000, 0, 0x1d000), 0x10c00000, 0x4000, 2, 2, -0x4000, 1),
    SceneWarp(4, VecFx32Copy(0x17000, 0, 0x1a000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
    SceneWarp(3, VecFx32Copy(0x9000, 0, 0x1a000), 0x23800000, 0x4000, 2, 2, 0x4000, 3),
    SceneWarp(2, data_ov032_02258ca4, 0x23800000, -0x8000, 2, 2, -0x8000, 3),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

u32 data_ov032_02258c04[1] = {0x1004};

u32 data_ov032_02258c00[1] = {0x100d0};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov032_022589e0) {
    HOST_OVERLAY_VAR(data_ov032_02258c34),
    HOST_OVERLAY_VAR(data_ov032_02258c4c),
    HOST_OVERLAY_VAR(data_ov032_02258c20),
    HOST_OVERLAY_VAR(data_ov032_02258c08),
    HOST_OVERLAY_VAR(data_ov032_02258c18),
    HOST_OVERLAY_VAR(data_ov032_02258c10),
    HOST_OVERLAY_VAR(data_ov032_02258cec),
    HOST_OVERLAY_VAR(data_ov032_02258c04),
    HOST_OVERLAY_VAR(data_ov032_02258c00),
    HOST_OVERLAY_VARS_END
};
