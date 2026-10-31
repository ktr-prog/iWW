#ifndef PROTO_PROTO_OV102_UNK_OV102_02294C40_H
#define PROTO_PROTO_OV102_UNK_OV102_02294C40_H


#include "types.h"
#include "sys/ProcProfile.h"
struct Unk_ov102_02297580_Ent;
#ifndef __cplusplus
typedef struct Unk_ov102_02297580_Ent Unk_ov102_02297580_Ent;
#endif
#ifdef __cplusplus
class ChestMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ChestMenu_SetupBgLayers
void ChestMenu_SetupBgLayers();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ChestMenu_Create
ChestMenu *ChestMenu_Create();
#endif
#ifndef PROTO_LOCAL_sChestMenuProfile
extern ProcProfile sChestMenuProfile;
#endif
#ifndef PROTO_LOCAL_sChestPageTabSprites
extern Unk_ov102_02297580_Ent sChestPageTabSprites[18];
#endif
}
#endif

#endif
