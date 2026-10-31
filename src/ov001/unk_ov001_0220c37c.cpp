#include "types.h"
#include "net/AossParam.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02202c44.h"
#include "proto/ov001/unk_ov001_0220c37c.h"

extern "C" {
extern const char data_ov001_02229f84[12];
const char data_ov001_02229f84[12] = "NINTENDO-DS";

volatile u8 sWfcAossSucceeded;
AossParam *sWfcAossConfig;

extern s32 Aoss_Run(void *);
extern s32 Aoss_WlanStartup(void *, void *);

#pragma thumb off

extern void WfcHeap_Free(void *p);
extern void *WfcHeap_Alloc(s32, s32);
extern void *WfcHeap_AllocClear(s32, s32);
extern void WfcHeap_FreeAndClear(void *);
extern void WfcConfig_StoreAoss(void *);
extern void MIi_CpuClear16(u32, void *, u32);
extern void MI_CpuCopy8(const void *, void *);
extern void OS_GetMacAddress(void *);

void WfcAoss_Begin() {
    volatile u16 z;
    AossClientInfo r;
    sWfcAossConfig = (AossParam *)WfcHeap_AllocClear(sizeof(AossParam), 4);
    sWfcAossSucceeded = 0;
    z = 0;
    MIi_CpuClear16(z, &r, 0x104);
    r.tlvType = 0x50;
    r.nameLength = 0xc;
    MI_CpuCopy8(data_ov001_02229f84, r.name);
    sWfcAossConfig->keyTypeMask = 3;
    sWfcAossConfig->clientInfo = r;
    sWfcAossConfig->apRetryCount = 1;
    sWfcAossConfig->apRetryWait = -1;
    sWfcAossConfig->packetRetryCount = 1;
    sWfcAossConfig->packetRetryWait = -1;
    sWfcAossConfig->recvTimeout = -1;
    OS_GetMacAddress(sWfcAossConfig->macAddress);
    if (Aoss_WlanStartup((void *)WfcAoss_Alloc, (void *)WfcAoss_Free) != 0) {
        Fatal_Trap();
    }
}

void WfcAoss_End(s32 a) {
    Aoss_WlanShutdown();
    if (a != 0) {
        AossParam *o = sWfcAossConfig;
        if (o->errorCode == 0) {
            if (sWfcAossSucceeded == 1) {
                WfcConfig_StoreAoss(o->result);
            }
        }
    }
    WfcHeap_FreeAndClear(&sWfcAossConfig);
}

u32 WfcAoss_Run() {
    if (Aoss_Run(sWfcAossConfig) == 0) {
        sWfcAossSucceeded = 1;
        return 1;
    }
    u32 t = sWfcAossConfig->errorCode;
    if (t == 1) goto zero;
    if ((u8)(t + 0xfd) > 2) goto two;
zero:
    return 0;
two:
    return 2;
}

void *WfcAoss_Alloc(s32 a) {
    return WfcHeap_Alloc(a, 0x20);
}

void WfcAoss_Free(void *p) {
    WfcHeap_Free(p);
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220c37c) {
    HOST_OVERLAY_VAR(sWfcAossSucceeded),
    HOST_OVERLAY_VAR(sWfcAossConfig),
    HOST_OVERLAY_VARS_END
};
