#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020FEDCC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020FEDCC_H


#include "types.h"
#include "types64.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_DWC_Init
u32 DWC_Init(u8 *p);
#endif
#ifndef PROTO_LOCAL_DWCi_Acc_SetMaskBits
BOOL DWCi_Acc_SetMaskBits(u32 *p, u32 v, u32 shift, u32 mask);
#endif
#ifndef PROTO_LOCAL_DWC_Acc_CreateFriendKey
u64 DWC_Acc_CreateFriendKey(u32 lo, u32 key);
#endif
#ifndef PROTO_LOCAL_DWC_Acc_CheckFriendKey
BOOL DWC_Acc_CheckFriendKey(u64 v, u32 key);
#endif
#ifndef PROTO_LOCAL_DWC_Acc_FriendKeyToGsProfileId
u32 DWC_Acc_FriendKeyToGsProfileId(u64 v, u32 key);
#endif
#ifndef PROTO_LOCAL_DWCi_Acc_U64ToString32
void DWCi_Acc_U64ToString32(u64 v, s32 nbits, char *out);
#endif
#ifndef PROTO_LOCAL_DWCi_Util_IsLeapYear
BOOL DWCi_Util_IsLeapYear(u32 y);
#endif
#ifndef PROTO_LOCAL_DWCi_Util_WiFiId_scrambleUid
u64 DWCi_Util_WiFiId_scrambleUid(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_DWCi_AUTH_MakeWiFiID
BOOL DWCi_AUTH_MakeWiFiID(u8 *buf);
#endif
#ifndef PROTO_LOCAL_DWC_Auth_CheckWiFiIDNeedCreate
BOOL DWC_Auth_CheckWiFiIDNeedCreate(void);
#endif
#ifndef PROTO_LOCAL_DWC_BM_Init
s32 DWC_BM_Init(u8 *buf);
#endif
#ifndef PROTO_LOCAL_checkAp
BOOL checkAp(u8 *page);
#endif
#ifndef PROTO_LOCAL_init__DwcBm
BOOL init__DwcBm(u8 *buf);
#endif
#ifndef PROTO_LOCAL_initPage
void initPage(u8 *buf, u32 idx);
#endif
#ifndef PROTO_LOCAL_DWCi_BM_GetApInfo
BOOL DWCi_BM_GetApInfo(u8 *dst);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlInit
BOOL DWCi_BACKUPlInit(u16 *p);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlRead
BOOL DWCi_BACKUPlRead(u8 *dst);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlWritePage
BOOL DWCi_BACKUPlWritePage(u8 *buf, u32 *flags, u8 *tmp);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlWriteAll
BOOL DWCi_BACKUPlWriteAll(u8 *buf);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlSetWiFi
void DWCi_BACKUPlSetWiFi(u8 *p);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlConvMaskCidr
u8 DWCi_BACKUPlConvMaskCidr(u8 *p);
#endif
#ifndef PROTO_LOCAL_DWCi_BACKUPlConvMaskAddr
void DWCi_BACKUPlConvMaskAddr(u32 n, u8 *out);
#endif
#ifndef PROTO_LOCAL_DWC_BACKUPlCheckSsid
BOOL DWC_BACKUPlCheckSsid(u8 *p);
#endif
#ifndef PROTO_LOCAL_DWC_BACKUPlCheckIp
BOOL DWC_BACKUPlCheckIp(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_DWC_BACKUPlCheckAddress
BOOL DWC_BACKUPlCheckAddress(u8 *p);
#endif
#ifndef PROTO_LOCAL_data_02135c9c
extern const u8 data_02135c9c[4];
#endif
#ifndef PROTO_LOCAL_data_02135ca0
extern const u8 data_02135ca0[8];
#endif
#ifndef PROTO_LOCAL_data_02135ca8
extern const u8 data_02135ca8[16];
#endif
#ifndef PROTO_LOCAL_data_0213bba8
extern u32 data_0213bba8[13];
#endif
#ifdef __cplusplus
}
#endif

#endif
