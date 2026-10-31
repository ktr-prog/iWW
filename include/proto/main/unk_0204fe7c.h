#ifndef PROTO_PROTO_MAIN_UNK_0204FE7C_H
#define PROTO_PROTO_MAIN_UNK_0204FE7C_H


#include "types.h"
#ifdef __cplusplus
#include "save/Backup.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sFishDisplayNetHandlers
extern void (*sFishDisplayNetHandlers[3]) (u8 *, u32);
#endif
#ifndef PROTO_LOCAL_Save_Sum16
u16 Save_Sum16(u16 *p, u32 n);
#endif
#ifndef PROTO_LOCAL_Save_CalcChecksum
u16 Save_CalcChecksum(u16 *p, u32 n, u32 m);
#endif
#ifndef PROTO_LOCAL_Backup_CancelAndWait
void Backup_CancelAndWait(void);
#endif
#ifndef PROTO_LOCAL_FishDisplay_OnNetPacket
void FishDisplay_OnNetPacket(u8 *p, u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Backup_Write
s32 Backup_Write(Backup *g, u32 a, const void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Backup_WriteAsync
s32 Backup_WriteAsync(Backup *g, u32 a, const void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Backup_Read
s32 Backup_Read(Backup *g, void *a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Backup_ReadAsync
s32 Backup_ReadAsync(Backup *g, void *a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Backup_GetStatus
s32 Backup_GetStatus(Backup *g);
#endif
#ifndef PROTO_LOCAL_Backup_EndAccess
void Backup_EndAccess(Backup *g);
#endif
}
#endif

#endif
