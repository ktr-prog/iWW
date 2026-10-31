#ifndef PROTO_PROTO_MAIN_UNK_02096C10_H
#define PROTO_PROTO_MAIN_UNK_02096C10_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "item/Letter.h"
class LetterDeliveryProc;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BottleLetterRecord_GetLetter
void *BottleLetterRecord_GetLetter(void *p);
#endif
#ifndef PROTO_LOCAL_FutureLetter_GetLetter
void *FutureLetter_GetLetter(void *p);
#endif
#ifndef PROTO_LOCAL_MotherLetterState_Construct
void MotherLetterState_Construct();
#endif
#ifndef PROTO_LOCAL_MotherLetterState_Destruct
void MotherLetterState_Destruct();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BottleLetterRecord_Construct
Letter *BottleLetterRecord_Construct(Letter *p);
#endif
#ifndef PROTO_LOCAL_BottleLetterRecord_Destruct
Letter *BottleLetterRecord_Destruct(Letter *p);
#endif
#ifndef PROTO_LOCAL_FutureLetter_Construct
Letter *FutureLetter_Construct(Letter *p);
#endif
#ifndef PROTO_LOCAL_FutureLetter_Destruct
Letter *FutureLetter_Destruct(Letter *p);
#endif
#ifndef PROTO_LOCAL_LetterDeliveryProc_Create
LetterDeliveryProc *LetterDeliveryProc_Create();
#endif
}
#ifndef PROTO_LOCAL_data_020e1da0
extern ProcProfile data_020e1da0;
#endif
#endif

#endif
