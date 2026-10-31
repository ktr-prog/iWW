#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020F30FC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020F30FC_H


#include "types.h"
#ifdef __cplusplus
#include "snd/SndPosNode.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Snd_InstallListenerCallbacks
void Snd_InstallListenerCallbacks(void);
#endif
#ifndef PROTO_LOCAL_Snd_ClearListenerCallbacks
void Snd_ClearListenerCallbacks(void);
#endif
#ifndef PROTO_LOCAL_Snd_CalcSeVolume
s32 Snd_CalcSeVolume(s32 a, s32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_gSndPosList
extern SndPosList *gSndPosList;
#endif
#endif

#endif
