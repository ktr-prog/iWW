#ifndef PROTO_PROTO_OV001_UNK_OV001_0221EB38_H
#define PROTO_PROTO_OV001_UNK_OV001_0221EB38_H


#include "types.h"
struct WfcHeaderWork;
#ifndef __cplusplus
typedef struct WfcHeaderWork WfcHeaderWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcHeader_Create
void WfcHeader_Create(s32 n);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInTask0
void WfcHeader_SlideInTask0(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInTask1
void WfcHeader_SlideInTask1(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInTask2
void WfcHeader_SlideInTask2(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInTask3
void WfcHeader_SlideInTask3(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInTask4
void WfcHeader_SlideInTask4(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideInDone
void WfcHeader_SlideInDone(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_StartSlideOut
void WfcHeader_StartSlideOut();
#endif
#ifndef PROTO_LOCAL_WfcHeader_SetStep
void WfcHeader_SetStep(s32 n);
#endif
#ifndef PROTO_LOCAL_WfcHeader_IsAnimating
s32 WfcHeader_IsAnimating();
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideOutTask4
void WfcHeader_SlideOutTask4(void *r);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideOutTask3
void WfcHeader_SlideOutTask3(void *a);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideOutTask2
void WfcHeader_SlideOutTask2(void *a);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideOutTask1
void WfcHeader_SlideOutTask1(void *a);
#endif
#ifndef PROTO_LOCAL_WfcHeader_SlideOutTask0
void WfcHeader_SlideOutTask0(void *a);
#endif
#ifndef PROTO_LOCAL_WfcHeader_IsSlideOutDone
BOOL WfcHeader_IsSlideOutDone();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcHeader
extern WfcHeaderWork *sWfcHeader;
#endif
}
#endif

#endif
