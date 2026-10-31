#ifndef PROTO_PROTO_OV097_UNK_0229B280_H
#define PROTO_PROTO_OV097_UNK_0229B280_H


#include "types.h"
#ifdef __cplusplus
#include "menu/PocketMenu.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PocketMenu_CanEditRoom
BOOL PocketMenu_CanEditRoom();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PocketMenu_AddRoomItemOptions
void PocketMenu_AddRoomItemOptions(PocketMenu *self, s32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenu_RequestDropIndoor
s32 PocketMenu_RequestDropIndoor(PocketMenu *self, s32 a);
#endif
}
#endif

#endif
