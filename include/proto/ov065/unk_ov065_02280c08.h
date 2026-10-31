#ifndef PROTO_PROTO_OV065_UNK_OV065_02280C08_H
#define PROTO_PROTO_OV065_UNK_OV065_02280C08_H


#include "types.h"
#include "net/gp.h"
#include "net/gpiTransfer.h"
#ifdef __cplusplus
#include "net/gpiPeer.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Unk_ov065_02281180_pool_order
__declspec(weak) void Unk_ov065_02281180_pool_order(void);
#endif
#ifndef PROTO_LOCAL_GsGpPeer_SetSocketBuffers
void GsGpPeer_SetSocketBuffers(s32 s);
#endif
#ifndef PROTO_LOCAL_gpiProcessPeers
s32 gpiProcessPeers(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpiFreeMessage
void gpiFreeMessage(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiProcessPeerInitiatingConnection
s32 gpiProcessPeerInitiatingConnection(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiProcessPeerAcceptingConnection
s32 gpiProcessPeerAcceptingConnection(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiPeerSendMessages
s32 gpiPeerSendMessages(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiProcessPeerConnected
s32 gpiProcessPeerConnected(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiProcessPeer
s32 gpiProcessPeer(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiDestroyPeer
void gpiDestroyPeer(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiRemovePeer
void gpiRemovePeer(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiGetPeerByProfile
GPIPeer *gpiGetPeerByProfile(GPConnection *h, s32 id);
#endif
#ifndef PROTO_LOCAL_gpiAddPeer
GPIPeer *gpiAddPeer(GPConnection *h, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_gpiPeerGetSig
s32 gpiPeerGetSig(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiPeerStartConnect
s32 gpiPeerStartConnect(GPConnection *h, GPIPeer *n);
#endif
#ifndef PROTO_LOCAL_gpiPeerAddMessage
s32 gpiPeerAddMessage(GPConnection *h, GPIPeer *n, s32 a, const char *b);
#endif
#ifndef PROTO_LOCAL_gpiPeerStartTransferMessage
s32 gpiPeerStartTransferMessage(GPConnection *h, GPIPeer *n, s32 a, GPITransferID *s);
#endif
#ifndef PROTO_LOCAL_gpiPeerFinishTransferMessage
s32 gpiPeerFinishTransferMessage(GPConnection *h, GPIPeer *n, char *str, s32 len);
#endif
}
#endif

#endif
