#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0211A6C0_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0211A6C0_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FS_ClearOverlayImage
void FS_ClearOverlayImage(FSOverlayInfoHeader *h);
#endif
#ifndef PROTO_LOCAL_FS_GetOverlayFileID
FSFileID FS_GetOverlayFileID(const FSOverlayInfoHeader *h);
#endif
#ifdef __cplusplus
}
#endif

#endif
