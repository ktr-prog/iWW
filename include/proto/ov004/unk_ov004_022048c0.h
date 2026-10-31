#ifndef PROTO_PROTO_OV004_UNK_OV004_022048C0_H
#define PROTO_PROTO_OV004_UNK_OV004_022048C0_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class Atm;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sAtmStringBankPtr
extern char *sAtmStringBankPtr;
#endif
#ifndef PROTO_LOCAL_sAtmMsgFile
extern char sAtmMsgFile[12];
#endif
#ifndef PROTO_LOCAL_sAtmMsgFilePtr
extern char *sAtmMsgFilePtr;
#endif
#ifndef PROTO_LOCAL_sAtmStringBank
extern char sAtmStringBank[8];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Atm_Create
Atm *Atm_Create();
#endif
#ifndef PROTO_LOCAL_Atm_GetInstance
Atm *Atm_GetInstance();
#endif
#ifndef PROTO_LOCAL_sAtmInstance
extern Atm *sAtmInstance;
#endif
#ifndef PROTO_LOCAL_sAtmProfile
extern ActorProfile sAtmProfile;
#endif
}
#endif

#endif
