#ifndef PROTO_PROTO_MAIN_UNK_0209D70C_H
#define PROTO_PROTO_MAIN_UNK_0209D70C_H


#include "types.h"
#ifdef __cplusplus
#include "save/SaveData.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SaveData_SyncClockOffset
void SaveData_SyncClockOffset(SaveData *p);
#endif
#ifndef PROTO_LOCAL_SaveData_Setup
void SaveData_Setup(SaveData *p, u32 idx);
#endif
}
#ifndef PROTO_LOCAL_gSaveData
extern SaveData gSaveData;
#endif
#endif

#endif
