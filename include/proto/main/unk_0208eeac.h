#ifndef PROTO_PROTO_MAIN_UNK_0208EEAC_H
#define PROTO_PROTO_MAIN_UNK_0208EEAC_H


#include "types.h"
#ifdef __cplusplus
#include "ui/InputModeIcon.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ReceivedLetter_Clear
void ReceivedLetter_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_ReceivedLetter_HasLetter
BOOL ReceivedLetter_HasLetter(void *p);
#endif
#ifndef PROTO_LOCAL_ReceivedLetter_GetLetter
void *ReceivedLetter_GetLetter(void *p);
#endif
#ifndef PROTO_LOCAL_InputMode_Clear
void InputMode_Clear();
#endif
#ifndef PROTO_LOCAL_InputMode_SetButtons
void InputMode_SetButtons();
#endif
#ifndef PROTO_LOCAL_InputMode_SetTouch
void InputMode_SetTouch();
#endif
#ifndef PROTO_LOCAL_InputMode_IsButtons
BOOL InputMode_IsButtons();
#endif
#ifndef PROTO_LOCAL_InputMode_IsTouch
BOOL InputMode_IsTouch();
#endif
#ifndef PROTO_LOCAL_InputModeIcon_Init
void InputModeIcon_Init();
#endif
#ifndef PROTO_LOCAL_InputModeIcon_Exit
void InputModeIcon_Exit();
#endif
#ifndef PROTO_LOCAL_InputModeIcon_Update
void InputModeIcon_Update();
#endif
#ifndef PROTO_LOCAL_InputModeIcon_Draw
void InputModeIcon_Draw();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sInputModeIcon
extern InputModeIcon sInputModeIcon;
#endif
#endif

#endif
