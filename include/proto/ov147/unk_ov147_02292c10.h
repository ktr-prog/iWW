#ifndef PROTO_PROTO_OV147_UNK_OV147_02292C10_H
#define PROTO_PROTO_OV147_UNK_OV147_02292C10_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_Alloc
void *TitleBlinkText_Alloc(u32 size);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_Free
void TitleBlinkText_Free(void *p);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_LoadGraphics
void TitleBlinkText_LoadGraphics(s32 idx);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_ReadChars
void TitleBlinkText_ReadChars(FSFile *a, const char *b, void *c);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_ReadPalette
void TitleBlinkText_ReadPalette(FSFile *a, const char *b, void *c);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_ReadScreen
void TitleBlinkText_ReadScreen(FSFile *a, const char *b, void *c);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_UploadChars
void TitleBlinkText_UploadChars(void *p);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_UploadPalette
void TitleBlinkText_UploadPalette(void *p);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_UploadScreen
void TitleBlinkText_UploadScreen(void *p);
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_SetupBg3
void TitleBlinkText_SetupBg3();
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_ShowBg3
void TitleBlinkText_ShowBg3();
#endif
#ifndef PROTO_LOCAL_TitleBlinkText_HideBg3
void TitleBlinkText_HideBg3();
#endif
#ifdef __cplusplus
}
#endif

#endif
