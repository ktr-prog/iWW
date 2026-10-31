#ifndef PROTO_PROTO_OV075_UNK_OV075_022713C0_H
#define PROTO_PROTO_OV075_UNK_OV075_022713C0_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
class SpNpcPete;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcPete_Create
SpNpcPete *SpNpcPete_Create();
#endif
#ifndef PROTO_LOCAL_SpNpcPete_ChangeAct
void SpNpcPete_ChangeAct(SpNpcPete *o, s32 state);
#endif
#ifndef PROTO_LOCAL_SpNpcPete_IsInFocusBox
s32 SpNpcPete_IsInFocusBox(SpNpcPete *self, VecFx32 *pa, VecFx32 *pb);
#endif
}
#endif

#endif
