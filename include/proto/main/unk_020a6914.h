#ifndef PROTO_PROTO_MAIN_UNK_020A6914_H
#define PROTO_PROTO_MAIN_UNK_020A6914_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NetSceneMsg_Init
void NetSceneMsg_Init(void);
#endif
#ifndef PROTO_LOCAL_NetSceneMsg_Fini
void NetSceneMsg_Fini(void);
#endif
#ifndef PROTO_LOCAL_NetSceneMsg_Set
void NetSceneMsg_Set(u8 *a, u8 b);
#endif
#ifndef PROTO_LOCAL_NetSceneMsg_Get
void NetSceneMsg_Get(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_NetStatusMsgBase_Init
void NetStatusMsgBase_Init(void);
#endif
#ifndef PROTO_LOCAL_NetStatusMsgBase_Fini
void NetStatusMsgBase_Fini(void);
#endif
#ifndef PROTO_LOCAL_NetStatusMsgBase_Pack
void NetStatusMsgBase_Pack(u8 *p, int a, int b, int c, u8 d, int e);
#endif
#ifdef __cplusplus
}
#endif

#endif
