#include "ds_div.h"
#include "host_shared_calls.h"
#include "uptr.h"
#include "types.h"
#include "net/SockAddrIn.h"
#include "net/AossParam.h"
#include "proto/ov001/unk_ov001_02200680.h"
#include "proto/ov001/unk_ov001_02202c44.h"

struct AossRandState {
    u32 seed;
    u32 mul;
    u32 add;
};

struct AossSocConfig {
    u32 unk_00;
    s32 (*unk_04)(s32, s32);
    s32 (*unk_08)(s32, s32);
    u32 pad_0c;
    u32 ipAddress;
    u32 netmask;
    u32 gateway;
    u8 pad_1c[8];
    u32 unk_24;
    u32 unk_28;
    u8 pad_2c[0x2c];
};

struct AossSession {
    u8 *clientName;
    s32 clientNameLength;
    u32 requestedKeyTypes;
    u32 receivedKeyTypes;
    u32 apAddress;
    u32 netmask;
    s8 useUnicast;
    s8 clientInfoTag;
};

struct AossRc4State {
    u32 i;
    u32 j;
    u8 *s;
    u32 n;
};

struct AossKeyBlock {
    u8 pad_00[4];
    s32 len;
    u8 ssid[0x28];
    u8 key1[0x40];
    u8 key2[0x40];
    u8 key3[0x40];
    u8 key4[0x40];
};

struct AossPollFd;
struct AossScanList;

extern "C" s32 Aoss_SocAlloc(s32 a, s32 b);
extern "C" s32 Aoss_SocFree(s32 a, s32 b);

extern "C" AossRandState sAossRand;
extern "C" AossSocConfig sAossSocConfig;
extern "C" AossSession sAossSession;
extern "C" s16 sAossDefaultRetry[2];
extern "C" s32 sAossSocket;
extern "C" s32 sAossProgress;
extern "C" s32 sAossEncryptFlag;
extern "C" s32 sAossError;
extern "C" u32 sAossRandSeeded;
extern "C" u32 sAossCrcTable[0x100];
extern "C" u8 *sAossPacketBuf;
extern "C" u8 sAossKeyBlockTags[4];
extern "C" u8 sAossSessionId[8];
extern "C" u8 sAossRc4Key[0x64];
extern "C" u8 sAossNameBuf[0x280];
extern "C" u8 sAossKeyBuf[0x6a0];
extern "C" void *sAossScanList;
extern "C" AossConnectResult *sAossConnectResult;

#define FAIL(c) { o[0x116] = (c); Aoss_FreeScanBuffers(); return -1; }
#define data_ov001_0222b90a (sAossRc4Key + 2)
#define data_ov001_0222bff4 (*(AossKeyBlock *)(sAossKeyBuf + 0x8))
#define data_ov001_0222c124 (*(AossKeyBlock *)(sAossKeyBuf + 0x138))
#define data_ov001_0222c254 (*(AossKeyBlock *)(sAossKeyBuf + 0x268))
#define data_ov001_0222c2c4 (*(AossKeyBlock *)(sAossKeyBuf + 0x2d8))
#define sAossMelcoStr ((u8 *)"MELCO")
#define sAossEssidStr ((u8 *)"ESSID-AOSS")

extern "C" {
extern u32 gOwnIp;
extern s32 (*sAossFreeFunc)(s32);
extern s32 (*sAossAllocFunc)(s32);

void Aoss_FdSet(u32 v, AossPollFd *s);
void Aoss_FdZero(AossPollFd *s);
u16 Aoss_Rand16(void);
s32 Aoss_Strlen(char *s);
s32 Aoss_Ntohs(s32 v);
u32 Aoss_Ntohl(u32 v);
u16 Aoss_Htons(s32 v);
u32 Aoss_Htonl(u32 v);
s32 Aoss_SocketClose(s32 s);
s32 Aoss_SocketBind(s32 a, u8 *b, s32 c);
s32 Aoss_SocketCreate(s32 a, s32 b, s32 c);
s32 Aoss_SetSockOpt(s32 s, s32 l, s32 o, void *v, s32 n);
s32 Aoss_SendTo(s32 a, const void *b, s32 c, s32 d, SockAddrIn *p, u32 v);
s32 Aoss_Select(s32 a, AossPollFd *p, s32 c, s32 d, s32 *q);
s32 Aoss_RecvFrom(s32 a, void *b, s32 c, s32 d, SockAddrIn *p, s32 *q);
void *Aoss_Memset(void *p, u32 v, u32 n);
void Aoss_Memcpy(void *dst, void *src, u32 n);
s32 Aoss_Memcmp(u8 *a, u8 *b, s32 n);
s32 Aoss_NetCleanup();
s32 Aoss_NetStartup(u32 a, u32 b, u32 c);
s32 Aoss_SocFree(s32 a, s32 b);
s32 Aoss_SocAlloc(s32 a, s32 b);
void Aoss_SwapHalves(u8 *a, s32 n, u8 *t);
void Aoss_XorHalf(char *a, u8 *b, s32 n);
void Aoss_MakeRoundKey(s32 x, char *b, s32 n, char *key, s32 klen);
s32 Aoss_Scramble(u8 *out, s32 n, u8 *key, s32 klen);
void Aoss_InitCrc32Table(u32 unused, u32 *t);
u32 Aoss_UpdateCrc32(u32 crc, u8 *data, s32 len, s32 init, u32 *tbl);
u8 Aoss_CalcCrc32Low8(u8 *data, s32 len);
u32 Aoss_Rc4NextByte(AossRc4State *st);
void Aoss_Rc4Crypt(AossRc4State *st, u8 *out, u8 *in, u32 n);
void Aoss_Rc4Init(AossRc4State *st, u8 *key, u32 klen, u32 n);
s32 Aoss_DecryptPayload(u8 *a, u8 *b, u32 n, u32 crc, u8 *x, u8 *y, s32 z);
s32 Aoss_EncryptPayload(u8 *a, u8 *b, u32 n, u8 *out, u8 *x, u8 *y, s32 z);
s32 Aoss_SendPacket(const void *a, s32 b, s32 n, s32 c);
void Aoss_WriteHeader(u16 *out, u32 x, u32 y, u32 z, s8 a5, s8 a6, u8 *in);
void Aoss_WriteBody(s32 mode, u8 *out, u8 *in, s16 *len, u16 *flag, u8 *crcout);
s32 Aoss_BuildClientInfoTlv(u8 *out);
s32 Aoss_SendFinishRequest(void *a, u8 *b, s32 c);
s32 Aoss_SendKeyRequest(void *a, u8 *b, s32 c);
s32 Aoss_SendStartRequest(void *unused, u8 *src, s32 arg);
s32 Aoss_SendForStage(s32 sel, void *a, u8 *b, s32 c);
BOOL Aoss_IsFlag10Set(u32 x);
s32 Aoss_ParseKeyBlock(s32 idx, u8 *p, s32 len, u8 *base, u8 *extra);
s32 Aoss_ParseTlv70(u8 *p, void *dst);
s32 Aoss_ParsePskTlvs(u8 *p, u8 *dst);
s32 Aoss_ParseWepTlvs(u8 *p, u8 *dst);
u32 Aoss_ReadLE(u8 *p, s32 n);
s32 Aoss_ParseStartReply(u8 *p, u8 *dst);
s32 Aoss_CheckReplyNonce(u8 *a, u8 *b);
s32 Aoss_CheckSessionId(s32 a, u8 *b);
s32 Aoss_ValidateRecvPacket(u8 *p);
s32 Aoss_HandleFinishReply(s32 mode, u8 *q, s32 *cnt, u8 *r3);
s32 Aoss_HandleKeyReply(s32 mode, u8 *q, s32 *cnt, u8 *r3);
s32 Aoss_HandleStartReply(s32 a, u8 *b, s32 *cnt, void *c);
s32 Aoss_HandleRecvPacket(s32 a, u8 *b, s32 *cnt, void *c, s32 sock);
s32 Aoss_SetProgress(s32 x);
void Aoss_InitNonces(s32 n, u8 *p, void *x);
s32 Aoss_BuildAossApConfig(AossApConfig *p);
s32 Aoss_FindAossAp(AossScanList *p);
s32 Aoss_IsPrintable(u8 *s, s32 n);
s32 Aoss_StoreResult(u8 *o);
s32 Aoss_GetError();
void Aoss_SetError(s32 v);
void Aoss_InitSession(u8 *p);
void Aoss_FreeScanBuffers();
u32 Aoss_PickHostAddress(u32 a, u32 b);
s32 Aoss_RunProtocol(u8 *o);
s32 Aoss_Run(AossParam *a);
s32 RTC_GetTime(void *p);
s32 Sock_Close(s32 a);
s32 Sock_Bind(s32 a, void *sa);
s32 Sock_Create(s32 a, s32 b);
s32 Sock_SendTo(sptr a, const void *b, s32 c, u32 d, SockAddrIn *sa);
s32 Sock_Poll(void *, s32, s64);
s32 Sock_RecvFrom(sptr a, void *b, s32 c, u32 d, SockAddrIn *sa);
s32 Sock_Cleanup();
s32 Sock_Startup(void *);
void *MI_CpuFill8(void *, s32, u32);
void *MI_CpuCopy8(void *, void *, u32);
void OS_Sleep(s32);
}

struct AossScanList {
    s32 count;
    AossApInfo aps[64];
};

struct AossRecvBuffer {
    s32 sock;
    s32 recvLength;
    u8 unk_08[4];
    u8 unk_0c[0x5ec];
};

struct AossRetryLimits {
    s16 v[2];
};

struct AossPacketHeader {
    u8 pad[0x10];
    u8 nonce[8];
};

struct AossPollFd {
    u32 fd;
    u16 events;
    u16 revents;
};

struct AossKeyRequestLocals {
    s8 a;
    s16 b;
    s16 c;
    u8 dat[8];
    SockAddrIn sa;
};

extern "C" s32 Aoss_Run(AossParam *a) {
    s32 r;
    if (a->apRetryCount == 0 || a->apRetryCount < -1 || a->apRetryWait < -1 || a->packetRetryCount == 0 || a->packetRetryCount < -1
        || a->packetRetryWait < -1 || a->recvTimeout < -1 || a->clientInfo.nameLength == 0 || a->clientInfo.nameLength > 0x100
        || a->clientInfo.name[a->clientInfo.nameLength - 1] != 0) {
        r = -1;
    } else {
        r = 0;
    }
    if (sAossAllocFunc == 0 || sAossFreeFunc == 0) {
        r = -1;
    }
    if (r == -1) {
        a->errorCode = 0xf;
        Aoss_FreeScanBuffers();
        return -1;
    }
    sAossPacketBuf = (u8 *)Aoss_Alloc(0x5f8);
    if (sAossPacketBuf == 0) {
        a->errorCode = 0xf;
        Aoss_FreeScanBuffers();
        return -1;
    }
    Aoss_SetProgress(-1);
    s32 res = Aoss_RunProtocol((u8 *)a);
    Aoss_Free(sAossPacketBuf);
    Aoss_FreeScanBuffers();
    s32 t = sAossSocket;
    if (t != -1) {
        Aoss_SocketClose(t);
    }
    return res;
}

extern "C" s32 Aoss_RunProtocol(u8 *o)
{
    s32 usec;
    s32 t;
    s32 state;
    s32 res;
    s32 ip;
    AossRecvBuffer *buf;
    s32 sec;
    s32 m1;
    s32 res2;
    s32 r;
    s32 i;
    s32 ret;
    s32 sl;
    s32 z;
    s32 *a;

    volatile AossRetryLimits v01 = *(AossRetryLimits *)sAossDefaultRetry;
    volatile AossRetryLimits v23 = { 0, 0 };
    state = 0;
    s32 opt = 1;
    s32 tries = state;
    SockAddrIn sa40;
    s32 len48;
    s32 fdset[2];
    s32 tv[2];
    SockAddrIn sa5c;
    u8 st64[0x18];
    AossApConfig cmd7c;
    s32 pkt[5];
    ip = state;
    Aoss_Memset(st64, state, 0x18);
    v01.v[0] = *(s16 *)(o + 0x106);
    if (v01.v[0] == -1) {
        v01.v[0] = 10;
    }
    v23.v[0] = *(s16 *)(o + 0x10a);
    if (v23.v[0] == -1) {
        v23.v[0] = 10;
    }
    v01.v[1] = *(s16 *)(o + 0x108);
    if (v01.v[1] == -1) {
        v01.v[1] = 100;
    }
    v23.v[1] = *(s16 *)(o + 0x10c);
    if (v23.v[1] == -1) {
        v23.v[1] = 100;
    }
    t = *(s16 *)(o + 0x10e);
    if (t == -1) {
        t = 0x7d0;
    }
    Aoss_InitSession(o);
    if ((sAossSession.requestedKeyTypes & 1) != 1) {
        Aoss_SetError(0x13);
        FAIL(0xf);
    }
    i = 0;
    Aoss_SetProgress(i);
    sl = v01.v[1];
    z = i;
    for (;;) {
        if (sAossScanList != 0) {
            Aoss_Free(sAossScanList);
            sAossScanList = NULL;
        }
        if (Aoss_ScanAps(&sAossScanList) == -1) {
            FAIL(0xf);
        }
        r = Aoss_FindAossAp((AossScanList *)sAossScanList);
        if (r == 4) {
            FAIL(2);
        }
        if (r == 0) {
            break;
        }
        if (i >= v01.v[0]) {
            FAIL(1);
        }
        Aoss_Sleep(sl);
        i = (s16)(i + 1);
    }
    Aoss_SetProgress(1);
    Aoss_Memset(&cmd7c, 0, sizeof(cmd7c));
    if (Aoss_BuildAossApConfig(&cmd7c) != 0) {
        FAIL(0xf);
    }
    sAossConnectResult = (AossConnectResult *)Aoss_Alloc(sizeof(AossConnectResult));
    if (sAossConnectResult == 0) {
        FAIL(0xf);
    }
    Aoss_Memset(sAossConnectResult, 0, sizeof(AossConnectResult));
    i = 0;
    if (v01.v[0] > 0) {
        do {
            r = Aoss_ConnectAp(&cmd7c, sAossConnectResult);
            if (r == -1) {
                FAIL(0xf);
            }
            if (r == 0) {
                if (r != 0) {
                    break;
                }
                if (sAossConnectResult->connected == 1) {
                    break;
                }
            }
            Aoss_Sleep(sl);
            i = (s16)(i + 1);
        } while (i < v01.v[0]);
    }
    if (i == v01.v[0]) {
        FAIL(0xf);
    }
    if (Aoss_NetStartup(0xc0a80b65, -256, 0xc0a80b65) != 0) {
        Aoss_SetError(0xc);
        FAIL(0xf);
    }
    Aoss_FreeScanBuffers();
    Aoss_InitNonces(3, st64, o + 0x110);
    sAossSocket = Aoss_SocketCreate(2, 2, 0);
    if (sAossSocket < 0) {
        FAIL(0xf);
    }
    if (Aoss_SetSockOpt(sAossSocket, 0xffff, 1, &opt, 4) < 0) {
        Aoss_SetError(0xb);
        FAIL(0xf);
    }
    Aoss_Memset(&sa5c, 0, 8);
    sa5c.family = 2;
    sa5c.addr = Aoss_Htonl(0xc0a80b65);
    sa5c.port = Aoss_Htons(0x5790);
    if (Aoss_SocketBind(sAossSocket, (u8 *)&sa5c, 8) < 0) {
        FAIL(0xf);
    }
    a = pkt;
    z = 0;
    m1 = -1;
top:
    buf = (AossRecvBuffer *)sAossPacketBuf;
    Aoss_Memset(a, z, 0x14);
    pkt[4] = 0xc0a80b65;
    pkt[0] = 0xc0a80b01;
    usec = t;
    t = usec;
    sec = t / 1000;
    usec = (t % 1000) * 1000;
again:
    if (state == 1 && sAossSession.useUnicast != 1) {
        if (sAossSocket != -1) {
            Aoss_SocketClose(sAossSocket);
        }
        sAossSocket = m1;
        if (Aoss_NetCleanup() != 0) {
            FAIL(0xf);
        }
        if (sAossScanList != 0) {
            Aoss_Free(sAossScanList);
            sAossScanList = NULL;
        }
        sAossScanList = Aoss_Alloc(0x58);
        if (sAossScanList == 0) {
            FAIL(0xf);
        }
        for (;;) {
            res2 = Aoss_ScanAps(&sAossScanList);
            if (res2 == -1) {
                FAIL(0xf);
            }
            r = Aoss_FindAossAp((AossScanList *)sAossScanList);
            if (r == 4) {
                FAIL(2);
            }
            if (r == 0) {
                break;
            }
            if (i >= v01.v[0]) {
                FAIL(1);
            }
            Aoss_Sleep(sl);
            i = (s16)(i + 1);
        }
        if (res2 == -1) {
            FAIL(0xf);
        }
        sAossConnectResult = (AossConnectResult *)Aoss_Alloc(sizeof(AossConnectResult));
        if (sAossConnectResult == 0) {
            FAIL(0xf);
        }
        Aoss_Memset(sAossConnectResult, z, sizeof(AossConnectResult));
        i = z;
        if (v01.v[0] > 0) {
            do {
                r = Aoss_ConnectAp(&cmd7c, sAossConnectResult);
                if (r == -1) {
                    FAIL(0xf);
                }
                if (r == 0) {
                    if (r != 0) {
                        break;
                    }
                    if (sAossConnectResult->connected == 1) {
                        break;
                    }
                }
                Aoss_Sleep(sl);
                i = (s16)(i + 1);
            } while (i < v01.v[0]);
        }
        if (i == v01.v[0]) {
            FAIL(0xf);
        }
        ip = Aoss_PickHostAddress(sAossSession.apAddress, sAossSession.netmask);
        if (Aoss_NetStartup(ip, sAossSession.netmask, ip) != 0) {
            Aoss_SetError(0xc);
            FAIL(0xf);
        }
        sAossSession.useUnicast = 1;
        Aoss_FreeScanBuffers();
        sAossSocket = Aoss_SocketCreate(2, 2, z);
        if (sAossSocket < 0) {
            FAIL(0xf);
        }
        if (Aoss_SetSockOpt(sAossSocket, 0xffff, 1, &opt, 4) < 0) {
            Aoss_SetError(0xb);
            FAIL(0xf);
        }
        Aoss_Memset(&sa5c, z, 8);
        sa5c.family = 2;
        sa5c.addr = Aoss_Htonl(ip);
        sa5c.port = Aoss_Htons(0x5790);
        if (Aoss_SocketBind(sAossSocket, (u8 *)&sa5c, 8) < 0) {
            FAIL(0xf);
        }
    }
    r = Aoss_SendForStage(state, pkt, st64, sAossSocket);
    if (r == -1) {
        Aoss_SetError(state + 0x1000);
        FAIL(0xf);
    }
    Aoss_Memset(buf, z, 0x5f8);
    Aoss_FdZero((AossPollFd *)fdset);
    Aoss_FdSet(sAossSocket, (AossPollFd *)fdset);
    tv[0] = sec;
    tv[1] = usec;
    if (Aoss_Select(sAossSocket + 1, (AossPollFd *)fdset, z, z, tv) <= 0) {
        tries++;
        if (tries > v23.v[0]) {
            if (state == 0) {
                Aoss_SetError(0xf);
            } else if (state == 1) {
                Aoss_SetError(0x10);
            } else {
                Aoss_SetError(0x11);
            }
            ret = -1;
            goto done;
        }
        Aoss_Sleep(v23.v[1]);
        goto again;
    }
    len48 = 8;
    r = Aoss_RecvFrom(sAossSocket, buf->unk_0c, 0x5dc, z, &sa40, &len48);
    buf->sock = sAossSocket;
    buf->recvLength = (u32)Aoss_Ntohs((u16)r);
    res = Aoss_HandleRecvPacket(state, (u8 *)buf, &tries, st64, sAossSocket);
    if (res == 100) {
        ret = 0;
        goto done;
    }
    if (res == -1) {
        ret = -1;
        goto done;
    }
    if (state != res) {
        if (res == 2) {
            if (sAossSocket != -1) {
                Aoss_SocketClose(sAossSocket);
            }
            sAossSocket = m1;
            if (Aoss_NetCleanup() != 0) {
                FAIL(0xf);
            }
            i = z;
            Aoss_SetProgress(4);
            for (;;) {
                if (sAossScanList != 0) {
                    Aoss_Free(sAossScanList);
                    sAossScanList = NULL;
                }
                if (Aoss_ScanAps(&sAossScanList) == -1) {
                    FAIL(0xf);
                }
                r = Aoss_FindAossAp((AossScanList *)sAossScanList);
                if (r == 4) {
                    FAIL(2);
                }
                if (r == 0) {
                    break;
                }
                if (i >= v01.v[0]) {
                    FAIL(1);
                }
                Aoss_Sleep(sl);
                i = (s16)(i + 1);
            }
            sAossConnectResult = (AossConnectResult *)Aoss_Alloc(sizeof(AossConnectResult));
            if (sAossConnectResult == 0) {
                FAIL(0xf);
            }
            Aoss_Memset(sAossConnectResult, z, sizeof(AossConnectResult));
            i = z;
            if (v01.v[0] > 0) {
                do {
                    r = Aoss_ConnectAp(&cmd7c, sAossConnectResult);
                    if (r == -1) {
                        FAIL(0xf);
                    }
                    if (r == 0) {
                        if (r != 0) {
                            break;
                        }
                        if (sAossConnectResult->connected == 1) {
                            break;
                        }
                    }
                    Aoss_Sleep(sl);
                    i = (s16)(i + 1);
                } while (i < v01.v[0]);
            }
            if (i == v01.v[0]) {
                FAIL(0xf);
            }
            if (Aoss_NetStartup(ip, sAossSession.netmask, ip) != 0) {
                Aoss_SetError(0xc);
                FAIL(0xf);
            }
            Aoss_FreeScanBuffers();
            sAossSocket = Aoss_SocketCreate(2, 2, z);
            if (sAossSocket < 0) {
                FAIL(0xf);
            }
            if (Aoss_SetSockOpt(sAossSocket, 0xffff, 1, &opt, 4) < 0) {
                Aoss_SetError(0xb);
                FAIL(0xf);
            }
            Aoss_Memset(&sa5c, z, 8);
            sa5c.family = 2;
            sa5c.addr = Aoss_Htonl(ip);
            sa5c.port = Aoss_Htons(0x5790);
            if (Aoss_SocketBind(sAossSocket, (u8 *)&sa5c, 8) < 0) {
                FAIL(0xf);
            }
        }
        state = res;
        goto top;
    }
    state = res;
    if (tries > v23.v[0]) {
        if (res == 0) {
            Aoss_SetError(0xf);
        } else if (res == 1) {
            Aoss_SetError(0x10);
        } else {
            Aoss_SetError(0x11);
        }
        ret = -1;
        goto done;
    }
    Aoss_Sleep(v23.v[1]);
    goto top;
done:
    if (sAossSocket != -1) {
        Aoss_SocketClose(sAossSocket);
    }
    sAossSocket = -1;
    if (Aoss_NetCleanup() != 0) {
        FAIL(0xf);
    }
    if (ret != 0) {
        u8 code;
        switch (Aoss_GetError()) {
        case 0xf:
            code = 3;
            break;
        case 0x10:
            code = 4;
            break;
        case 0x11:
            code = 5;
            break;
        case 0x14:
            code = 7;
            break;
        case 0x15:
            code = 8;
            break;
        default:
            code = 0xf;
            break;
        }
        FAIL(code);
    }
    if (Aoss_StoreResult(o) != 0) {
        FAIL(6);
    }
    return 0;
}

extern "C" u32 Aoss_PickHostAddress(u32 a, u32 b)
{
    u32 m = a & b;
    u32 nb = ~b;
    u32 lo = (a & nb) + 1;
    u32 x = m | lo;
    if (x >= (m | nb)) {
        x = m | 1;
    }
    return x;
}

extern "C" void Aoss_FreeScanBuffers()
{
    if (sAossConnectResult != 0) {
        Aoss_Free(sAossConnectResult);
        sAossConnectResult = 0;
    }
    if (sAossScanList != 0) {
        Aoss_Free(sAossScanList);
        sAossScanList = 0;
    }
}

extern "C" void Aoss_InitSession(u8 *p)
{
    Aoss_Memset(sAossSessionId, 0, 8);
    sAossError = 1;
    Aoss_Memset(&sAossSession, 0, 0x1c);
    sAossSession.clientName = p + 6;
    sAossSession.clientNameLength = *(u16 *)(p + 4);
    sAossSession.requestedKeyTypes = *(u16 *)p & 0xf;
    sAossSession.clientInfoTag = p[2];
    sAossSession.receivedKeyTypes = 0;
    sAossSession.apAddress = 0xc0a80b01;
    sAossSession.useUnicast = 0;
}

extern "C" void Aoss_SetError(s32 v)
{
    sAossError = v;
}

extern "C" s32 Aoss_GetError()
{
    return sAossError;
}

extern "C" s32 Aoss_StoreResult(u8 *o)
{
    u8 *r5 = o + 0x117;
    AossKeyBlock *a = &data_ov001_0222bff4;
    AossKeyBlock *b = &data_ov001_0222c124;
    AossKeyBlock *c = &data_ov001_0222c254;
    AossKeyBlock *d = &data_ov001_0222c2c4;
    if (r5 == 0) {
        return -1;
    }
    *(u16 *)o = sAossSession.requestedKeyTypes & sAossSession.receivedKeyTypes;
    Aoss_Memset(r5, 0, 0x154);
    if ((*(u16 *)o & 1) != 0) {
        Aoss_Memcpy(r5, a->key1, a->len);
        Aoss_Memcpy(r5 + 6, a->key2, a->len);
        Aoss_Memcpy(r5 + 0xc, a->key3, a->len);
        Aoss_Memcpy(r5 + 0x12, a->key4, a->len);
        if (Aoss_IsPrintable(a->ssid, Aoss_Strlen((char *)a->ssid)) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0x18, a->ssid, Aoss_Strlen((char *)a->ssid));
    }
    if ((*(u16 *)o & 2) != 0) {
        Aoss_Memcpy(r5 + 0x39, b->key1, b->len);
        Aoss_Memcpy(r5 + 0x47, b->key2, b->len);
        Aoss_Memcpy(r5 + 0x55, b->key3, b->len);
        Aoss_Memcpy(r5 + 0x63, b->key4, b->len);
        if (Aoss_IsPrintable(b->ssid, Aoss_Strlen((char *)b->ssid)) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0x71, b->ssid, Aoss_Strlen((char *)b->ssid));
    }
    if ((*(u16 *)o & 4) != 0) {
        if (Aoss_IsPrintable(c->key1, c->len - 1) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0x92, c->key1, c->len);
        if (Aoss_IsPrintable(c->ssid, Aoss_Strlen((char *)c->ssid)) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0xd2, c->ssid, Aoss_Strlen((char *)c->ssid));
    }
    if ((*(u16 *)o & 8) != 0) {
        if (Aoss_IsPrintable(d->key1, d->len - 1) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0xf3, d->key1, d->len);
        if (Aoss_IsPrintable(d->ssid, Aoss_Strlen((char *)d->ssid)) != 0) {
            goto fail;
        }
        Aoss_Memcpy(r5 + 0x133, d->ssid, Aoss_Strlen((char *)d->ssid));
    }
    o[0x116] = 0;
    return 0;
fail:
    Aoss_Memset(r5, 0, 0x154);
    return -1;
}

extern "C" s32 Aoss_IsPrintable(u8 *s, s32 n)
{
    s32 i;
    for (i = 0; i < n; i++) {
        u32 c = *s++;
        if (c < 0x20 || c > 0x7f) {
            return -1;
        }
    }
    return 0;
}

extern "C" s32 Aoss_FindAossAp(AossScanList *p)
{
    s32 n;
    s32 r = 0;
    s32 cnt = 0;
    s32 i;
    n = p->count;
    if (n == 0) {
        return 5;
    }
    if ((u32)n > 0x40) {
        n = 0x40;
    }
    for (i = 0; i < n; i++) {
        if ((p->aps[i].bssType & 1) != 0) {
            if (p->aps[i].ssidLength == Aoss_Strlen((char *)sAossEssidStr)) {
                if (Aoss_Memcmp(p->aps[i].ssid, sAossEssidStr, Aoss_Strlen((char *)sAossEssidStr)) == 0) {
                    cnt++;
                }
            }
        }
    }
    if (cnt > 1) {
        r = 4;
    }
    if (cnt == 0) {
        r = 5;
    }
    return r;
}

extern "C" s32 Aoss_BuildAossApConfig(AossApConfig *p)
{
    p->ssidLength = Aoss_Strlen((char *)sAossEssidStr);
    Aoss_Memcpy(p->ssid, sAossEssidStr, p->ssidLength);
    p->mode = 1;
    p->wepKeyLength = Aoss_Strlen((char *)sAossMelcoStr);
    if ((u32)p->wepKeyLength > 0xd) {
        return -1;
    }
    Aoss_Memcpy(p->wepKey, sAossMelcoStr, p->wepKeyLength);
    return 0;
}

extern "C" void Aoss_InitNonces(s32 n, u8 *p, void *x)
{
    s32 i;
    for (i = 0; i < n; i++) {
        Aoss_Memcpy(p, x, 6);
        *(u16 *)(p + 6) = Aoss_Rand16();
        *(u16 *)(p + 6) = Aoss_Htons(*(u16 *)(p + 6));
        p += 8;
    }
}

extern "C" s32 Aoss_SetProgress(s32 x)
{
    s32 z = 0;
    if (x == -1) {
        sAossProgress = x;
        return z;
    }
    if (sAossProgress != x) {
        sAossProgress = x;
        return Aoss_NotifyProgress(x);
    }
    return z;
}

extern "C" s32 Aoss_HandleRecvPacket(s32 a, u8 *b, s32 *cnt, void *c, s32 sock)
{
    u8 *p = b + 0xc;
    if ((u32)Aoss_Ntohs(*(u16 *)(b + 0xc)) < 1) {
        (*cnt)++;
        return a;
    }
    if (p[0xf] != 0x11) {
        (*cnt)++;
        return a;
    }
    if (Aoss_ValidateRecvPacket(b + 0xc) > 0) {
        (*cnt)++;
        return a;
    }
    switch ((u32)Aoss_Ntohs(*(u16 *)(p + 6))) {
    case 0x1010:
        a = Aoss_HandleStartReply(a, b, cnt, c);
        break;
    case 0x2010:
        a = Aoss_HandleKeyReply(a, b, cnt, (u8 *)c);
        break;
    case 0x3010:
        a = Aoss_HandleFinishReply(a, b, cnt, (u8 *)c);
        break;
    }
    return a;
}

extern "C" s32 Aoss_HandleStartReply(s32 a, u8 *b, s32 *cnt, void *c)
{
    u8 *p;
    u8 *q;
    if (a != 0) {
        (*cnt)++;
        return a;
    }
    p = b + 0xc;
    q = b + 0x24;
    if (Aoss_CheckReplyNonce((u8 *)c, p + 0x10) < 0) {
        (*cnt)++;
        return a;
    }
    if ((u32)Aoss_Ntohs(*(u16 *)(q + 2)) == 0) {
        (*cnt)++;
        return a;
    }
    if (q[0] == 7) {
        s32 *w = (s32 *)(q + 4);
        if (Aoss_Ntohl(*(s32 *)(q + 4)) == -2) {
            Aoss_SetError(0x14);
        } else if (Aoss_Ntohl(w[0]) == -3) {
            Aoss_SetError(0x15);
        } else {
            Aoss_SetError(0x18);
        }
        return -1;
    }
    if (q[0] != 1) {
        (*cnt)++;
        return a;
    }
    s32 r = Aoss_ParseStartReply(q + 4, sAossNameBuf);
    if (r < 0) {
        if (r == -2) {
            Aoss_SetError(0x16);
            return -1;
        }
        (*cnt)++;
        return a;
    }
    sAossEncryptFlag = Aoss_IsFlag10Set(Aoss_Ntohs(*(u16 *)(p + 0xc)));
    *cnt = 0;
    return 1;
}

extern "C" s32 Aoss_HandleKeyReply(s32 mode, u8 *q, s32 *cnt, u8 *r3)
{
    u8 *r7;
    u8 *r4;
    if (mode != 1) {
        (*cnt)++;
        return mode;
    }
    r7 = q + 0xc;
    r4 = q + 0x24;
    if (Aoss_CheckReplyNonce(r3 + 8, r7 + 0x10) < 0) {
        (*cnt)++;
        return mode;
    }
    if (Aoss_Ntohs(*(u16 *)(r4 + 2)) == 0) {
        (*cnt)++;
        return mode;
    }
    if (r4[0] == 7) {
        if (Aoss_Ntohl(*(u32 *)(r4 + 4)) == -2) {
            Aoss_SetError(0x14);
        } else if (Aoss_Ntohl(*(u32 *)(r4 + 4)) == -3) {
            Aoss_SetError(0x15);
        } else {
            Aoss_SetError(0x18);
        }
        return -1;
    }
    Aoss_Memset(sAossKeyBuf, 0, 0x6a0);
    if (Aoss_ParseKeyBlock(0, r4, Aoss_Ntohs(*(u16 *)(r7 + 0xa)), sAossKeyBuf, sAossNameBuf) < 0) {
        (*cnt)++;
        return mode;
    }
    if ((sAossSession.receivedKeyTypes & sAossSession.requestedKeyTypes) == 0) {
        return mode;
    }
    *cnt = 0;
    return 2;
}

extern "C" s32 Aoss_HandleFinishReply(s32 mode, u8 *q, s32 *cnt, u8 *r3)
{
    u8 *r4;
    if (mode != 2) {
        (*cnt)++;
        return mode;
    }
    r4 = q + 0x24;
    if (Aoss_CheckReplyNonce(r3 + 0x10, ((AossPacketHeader *)(q + 0xc))->nonce) < 0) {
        (*cnt)++;
        return mode;
    }
    if (r4[0] != 7) {
        (*cnt)++;
        return mode;
    }
    if (Aoss_Ntohs(*(u16 *)(r4 + 2)) == 0) {
        (*cnt)++;
        return mode;
    }
    if (Aoss_Ntohl(*(u32 *)(r4 + 4)) == 0) {
        return 0x64;
    }
    if (Aoss_Ntohl(*(u32 *)(r4 + 4)) == -2) {
        Aoss_SetError(0x14);
        return -1;
    }
    if (Aoss_Ntohl(*(u32 *)(r4 + 4)) == -3) {
        Aoss_SetError(0x15);
        return -1;
    }
    Aoss_SetError(0x18);
    return -1;
}

extern "C" s32 Aoss_ValidateRecvPacket(u8 *p)
{
    u8 buf[8];
    u8 *r4 = p + 0x18;
    u32 len;
    u8 *m;
    s32 t;
    s32 r;

    Aoss_Memcpy(buf, p + 0x10, 8);
    t = Aoss_Strlen((char *)sAossMelcoStr);
    if (Aoss_Scramble(buf, 8, sAossMelcoStr, t) == -1) {
        Aoss_SetError(2);
        return -100;
    }
    r = Aoss_CheckSessionId(Aoss_Ntohs(*(u16 *)(p + 6)), buf);
    if (r != 0) {
        return r;
    }
    if (Aoss_Ntohs(*(u16 *)(p + 6)) == 0x1000) {
        Aoss_Memcpy(sAossSessionId, buf, 8);
    }
    if ((Aoss_Ntohs(*(u16 *)(p + 0xc)) & 0xf) == 0) {
        return 0;
    }
    len = Aoss_Ntohs(*(u16 *)r4);
    m = (u8 *)Aoss_Alloc(len);
    if (m == NULL) {
        Aoss_SetError(2);
        return 0x64;
    }
    if (Aoss_DecryptPayload(r4 + 4, m, len, p[0xe], r4 + 2, sAossSessionId, 8) < 0) {
        Aoss_Free(m);
        if (Aoss_GetError() == 2) {
            return 0x64;
        }
        return 0xc8;
    }
    Aoss_Memcpy(r4, m, len);
    *(u16 *)(p + 0xa) = Aoss_Htons((u16)len);
    Aoss_Free(m);
    return 0;
}

extern "C" s32 Aoss_CheckSessionId(s32 a, u8 *b)
{
    s32 r;
    s32 i;
    s32 f;
    u8 *t;
    r = 0;
    f = r;
    i = r;
    t = sAossSessionId;
    do {
        if (*t != 0) { f = 1; break; }
        t++; i++;
    } while (i < 6);
    if (f != 0) {
        if (Aoss_Memcmp(sAossSessionId, b, 6) != 0) {
            r = 1;
        }
    } else if (a != 0x1000) {
        r = 2;
    }
    return r;
}

extern "C" s32 Aoss_CheckReplyNonce(u8 *a, u8 *b)
{
    s32 r = 0;
    s32 t;
    s32 x;
    t = Aoss_Strlen((char *)sAossMelcoStr);
    Aoss_Scramble(b, 8, sAossMelcoStr, t);
    if (Aoss_Memcmp(a, b, 6) != 0) {
        r = -1;
    } else {
        x = Aoss_Ntohs(*(u16 *)(a + 6));
        if (x + 1 != Aoss_Ntohs(*(u16 *)(b + 6))) {
            r = -2;
        }
    }
    return r;
}

extern "C" s32 Aoss_ParseStartReply(u8 *p, u8 *dst)
{
    u8 *q;
    s32 len;
    Aoss_Memset(dst, 0, 0x104);
    q = p;
    for (;;) {
        len = Aoss_Ntohs(*(u16 *)(q + 2));
        if (len <= 0) {
            return -1;
        }
        switch (q[0]) {
        case 0:
            Aoss_Memcpy(dst, q + 6, len);
            break;
        case 1:
            Aoss_Memcpy(dst + 0x80, q + 6, len);
            break;
        case 2:
            Aoss_Memcpy(dst + 0x100, q + 6, len);
            break;
        case 3:
        case 4:
            if (Aoss_Ntohs(q[6]) <= 0) {
                return -2;
            }
            break;
        case 5:
            sAossSession.apAddress = Aoss_Ntohl(Aoss_ReadLE(q + 6, len));
            break;
        case 6:
            sAossSession.netmask = Aoss_Ntohl(Aoss_ReadLE(q + 6, len));
            break;
        default:
            return -1;
        }
        if (*(u16 *)(q + 4) == 0) {
            break;
        }
        q = p + Aoss_Ntohs(*(u16 *)(q + 4));
    }
    return 0;
}

extern "C" u32 Aoss_ReadLE(u8 *p, s32 n)
{
    u32 r = 0;
    s32 i;
    u8 *q = p + (n - 1);
    i = r;
    for (; i < n; i++) {
        r = (r << 8) + *q--;
    }
    return r;
}

extern "C" s32 Aoss_ParseWepTlvs(u8 *p, u8 *dst)
{
    u8 *q = p + 6;
    u32 len;
    s32 t;
    for (;;) {
        len = Aoss_Ntohs(*(u16 *)(q + 2));
        t = q[0];
        switch (t) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            if (len > 5) {
                return -1;
            }
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            if (len > 0xd) {
                return -1;
            }
            break;
        case 0x15:
        case 0x25:
            if (len > 0x21) {
                return -1;
            }
            break;
        }
        switch (t) {
        case 0x10:
        case 0x20:
            Aoss_Memcpy(dst + 0x30, q + 6, len);
            *(u32 *)(dst + 4) = len;
            break;
        case 0x11:
        case 0x21:
            Aoss_Memcpy(dst + 0x70, q + 6, len);
            *(u32 *)(dst + 4) = len;
            break;
        case 0x12:
        case 0x22:
            Aoss_Memcpy(dst + 0xb0, q + 6, len);
            *(u32 *)(dst + 4) = len;
            break;
        case 0x13:
        case 0x23:
            Aoss_Memcpy(dst + 0xf0, q + 6, len);
            *(u32 *)(dst + 4) = len;
            break;
        case 0x15:
        case 0x25:
            if (len != 0 && *(q + (len - 1) + 6) != 0) {
                return -1;
            }
            Aoss_Memcpy(dst + 8, q + 6, len);
            break;
        default:
            return -1;
        }
        if (*(u16 *)(q + 4) == 0) {
            break;
        }
        q = p + 6 + Aoss_Ntohs(*(u16 *)(q + 4));
    }
    return 0;
}

extern "C" s32 Aoss_ParsePskTlvs(u8 *p, u8 *dst)
{
    u8 *q = p + 6;
    u32 len;
    s32 t;
    for (;;) {
        len = Aoss_Ntohs(*(u16 *)(q + 2));
        t = q[0];
        switch (t) {
        case 0x30:
        case 0x40:
            if (len > 0x40) {
                return -1;
            }
            break;
        case 0x35:
        case 0x45:
            if (len > 0x21) {
                return -1;
            }
            break;
        }
        switch (t) {
        case 0x30:
        case 0x40:
            Aoss_Memcpy(dst + 0x30, q + 6, len);
            *(u32 *)(dst + 4) = len;
            break;
        case 0x35:
        case 0x45:
            if (len != 0 && *(q + (len - 1) + 6) != 0) {
                return -1;
            }
            Aoss_Memcpy(dst + 8, q + 6, len);
            break;
        default:
            return -1;
        }
        if (*(u16 *)(q + 4) == 0) {
            break;
        }
        q = p + 6 + Aoss_Ntohs(*(u16 *)(q + 4));
    }
    return 0;
}

extern "C" s32 Aoss_ParseTlv70(u8 *p, void *dst)
{
    u8 *q = p + 6;
    s32 len = Aoss_Ntohs(*(u16 *)(q + 2));
    if (len <= 0) {
        return -1;
    }
    if (q[0] != 0x70) {
        return -1;
    }
    Aoss_Memcpy(dst, q + 6, len);
    return 0;
}

extern "C" s32 Aoss_ParseKeyBlock(s32 idx, u8 *p, s32 len, u8 *base, u8 *extra)
{
    u32 flags;
    u8 *key;
    u8 *r6;
    s32 r7;
    s32 n;
    s32 r;
    u8 *x;
    u8 *rec;

    flags = 0;
    if (len <= 0) {
        return -2;
    }
    key = sAossKeyBlockTags + idx;
    do {
        rec = p;
        if (p[0] == key[0]) {
            goto found;
        }
        n = Aoss_Ntohs(*(u16 *)(p + 2)) + 4;
        p += n;
        len -= n;
    } while (len > 0);
    return -4;
found:
    p += 4;
    r7 = Aoss_Ntohs(*(u16 *)(rec + 2));
    r6 = base + idx * 0x350;
    x = extra + (idx + 3) * 0x80;
    do {
        switch (p[0]) {
        case 3:
            r = Aoss_ParseWepTlvs(p, r6 + 8);
            flags |= 1;
            break;
        case 4:
            r = Aoss_ParseWepTlvs(p, r6 + 0x138);
            flags |= 2;
            break;
        case 5:
            r = Aoss_ParsePskTlvs(p, r6 + 0x268);
            flags |= 4;
            break;
        case 6:
            r = Aoss_ParsePskTlvs(p, r6 + 0x2d8);
            flags |= 8;
            break;
        case 10:
            r = Aoss_ParseTlv70(p, x);
            break;
        default:
            r = -3;
            break;
        }
        if (r != 0) {
            return r;
        }
        n = Aoss_Ntohs(*(u16 *)(p + 2)) + 4;
        p += n;
        r7 -= n;
    } while (r7 > 0);
    sAossSession.receivedKeyTypes |= flags;
    return 0;
}

extern "C" BOOL Aoss_IsFlag10Set(u32 x)
{
    BOOL r = FALSE;
    if ((x & 0x10) != 0) {
        r = TRUE;
    }
    return r;
}

extern "C" s32 Aoss_SendForStage(s32 sel, void *a, u8 *b, s32 c)
{
    switch (sel) {
    case 0:
        Aoss_SetProgress(2);
        return Aoss_SendStartRequest(a, b, c);
    case 1:
        Aoss_SetProgress(3);
        return Aoss_SendKeyRequest(a, b, c);
    case 2:
        Aoss_SetProgress(5);
        return Aoss_SendFinishRequest(a, b, c);
    default:
        return -1;
    }
}

extern "C" s32 Aoss_SendStartRequest(void *unused, u8 *src, s32 arg)
{
    s8 a;
    s16 b;
    s16 c;
    u8 buf[8];
    u8 *g;
    u8 *p;
    u8 *r6;

    a = 0;
    b = 0;
    c = 0;
    g = sAossPacketBuf;
    Aoss_Memset(g, 0, 0x5dc);
    p = (u8 *)Aoss_Alloc(0x210);
    if (p == NULL) {
        Aoss_SetError(2);
        return -1;
    }
    Aoss_Memset(p, 0, 0x210);
    r6 = g + 0x18;
    Aoss_Memcpy(sAossSessionId, src, 8);
    Aoss_Memcpy(buf, sAossSessionId, 8);
    b = Aoss_BuildClientInfoTlv(p + 4);
    if (b < 0) {
        Aoss_SetError(3);
        if (p != NULL) {
            Aoss_Free(p);
        }
        return -1;
    }
    *p = 0;
    *(u16 *)(p + 2) = Aoss_Htons((u16)b);
    b = b + 4;
    Aoss_WriteBody(0, r6, p, &b, (u16 *)&c, (u8 *)&a);
    c = c | 0x10;
    if (Aoss_Scramble(buf, 8, sAossMelcoStr, 6) != 0) {
        Aoss_SetError(2);
        if (p != NULL) {
            Aoss_Free(p);
        }
        return -1;
    }
    Aoss_WriteHeader((u16 *)g, 0x1000, b, c, a, 0x11, buf);
    b = b + 0x18;
    Aoss_SendPacket(g, b, 0xff, arg);
    if (p != NULL) {
        Aoss_Free(p);
    }
    return 0;
}

extern "C" s32 Aoss_SendKeyRequest(void *a, u8 *b, s32 c) {
    AossKeyRequestLocals l;
    u8 *r4;
    l.a = 0;
    l.b = 0;
    l.c = 0;
    r4 = sAossPacketBuf;
    Aoss_Memset(&l.sa, 0, 8);
    Aoss_Memset(r4, 0, 0x5dc);
    l.sa.len = 2;
    l.sa.family = 0;
    l.sa.port = Aoss_Htons(4);
    l.sa.addr = sAossSession.requestedKeyTypes;
    l.sa.addr = Aoss_Htonl(l.sa.addr);
    l.b = 8;
    Aoss_WriteBody(sAossEncryptFlag, r4 + 0x18, (u8 *)&l.sa, &l.b, (u16 *)&l.c, (u8 *)&l.a);
    Aoss_Memcpy(l.dat, b + 8, 8);
    if (Aoss_Scramble(l.dat, 8, sAossMelcoStr, 6) != 0) {
        Aoss_SetError(2);
        return -1;
    }
    Aoss_WriteHeader((u16 *)r4, 0x2000, l.b, l.c, l.a, 0x11, l.dat);
    l.b = l.b + 0x18;
    Aoss_SendPacket(r4, l.b, 0, c);
    return 0;
}

extern "C" s32 Aoss_SendFinishRequest(void *a, u8 *b, s32 c) {
    u8 *r4 = sAossPacketBuf;
    u8 buf[8];
    Aoss_Memset(r4, 0, 0x5dc);
    Aoss_Memcpy(buf, b + 0x10, 8);
    Aoss_Scramble(buf, 8, sAossMelcoStr, Aoss_Strlen((char *)sAossMelcoStr));
    Aoss_WriteHeader((u16 *)r4, 0x3000, 0, 0, 0, 0x11, buf);
    Aoss_SendPacket(r4, 0x18, 0, c);
    return 0;
}

extern "C" s32 Aoss_BuildClientInfoTlv(u8 *out) {
    s16 acc = 0;
    s32 len;
    s32 t;
    u8 *q;
    out[0] = sAossSession.clientInfoTag;
    out[1] = 1;
    len = (s16)sAossSession.clientNameLength;
    Aoss_Memcpy(out + 6, sAossSession.clientName, len);
    *(u16 *)(out + 2) = Aoss_Htons((u16)len);
    t = (s16)(((s16)(len + 6) + 1) / 2 * 2);
    *(u16 *)(out + 4) = Aoss_Htons((u16)t);
    acc += t;
    q = out + t;
    q[0] = 0x60;
    q[1] = 0;
    *(u16 *)(q + 4) = Aoss_Htons(0);
    {
        u32 w = Aoss_Htonl(0xe);
        Aoss_Memcpy(q + 6, &w, 4);
    }
    *(u16 *)(q + 2) = Aoss_Htons(4);
    acc += 10;
    return acc;
}

extern "C" void Aoss_WriteBody(s32 mode, u8 *out, u8 *in, s16 *len, u16 *flag, u8 *crcout) {
    if (mode == 1) {
        *flag = 1;
        Aoss_EncryptPayload(in, out + 4, *len, crcout, out + 2, sAossSessionId, 8);
        *(u16 *)out = Aoss_Htons(*(u16 *)len);
        *len = *len + 4;
    } else {
        Aoss_Memcpy(out, in, *len);
    }
}

extern "C" void Aoss_WriteHeader(u16 *out, u32 x, u32 y, u32 z, s8 a5, s8 a6, u8 *in) {
    u8 *o = (u8 *)out;
    out[0] = Aoss_Htons(1);
    out[1] = 0;
    out[2] = 0;
    out[3] = Aoss_Htons((u16)x);
    out[4] = 0;
    out[5] = Aoss_Htons((u16)y);
    out[6] = Aoss_Htons((u16)z);
    o[0xe] = a5;
    o[0xf] = a6;
    Aoss_Memcpy(o + 0x10, in, 8);
}

extern "C" s32 Aoss_SendPacket(const void *a, s32 b, s32 n, s32 c) {
    SockAddrIn sa;
    Aoss_Memset(&sa, 0, 8);
    sa.family = 2;
    sa.port = Aoss_Htons(0x5790);
    sa.addr = Aoss_Htonl(sAossSession.apAddress);
    if (n == 0xff || sAossSession.useUnicast == 0) {
        sa.addr = -1;
    }
    return Aoss_SendTo(c, a, b, 0, &sa, 8);
}

extern "C" s32 Aoss_EncryptPayload(u8 *a, u8 *b, u32 n, u8 *out, u8 *x, u8 *y, s32 z) {
    u16 v;
    AossRc4State st;
    *out = Aoss_CalcCrc32Low8(a, n);
    st.s = (u8 *)Aoss_Alloc(n);
    if (st.s == NULL) {
        return -1;
    }
    v = Aoss_Rand16();
    Aoss_Memcpy(x, &v, 2);
    Aoss_Memcpy(sAossRc4Key, x, 2);
    Aoss_Memcpy(data_ov001_0222b90a, y, z);
    Aoss_Rc4Init(&st, sAossRc4Key, z + 2, n);
    Aoss_Rc4Crypt(&st, b, a, n);
    Aoss_Free(st.s);
    return 0;
}

extern "C" s32 Aoss_DecryptPayload(u8 *a, u8 *b, u32 n, u32 crc, u8 *x, u8 *y, s32 z) {
    AossRc4State st;
    st.s = (u8 *)Aoss_Alloc(n);
    if (st.s == NULL) {
        Aoss_SetError(2);
        return -1;
    }
    Aoss_Memcpy(sAossRc4Key, x, 2);
    Aoss_Memcpy(data_ov001_0222b90a, y, z);
    Aoss_Rc4Init(&st, sAossRc4Key, z + 2, n);
    Aoss_Rc4Crypt(&st, b, a, n);
    u32 c = Aoss_CalcCrc32Low8(b, n);
    if (c != crc) {
        Aoss_SetError(0x12);
        Aoss_Free(st.s);
        return -1;
    }
    Aoss_Free(st.s);
    return 0;
}

extern "C" void Aoss_Rc4Init(AossRc4State *st, u8 *key, u32 klen, u32 n) {
    u8 *s = st->s;
    u32 i, j, k;
    st->j = 0;
    st->i = st->j;
    st->n = n;
    for (i = 0; i < n; i++) {
        s[i] = i;
    }
    j = 0;
    k = 0;
    for (i = 0; i < n; i++) {
        u32 si = s[i];
        u32 sj;
        j = DS_UMOD((j + key[k] + si), st->n);
        sj = s[j];
        s[j] = si;
        s[i] = sj;
        k++;
        if (k >= klen) {
            k = 0;
        }
    }
}

extern "C" void Aoss_Rc4Crypt(AossRc4State *st, u8 *out, u8 *in, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        u32 t = (u8)Aoss_Rc4NextByte(st);
        u32 c = in[i];
        out[i] = t ^ c;
    }
}

extern "C" u32 Aoss_Rc4NextByte(AossRc4State *st) {
    u8 *s = st->s;
    u32 n = st->n;
    u32 i = (u8)(DS_UMOD((st->i + 1), n));
    u32 si = s[i];
    u32 j = (u8)(DS_UMOD((si + st->j), n));
    u32 sj = s[j];
    st->i = i;
    st->j = j;
    s[j] = si;
    s[i] = sj;
    return s[DS_UMOD((si + sj), st->n)];
}

extern "C" u8 Aoss_CalcCrc32Low8(u8 *data, s32 len) {
    u32 r = Aoss_UpdateCrc32(-1, data, len, 0, sAossCrcTable);
    return (u8)(r ^ -1);
}

extern "C" u32 Aoss_UpdateCrc32(u32 crc, u8 *data, s32 len, s32 init, u32 *tbl) {
    s32 i;
    if (init == 0) {
        Aoss_InitCrc32Table(init, tbl);
    }
    for (i = 0; i < len; i++) {
        u32 t = crc >> 8;
        crc = crc ^ data[i];
        crc = crc & 0xff;
        crc = t ^ tbl[crc];
    }
    return crc;
}

extern "C" void Aoss_InitCrc32Table(u32 unused, u32 *t) {
    u32 r;
    s32 i;
    s32 j;
    for (i = 0; i < 0x100; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) {
                r = (r >> 1) ^ 0xedb88320;
            } else {
                r = r >> 1;
            }
        }
        *t++ = r;
    }
}

extern "C" s32 Aoss_Scramble(u8 *out, s32 n, u8 *key, s32 klen) {
    s32 i;
    u8 *t1;
    u8 *t2;
    t1 = (u8 *)Aoss_Alloc(n / 2);
    if (t1 == NULL) {
        return -1;
    }
    t2 = (u8 *)Aoss_Alloc(n);
    if (t2 == NULL) {
        Aoss_Free(t1);
        return -1;
    }
    for (i = 0; i < 2; i++) {
        Aoss_MakeRoundKey(i, (char *)t1, n, (char *)key, klen);
        Aoss_XorHalf((char *)t1, out, n);
        Aoss_SwapHalves(out, n, t2);
    }
    Aoss_Free(t1);
    Aoss_Free(t2);
    return 0;
}

extern "C" void Aoss_MakeRoundKey(s32 x, char *b, s32 n, char *key, s32 klen) {
    s32 h = n / 2;
    s32 k = DS_MOD(x, klen);
    s32 i;
    for (i = 0; i < h; i++) {
        b[i] = i;
        b[i] ^= key[k++];
        if (k >= klen) {
            k = 0;
        }
    }
}

extern "C" void Aoss_XorHalf(char *a, u8 *b, s32 n) {
    s32 h = n / 2;
    s32 i;
    for (i = 0; i < h; i++) {
        b[h + i] ^= a[i];
    }
}

extern "C" void Aoss_SwapHalves(u8 *a, s32 n, u8 *t) {
    s32 h = n / 2;
    Aoss_Memcpy(t, a + h, h);
    Aoss_Memcpy(t + h, a, h);
    Aoss_Memcpy(a, t, n);
}

extern "C" s32 Aoss_SocAlloc(s32 a, s32 b) {
    if (b > 0) {
        return sAossAllocFunc(b);
    }
    return 0;
}

extern "C" s32 Aoss_SocFree(s32 a, s32 b) {
    return sAossFreeFunc(b);
}

extern "C" s32 Aoss_NetStartup(u32 a, u32 b, u32 c) {
    sAossSocConfig.ipAddress = Aoss_Htonl(a);
    sAossSocConfig.netmask = Aoss_Htonl(b);
    sAossSocConfig.gateway = Aoss_Htonl(c);
    if (Shared_Sock_Startup(&sAossSocConfig) < 0) {
        return -1;
    }
    if (gOwnIp == 0) {
        do {
            OS_Sleep(100);
        } while (gOwnIp == 0);
    }
    return 0;
}

extern "C" s32 Aoss_NetCleanup() {
    if (Sock_Cleanup() < 0) {
        return -1;
    }
    return -(Aoss_WlanDisconnect() != 0 ? 1 : 0);
}

extern "C" s32 Aoss_Memcmp(u8 *a, u8 *b, s32 n) {
    s32 r = 0;
    s32 t;
    goto test;
loop:
    a++;
    b++;
test:
    t = n;
    n--;
    if (t > 0) {
        r = *a - *b;
        if (r == 0) {
            goto loop;
        }
    }
    return r;
}

extern "C" void Aoss_Memcpy(void *dst, void *src, u32 n) {
    MI_CpuCopy8(src, dst, n);
}

extern "C" void *Aoss_Memset(void *p, u32 v, u32 n) {
    return MI_CpuFill8(p, (u8)v, n);
}

extern "C" s32 Aoss_RecvFrom(s32 a, void *b, s32 c, s32 d, SockAddrIn *p, s32 *q) {
    s32 v = *q;
    p->len = v;
    return Sock_RecvFrom(a, b, c, d, p);
}

extern "C" s32 Aoss_Select(s32 a, AossPollFd *p, s32 c, s32 d, s32 *q) {
    s64 sum = 0;
    AossPollFd t = *p;
    sum += q[0] * 0x1ff6210 / 0x40;
    sum += q[1] * 0x1ff6210 / 0x40;
    return Sock_Poll(&t, 1, sum);
}

extern "C" s32 Aoss_SendTo(s32 a, const void *b, s32 c, s32 d, SockAddrIn *p, u32 v) {
    p->len = v;
    return Sock_SendTo(a, b, c, d, p);
}

extern "C" s32 Aoss_SetSockOpt(s32 s, s32 l, s32 o, void *v, s32 n) {
    return s;
}

extern "C" s32 Aoss_SocketCreate(s32 a, s32 b, s32 c) {
    return Sock_Create(a, b);
}

extern "C" s32 Aoss_SocketBind(s32 a, u8 *b, s32 c) {
    *b = c;
    return Shared_Sock_Bind(a, b);
}

extern "C" s32 Aoss_SocketClose(s32 s) {
    return Sock_Close(s);
}

extern "C" u32 Aoss_Htonl(u32 v) {
    return ((v << 24) & 0xff000000) | (((v << 8) & 0xff0000) | (((v >> 24) & 0xff) | ((v >> 8) & 0xff00)));
}

extern "C" u16 Aoss_Htons(s32 v) {
    return (u16)(((v >> 8) & 0xff) | ((v << 8) & 0xff00));
}

extern "C" u32 Aoss_Ntohl(u32 v) {
    return ((v << 24) & 0xff000000) | (((v << 8) & 0xff0000) | (((v >> 24) & 0xff) | ((v >> 8) & 0xff00)));
}

extern "C" s32 Aoss_Ntohs(s32 v) {
    return (u16)(((v >> 8) & 0xff) | ((v << 8) & 0xff00));
}

extern "C" s32 Aoss_Strlen(char *s) {
    s32 n = 0;
    while (s[n] != 0) {
        n++;
    }
    return n;
}

extern "C" u16 Aoss_Rand16(void) {
    if (sAossRandSeeded == 0) {
        u32 s = 0;
        u32 buf[3];
        Aoss_Memset(buf, 0, 12);
        if (RTC_GetTime(buf) == 0) {
            s = s + (buf[0] << 10);
            s = s + (buf[1] << 3);
            s = s + buf[2];
        }
        sAossRand.seed = s;
        sAossRand.mul = 0x5d588b65;
        sAossRand.add = 0x269ec3;
        sAossRandSeeded = 1;
    }
    sAossRand.seed = sAossRand.add + sAossRand.mul * sAossRand.seed;
    return (u16)(((sAossRand.seed >> 16) * 0x7fff) >> 16);
}

extern "C" void Aoss_FdZero(AossPollFd *s) {
    s->fd = 0;
    s->events = 0;
    s->revents = 0;
}

extern "C" void Aoss_FdSet(u32 v, AossPollFd *s) {
    s->fd = v;
    s->events = 1;
}

extern "C" s32 sAossError;
extern "C" u8 sAossRc4Key[0x64];
extern "C" u32 sAossRandSeeded;
extern "C" u32 sAossCrcTable[0x100];
extern "C" AossConnectResult *sAossConnectResult;
extern "C" u8 sAossSessionId[8];
extern "C" void *sAossScanList;
extern "C" u8 *sAossPacketBuf;
extern "C" s32 sAossProgress;
extern "C" s16 sAossDefaultRetry[2];
extern "C" u8 sAossKeyBlockTags[4];
extern "C" AossSocConfig sAossSocConfig;
extern "C" s32 sAossEncryptFlag;
extern "C" AossRandState sAossRand;
extern "C" u8 sAossKeyBuf[0x6a0];
extern "C" AossSession sAossSession;
extern "C" s32 sAossSocket;
extern "C" u8 sAossNameBuf[0x280];

extern "C" s32 sAossError = 0;

extern "C" u8 sAossRc4Key[0x64] = {0};

extern "C" u32 sAossRandSeeded = 0;

extern "C" u32 sAossCrcTable[0x100] = {0};

extern "C" AossConnectResult *sAossConnectResult = 0;

extern "C" u8 sAossSessionId[8] = {0};

extern "C" void *sAossScanList = 0;

extern "C" u8 *sAossPacketBuf = 0;

extern "C" s32 sAossProgress = -1;

extern "C" s16 sAossDefaultRetry[2] = {-1, -1};

extern "C" u8 sAossKeyBlockTags[4] = {9, 8, 0, 0};

extern "C" AossSocConfig sAossSocConfig = {0x01000000, Aoss_SocAlloc, Aoss_SocFree, 0, 0, 0, 0, {0}, 0x1000, 0x1000, {0}};

extern "C" s32 sAossEncryptFlag = 0;

extern "C" AossRandState sAossRand = {0};

extern "C" u8 sAossKeyBuf[0x6a0] = {0};

extern "C" AossSession sAossSession = {0};

extern "C" s32 sAossSocket = -1;

extern "C" u8 sAossNameBuf[0x280] = {0};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02200680) {
    HOST_OVERLAY_VAR(sAossError),
    HOST_OVERLAY_VAR(sAossRc4Key),
    HOST_OVERLAY_VAR(sAossRandSeeded),
    HOST_OVERLAY_VAR(sAossCrcTable),
    HOST_OVERLAY_VAR(sAossConnectResult),
    HOST_OVERLAY_VAR(sAossSessionId),
    HOST_OVERLAY_VAR(sAossScanList),
    HOST_OVERLAY_VAR(sAossPacketBuf),
    HOST_OVERLAY_VAR(sAossProgress),
    HOST_OVERLAY_VAR(sAossDefaultRetry),
    HOST_OVERLAY_VAR(sAossKeyBlockTags),
    HOST_OVERLAY_VAR(sAossSocConfig),
    HOST_OVERLAY_VAR(sAossEncryptFlag),
    HOST_OVERLAY_VAR(sAossRand),
    HOST_OVERLAY_VAR(sAossKeyBuf),
    HOST_OVERLAY_VAR(sAossSession),
    HOST_OVERLAY_VAR(sAossSocket),
    HOST_OVERLAY_VAR(sAossNameBuf),
    HOST_OVERLAY_VARS_END
};
