#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern u32 data_ov029_02258b80[1];
extern SceneSpawnGroup data_ov029_02258bb8[3];
extern SceneSpawnRecord data_ov029_02258ba4[1];
extern SceneSpawnList data_ov029_02258b9c;
extern SceneWarpList data_ov029_02258b8c;
extern SceneMapInfo data_ov029_02258b94;
extern SceneWarp data_ov029_02258c54[7];
extern SceneInfo data_ov029_02258bd0;
extern u32 data_ov029_02258b84[2];

u32 data_ov029_02258b80[1] = {0x1010};

SceneSpawnGroup data_ov029_02258bb8[3] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 2, 0, data_ov029_02258b84},
    {1, 1, 0, data_ov029_02258ba4},
};

SceneSpawnRecord data_ov029_02258ba4[1] = {
    {0x1000009, 0x1d00002, 0x80000000, 0, 0x800000},
};

SceneSpawnList data_ov029_02258b9c = {3, 0, data_ov029_02258bb8};

SceneWarpList data_ov029_02258b8c = {data_ov029_02258c54, 7};

SceneMapInfo data_ov029_02258b94 = {data_ov029_02258b80, 1, 1};

SceneWarp data_ov029_02258c54[7] = {
    SceneWarp(0x3c, VecFx32Copy(0, 0, 0), 0, 0, 2, 2, 0, 4),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0, 0, 2, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

SceneInfo data_ov029_02258bd0 = {&data_ov029_02258b9c, 0, &data_ov029_02258b94, &data_ov029_02258b8c, -1, -1};

u32 data_ov029_02258b84[2] = {0x100d0, 0x100c2};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov029_022589e0) {
    HOST_OVERLAY_VAR(data_ov029_02258b80),
    HOST_OVERLAY_VAR(data_ov029_02258bb8),
    HOST_OVERLAY_VAR(data_ov029_02258ba4),
    HOST_OVERLAY_VAR(data_ov029_02258b9c),
    HOST_OVERLAY_VAR(data_ov029_02258b8c),
    HOST_OVERLAY_VAR(data_ov029_02258b94),
    HOST_OVERLAY_VAR(data_ov029_02258c54),
    HOST_OVERLAY_VAR(data_ov029_02258bd0),
    HOST_OVERLAY_VAR(data_ov029_02258b84),
    HOST_OVERLAY_VARS_END
};
