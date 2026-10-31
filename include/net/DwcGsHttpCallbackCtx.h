#ifndef NET_DWCGSHTTPCALLBACKCTX_H
#define NET_DWCGSHTTPCALLBACKCTX_H

#include "types.h"


typedef void (*DwcGsHttpCallback)(char *data, s32 len, s32 result, void *userData);

struct DwcGsHttpCallbackCtx {
    /* 0x0 */ void *userData;
    /* 0x4 */ DwcGsHttpCallback callback;
};
#ifndef __cplusplus
typedef struct DwcGsHttpCallbackCtx DwcGsHttpCallbackCtx;
#endif

#endif
