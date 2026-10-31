#ifndef PROTO_PROTO_MAIN_UNK_0209C08C_H
#define PROTO_PROTO_MAIN_UNK_0209C08C_H


#include "types.h"
#ifdef __cplusplus
class SavedFadeIn;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ModelSlotHandle_Init
void ModelSlotHandle_Init(u16 *p);
#endif
#ifndef PROTO_LOCAL_ModelSlotHandle_Destroy
void ModelSlotHandle_Destroy(u16 *p);
#endif
#ifndef PROTO_LOCAL_Scene_SaveFadeIn
void Scene_SaveFadeIn(u32 v);
#endif
#ifndef PROTO_LOCAL_Scene_GetSavedFadeIn
u32 Scene_GetSavedFadeIn();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sSavedFadeIn
extern SavedFadeIn sSavedFadeIn;
#endif
#endif

#endif
