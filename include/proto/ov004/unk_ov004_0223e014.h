#ifndef PROTO_PROTO_OV004_UNK_OV004_0223E014_H
#define PROTO_PROTO_OV004_UNK_OV004_0223E014_H


#include "types.h"
#include "sys/ProcProfile.h"
struct ResidentSelectStateEntry;
#ifndef __cplusplus
typedef struct ResidentSelectStateEntry ResidentSelectStateEntry;
#endif
#ifdef __cplusplus
class ResidentSelect;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ResidentSelect_Create
ResidentSelect *ResidentSelect_Create();
#endif
#ifndef PROTO_LOCAL_ResidentSelect_UpdateCursor
void ResidentSelect_UpdateCursor(ResidentSelect *o);
#endif
}
#ifndef PROTO_LOCAL_sResidentSelectProfile
extern ProcProfile sResidentSelectProfile;
#endif
#ifndef PROTO_LOCAL_sResidentSelectStates
extern ResidentSelectStateEntry sResidentSelectStates[7];
#endif
#endif

#endif
