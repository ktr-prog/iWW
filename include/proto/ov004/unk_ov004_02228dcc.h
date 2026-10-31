#ifndef PROTO_PROTO_OV004_UNK_OV004_02228DCC_H
#define PROTO_PROTO_OV004_UNK_OV004_02228DCC_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class TarotProps;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TarotProps_StartAct01
BOOL TarotProps_StartAct01();
#endif
#ifndef PROTO_LOCAL_TarotProps_StartAct02
BOOL TarotProps_StartAct02();
#endif
#ifndef PROTO_LOCAL_TarotProps_StartAct03
BOOL TarotProps_StartAct03();
#endif
#ifndef PROTO_LOCAL_TarotProps_Draw
void TarotProps_Draw();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTarotPropsProfile
extern ActorProfile sTarotPropsProfile;
#endif
#ifndef PROTO_LOCAL_sTarotProps
extern TarotProps *sTarotProps;
#endif
#ifndef PROTO_LOCAL_TarotProps_Create
TarotProps *TarotProps_Create();
#endif
}
#endif

#endif
