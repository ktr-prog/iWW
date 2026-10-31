#ifndef PROTO_PROTO_MAIN_UNK_0209C9F8_H
#define PROTO_PROTO_MAIN_UNK_0209C9F8_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "sys/ProcBase.h"
class GameRoot;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_GameRoot_Boot
void GameRoot_Boot();
#endif
#ifndef PROTO_LOCAL_SoftReset_ClearSystems
void SoftReset_ClearSystems();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_GameRoot_Create
GameRoot *GameRoot_Create();
#endif
}
#ifndef PROTO_LOCAL_gGameRoot
extern GameProc *gGameRoot;
#endif
#ifndef PROTO_LOCAL_sGameRootProfile
extern ProcProfile sGameRootProfile;
#endif
#endif

#endif
