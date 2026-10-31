#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/FxVec3.h"
#include "game/SceneInfo.h"





extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov024_02258af4;
extern u32 data_ov024_02258ac0[1];
extern SceneWarpList data_ov024_02258ac8;
extern u32 data_ov024_02258ac4[1];
extern SceneMapInfo data_ov024_02258ad8;
extern SceneSpawnGroup data_ov024_02258b0c[3];
extern const FxVec3 data_ov024_02258b64;
extern SceneSpawnList data_ov024_02258ad0;
extern SceneSpawnRecord data_ov024_02258ae0[1];
extern SceneWarp data_ov024_02258b70[2];

SceneInfo data_ov024_02258af4 = {&data_ov024_02258ad0, 0, &data_ov024_02258ad8, &data_ov024_02258ac8, -1, -1};

u32 data_ov024_02258ac0[1] = {0x1022};

SceneWarpList data_ov024_02258ac8 = {data_ov024_02258b70, 2};

u32 data_ov024_02258ac4[1] = {0x52};

SceneMapInfo data_ov024_02258ad8 = {data_ov024_02258ac0, 1, 1};

SceneSpawnGroup data_ov024_02258b0c[3] = {
    {2, 1, 0, data_ov024_02258ac4},
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {1, 1, 0, data_ov024_02258ae0},
};

constexpr FxVec3 data_ov024_02258b64(0x10000, 0x200, 0x1d000);

SceneSpawnList data_ov024_02258ad0 = {3, 0, data_ov024_02258b0c};

SceneSpawnRecord data_ov024_02258ae0[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

SceneWarp data_ov024_02258b70[2] = {
    SceneWarp(0x20, VecFx32Copy(0x17000, 0, 0x14000), 0x23800000, -0x4000, 2, 2, -0x4000, 3),
    SceneWarp(0x26, data_ov024_02258b64, 0x23800000, -0x8000, 2, 2, -0x8000, 3),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov024_022589e0) {
    HOST_OVERLAY_VAR(data_ov024_02258af4),
    HOST_OVERLAY_VAR(data_ov024_02258ac0),
    HOST_OVERLAY_VAR(data_ov024_02258ac8),
    HOST_OVERLAY_VAR(data_ov024_02258ac4),
    HOST_OVERLAY_VAR(data_ov024_02258ad8),
    HOST_OVERLAY_VAR(data_ov024_02258b0c),
    HOST_OVERLAY_VAR(data_ov024_02258ad0),
    HOST_OVERLAY_VAR(data_ov024_02258ae0),
    HOST_OVERLAY_VAR(data_ov024_02258b70),
    HOST_OVERLAY_VARS_END
};
