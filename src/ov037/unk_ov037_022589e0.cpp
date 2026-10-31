#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"





extern SceneSpawnGroup data_ov037_02258aac[1];
extern SceneWarp data_ov037_02258b24[3];
extern u32 data_ov037_02258aa0[1];
extern SceneMapInfo data_ov037_02258aa4;
extern SceneSpawnList data_ov037_02258ab4;
extern SceneWarpList data_ov037_02258abc;
extern SceneInfo data_ov037_02258ad4;
extern u32 data_ov037_02258ac4[4];

SceneSpawnGroup data_ov037_02258aac[1] = {
    {2, 4, 0, data_ov037_02258ac4},
};

SceneWarp data_ov037_02258b24[3] = {
    SceneWarp(0x3e, VecFx32Copy(0, 0, 0), 0x800000, 0, 3, 2, 0, 0),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 3, 2, 0, 0),
    SceneWarp(0x3d, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

u32 data_ov037_02258aa0[1] = {0x1015};

SceneMapInfo data_ov037_02258aa4 = {data_ov037_02258aa0, 1, 1};

SceneSpawnList data_ov037_02258ab4 = {1, 0, data_ov037_02258aac};

SceneWarpList data_ov037_02258abc = {data_ov037_02258b24, 3};

SceneInfo data_ov037_02258ad4 = {&data_ov037_02258ab4, 0, &data_ov037_02258aa4, &data_ov037_02258abc, -1, -1};

u32 data_ov037_02258ac4[4] = {0xc9, 0xca, 0xb, 0xc7};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov037_022589e0) {
    HOST_OVERLAY_VAR(data_ov037_02258aac),
    HOST_OVERLAY_VAR(data_ov037_02258b24),
    HOST_OVERLAY_VAR(data_ov037_02258aa0),
    HOST_OVERLAY_VAR(data_ov037_02258aa4),
    HOST_OVERLAY_VAR(data_ov037_02258ab4),
    HOST_OVERLAY_VAR(data_ov037_02258abc),
    HOST_OVERLAY_VAR(data_ov037_02258ad4),
    HOST_OVERLAY_VAR(data_ov037_02258ac4),
    HOST_OVERLAY_VARS_END
};
