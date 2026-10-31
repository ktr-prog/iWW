#ifndef PROTO_PROTO_MAIN_UNK_0206CBDC_H
#define PROTO_PROTO_MAIN_UNK_0206CBDC_H


#include "types.h"
#ifdef __cplusplus
#include "ui/LetterLayout.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_LetterLayout_SplitBody
s32 LetterLayout_SplitBody(void *unused, u8 *a, s32 *b, s32 *c);
#endif
#ifndef PROTO_LOCAL_Text_SplitLines
s32 Text_SplitLines(u8 *str, s32 *starts, s32 *cnt, s32 len, s32 maxw, s32 pxw, s32 maxLines);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_LetterLayout_HighlightSignature
void LetterLayout_HighlightSignature(LetterLayout *self, u32 a, u32 b, u32 c);
#endif
}
#endif

#endif
