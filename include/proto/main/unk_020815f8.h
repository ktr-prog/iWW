#ifndef PROTO_PROTO_MAIN_UNK_020815F8_H
#define PROTO_PROTO_MAIN_UNK_020815F8_H


#include "types.h"
struct NpcActorRegistry;
#ifndef __cplusplus
typedef struct NpcActorRegistry NpcActorRegistry;
#endif
#ifdef __cplusplus
#include "actor/NpcActor.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NpcRegistry_Clear
void NpcRegistry_Clear();
#endif
#ifndef PROTO_LOCAL_NpcRegistry_GetSlotCount
s32 NpcRegistry_GetSlotCount();
#endif
#ifndef PROTO_LOCAL_NpcRegistry_RemoveVillager
s32 NpcRegistry_RemoveVillager(u16 *handle);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_RemoveSpNpc
s32 NpcRegistry_RemoveSpNpc(u16 *handle);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_NpcRegistry_GetVillager
NpcActor *NpcRegistry_GetVillager(s32 i);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_GetBySlot
NpcActor *NpcRegistry_GetBySlot(s32 n);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindVillager
NpcActor *NpcRegistry_FindVillager(u32 idx);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindSpNpc
NpcActor *NpcRegistry_FindSpNpc(u32 idx);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindByKind
NpcActor *NpcRegistry_FindByKind(s32 kind, u32 x);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindByHandle
NpcActor *NpcRegistry_FindByHandle(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindVillagerByHandle
NpcActor *NpcRegistry_FindVillagerByHandle(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindSpNpcByHandle
NpcActor *NpcRegistry_FindSpNpcByHandle(u16 *p);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_FindAt
NpcActor *NpcRegistry_FindAt(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_PickRandomVillager
NpcActor *NpcRegistry_PickRandomVillager(s32 *idx);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_AddVillager
s32 NpcRegistry_AddVillager(NpcActor *actor, u16 *handle);
#endif
#ifndef PROTO_LOCAL_NpcRegistry_AddSpNpc
s32 NpcRegistry_AddSpNpc(NpcActor *actor, u16 *handle);
#endif
}
#ifndef PROTO_LOCAL_gNpcActorRegistry
extern NpcActorRegistry gNpcActorRegistry;
#endif
#endif

#endif
