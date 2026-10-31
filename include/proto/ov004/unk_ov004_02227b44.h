#ifndef PROTO_PROTO_OV004_UNK_OV004_02227B44_H
#define PROTO_PROTO_OV004_UNK_OV004_02227B44_H


#include "types.h"
struct MuseumDisplayKind;
#ifndef __cplusplus
typedef struct MuseumDisplayKind MuseumDisplayKind;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/NNSG3dRS.h"
class MuseumDisplay;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sMuseumPictureTexPath
extern char sMuseumPictureTexPath[0x20];
#endif
#ifndef PROTO_LOCAL_sMuseumDisplayNodeName
extern char sMuseumDisplayNodeName[0x28];
#endif
#ifndef PROTO_LOCAL_sMuseumInsectTexPath
extern char sMuseumInsectTexPath[0x20];
#endif
#ifndef PROTO_LOCAL_sMuseumInsectArcPath
extern char sMuseumInsectArcPath[0x1c];
#endif
#ifndef PROTO_LOCAL_sMuseumPictureArcPath
extern char sMuseumPictureArcPath[0x1c];
#endif
#ifndef PROTO_LOCAL_MuseumDisplay_GetPaintingItem
u16 MuseumDisplay_GetPaintingItem(u32 i);
#endif
#ifndef PROTO_LOCAL_MuseumDisplay_InitRenderObj
void MuseumDisplay_InitRenderObj(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_02250e08
extern DebugColor data_ov004_02250e08;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250e18
extern DebugColor data_ov004_02250e18;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250e14
extern DebugColor data_ov004_02250e14;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250e1c
extern DebugColor data_ov004_02250e1c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250e10
extern DebugColor data_ov004_02250e10;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250e0c
extern DebugColor data_ov004_02250e0c;
#endif
#ifndef PROTO_LOCAL_sMuseumDisplayProfile
extern ActorProfile sMuseumDisplayProfile;
#endif
#ifndef PROTO_LOCAL_MuseumDisplay_Create
MuseumDisplay *MuseumDisplay_Create();
#endif
#ifndef PROTO_LOCAL_MuseumDisplay_GetKindInfo
const MuseumDisplayKind *MuseumDisplay_GetKindInfo(u32 i);
#endif
#ifndef PROTO_LOCAL_MuseumDisplay_NodeCallback
void MuseumDisplay_NodeCallback(NNSG3dRS *o);
#endif
}
#endif

#endif
