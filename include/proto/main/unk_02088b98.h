#ifndef PROTO_PROTO_MAIN_UNK_02088B98_H
#define PROTO_PROTO_MAIN_UNK_02088B98_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorCollider.h"
class BugNetTarget;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ActorCollider_InitList
void ActorCollider_InitList(void);
#endif
#ifndef PROTO_LOCAL_ActorCollider_ClearList
void ActorCollider_ClearList(void);
#endif
#ifndef PROTO_LOCAL_ActorCollider_ResolveAll
void ActorCollider_ResolveAll();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_data_021ce63c
extern BugNetTarget *data_021ce63c;
#endif
#ifndef PROTO_LOCAL_gActorColliderList
extern ActorCollider *gActorColliderList;
#endif
#endif

#endif
