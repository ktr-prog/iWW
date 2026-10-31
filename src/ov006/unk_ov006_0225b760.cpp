#include "types.h"
#include "gfx/VecFx32.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"
#include "proto/ov003/unk_ov003_022187f8.h"
#include "proto/ov006/unk_ov006_0225b760.h"





extern u32 data_ov006_0225b7cc[36];
extern SceneInfo data_ov006_0225b79c;
extern u32 data_ov006_0225b790[3];
extern SceneSpawnList data_ov006_0225b780;
extern SceneSpawnGroup data_ov006_0225b7b4[3];
extern SceneMapInfo data_ov006_0225b788;

u32 data_ov006_0225b7cc[36] = {
    0x12, 0xc, 0xd, 0xb, 0xa, 0x13, 0xe, 0x1a, 0x46, 0x15, 0x15, 0x10,
    0xe, 0x14, 0x4b, 0x16, 0x16, 0x10, 0xe, 0x14, 0x4a, 0x26, 0x17, 0x10,
    0xf, 0x29, 0x2d, 0x29, 0x29, 0x11, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
};

SceneInfo data_ov006_0225b79c = {&data_ov006_0225b780, 1, &data_ov006_0225b788, &sFieldSceneObjectList, 9, 0x93};

u32 data_ov006_0225b790[3] = {0xbc, 0xd0, 0xd4};

SceneSpawnList data_ov006_0225b780 = {3, 0, data_ov006_0225b7b4};

SceneSpawnGroup data_ov006_0225b7b4[3] = {
    {2, FIELD_SCENE_PROFILE_COUNT, 0, sFieldSceneProfiles},
    {2, 3, 0, data_ov006_0225b790},
    {1, 0, 0, 0},
};

SceneMapInfo data_ov006_0225b788 = {data_ov006_0225b7cc, 6, 6};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov006_0225b760) {
    HOST_OVERLAY_VAR(data_ov006_0225b7cc),
    HOST_OVERLAY_VAR(data_ov006_0225b79c),
    HOST_OVERLAY_VAR(data_ov006_0225b790),
    HOST_OVERLAY_VAR(data_ov006_0225b780),
    HOST_OVERLAY_VAR(data_ov006_0225b7b4),
    HOST_OVERLAY_VAR(data_ov006_0225b788),
    HOST_OVERLAY_VARS_END
};
