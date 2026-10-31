#ifndef NET_DWCWIFIINFO_H
#define NET_DWCWIFIINFO_H

#include "types.h"

struct DwcWiFiInfo {
    /* 0x00 */ u64 userId;
    /* 0x08 */ u64 unk_08;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
};

#ifdef __cplusplus
extern "C"
#endif
void DWCi_BM_GetWiFiInfo(struct DwcWiFiInfo *info);

#endif
