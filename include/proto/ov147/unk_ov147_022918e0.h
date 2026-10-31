#ifndef PROTO_PROTO_OV147_UNK_OV147_022918E0_H
#define PROTO_PROTO_OV147_UNK_OV147_022918E0_H


#include "types.h"
#include "sys/ProcProfile.h"
struct TitleStateEntry;
#ifndef __cplusplus
typedef struct TitleStateEntry TitleStateEntry;
#endif
#ifdef __cplusplus
class TitleScreen;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sTitleLogoRevealMasks
extern u32 sTitleLogoRevealMasks[15][8];
#endif
#ifndef PROTO_LOCAL_sTitleTalkFile
extern char sTitleTalkFile[];
#endif
#ifndef PROTO_LOCAL_sTitleLogoHideMasks
extern u32 sTitleLogoHideMasks[7][8];
#endif
#ifndef PROTO_LOCAL_sTitleLogoScreen
extern u16 sTitleLogoScreen[0x400];
#endif
#ifndef PROTO_LOCAL_sTitleLogoMask2
extern u8 sTitleLogoMask2[0x1e0];
#endif
#ifndef PROTO_LOCAL_sTitleTalkFilePtr
extern char *sTitleTalkFilePtr;
#endif
#ifndef PROTO_LOCAL_sTitleLogoCharsWork
extern u32 sTitleLogoCharsWork[0x1c0][8];
#endif
#ifndef PROTO_LOCAL_sTitleLogoChars
extern u32 sTitleLogoChars[0x1c0][8];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTitleStates
extern TitleStateEntry sTitleStates[12];
#endif
#ifndef PROTO_LOCAL_TitleScreen_Create
TitleScreen *TitleScreen_Create();
#endif
#ifndef PROTO_LOCAL_sTitleScreenProfile
extern ProcProfile sTitleScreenProfile;
#endif
}
#endif

#endif
