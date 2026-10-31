#include "types.h"
#include "game/SceneInfo.h"


extern u32 sRoomCommonProfiles[];

extern u32 data_ov008_0225b780[1];
extern SceneSpawnList data_ov008_0225b78c;
extern SceneMapInfo data_ov008_0225b784;
extern SceneInfo data_ov008_0225b79c;
extern SceneSpawnGroup data_ov008_0225b794[1];

u32 data_ov008_0225b780[1] = {0x1000};

SceneSpawnList data_ov008_0225b78c = {1, 0, data_ov008_0225b794};

SceneMapInfo data_ov008_0225b784 = {data_ov008_0225b780, 1, 1};

SceneInfo data_ov008_0225b79c = {&data_ov008_0225b78c, 1, &data_ov008_0225b784, 0, -1, -1};

SceneSpawnGroup data_ov008_0225b794[1] = {
    {2, ROOM_COMMON_PROFILE_COUNT, 0, sRoomCommonProfiles},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov008_0225b760) {
    HOST_OVERLAY_VAR(data_ov008_0225b780),
    HOST_OVERLAY_VAR(data_ov008_0225b78c),
    HOST_OVERLAY_VAR(data_ov008_0225b784),
    HOST_OVERLAY_VAR(data_ov008_0225b79c),
    HOST_OVERLAY_VAR(data_ov008_0225b794),
    HOST_OVERLAY_VARS_END
};
