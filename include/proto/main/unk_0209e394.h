#ifndef PROTO_PROTO_MAIN_UNK_0209E394_H
#define PROTO_PROTO_MAIN_UNK_0209E394_H


#include "types.h"
#include "sys/ProcProfile.h"
struct SaveMenuStateEntry;
#ifndef __cplusplus
typedef struct SaveMenuStateEntry SaveMenuStateEntry;
#endif
#ifdef __cplusplus
class SaveMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SaveData_ConstructDateRecord
void SaveData_ConstructDateRecord();
#endif
#ifndef PROTO_LOCAL_SaveData_DestructDateRecord
void SaveData_DestructDateRecord();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SaveMenu_Create
SaveMenu *SaveMenu_Create();
#endif
}
#ifndef PROTO_LOCAL_sSaveMenuProfile
extern ProcProfile sSaveMenuProfile;
#endif
#ifndef PROTO_LOCAL_sSaveMenuStates
extern SaveMenuStateEntry sSaveMenuStates[6];
#endif
#endif

#endif
