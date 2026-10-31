#ifndef PROTO_PROTO_MAIN_UNK_020821C4_H
#define PROTO_PROTO_MAIN_UNK_020821C4_H


#include "types.h"
#ifdef __cplusplus
#include "npc/NpcBodyAnimPool.h"
#include "npc/NpcResPools.h"
#include "npc/VillagerAnimHeapRefPool.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_NpcBodyAnimPool_Get
NpcBodyAnimPool *NpcBodyAnimPool_Get();
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapRefPool_Get
VillagerAnimHeapRefPool *VillagerAnimHeapRefPool_Get();
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapRefPool_Get
SpNpcAnimHeapRefPool *SpNpcAnimHeapRefPool_Get();
#endif
#ifndef PROTO_LOCAL_NpcClothTexPool_Get
NpcClothTexPool *NpcClothTexPool_Get();
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRefPool_Get
NpcTexPatBufRefPool *NpcTexPatBufRefPool_Get();
#endif
#ifndef PROTO_LOCAL_NpcFaceAnimPool_Get
NpcFaceAnimPool *NpcFaceAnimPool_Get();
#endif
#ifndef PROTO_LOCAL_NpcTexPatHeapPool_Get
NpcTexPatHeapPool *NpcTexPatHeapPool_Get();
#endif
#ifndef PROTO_LOCAL_NpcHeldItemModelPool_Get
NpcHeldItemModelPool *NpcHeldItemModelPool_Get();
#endif
}
#ifndef PROTO_LOCAL_sNpcBodyAnimPool
extern NpcBodyAnimPool sNpcBodyAnimPool;
#endif
#ifndef PROTO_LOCAL_sVillagerAnimHeapRefPool
extern VillagerAnimHeapRefPool sVillagerAnimHeapRefPool;
#endif
#ifndef PROTO_LOCAL_sSpNpcAnimHeapRefPool
extern SpNpcAnimHeapRefPool sSpNpcAnimHeapRefPool;
#endif
#ifndef PROTO_LOCAL_sNpcClothTexPool
extern NpcClothTexPool sNpcClothTexPool;
#endif
#ifndef PROTO_LOCAL_sNpcTexPatBufRefPool
extern NpcTexPatBufRefPool sNpcTexPatBufRefPool;
#endif
#ifndef PROTO_LOCAL_sNpcFaceAnimPool
extern NpcFaceAnimPool sNpcFaceAnimPool;
#endif
#ifndef PROTO_LOCAL_sNpcTexPatHeapPool
extern NpcTexPatHeapPool sNpcTexPatHeapPool;
#endif
#ifndef PROTO_LOCAL_sNpcHeldItemModelPool
extern NpcHeldItemModelPool sNpcHeldItemModelPool;
#endif
#endif

#endif
