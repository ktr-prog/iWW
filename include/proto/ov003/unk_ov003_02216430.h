#ifndef PROTO_PROTO_OV003_UNK_OV003_02216430_H
#define PROTO_PROTO_OV003_UNK_OV003_02216430_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/NNSG3dRS.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownHall_Create
void *TownHall_Create();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTownHallProfile
extern ActorProfile sTownHallProfile;
#endif
#ifndef PROTO_LOCAL_TownHall_NodeCallback
void TownHall_NodeCallback(NNSG3dRS *a);
#endif
}
#endif

#endif
