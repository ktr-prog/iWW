#ifndef PROTO_PROTO_OV003_UNK_OV003_0222EE6C_H
#define PROTO_PROTO_OV003_UNK_OV003_0222EE6C_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "gfx/Camera.h"
#include "gfx/DebugColor.h"
class SnowballSpawner;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSnowballSpawnerProfile
extern ProcProfile sSnowballSpawnerProfile;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b748
extern DebugColor data_ov003_0225b748;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b744
extern DebugColor data_ov003_0225b744;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b740
extern DebugColor data_ov003_0225b740;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b73c
extern DebugColor data_ov003_0225b73c;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b738
extern DebugColor data_ov003_0225b738;
#endif
#ifndef PROTO_LOCAL_data_ov003_0225b74c
extern DebugColor data_ov003_0225b74c;
#endif
#ifndef PROTO_LOCAL_FieldCamera_UpdateFocusZoom
void FieldCamera_UpdateFocusZoom(Camera *cam);
#endif
#ifndef PROTO_LOCAL_SnowballSpawner_Create
SnowballSpawner *SnowballSpawner_Create();
#endif
}
#endif

#endif
