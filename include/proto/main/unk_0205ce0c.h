#ifndef PROTO_PROTO_MAIN_UNK_0205CE0C_H
#define PROTO_PROTO_MAIN_UNK_0205CE0C_H


#include "types.h"
struct CharaFaceAnimPool;
#ifndef __cplusplus
typedef struct CharaFaceAnimPool CharaFaceAnimPool;
#endif
#ifdef __cplusplus
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CharaFaceAnimPool_Destroy
void CharaFaceAnimPool_Destroy();
#endif
#ifndef PROTO_LOCAL_CharaFaceAnim_GetPath
char *CharaFaceAnim_GetPath(u32 x);
#endif
#ifndef PROTO_LOCAL_CharaFaceAnim_GetAnimSize
u32 CharaFaceAnim_GetAnimSize();
#endif
#ifndef PROTO_LOCAL_CharaFaceAnim_GetSlotSize
u32 CharaFaceAnim_GetSlotSize();
#endif
#ifndef PROTO_LOCAL_CharaFaceAnim_GetKind
u32 CharaFaceAnim_GetKind(u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CharaFaceAnimPool_Create
void CharaFaceAnimPool_Create(Heap *parent);
#endif
}
#ifndef PROTO_LOCAL_sCharaFaceAnimPathBuf
extern char sCharaFaceAnimPathBuf[0x14];
#endif
#ifndef PROTO_LOCAL_sCharaFaceAnimPool
extern CharaFaceAnimPool sCharaFaceAnimPool;
#endif
#endif

#endif
