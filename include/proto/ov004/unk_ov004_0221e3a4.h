#ifndef PROTO_PROTO_OV004_UNK_OV004_0221E3A4_H
#define PROTO_PROTO_OV004_UNK_OV004_0221E3A4_H


#include "types.h"
struct SpNpcTortimer2ActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimer2ActEntry SpNpcTortimer2ActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimer2;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcTortimer2_IsIdle
BOOL SpNpcTortimer2_IsIdle();
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimer2ModelPath
extern u8 sSpNpcTortimer2ModelPath[23];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimer2TexturePath
extern u8 sSpNpcTortimer2TexturePath[27];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcTortimer2_Create
SpNpcTortimer2 *SpNpcTortimer2_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimer2Profile
extern ActorProfile sSpNpcTortimer2Profile;
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimer2ActTable
extern SpNpcTortimer2ActEntry sSpNpcTortimer2ActTable[2];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimer2
extern SpNpcTortimer2 *volatile sSpNpcTortimer2;
#endif
}
#endif

#endif
