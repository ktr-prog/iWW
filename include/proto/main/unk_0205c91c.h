#ifndef PROTO_PROTO_MAIN_UNK_0205C91C_H
#define PROTO_PROTO_MAIN_UNK_0205C91C_H


#include "types.h"
struct CharaClothTexPool;
#ifndef __cplusplus
typedef struct CharaClothTexPool CharaClothTexPool;
#endif
#ifdef __cplusplus
#include "actor/CharaClothTexRef.h"
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CharaClothTexPool_Destroy
void CharaClothTexPool_Destroy();
#endif
#ifndef PROTO_LOCAL_CharaClothTexRef_LoadPattern
void CharaClothTexRef_LoadPattern(u8 *p, void *q);
#endif
#ifndef PROTO_LOCAL_CharaClothTexRef_CopyFromSlot
void CharaClothTexRef_CopyFromSlot(void *pp, s32 x);
#endif
#ifndef PROTO_LOCAL_CharaClothTexRef_GetBuffer
void *CharaClothTexRef_GetBuffer(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CharaClothTexPool_Create
void CharaClothTexPool_Create(Heap *parent);
#endif
#ifndef PROTO_LOCAL_CharaClothTexPool_GetOwnRef
CharaClothTexRef *CharaClothTexPool_GetOwnRef();
#endif
#ifndef PROTO_LOCAL_CharaClothTexPool_GetItem
void CharaClothTexPool_GetItem(u16 *out, CharaClothTexPool *t, u32 idx);
#endif
}
#ifndef PROTO_LOCAL_sCharaClothTexPool
extern CharaClothTexPool sCharaClothTexPool;
#endif
#endif

#endif
