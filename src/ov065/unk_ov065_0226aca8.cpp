#include "types.h"
#include "proto/ov065/unk_ov065_0226aca8.h"

extern "C" {

s32 _s32_div_f(s32, s32);

volatile u8 sWifiRssiCount[4];
u8 sWifiRssiSamples[16];


u8 WifiLink_GetAverageRssi() {
    u32 sum = 0;
    u8 cnt = sWifiRssiCount[0];
    s32 i;
    if (cnt > 16) {
        u8 *p;
        i = sum;
        p = sWifiRssiSamples;
        for (; i < 16; p++, i++) {
            sum += *p;
        }
        sum = _s32_div_f(sum, 16);
    } else if (cnt != 0) {
        for (i = sum; i < cnt; i++) {
            sum += sWifiRssiSamples[i];
        }
        sum = _s32_div_f(sum, cnt);
    }
    return sum;
}

u32 WifiLink_GetLinkLevel() {
    u32 n = WifiLink_GetAverageRssi();
    u32 r = 0;
    if (n >= 0x1c) {
        r = 3;
    } else if (n >= 0x16) {
        r = 2;
    } else if (n >= 0x10) {
        r = 1;
    }
    return r;
}

void WifiLink_AddRssiSample(s32 v) {
    u32 c;
    u8 idx;
    if ((v & 2) != 0) {
        c = ((u32)v << 22) >> 24;
    } else {
        c = (u8)((v >> 2) + 0x19);
    }
    idx = sWifiRssiCount[0];
    sWifiRssiSamples[idx % 16] = c;
    if (idx >= 16) {
        sWifiRssiCount[0] = (idx + 1) % 16 + 16;
    } else {
        sWifiRssiCount[0] = sWifiRssiCount[0] + 1;
    }
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_0226aca8) {
    HOST_OVERLAY_VAR(sWifiRssiCount),
    HOST_OVERLAY_VAR(sWifiRssiSamples),
    HOST_OVERLAY_VARS_END
};
