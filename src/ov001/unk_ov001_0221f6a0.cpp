#include "uptr.h"
#include "types.h"
#include "nitro/wm.h"
#include "nitro/os_rtc.h"
#include "proto/autoload_2/unk_02115468.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/ov001/unk_ov001_0221f6a0.h"
#include "proto/ov001/unk_ov001_02226f68.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

struct WfcUsbFoundAp {
    u8 bssid[6];
    u8 isGranted;
};

struct WfcUsbScanWork {
    u8 wmBuf[0xf00];
    u8 scanBuf[0x400];
    WfcUsbFoundAp foundAps[16];
    void (*callback)(s32);
    WMScanExParam scanParam;
    union {
        WMStatus status;
        u8 statusBuf[0x7bc];
    };
    u64 startTick;
    void *timeoutTask;
    u8 stopState;
    u8 pendingResult;
    u8 timedOut;
    u8 unk_1b83[0x1d];
};
#if !HOST64
static_assert(sizeof(WfcUsbScanWork) == 0x1ba0 && __builtin_offsetof(WfcUsbScanWork, startTick) == 0x1b74, "DS layout");
#endif

extern "C" const u8 sWfcEmptyBssid[8];
extern "C" const u8 sWfcUsbApSsid[12];
extern "C" const WMScanExParam sWfcUsbScanParam;
extern "C" WfcUsbScanWork *sWfcUsbScan;

extern "C" {
void DC_InvalidateRange(void *, s32);
void MI_CpuCopy8(const void *, const void *, s32);
u32 WM_ReadStatus(void *dst);
u32 WM_Reset(WMCallback cb);
u32 WM_End(WMCallback cb);
u32 WM_Initialize(void *buf, WMCallback cb, u16 dmaNo);
u32 WM_StartScanEx(WMCallback cb, WMScanExParam *p);
u32 WM_GetDispersionScanPeriod();
}

extern "C" {

s32 WfcUsbScan_Start(void (*cb)(s32))
{
    WfcUsbScanWork *g;
    OSOwnerInfo info;
    g = (WfcUsbScanWork *)WfcHeap_AllocClear(sizeof(WfcUsbScanWork), 0x20);
    sWfcUsbScan = g;
    g->callback = cb;
    g = sWfcUsbScan;
    g->startTick = OS_GetTick();
    if (WM_Initialize(g->wmBuf, WfcUsbScan_WmCallback, 3) == 2) {
        do {
            WM_ReadStatus(&sWfcUsbScan->status);
            g = sWfcUsbScan;
        } while (g->status.state != 2);
        g->scanParam = sWfcUsbScanParam;
        g->scanParam.scanBuf = (WMBssDesc *)g->scanBuf;
        u16 v = WM_GetDispersionScanPeriod();
        sWfcUsbScan->scanParam.maxChannelTime = v;
        OS_GetOwnerInfo(&info);
        MI_CpuCopy8(sWfcUsbApSsid, sWfcUsbScan->scanParam.ssid, 8);
        sWfcUsbScan->scanParam.ssid[9] = 1;
        MI_CpuCopy8(info.nickName, sWfcUsbScan->scanParam.ssid + 12, info.nickNameLength * 2);
        if (WfcUsbScan_StartScan() != 0) {
            sWfcUsbScan->timeoutTask = WfcTask_Add(0, (void *)WfcUsbScan_TimeoutTask, 0, 0x78);
            return 1;
        }
    }
    WfcHeap_FreeAndClear((void **)&sWfcUsbScan);
    return 0;
}

s32 WfcUsbScan_StartScan()
{
    return WM_StartScanEx(WfcUsbScan_WmCallback, &sWfcUsbScan->scanParam) == 2 ? 1 : 0;
}

s32 WfcUsbScan_Stop()
{
    WfcUsbScanWork *g = sWfcUsbScan;
    g->stopState = 1;
    WM_ReadStatus(&sWfcUsbScan->status);
    if (sWfcUsbScan->status.state != 2) {
        if (WM_Reset(WfcUsbScan_WmCallback) != 2) {
            return 0;
        }
        do {
            WM_ReadStatus(&sWfcUsbScan->status);
        } while (sWfcUsbScan->status.state != 2);
    }
    if (WM_End(WfcUsbScan_WmCallback) != 2) {
        return 0;
    }
    WfcUsbScanWork *h = sWfcUsbScan;
    if (h->timeoutTask != 0) {
        WfcTask_Delete(0, h->timeoutTask);
    }
    volatile WfcUsbScanWork *v = sWfcUsbScan;
    while (v->stopState != 2) {
    }
    WfcHeap_FreeAndClear((void **)&sWfcUsbScan);
    return 1;
}

void WfcUsbScan_SetCallback(void (*cb)(s32))
{
    sWfcUsbScan->callback = cb;
}

void WfcUsbScan_WmCallback(WMMsg *msg)
{
    WMStartScanExCallback *m = (WMStartScanExCallback *)msg;
    WfcUsbScanWork *g;
    if (m->errcode != 0) {
        return;
    }
    g = sWfcUsbScan;
    if (g->stopState != 0) {
        if (m->apiid == 2) {
            g->stopState = 2;
        }
        return;
    }
    if (m->apiid != 0x26) {
        return;
    }
    switch (m->state) {
    case 5:
        if (g->timedOut != 0) {
            WfcUsbScan_CheckGranted(m);
        } else {
            WfcUsbScan_CollectAps(m);
        }
        WfcUsbScan_StartScan();
        break;
    case 4:
        WfcUsbScan_StartScan();
        break;
    default:
        Fatal_Trap();
        break;
    }
}

void WfcUsbScan_CollectAps(WMStartScanExCallback *a)
{
    s32 i;
    WMBssDesc *e;
    s32 j;
    WfcUsbFoundAp *p;
    WfcUsbScanWork *g;
    for (i = 0; i < a->bssDescCount; i++) {
        e = a->bssDesc[i];
        DC_InvalidateRange(e, 0xc0);
        if (memcmp(e->ssid, sWfcUsbApSsid, 8) == 0) {
            g = sWfcUsbScan;
            for (j = 0, p = g->foundAps; j < 16; p++, j++) {
                if (memcmp(e->bssid, p->bssid, 6) == 0) {
                    if (g->foundAps[j].isGranted != 0) {
                        goto next;
                    }
                    if ((e->ssid[9] & 1) == 0) {
                        goto next;
                    }
                    if (g->callback == NULL) {
                        return;
                    }
                    g->callback(1);
                    return;
                }
            }
            for (j = 0; j < 16; j++) {
                if (memcmp(g->foundAps[j].bssid, sWfcEmptyBssid, 6) == 0) {
                    MI_CpuCopy8(e->bssid, g->foundAps[j].bssid, 6);
                    sWfcUsbScan->foundAps[j].isGranted = (e->ssid[9] & 1) ? 1 : 0;
                    break;
                }
            }
        }
    next:;
    }
}

void WfcUsbScan_CheckGranted(WMStartScanExCallback *a)
{
    WMBssDesc *e;
    WfcUsbScanWork *g = sWfcUsbScan;
    s32 i;
    s32 j;
    s32 n;
    WfcUsbFoundAp *p;
    WfcUsbScanWork *h;
    if (g->pendingResult != 0) {
        if (g->callback != NULL) {
            g->callback(g->pendingResult);
        }
        return;
    }
    DC_InvalidateRange(g->scanBuf, 0x400);
    n = a->bssDescCount;
    i = 0;
    if (n <= 0) {
        return;
    }
    h = sWfcUsbScan;
    do {
        e = a->bssDesc[i];
        if (memcmp(e->ssid, sWfcUsbApSsid, 8) == 0 && (e->ssid[9] & 1) != 0) {
            for (j = 0, p = h->foundAps; j < 16; j++, p++) {
                if (memcmp(e->bssid, p->bssid, 6) == 0) {
                    if (h->foundAps[j].isGranted != 0) {
                        break;
                    }
                    if (h->callback == NULL) {
                        h->pendingResult = 1;
                        return;
                    }
                    h->callback(1);
                    return;
                }
            }
        }
        i++;
    } while (i < n);
}

void WfcUsbScan_TimeoutTask(void *task, void *work)
{
    WfcUsbScanWork *g;
    s32 i, b, a;
    u64 now = OS_GetTick();
    g = sWfcUsbScan;
    a = 0;
    if (now < g->startTick + 0x17f898) return;
    b = 0;
    for (i = 0; i < 16; i++) {
        if (memcmp(g->foundAps[i].bssid, sWfcEmptyBssid, 6)) {
            if (g->foundAps[i].isGranted) b = 1;
            else a = 1;
        }
    }
    if (b && a) {
        if (g->callback) g->callback(2);
    } else if (b) {
        if (g->callback) g->callback(1);
    } else if (!a) {
        if (g->callback) g->callback(0);
    }
    sWfcUsbScan->timeoutTask = 0;
    sWfcUsbScan->timedOut = 1;
    WfcTask_RequestDelete(0, task);
}

extern "C" const u8 sWfcEmptyBssid[8] = {0, 0, 0, 0, 0, 0, 0, 0};
extern "C" const u8 sWfcUsbApSsid[12] = {'N', 'W', 'C', 'U', 'S', 'B', 'A', 'P', 0, 0, 0, 0};
extern "C" const WMScanExParam sWfcUsbScanParam = {
    0, 0x400, 0x3fff, 0, {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, 2, 0x20, {0}, 8, {0},
};
extern "C" WfcUsbScanWork *sWfcUsbScan = 0;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221f6a0) {
    HOST_OVERLAY_VAR(sWfcUsbScan),
    HOST_OVERLAY_VARS_END
};
