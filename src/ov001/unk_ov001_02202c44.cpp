#include "types.h"
#include "nitro/os_alarm.h"
#include "uptr.h"
#include "net/AossParam.h"
#include "nitro/wm.h"
#include "sys/OSMessageQueue.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/ov001/unk_ov001_02202c44.h"
#include "proto/ov001/unk_ov001_022032f8.h"

typedef void *(*AossAllocFunc)(u32);
typedef void (*AossFreeFunc)(void *);

struct AossRateEntry {
    u16 mask;
    u8 val;
};
#define data_ov001_0222c6ce (sAossWepDesc + 2)

extern "C" void *sAossWlanWork = 0;
extern "C" AossFreeFunc sAossFreeFunc = 0;
extern "C" AossAllocFunc sAossAllocFunc = 0;
extern "C" s32 (*sAossProgressCb)(s32) = 0;
extern "C" OSMessageQueue sAossMsgQueue = {};
extern "C" AossRateEntry sAossRateTable[12] = {
    {0x1, 2}, {0x2, 4}, {0x4, 0xb}, {0x8, 0xc}, {0x10, 0x12}, {0x20, 0x16}, {0x40, 0x18}, {0x80, 0x24},
    {0x100, 0x30}, {0x200, 0x48}, {0x400, 0x60}, {0x800, 0x6c},
};
extern "C" OSMessage sAossMsgArray[4] = {0};
extern "C" u8 sAossBssDesc[0xc0] = {0};
extern "C" u8 sAossWepDesc[0x74] = {0};

extern "C" {
u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
s32 OS_Sleep(s32);
BOOL OS_ReceiveMessage(OSMessageQueue *mq, OSMessage *msg, s32 flags);
BOOL OS_SendMessage(OSMessageQueue *mq, OSMessage msg, s32 flags);
void OS_InitMessageQueue(OSMessageQueue *mq, OSMessage *buf, s32 count);
void MIi_CpuClear16(u16, void *, u32);
void MIi_CpuCopy16(void *, void *, u32);
void MIi_CpuCopy32(void *, void *, u32);
void MI_CpuFill8(void *, s32, u32);
void MI_CpuCopy8(void *, void *, u32);

s32 Aoss_FreeScanBuffers();
s32 Aoss_SetProgress(s32);
s32 Aoss_RunProtocol(void *);
void Aoss_SocketClose(s32);
s32 WifiLink_ClearApList();
s32 WifiLink_Init(void *, s32);
s32 WifiLink_ConnectAsync(void *, void *, s32);
s32 WifiLink_CleanupAsync();
void Aoss_ConvertBssDesc(WMBssDesc *, AossApInfo *);

}

enum Loop_02203004 { LOOP_02203004_0 = 0 };

extern "C" void Aoss_ConvertBssDesc(WMBssDesc *a, AossApInfo *b) {
    b->ssidLength = a->ssidLength;
    MIi_CpuCopy16(a->ssid, b->ssid, 0x20);
    b->channel = a->channel;
    MIi_CpuCopy16(a->bssid, b->bssid, 6);
    s32 i;
    s32 n;
    n = 0;
    i = 0;
    AossRateEntry *e = sAossRateTable;
    for (; i < 12; e++, i++) {
        if (a->rateSet.support & e->mask) {
            b->rates[n] = e->val;
            if (a->rateSet.basic & e->mask) {
                b->rates[n] |= 0x80;
            }
            n++;
        }
    }
    b->numRates = n;
    b->beaconPeriod = a->beaconPeriod;
    u32 t = a->capaInfo & 3;
    if (t == 1) {
        b->bssType = 1;
    } else if (t == 2) {
        b->bssType = 2;
    } else {
        b->bssType = 0;
    }
}

extern "C" void Aoss_SetBssDescSsid(void *a, void *b) {
    volatile u16 z = 0;
    MIi_CpuClear16(z, (u8 *)b + 0xc, 0x20);
    *(u16 *)((u8 *)b + 0xa) = *(u32 *)a;
    MI_CpuCopy8((u8 *)a + 4, (u8 *)b + 0xc, *(u16 *)((u8 *)b + 0xa));
}

extern "C" void Aoss_StoreConnectResult(AossConnectResult *a, WMBssDesc *b, s32 c) {
    a->connected = c;
    Aoss_ConvertBssDesc(b, &a->ap);
}

extern "C" void Aoss_PostWcmMsg(s32 a) {
    OS_SendMessage(&sAossMsgQueue, (OSMessage)(sptr)a, 0);
}

extern "C" void Aoss_PostAlarmMsg(void *a) {
    OS_SendMessage(&sAossMsgQueue, a, 0);
}

extern "C" s32 Aoss_WlanStartup(AossAllocFunc a, AossFreeFunc b) {
    s32 ok = 1;
    OSMessage msg;
    void *p;
    OS_InitMessageQueue(&sAossMsgQueue, sAossMsgArray, 4);
    if (a == 0 || b == 0) {
        return -1;
    }
    u32 irq = OS_DisableInterrupts();
    sAossAllocFunc = a;
    sAossFreeFunc = b;
    OS_RestoreInterrupts(irq);
    p = sAossAllocFunc(0x5890);
    sAossWlanWork = p;
    if (p == 0) {
        return -1;
    }
    if (Aoss_WcmInit((void *)Aoss_PostWcmMsg, p, 0x5890) == 0) {
        ok = 0;
    }
    if (ok != 0) {
        do {
            OS_ReceiveMessage(&sAossMsgQueue, &msg, 1);
            switch ((sptr)msg) {
            case 4:
            case 5:
                break;
            case 6:
                return 0;
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            default:
                ok = 0;
                break;
            }
        } while (ok != 0);
    }
    sAossFreeFunc(sAossWlanWork);
    return -1;
}

extern "C" s32 Aoss_WlanShutdown() {
    s32 r4 = 1;
    s32 res = -1;
    OSMessage msg;
    if (sAossFreeFunc == 0) {
        return res;
    }
    if (Aoss_WcmCleanup() == 0) {
        return -1;
    }
    do {
        OS_ReceiveMessage(&sAossMsgQueue, &msg, 1);
        switch ((sptr)msg) {
        case 20:
            r4 = 0;
            res = r4;
            sAossFreeFunc(sAossWlanWork);
            break;
        case 4:
        case 5:
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        default:
            r4 = 0;
            break;
        }
    } while (r4 != 0);
    u32 irq = OS_DisableInterrupts();
    sAossAllocFunc = 0;
    sAossFreeFunc = 0;
    OS_RestoreInterrupts(irq);
    return res;
}

extern "C" s32 Aoss_WlanDisconnect() {
    Loop_02203004 loop;
    s32 res = -1;
    OSMessage msg;
    if (Aoss_WcmDisconnect()) {
        loop = LOOP_02203004_0;
        do {
            OS_ReceiveMessage(&sAossMsgQueue, &msg, 1);
            switch ((sptr)msg) {
            case 14:
                res = loop;
                break;
            default:
                break;
            }
        } while (loop);
    }
    return res;
}

extern "C" s32 Aoss_ScanAps(void **out) {
    s32 r6 = 0;
    s32 res = -1;
    s32 loop = 1;
    s32 r7 = r6;
    s32 r5 = r6;
    void *buf;
    u8 *r4;
    OSMessage msg;
    OSAlarm alarm;
    if (sAossAllocFunc == 0 || sAossFreeFunc == 0) {
        return -1;
    }
    r4 = (u8 *)sAossAllocFunc(0x3000);
    if (r4 == 0) {
        return -1;
    }
    buf = r4;
    if (Aoss_WcmStartSearch(NULL, NULL, 0, 0x30bffe)) {
        OS_CreateAlarm(&alarm);
        OS_SetAlarm(&alarm, 0x3fec42, Aoss_PostAlarmMsg, (void *)0x13);
        do {
            OS_ReceiveMessage(&sAossMsgQueue, &msg, 1);
            switch ((sptr)msg) {
            case 19:
                if (r6 == 0) {
                    if (r5 != 0) {
                        r7 = Aoss_WcmReadApList(r4, 0x40);
                    }
                    if (Aoss_WcmEndSearch() == 0) {
                        goto done;
                    }
                    r6 = 1;
                }
                break;
            case 5:
                if (r6 == 0) {
                    if (r5 < 8) {
                        r5++;
                    } else {
                        r7 = Aoss_WcmReadApList(r4, 0x40);
                        if (Aoss_WcmEndSearch() == 0) {
                            goto done;
                        }
                        r6 = 1;
                    }
                }
                break;
            case 10:
                loop = 0;
                res = 0;
                break;
            case 4:
            case 8:
            case 18:
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 6:
            case 7:
            case 9:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            default:
                goto done;
            }
        } while (loop != 0);
        {
            u8 *p;
            if (r7 != 0) {
                p = (u8 *)sAossAllocFunc((r7 - 1) * 0x54 + 0x58);
                if (p == 0) {
                    goto done;
                }
            } else {
                p = (u8 *)sAossAllocFunc(0x58);
                if (p == 0) {
                    goto done;
                }
            }
            *out = p;
            *(s32 *)p = r7;
            r6 = 0;
            if (r7 > 0) {
                u8 *q = p + 4;
                do {
                    Aoss_ConvertBssDesc((WMBssDesc *)r4, (AossApInfo *)q);
                    r4 += 0xc0;
                    q += 0x54;
                    r6++;
                } while (r6 < r7);
            }
        }
    done:
        OS_CancelAlarm(&alarm);
        do {
        } while (OS_ReceiveMessage(&sAossMsgQueue, &msg, 0) == 1);
    }
    sAossFreeFunc(buf);
    return res;
}

extern "C" s32 Aoss_ConnectAp(AossApConfig *a, AossConnectResult *b) {
    s32 r4;
    s32 res;
    s32 cnt;
    s32 got;
    u32 r6;
    r4 = 1;
    got = 0;
    res = -1;
    if (a->mode == 0) {
        r6 = 0x80000;
    } else if (a->mode == 1) {
        r6 = 0xc0000;
    }
    MI_CpuFill8(sAossWepDesc, 0, 0x60);
    if (a->wepKeyLength == 5) {
        sAossWepDesc[0] = 1;
    } else if (a->wepKeyLength == 0xd) {
        sAossWepDesc[0] = 2;
    } else if (a->wepKeyLength == 0x10) {
        sAossWepDesc[0] = 3;
    } else {
        return -1;
    }
    sAossWepDesc[1] = 0;
    MI_CpuCopy8(a->wepKey, data_ov001_0222c6ce, a->wepKeyLength);
    WifiLink_ClearApList();
    if (Aoss_WcmStartSearch(0, a->ssid, a->ssidLength, 0x30bffe)) {
        OSMessage msg;
        OSAlarm alarm;
        cnt = 0;
        OS_CreateAlarm(&alarm);
        OS_SetAlarm(&alarm, 0x3fec42, Aoss_PostAlarmMsg, (void *)0x12);
        r6 = r6 | 0x30000;
        s32 r5 = 0;
        do {
            OS_ReceiveMessage(&sAossMsgQueue, &msg, 1);
            switch ((sptr)msg) {
            case 18:
                if (got == 0) {
                    r4 = r5;
                }
                break;
            case 5:
                if (got == 0) {
                    OS_CancelAlarm(&alarm);
                    if (Aoss_WcmReadApList(sAossBssDesc, 1) != 1) {
                        r4 = r5;
                    } else {
                        Aoss_SetBssDescSsid(a, sAossBssDesc);
                        if (Aoss_WcmConnect(sAossBssDesc, sAossWepDesc, r6) == 0) {
                            r4 = r5;
                        } else {
                            got = 1;
                        }
                    }
                }
                break;
            case 10:
                Aoss_SetBssDescSsid(a, sAossBssDesc);
                if (Aoss_WcmConnect(sAossBssDesc, sAossWepDesc, r6) == 0) {
                    r4 = r5;
                }
                break;
            case 12:
                res = r5;
                r4 = r5;
                break;
            case 13:
                cnt++;
                if (cnt < 3) {
                    if (Aoss_WcmConnect(sAossBssDesc, sAossWepDesc, r6) == 0) {
                        r4 = r5;
                    }
                } else {
                    r4 = r5;
                }
                break;
            default:
                r4 = r5;
                break;
            case 4:
            case 8:
            case 19:
                break;
            }
        } while (r4 != 0);
        OS_CancelAlarm(&alarm);
        do {
        } while (OS_ReceiveMessage(&sAossMsgQueue, &msg, r5) == 1);
    }
    Aoss_StoreConnectResult(b, (WMBssDesc *)sAossBssDesc, res == 0);
    return res;
}

extern "C" s32 Aoss_Sleep(s32 a) {
    return OS_Sleep(a);
}




extern "C" s32 Aoss_NotifyProgress(s32 a) {
    if (sAossProgressCb) {
        sAossProgressCb(a);
    }
    return 0;
}

extern "C" void *Aoss_Alloc(u32 a) {
    return sAossAllocFunc(a);
}

extern "C" void Aoss_Free(void *a) {
    sAossFreeFunc(a);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02202c44) {
    HOST_OVERLAY_VAR(sAossWlanWork),
    HOST_OVERLAY_VAR(sAossFreeFunc),
    HOST_OVERLAY_VAR(sAossAllocFunc),
    HOST_OVERLAY_VAR(sAossProgressCb),
    HOST_OVERLAY_VAR(sAossMsgQueue),
    HOST_OVERLAY_VAR(sAossRateTable),
    HOST_OVERLAY_VAR(sAossMsgArray),
    HOST_OVERLAY_VAR(sAossBssDesc),
    HOST_OVERLAY_VAR(sAossWepDesc),
    HOST_OVERLAY_VARS_END
};
