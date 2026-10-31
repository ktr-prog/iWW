#ifndef PROTO_PROTO_MAIN_UNK_020A8C9C_H
#define PROTO_PROTO_MAIN_UNK_020A8C9C_H


#include "types.h"
#ifdef __cplusplus
class BufferBmgReader;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ChoiceWindow_BlankTiles
void ChoiceWindow_BlankTiles(void *p, u32 n);
#endif
#ifndef PROTO_LOCAL_ChoiceWindow_GetLabelTile
s32 ChoiceWindow_GetLabelTile(s32 a, s32 mode);
#endif
#ifndef PROTO_LOCAL_Choice_GetBmgName
const void *Choice_GetBmgName(u32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sChoiceBmgReader
extern BufferBmgReader sChoiceBmgReader;
#endif
#endif

#endif
