#ifndef PROTO_PROTO_MAIN_UNK_0208E6D8_H
#define PROTO_PROTO_MAIN_UNK_0208E6D8_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class TransitionCommIcon;
class TransitionCommIconProc;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_RequestShow
void TransitionCommIcon_RequestShow(u32 i);
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_RequestHide
void TransitionCommIcon_RequestHide(u32 i);
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Resume
void TransitionCommIcon_Resume();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_ResumeWinOut
void TransitionCommIcon_ResumeWinOut();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Suspend
void TransitionCommIcon_Suspend();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Init
void TransitionCommIcon_Init();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Exit
void TransitionCommIcon_Exit();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Update
void TransitionCommIcon_Update();
#endif
#ifndef PROTO_LOCAL_TransitionCommIcon_Draw
void TransitionCommIcon_Draw();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TransitionCommIconProc_Create
TransitionCommIconProc *TransitionCommIconProc_Create();
#endif
}
#ifndef PROTO_LOCAL_sTransitionCommIcon
extern TransitionCommIcon sTransitionCommIcon;
#endif
#ifndef PROTO_LOCAL_sTransitionCommIconProfile
extern ProcProfile sTransitionCommIconProfile;
#endif
#endif

#endif
