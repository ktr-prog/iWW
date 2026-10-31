#include "ds_div.h"
#include "uptr.h"
#include "types.h"
#include "net/WifiLinkConfig.h"
#include "net/WifiLinkSendState.h"
#include "net/WifiLinkWork.h"
#include "net/WifiApControl.h"
#include "net/WifiApConfig.h"
#include "net/WifiApContext.h"
#include "nitro/wm.h"
#include "net/WifiLinkEvent.h"
#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02114d84.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/ov065/unk_ov065_02268c64.h"
#include "proto/ov065/unk_ov065_0226aca8.h"
#include "proto/ov065/unk_ov065_0226ad84.h"
namespace N_8ec8 { struct WifiLinkWmCallbackArg; }
extern "C" {
void WifiLink_SetupScanParams(const u8 *a, const u8 *b, u32 c);
s32 WifiLink_EndSearchAsync();
void WifiLink_OnFrameReceived(u8 *p);
void WifiLink_AddApListEntry(WMBssDesc *a, u32 b);
void WifiLink_OnEndDcf(N_8ec8::WifiLinkWmCallbackArg *m);
void WifiLink_OnScanResult(WMStartScanExCallback *m);
void WifiLink_OnWmCommand(N_8ec8::WifiLinkWmCallbackArg *m);
void WifiLink_OnWmIndication(N_8ec8::WifiLinkWmCallbackArg *m);
void WifiLink_OnConnectEvent(N_8ec8::WifiLinkWmCallbackArg *m);
void WifiLink_OnReset(WMMsg *m);
u32 WifiLink_NextAllowedChannel(s32 a);
void WifiLink_NotifyRequest(s32 a, void *b, s32 c, s32 d);
void WifiLink_SetPhase(s32 st);
}
extern "C" {
void MI_CpuFill8(void *dst, u32 data, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
}

extern "C" {

extern const u8 gWifiLinkAnyBssid[8];
extern const u8 gWifiLinkAnySsid[0x20];
const u8 gWifiLinkAnyBssid[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0};
const u8 gWifiLinkAnySsid[0x20] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
WifiLinkSendState sWifiLinkSendState;
WifiLinkWork *volatile sWifiLinkWork;
OSThreadQueue sWifiLinkSendWaitQueue;
OSMutex sWifiLinkSendLock;

}

namespace N_ab40 {



typedef void (*WifiLinkRecvCallback)(void *, void *, void *, u32);









extern "C" {

extern WifiLinkSendState sWifiLinkSendState;
extern OSMutex sWifiLinkSendLock;
extern WifiApAllocator *sWifiApAllocator;
extern WifiApControl *sWifiApControl;

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
s32 func_02133150(s32, s32);
s32 DGT_Hash1GetDigest_R();
s32 DGT_Hash1SetSource();
s32 DGT_Hash1Reset();
void MIi_CpuClear32(u32, void *, u32);
void MIi_CpuCopy32(void *, void *, u32);
s32 strncmp(void *, void *, u32);
s32 WM_SetDCFData(void *, void *, void *, u32);
void DWCi_BM_GetApInfo(void *);

WifiLinkWork *WifiLink_GetWork();
s32 WifiLink_Init(void *, u32);
void WifiLink_UnlockFromIrq(OSMutex *);
BOOL WifiLink_TryLockFromIrq(OSMutex *);
void WifiLink_OnKeepAliveSent();
s32 WifiAp_CleanupStep(u8 *);
s32 WifiAp_GetErrorCode2();
u8 WifiAp_StepFailedCleanup();
u8 WifiAp_ProcessConnect();
u8 WifiAp_StepRecoverLink();
u8 WifiAp_ProcessSearch();
u8 WifiAp_ProcessStartup();
u8 WifiAp_ProcessNetSetup();






































void WifiLink_InitSendState() {
    if (sWifiLinkSendState.initialized == 0) {
        sWifiLinkSendState.initialized = 1;
        sWifiLinkSendState.sendResult = 0;
        sWifiLinkSendState.unk_08 = 0;
        sWifiLinkSendState.unk_04 = 0;
        OS_InitMutex(&sWifiLinkSendLock);
    }
}

void WifiLink_OnFrameReceived(u8 *p) {
    WifiLinkRecvCallback cb = sWifiLinkSendState.recvCallback;
    if (cb != 0) {
        cb(p + 0x1e, p + 0x18, p + 0x2c, *(u16 *)(p + 6));
    }
}

void WifiLink_SendKeepAlive() {
    WifiLinkWork *c = WifiLink_GetWork();
    if (c != 0 && c->phase == 9 && c->isResetting != 1) {
        if (WifiLink_TryLockFromIrq(&sWifiLinkSendLock) != 0) {
            if (WM_SetDCFData((void *)WifiLink_OnKeepAliveSent, c->targetBss.bssid, c->sendBuf, 0) != 2) {
                WifiLink_UnlockFromIrq(&sWifiLinkSendLock);
            }
        }
    }
}

u8 *WifiLink_GetConnectedBssid() {
    u8 *r5 = 0;
    WifiLinkWork *c = WifiLink_GetWork();
    u32 irq = OS_DisableInterrupts();
    if (c != 0 && c->phase == 9 && c->isResetting == 0) {
        r5 = c->targetBss.bssid;
    }
    OS_RestoreInterrupts(irq);
    return r5;
}

u8 *WifiLink_GetConnectedSsid(u16 *out) {
    u8 *r7 = 0;
    u32 r6 = 0;
    WifiLinkWork *c = WifiLink_GetWork();
    u32 irq = OS_DisableInterrupts();
    if (c != 0 && c->phase == 9 && c->isResetting == 0) {
        r7 = c->targetBss.ssid;
        r6 = c->targetBss.ssidLength;
    }
    OS_RestoreInterrupts(irq);
    if (out != 0) {
        *out = r6;
    }
    return r7;
}

void WifiLink_SetRecvCallback(WifiLinkRecvCallback cb) {
    u32 irq = OS_DisableInterrupts();
    sWifiLinkSendState.recvCallback = cb;
    OS_RestoreInterrupts(irq);
}

}
}

namespace N_a144 {



extern "C" {
extern WifiLinkWork *volatile sWifiLinkWork;
extern OSMutex sWifiLinkSendLock;
extern WifiLinkSendState sWifiLinkSendState;
extern OSThreadQueue sWifiLinkSendWaitQueue;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32);
void OS_IrqHandler(void);
void DC_InvalidateRange(void *, u32);
s32 WM_StartScanEx(void *, void *);
s32 WM_PowerOff(void *);
s32 WM_Init(void *, u32);
s32 WM_GetAllowedChannel(void);
s32 WM_Finish(void);
s32 WM_SetIndCallback(void *);
s32 WM_Enable(void *);
s32 OS_IsTickAvailable(void);
s32 OS_IsAlarmAvailable(void);
void MIi_CpuCopyFast(void *, void *, u32);
s32 WM_SetDCFData(void *, void *, void *, u32);

void WifiLink_ApplyConfig(WifiLinkConfig *, WifiLinkNotifyCallback);
void WifiLink_SetDefaultOptions(void);
void WifiLink_RestartKeepAliveAlarm(void);
WifiLinkWork *WifiLink_GetWork(void);
void WifiLink_InitSendState(void);

s32 WifiLink_CleanupAsync(void);
s32 WifiLink_StartupAsync(WifiLinkConfig *, WifiLinkNotifyCallback);
s32 WifiLink_Finish(void);
s32 WifiLink_Init(void *, u32);
void WifiApList_MoveToTail(WifiApListEntry *);
WifiApListEntry *WifiApList_FindById(u32);
WifiApListEntry *WifiApList_FindByBssid(void *);
WifiApListEntry *WifiApList_GetOldest(void);
WifiApListEntry *WifiApList_AllocEntry(void);
void *WifiLink_GetApListEntry(u32);
BOOL WifiLink_LockApList(BOOL);
u32 WifiLink_GetApListCount(void);
void WifiLink_ClearApList(void);
void WifiLink_UnlockFromIrq(OSMutex *);
BOOL WifiLink_TryLockFromIrq(OSMutex *);
void WifiLink_OnKeepAliveSent(void);
void WifiLink_OnSendDone(WMMsg *);









static inline u8 *Unk_ov065_0226a6b4_Data(WifiApListEntry *n)
{
    return n->bssDesc;
}















s32 WifiLink_SendFrame(u8 *a, void *b, u32 c)
{
    u32 e = OS_DisableInterrupts();
    if (WifiLink_GetWork() == NULL) {
        OS_RestoreInterrupts(e);
        return -1;
    }
    OS_LockMutex(&sWifiLinkSendLock);
    WifiLinkWork *s = WifiLink_GetWork();
    if (s == NULL) {
        OS_UnlockMutex(&sWifiLinkSendLock);
        OS_RestoreInterrupts(e);
        return -1;
    }
    if (s->phase != 9 || s->isResetting == 1) {
        OS_UnlockMutex(&sWifiLinkSendLock);
        OS_RestoreInterrupts(e);
        return -4;
    }
    MI_CpuCopy8(b, s->sendBuf, c);
    switch (WM_SetDCFData((void *)WifiLink_OnSendDone, a, s->sendBuf, (u16)c)) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    default:
        OS_UnlockMutex(&sWifiLinkSendLock);
        OS_RestoreInterrupts(e);
        return -5;
    case 2:
        break;
    }
    OS_SleepThread(&sWifiLinkSendWaitQueue);
    switch (sWifiLinkSendState.sendResult) {
    case 1:
    default:
        OS_UnlockMutex(&sWifiLinkSendLock);
        OS_RestoreInterrupts(e);
        return -5;
    case 0:
        OS_UnlockMutex(&sWifiLinkSendLock);
        OS_RestoreInterrupts(e);
        return c;
    }
}

void WifiLink_OnSendDone(WMMsg *p)
{
    if (p->id == 0x12) {
        sWifiLinkSendState.sendResult = p->errcode;
        if (p->errcode == 0) {
            WifiLink_RestartKeepAliveAlarm();
        }
        OS_WakeupThread(&sWifiLinkSendWaitQueue);
    }
}

void WifiLink_OnKeepAliveSent(void)
{
    WifiLink_UnlockFromIrq(&sWifiLinkSendLock);
}

BOOL WifiLink_TryLockFromIrq(OSMutex *m)
{
    OSThread *o = m->thread;
    if (o == NULL) {
        m->thread = (OSThread *)OS_IrqHandler;
        m->count = m->count + 1;
        return TRUE;
    }
    if (o == (OSThread *)OS_IrqHandler) {
        m->count = m->count + 1;
        return TRUE;
    }
    return FALSE;
}

void WifiLink_UnlockFromIrq(OSMutex *m)
{
    if (m->thread == (OSThread *)OS_IrqHandler) {
        m->count = m->count - 1;
        if (m->count == 0) {
            m->thread = NULL;
            OS_WakeupThread(&m->queue);
        }
    }
}

void WifiLink_ClearApList(void)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *s = WifiLink_GetWork();
    if (s == NULL) {
        OS_RestoreInterrupts(e);
        return;
    }
    WifiApList *list = s->apList;
    if (list != NULL && (s32)s->apListSize > 0) {
        MI_CpuFill8(list, 0, s->apListSize);
    }
    OS_RestoreInterrupts(e);
}

u32 WifiLink_GetApListCount(void)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *s = WifiLink_GetWork();
    u32 r = 0;
    if (s == NULL) {
        OS_RestoreInterrupts(e);
        return r;
    }
    WifiApList *list = s->apList;
    if (list != NULL && s->apListSize > 0xc) {
        r = list->count;
    }
    OS_RestoreInterrupts(e);
    return r;
}

BOOL WifiLink_LockApList(BOOL a)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *s = WifiLink_GetWork();
    if (s == NULL) {
        OS_RestoreInterrupts(e);
        return FALSE;
    }
    if (a != 0) {
        a = s->isApListLocked != 0 ? TRUE : FALSE;
        s->isApListLocked = 1;
    } else {
        a = s->isApListLocked != 0 ? TRUE : FALSE;
        s->isApListLocked = 0;
    }
    OS_RestoreInterrupts(e);
    return a;
}

void *WifiLink_GetApListEntry(u32 id)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *s = WifiLink_GetWork();
    if (s == NULL) {
        OS_RestoreInterrupts(e);
        return NULL;
    }
    WifiApListEntry *n = WifiApList_FindById(id);
    if (n == NULL) {
        OS_RestoreInterrupts(e);
        return NULL;
    }
    OS_RestoreInterrupts(e);
    return n->bssDesc;
}

void WifiLink_AddApListEntry(WMBssDesc *a, u32 b)
{
    WifiLinkWork *s = WifiLink_GetWork();
    if (s != NULL) {
        if (s->isApListLocked == 0) {
            if (a->gameInfoLength == 0) {
                WifiApListEntry *n = WifiApList_FindByBssid(a->bssid);
                if (n == NULL) {
                    n = WifiApList_AllocEntry();
                }
                if (n == NULL && s->apListReplaceOldest == 1) {
                    n = WifiApList_GetOldest();
                }
                if (n != NULL) {
                    n->linkLevel = b;
                    MIi_CpuCopyFast(a, n->bssDesc, 0xc0);
                    WifiApList_MoveToTail(n);
                }
            }
        }
    }
}

WifiApListEntry *WifiApList_AllocEntry(void)
{
    WifiLinkWork *s = WifiLink_GetWork();
    WifiApList *list = s->apList;
    WifiApListEntry *r = NULL;
    if (list != NULL && s->apListSize > 0xc) {
        u32 n = (s->apListSize - __builtin_offsetof(WifiApList, nodes)) / sizeof(WifiApListEntry);
        if (n != 0 && n > list->count) {
            s32 i = 0;
            for (i = 0; (u32)i < n; i++) {
                r = &list->nodes[i];
                if (r->inUse == 0) {
                    break;
                }
            }
            if ((u32)i < n) {
                r->inUse = 1;
                r->id = list->count;
                r->next = NULL;
                r->prev = list->tail;
                list->tail = r;
                if (r->prev != NULL) {
                    r->prev->next = r;
                } else {
                    list->head = r;
                }
                list->count = list->count + 1;
            }
        }
    }
    return r;
}

WifiApListEntry *WifiApList_GetOldest(void)
{
    WifiLinkWork *s = WifiLink_GetWork();
    WifiApList *list = s->apList;
    if (list != NULL && s->apListSize > 0xc) {
        return list->head;
    }
    return NULL;
}

WifiApListEntry *WifiApList_FindByBssid(void *key)
{
    WifiLinkWork *s = WifiLink_GetWork();
    WifiApList *list = s->apList;
    WifiApListEntry *n = NULL;
    if (key == NULL) {
        return n;
    }
    if (list != NULL && s->apListSize > 0xc) {
        for (n = list->head; n != NULL; n = n->next) {
            if (WifiAp_MacEquals(Unk_ov065_0226a6b4_Data(n) + 4, (u8 *)key) != 0) {
                break;
            }
        }
    }
    return n;
}

WifiApListEntry *WifiApList_FindById(u32 id)
{
    WifiLinkWork *s = WifiLink_GetWork();
    WifiApList *list = s->apList;
    WifiApListEntry *n = NULL;
    if (list != NULL && s->apListSize > 0xc) {
        for (n = list->head; n != NULL; n = n->next) {
            if (n->id == id) {
                break;
            }
        }
    }
    return n;
}

void WifiApList_MoveToTail(WifiApListEntry *node)
{
    WifiLinkWork *s = WifiLink_GetWork();
    WifiApList *list = s->apList;
    if (node != NULL && list != NULL && s->apListSize > 0xc) {
        WifiApListEntry *c = list->head;
        for (; c != NULL; c = c->next) {
            if (c == node) {
                if (c->prev != NULL) {
                    c->prev->next = c->next;
                } else {
                    list->head = c->next;
                }
                if (c->next != NULL) {
                    c->next->prev = c->prev;
                } else {
                    list->tail = c->prev;
                }
                break;
            }
        }
        node->next = NULL;
        node->prev = list->tail;
        list->tail = node;
        if (node->prev != NULL) {
            node->prev->next = node;
        } else {
            list->head = node;
        }
        if (c == NULL) {
            node->id = list->count;
            list->count = list->count + 1;
        }
    }
}

s32 WifiLink_Init(void *a, u32 b)
{
    u32 e = OS_DisableInterrupts();
    if (sWifiLinkWork != NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    if (a == NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    if (((uptr)a & 0x1f) != 0) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    if (b < 0x2300) {
        OS_RestoreInterrupts(e);
        return 6;
    }
    sWifiLinkWork = (WifiLinkWork *)a;
    ((WifiLinkWork *)a)->phase = 1;
    sWifiLinkWork->pendingRequest = 0;
    sWifiLinkWork->scanPeriod = 0;
    sWifiLinkWork->isApListLocked = 0;
    sWifiLinkWork->isResetting = 0;
    sWifiLinkWork->aid = 0;
    sWifiLinkWork->connectFailStatus = 0;
    WifiLink_SetDefaultOptions();
    WifiLink_InitSendState();
    if (OS_IsTickAvailable() == 0) {
        OS_InitTick();
    }
    if (OS_IsAlarmAvailable() == 0) {
        OS_InitAlarm();
    }
    OS_CreateAlarm(&sWifiLinkWork->keepAliveAlarm);
    OS_RestoreInterrupts(e);
    return 0;
}

s32 WifiLink_Finish(void)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *g = sWifiLinkWork;
    if (g == NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    if (g->phase != 1) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    sWifiLinkWork = NULL;
    OS_RestoreInterrupts(e);
    return 0;
}

s32 WifiLink_StartupAsync(WifiLinkConfig *a, WifiLinkNotifyCallback b)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *g = sWifiLinkWork;
    if (g == NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    switch (g->phase) {
    case 1:
        WifiLink_ApplyConfig(a, b);
        break;
    case 2:
        OS_RestoreInterrupts(e);
        return 2;
    case 3:
        OS_RestoreInterrupts(e);
        return 0;
    default:
        OS_RestoreInterrupts(e);
        return 1;
    }
    WifiLinkWork *t = sWifiLinkWork;
    switch (WM_Init(t, (u16)t->dmaNo)) {
    case 3:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    case 4:
        OS_RestoreInterrupts(e);
        return 5;
    case 1:
    case 2:
    case 5:
    case 6:
    default:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    case 0:
        break;
    }
    if (WM_GetAllowedChannel() == 0) {
        if (WM_Finish() != 0) {
            WifiLink_SetPhase(0xb);
            OS_RestoreInterrupts(e);
            return 7;
        }
        OS_RestoreInterrupts(e);
        return 5;
    }
    if (WM_SetIndCallback((void *)WifiLink_OnWmIndication) != 0) {
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    }
    switch (WM_Enable((void *)WifiLink_OnWmCommand)) {
    case 2:
        WifiLink_SetPhase(2);
        sWifiLinkWork->pendingRequest = 1;
        break;
    case 8:
        WifiLink_SetPhase(0xc);
        OS_RestoreInterrupts(e);
        return 1;
    case 3:
    default:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    }
    OS_RestoreInterrupts(e);
    return 3;
}

s32 WifiLink_CleanupAsync(void)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *g = sWifiLinkWork;
    if (g == NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    switch (g->phase) {
    case 4:
        OS_RestoreInterrupts(e);
        return 2;
    case 1:
        OS_RestoreInterrupts(e);
        return 0;
    default:
        OS_RestoreInterrupts(e);
        return 1;
    case 3:
        break;
    }
    switch (WM_PowerOff((void *)WifiLink_OnWmCommand)) {
    case 2:
        WifiLink_SetPhase(4);
        sWifiLinkWork->pendingRequest = 2;
        break;
    case 8:
        OS_RestoreInterrupts(e);
        return 4;
    case 3:
    default:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    }
    OS_RestoreInterrupts(e);
    return 3;
}

s32 WifiLink_SearchAsync(const u8 *a, const u8 *b, s32 c)
{
    if (a == NULL || b == NULL) {
    }
    return WifiLink_BeginSearchAsync(a, b, c);
}

s32 WifiLink_BeginSearchAsync(const u8 *a, const u8 *b, s32 c)
{
    u32 e = OS_DisableInterrupts();
    WifiLinkWork *g = sWifiLinkWork;
    if (g == NULL) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    switch (g->phase) {
    case 5:
        WifiLink_SetupScanParams(a, b, c);
        OS_RestoreInterrupts(e);
        return 2;
    case 6:
        WifiLink_SetupScanParams(a, b, c);
        OS_RestoreInterrupts(e);
        return 0;
    default:
        OS_RestoreInterrupts(e);
        return 1;
    case 3:
        break;
    }
    WifiLink_SetupScanParams(a, b, c);
    {
        WifiLinkWork *t = sWifiLinkWork;
        DC_InvalidateRange(t->scanParam.scanBuf, t->scanParam.scanBufSize);
    }
    {
        u32 *cp = &sWifiLinkWork->scanCount;
        *cp = *cp + 1;
    }
    switch (WM_StartScanEx((void *)WifiLink_OnScanResult, &sWifiLinkWork->scanParam)) {
    case 2:
        WifiLink_SetPhase(5);
        sWifiLinkWork->pendingRequest = 3;
        break;
    case 8:
        OS_RestoreInterrupts(e);
        return 4;
    case 3:
    default:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(e);
        return 7;
    }
    OS_RestoreInterrupts(e);
    return 3;
}

}
}

namespace N_97ec {


typedef WifiLinkWork G;


extern "C" {
extern G *volatile sWifiLinkWork;

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
s32 WM_Reset(void *);
u32 WM_GetDispersionScanPeriod();
u16 *WMi_GetStatusAddress();
void DC_InvalidateRange(void *, u32);
s32 WM_Finish();
s32 WM_Disable(void *);
s32 WM_PowerOff(void *);
s32 WM_EndDCF(void *);
s32 WM_SetLifeTime(void *, u32, u32, u32, u32);
s32 func_02133150(s32, s32);

void WifiLink_SendKeepAlive();

void WifiLink_ResetOnError();
void WifiLink_OnKeepAliveAlarm();
void WifiLink_RestartKeepAliveAlarm();
void WifiLink_Notify(s32 a, s32 b, uptr c, uptr d, s32 e);
void WifiLink_SetDefaultOptions();
void WifiLink_ApplyConfig(WifiLinkConfig *, WifiLinkNotifyCallback);
WifiLinkWork *WifiLink_GetWork();
u32 WifiLink_UpdateOptions(u32);
u32 WifiLink_GetPhase();
s32 WifiLink_TerminateAsync();
s32 WifiLink_DisconnectAsync();
s32 WifiLink_ConnectAsync(u8 *, u8 *, u32);
void WifiLink_SetupScanParams(const u8 *a, const u8 *b, u32 c);
s32 WifiLink_EndSearchAsync();
}

s32 WifiLink_EndSearchAsync() {
    u32 irq = OS_DisableInterrupts();
    G *g = sWifiLinkWork;
    if (g == 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    switch (g->phase) {
    case 6:
        WifiLink_SetPhase(7);
        sWifiLinkWork->pendingRequest = 4;
        break;
    case 7:
        OS_RestoreInterrupts(irq);
        return 2;
    case 3:
        OS_RestoreInterrupts(irq);
        return 0;
    default:
        OS_RestoreInterrupts(irq);
        return 1;
    }
    OS_RestoreInterrupts(irq);
    return 3;
}

s32 WifiLink_ConnectAsync(u8 *a, u8 *b, u32 c) {
    u32 irq;
    G *g;
    s32 r;
    irq = OS_DisableInterrupts();
    g = sWifiLinkWork;
    if (g == 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    switch (g->phase) {
    case 3:
        if (a == 0) {
            OS_RestoreInterrupts(irq);
            return 1;
        }
        if (*(u16 *)(a + 0x3c) != 0) {
            OS_RestoreInterrupts(irq);
            return 1;
        }
        if (b != 0) {
            u32 x = b[0];
            if (x >= 4 || b[1] >= 4) {
                OS_RestoreInterrupts(irq);
                return 1;
            }
            g->wepMode = x;
            sWifiLinkWork->wepKeyId = b[1];
            g = sWifiLinkWork;
            if (g->wepMode == 0) {
                MI_CpuFill8(g->wepKeys, 0, 0x50);
            } else {
                MI_CpuCopy8(b + 2, g->wepKeys, 0x50);
            }
        } else {
            MI_CpuFill8(g->wepKeys, 0, 0x52);
        }
        MI_CpuCopy8(a, &sWifiLinkWork->targetBss, 0xc0);
        g = sWifiLinkWork;
        g->targetBss.rateSet.support = g->targetBss.rateSet.basic | 3;
        WifiLink_UpdateOptions(c);
        break;
    case 8:
        OS_RestoreInterrupts(irq);
        return 2;
    case 9:
        OS_RestoreInterrupts(irq);
        return 0;
    default:
        OS_RestoreInterrupts(irq);
        return 1;
    }
    r = WM_SetLifeTime((void *)WifiLink_OnWmCommand, 0xffff, 0x50, 0xffff, 0xffff);
    switch (r) {
    case 2:
        WifiLink_SetPhase(8);
        sWifiLinkWork->pendingRequest = 5;
        break;
    case 8:
        OS_RestoreInterrupts(irq);
        return 4;
    case 3:
    default:
        WifiLink_SetPhase(0xb);
        OS_RestoreInterrupts(irq);
        return 7;
    }
    OS_RestoreInterrupts(irq);
    return 3;
}

s32 WifiLink_DisconnectAsync() {
    u32 irq = OS_DisableInterrupts();
    G *g = sWifiLinkWork;
    s32 r;
    if (g == 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    switch (g->phase) {
    case 10:
        OS_RestoreInterrupts(irq);
        return 2;
    case 3:
        OS_RestoreInterrupts(irq);
        return 0;
    default:
        OS_RestoreInterrupts(irq);
        return 1;
    case 9:
        if (g->isResetting == 1) {
            WifiLink_SetPhase(0xa);
            sWifiLinkWork->pendingRequest = 6;
        } else {
            r = WM_EndDCF((void *)WifiLink_OnEndDcf);
            switch (r) {
            case 2:
                WifiLink_SetPhase(0xa);
                sWifiLinkWork->pendingRequest = 6;
                break;
            case 8:
                OS_RestoreInterrupts(irq);
                return 4;
            case 3:
            default:
                WifiLink_SetPhase(0xb);
                OS_RestoreInterrupts(irq);
                return 7;
            }
        }
        OS_RestoreInterrupts(irq);
        return 3;
    }
}

s32 WifiLink_TerminateAsync() {
    u32 irq = OS_DisableInterrupts();
    G *g = sWifiLinkWork;
    s32 r;
    if (g == 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    switch (g->phase) {
    case 13:
        OS_RestoreInterrupts(irq);
        return 2;
    case 1:
        OS_RestoreInterrupts(irq);
        return 0;
    case 6:
        WifiLink_SetPhase(0xd);
        sWifiLinkWork->pendingRequest = 9;
        OS_RestoreInterrupts(irq);
        return 3;
    default:
        OS_RestoreInterrupts(irq);
        return 1;
    case 3:
    case 9:
    case 12:
        if (g->isResetting == 1) {
            WifiLink_SetPhase(0xd);
            sWifiLinkWork->pendingRequest = 9;
            goto done;
        } else {
            u16 *p = WMi_GetStatusAddress();
            DC_InvalidateRange(p, 2);
            switch (*p) {
            case 0:
                r = WM_Finish();
                if (r == 0) {
                    WifiLink_SetPhase(1);
                    sWifiLinkWork->pendingRequest = 0;
                    OS_RestoreInterrupts(irq);
                    return 0;
                }
                break;
            case 1:
                r = WM_Disable((void *)WifiLink_OnWmCommand);
                break;
            case 2:
                r = WM_PowerOff((void *)WifiLink_OnWmCommand);
                break;
            default:
                sWifiLinkWork->isResetting = 1;
                r = WM_Reset((void *)WifiLink_OnReset);
                break;
            }
            switch (r) {
            case 2:
                WifiLink_SetPhase(0xd);
                sWifiLinkWork->pendingRequest = 9;
                goto done;
            case 8:
                OS_RestoreInterrupts(irq);
                return 4;
            case 3:
            default:
                WifiLink_SetPhase(0xb);
                OS_RestoreInterrupts(irq);
                return 7;
            }
        }
    }
done:
    OS_RestoreInterrupts(irq);
    return 3;
}

u32 WifiLink_GetPhase() {
    u32 irq = OS_DisableInterrupts();
    u32 r = 0;
    G *g = sWifiLinkWork;
    if (g != 0) {
        r = g->phase;
    }
    OS_RestoreInterrupts(irq);
    return r;
}

u32 WifiLink_UpdateOptions(u32 v) {
    u32 irq = OS_DisableInterrupts();
    u32 m = 0;
    G *g = sWifiLinkWork;
    u32 old = g->options;
    if (g == 0) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    if ((v & 0x8000) != 0) {
        m |= 0x3ffe;
        if ((v & 0x3ffe) == 0) v |= 0xa082;
    }
    if ((v & 0x20000) != 0) m |= 0x10000;
    if ((v & 0x80000) != 0) m |= 0x40000;
    if ((v & 0x200000) != 0) m |= 0x100000;
    if ((v & 0x800000) != 0) m |= 0x400000;
    g->options = v | (old & ~m);
    OS_RestoreInterrupts(irq);
    return old;
}

WifiLinkWork *WifiLink_GetWork() {
    return sWifiLinkWork;
}

void WifiLink_ApplyConfig(WifiLinkConfig *p, WifiLinkNotifyCallback arg) {
    if (p == 0) {
        sWifiLinkWork->dmaNo = 3;
        sWifiLinkWork->apList = 0;
        sWifiLinkWork->apListSize = 0;
        sWifiLinkWork->apListReplaceOldest = 0;
    } else {
        uptr t4;
        sWifiLinkWork->dmaNo = p->dmaNo & 3;
        t4 = (uptr)p->bssDescBuffer;
        if (((4 - (t4 & 3)) & 3) + 0xc > (u32)p->bssDescBufferSize) {
            sWifiLinkWork->apList = 0;
            sWifiLinkWork->apListSize = 0;
        } else {
            sWifiLinkWork->apList = (WifiApList *)((t4 + 3) & ~(uptr)3);
            sWifiLinkWork->apListSize = p->bssDescBufferSize - ((4 - (t4 & 3)) & 3);
            MI_CpuFill8((void *)sWifiLinkWork->apList, 0, sWifiLinkWork->apListSize);
        }
        sWifiLinkWork->apListReplaceOldest = p->bssDescMode;
    }
    sWifiLinkWork->notifyCallback = arg;
}

void WifiLink_SetupScanParams(const u8 *a, const u8 *b, u32 c) {
    G *g;
    u32 t;
    WifiLink_UpdateOptions(c);
    g = sWifiLinkWork;
    g->scanParam.scanBuf = (WMBssDesc *)g->wmBuf;
    sWifiLinkWork->scanParam.scanBufSize = 0x400;
    sWifiLinkWork->scanParam.channelList = (1 << WifiLink_NextAllowedChannel(0)) >> 1;
    t = sWifiLinkWork->scanPeriod;
    if (t == 0) t = WM_GetDispersionScanPeriod();
    g = sWifiLinkWork;
    g->scanParam.maxChannelTime = t;
    g = sWifiLinkWork;
    g->scanParam.scanType = (g->options & 0x300000) != 0x300000 ? 1 : 0;
    if (a == 0) {
        MI_CpuCopy8(gWifiLinkAnyBssid, sWifiLinkWork->scanParam.bssid, 6);
    } else {
        MI_CpuCopy8(a, sWifiLinkWork->scanParam.bssid, 6);
    }
    if (b == 0 || b == gWifiLinkAnySsid) {
        MI_CpuCopy8(gWifiLinkAnySsid, sWifiLinkWork->scanParam.ssid, 0x20);
        sWifiLinkWork->scanParam.ssidLength = 0;
    } else {
        s32 n;
        MI_CpuCopy8(b, sWifiLinkWork->scanParam.ssid, 0x20);
        n = 0;
        for (;;) {
            if (*b == 0) break;
            b++;
            n++;
            if (n >= 0x20) break;
        }
        sWifiLinkWork->scanParam.ssidLength = n;
    }
    sWifiLinkWork->scanCount = 0;
}

void WifiLink_SetDefaultOptions() {
    sWifiLinkWork->options = 0xaaa082;
}

u32 WifiLink_NextAllowedChannel(s32 a) {
    s32 i = 0;
    s32 c = a;
    u32 mask = sWifiLinkWork->options;
    do {
        if ((mask & (1 << (c % 13 + 1))) != 0) break;
        c++;
        i++;
    } while (i < 13);
    return (u16)((a + i) % 13 + 1);
}

void WifiLink_NotifyRequest(s32 a, void *b, s32 c, s32 d) {
    G *g = sWifiLinkWork;
    s32 old = g->pendingRequest;
    g->pendingRequest = 0;
    WifiLink_Notify(old, a, (uptr)b, c, d);
}

void WifiLink_Notify(s32 a, s32 b, uptr c, uptr d, s32 e) {
    G *g = sWifiLinkWork;
    WifiLinkNotifyCallback *cb = &g->notifyCallback;
    if (*cb != 0) {
        WifiLinkEvent ev;
        ev.request = a;
        ev.result = b;
        ev.bssDesc = (WMBssDesc *)c;
        ev.detail = (u32)d;
        ev.sourceLine = e;
        (*cb)(&ev);
    }
}

void WifiLink_SetPhase(s32 st) {
    u32 irq = OS_DisableInterrupts();
    G *g = sWifiLinkWork;
    if (g->phase == 9 && st != 9) {
        OS_CancelAlarm(&g->keepAliveAlarm);
    }
    g = sWifiLinkWork;
    if (g->phase != 0xb) {
        g->phase = st;
    }
    if (st == 9) {
        g = sWifiLinkWork;
        OS_SetAlarm(&g->keepAliveAlarm, 0x22f5341, (void (*)(void *))WifiLink_OnKeepAliveAlarm, NULL);
    }
    OS_RestoreInterrupts(irq);
}

void WifiLink_RestartKeepAliveAlarm() {
    u32 irq = OS_DisableInterrupts();
    G *g = sWifiLinkWork;
    OS_CancelAlarm(&g->keepAliveAlarm);
    g = sWifiLinkWork;
    if (g->phase == 9) {
        OS_SetAlarm(&g->keepAliveAlarm, 0x22f5341, (void (*)(void *))WifiLink_OnKeepAliveAlarm, NULL);
    }
    OS_RestoreInterrupts(irq);
}

void WifiLink_OnKeepAliveAlarm() {
    WifiLink_SendKeepAlive();
    WifiLink_RestartKeepAliveAlarm();
}

void WifiLink_ResetOnError() {
    G *g = sWifiLinkWork;
    if (g->isResetting == 0) {
        g->isResetting = 1;
        if (WM_Reset((void *)WifiLink_OnReset) != 2) {
            WifiLink_SetPhase(0xb);
            WifiLink_NotifyRequest(7, 0, 0, 0x611);
        }
    }
}

}

namespace N_8ec8 {


struct WifiLinkDcfFrame;
struct WifiLinkWmCallbackArg {
    u16 apiid;
    u16 errcode;
    u16 h4;
    u16 h6;
    union {
        struct {
            u16 h8;
            u16 ha;
            u16 hc;
            u16 he;
        };
        WifiLinkDcfFrame *dcfFrame;
        u8 *dcfBuf;
    };
};

struct WifiLinkDcfFrame {
    u8 pad_00[0xe];
    u16 he;
};



extern "C" {

extern WifiLinkWork *volatile sWifiLinkWork;

void WifiLink_Notify(s32 a, s32 b, uptr c, uptr d, s32 e);
void WifiLink_ResetOnError();
u32 WifiLink_CountBits(u32);
u32 WifiLink_CountLeadingZeros(u32);
void DC_InvalidateRange(void *, u32);
s32 WM_Disconnect(void *, u32);
s32 WM_StartDCF(void *, void *, u32);
s32 WM_StartScanEx(void *, void *);
s32 WM_EndScan(void *);
s32 WM_PowerOn(void *);
s32 WM_Finish();
s32 WM_Disable(void *);
s32 WM_SetBeaconIndication(void *, u32);
s32 WM_SetWEPKeyEx(void *, u32, u32, void *);
s32 WM_StartConnectEx(void *, void *, u32, u32, u32);

void WifiLink_OnDcfEvent(WifiLinkWmCallbackArg *m);
void WifiLink_OnDisconnect(WifiLinkWmCallbackArg *m);
void WifiLink_OnEndScan(WifiLinkWmCallbackArg *m);










void WifiLink_OnWmIndication(WifiLinkWmCallbackArg *m) {
    if (m->errcode == 8 && m->h4 == 0x16 && m->h6 == 0x25) {
        switch (sWifiLinkWork->phase) {
        case 8:
            WifiLink_SetPhase(0xc);
            break;
        case 9:
        case 12:
            WifiLink_ResetOnError();
            break;
        case 10:
            WifiLink_SetPhase(0xc);
            break;
        case 11:
            break;
        }
    }
}

void WifiLink_OnWmCommand(WifiLinkWmCallbackArg *m) {
    s32 res = 0x14;
    switch (m->errcode) {
    case 0: {
        switch (m->apiid) {
        case 3:
            res = WM_PowerOn((void *)WifiLink_OnWmCommand);
            break;
        case 4: {
            s32 r = WM_Finish();
            switch (r) {
            case 0:
                WifiLink_SetPhase(1);
                WifiLink_NotifyRequest(0, 0, 0, 0x663);
                return;
            case 4:
            default:
                WifiLink_SetPhase(0xb);
                WifiLink_NotifyRequest(7, 0, 0, 0x66a);
                return;
            }
        }
        case 5:
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(0, 0, 0, 0x670);
            return;
        case 6:
            res = WM_Disable((void *)WifiLink_OnWmCommand);
            break;
        case 0x1d:
            res = WM_SetBeaconIndication((void *)WifiLink_OnWmCommand, 0);
            break;
        case 0x19: {
            WifiLinkWork *g = sWifiLinkWork;
            res = WM_SetWEPKeyEx((void *)WifiLink_OnWmCommand, g->wepMode, g->wepKeyId, g->wepKeys);
            break;
        }
        case 0x27: {
            WifiLinkWork *g = sWifiLinkWork;
            u32 t = g->options;
            s32 a0;
            u32 b;
            if ((t & 0xc0000) == 0xc0000) a0 = 1; else a0 = 0;
            u16 a = a0;
            if ((t & 0x30000) != 0x30000) b = 1; else b = 0;
            res = WM_StartConnectEx((void *)WifiLink_OnConnectEvent, &g->targetBss, 0, b, a);
            break;
        }
        }
        if (res == 2) {
            return;
        }
        if (res == 3) goto e3;
        if (res != 8) goto e3;
        WifiLink_SetPhase(0xc);
        WifiLink_NotifyRequest(1, sWifiLinkWork->pendingRequest == 5 ? &sWifiLinkWork->targetBss : 0, 0, 0x6a7);
        return;
    e3:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, sWifiLinkWork->pendingRequest == 5 ? &sWifiLinkWork->targetBss : 0, 0, 0x6b0);
        return;
    }
    case 1:
        WifiLink_SetPhase(0xc);
        WifiLink_NotifyRequest(1, sWifiLinkWork->pendingRequest == 5 ? &sWifiLinkWork->targetBss : 0, 0, 0x6d0);
        return;
    case 2:
    case 3:
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, sWifiLinkWork->pendingRequest == 5 ? &sWifiLinkWork->targetBss : 0, 0, 0x6da);
        return;
    }
}

void WifiLink_OnScanResult(WMStartScanExCallback *m) {
    s32 res = 0x14;
    switch (m->errcode) {
    case 0: {
        if (sWifiLinkWork->phase == 5) {
            WifiLink_SetPhase(6);
            WifiLink_NotifyRequest(0, 0, 0, 0x6f6);
        }
        switch (sWifiLinkWork->phase) {
        case 6: {
            sWifiLinkWork->pendingRequest = 7;
            if (m->state == 5) {
                s32 i;
                DC_InvalidateRange(sWifiLinkWork->scanParam.scanBuf, sWifiLinkWork->scanParam.scanBufSize);
                for (i = 0; i < (s32)m->bssDescCount; i++) {
                    WifiLink_AddApListEntry(m->bssDesc[i], m->linkLevel[i]);
                    WifiLink_Notify(7, 0, (uptr)m->bssDesc[i], (uptr)m, 0x70b);
                }
            }
            u32 t = sWifiLinkWork->options;
            if ((t & 0xc00000) == 0xc00000) {
                u32 cnt = WifiLink_CountBits(t & 0x3ffe);
                if (cnt != 0) {
                    u32 x = sWifiLinkWork->scanCount;
                    if (DS_UMOD(x, cnt) == 0) {
                        WifiLink_Notify(8, 0, x, 0, 0x718);
                    }
                }
            }
            {
                u32 n = WifiLink_CountLeadingZeros(m->channelList);
                u32 k = WifiLink_NextAllowedChannel((u16)(32 - n));
                sWifiLinkWork->scanParam.channelList = (s16)((1 << k) >> 1);
            }
            DC_InvalidateRange(sWifiLinkWork->scanParam.scanBuf, sWifiLinkWork->scanParam.scanBufSize);
            sWifiLinkWork->scanCount++;
            res = WM_StartScanEx((void *)WifiLink_OnScanResult, &sWifiLinkWork->scanParam);
            break;
        }
        case 7:
            res = WM_EndScan((void *)WifiLink_OnEndScan);
            break;
        case 0xd:
            WifiLink_ResetOnError();
            return;
        default:
            break;
        }
        if (res == 2) {
            return;
        }
        if (res == 3) goto e3;
        if (res != 8) goto e3;
        WifiLink_SetPhase(0xc);
        WifiLink_NotifyRequest(1, 0, 0, 0x743);
        return;
    e3:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, 0, 0, 0x74c);
        return;
    }
    case 1:
        WifiLink_ResetOnError();
        return;
    case 2:
    case 3:
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, 0, 0, 0x75d);
        return;
    }
}

void WifiLink_OnEndScan(WifiLinkWmCallbackArg *m) {
    switch (m->errcode) {
    case 0:
        WifiLink_SetPhase(3);
        WifiLink_NotifyRequest(0, 0, 0, 0x774);
        return;
    case 1:
        WifiLink_ResetOnError();
        return;
    case 2:
    case 3:
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, 0, 0, 0x784);
        return;
    }
}

void WifiLink_OnConnectEvent(WifiLinkWmCallbackArg *m) {
    switch (m->errcode) {
    case 0:
        switch (m->h8) {
        case 8:
        case 9: {
            WifiLinkWork *g = sWifiLinkWork;
            switch (g->phase - 8) {
            case 2:
                g->aid = 0;
            case 0:
                WifiLink_SetPhase(0xc);
                break;
            case 1:
                g->aid = 0;
                sWifiLinkWork->pendingRequest = 6;
            case 4:
                WifiLink_ResetOnError();
                break;
            case 3:
                break;
            }
            break;
        }
        case 7: {
            if (sWifiLinkWork->phase == 0xc) {
                WifiLink_SetPhase(8);
                WifiLink_ResetOnError();
                return;
            }
            u32 v = m->ha;
            if (v >= 1 && v <= 0x7d7) {
                sWifiLinkWork->aid = v;
                s32 r = WM_StartDCF((void *)WifiLink_OnDcfEvent, sWifiLinkWork->wmBuf, 0x620);
                if (r == 2) {
                    return;
                }
                if (r == 3) goto e3;
                if (r != 8) goto e3;
                WifiLink_SetPhase(0xc);
                WifiLink_NotifyRequest(1, &sWifiLinkWork->targetBss, 0, 0x7d7);
                return;
            e3:
                WifiLink_SetPhase(0xb);
                WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x7e0);
                return;
            }
            WifiLink_ResetOnError();
            return;
        }
        case 6:
            break;
        case 0: case 1: case 2: case 3: case 4: case 5:
        default:
            WifiLink_SetPhase(0xb);
            WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, m->h8, 0x7ee);
            return;
        }
        break;
    case 1:
        sWifiLinkWork->connectFailStatus = m->he;
    case 6:
    case 11:
    case 12:
        WifiLink_SetPhase(8);
        WifiLink_ResetOnError();
        return;
    case 2: case 3: case 4: case 5: case 7: case 8: case 9: case 10:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x804);
        return;
    }
}

void WifiLink_OnDisconnect(WifiLinkWmCallbackArg *m) {
    switch (m->errcode) {
    case 0: {
        WifiLinkWork *g = sWifiLinkWork;
        if (g->phase == 0xc) {
            WifiLink_SetPhase(0xa);
            WifiLink_ResetOnError();
            return;
        }
        g->aid = 0;
        WifiLink_SetPhase(3);
        WifiLink_NotifyRequest(0, &sWifiLinkWork->targetBss, 0, 0x827);
        return;
    }
    case 1:
    case 3:
        WifiLink_SetPhase(0xa);
        WifiLink_ResetOnError();
        return;
    case 2:
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x839);
        return;
    }
}

void WifiLink_OnDcfEvent(WifiLinkWmCallbackArg *m) {
    switch (m->errcode) {
    case 0:
        switch (m->h4) {
        case 0xe:
            if (sWifiLinkWork->phase == 0xc) {
                WifiLink_SetPhase(8);
                WifiLink_ResetOnError();
                return;
            }
            WifiLink_SetPhase(9);
            WifiLink_NotifyRequest(0, &sWifiLinkWork->targetBss, 0, 0x85d);
            return;
        case 0xf: {
            WifiLinkDcfFrame *p = m->dcfFrame;
            WifiLink_AddRssiSample((u8)(p->he >> 8));
            DC_InvalidateRange(m->dcfBuf, 0x620);
            WifiLink_OnFrameReceived(m->dcfBuf);
            return;
        }
        default:
            WifiLink_SetPhase(0xb);
            WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, m->h4, 0x86b);
            return;
        }
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x877);
    }
}

void WifiLink_OnEndDcf(WifiLinkWmCallbackArg *m) {
    switch (m->errcode) {
    case 0: {
        if (sWifiLinkWork->phase == 0xc) {
            WifiLink_SetPhase(0xa);
            WifiLink_ResetOnError();
            return;
        }
        s32 r = WM_Disconnect((void *)WifiLink_OnDisconnect, 0);
        if (r == 2) {
            return;
        }
        if (r == 3) goto b3;
        if (r != 8) goto b0;
        WifiLink_SetPhase(0xc);
        WifiLink_NotifyRequest(1, &sWifiLinkWork->targetBss, 0, 0x8a0);
        return;
    b3:
        WifiLink_SetPhase(0xa);
        WifiLink_ResetOnError();
        return;
    b0:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x8ac);
        return;
    }
    case 1:
    case 3:
        WifiLink_SetPhase(0xa);
        WifiLink_ResetOnError();
        return;
    case 2:
    case 4:
    default:
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, 0, 0x8bf);
        return;
    }
}

}
}

namespace N_8470 {


extern "C" {
extern WifiLinkWork *volatile sWifiLinkWork;
s32 WM_StartConnectEx(void *cb, void *buf, u32 a, u32 b, u32 c);
s32 WM_PowerOff(void *cb);

void WifiLink_OnReset(WMMsg *m)
{
    if (m->errcode == 0) {
        sWifiLinkWork->isResetting = 0;
        sWifiLinkWork->aid = 0;
        switch (sWifiLinkWork->phase) {
        case 5:
        case 6:
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(1, 0, 0, 0x8e1);
            break;
        case 7:
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(0, 0, 0, 0x8e7);
            break;
        case 8: {
            u32 old;
            u32 w;
            u32 x;
            u32 y;
            u16 xs;
            s32 r;
            old = sWifiLinkWork->connectFailStatus;
            sWifiLinkWork->connectFailStatus = 0;
            if (old == 0x12) {
                WifiLinkWork *g = sWifiLinkWork;
                if ((g->targetBss.rateSet.support & 0x24) != 0x24) {
                    x = 0;
                    g->targetBss.rateSet.support |= 0x24;
                    w = sWifiLinkWork->options;
                    if ((w & 0xc0000) == 0xc0000) {
                        x = 1;
                    }
                    xs = x;
                    if ((w & 0x30000) == 0x30000) {
                        y = 0;
                    } else {
                        y = 1;
                    }
                    r = WM_StartConnectEx((void *)WifiLink_OnConnectEvent, &sWifiLinkWork->targetBss, 0, y, xs);
                    if (r == 2) {
                        break;
                    }
                    if (r != 3 && r == 8) {
                        WifiLink_SetPhase(0xc);
                        WifiLink_NotifyRequest(1, &sWifiLinkWork->targetBss, old, 0x905);
                    } else {
                        WifiLink_SetPhase(0xb);
                        WifiLink_NotifyRequest(7, &sWifiLinkWork->targetBss, old, 0x90c);
                    }
                    break;
                }
            }
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(1, &sWifiLinkWork->targetBss, old, 0x913);
            break;
        }
        case 9:
        case 12:
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(0, &sWifiLinkWork->targetBss, 1, 0x91b);
            break;
        case 10:
            WifiLink_SetPhase(3);
            WifiLink_NotifyRequest(0, &sWifiLinkWork->targetBss, 0, 0x922);
            break;
        case 13: {
            s32 r = WM_PowerOff((void *)WifiLink_OnWmCommand);
            if (r == 2) {
                break;
            }
            if (r != 3 && r == 8) {
                WifiLink_SetPhase(0xc);
                WifiLink_NotifyRequest(1, 0, 0, 0x930);
            } else {
                WifiLink_SetPhase(0xb);
                WifiLink_NotifyRequest(7, 0, 0, 0x939);
            }
            break;
        }
        default:
            WifiLink_SetPhase(0xb);
            WifiLink_NotifyRequest(7, 0, sWifiLinkWork->phase, 0x93f);
            break;
        }
    } else {
        WifiLink_SetPhase(0xb);
        WifiLink_NotifyRequest(7, 0, 0, 0x946);
    }
}
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02268c64) {
    HOST_OVERLAY_VAR(sWifiLinkSendState),
    HOST_OVERLAY_VAR(sWifiLinkWork),
    HOST_OVERLAY_VAR(sWifiLinkSendWaitQueue),
    HOST_OVERLAY_VAR(sWifiLinkSendLock),
    HOST_OVERLAY_VARS_END
};
