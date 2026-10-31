#ifndef PROTO_PROTO_OV082_UNK_OV082_022713C0_H
#define PROTO_PROTO_OV082_UNK_OV082_022713C0_H


#include "types.h"
struct SpNpcTortimerBugOffActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerBugOffActEntry SpNpcTortimerBugOffActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimerBugOff;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerBugOffTexturePath
extern u8 sSpNpcTortimerBugOffTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerBugOffModelPath
extern u8 sSpNpcTortimerBugOffModelPath[];
#endif
#ifndef PROTO_LOCAL_SpNpcTortimerBugOff_IsInsect
BOOL SpNpcTortimerBugOff_IsInsect(u16 *p, s32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcTortimerBugOff_Create
SpNpcTortimerBugOff *SpNpcTortimerBugOff_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerBugOffProfile
extern ActorProfile sSpNpcTortimerBugOffProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerBugOffActTable
extern SpNpcTortimerBugOffActEntry sSpNpcTortimerBugOffActTable[3];
#endif
#endif

#endif
