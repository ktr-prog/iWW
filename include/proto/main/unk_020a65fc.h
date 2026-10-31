#ifndef PROTO_PROTO_MAIN_UNK_020A65FC_H
#define PROTO_PROTO_MAIN_UNK_020A65FC_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NetStatusMsgBase_Unpack
void NetStatusMsgBase_Unpack(u8 *p, s32 *a, u8 *b, u8 *c, u8 *d, s32 *e);
#endif
#ifndef PROTO_LOCAL_NetStatusUpdateMsg_Init
void *NetStatusUpdateMsg_Init(void *p);
#endif
#ifndef PROTO_LOCAL_NetStatusUpdateMsg_Fini
void *NetStatusUpdateMsg_Fini(void *p);
#endif
#ifndef PROTO_LOCAL_NetStatusUpdateMsg_Pack
void NetStatusUpdateMsg_Pack(u8 *p, s32 b, s32 c, s32 d, s32 e);
#endif
#ifndef PROTO_LOCAL_NetStatusUpdateMsg_Unpack
void NetStatusUpdateMsg_Unpack(u8 *p, u8 *b, u8 *c, u8 *d, s32 *e);
#endif
#ifndef PROTO_LOCAL_NetStatusMsg_Init
void *NetStatusMsg_Init(void *p);
#endif
#ifndef PROTO_LOCAL_NetStatusMsg_Fini
void *NetStatusMsg_Fini(void *p);
#endif
#ifndef PROTO_LOCAL_NetStatusMsg_Pack
void NetStatusMsg_Pack(u8 *p, s32 a, s32 b, s32 c, u8 d, s32 e);
#endif
#ifndef PROTO_LOCAL_NetStatusMsg_Unpack
void NetStatusMsg_Unpack(u8 *p, s32 *a, u8 *b, u8 *c, u8 *d, s32 *e);
#endif
#ifndef PROTO_LOCAL_NetSyncMsg_Init
void NetSyncMsg_Init();
#endif
#ifndef PROTO_LOCAL_NetSyncMsg_Fini
void NetSyncMsg_Fini();
#endif
#ifndef PROTO_LOCAL_NetSyncMsg_Pack
void NetSyncMsg_Pack(u8 *p, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_NetSyncMsg_Unpack
void NetSyncMsg_Unpack(u8 *p, s32 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_NetArea_WriteStateAPart0
void NetArea_WriteStateAPart0();
#endif
#ifndef PROTO_LOCAL_NetArea_WriteStateANpcTalk
void NetArea_WriteStateANpcTalk();
#endif
#ifndef PROTO_LOCAL_NetArea_BuildStateA
void NetArea_BuildStateA();
#endif
#ifdef __cplusplus
}
#endif

#endif
