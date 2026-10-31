#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020FAC28_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020FAC28_H


#include "types.h"
struct Emit;
struct Part;
#ifndef __cplusplus
typedef struct Emit Emit;
typedef struct Part Part;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_drawXYPlane
void drawXYPlane(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_drawXZPlane
void drawXZPlane(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_rotTypeXYZ
void rotTypeXYZ(s32 a, s32 b, s32 *m);
#endif
#ifndef PROTO_LOCAL_rotTypeY
void rotTypeY(s32 a, s32 b, s32 *m);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_spl_gen_child
void spl_gen_child(Part *a, Emit *b, void *list);
#endif
}
#endif

#endif
