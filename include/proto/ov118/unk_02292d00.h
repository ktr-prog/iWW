#ifndef PROTO_PROTO_OV118_UNK_02292D00_H
#define PROTO_PROTO_OV118_UNK_02292D00_H


#include "types.h"
#include "nitro/gxoam.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class MapTab;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sMapTabResidentsButtonCells
extern GXOamAttr sMapTabResidentsButtonCells[4];
#endif
#ifndef PROTO_LOCAL_sMapTabIconCell
extern GXOamAttr sMapTabIconCell;
#endif
#ifndef PROTO_LOCAL_sMapTabPlacesButtonCells
extern GXOamAttr sMapTabPlacesButtonCells[4];
#endif
#ifndef PROTO_LOCAL_sMapTabFrameCells
extern GXOamAttr sMapTabFrameCells[10];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MapTab_Create
MapTab *MapTab_Create();
#endif
#ifndef PROTO_LOCAL_sMapTabProfile
extern ProcProfile sMapTabProfile;
#endif
}
#endif

#endif
