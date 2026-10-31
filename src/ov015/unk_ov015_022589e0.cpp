#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"




extern u32 sRoomCommonProfiles[];

extern u32 data_ov015_02258ac0[1];
extern SceneSpawnRecord data_ov015_02258b30[3];
extern SceneSpawnList data_ov015_02258acc;
extern SceneWarpList data_ov015_02258ac4;
extern SceneInfo data_ov015_02258af8;
extern SceneSpawnGroup data_ov015_02258b10[4];
extern SceneSpawnRecord data_ov015_02258ae4[1];
extern u32 data_ov015_02258adc[2];
extern SceneMapInfo data_ov015_02258ad4;
extern SceneWarp data_ov015_02258ba4[3];

u32 data_ov015_02258ac0[1] = {0x101a};

SceneSpawnRecord data_ov015_02258b30[3] = {
    {0x11, 0, 0, 0, 0},
    {0x1400072, 0x1100000, 0, 0, 0xd000},
    {0xc00073, 0x1100000, 0, 0, 0xd001},
};

SceneSpawnList data_ov015_02258acc = {4, 0, data_ov015_02258b10};

SceneWarpList data_ov015_02258ac4 = {data_ov015_02258ba4, 3};

SceneInfo data_ov015_02258af8 = {&data_ov015_02258acc, 0, &data_ov015_02258ad4, &data_ov015_02258ac4, 0x30, -1};

SceneSpawnGroup data_ov015_02258b10[4] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
    {2, 2, 0, data_ov015_02258adc},
    {1, 1, 0, data_ov015_02258ae4},
    {0, 3, 0, data_ov015_02258b30},
};

SceneSpawnRecord data_ov015_02258ae4[1] = {
    {0x1000009, 0x1a00002, 0x80000000, 0, 0x800000},
};

u32 data_ov015_02258adc[2] = {0xd0, 0xc7};

SceneMapInfo data_ov015_02258ad4 = {data_ov015_02258ac0, 1, 1};

SceneWarp data_ov015_02258ba4[3] = {
    SceneWarp(0x3d, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 4),
    SceneWarp(0x3f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
    SceneWarp(0x2f, VecFx32Copy(0, 0, 0), 0x800000, 0, 2, 2, 0, 0),
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov015_022589e0) {
    HOST_OVERLAY_VAR(data_ov015_02258ac0),
    HOST_OVERLAY_VAR(data_ov015_02258b30),
    HOST_OVERLAY_VAR(data_ov015_02258acc),
    HOST_OVERLAY_VAR(data_ov015_02258ac4),
    HOST_OVERLAY_VAR(data_ov015_02258af8),
    HOST_OVERLAY_VAR(data_ov015_02258b10),
    HOST_OVERLAY_VAR(data_ov015_02258ae4),
    HOST_OVERLAY_VAR(data_ov015_02258adc),
    HOST_OVERLAY_VAR(data_ov015_02258ad4),
    HOST_OVERLAY_VAR(data_ov015_02258ba4),
    HOST_OVERLAY_VARS_END
};
