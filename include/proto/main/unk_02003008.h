#ifndef PROTO_PROTO_MAIN_UNK_02003008_H
#define PROTO_PROTO_MAIN_UNK_02003008_H


#include "types.h"
#ifdef __cplusplus
#include "npc/VillagerId.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Villager_PersonalityToGender
u32 Villager_PersonalityToGender(u32 t);
#endif
#ifndef PROTO_LOCAL_Villager_MakePersonalityFileName
void Villager_MakePersonalityFileName(void *buf, u32 size, const char *key, u32 idx);
#endif
#ifndef PROTO_LOCAL_Villager_PersonalityToVoiceType
u32 Villager_PersonalityToVoiceType(u32 t);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_VillagerId_GetPersonality
u32 VillagerId_GetPersonality(VillagerId *o);
#endif
}
#ifndef PROTO_LOCAL_sPersonalityPrefixSnooty
extern char sPersonalityPrefixSnooty[];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixJock
extern char sPersonalityPrefixJock[];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixNormal
extern char sPersonalityPrefixNormal[];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixPeppy
extern char sPersonalityPrefixPeppy[];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixCranky
extern char sPersonalityPrefixCranky[];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixes
extern char *sPersonalityPrefixes[6];
#endif
#ifndef PROTO_LOCAL_sPersonalityPrefixLazy
extern char sPersonalityPrefixLazy[];
#endif
#endif

#endif
