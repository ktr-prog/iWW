#ifndef PROTO_PROTO_MAIN_UNK_02041868_H
#define PROTO_PROTO_MAIN_UNK_02041868_H


#include "types.h"
#include "game/Unk_02042104_Date.h"
struct TownJunkInsectFlags;
#ifndef __cplusplus
typedef struct TownJunkInsectFlags TownJunkInsectFlags;
#endif
#ifdef __cplusplus
#include "town/TownUpdateThread.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TownBbs_UpdateDaily
void TownBbs_UpdateDaily();
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Main
void TownUpdateThread_Main(void *arg);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Create
void TownUpdateThread_Create();
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Request
void TownUpdateThread_Request(u8 *a, u8 *b, u32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Start
s32 TownUpdateThread_Start();
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_PollDone
BOOL TownUpdateThread_PollDone();
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Destroy
void TownUpdateThread_Destroy();
#endif
#ifndef PROTO_LOCAL_TownJunkInsects_Refresh
void TownJunkInsects_Refresh();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TownBbs_GetDaysToPost
s32 TownBbs_GetDaysToPost(void *o, u8 *a, Unk_02042104_Date *d);
#endif
#ifndef PROTO_LOCAL_TownBbs_CatchUpPelicanDate
void TownBbs_CatchUpPelicanDate(void *o, u8 *base, Unk_02042104_Date *d);
#endif
#ifndef PROTO_LOCAL_TownBbs_PostEventsForDay
void TownBbs_PostEventsForDay(void *o, u8 *base, Unk_02042104_Date *d);
#endif
#ifndef PROTO_LOCAL_TownBbs_PostDays
void TownBbs_PostDays(void *o, u8 *base, s32 cnt, Unk_02042104_Date *d, s32 flag0);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Init
void TownUpdateThread_Init(TownUpdateThread *p);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_SetArgs
void TownUpdateThread_SetArgs(TownUpdateThread *p, u8 *a, u8 *b, u32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_StartCtx
s32 TownUpdateThread_StartCtx(TownUpdateThread *p);
#endif
#ifndef PROTO_LOCAL_TownUpdateThread_Kill
void TownUpdateThread_Kill(TownUpdateThread *p);
#endif
#ifndef PROTO_LOCAL_TownJunkInsects_InitFromEval
void TownJunkInsects_InitFromEval(TownJunkInsectFlags *p);
#endif
#ifndef PROTO_LOCAL_TownJunkInsects_Apply
void TownJunkInsects_Apply(TownJunkInsectFlags *p);
#endif
}
#ifndef PROTO_LOCAL_sTownBbsUpdateCtx
extern u8 sTownBbsUpdateCtx[4];
#endif
#ifndef PROTO_LOCAL_gTownJunkInsectFlags
extern TownJunkInsectFlags gTownJunkInsectFlags;
#endif
#endif

#endif
