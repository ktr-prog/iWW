#ifndef PROTO_PROTO_MAIN_UNK_020C0324_H
#define PROTO_PROTO_MAIN_UNK_020C0324_H


#include "types.h"
struct SpNpcKatieActEntry;
#ifndef __cplusplus
typedef struct SpNpcKatieActEntry SpNpcKatieActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "npc/SpNpcKatie.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcKatie_IsIdle
BOOL SpNpcKatie_IsIdle();
#endif
#ifndef PROTO_LOCAL_SpNpcKatie_ResetAct
void SpNpcKatie_ResetAct();
#endif
#ifndef PROTO_LOCAL_SpNpcKatie_ChangeAct05
void SpNpcKatie_ChangeAct05();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcKatie_Create
SpNpcKatie *SpNpcKatie_Create(void);
#endif
}
#ifndef PROTO_LOCAL_data_021f458c
extern DebugColor data_021f458c;
#endif
#ifndef PROTO_LOCAL_data_021f4580
extern DebugColor data_021f4580;
#endif
#ifndef PROTO_LOCAL_data_021f4584
extern DebugColor data_021f4584;
#endif
#ifndef PROTO_LOCAL_data_021f457c
extern DebugColor data_021f457c;
#endif
#ifndef PROTO_LOCAL_data_021f4590
extern DebugColor data_021f4590;
#endif
#ifndef PROTO_LOCAL_data_021f4588
extern DebugColor data_021f4588;
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieActTable
extern SpNpcKatieActEntry sSpNpcKatieActTable[9];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieInstance
extern SpNpcKatie *sSpNpcKatieInstance;
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieKey
extern char sSpNpcKatieKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieMsgKey
extern char *sSpNpcKatieMsgKey;
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieTexPath
extern char sSpNpcKatieTexPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieModelPath
extern char sSpNpcKatieModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatieProfile
extern ActorProfile sSpNpcKatieProfile;
#endif
#endif

#endif
