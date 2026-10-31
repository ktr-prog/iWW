#ifndef PROTO_PROTO_MAIN_UNK_0205D1F8_H
#define PROTO_PROTO_MAIN_UNK_0205D1F8_H


#include "types.h"
struct CharaFaceAnimWorkPool;
#ifndef __cplusplus
typedef struct CharaFaceAnimWorkPool CharaFaceAnimWorkPool;
#endif
#ifdef __cplusplus
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CharaFaceAnimWorkPool_Destroy
void CharaFaceAnimWorkPool_Destroy();
#endif
#ifndef PROTO_LOCAL_CharaFaceAnimWork_GetHeapSize
u32 CharaFaceAnimWork_GetHeapSize();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CharaFaceAnimWorkPool_Create
void CharaFaceAnimWorkPool_Create(Heap *parent);
#endif
}
#ifndef PROTO_LOCAL_sCharaFaceAnimWorkPool
extern CharaFaceAnimWorkPool sCharaFaceAnimWorkPool;
#endif
#endif

#endif
