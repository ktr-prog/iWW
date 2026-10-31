#ifndef PROTO_PROTO_MAIN_UNK_0208F0B0_H
#define PROTO_PROTO_MAIN_UNK_0208F0B0_H


#include "types.h"
#ifdef __cplusplus
class TownExchangeRemoteRecords;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownExchange_InitNop
void TownExchange_InitNop();
#endif
#ifndef PROTO_LOCAL_TownExchange_Clear
void TownExchange_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_TownExchange_GetLetter
void *TownExchange_GetLetter(void *p);
#endif
#ifndef PROTO_LOCAL_TownExchange_GetRemote
void *TownExchange_GetRemote(s32 i);
#endif
#ifndef PROTO_LOCAL_TownExchange_GetForAid
void *TownExchange_GetForAid(s32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sTownExchangeRemoteRecords
extern TownExchangeRemoteRecords sTownExchangeRemoteRecords;
#endif
#endif

#endif
