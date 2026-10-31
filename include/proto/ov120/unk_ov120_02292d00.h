#ifndef PROTO_PROTO_OV120_UNK_OV120_02292D00_H
#define PROTO_PROTO_OV120_UNK_OV120_02292D00_H


#include "types.h"
#include "sys/ProcProfile.h"
struct Unk_ov120_02293a2c_Oam;
#ifndef __cplusplus
typedef struct Unk_ov120_02293a2c_Oam Unk_ov120_02293a2c_Oam;
#endif
#ifdef __cplusplus
class MapViewerMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sMapViewPlacesButtonCells
extern u8 sMapViewPlacesButtonCells[32];
#endif
#ifndef PROTO_LOCAL_sMapViewFrameCells
extern u8 sMapViewFrameCells[80];
#endif
#ifndef PROTO_LOCAL_sMapViewResidentsButtonCells
extern u8 sMapViewResidentsButtonCells[32];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MapViewerMenu_Create
MapViewerMenu *MapViewerMenu_Create();
#endif
#ifndef PROTO_LOCAL_sMapViewIconCell
extern Unk_ov120_02293a2c_Oam sMapViewIconCell;
#endif
#ifndef PROTO_LOCAL_sMapViewerMenuProfile
extern ProcProfile sMapViewerMenuProfile;
#endif
}
#endif

#endif
