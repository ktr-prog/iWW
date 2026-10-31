#include "types.h"
#include "game/SceneInfo.h"


extern u32 sRoomCommonProfiles[];

extern SceneInfo data_ov007_0225b7a8;
extern SceneSpawnList data_ov007_0225b790;
extern SceneSpawnGroup data_ov007_0225b788[1];
extern u32 data_ov007_0225b798[4];
extern SceneMapInfo data_ov007_0225b780;

SceneInfo data_ov007_0225b7a8 = {&data_ov007_0225b790, 1, &data_ov007_0225b780, 0, -1, -1};

SceneSpawnList data_ov007_0225b790 = {1, 0, data_ov007_0225b788};

SceneSpawnGroup data_ov007_0225b788[1] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
};

u32 data_ov007_0225b798[4] = {0x1000, 0x1000, 0x1000, 0x1000};

SceneMapInfo data_ov007_0225b780 = {data_ov007_0225b798, 2, 2};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov007_0225b760) {
    HOST_OVERLAY_VAR(data_ov007_0225b7a8),
    HOST_OVERLAY_VAR(data_ov007_0225b790),
    HOST_OVERLAY_VAR(data_ov007_0225b788),
    HOST_OVERLAY_VAR(data_ov007_0225b798),
    HOST_OVERLAY_VAR(data_ov007_0225b780),
    HOST_OVERLAY_VARS_END
};
