#ifndef PROTO_PROTO_OV133_UNK_OV133_022936C0_H
#define PROTO_PROTO_OV133_UNK_OV133_022936C0_H


#include "types.h"
#include "nitro/gxoam.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class FriendCodeMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sFriendCodeKeySeIds
extern u16 sFriendCodeKeySeIds[10];
#endif
#ifndef PROTO_LOCAL_sCaretCells
extern GXOamAttr sCaretCells[1];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FriendCodeMenu_Create
FriendCodeMenu *FriendCodeMenu_Create();
#endif
#ifndef PROTO_LOCAL_sFriendCodeMenuProfile
extern ProcProfile sFriendCodeMenuProfile;
#endif
}
#endif

#endif
