#ifndef PROTO_PROTO_OV001_UNK_OV001_02207904_H
#define PROTO_PROTO_OV001_UNK_OV001_02207904_H


#include "types.h"
struct WfcBusyIcon;
#ifndef __cplusplus
typedef struct WfcBusyIcon WfcBusyIcon;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcBusyIcon_Create
void WfcBusyIcon_Create(u32 idx);
#endif
#ifndef PROTO_LOCAL_WfcBusyIcon_Delete
void WfcBusyIcon_Delete();
#endif
#ifndef PROTO_LOCAL_WfcBusyIcon_Task
void WfcBusyIcon_Task(void *task);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcBusyIcon
extern WfcBusyIcon *sWfcBusyIcon;
#endif
}
#endif

#endif
