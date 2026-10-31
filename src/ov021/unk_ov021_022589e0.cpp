#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/FxVec3.h"
#include "game/SceneInfo.h"





extern u32 sRoomCommonProfiles[];

extern SceneWarpList data_ov021_02258c0c;
extern u32 data_ov021_02258c00[1];
extern SceneSpawnRecord data_ov021_02258c24[1];
extern SceneSpawnGroup data_ov021_02258c64[4];
extern SceneSpawnList data_ov021_02258c04;
extern SceneInfo data_ov021_02258c4c;
extern u32 data_ov021_02258c14[2];
extern const FxVec3 data_ov021_02258cc4;
extern SceneWarp data_ov021_02258d0c[7];
extern SceneSpawnRecord data_ov021_02258c38[1];
extern SceneMapInfo data_ov021_02258c1c;

SceneWarpList data_ov021_02258c0c = {data_ov021_02258d0c, 7};

u32 data_ov021_02258c00[1] = {0x101d};

SceneSpawnRecord data_ov021_02258c24[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneSpawnGroup data_ov021_02258c64[4] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 2, 0, data_ov021_02258c14},
    {1, 1, 0, data_ov021_02258c24},
    {0, 1, 0, data_ov021_02258c38},
};

SceneSpawnList data_ov021_02258c04 = {4, 0, data_ov021_02258c64};

SceneInfo data_ov021_02258c4c = {&data_ov021_02258c04, 0, &data_ov021_02258c1c, &data_ov021_02258c0c, 0x2f, -1};

u32 data_ov021_02258c14[2] = {0x100c2, 0x51};

constexpr FxVec3 data_ov021_02258cc4(0x10000, 0x200, 0x1d000);

SceneWarp data_ov021_02258d0c[7] = {
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 4),
    SceneWarp(0x21, VecFx32Copy(0x1b000, 0, 0x1a000), 0x23800000, -0x4000, 2, 2, -0x4000, 2),
    SceneWarp(0x29, VecFx32Copy(0x1b000, 0, 0x1e000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
    SceneWarp(0x22, data_ov021_02258cc4, 0x23800000, -0x8000, 2, 2, -0x8000, 1),
    SceneWarp(0x27, VecFx32Copy(0x16000, 0, 0x1d000), 0x23800000, -0x8000, 2, 2, -0x8000, 3),
    SceneWarp(0x25, VecFx32Copy(0x5000, 0, 0x1a000), 0x23800000, 0x4000, 2, 2, 0x4000, 3),
    SceneWarp(0x23, VecFx32Copy(0x5000, 0, 0x1a000), 0x23800000, 0x4000, 2, 2, 0x4000, 3),
};

SceneSpawnRecord data_ov021_02258c38[1] = {
    {0xf0006e, 0x1500000, 0, 0, 0xd00c},
};

SceneMapInfo data_ov021_02258c1c = {data_ov021_02258c00, 1, 1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov021_022589e0) {
    HOST_OVERLAY_VAR(data_ov021_02258c0c),
    HOST_OVERLAY_VAR(data_ov021_02258c00),
    HOST_OVERLAY_VAR(data_ov021_02258c24),
    HOST_OVERLAY_VAR(data_ov021_02258c64),
    HOST_OVERLAY_VAR(data_ov021_02258c04),
    HOST_OVERLAY_VAR(data_ov021_02258c4c),
    HOST_OVERLAY_VAR(data_ov021_02258c14),
    HOST_OVERLAY_VAR(data_ov021_02258d0c),
    HOST_OVERLAY_VAR(data_ov021_02258c38),
    HOST_OVERLAY_VAR(data_ov021_02258c1c),
    HOST_OVERLAY_VARS_END
};
