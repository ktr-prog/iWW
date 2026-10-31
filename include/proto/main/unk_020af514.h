#ifndef PROTO_PROTO_MAIN_UNK_020AF514_H
#define PROTO_PROTO_MAIN_UNK_020AF514_H


#include "types.h"
#ifdef __cplusplus
#include "field/LooseSnowballs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Snowman_FindInTown
BOOL Snowman_FindInTown(s32 *a, s32 *b, u32 idx);
#endif
#ifndef PROTO_LOCAL_Snowman_RemoveFromTown
BOOL Snowman_RemoveFromTown(u32 idx);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_gLooseSnowballs
extern LooseSnowballs gLooseSnowballs;
#endif
#endif

#endif
