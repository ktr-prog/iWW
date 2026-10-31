#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_021093F4_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_021093F4_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNS_SndInit
void NNS_SndInit(void);
#endif
#ifndef PROTO_LOCAL_NNS_SndMain
void NNS_SndMain(void);
#endif
#ifndef PROTO_LOCAL_NNS_SndSetMasterVolume
void NNS_SndSetMasterVolume(u32 a);
#endif
#ifndef PROTO_LOCAL_NNS_SndUpdateDriverInfo
BOOL NNS_SndUpdateDriverInfo(void);
#endif
#ifndef PROTO_LOCAL_NNSi_SndReadDriverPlayerInfo
u32 NNSi_SndReadDriverPlayerInfo(u32 a, void *b);
#endif
#ifndef PROTO_LOCAL_NNSi_SndReadDriverTrackInfo
u32 NNSi_SndReadDriverTrackInfo(u32 a, u32 b, void *c);
#endif
#ifndef PROTO_LOCAL_BeginSleep
u32 BeginSleep(void);
#endif
#ifndef PROTO_LOCAL_EndSleep
void EndSleep(void);
#endif
#ifdef __cplusplus
}
#endif

#endif
