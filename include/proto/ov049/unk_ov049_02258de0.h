#ifndef PROTO_PROTO_OV049_UNK_OV049_02258DE0_H
#define PROTO_PROTO_OV049_UNK_OV049_02258DE0_H


#include "types.h"
struct SpNpcMabelActEntry;
struct SpNpcMabelChoiceMenu;
struct SpNpcMabelTalkScript;
#ifndef __cplusplus
typedef struct SpNpcMabelActEntry SpNpcMabelActEntry;
typedef struct SpNpcMabelChoiceMenu SpNpcMabelChoiceMenu;
typedef struct SpNpcMabelTalkScript SpNpcMabelTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcMabel;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov049_0225ba48
extern u8 data_ov049_0225ba48[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelSequence4Key
extern char sSpNpcMabelSequence4Key[];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelDramaKey
extern char sSpNpcMabelDramaKey[];
#endif
#ifndef PROTO_LOCAL_data_ov049_0225ba44
extern u8 data_ov049_0225ba44[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelMsgKeys
extern char *sSpNpcMabelMsgKeys[3];
#endif
#ifndef PROTO_LOCAL_data_ov049_0225ba4c
extern u8 data_ov049_0225ba4c[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelModelPath
extern char sSpNpcMabelModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelTexturePath
extern char sSpNpcMabelTexturePath[];
#endif
#ifndef PROTO_LOCAL_data_ov049_0225ba40
extern u8 data_ov049_0225ba40[4];
#endif
#ifndef PROTO_LOCAL_SpNpcMabel_IsDeliveryItem
BOOL SpNpcMabel_IsDeliveryItem(u16 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelKey
extern char sSpNpcMabelKey[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcMabel_Create
SpNpcMabel *SpNpcMabel_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelItemChoiceMenus
extern SpNpcMabelChoiceMenu sSpNpcMabelItemChoiceMenus[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelTalkScripts
extern SpNpcMabelTalkScript sSpNpcMabelTalkScripts[10];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelActTable
extern SpNpcMabelActEntry sSpNpcMabelActTable[16];
#endif
#ifndef PROTO_LOCAL_sSpNpcMabelProfile
extern ActorProfile sSpNpcMabelProfile;
#endif
}
#endif

#endif
