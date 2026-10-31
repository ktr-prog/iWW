#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"





extern SceneSpawnGroup data_ov018_02258ab4[1];
extern SceneWarp data_ov018_02258b24[3];
extern u32 data_ov018_02258aa0[1];
extern SceneInfo data_ov018_02258acc;
extern SceneSpawnList data_ov018_02258abc;
extern SceneMapInfo data_ov018_02258ac4;
extern SceneWarpList data_ov018_02258aac;
extern u32 data_ov018_02258aa4[2];

SceneSpawnGroup data_ov018_02258ab4[1] = {
    {2, 2, 0, data_ov018_02258aa4},
};

SceneWarp data_ov018_02258b24[3] = {
    SceneWarp(0x3e, VecFx32Copy(0, 0, 0), 0x800000, 0, 3, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 3, 2, 0, 0),
    SceneWarp(0x3d, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

u32 data_ov018_02258aa0[1] = {0x1015};

SceneInfo data_ov018_02258acc = {&data_ov018_02258abc, 0, &data_ov018_02258ac4, &data_ov018_02258aac, 0x38, -1};

SceneSpawnList data_ov018_02258abc = {1, 0, data_ov018_02258ab4};

SceneMapInfo data_ov018_02258ac4 = {data_ov018_02258aa0, 1, 1};

SceneWarpList data_ov018_02258aac = {data_ov018_02258b24, 3};

u32 data_ov018_02258aa4[2] = {0xb, 0xcd};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov018_022589e0) {
    HOST_OVERLAY_VAR(data_ov018_02258ab4),
    HOST_OVERLAY_VAR(data_ov018_02258b24),
    HOST_OVERLAY_VAR(data_ov018_02258aa0),
    HOST_OVERLAY_VAR(data_ov018_02258acc),
    HOST_OVERLAY_VAR(data_ov018_02258abc),
    HOST_OVERLAY_VAR(data_ov018_02258ac4),
    HOST_OVERLAY_VAR(data_ov018_02258aac),
    HOST_OVERLAY_VAR(data_ov018_02258aa4),
    HOST_OVERLAY_VARS_END
};
