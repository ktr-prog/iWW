#include "uptr.h"
#include "types.h"
#include "net/IpSocket.h"
#include "net/IpFragEntry.h"
#include "net/IpHeader.h"
#include "nitro/math.h"
#include "net/IpStackConfig.h"
#include "net/SslSession.h"
#include "net/SslConnection.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_02000b44.h"
#include "proto/ov065/unk_ov065_02261638.h"



struct ArpCacheEntry {
    s32 ipAddr;
    u8 macAddr[6];
    u16 lastUsed;
};

extern "C" {
int OS_IsThreadTerminated(OSThread *t);
void OS_Sleep(unsigned int msec);
void OS_WakeupThreadDirect(OSThread *t);
}

extern "C" {
void MI_CpuFill8(void *dst, u32 v, u32 n);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s64 _ll_mul(s64 a, s64 b);
}


extern "C" {

extern "C" u8 data_ov065_0228f3c0[0x800] = {0};
extern "C" u8 sIpRecvThreadStack[0x800] = {0};
extern "C" IpFragEntry sIpFragTable[8] = {};
extern "C" u8 sTimerThreadTxBuf[0x180] = {0};
extern "C" u8 sTimerThreadRxBuf[0x180] = {0};
extern "C" OSThread sIpTimerThread = {};
extern "C" OSThread sIpRecvThread = {};
extern "C" IpSocket sTimerThreadSoc = {};
extern "C" IpSocket sTcpResetSoc = {};
extern "C" ArpCacheEntry sArpCache[8] = {};
extern "C" u8 data_ov065_0228ec1c[0x3c] = {0};
extern "C" MATHRandContext32 sIpRandState = {0};
extern "C" u8 sLlcSnapHeader[12] = {0xaa, 0xaa, 3, 0, 0, 0, 8, 0, 0, 0, 0, 0};
extern "C" char sDhcpHostName[] = "NintendoDS";
extern "C" u32 sDnsServers[2] = {0};
extern "C" u8 sBroadcastMac[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0};
extern "C" u8 sOwnMac[6] = {0};
extern "C" u32 sRecvRingSize = 0;
extern "C" u32 sDhcpServerId = 0;
extern "C" OSThread *sRecvRingWaiter = 0;
extern "C" u32 sDhcpRequestedIp = 0;
extern "C" u32 sDhcpLeaseTime = 0;
extern "C" void (*sAddrConfiguredCallback)(void) = 0;
extern "C" u32 sIpTimerStopRequest = 0;
extern "C" void (*sIpFree)(void *) = 0;
extern "C" void (*sIpIdleCallback)(void) = 0;
extern "C" u32 sRecvRingWrite = 0;
extern "C" u32 sGateway = 0;
extern "C" u32 sDhcpRetryTime = 0;
extern "C" u32 sRecvRingRead = 0;
extern "C" u8 *sRecvRingBuf = 0;
extern "C" u32 sIpStackStatus = 0;
extern "C" u32 sIcmpEchoReplyEnabled = 1;
extern "C" s32 (*sIpLinkCheckCallback)(void) = 0;
extern "C" u32 sIpThreadPriority = 0x10;
extern "C" u32 sNetmask = 0;
extern "C" u32 sIpStackFlags = 0;
extern "C" void *(*sIpAlloc)(u32) = 0;
extern "C" u32 gOwnIp = 0;
extern "C" u32 sIpYieldMode = 0;
extern "C" u16 sIpIdCounter = 0;
extern "C" u16 sIcmpSeq = 0;
extern "C" u16 sMss = 0;
extern "C" u16 sNextEphemeralPort = 0;
extern "C" u8 sLinkSendError = 0;
extern "C" u8 sArpConflict = 0;













extern "C" {
extern u32 sGateway;
extern u32 sNetmask;
extern u32 gOwnIp;
extern u32 sIpThreadPriority;
extern OSThread sIpRecvThread;
extern OSThread sIpTimerThread;
extern u8 *sRecvRingBuf;
extern u32 sRecvRingSize;
extern void (*sIpIdleCallback)(void);
extern u32 sIpTimerStopRequest;
extern u32 sIpStackStatus;
extern u32 sDnsServers[2];
extern u32 sDhcpServerId;
extern ArpCacheEntry sArpCache[8];
extern OSThreadInfo data_021fcc2c;
extern IpFragEntry sIpFragTable[8];
extern void (*sIpFree)(void *);
extern u32 sIpYieldMode;
extern SslSession sSslSessionCache[4];
extern void *(*sIpAlloc)(u32);
extern s32 (*sIpLinkCheckCallback)(void);
extern u32 sIpStackFlags;
extern u16 sMss;
extern u32 sDhcpRequestedIp;
extern u32 sRecvRingRead;
extern u32 sRecvRingWrite;
extern u16 sNextEphemeralPort;
extern u8 sArpConflict;

void IpStack_RecvThreadMain(void);
void IpStack_TimerThreadMain(void);
u32 Ssl_EncryptRecord(void *, void *);
u8 *Tcp_Read(u32 *, IpSocket *);
void Tcp_Consume(u32, IpSocket *);
void Ssl_ProcessRecord(void *, void *);
s32 Ssl_ReadExact(void *, u32, IpSocket *);
u8 Ssl_ReadRecord(IpSocket *);

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32);
void OS_SetThreadPriority(OSThread *, u32);
void OS_JoinThread(OSThread *);
void OS_DestroyThread(OSThread *);
void OS_CreateThread(OSThread *, void *, u32, void *, u32, u32);
void OS_GetMacAddress(void *);

u32 Ip_ChecksumAdd(u8 *p, u32 len, u32 sum);
s32 Ip_IsOnLocalNet(u32 a);
s32 IpStack_RequestStop(void);
void Ssl_ClearSessionCache(void);
void Ssl_ReceiveRecordPart(IpSocket *o);
s32 IpStack_ReturnTrue(void);
void IpStack_Nop(void);
}

extern "C" {

extern "C" {
void IpStack_Nop(void);
s32 IpStack_ReturnTrue(void);
void IpStack_Init(IpStackConfig *c);
s32 IpStack_RequestStop(void);
void IpStack_SetIdleCallback(void (*f)(void));
void IpStack_Shutdown(void);
void IpStack_SetThreadPriority(u32 a);
u32 Ip_ChecksumAdd(u8 *p, u32 len, u32 sum);
u32 Ip_ChecksumFinish(u32 x);
u32 Ip_Checksum(u8 *a, u32 b);
s32 Ip_IsOnLocalNet(u32 a);
}

void IpStack_ResetAddress(u32 a) {
    BOOL f;
    if (gOwnIp != 0) {
        f = TRUE;
    } else {
        f = FALSE;
    }
    sIpStackStatus = a;
    gOwnIp = 0;
    sNetmask = 0;
    sGateway = 0;
    sDnsServers[0] = 0;
    sDnsServers[1] = 0;
    sDhcpServerId = 0;
    if (f) {
        MI_CpuFill8(sArpCache, 0, sizeof(sArpCache));
        {
            OSThread *t = data_021fcc2c.list;
            if (t != 0) {
                do {
                    IpSocket *s = (IpSocket *)t->specific[0];
                    if (s != 0) {
                        if (s->ownerThread != 0) {
                            if (s->state != 10 && s->state != 11) {
                                s->state = 0;
                            }
                            if (s->waitReason != 0) {
                                s->waitReason = 0;
                                OS_WakeupThreadDirect(s->ownerThread);
                            }
                        }
                    }
                    t = t->next;
                } while (t != 0);
            }
        }
        {
            s32 i;
            IpFragEntry *e;
            for (i = 0, e = sIpFragTable; i < 8; e++, i++) {
                if (e->cnt != 0) {
                    sIpFree(e->buf);
                    e->cnt = 0;
                }
            }
        }
        Ssl_ClearSessionCache();
    }
}

void IpStack_Yield(void) {
    if (sIpYieldMode == 0) {
        OS_YieldThread();
    } else {
        OS_Sleep(sIpYieldMode);
    }
}

void IpStack_Nop(void) {
}

s32 IpStack_ReturnTrue(void) {
    return 1;
}

void IpStack_Init(IpStackConfig *c) {
    OSi_ReferSymbol(0);
    u64 seed = *(u64 *)&c->randSeed;
    if (seed != 0) {
        sIpRandState.x = seed;
        sIpRandState.mul = 0x5d588b656c078965ULL;
        sIpRandState.add = 0x269ec3;
    } else {
        sIpRandState.x = OS_GetTick();
        sIpRandState.mul = 0x5d588b656c078965ULL;
        sIpRandState.add = 0x269ec3;
    }
    if (c->allocFunc != 0 && c->freeFunc != 0) {
        sIpAlloc = c->allocFunc;
        sIpFree = c->freeFunc;
    } else {
        sIpAlloc = (void *(*)(u32))IpStack_Nop;
        sIpFree = (void (*)(void *))IpStack_Nop;
    }
    sIpStackFlags = c->stackFlags;
    if (c->mss != 0) {
        sMss = c->mss;
    } else {
        sMss = 0x5b4;
    }
    sDhcpRequestedIp = c->requestedIp;
    sIpYieldMode = c->yieldMode;
    if (c->addrReadyCallback != 0) {
        sAddrConfiguredCallback = c->addrReadyCallback;
    } else {
        sAddrConfiguredCallback = IpStack_Nop;
    }
    if (c->linkCheckCallback != 0) {
        sIpLinkCheckCallback = c->linkCheckCallback;
    } else {
        sIpLinkCheckCallback = IpStack_ReturnTrue;
    }
    sRecvRingBuf = c->recvRingBuf;
    sRecvRingSize = c->recvRingSize;
    sRecvRingRead = 0;
    sRecvRingWrite = 0;
    {
        MATHRandContext32 *r = &sIpRandState;
        r->x = (u64)((s64)r->mul * (s64)r->x) + r->add;
        u32 hi = (u32)(r->x >> 32);
        sNextEphemeralPort = ((u64)((s64)hi * (s64)0xf88) >> 32) + 0x400;
    }
    OS_GetMacAddress(sOwnMac);
    sArpConflict = 0;
    OS_CreateThread(&sIpRecvThread, (void *)IpStack_RecvThreadMain, 0, sIpRecvThreadStack + 0x800, 0x800, sIpThreadPriority);
    OS_CreateThread(&sIpTimerThread, (void *)IpStack_TimerThreadMain, 0, data_ov065_0228f3c0 + 0x800, 0x800, sIpThreadPriority);
    OS_WakeupThreadDirect(&sIpRecvThread);
    OS_WakeupThreadDirect(&sIpTimerThread);
}

s32 IpStack_RequestStop(void) {
    u32 s = OS_DisableInterrupts();
    s32 r = OS_IsThreadTerminated(&sIpTimerThread);
    if (r == 0) {
        if (sIpTimerStopRequest == 0) {
            sIpTimerStopRequest = 1;
            OS_WakeupThreadDirect(&sIpTimerThread);
        }
    }
    OS_RestoreInterrupts(s);
    return r;
}

void IpStack_SetIdleCallback(void (*f)(void)) {
    sIpIdleCallback = f;
}

void IpStack_Shutdown(void) {
    IpStack_RequestStop();
    OS_JoinThread(&sIpTimerThread);
    OS_DestroyThread(&sIpRecvThread);
    sRecvRingWaiter = 0;
    IpStack_ResetAddress(0);
    sRecvRingBuf = 0;
    sRecvRingSize = 0;
}

void IpStack_SetThreadPriority(u32 a) {
    sIpThreadPriority = a;
    OS_SetThreadPriority(&sIpRecvThread, a);
    OS_SetThreadPriority(&sIpTimerThread, a);
}

u32 Ip_ChecksumAdd(u8 *p, u32 len, u32 sum) {
    u32 t;
    if (((uptr)p & 1) != 0) {
        while (len > 1) {
            t = (u16)((p[0] << 8) | p[1]);
            sum += t;
            p += 2;
            len -= 2;
        }
    } else {
        u32 w;
        u32 v;
        u16 h = sum;
        sum = (u16)((h >> 8) | (h << 8));
        while (len > 1) {
            w = *(u16 *)p;
            sum += w;
            p += 2;
            len -= 2;
        }
        v = ((sum >> 8) & 0xff00ff) | ((sum << 8) & 0xff00ff00);
        sum = (v >> 16) | (v << 16);
    }
    if (len != 0) {
        sum += p[0] << 8;
    }
    t = (sum & 0xffff) + (sum >> 16);
    t = t + (t >> 16);
    return (u16)t;
}

u32 Ip_ChecksumFinish(u32 x) {
    x = (u16)(x ^ 0xffff);
    if (x == 0) {
        x = 0xffff;
    }
    return x;
}

u32 Ip_Checksum(u8 *a, u32 b) {
    return Ip_ChecksumFinish((u16)Ip_ChecksumAdd(a, b, 0));
}

s32 Ip_VerifyPseudoChecksum(u8 *a, u32 b, u8 *c, u32 d) {
    u32 s = Ip_ChecksumAdd(a, b, d);
    s = Ip_ChecksumAdd(c + 0xc, 8, s);
    s += b;
    if ((s & 0x10000) != 0) {
        s = (s + 1) & 0xffff;
    }
    if (s != 0xffff) {
        return 1;
    }
    return 0;
}

s32 Ip_IsOnLocalNet(u32 a) {
    s32 r = TRUE;
    s32 z = 0;
    if (a != (u32)-1) {
        if (a != 0x7f000001) {
            u32 m = sNetmask;
            if ((a & m) != (gOwnIp & m)) {
                r = z;
            }
        }
    }
    return r;
}

u32 Ip_GetNextHop(u32 a) {
    if (Ip_IsOnLocalNet(a) == 0) {
        a = sGateway;
    }
    return a;
}


}



#define BS16(x) ((u16)((((s32)(x)) >> 8) | (((s32)(x)) << 8)))

extern "C" {
extern OSThreadInfo data_021fcc2c;
extern u8 sBroadcastMac[];
extern u8 sLlcSnapHeader[];
extern u8 sLinkSendError;
extern u16 sIcmpSeq;
extern u16 sIpIdCounter;
extern u32 sNetmask;
extern u32 sRecvRingWrite;
extern u32 gOwnIp;
extern u8 *sRecvRingBuf;
extern u32 sRecvRingSize;
extern u32 sRecvRingRead;
extern ArpCacheEntry sArpCache[8];

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);

s32 WifiLink_SendFrame(u8 *, void *, u32);
u32 Ip_Checksum(u8 *, u32);
u32 Ip_ChecksumFinish(u32);
u32 Ip_ChecksumAdd(u8 *, u32, u32);
s32 Ip_IsOnLocalNet(u32);

void Icmp_SendEchoRequest(u8 *a, u32 b, IpSocket *c);
void Ip_Send(u8 *p, u32 len, u8 *data, u32 n, u32 x, u8 flag);
void Ip_SendPacket(u8 *p, u32 off, u8 *data, u32 n, u32 x, u32 w);
void Eth_SendIp(u8 *p, u32 off, u8 *data, u32 n, u32 x, u16 w);
u8 *Arp_Resolve(u32 ip);
u8 *Arp_Lookup(u32 ip);
u8 *Eth_WaitFrame(u32 *out);
void Eth_OnFrameReceived(u8 *, u8 *, u8 *, u32);
void Eth_EnqueueFrame(u8 *, u8 *, u8 *, u32, u8 *, u32);
s32 Ip_IsForMe(u32 ip);
s32 Ip_IsMulticast(u32 ip);
s32 Ip_IsBroadcast(u32 ip);

extern "C" {
s32 Ip_IsBroadcast(u32 ip);
s32 Ip_IsMulticast(u32 ip);
s32 Ip_IsForMe(u32 ip);
void Eth_EnqueueFrame(u8 *a, u8 *b, u8 *c, u32 d, u8 *data, u32 n);
void Eth_OnFrameReceived(u8 *a, u8 *b, u8 *c, u32 d);
u8 *Eth_WaitFrame(u32 *out);
u8 *Arp_Lookup(u32 ip);
u8 *Arp_Resolve(u32 ip);
void Eth_SendIp(u8 *p, u32 off, u8 *data, u32 n, u32 x, u16 w);
void Ip_SendPacket(u8 *p, u32 off, u8 *data, u32 n, u32 x, u32 w);
void Ip_Send(u8 *p, u32 len, u8 *data, u32 n, u32 x, u8 flag);
void Icmp_SendEchoRequest(u8 *a, u32 b, IpSocket *c);
}

s32 Ip_IsBroadcast(u32 ip)
{
    BOOL r = FALSE;
    if (Ip_IsOnLocalNet(ip) != 0) {
        u32 m = ~sNetmask;
        if (m == (m & ip)) {
            r = TRUE;
        }
    }
    return r;
}

s32 Ip_IsMulticast(u32 ip)
{
    if ((ip & 0xf0000000) == 0xe0000000) {
        return 1;
    }
    return 0;
}

s32 Ip_IsForMe(u32 ip)
{
    BOOL r = TRUE;
    BOOL c = TRUE;
    BOOL b = TRUE;
    BOOL a = TRUE;
    u32 g = gOwnIp;
    if (g != 0 && ip != g) {
        a = FALSE;
    }
    if (a == 0) {
        if (ip != 0x7f000001) {
            b = FALSE;
        }
    }
    if (b == 0) {
        if (Ip_IsBroadcast(ip) == 0) {
            c = FALSE;
        }
    }
    if (c == 0) {
        if (Ip_IsMulticast(ip) == 0) {
            r = FALSE;
        }
    }
    return r;
}

s32 Eth_MacDiffers(const void *pa, const void *pb)
{
    const u16 *a = (const u16 *)pa;
    const u16 *b = (const u16 *)pb;
    s32 i;
    for (i = 0; i < 3; i++) {
        u32 x = *a++;
        u32 y = *b++;
        if (x != y) {
            return 1;
        }
    }
    return 0;
}

void Eth_SendFrame(u8 *hdr, u32 hlen, u8 *data, u32 n)
{
    s32 r;
    if (hdr + hlen != data) {
        MI_CpuCopy8(data, hdr + hlen, n);
    }
    MI_CpuCopy8(sLlcSnapHeader, hdr + 6, 6);
    r = WifiLink_SendFrame(hdr, hdr + 6, hlen + n - 6);
    sLinkSendError = (r < 0) ? 1 : 0;
}

void Eth_EnqueueFrame(u8 *a, u8 *b, u8 *c, u32 d, u8 *data, u32 n)
{
    u8 *buf = sRecvRingBuf;
    u32 lim;
    u32 tot;
    u32 sz;
    u32 wr;
    u32 rd;
    u32 end;
    u32 nw;
    if (buf == 0) {
        return;
    }
    lim = sRecvRingSize;
    if (lim == 0) {
        return;
    }
    tot = d + n;
    if (tot < 8 || tot > 0x5e4) {
        return;
    }
    if (c[0] != sLlcSnapHeader[0]) {
        return;
    }
    if (c[1] != sLlcSnapHeader[1]) {
        return;
    }
    if (c[2] != sLlcSnapHeader[2]) {
        return;
    }
    if (c[6] != 8) {
        return;
    }
    if (c[7] != 0 && c[7] != 6) {
        return;
    }
    sz = (u16)((tot + 9) & ~1);
    wr = sRecvRingWrite;
    end = wr + sz;
    nw = end;
    rd = sRecvRingRead;
    if (wr < rd) {
        if (rd <= end) {
            return;
        }
    }
    if (end == lim) {
        nw = 0;
        if (rd == 0) {
            return;
        }
    } else if (end > lim) {
        nw = sz;
        if (rd <= sz) {
            return;
        }
    }
    if (end > lim) {
        if (lim - wr >= 2) {
            buf[wr] = 0;
            u8 *pw = sRecvRingBuf + sRecvRingWrite;
            pw[1] = 0;
        }
        sRecvRingWrite = 0;
    }
    sRecvRingBuf[sRecvRingWrite] = sz;
    u8 *pw2 = sRecvRingBuf + sRecvRingWrite;
    pw2[1] = (s32)sz >> 8;
    MI_CpuCopy8(b, sRecvRingBuf + sRecvRingWrite + 2, 6);
    MI_CpuCopy8(a, sRecvRingBuf + sRecvRingWrite + 8, 6);
    MI_CpuCopy8(c + 6, sRecvRingBuf + sRecvRingWrite + 0xe, d - 6);
    if (data != 0 && n != 0) {
        MI_CpuCopy8(data, sRecvRingBuf + sRecvRingWrite + 8 + d, n);
    }
    sRecvRingWrite = nw;
}

void Eth_OnFrameReceived(u8 *a, u8 *b, u8 *c, u32 d)
{
    Eth_EnqueueFrame(a, b, c, d, 0, 0);
    if (sRecvRingWaiter != 0) {
        if (OS_IsThreadTerminated(sRecvRingWaiter) == 0) {
            OS_WakeupThreadDirect(sRecvRingWaiter);
        }
    }
}

u8 *Eth_WaitFrame(u32 *out)
{
    u32 len;
    u32 lim;
    u8 *buf;
    while (sRecvRingRead == sRecvRingWrite) {
        sRecvRingWaiter = data_021fcc2c.current;
        OS_SleepThread(0);
        sRecvRingWaiter = 0;
    }
    lim = sRecvRingSize;
    buf = sRecvRingBuf;
    do {
        u32 o;
        if (lim - sRecvRingRead < 2) {
            sRecvRingRead = 0;
        }
        o = sRecvRingRead;
        u8 *pp = buf + o;
        u32 l0 = buf[o];
        len = (u16)(l0 + (pp[1] << 8));
        if (len == 0) {
            sRecvRingRead = 0;
        }
    } while (len == 0);
    *out = len - 2;
    return sRecvRingBuf + sRecvRingRead + 2;
}

void Eth_PopFrame()
{
    u32 irq = OS_DisableInterrupts();
    u32 o = sRecvRingRead;
    u8 *base = sRecvRingBuf;
    u32 lo = base[o];
    u32 v = o + (lo + ((base + o)[1] << 8));
    sRecvRingRead = v;
    if (v >= sRecvRingSize) {
        sRecvRingRead = 0;
    }
    OS_RestoreInterrupts(irq);
}

u8 *Arp_Lookup(u32 ip)
{
    u32 irq = OS_DisableInterrupts();
    u8 *r = 0;
    if (ip == 0x7f000001 || ip == gOwnIp) {
        r = sOwnMac;
    } else if (Ip_IsBroadcast(ip) != 0 || Ip_IsMulticast(ip) != 0) {
        r = sBroadcastMac;
    } else {
        s32 i;
        ArpCacheEntry *e;
        for (i = 0, e = sArpCache; (u32)i < 8; e++, i++) {
            if (ip == e->ipAddr) {
                u32 t = (u32)(OS_GetTick() >> 16);
                sArpCache[i].lastUsed = t;
                r = sArpCache[i].macAddr;
                break;
            }
        }
    }
    OS_RestoreInterrupts(irq);
    return r;
}

void Arp_SendRequest(u32 ip)
{
    u8 b[0x30];
    MI_CpuFill8(b, 0, 0x2a);
    MI_CpuFill8(b, 0xff, 6);
    MI_CpuCopy8(sOwnMac, b + 6, 6);
    *(u16 *)(b + 0xc) = 0x608;
    b[0xf] = 1;
    b[0x10] = 8;
    *(u16 *)(b + 0x12) = 0x406;
    b[0x15] = 1;
    MI_CpuCopy8(sOwnMac, b + 0x16, 6);
    *(u16 *)(b + 0x1c) = BS16((u16)(gOwnIp >> 16));
    *(u16 *)(b + 0x1e) = BS16((u16)gOwnIp);
    *(u16 *)(b + 0x26) = BS16((u16)(ip >> 16));
    *(u16 *)(b + 0x28) = BS16((u16)ip);
    Eth_SendFrame(b, 0x2a, 0, 0);
}

u8 *Arp_Resolve(u32 ip)
{
    u32 j = 0;
    u32 z = 0;
    do {
        u32 k;
        Arp_SendRequest(ip);
        k = z;
        do {
            u8 *r;
            OS_Sleep(100);
            r = Arp_Lookup(ip);
            if (r != 0) {
                return r;
            }
            k++;
        } while (k < 0x14);
        j++;
    } while (j < 8);
    return 0;
}

void Arp_UpdateCache(u8 *mac, u32 ip, u32 flag)
{
    u32 now;
    s32 i;
    if (ip == 0x7f000001 || ip == gOwnIp) {
        return;
    }
    if (Ip_IsOnLocalNet(ip) == 0) {
        return;
    }
    if (Ip_IsMulticast(ip) != 0) {
        return;
    }
    now = (u16)(OS_GetTick() >> 16);
    {
        ArpCacheEntry *e;
        for (i = 0, e = sArpCache; (u32)i < 8; e++, i++) {
            if (ip == e->ipAddr) {
                sArpCache[i].lastUsed = now;
                MI_CpuCopy8(mac, sArpCache[i].macAddr, 6);
                return;
            }
        }
    }
    if (flag != 0) {
        u32 best = 0;
        u32 idx = 0;
        ArpCacheEntry *e;
        for (i = 0, e = sArpCache; (u32)i < 8; e++, i++) {
            if (e->ipAddr == 0) {
                idx = i;
                break;
            }
            s32 d = (s16)(now - e->lastUsed);
            if (d > (s32)best) {
                best = (u16)(now - e->lastUsed);
                idx = i;
            }
        }
        sArpCache[idx].ipAddr = ip;
        MI_CpuCopy8(mac, sArpCache[idx].macAddr, 6);
        sArpCache[idx].lastUsed = now;
    }
}

void Eth_SendIp(u8 *p, u32 off, u8 *data, u32 n, u32 x, u16 w)
{
    *(u16 *)(p - 2) = BS16(w);
    if (Ip_IsMulticast(x) == 0) {
        u8 *r;
        u32 k = Ip_GetNextHop(x);
        if (k == 0) {
            return;
        }
        r = Arp_Lookup(k);
        if (r == 0) {
            r = Arp_Resolve(k);
        }
        if (r == 0) {
            return;
        }
        MI_CpuCopy8(r, p - 0xe, 6);
    } else {
        p[-0xe] = 1;
        p[-0xd] = 0;
        p[-0xc] = 0x5e;
        p[-0xb] = (x >> 16) & 0x7f;
        p[-0xa] = x >> 8;
        p[-9] = x;
    }
    MI_CpuCopy8(sOwnMac, p - 8, 6);
    Eth_SendFrame(p - 0xe, off + 0xe, data, n);
}

void Ip_SendPacket(u8 *p, u32 off, u8 *data, u32 n, u32 x, u32 w)
{
    *(u16 *)(p - 0x12) = BS16((u16)(off + 0x14 + n));
    *(u16 *)(p - 0xe) = BS16((u16)w);
    *(u16 *)(p - 0xa) = 0;
    u32 ck = Ip_Checksum(p - 0x14, 0x14);
    *(u16 *)(p - 0xa) = BS16(ck);
    if (x != 0x7f000001 && x != gOwnIp) {
        Eth_SendIp(p - 0x14, off + 0x14, data, n, x, 0x800);
    }
    if (x == 0x7f000001 || x == gOwnIp || Ip_IsMulticast(x) != 0) {
        MI_CpuCopy8(sLlcSnapHeader, p - 0x1c, 8);
        u32 irq = OS_DisableInterrupts();
        Eth_EnqueueFrame(sOwnMac, sOwnMac, p - 0x1c, off + 0x1c, data, n);
        OS_RestoreInterrupts(irq);
    }
}

void Ip_Send(u8 *p, u32 len, u8 *data, u32 n, u32 x, u8 flag)
{
    u32 i;
    p[-0x14] = 0x45;
    i = 0;
    p[-0x13] = 0;
    sIpIdCounter = sIpIdCounter + 1;
    *(u16 *)(p - 0x10) = BS16(sIpIdCounter);
    p[-0xc] = 0x80;
    p[-0xb] = flag;
    *(u16 *)(p - 8) = BS16((u16)(gOwnIp >> 16));
    *(u16 *)(p - 6) = BS16((u16)gOwnIp);
    *(u16 *)(p - 4) = BS16((u16)(x >> 16));
    *(u16 *)(p - 2) = BS16((u16)x);
    if (len > 0x5c8) {
        u8 *s = p;
        while (len > 0x5c8) {
            Ip_SendPacket(p, 0, s, 0x5c8, x, i | 0x2000);
            s += 0x5c8;
            len -= 0x5c8;
            i = (u16)(i + 0xb9);
        }
        if (len != 0) {
            if (n != 0) {
                Ip_SendPacket(p, 0, s, len, x, i | 0x2000);
            } else {
                Ip_SendPacket(p, 0, s, len, x, i);
            }
            i = (u16)(i + (len >> 3));
            len = 0;
        }
    }
    if (len + n > 0x5c8) {
        do {
            u32 c = 0x5c8 - len;
            Ip_SendPacket(p, len, data, c, x, i | 0x2000);
            data += c;
            n -= c;
            i = (u16)(i + 0xb9);
            len = 0;
        } while (n > 0x5c8);
    }
    if (len + n != 0) {
        Ip_SendPacket(p, len, data, n, x, i);
    }
}

void Icmp_SendEchoRequest(u8 *a, u32 b, IpSocket *c)
{
    u8 *h = c->txBuf;
    u8 *q = h + 0x22;
    *(u16 *)(h + 0x22) = 8;
    *(u16 *)(q + 4) = (u16)(uptr)data_021fcc2c.current;
    *(u16 *)(q + 2) = 0;
    u16 id = sIcmpSeq;
    c->localPort = id;
    sIcmpSeq = sIcmpSeq + 1;
    *(u16 *)(q + 6) = id;
    u32 t = Ip_ChecksumAdd(q, 8, 0);
    t = Ip_ChecksumAdd(a, b, t);
    u32 ck = Ip_ChecksumFinish((u16)t);
    *(u16 *)(q + 2) = BS16(ck);
    Ip_Send(q, 8, a, b, c->remoteAddr, 1);
}

}








extern "C" {
extern OSThreadInfo data_021fcc2c;
extern IpSocket sTcpResetSoc;
extern OSThread sIpRecvThread;
extern u32 sIcmpEchoReplyEnabled;
extern u32 gOwnIp;
extern u8 sArpConflict;
extern u16 sMss;
#define sRecvThreadTxBuf (data_ov065_0228ec1c + 0x22)


u8 *Arp_Lookup(u32);
s32 Ip_IsMulticast(u32);
u32 Ip_Checksum(u8 *, u32);
u32 Ip_ChecksumFinish(u32);
u32 Ip_ChecksumAdd(u8 *, u32, u32);
void Ip_Send(u8 *p, u32 len, u8 *data, u32 n, u32 x, u8 flag);

s32 Ip_IsNextHopResolved(u32);
s32 Tcp_MatchConnection(u8 *, u8 *, IpSocket *);
s32 Ip_AreAddrsValid(u32, u32);
void Icmp_DeliverEchoReply(u8 *, u8 *, u32);
void Icmp_SendEchoReply(u8 *, u8 *, u32);
void Arp_SendReply(u8 *);
}

#define BS16(x) ((u16)((((s32)(x)) >> 8) | (((s32)(x)) << 8)))

static inline u32 Swap32(u8 *p) {
    u32 hi = BS16(*(u16 *)(p));
    u32 lo = BS16(*(u16 *)(p + 2));
    return (hi << 16) | lo;
}

extern "C" {
void Arp_SendReply(u8 *a);
void Icmp_SendEchoReply(u8 *a, u8 *b, u32 c);
void Icmp_DeliverEchoReply(u8 *a, u8 *b, u32 c);
s32 Ip_AreAddrsValid(u32 x, u32 y);
s32 Tcp_MatchConnection(u8 *a, u8 *b, IpSocket *s);
s32 Ip_IsNextHopResolved(u32 x);
}

void Udp_Send(u8 *a, u32 b, IpSocket *s) {
    u8 *q = s->txBuf;
    u8 *p = q + 0x22;
    *(u16 *)(p - 0xc) = BS16((u16)(gOwnIp >> 16));
    *(u16 *)(p - 0xa) = BS16((u16)gOwnIp);
    *(u16 *)(p - 8) = BS16((u16)(s->remoteAddr >> 16));
    *(u16 *)(p - 6) = BS16((u16)s->remoteAddr);
    *(u16 *)(p - 4) = 0x1100;
    *(u16 *)(p + 4) = BS16((u16)(b + 8));
    *(u16 *)(p - 2) = *(u16 *)(p + 4);
    *(u16 *)(p + 2) = BS16(s->remotePort);
    *(u16 *)(q + 0x22) = BS16(s->localPort);
    *(u16 *)(p + 6) = 0;
    u32 v = Ip_ChecksumFinish((u16)Ip_ChecksumAdd(a, b, Ip_ChecksumAdd(p - 0xc, 0x14, 0)));
    *(u16 *)(p + 6) = BS16(v);
    Ip_Send(p, 8, a, b, s->remoteAddr, 0x11);
}

void Tcp_SendSegment(u8 *x, u32 y, IpSocket *s, u32 flags, u32 z) {
    u8 *p;
    u32 hl;
    u32 f2;
    if (s->state != 0) {
        if (data_021fcc2c.current == &sIpRecvThread) {
            p = sRecvThreadTxBuf;
        } else {
            p = s->txBuf + 0x22;
        }
        f2 = flags & 2;
        if (f2 != 0) {
            hl = 0x18;
        } else {
            hl = 0x14;
        }
        *(u16 *)(p - 0xc) = BS16((u16)(gOwnIp >> 16));
        *(u16 *)(p - 0xa) = BS16((u16)gOwnIp);
        *(u16 *)(p - 8) = BS16((u16)(s->remoteAddr >> 16));
        *(u16 *)(p - 6) = BS16((u16)s->remoteAddr);
        *(u16 *)(p - 4) = 0x600;
        *(u16 *)(p - 2) = BS16((u16)(hl + y));
        *(u16 *)(p) = BS16(s->localPort);
        *(u16 *)(p + 2) = BS16(s->remotePort);
        *(u16 *)(p + 4) = BS16((u16)(s->sendNext >> 16));
        *(u16 *)(p + 6) = BS16((u16)s->sendNext);
        *(u16 *)(p + 8) = BS16((u16)(s->recvNext >> 16));
        *(u16 *)(p + 0xa) = BS16((u16)s->recvNext);
        p[0xc] = (hl >> 2) << 4;
        p[0xd] = flags;
        *(u16 *)(p + 0xe) = BS16((u16)(s->rxBufSize - s->rxLen));
        *(u16 *)(p + 0x10) = 0;
        *(u16 *)(p + 0x12) = BS16(*(u16 *)&z);
        if (f2 != 0) {
            *(u16 *)(p + 0x14) = BS16((u16)((sMss + 0x2040000U) >> 16));
            *(u16 *)(p + 0x16) = BS16((u16)(sMss + 0x2040000U));
        }
        u32 v = Ip_ChecksumFinish((u16)Ip_ChecksumAdd(x, y, Ip_ChecksumAdd(p - 0xc, hl + 0xc, 0)));
        *(u16 *)(p + 0x10) = BS16(v);
        Ip_Send(p, hl, x, y, s->remoteAddr, 6);
        s->sendNext = s->sendNext + y;
        flags &= 3;
        if (flags != 0) {
            s->sendNext = s->sendNext + 1;
        }
    }
}

void Arp_SendReply(u8 *a) {
    *(u16 *)(a + 6) = 0x200;
    MI_CpuCopy8(a + 8, a + 0x12, 10);
    MI_CpuCopy8(sOwnMac, a + 8, 6);
    *(u16 *)(a + 0xe) = BS16((u16)(gOwnIp >> 16));
    *(u16 *)(a + 0x10) = BS16((u16)gOwnIp);
    MI_CpuCopy8(a + 0x12, a - 0xe, 6);
    MI_CpuCopy8(sOwnMac, a - 8, 6);
    Eth_SendFrame(a - 0xe, 0x2a, 0, 0);
}

void Arp_Input(u8 *a, u32 len) {
    if (len >= 0x1c && Eth_MacDiffers(a + 8, sOwnMac) != 0 && *(volatile u32 *)&gOwnIp != 0
        && *(u16 *)a == 0x100 && *(u16 *)(a + 2) == 8 && *(u16 *)(a + 4) == 0x406) {
        u32 t = BS16(*(u16 *)(a + 6));
        if (t != 1) {
            if (t != 2) {
                return;
            }
        }
        {
            u32 x = Swap32(a + 0xe);
            u32 g = gOwnIp;
            BOOL k7;
            BOOL k4;
            if (x == g) {
                k7 = TRUE;
            } else {
                k7 = FALSE;
            }
            if (g == Swap32(a + 0x18)) {
                k4 = TRUE;
            } else {
                k4 = FALSE;
            }
            if (!k7) {
                Arp_UpdateCache(a + 8, x, k4);
            }
            if (t == 1 && k4) {
                Arp_SendReply(a);
                return;
            }
            if (t == 2 && k4 && k7) {
                sArpConflict = 1;
            }
        }
    }
}

void Icmp_SendEchoReply(u8 *a, u8 *b, u32 c) {
    u32 k = Swap32(a + 0xc);
    if (Ip_IsMulticast(k) == 0) {
        k = Ip_GetNextHop(k);
        if (k != 0) {
            if (Arp_Lookup(k) == 0) {
                Arp_SendRequest(k);
                return;
            }
            b[0] = 0;
            *(u16 *)(b + 2) = 0;
            u32 r = Ip_Checksum(b, c);
            *(u16 *)(b + 2) = BS16(r);
            Ip_Send(b, c, 0, 0, Swap32(a + 0xc), 1);
        }
    }
}

void Icmp_DeliverEchoReply(u8 *a, u8 *b, u32 c) {
    OSThread *t;
    for (t = data_021fcc2c.list; t != 0; t = t->next) {
        IpSocket *s = (IpSocket *)t->specific[0];
        if (s != 0 && s->ownerThread != 0 && s->state == 11 && (u16)(uptr)s->ownerThread == *(u16 *)(b + 4)
            && s->localPort == *(u16 *)(b + 6) && s->rxLen == 0 && s->remoteAddr == Swap32(a + 0xc)) {
            u32 m = s->rxBufSize;
            c -= 8;
            if (c > m) {
                s->rxLen = m;
            } else {
                s->rxLen = c;
            }
            MI_CpuCopy8(b + 8, s->rxBuf, s->rxLen);
            if (s->waitReason == 3) {
                s->waitReason = 0;
                OS_WakeupThreadDirect(s->ownerThread);
            }
            return;
        }
    }
}

s32 Ip_AreAddrsValid(u32 x, u32 y) {
    if (x != 0 && x != -1 && y != 0 && y != -1) {
        return TRUE;
    }
    return FALSE;
}

void Icmp_Input(u8 *a, u8 *b, u32 c) {
    if (Ip_Checksum(b, c) == 0xffff) {
        if (Ip_AreAddrsValid(Swap32(a + 0xc), Swap32(a + 0x10)) != 0) {
            switch (b[0]) {
            case 0:
                Icmp_DeliverEchoReply(a, b, c);
                break;
            case 8:
                if (sIcmpEchoReplyEnabled != 0) {
                    Icmp_SendEchoReply(a, b, c);
                }
                break;
            }
        }
    }
}

IpSocket *Tcp_FindListener(u8 *a, u8 *b) {
    IpSocket *s;
    OSThread *t;
    for (t = data_021fcc2c.list; t != 0; t = t->next) {
        s = (IpSocket *)t->specific[0];
        if (s != 0 && s->ownerThread != 0 && s->state == 1 && s->localPort == BS16(*(u16 *)(b + 2))
            && (s->remotePort == 0 || s->remotePort == BS16(*(u16 *)b))
            && (s->remoteAddr == 0 || s->remoteAddr == Swap32(a + 0xc))) {
            return s;
        }
    }
    return 0;
}

s32 Tcp_MatchConnection(u8 *a, u8 *b, IpSocket *s) {
    s32 result = 0;
    BOOL c = FALSE;
    BOOL bb = FALSE;
    BOOL aa = FALSE;
    if (s->state != 10 && s->state != 11) {
        aa = TRUE;
    }
    if (aa) {
        if (s->localPort == BS16(*(u16 *)(b + 2))) {
            bb = TRUE;
        }
    }
    if (bb) {
        if (s->remotePort == BS16(*(u16 *)b)) {
            c = TRUE;
        }
    }
    if (c) {
        if (s->remoteAddr == Swap32(a + 0xc)) {
            result = 1;
        }
    }
    return result;
}

IpSocket *Tcp_FindConnection(u8 *a, u8 *b) {
    IpSocket *s;
    OSThread *t;
    for (t = data_021fcc2c.list; t != 0; t = t->next) {
        s = (IpSocket *)t->specific[0];
        if (s != 0 && s->ownerThread != 0 && Tcp_MatchConnection(a, b, s) != 0) {
            return s;
        }
    }
    return 0;
}

void Tcp_ParseOptions(u8 *a, IpSocket *s) {
    s32 n;
    u8 *p;
    s->peerMss = 0x218;
    n = (s32)(a[0xc] & 0xf0) / 4 - 0x14;
    p = a + 0x14;
    while (n--) {
        u32 k = *p++;
        if (k == 0) {
            break;
        }
        if (k == 1) {
            continue;
        }
        if (k == 2) {
            s->peerMss = (p[1] << 8) | p[2];
            p += 3;
            n -= 3;
        } else {
            s32 t = *p - 1;
            n -= t;
            p += t;
        }
    }
}

s32 Ip_IsNextHopResolved(u32 x) {
    u32 r = Ip_GetNextHop(x);
    if (r == 0) {
        return 1;
    }
    return Arp_Lookup(r) != NULL;
}

void Tcp_SendControl(IpSocket *s, u32 a, u32 b) {
    if (Ip_IsNextHopResolved(s->remoteAddr) != 0 || data_021fcc2c.current != &sIpRecvThread) {
        Tcp_SendSegment(0, 0, s, a, b);
    } else {
        Arp_SendRequest(Ip_GetNextHop(s->remoteAddr));
    }
}

void Tcp_SendAck(IpSocket *s, u32 x) {
    Tcp_SendControl(s, 0x10, x);
}

void Tcp_SendFinAck(IpSocket *s, u32 x) {
    Tcp_SendControl(s, 0x11, x);
}

void Tcp_SendReset(u8 *a, u8 *b, u32 c, u32 d) {
    IpSocket *g = &sTcpResetSoc;
    MI_CpuFill8(g, 0, sizeof(*g));
    g->localPort = BS16(*(u16 *)(b + 2));
    g->remotePort = BS16(*(u16 *)b);
    g->remoteAddr = Swap32(a + 0xc);
    if ((b[0xd] & 0x10) != 0) {
        g->sendNext = Swap32(b + 8);
        Tcp_SendControl(g, 4, d);
        return;
    }
    g->sendNext = 0;
    g->recvNext = c + Swap32(b + 4);
    if ((b[0xd] & 3) != 0) {
        g->recvNext = g->recvNext + 1;
    }
    Tcp_SendControl(g, 0x14, d);
}

void Tcp_AcceptSyn(u8 *a, u8 *b, IpSocket *s) {
    s->state = 3;
    s->handshakeTime = (u32)(OS_GetTick() >> 16);
    s->localAddr = Swap32(a + 0x10);
    s->remotePort = BS16(*(u16 *)b);
    s->remoteAddr = Swap32(a + 0xc);
    s->recvNext = Swap32(b + 4) + 1;
    Tcp_ParseOptions(b, s);
    Tcp_SendControl(s, 0x12, (u16)((a[5] << 8) + 1));
}





static inline u16 Unk_ov065_02262c5c_Bs(u16 v) {
    return (u16)((v >> 8) | (v << 8));
}

extern "C" {

extern IpFragEntry sIpFragTable[8];
extern OSThreadInfo data_021fcc2c;

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
s32 _s32_div_f(s32, s32);

s32 Ip_AreAddrsValid(u32, u32);

void Tcp_InputRst(IpHeader *p, TcpHeader *q);
void Tcp_InputFin(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputAck(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputSynAck(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputSyn(IpHeader *p, TcpHeader *q, u32 r);
s32 Tcp_InputSynExisting(IpHeader *p, TcpHeader *q, u32 r);

extern "C" {
s32 Tcp_InputSynExisting(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputSyn(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputSynAck(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputAck(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputFin(IpHeader *p, TcpHeader *q, u32 r);
void Tcp_InputRst(IpHeader *p, TcpHeader *q);
}

s32 Tcp_InputSynExisting(IpHeader *p, TcpHeader *q, u32 r) {
    IpSocket *s = Tcp_FindConnection((u8 *)p, (u8 *)q);
    if (s != 0) {
        if (s->state == 1) {
            Tcp_AcceptSyn((u8 *)p, (u8 *)q, s);
        } else if ((u8)(s->state + 0xfd) <= 1) {
            s->sendNext--;
            Tcp_AcceptSyn((u8 *)p, (u8 *)q, s);
        } else {
            Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 3));
        }
        return 1;
    }
    return 0;
}

void Tcp_InputSyn(IpHeader *p, TcpHeader *q, u32 r) {
    if (Ip_AreAddrsValid(((u32)Unk_ov065_02262c5c_Bs(p->srcAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->srcAddrLo),
                            ((u32)Unk_ov065_02262c5c_Bs(p->dstAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->dstAddrLo)) != 0) {
        if (Tcp_InputSynExisting(p, q, r) == 0) {
            IpSocket *x = Tcp_FindListener((u8 *)p, (u8 *)q);
            if (x != 0) {
                Tcp_AcceptSyn((u8 *)p, (u8 *)q, x);
                return;
            }
            OS_YieldThread();
            x = Tcp_FindListener((u8 *)p, (u8 *)q);
            if (x != 0) Tcp_AcceptSyn((u8 *)p, (u8 *)q, x);
        }
    }
}

void Tcp_InputSynAck(IpHeader *p, TcpHeader *q, u32 r) {
    IpSocket *s = Tcp_FindConnection((u8 *)p, (u8 *)q);
    if (s == 0 || s->state != 2) {
        Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 5));
        return;
    }
    OS_YieldThread();
    s->recvNext = (((u32)Unk_ov065_02262c5c_Bs(q->h4) << 16) | Unk_ov065_02262c5c_Bs(q->h6)) + 1;
    s->ackedSeq = ((u32)Unk_ov065_02262c5c_Bs(q->ackHi) << 16) | Unk_ov065_02262c5c_Bs(q->ackLo);
    s->peerWindow = Unk_ov065_02262c5c_Bs(q->window);
    Tcp_ParseOptions((u8 *)q, s);
    Tcp_SendAck(s, (u16)((p->b5 << 8) + 6));
    s->state = 4;
    if (s->waitReason == 1) {
        s->waitReason = 0;
        OS_WakeupThreadDirect(s->ownerThread);
    }
}

void Tcp_InputAck(IpHeader *p, TcpHeader *q, u32 r) {
    IpSocket *s = Tcp_FindConnection((u8 *)p, (u8 *)q);
    s32 fl;
    s32 last;
    u32 seq;
    if (s == 0) {
        Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 9));
        return;
    }
    fl = q->tcpFlags;
    s->ackedSeq = ((u32)Unk_ov065_02262c5c_Bs(q->ackHi) << 16) | Unk_ov065_02262c5c_Bs(q->ackLo);
    seq = ((u32)Unk_ov065_02262c5c_Bs(q->h4) << 16) | Unk_ov065_02262c5c_Bs(q->h6);
    if (s->state == 4 && (u32)s->recvNext != seq) {
        Tcp_SendAck(s, (u16)((p->b5 << 8) + 0xa));
        return;
    }
    s->peerWindow = Unk_ov065_02262c5c_Bs(q->window);
    switch (s->state) {
    case 0:
    case 2:
        Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 0x63));
        break;
    case 3:
        s->state = 4;
        if (s->waitReason == 1) {
            s->waitReason = 0;
            OS_WakeupThreadDirect(s->ownerThread);
        }
        if (r == 0) break;
    case 4:
        s->rxSegmentCount++;
        {
            u32 room = s->rxBufSize - s->rxLen;
            if (r > room) {
                r = room;
                last = 0;
            } else {
                last = 1;
            }
        }
        if (r != 0) {
            u32 sv = OS_DisableInterrupts();
            MI_CpuCopy8((u8 *)q + _s32_div_f(q->dataOffset & 0xf0, 4), s->rxBuf + s->rxLen, r);
            s->rxLen += r;
            s->recvNext += r;
            OS_RestoreInterrupts(sv);
            if (s->waitReason == 2) {
                s->waitReason = 0;
                OS_WakeupThreadDirect(s->ownerThread);
            }
        }
        if (last != 0 && (fl & 1) != 0) {
            s->state = 6;
            s->recvNext++;
            Tcp_SendFinAck(s, (u16)((p->b5 << 8) + 0xb));
            if (r == 0 && s->waitReason == 2) {
                s->waitReason = 0;
                OS_WakeupThreadDirect(s->ownerThread);
            }
        } else if (r != 0) {
            Tcp_SendAck(s, (u16)((p->b5 << 8) + 0xc));
        }
        break;
    case 7:
    case 8:
        if ((fl & 1) != 0) {
            s->recvNext += r + 1;
            Tcp_SendAck(s, (u16)((p->b5 << 8) + 0xd));
            s->state = 0;
            if (s->waitReason == 2) {
                s->waitReason = 0;
                OS_WakeupThreadDirect(s->ownerThread);
            }
        } else {
            if (r != 0) {
                s->recvNext += r;
                Tcp_SendAck(s, (u16)((p->b5 << 8) + 0xe));
            }
            s->state = 8;
        }
        break;
    case 6:
    case 9:
        s->state = 0;
        if (s->waitReason == 2) {
            s->waitReason = 0;
            OS_WakeupThreadDirect(s->ownerThread);
        }
        break;
    case 1:
    case 5:
    default:
        if ((fl & 1) != 0) s->recvNext++;
        Tcp_SendAck(s, (u16)((p->b5 << 8) + 0x12));
        break;
    }
    OS_YieldThread();
}

void Tcp_InputFin(IpHeader *p, TcpHeader *q, u32 r) {
    IpSocket *s = Tcp_FindConnection((u8 *)p, (u8 *)q);
    if (s != 0) {
        switch (s->state) {
        case 7:
            s->recvNext++;
            Tcp_SendAck(s, (u16)((p->b5 << 8) + 0x13));
            s->state = 9;
            return;
        case 8:
            s->recvNext++;
            Tcp_SendAck(s, (u16)((p->b5 << 8) + 0x14));
            s->state = 0;
            if (s->waitReason == 2) {
                s->waitReason = 0;
                OS_WakeupThreadDirect(s->ownerThread);
                return;
            }
            return;
        case 4:
            s->recvNext++;
            Tcp_SendFinAck(s, (u16)((p->b5 << 8) + 0x15));
            s->state = 6;
            return;
        default:
            Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 0x16));
            break;
        }
    }
}

void Tcp_InputRst(IpHeader *p, TcpHeader *q) {
    IpSocket *s = Tcp_FindConnection((u8 *)p, (u8 *)q);
    if (s != 0) {
        OS_YieldThread();
        s->state = 0;
        if ((u32)(s->waitReason - 1) <= 1) {
            s->waitReason = 0;
            OS_WakeupThreadDirect(s->ownerThread);
        }
    }
}

void Tcp_Input(IpHeader *p, TcpHeader *q, u32 r) {
    if (Ip_VerifyPseudoChecksum((u8 *)q, r, (u8 *)p, 6) == 0) {
        s32 t;
        r -= _s32_div_f(q->dataOffset & 0xf0, 4);
        t = q->tcpFlags;
        switch (t & 0x17) {
        case 2:
            if ((t & 0x28) == 0) Tcp_InputSyn(p, q, r);
            return;
        case 0x12:
            if ((t & 0x28) == 0) Tcp_InputSynAck(p, q, r);
            return;
        case 0x10:
        case 0x11:
            Tcp_InputAck(p, q, r);
            return;
        case 1:
            Tcp_InputFin(p, q, r);
            return;
        default:
            break;
        }
        if ((t & 4) != 0) {
            Tcp_InputRst(p, q);
            return;
        }
        Tcp_SendReset((u8 *)p, (u8 *)q, r, (u16)((p->b5 << 8) + 0x17));
    }
}

void Udp_Input(IpHeader *p, UdpHeader *q, u32 c) {
    if (q->checksum != 0 && Ip_VerifyPseudoChecksum((u8 *)q, c, (u8 *)p, 0x11) != 0) return;
    OSThread *s = data_021fcc2c.list;
    for (; s != 0; s = s->next) {
        IpSocket *k = (IpSocket *)s->specific[0];
        if (k != 0 && k->ownerThread != 0 && k->state == 10 && k->localPort == Unk_ov065_02262c5c_Bs(q->dstPort)
            && (k->remotePort == 0 || k->remotePort == Unk_ov065_02262c5c_Bs(q->srcPort))
            && (k->remoteAddr == 0 || k->remoteAddr == (u32)-1
                || k->remoteAddr == (((u32)Unk_ov065_02262c5c_Bs(p->srcAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->srcAddrLo)))) {
            k->localAddr = ((u32)Unk_ov065_02262c5c_Bs(p->dstAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->dstAddrLo);
            if (k->remoteAddr == 0) {
                k->remoteAddr = ((u32)Unk_ov065_02262c5c_Bs(p->srcAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->srcAddrLo);
                k->remotePort = Unk_ov065_02262c5c_Bs(q->srcPort);
            }
            if (k->rxLen != 0) return;
            u32 m = k->rxBufSize;
            c -= 8;
            if (c > m) k->rxLen = m;
            else k->rxLen = c;
            MI_CpuCopy8(q + 1, k->rxBuf, k->rxLen);
            if (k->waitReason == 3) {
                k->waitReason = 0;
                OS_WakeupThreadDirect(k->ownerThread);
                return;
            }
            if (k->udpCallback != 0) {
                if (k->udpCallback(k->rxBuf, k->rxLen, k) != 0) k->rxLen = 0;
            }
            return;
        }
    }
    return;
}

u8 *Ip_Reassemble(IpHeader *p, s32 *out) {
    u32 flags;
    u8 *ret;
    *out = 0;
    IpFragEntry *free = 0;
    flags = Unk_ov065_02262c5c_Bs(p->fragField);
    if ((flags & 0x3fff) != 0) {
        u32 len, off, hl, end, o8;
        hl = (p->verIhl & 0xf) << 2;
        u32 id = *(u16 *)&p->b4;
        u32 key = ((u32)Unk_ov065_02262c5c_Bs(p->srcAddrHi) << 16) | Unk_ov065_02262c5c_Bs(p->srcAddrLo);
        IpFragEntry *e = sIpFragTable;
        u32 i;
        for (i = 0; i < 8; e++, i++) {
            if (e->cnt != 0 && e->key == key && e->id == id) break;
            if (e->cnt == 0 && free == 0) free = e;
        }
        len = Unk_ov065_02262c5c_Bs(p->totalLength) - hl;
        off = flags & 0x1fff;
        o8 = off << 3;
        end = len + o8;
        if (i == 8) {
            if (free == 0 || end > 0x1000) return 0;
            e = free;
            e->buf = (u8 *)sIpAlloc(hl + 0x100e);
            if (e->buf == 0) return 0;
            e->key = key;
            e->id = id;
            e->total = 0;
            u64 t = OS_GetTick();
            e->tick = (u32)(t >> 16);
            e->data = e->buf + 0xe + hl;
            MI_CpuCopy8(p, e->buf + 0xe, hl);
        }
        if (e->cnt == 8 || end > 0x1000) {
            e->cnt = 0;
            sIpFree(e->buf);
            return 0;
        }
        u32 fin = off + ((len + 7) >> 3);
        flags &= 0x2000;
        if (flags == 0) {
            e->end = end;
            e->total = fin;
        }
        e->start[e->cnt] = off;
        e->fin[e->cnt] = fin;
        e->cnt++;
        MI_CpuCopy8((u8 *)p + hl, e->data + o8, len);
        u32 total = e->total;
        if (total == 0) return 0;
        u32 n, k, cur = 0;
        k = cur;
        n = e->cnt;
        for (; k < n;) {
            if (e->start[k] <= cur && cur < e->fin[k]) {
                cur = e->fin[k];
                k = 0;
            } else {
                k++;
            }
        }
        if (cur < total) return 0;
        ret = e->buf + 0xe;
        *(u16 *)(ret + 2) = Unk_ov065_02262c5c_Bs((u16)(e->end + ((ret[0] & 0xf) << 2)));
        e->cnt = 0;
        *out = 1;
        return ret;
    }
    return (u8 *)p;
}


}








extern "C" {
extern OSThreadInfo data_021fcc2c;
extern void (*sAddrConfiguredCallback)();
extern s32 (*sIpLinkCheckCallback)();
extern void (*sIpFree)(void *);
extern u32 gOwnIp;
extern u8 sArpConflict;
extern u8 sLinkSendError;
extern u16 sMss;
extern u16 sNextEphemeralPort;

u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);

s32 Ssl_GetReadLength(IpSocket *);
void Icmp_SendEchoRequest(u8 *, u32, IpSocket *);
s32 Ssl_Write(u8 *, u32, u8 *, u32, IpSocket *);
s32 Ssl_Consume(u32, IpSocket *);
u8 *Ssl_Read(u32 *, IpSocket *);
s32 Ssl_Shutdown(IpSocket *);
s32 Ssl_Connect(IpSocket *);
s32 Ssl_Accept(IpSocket *);
u8 *Eth_WaitFrame(u32 *);
s32 Ip_IsForMe(u32);
u32 Ip_Checksum(u8 *, u32);

void Arp_ProbeAddressConflict();
void IpSoc_FlushPending();
s32 IpSoc_GetReadLength();
u32 IpSoc_WriteTwo(u8 *, u32, u8 *, u32);
void Tcp_SendTwoBuffers(u8 *, u32, u8 *, u32, IpSocket *, u32);
u32 Tcp_SendSegments(u8 *, u32, IpSocket *, u32);
void IpSoc_Consume(u32);
void Tcp_Consume(u32, IpSocket *);
u8 *IpSoc_Read(u32 *);
u8 *Tcp_Read(u32 *, IpSocket *);
u8 *IpSoc_WaitDatagram(u32 *, IpSocket *);
void IpSoc_TcpWaitClosed();
void IpSoc_TcpShutdown();
void Tcp_Shutdown(IpSocket *);
u32 IpSoc_GetPeer(u16 *, u32 *);
s32 IpSoc_TcpConnect();
s32 Tcp_Connect(IpSocket *);
void IpSoc_TcpListen();
void IpSoc_SetUdpCallback(IpSocketUdpCallback);
void Tcp_Listen(IpSocket *);
void IpSoc_ShareWithThread(OSThread *);
void IpSoc_Release();
void IpSoc_Init();
void IpSoc_Bind(u32, u32, u32);
void IpSoc_SetUdp();
void IpSoc_Unuse();
u32 IpStack_Rand32();
u16 IpSoc_AllocEphemeralPort();
void IpStack_RecvThreadMain();
void Ip_Input(u8 *, u32);
}

static inline u16 Swap16(u16 v) {
    return (v >> 8) | (v << 8);
}

extern "C" {
void Ip_Input(u8 *p, u32 len);
void IpStack_RecvThreadMain();
u16 IpSoc_AllocEphemeralPort();
u32 IpStack_Rand32();
void IpSoc_Unuse();
void IpSoc_SetUdp();
void IpSoc_Bind(u32 a, u32 b, u32 c);
void IpSoc_Init();
void IpSoc_Release();
void IpSoc_ShareWithThread(OSThread *t);
void Tcp_Listen(IpSocket *s);
void IpSoc_SetUdpCallback(IpSocketUdpCallback v);
void IpSoc_TcpListen();
s32 Tcp_Connect(IpSocket *s);
s32 IpSoc_TcpConnect();
u32 IpSoc_GetPeer(u16 *a, u32 *b);
void Tcp_Shutdown(IpSocket *s);
void IpSoc_TcpShutdown();
void IpSoc_TcpWaitClosed();
u8 *IpSoc_WaitDatagram(u32 *out, IpSocket *s);
u8 *Tcp_Read(u32 *out, IpSocket *s);
u8 *IpSoc_Read(u32 *out);
void Tcp_Consume(u32 a, IpSocket *s);
void IpSoc_Consume(u32 a);
u32 Tcp_SendSegments(u8 *a, u32 b, IpSocket *s, u32 flag);
void Tcp_SendTwoBuffers(u8 *a, u32 b, u8 *c, u32 d, IpSocket *s, u32 flag);
u32 IpSoc_WriteTwo(u8 *a, u32 b, u8 *c, u32 d);
s32 IpSoc_GetReadLength();
void IpSoc_FlushPending();
void Arp_ProbeAddressConflict();
}

void Ip_Input(u8 *p, u32 len) {
    s32 flag;
    u32 dst;
    u32 src;
    src = (Swap16(*(u16 *)(p + 0xc)) << 16) | Swap16(*(u16 *)(p + 0xe));
    dst = (Swap16(*(u16 *)(p + 0x10)) << 16) | Swap16(*(u16 *)(p + 0x12));
    if (dst != src) {
        if (Ip_IsForMe(dst) == 0) return;
        if (len < Swap16(*(u16 *)(p + 2))) return;
        if (Ip_Checksum(p, (p[0] & 0xf) * 4) != 0xffff) return;
        {
            u16 c = *(u16 *)(p + 0x12);
            u16 d = *(u16 *)(p + 0x10);
            u32 x = (Swap16(d) << 16) | Swap16(c);
            if (gOwnIp == x) {
                u16 a = *(u16 *)(p + 0xe);
                u16 b = *(u16 *)(p + 0xc);
                Arp_UpdateCache(p - 8, (Swap16(b) << 16) | Swap16(a), 0);
            }
        }
    }
    p = Ip_Reassemble((IpHeader *)p, &flag);
    if (p == 0) return;
    {
        u32 hl = (p[0] & 0xf) * 4;
        u8 *pay = p + hl;
        u32 n = Swap16(*(u16 *)(p + 2)) - hl;
        u8 proto = p[9];
        if (proto == 0x11) {
            Udp_Input((IpHeader *)p, (UdpHeader *)pay, n);
        } else if (gOwnIp != 0) {
            if (proto == 1) {
                Icmp_Input(p, pay, n);
            } else if (proto == 6) {
                Tcp_Input((IpHeader *)p, (TcpHeader *)pay, n);
            }
        }
        if (flag != 0) {
            sIpFree(p - 0xe);
        }
    }
}

void IpStack_RecvThreadMain() {
    u32 len;
    for (;;) {
        u8 *p = Eth_WaitFrame(&len);
        if (len > 0x22) {
            u16 t = Swap16(*(u16 *)(p + 0xc));
            switch (t) {
            case 0x800:
                Ip_Input(p + 0xe, len - 0xe);
                break;
            case 0x806:
                Arp_Input(p + 0xe, len - 0xe);
                break;
            }
        }
        Eth_PopFrame();
    }
}

u16 IpSoc_AllocEphemeralPort() {
    s32 found;
    do {
        found = 0;
        sNextEphemeralPort++;
        if (sNextEphemeralPort < 0x400 || sNextEphemeralPort >= 0x1388) {
            sNextEphemeralPort = 0x400;
        }
        OSThread *t;
        for (t = data_021fcc2c.list; t != 0; t = t->next) {
            IpSocket *s = (IpSocket *)t->specific[0];
            if (s != 0 && s->ownerThread != 0 && s->localPort == sNextEphemeralPort) {
                found = 1;
                break;
            }
        }
    } while (found != 0);
    return sNextEphemeralPort;
}

u32 IpStack_Rand32() {
    MATHRandContext32 *g = &sIpRandState;
    g->x = _ll_mul(g->mul, g->x) + g->add;
    return (u32)(g->x >> 32);
}

void IpSoc_Use(IpSocket *s) {
    data_021fcc2c.current->specific[0] = s;
}

void IpSoc_Unuse() {
    data_021fcc2c.current->specific[0] = 0;
}

void IpSoc_SetUdp() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        s->state = 10;
        s->rxLen = 0;
    }
}

void IpSoc_Bind(u32 a, u32 b, u32 c) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (c == 0x7f000001) {
            c = gOwnIp;
        }
        s->boundRemotePort = b;
        s->remotePort = s->boundRemotePort;
        s->boundRemoteAddr = c;
        s->remoteAddr = s->boundRemoteAddr;
        if (a == 0) {
            s->localPort = IpSoc_AllocEphemeralPort();
        } else {
            s->localPort = a;
        }
    }
}

void IpSoc_Init() {
    OSThread *c = data_021fcc2c.current;
    IpSocket *s = (IpSocket *)c->specific[0];
    if (s != 0) {
        s->ownerThread = c;
        s->state = 0;
        s->rxLen = 0;
        s->pendingTxLen = 0;
        s->udpCallback = 0;
    }
}

void IpSoc_Release() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        s->ownerThread = 0;
    }
}

void IpSoc_ShareWithThread(OSThread *t) {
    t->specific[0] = data_021fcc2c.current->specific[0];
}

void Tcp_Listen(IpSocket *s) {
    s->sendNext = IpStack_Rand32();
    s->state = 1;
    s->waitReason = 1;
    OS_SleepThread(0);
}

extern "C" void IpSoc_SetUdpCallback(IpSocketUdpCallback v) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        s->udpCallback = v;
    }
}

void IpSoc_TcpListen() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->useSsl != 0) {
            Ssl_Accept(s);
        } else {
            Tcp_Listen(s);
        }
    }
}

s32 Tcp_Connect(IpSocket *s) {
    u32 i;
    u32 seed = IpStack_Rand32();
    i = 0;
    do {
        s->sendNext = seed;
        s->state = 2;
        s->handshakeTime = (u32)(OS_GetTick() >> 16);
        Tcp_SendControl(s, 2, 0x18);
        u32 ints = OS_DisableInterrupts();
        if (gOwnIp != 0) {
            s->waitReason = 1;
            OS_SleepThread(0);
        }
        OS_RestoreInterrupts(ints);
        if (s->state == 4) {
            return 0;
        }
        if (gOwnIp == 0) break;
        i++;
    } while (i < 3);
    return 1;
}

s32 IpSoc_TcpConnect() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->useSsl != 0) {
            return Ssl_Connect(s);
        }
        return Tcp_Connect(s);
    }
    return 1;
}

u32 IpSoc_GetPeer(u16 *a, u32 *b) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->state == 4 || s->state == 10) {
            if (a != 0) {
                *a = s->remotePort;
            }
            if (b != 0) {
                *b = s->localAddr;
            }
            return s->remoteAddr;
        }
    }
    return 0;
}

void Tcp_Shutdown(IpSocket *s) {
    OS_YieldThread();
    u8 st = s->state;
    if ((u8)(st + 0xfd) <= 1) {
        Tcp_SendFinAck(s, 0x19);
        s->state = 7;
    } else if (st != 0) {
        Tcp_SendAck(s, 0x1a);
    }
}

void IpSoc_TcpShutdown() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->useSsl != 0) {
            Ssl_Shutdown(s);
        } else {
            Tcp_Shutdown(s);
        }
    }
}

void IpSoc_TcpWaitClosed() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        s32 t = (s32)(OS_GetTick() >> 16);
        while (sIpLinkCheckCallback() != 0 && s->state != 0 && (s32)(OS_GetTick() >> 16) - t < 0x27) {
            IpStack_Yield();
        }
    }
}

u8 *IpSoc_WaitDatagram(u32 *out, IpSocket *s) {
    while (s->rxLen == 0) {
        s->waitReason = 3;
        OS_SleepThread(0);
    }
    *out = s->rxLen;
    return s->rxBuf;
}

u8 *Tcp_Read(u32 *out, IpSocket *s) {
    if (s->rxLen == 0 && s->state == 4) {
        while (s->rxLen == 0 && s->state == 4) {
            s->waitReason = 2;
            OS_SleepThread(0);
        }
    } else {
        OS_YieldThread();
    }
    *out = s->rxLen;
    if (*out != 0) {
        return s->rxBuf;
    }
    return 0;
}

u8 *IpSoc_Read(u32 *out) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if ((u8)(s->state + 0xf6) <= 1) {
            return IpSoc_WaitDatagram(out, s);
        }
        if (s->useSsl != 0) {
            return Ssl_Read(out, s);
        }
        return Tcp_Read(out, s);
    }
    *out = 0;
    return 0;
}

void Tcp_Consume(u32 a, IpSocket *s) {
    u32 ints = OS_DisableInterrupts();
    u32 n = s->rxLen;
    if (a >= n) {
        s->rxLen = 0;
    } else {
        u8 *p = s->rxBuf;
        u8 *q = p + a;
        n -= a;
        s->rxLen = n;
        q = n ? q : q;
        memmove(p, q, n);
    }
    OS_RestoreInterrupts(ints);
    if (s->state != 10 && s->state != 11 && s->rxLen == 0) {
        Tcp_SendAck(s, 0x1b);
    }
}

void IpSoc_Consume(u32 a) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->useSsl != 0) {
            Ssl_Consume(a, s);
            return;
        }
        Tcp_Consume(a, s);
    }
}

u32 Tcp_SendSegments(u8 *a, u32 b, IpSocket *s, u32 flag) {
    u32 r4 = 1;
    u32 win;
    u32 cnt;
    u32 budget;
    if (flag != 0) {
        win = 1;
    } else {
        win = s->peerWindow;
    }
    cnt = s->rxSegmentCount;
    budget = cnt * 2 + 4;
    while (b != 0 && s->state == 4) {
        r4 = s->peerMss;
        if (r4 >= win) r4 = win;
        if (sMss < r4) r4 = sMss;
        if (flag == 0) r4 &= ~1;
        if (b < r4) r4 = b;
        {
            u32 t = budget + (s->rxSegmentCount - cnt);
            cnt = s->rxSegmentCount;
            budget = t - 1;
            if (t == 0) r4 = 0;
        }
        if (r4 == 0) break;
        win -= r4;
        Tcp_SendSegment(a, r4, s, 0x18, 0);
        OS_YieldThread();
        a += r4;
        b -= r4;
    }
    return r4;
}

void Tcp_SendTwoBuffers(u8 *a, u32 b, u8 *c, u32 d, IpSocket *s, u32 flag) {
    if (Tcp_SendSegments(a, b, s, flag) != 0) {
        if (d != 0) {
            Tcp_SendSegments(c, d, s, 0);
        }
    }
}

u32 Tcp_Write(u8 *a, u32 b, u8 *c, u32 d, IpSocket *s) {
    s32 total = 0;
    u32 prev;
    s32 now;
    s32 t1;
    u32 sent;
    u32 flag;
    s->rxSegmentCount = 0;
    flag = 0;
    now = (s32)(OS_GetTick() >> 16);
    while (sIpLinkCheckCallback() != 0 && b != 0 && s->state == 4 && (s32)(OS_GetTick() >> 16) - now < 0x9f) {
        prev = s->sendNext;
        Tcp_SendTwoBuffers(a, b, c, d, s, flag);
        t1 = (s32)(OS_GetTick() >> 16);
        for (;;) {
            IpStack_Yield();
            if (sIpLinkCheckCallback() == 0) break;
            if (s->state != 4) break;
            if (s->sendNext == s->ackedSeq) break;
            if ((s32)(OS_GetTick() >> 16) - t1 >= 0xf) break;
            if (flag != 0 && s->peerWindow != 0) break;
        }
        sent = s->ackedSeq - prev;
        total += sent;
        if (sent != 0) {
            now = (s32)(OS_GetTick() >> 16);
        }
        s->sendNext = s->ackedSeq;
        if (s->state == 4 && s->peerWindow == 0 && sent == 0) {
            if (flag == 0) {
                t1 = (s32)(OS_GetTick() >> 16);
                while (sIpLinkCheckCallback() != 0 && (s32)(OS_GetTick() >> 16) - t1 < 0xf) {
                    IpStack_Yield();
                    if (s->peerWindow != 0) break;
                }
                if (s->peerWindow == 0) {
                    flag = 1;
                }
            }
        } else {
            flag = 0;
        }
        if (sent >= b) {
            u32 x = sent - b;
            a = c + x;
            b = d - x;
            c = 0;
            d = 0;
        } else {
            a = a + sent;
            b = b - sent;
        }
    }
    return total;
}

u32 IpSoc_WriteTwo(u8 *a, u32 b, u8 *c, u32 d) {
    u32 r;
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        u8 st = s->state;
        if (st == 10) {
            if (b != 0) {
                Udp_Send(a, b, s);
            }
            if (d != 0) {
                Udp_Send(c, d, s);
            }
            r = b + d;
        } else if (st == 11) {
            if (b != 0) {
                Icmp_SendEchoRequest(a, b, s);
            }
            if (d != 0) {
                Icmp_SendEchoRequest(c, d, s);
            }
            r = b + d;
        } else {
            if (s->useSsl != 0) {
                r = Ssl_Write(a, b, c, d, s);
            } else {
                r = Tcp_Write(a, b, c, d, s);
            }
        }
        if (sLinkSendError == 0) {
            return r;
        }
    }
    return 0;
}

u32 IpSoc_Write(const u8 *a, u32 b) {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        u32 r;
        if (s->pendingTxLen != 0) {
            r = IpSoc_WriteTwo(s->pendingTx, s->pendingTxLen, (u8 *)a, b);
            if (r < s->pendingTxLen) {
                memmove(s->pendingTx, s->pendingTx + r, s->pendingTxLen - r);
                s->pendingTxLen = s->pendingTxLen - r;
                return 0;
            }
            r = r - s->pendingTxLen;
            s->pendingTxLen = 0;
            return r;
        }
        return IpSoc_WriteTwo((u8 *)a, b, 0, 0);
    }
    return 0;
}

s32 IpSoc_GetReadLength() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    s32 r;
    if (s != 0) {
        if (s->useSsl != 0) {
            r = Ssl_GetReadLength(s);
        } else {
            r = s->rxLen;
        }
        if (r == 0) {
            if (s->state != 4 && (u8)(s->state + 0xf6) > 1) {
                return -1;
            }
        }
        return r;
    }
    return 0;
}

void IpSoc_FlushPending() {
    IpSocket *s = (IpSocket *)data_021fcc2c.current->specific[0];
    if (s != 0) {
        if (s->pendingTxLen != 0) {
            IpSoc_WriteTwo(s->pendingTx, s->pendingTxLen, 0, 0);
            s->pendingTxLen = 0;
        }
    }
}

void Arp_ProbeAddressConflict() {
    s32 start;
    sAddrConfiguredCallback();
    if (gOwnIp != 0) {
        Arp_SendRequest(gOwnIp);
        OS_Sleep(0x64);
        Arp_SendRequest(gOwnIp);
        start = (s32)(OS_GetTick() >> 16);
        while (sIpLinkCheckCallback() != 0 && (s32)(OS_GetTick() >> 16) - start < 0x17) {
            if (sArpConflict != 0) {
                IpStack_ResetAddress(4);
                return;
            }
            OS_Sleep(0x64);
        }
    }
}




extern "C" {
#define data_ov065_0228ef2a (sTimerThreadTxBuf + 0x2a)
extern s32 (*sIpLinkCheckCallback)(void);
extern void (*sIpIdleCallback)(void);
extern void (*sIpFree)(void *);
extern u32 sIpStackStatus;
extern u32 sNetmask;
extern u32 sDhcpServerId;
extern u32 sIpStackFlags;
extern u32 sGateway;
extern u32 sDhcpRetryTime;
extern u32 sIpTimerStopRequest;
extern u32 gOwnIp;
extern u32 sDhcpLeaseTime;
extern u32 sDhcpRequestedIp;
extern u32 sDnsServers[2];
extern ArpCacheEntry sArpCache[8];
extern IpSocket sTimerThreadSoc;
extern u8 sTimerThreadTxBuf[];
extern u8 sTimerThreadRxBuf[];
extern IpFragEntry sIpFragTable[8];
extern OSThreadInfo data_021fcc2c;


u8 *IpSoc_Read(u32 *len);
void IpSoc_Consume(u32 len);
s32 IpSoc_GetReadLength(void);
void Ssl_ExpireSessions(u32 a);
void IpSoc_Init(void);
void IpSoc_SetUdp(void);
void IpSoc_Bind(u32 a, u32 b, u32 c);
void IpSoc_Release(void);
void IpSoc_Unuse(void);
void Arp_ProbeAddressConflict(void);
}

static inline u32 RD16(const u8 *p) { return (u16)(p[0] << 8 | p[1]); }
#define BS16(x) ((u16)((((s32)(x)) >> 8) | (((s32)(x)) << 8)))

extern "C" {
s32 Dns_Query(const u8 *name, u32 type, s32 xid);
u32 IpAddr_ParseDecimal(const u8 *p, const u8 **end);
u8 *Dns_SkipName(u8 *p);
u8 *Dhcp_BuildHeader(u8 *buf, u32 msgtype, u32 *xidout);
u8 *Dhcp_PadTo(u32 a, u32 size, u8 *dst, u32 used);
u32 Dhcp_SendRequest(u32 mode);
u32 Dhcp_SendDiscover(void);
s32 Dhcp_WaitReply(u32 xid, s32 i);
s32 Dhcp_Request(u32 *out, s32 mode);
s32 Dhcp_Discover(void);
void Dhcp_SendRelease(void);

extern "C" {
void IpStack_TimerThreadMain(void);
u8 *Dhcp_BuildHeader(u8 *buf, u32 msgtype, u32 *xidout);
u8 *Dhcp_PadTo(u32 a, u32 size, u8 *dst, u32 used);
u32 Dhcp_SendDiscover(void);
u32 Dhcp_SendRequest(u32 mode);
s32 Dhcp_WaitReply(u32 xid, s32 i);
s32 Dhcp_Discover(void);
s32 Dhcp_Request(u32 *out, s32 mode);
void Dhcp_SendRelease(void);
u8 *Dns_SkipName(u8 *p);
s32 Dns_Query(const u8 *name, u32 type, s32 xid);
u32 IpAddr_ParseDecimal(const u8 *p, const u8 **end);
s32 IpAddr_Parse(const u8 *s, u32 *out);
s32 Dns_QueryServer(const u8 *a, u32 server, s32 c);
}

void IpStack_TimerThreadMain(void) {
    s32 state;
    s32 first;
    u32 cnt;
    u32 now;
    s32 i;
    ArpCacheEntry *e;
    OSThread *n;
    s32 j;
    IpFragEntry *q;

    sIpTimerStopRequest = 0;
    MI_CpuFill8(&sTimerThreadSoc, 0, sizeof(sTimerThreadSoc));
    sTimerThreadSoc.rxBufSize = 0x180;
    sTimerThreadSoc.rxBuf = sTimerThreadRxBuf;
    sTimerThreadSoc.txBufSize = 0x180;
    sTimerThreadSoc.txBuf = sTimerThreadTxBuf;
    IpSoc_Use(&sTimerThreadSoc);
    state = 0;
    first = 1;
    cnt = 1;
    sIpStackStatus = 1;
    for (;;) {
        OS_Sleep(1000);
        if (sIpTimerStopRequest != 0) {
            break;
        }
        now = (u32)(OS_GetTick() >> 16);
        if (sIpLinkCheckCallback() != 0) {
            cnt--;
            if (cnt == 0) {
                if ((sIpStackFlags & 1) != 0) {
                    if (state == 0) {
                        Arp_ProbeAddressConflict();
                        state = 1;
                    }
                } else {
                    switch (state) {
                    case 0:
                        if (first != 0) {
                            sIpStackStatus = 2;
                            first = 0;
                        }
                        if (Dhcp_Discover() == 0 || Dhcp_Request(&cnt, 0) == 0) {
                            Arp_ProbeAddressConflict();
                            state = 3;
                        } else {
                            state = 1;
                        }
                        break;
                    case 1:
                        if (Dhcp_Request(&cnt, 1) == 0) {
                            if (cnt < 0x3c) {
                                state = 2;
                            }
                        }
                        break;
                    case 2:
                        if (Dhcp_Request(&cnt, 2) != 0) {
                            state = 1;
                        } else if (cnt < 0x3c) {
                            IpStack_ResetAddress(3);
                            state = 0;
                            cnt = 1;
                        }
                        break;
                    case 3:
                        break;
                    }
                }
            }
        } else {
            IpStack_ResetAddress(1);
            state = 0;
            cnt = 1;
        }
        for (i = 0, e = sArpCache; i < 8; e++, i++) {
            if (e->ipAddr != 0) {
                if ((s16)(now - e->lastUsed) > 0x3bd) {
                    e->ipAddr = 0;
                }
            }
        }
        for (n = data_021fcc2c.list; n != NULL; n = n->next) {
            IpSocket *b = (IpSocket *)n->specific[0];
            if (b != NULL && b->ownerThread != 0) {
                u32 st = b->state;
                if (st == 3 && (s32)(now - b->handshakeTime) > 0x27) {
                    b->state = 1;
                    b->remotePort = b->boundRemotePort;
                    b->remoteAddr = b->boundRemoteAddr;
                } else if (st == 2 && (s32)(now - b->handshakeTime) > 0x27) {
                    if (b->waitReason == 1) {
                        b->state = 0;
                        b->waitReason = 0;
                        OS_WakeupThreadDirect(b->ownerThread);
                    }
                }
            }
        }
        for (j = 0, q = sIpFragTable; j < 8; q++, j++) {
            if (q->cnt != 0) {
                if ((s32)(now - q->tick) > 0xef) {
                    sIpFree(q->buf);
                    q->cnt = 0;
                }
            }
        }
        Ssl_ExpireSessions(now);
        if (sIpIdleCallback != NULL) {
            sIpIdleCallback();
        }
    }
    if ((sIpStackFlags & 1) == 0 && state != 3) {
        Dhcp_SendRelease();
    }
    IpSoc_Unuse();
}

u8 *Dhcp_BuildHeader(u8 *buf, u32 msgtype, u32 *xidout) {
    u64 m;
    u32 hi;
    MI_CpuFill8(buf, 0, 0xec);
    *(u16 *)(buf + 0) = 0x101;
    buf[2] = 6;
    m = _ll_mul(sIpRandState.mul, sIpRandState.x);
    sIpRandState.x = sIpRandState.add + m;
    m = sIpRandState.x;
    hi = (u32)(m >> 32);
    if (xidout != 0) {
        *xidout = hi;
    }
    *(u16 *)(buf + 4) = BS16((u16)(hi >> 16));
    *(u16 *)(buf + 6) = BS16((u16)hi);
    *(u16 *)(buf + 0xc) = BS16((u16)(gOwnIp >> 16));
    *(u16 *)(buf + 0xe) = BS16((u16)gOwnIp);
    MI_CpuCopy8(sOwnMac, buf + 0x1c, 6);
    *(u16 *)(buf + 0xec) = 0x8263;
    *(u16 *)(buf + 0xee) = 0x6353;
    *(u16 *)(buf + 0xf0) = 0x135;
    buf[0xf2] = msgtype;
    buf[0xf3] = 0x3d;
    buf[0xf4] = 7;
    buf[0xf5] = 1;
    MI_CpuCopy8(sOwnMac, buf + 0xf6, 6);
    buf[0xfc] = 0xc;
    buf[0xfd] = 0xa;
    MI_CpuCopy8(sDhcpHostName, buf + 0xfe, 0xa);
    buf[0x108] = 0x37;
    buf[0x109] = 3;
    buf[0x10a] = 1;
    buf[0x10b] = 3;
    buf[0x10c] = 6;
    return buf + 0x10d;
}

u8 *Dhcp_PadTo(u32 a, u32 size, u8 *dst, u32 used) {
    if (used < size) {
        u32 n = size - used;
        MI_CpuFill8(dst, a, n);
        dst += n;
    }
    return dst;
}

u32 Dhcp_SendDiscover(void) {
    u32 xid;
    u8 *const buf = data_ov065_0228ef2a;
    u8 *p = Dhcp_BuildHeader(buf, 1, &xid);
    if (sDhcpRequestedIp != 0) {
        p[0] = 0x32;
        p[1] = 4;
        p[2] = (u16)(sDhcpRequestedIp >> 16) >> 8;
        p[3] = sDhcpRequestedIp >> 16;
        p[4] = (u16)sDhcpRequestedIp >> 8;
        p[5] = sDhcpRequestedIp;
        p += 6;
    }
    *p = 0xff;
    p++;
    u8 *e = Dhcp_PadTo(0, 0x12c, p, p - buf);
    IpSoc_Write(buf, e - buf);
    return xid;
}

u32 Dhcp_SendRequest(u32 mode) {
    u32 xid;
    u8 *const buf = data_ov065_0228ef2a;
    u8 *p = Dhcp_BuildHeader(buf, 3, &xid);
    if (mode == 0) {
        p[0] = 0x32;
        p[1] = 4;
        p[2] = (u16)(sDhcpRequestedIp >> 16) >> 8;
        p[3] = sDhcpRequestedIp >> 16;
        p[4] = (u16)sDhcpRequestedIp >> 8;
        p[5] = sDhcpRequestedIp;
        p[6] = 0x36;
        p[7] = 4;
        p[8] = (u16)(sDhcpServerId >> 16) >> 8;
        p[9] = sDhcpServerId >> 16;
        p[10] = (u16)sDhcpServerId >> 8;
        p[11] = sDhcpServerId;
        p += 12;
    }
    *p = 0xff;
    p++;
    u8 *e = Dhcp_PadTo(0, 0x12c, p, p - buf);
    IpSoc_Write(buf, e - buf);
    return xid;
}

s32 Dhcp_WaitReply(u32 xid, s32 i) {
    u32 len;
    s32 result;
    u32 start;
    s32 timeout;
    u8 *p;

    timeout = (i + 1) * 15;
    start = (u32)(OS_GetTick() >> 16);
    result = 0;
    goto test;
loop:
    if (IpSoc_GetReadLength() == 0) {
        IpStack_Yield();
        goto test;
    }
    {
        p = IpSoc_Read(&len);
        if (len > 0xf0 && p[0] == 2) {
            u32 rx = (BS16(*(u16 *)(p + 4)) << 16) | BS16(*(u16 *)(p + 6));
            if (xid == rx && Eth_MacDiffers(p + 0x1c, sOwnMac) == 0) {
                u8 *o;
                u8 *end;
                u32 ip;
                result = 3;
                ip = ((u16)(p[0x10] << 8 | p[0x11]) << 16) | (u16)(p[0x12] << 8 | p[0x13]);
                end = p + len;
                if (p[0xec] == 0x63 && p[0xed] == 0x82 && p[0xee] == 0x53 && ((o = p + 0xf0), p[0xef] == 0x63)) {
                    s32 c;
                    goto otest;
                    {
                    oloop:
                        if (c == 0) {
                            goto otest;
                        }
                        switch (c) {
                        case 1:
                            sNetmask = ((u16)(o[1] << 8 | o[2]) << 16) | (u16)(o[3] << 8 | o[4]);
                            break;
                        case 3:
                            sGateway = ((u16)(o[1] << 8 | o[2]) << 16) | (u16)(o[3] << 8 | o[4]);
                            break;
                        case 6:
                            if (o[0] < 8) {
                                sDnsServers[1] = 0;
                            } else {
                                sDnsServers[1] = ((u16)(o[5] << 8 | o[6]) << 16) | (u16)(o[7] << 8 | o[8]);
                            }
                            sDnsServers[0] = ((u16)(o[1] << 8 | o[2]) << 16) | (u16)(o[3] << 8 | o[4]);
                            break;
                        case 0x33:
                            sDhcpLeaseTime = ((u16)(o[1] << 8 | o[2]) << 16) | (u16)(o[3] << 8 | o[4]);
                            break;
                        case 0x35:
                            switch (o[1]) {
                            case 2:
                                sDhcpRequestedIp = ip;
                                result = 1;
                                break;
                            case 5:
                                gOwnIp = ip;
                                result = 2;
                                break;
                            }
                            break;
                        case 0x36:
                            sDhcpServerId = ((u16)(o[1] << 8 | o[2]) << 16) | (u16)(o[3] << 8 | o[4]);
                            break;
                        }
                        o += o[0] + 1;
                    otest:
                        if (o < end) {
                            c = *o++;
                            if (c != 0xff) {
                                goto oloop;
                            }
                        }
                    }
                }
            }
        }
        IpSoc_Consume(len);
    }
test:
    if (sIpLinkCheckCallback() != 0 && result == 0) {
        u32 now = (u32)(OS_GetTick() >> 16);
        if ((s32)(now - start) < timeout) {
            goto loop;
        }
    }
    return result;
}

s32 Dhcp_Discover(void) {
    s32 r;
    s32 i;
    IpSoc_Init();
    IpSoc_SetUdp();
    IpSoc_Bind(0x44, 0x43, -1);
    for (i = 0; i < 4; i++) {
        r = Dhcp_WaitReply(Dhcp_SendDiscover(), i);
        if (r == 1) {
            break;
        }
    }
    IpSoc_Release();
    if (r == 1) {
        return 1;
    }
    return 0;
}

s32 Dhcp_Request(u32 *out, s32 mode) {
    s32 r;
    s32 i;
    u32 v;
    IpSoc_Init();
    IpSoc_SetUdp();
    if (mode == 1) {
        IpSoc_Bind(0x44, 0x43, sDhcpServerId);
    } else {
        IpSoc_Bind(0x44, 0x43, -1);
    }
    for (i = 0; i < 4; i++) {
        r = Dhcp_WaitReply(Dhcp_SendRequest(mode), i);
        if (r != 0) {
            break;
        }
    }
    IpSoc_Release();
    if (r == 2) {
        *out = sDhcpLeaseTime >> 1;
        sDhcpRetryTime = (sDhcpLeaseTime * 3) >> 3;
        return 1;
    }
    v = sDhcpRetryTime >> 1;
    sDhcpRetryTime = v;
    *out = v;
    switch (mode) {
    case 1:
        if (v < 0x3c) {
            *out = 1;
            sDhcpRetryTime = sDhcpLeaseTime >> 3;
        }
        break;
    case 2:
        if (v < 0x3c) {
            *out = 1;
        }
        break;
    }
    return 0;
}

void Dhcp_SendRelease(void) {
    IpSoc_Init();
    IpSoc_SetUdp();
    IpSoc_Bind(0x44, 0x43, sDhcpServerId);
    u8 *const buf = data_ov065_0228ef2a;
    u8 *p = Dhcp_BuildHeader(buf, 7, 0);
    *p = 0xff;
    p++;
    u8 *e = Dhcp_PadTo(0, 0x12c, p, p - buf);
    IpSoc_Write(buf, e - buf);
    IpSoc_Release();
}

u8 *Dns_SkipName(u8 *p) {
    u32 c = *p++;
    while (c != 0) {
        if ((c & 0xc0) == 0xc0) {
            p++;
            return p;
        }
        u8 *n = p + c;
        p = n + 1;
        c = *n;
    }
    return p;
}

s32 Dns_Query(const u8 *name, u32 type, s32 xid) {
    struct {
        u32 len;
        u16 id;
        u16 flags;
        u16 qd;
        u16 an;
        u16 ns;
        u16 ar;
        u8 name[0x30];
    } l;
    u8 *w;
    u8 *lp;
    u32 c;
    s32 result;

    l.id = BS16(xid);
    if (type == 1) {
        l.flags = 1;
    } else {
        l.flags = 0x1001;
    }
    l.qd = 0x100;
    l.an = 0;
    l.ns = 0;
    l.ar = 0;
    lp = l.name;
    w = lp + 1;
    l.len = 0;
    c = *name++;
    while (c != 0) {
        if (c != '.') {
            if (w - (u8 *)&l.id >= 0x3c) {
                return -1;
            }
            *w = c;
            w++;
            l.len++;
        } else {
            *lp = l.len;
            lp = w;
            w++;
            l.len = 0;
        }
        c = *name++;
    }
    *lp = l.len;
    *w = 0;
    w[1] = type >> 8;
    w[2] = type;
    w[3] = 0;
    w[4] = 1;
    IpSoc_Write((u8 *)&l.id, (w + 5) - (u8 *)&l.id);

    result = 0;
    u32 start = (u32)(OS_GetTick() >> 16);
    goto test;
loop:
    if (IpSoc_GetReadLength() == 0) {
        IpStack_Yield();
        goto test;
    }
    {
        u8 *p = IpSoc_Read(&l.len);
        if (l.len > 0xc) {
            u32 id = BS16(*(u16 *)p);
            if (xid == id) {
                u32 rc = p[3] & 0xf;
                if (rc == 3) {
                    result = -1;
                } else if (rc == 0) {
                    u32 qd;
                    u32 n;
                    u8 *end;
                    u8 *q;
                    end = p + l.len;
                    qd = (u16)(p[4] << 8 | p[5]);
                    q = p + 0xc;
                    n = qd - 1;
                    if (qd != 0) {
                        do {
                            q = Dns_SkipName(q) + 4;
                        } while (n--);
                    }
                    while (q < end) {
                        u32 rdl;
                        u8 *a;
                        u8 *b;
                        u8 *pa;
                        u8 *pb;
                        q = Dns_SkipName(q);
                        rdl = RD16(q + 8);
                        if (type == RD16(q)) {
                            a = q + 8;
                            pa = a + rdl;
                            b = q + 6;
                            pb = b + rdl;
                            result = (RD16(pb) << 16) | RD16(pa);
                            break;
                        }
                        q += rdl + 10;
                    }
                }
            }
        }
        IpSoc_Consume(l.len);
    }
test:
    if (sIpLinkCheckCallback() != 0 && result == 0) {
        u32 now = (u32)(OS_GetTick() >> 16);
        if ((s32)(now - start) < 15) {
            goto loop;
        }
    }
    return result;
}

u32 IpAddr_ParseDecimal(const u8 *p, const u8 **end) {
    *end = p;
    u32 n = 0;
    for (;;) {
        u8 d = *p - '0';
        if (d > 9) {
            break;
        }
        n = n * 10 + d;
        p++;
        *end = p;
    }
    return n;
}

s32 IpAddr_Parse(const u8 *s, u32 *out) {
    const u8 *end;
    u32 acc = 0;
    s32 i = 0;
    do {
        acc <<= 8;
        u32 v = IpAddr_ParseDecimal(s, &end);
        if (s == end) {
            return 0;
        }
        s = end;
        if (v > 0xff || (i != 3 && (s = end + 1, *end != '.')) || (i == 3 && *s != 0)) {
            return 0;
        }
        acc |= v;
        i++;
    } while (i < 4);
    *out = acc;
    return 1;
}

s32 Dns_QueryServer(const u8 *a, u32 server, s32 c) {
    s32 r;
    if (server == 0) {
        return -1;
    } else {
        IpSoc_Init();
        IpSoc_SetUdp();
        IpSoc_Bind(0, 0x35, server);
        r = Dns_Query(a, 1, c);
        IpSoc_Release();
    }
    return r;
}


}




extern "C" {
s32 Dns_QueryServer(const u8 *, u32, s32);
s32 IpAddr_Parse(const u8 *, u32 *);
extern u32 sDnsServers[2];

extern "C" {
s32 Dns_Resolve(const char *self);
}

s32 Dns_Resolve(const char *self) {
    struct {
        u8 flag[2];
        s32 res;
        u16 port[2];
    } l;
    s32 i;
    u8 *pf;
    u16 *pp;
    u32 *pt;
    s32 j;
    MATHRandContext32 *g = &sIpRandState;
    g->x = _ll_mul(g->mul, g->x) + g->add;
    l.port[0] = (u32)(((g->x >> 32) * 0x10000) >> 32);
    g->x = _ll_mul(g->mul, g->x) + g->add;
    l.port[1] = (u32)(((g->x >> 32) * 0x10000) >> 32);
    if (IpAddr_Parse((const u8 *)self, (u32 *)&l.res)) {
        return l.res;
    }
    l.flag[0] = 1;
    l.flag[1] = 1;
    for (i = 0; i < 3; i++) {
        j = 0;
        pf = l.flag;
        pp = l.port;
        pt = sDnsServers;
        for (; j < 2; pf++, pp++, pt++, j++) {
            if (*pf) {
                l.res = Dns_QueryServer((const u8 *)self, *pt, *pp);
                if (l.res != 0 && l.res != -1) {
                    goto done;
                }
                if (l.res == -1) {
                    *pf = 0;
                }
            }
        }
    }
done:
    if (l.res == -1) {
        l.res = 0;
    }
    return l.res;
}

}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02261638) {
    HOST_OVERLAY_VAR(data_ov065_0228f3c0),
    HOST_OVERLAY_VAR(sIpRecvThreadStack),
    HOST_OVERLAY_VAR(sIpFragTable),
    HOST_OVERLAY_VAR(sTimerThreadTxBuf),
    HOST_OVERLAY_VAR(sTimerThreadRxBuf),
    HOST_OVERLAY_VAR(sIpTimerThread),
    HOST_OVERLAY_VAR(sIpRecvThread),
    HOST_OVERLAY_VAR(sTimerThreadSoc),
    HOST_OVERLAY_VAR(sTcpResetSoc),
    HOST_OVERLAY_VAR(sArpCache),
    HOST_OVERLAY_VAR(data_ov065_0228ec1c),
    HOST_OVERLAY_VAR(sIpRandState),
    HOST_OVERLAY_VAR(sLlcSnapHeader),
    HOST_OVERLAY_VAR(sDhcpHostName),
    HOST_OVERLAY_VAR(sDnsServers),
    HOST_OVERLAY_VAR(sBroadcastMac),
    HOST_OVERLAY_VAR(sOwnMac),
    HOST_OVERLAY_VAR(sRecvRingSize),
    HOST_OVERLAY_VAR(sDhcpServerId),
    HOST_OVERLAY_VAR(sRecvRingWaiter),
    HOST_OVERLAY_VAR(sDhcpRequestedIp),
    HOST_OVERLAY_VAR(sDhcpLeaseTime),
    HOST_OVERLAY_VAR(sAddrConfiguredCallback),
    HOST_OVERLAY_VAR(sIpTimerStopRequest),
    HOST_OVERLAY_VAR(sIpFree),
    HOST_OVERLAY_VAR(sIpIdleCallback),
    HOST_OVERLAY_VAR(sRecvRingWrite),
    HOST_OVERLAY_VAR(sGateway),
    HOST_OVERLAY_VAR(sDhcpRetryTime),
    HOST_OVERLAY_VAR(sRecvRingRead),
    HOST_OVERLAY_VAR(sRecvRingBuf),
    HOST_OVERLAY_VAR(sIpStackStatus),
    HOST_OVERLAY_VAR(sIcmpEchoReplyEnabled),
    HOST_OVERLAY_VAR(sIpLinkCheckCallback),
    HOST_OVERLAY_VAR(sIpThreadPriority),
    HOST_OVERLAY_VAR(sNetmask),
    HOST_OVERLAY_VAR(sIpStackFlags),
    HOST_OVERLAY_VAR(sIpAlloc),
    HOST_OVERLAY_VAR(gOwnIp),
    HOST_OVERLAY_VAR(sIpYieldMode),
    HOST_OVERLAY_VAR(sIpIdCounter),
    HOST_OVERLAY_VAR(sIcmpSeq),
    HOST_OVERLAY_VAR(sMss),
    HOST_OVERLAY_VAR(sNextEphemeralPort),
    HOST_OVERLAY_VAR(sLinkSendError),
    HOST_OVERLAY_VAR(sArpConflict),
    HOST_OVERLAY_VARS_END
};
