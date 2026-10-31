#ifndef PROTO_PROTO_OV001_UNK_OV001_022032F8_H
#define PROTO_PROTO_OV001_UNK_OV001_022032F8_H


#include "types.h"
#include "net/WifiLinkConfig.h"
#ifdef __cplusplus
#include "net/WifiLinkEvent.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sAossWcmWork
extern u8 *sAossWcmWork;
#endif
#ifndef PROTO_LOCAL_sAossWcmWepDesc
extern u8 *sAossWcmWepDesc;
#endif
#ifndef PROTO_LOCAL_sAossWcmBssDesc
extern u8 *sAossWcmBssDesc;
#endif
#ifndef PROTO_LOCAL_sAossWcmBssid
extern u8 sAossWcmBssid[6];
#endif
#ifndef PROTO_LOCAL_sAossWcmState
extern s32 sAossWcmState;
#endif
#ifndef PROTO_LOCAL_sAossWcmSsid
extern u8 sAossWcmSsid[0x20];
#endif
#ifndef PROTO_LOCAL_sAossWcmBssidPtr
extern u8 *sAossWcmBssidPtr;
#endif
#ifndef PROTO_LOCAL_sAossWcmConnectOption
extern s32 sAossWcmConnectOption;
#endif
#ifndef PROTO_LOCAL_sAossWcmSsidPtr
extern u8 *sAossWcmSsidPtr;
#endif
#ifndef PROTO_LOCAL_sAossWcmConfig
extern WifiLinkConfig *sAossWcmConfig;
#endif
#ifndef PROTO_LOCAL_sAossWcmSearchOption
extern s32 sAossWcmSearchOption;
#endif
#ifndef PROTO_LOCAL_Aoss_WcmToIdle
s32 Aoss_WcmToIdle(void);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmReadApList
s32 Aoss_WcmReadApList(u8 *dst, s32 max);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmStartSearch
s32 Aoss_WcmStartSearch(u8 *a, u8 *b, s32 n, s32 d);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmEndSearch
s32 Aoss_WcmEndSearch(void);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmDisconnect
s32 Aoss_WcmDisconnect(void);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmCleanup
s32 Aoss_WcmCleanup(void);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmConnect
s32 Aoss_WcmConnect(void *a, void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_WcmInit
s32 Aoss_WcmInit(void *fn, void *buf, u32 size);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Aoss_WcmCallback
void Aoss_WcmCallback(WifiLinkEvent *p);
#endif
}
#endif

#endif
