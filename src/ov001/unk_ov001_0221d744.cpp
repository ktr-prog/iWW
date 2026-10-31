#include "types.h"
#include "net/WfcApScanEntry.h"
#include "nitro/wm.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0211f488.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_0221d744.h"

#pragma thumb off

struct WfcApScanWork {
    u8 wmWork[0xf00];
    u8 scanBuf[0x400];
    WfcApScanEntry entries[20];
    WMScanExParam scanParam;
    union {
        WMStatus status;
        u8 statusBuf[0x7bc];
    };
    u8 isStopping;
    u8 unk_1e49[0x17];
};

extern "C" {
s32 DC_InvalidateRange(void *, s32);
s32 MI_CpuCopy8(void *, void *, s32);
s32 WM_ReadStatus(void *);
s32 WM_Reset(void *);
s32 WM_End(void *);
s32 WM_StartScanEx(void *, WMScanExParam *);
s32 MIi_CpuClear16(s32, void *, s32);
s32 WM_Initialize(void *, void *, s32);
s32 WM_GetDispersionScanPeriod();
u32 WM_GetAllowedChannel();
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_AllocClear(s32, s32);
}

extern "C" const u8 sWfcWpaOui[4] = { 0x00, 0x50, 0xf2, 0x01 };
extern "C" const u8 sWfcApScanEmptyBssid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
extern "C" const WMScanExParam sWfcApScanParam = {
    0, 0x400, 0x3fff, 0, { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0, 0, { 0 }, 0, { 0 },
};
WfcApScanWork *sWfcApScan;

void WfcApScan_Alloc() {
    if (sWfcApScan != 0) return;
    sWfcApScan = (WfcApScanWork *)WfcHeap_AllocClear(sizeof(WfcApScanWork), 0x20);
}

void WfcApScan_Free() {
    if (sWfcApScan == 0) return;
    do {
    } while (WM_GetAllowedChannel() != 0x8000);
    WfcHeap_FreeAndClear(&sWfcApScan);
}

BOOL WfcApScan_Start() {
    volatile u16 z = 0;
    MIi_CpuClear16(z, sWfcApScan->entries, sizeof(sWfcApScan->entries));
    if (WM_Initialize(sWfcApScan->wmWork, (void *)WfcApScan_WmCallback, 3) != 2) return FALSE;
    WfcApScanWork *g;
    do {
        WM_ReadStatus(sWfcApScan->statusBuf);
        g = sWfcApScan;
    } while (g->status.state != 2);
    g->scanParam = sWfcApScanParam;
    g->scanParam.scanBuf = (WMBssDesc *)g->scanBuf;
    sWfcApScan->scanParam.maxChannelTime = WM_GetDispersionScanPeriod();
    if (WfcApScan_StartScan() != 0) return TRUE;
    return FALSE;
}

BOOL WfcApScan_StartScan() {
    if (WM_StartScanEx((void *)WfcApScan_WmCallback, &sWfcApScan->scanParam) == 2) return TRUE;
    return FALSE;
}

BOOL WfcApScan_Stop() {
    sWfcApScan->isStopping = 1;
    WM_ReadStatus(sWfcApScan->statusBuf);
    if (sWfcApScan->status.state != 2) {
        if (WM_Reset((void *)WfcApScan_WmCallback) != 2) return FALSE;
        do {
            WM_ReadStatus(sWfcApScan->statusBuf);
        } while (sWfcApScan->status.state != 2);
    }
    if (WM_End((void *)WfcApScan_WmCallback) != 2) return FALSE;
    return TRUE;
}

s32 WfcApScan_GetResults(WfcApScanEntry **out) {
    s32 cnt = 0;
    s32 i = 0;
    *out = sWfcApScan->entries;
    WfcApScanEntry *e = *out;
    for (; i < 20; i++, e++) {
        if (memcmp(e->bssid, sWfcApScanEmptyBssid, 6) != 0) cnt++;
    }
    return cnt;
}

void WfcApScan_WmCallback(WMMsg *msg) {
    WMStartScanExCallback *p = (WMStartScanExCallback *)msg;
    if (p->errcode != 0) return;
    if (sWfcApScan->isStopping != 0) return;
    if (p->apiid != 0x26) return;
    switch (p->state) {
    case 5:
        WfcApScan_StoreResults(p);
        WfcApScan_StartScan();
        break;
    case 4:
        WfcApScan_StartScan();
        break;
    default:
        Fatal_Trap();
        break;
    }
}

void WfcApScan_StoreResults(WMStartScanExCallback *p) {
    WfcApScanEntry *tbl;
    WMOtherElements buf;
    s32 i;
    tbl = sWfcApScan->entries;
    DC_InvalidateRange(sWfcApScan->scanBuf, sizeof(sWfcApScan->scanBuf));
    for (i = 0; i < p->bssDescCount; i++) {
        WMBssDesc *n = p->bssDesc[i];
        if (n->ssid[0] != 0 && n->gameInfoLength == 0) {
            s32 j = 0;
            WfcApScanEntry *e = tbl;
            do {
                if (memcmp(n->bssid, e->bssid, 6) == 0) break;
                e++;
                j++;
            } while (j < 20);
            if (j == 20) {
                j = 0;
                e = tbl;
                do {
                    if (memcmp(e->bssid, sWfcApScanEmptyBssid, 6) == 0) break;
                    e++;
                    j++;
                } while (j < 20);
                if (j == 20) return;
            }
            e = tbl + j;
            MI_CpuCopy8(n->bssid, e->bssid, 6);
            MI_CpuCopy8(n->ssid, e->ssid, 0x20);
            e->linkLevel = p->linkLevel[i];
            if ((n->capaInfo & 0x10) == 0) {
                e->security = 0;
            } else {
                e->security = 1;
                buf = WM_GetOtherElements(n);
                s32 k;
                s32 cnt = buf.count;
                for (k = 0; k < cnt; k++) {
                    if (buf.element[k].id == 0x30) {
                        e->security = 2;
                        break;
                    }
                    if (buf.element[k].id == 0xdd && buf.element[k].length >= 4 && memcmp(buf.element[k].body, sWfcWpaOui, 4) == 0) {
                        e->security = 2;
                        break;
                    }
                }
            }
        }
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221d744) {
    HOST_OVERLAY_VAR(sWfcApScan),
    HOST_OVERLAY_VARS_END
};
