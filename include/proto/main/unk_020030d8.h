#ifndef PROTO_PROTO_MAIN_UNK_020030D8_H
#define PROTO_PROTO_MAIN_UNK_020030D8_H


#include "types.h"
struct HudLinkIcon;
#ifndef __cplusplus
typedef struct HudLinkIcon HudLinkIcon;
#endif
#ifdef __cplusplus
#include "npc/VillagerId.h"
class HudUnkSlideIcon;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HudLinkIcon_Reset
void HudLinkIcon_Reset();
#endif
#ifndef PROTO_LOCAL_HudLinkIcon_Exit
void HudLinkIcon_Exit();
#endif
#ifndef PROTO_LOCAL_HudLinkIcon_Update
void HudLinkIcon_Update();
#endif
#ifndef PROTO_LOCAL_HudLinkIcon_Draw
void HudLinkIcon_Draw();
#endif
#ifndef PROTO_LOCAL_HudUnkSlideIcon_Reset
void HudUnkSlideIcon_Reset();
#endif
#ifndef PROTO_LOCAL_HudUnkSlideIcon_Exit
void HudUnkSlideIcon_Exit();
#endif
#ifndef PROTO_LOCAL_HudUnkSlideIcon_Update
void HudUnkSlideIcon_Update();
#endif
#ifndef PROTO_LOCAL_HudUnkSlideIcon_Draw
void HudUnkSlideIcon_Draw();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_VillagerId_CopyFrom
void VillagerId_CopyFrom(VillagerId *p, VillagerId *other);
#endif
#ifndef PROTO_LOCAL_VillagerId_CopyTo
void VillagerId_CopyTo(VillagerId *p, VillagerId *other);
#endif
#ifndef PROTO_LOCAL_VillagerId_Construct
VillagerId *VillagerId_Construct(VillagerId *p);
#endif
#ifndef PROTO_LOCAL_VillagerId_ConstructCopy
VillagerId *VillagerId_ConstructCopy(VillagerId *p, VillagerId *other);
#endif
#ifndef PROTO_LOCAL_VillagerId_Destruct
VillagerId *VillagerId_Destruct(VillagerId *p);
#endif
#ifndef PROTO_LOCAL_VillagerId_Clear
void VillagerId_Clear(VillagerId *p);
#endif
#ifndef PROTO_LOCAL_VillagerId_Copy
void VillagerId_Copy(VillagerId *dst, VillagerId *src);
#endif
}
#ifndef PROTO_LOCAL_sHudLinkIcon
extern HudLinkIcon sHudLinkIcon;
#endif
#ifndef PROTO_LOCAL_sHudUnkSlideIcon
extern HudUnkSlideIcon sHudUnkSlideIcon;
#endif
#endif

#endif
