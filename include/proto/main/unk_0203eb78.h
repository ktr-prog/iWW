#ifndef PROTO_PROTO_MAIN_UNK_0203EB78_H
#define PROTO_PROTO_MAIN_UNK_0203EB78_H


#include "types.h"
#ifdef __cplusplus
#include "talk/TalkRequestEntry.h"
#include "talk/TalkRequestList.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_AxMail_Construct
void *AxMail_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_AxMail_Destruct
void *AxMail_Destruct(void *p);
#endif
#ifndef PROTO_LOCAL_AxMail_GetDigest
u8 *AxMail_GetDigest(u8 *p);
#endif
#ifndef PROTO_LOCAL_AxMail_Deliver
BOOL AxMail_Deliver(u8 *p);
#endif
#ifndef PROTO_LOCAL_AxBbsNotice_Construct
void AxBbsNotice_Construct(void);
#endif
#ifndef PROTO_LOCAL_AxBbsNotice_Destruct
void AxBbsNotice_Destruct(void);
#endif
#ifndef PROTO_LOCAL_AxBbsNotice_GetDigest
u8 *AxBbsNotice_GetDigest(u8 *p);
#endif
#ifndef PROTO_LOCAL_AxBbsNotice_Post
BOOL AxBbsNotice_Post(u8 *p);
#endif
#ifndef PROTO_LOCAL_TalkRequestPool_Reset
void TalkRequestPool_Reset(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TalkRequestEntry_Free
void TalkRequestEntry_Free(TalkRequestEntry *e);
#endif
#ifndef PROTO_LOCAL_TalkRequestList_FreeAll
void TalkRequestList_FreeAll(TalkRequestList *l);
#endif
#ifndef PROTO_LOCAL_TalkRequestPool_Alloc
TalkRequestEntry *TalkRequestPool_Alloc(void);
#endif
}
#ifndef PROTO_LOCAL_sTalkRequestPool
extern TalkRequestEntry sTalkRequestPool[15];
#endif
#endif

#endif
