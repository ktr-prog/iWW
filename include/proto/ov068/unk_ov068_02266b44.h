#ifndef PROTO_PROTO_OV068_UNK_OV068_02266B44_H
#define PROTO_PROTO_OV068_UNK_OV068_02266B44_H


#include "types.h"
struct SpNpcNookIntroActEntry;
struct SpNpcNookIntroTalkScript;
#ifndef __cplusplus
typedef struct SpNpcNookIntroActEntry SpNpcNookIntroActEntry;
typedef struct SpNpcNookIntroTalkScript SpNpcNookIntroTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcNookIntro;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sNookTexRcd
extern char sNookTexRcd[0x1c];
#endif
#ifndef PROTO_LOCAL_sNookModelRcn
extern char sNookModelRcn[0x18];
#endif
#ifndef PROTO_LOCAL_sNookModelRcc
extern char sNookModelRcc[0x18];
#endif
#ifndef PROTO_LOCAL_sNookModelRcd
extern char sNookModelRcd[0x18];
#endif
#ifndef PROTO_LOCAL_sNookTexRcn
extern char sNookTexRcn[0x1c];
#endif
#ifndef PROTO_LOCAL_sNookTexRcc
extern char sNookTexRcc[0x1c];
#endif
#ifndef PROTO_LOCAL_sNookIntroMsgFile
extern char sNookIntroMsgFile[0x14];
#endif
#ifndef PROTO_LOCAL_sNookModelRcs
extern char sNookModelRcs[0x18];
#endif
#ifndef PROTO_LOCAL_sNookIntroMsgFilePtr
extern void *sNookIntroMsgFilePtr;
#endif
#ifndef PROTO_LOCAL_sNookTexRcs
extern char sNookTexRcs[0x1c];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sNookIntroTalkScripts
extern SpNpcNookIntroTalkScript sNookIntroTalkScripts[2];
#endif
#ifndef PROTO_LOCAL_SpNpcNookIntro_Create
SpNpcNookIntro *SpNpcNookIntro_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcNookIntroActTable
extern SpNpcNookIntroActEntry sSpNpcNookIntroActTable[6];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookIntroProfile
extern ActorProfile sSpNpcNookIntroProfile;
#endif
}
#endif

#endif
