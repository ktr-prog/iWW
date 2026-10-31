#ifndef PROTO_PROTO_MAIN_UNK_020C1738_H
#define PROTO_PROTO_MAIN_UNK_020C1738_H


#include "types.h"
struct SpNpcKaitlinActEntry;
#ifndef __cplusplus
typedef struct SpNpcKaitlinActEntry SpNpcKaitlinActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "game/FxVec3.h"
#include "gfx/DebugColor.h"
class SpNpcKaitlin;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcKaitlin_Create
SpNpcKaitlin *SpNpcKaitlin_Create();
#endif
}
#ifndef PROTO_LOCAL_SpNpcKaitlin_ChangeAct04
void SpNpcKaitlin_ChangeAct04();
#endif
#ifndef PROTO_LOCAL_SpNpcKaitlin_ChangeAct06
void SpNpcKaitlin_ChangeAct06();
#endif
#ifndef PROTO_LOCAL_data_021f4630
extern DebugColor data_021f4630;
#endif
#ifndef PROTO_LOCAL_data_021f463c
extern DebugColor data_021f463c;
#endif
#ifndef PROTO_LOCAL_data_021f4634
extern DebugColor data_021f4634;
#endif
#ifndef PROTO_LOCAL_data_021f4624
extern DebugColor data_021f4624;
#endif
#ifndef PROTO_LOCAL_data_021f4628
extern DebugColor data_021f4628;
#endif
#ifndef PROTO_LOCAL_data_021f462c
extern DebugColor data_021f462c;
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinActTable
extern SpNpcKaitlinActEntry sSpNpcKaitlinActTable[10];
#endif
#ifndef PROTO_LOCAL_data_021f4658
extern FxVec3 data_021f4658[2];
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinInstance
extern SpNpcKaitlin *sSpNpcKaitlinInstance;
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinKey
extern char sSpNpcKaitlinKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinModelPath
extern char sSpNpcKaitlinModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinTexPath
extern char sSpNpcKaitlinTexPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKaitlinProfile
extern ActorProfile sSpNpcKaitlinProfile;
#endif
#endif

#endif
