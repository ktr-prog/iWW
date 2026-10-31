#ifndef PROTO_PROTO_OV106_UNK_OV106_02294C40_H
#define PROTO_PROTO_OV106_UNK_OV106_02294C40_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class MailboxMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MailboxMenu_SetupBgLayers
void MailboxMenu_SetupBgLayers();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sMailboxMenuProfile
extern ProcProfile sMailboxMenuProfile;
#endif
#ifndef PROTO_LOCAL_MailboxMenu_Create
MailboxMenu *MailboxMenu_Create();
#endif
}
#endif

#endif
