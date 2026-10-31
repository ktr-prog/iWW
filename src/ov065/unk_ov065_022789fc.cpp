#include "ds_div.h"
#include "types.h"
#include "net/GsSocket.h"
#include "net/SockHostEnt.h"
#include "net/ghttpConnection.h"
#include "net/gsPlatformUtil.h"
#include "net/SockAddrIn.h"

#include "types64.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_022789fc.h"



extern "C" {
extern const char alternateEncoding[4] = "[]_";
extern const char urlSafeEncodeing[4] = "-_=";
extern const char defaultEncoding[4] = "+/=";
s32 randomnum = 1;
s32 GSINitroErrno;
u8 data_ov065_0229107c[4];
SockHostEnt localhost;
GsHostAddr data_ov065_02291094;
GsHostAddrList data_ov065_022910a8;
}

namespace FA {
extern "C" {
extern const char alternateEncoding[];
extern const char urlSafeEncodeing[];
extern const char defaultEncoding[];
extern s32 randomnum;
extern s32 GSINitroErrno;
s32 Sock_InetAtoN(const char *a, u32 *out);
s32 Sock_GetSockName(s32, void *);
s32 CheckRcode(s32, s32);
s32 longrand(void);
u32 nextlongrand(u32);
void TripToQuart(char *, char *, s32);
s32 inet_addr(const char *a);
}
}

namespace FB {









extern "C" {
extern s32 GSINitroErrno;
extern GsHostAddr data_ov065_02291094;
extern u8 data_0213a410[];
extern SockHostEnt localhost;
extern GsHostAddrList data_ov065_022910a8;
extern u8 data_ov065_0229107c[];
void MI_CpuFill8(void *p, s32 v, s32 n);
s32 Sock_SendTo(s32 a, const void *b, s32 c, u32 d, void *sa);
s32 Sock_Send(sptr a, const void *b, s32 c, u32 d);
s32 Sock_RecvFrom(sptr a, void *b, s32 c, u32 d, SockAddrIn *sa);
s32 Sock_Recv(sptr a, void *b, s32 c, u32 d);
s32 Sock_Accept(s32 a, u8 *sa);
s32 Sock_Listen(s32 a);
s32 Sock_Connect(s32 a, void *sa);
s32 Sock_Bind(s32 a, void *sa);
s32 Sock_Shutdown(s32 a);
s32 Sock_Close(s32 a);
s32 Sock_Create(s32 a, s32 b);
s32 Sock_Poll(GsPollFd *arr, u32 n, s64 timeout);
s32 Sock_Fcntl(s32 a, s32 cmd, u32 flags);
u32 SockCore_GetHostIp();
s32 IpAddr_StoreBe32(u32 v, u32 *p);
s32 GOAGetLastError(s32 s);
s32 ghiDoSend(GHIConnection *o, const char *buf, s32 n);
void OS_Sleep(s32 ms);
s32 OS_SPrintf(char *buf, const char *fmt, ...);

s32 CheckRcode(s32 a, s32 b);
s32 setsockopt(s32 a, s32 b, s32 c, const void *d, s32 e);
s32 getsockopt(s32 a, s32 b, s32 c, void *val, s32 *len);
s32 GSISocketSelect(s32 sock, s32 *rd, s32 *wr, s32 *ex);
s32 ghiAppendDataToBuffer(GHIBuffer *o, const char *s, s32 len);
s32 ghiResizeBuffer(GHIBuffer *o, s32 n);
}
}

namespace FB {
extern "C" {
s32 ghiAppendHeaderToBuffer(GHIBuffer *o, char *a, char *b) {
    if (!ghiAppendDataToBuffer(o, a, 0)) {
        return FALSE;
    }
    if (!ghiAppendDataToBuffer(o, ": ", 2)) {
        return FALSE;
    }
    if (!ghiAppendDataToBuffer(o, b, 0)) {
        return FALSE;
    }
    if (ghiAppendDataToBuffer(o, "\r\n", 2)) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace FB {
extern "C" {
s32 ghiAppendCharToBuffer(GHIBuffer *o, u8 c) {
    u8 t = c;
    if (o != 0) {
        return ghiAppendDataToBuffer(o, (char *)&t, 1);
    }
    return FALSE;
}
}
}

namespace FB {
extern "C" {
s32 ghiAppendIntToBuffer(GHIBuffer *o, s32 x) {
    char buf[16];
    OS_SPrintf(buf, "%d", x);
    return ghiAppendDataToBuffer(o, buf, 0);
}
}
}

namespace FB {
extern "C" {
void ghiResetBuffer(GHIBuffer *o) {
    o->len = 0;
    o->pos = 0;
    *o->data = 0;
}
}
}

namespace FB {
extern "C" {
s32 ghiSendBufferedData(GHIConnection *o) {
    s32 *pp = &o->sendBuffer.pos;
    s32 z = 0;
    s32 w, e;
    s32 r;
    do {
        s32 t = GSISocketSelect(o->socket, NULL, &w, &e);
        if (t == ~z || e != 0) {
            o->completed = 1;
            o->result = 5;
            o->socketError = GOAGetLastError(o->socket);
            return FALSE;
        }
        if (w == 0) {
            return TRUE;
        }
        r = ghiDoSend(o, o->sendBuffer.data + o->sendBuffer.pos, o->sendBuffer.len - o->sendBuffer.pos);
        if (r == ~z) {
            return FALSE;
        }
        *pp += r;
    } while (o->sendBuffer.pos < o->sendBuffer.len);
    return TRUE;
}
}
}

namespace FB {
extern "C" {
s32 ghiReadDataFromBuffer(GHIBuffer *o, char *dst, s32 *len) {
    s32 n = *len;
    s32 avail;
    if (n == 0) {
        return FALSE;
    }
    avail = o->len - o->pos;
    if (avail <= 0) {
        return FALSE;
    }
    if (n >= avail) {
        n = avail;
    }
    memcpy(dst, o->data + o->pos, n);
    dst[n] = 0;
    *len = n;
    o->pos += n;
    return TRUE;
}
}
}

namespace FB {
extern "C" {
u32 current_time() {
    return (OS_GetTick() << 6) / 0x82ea;
}
}
}

namespace FB {
extern "C" {
void msleep(s32 ms) {
    OS_Sleep(ms);
}
}
}

namespace FB {
extern "C" {
void SocketStartUp() {
}
}
}

namespace FB {
extern "C" {
void SocketShutDown() {
}
}
}

namespace FB {
extern "C" {
char *goastrdup(const char *s) {
    char *r;
    if (s == 0) {
        return 0;
    }
    r = (char *)GsUtil_Alloc(STD_GetStringLength(s) + 1);
    if (r != 0) {
        STD_CopyString(r, s);
    }
    return r;
}
}
}

namespace FB {
extern "C" {
char *_strlwr(char *s) {
    s32 c;
    char *r = s;
    c = *s;
    if (c != 0) {
        do {
            if (c >= 0 && c < 0x80) {
                c = data_0213a410[c];
            }
            *s = c;
            s++;
            c = *s;
        } while (c != 0);
    }
    return r;
}
}
}

namespace FB {
extern "C" {
s32 SetSockBlocking(s32 sock, s32 flag) {
    u32 v = Sock_Fcntl(sock, 3, 0);
    if (flag) {
        v = v & ~4;
    } else {
        v = v | 4;
    }
    if (Sock_Fcntl(sock, 4, v) == 0) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace FB {
extern "C" {
s32 SetReceiveBufferSize(s32 sock, s32 val) {
    s32 t = setsockopt(sock, 0xffff, 0x1002, &val, 4);
    BOOL r = FALSE;
    if (t != -1) {
        r = TRUE;
    }
    return r;
}
}
}

namespace FB {
extern "C" {
s32 SetSendBufferSize(s32 sock, s32 val) {
    s32 t = setsockopt(sock, 0xffff, 0x1001, &val, 4);
    BOOL r = FALSE;
    if (t != -1) {
        r = TRUE;
    }
    return r;
}
}
}

namespace FB {
extern "C" {
s32 GetReceiveBufferSize(s32 sock) {
    s32 v;
    s32 len = 4;
    s32 r = getsockopt(sock, 0xffff, 0x1002, &v, &len);
    s32 m = -1;
    if (r != m) {
        m = v;
    }
    return m;
}
}
}

namespace FB {
extern "C" {
s32 GetSendBufferSize(s32 sock) {
    s32 v;
    s32 len = 4;
    s32 r = getsockopt(sock, 0xffff, 0x1001, &v, &len);
    s32 m = -1;
    if (r != m) {
        m = v;
    }
    return m;
}
}
}

namespace FB {
extern "C" {
s32 GSISocketSelect(s32 sock, s32 *rd, s32 *wr, s32 *ex) {
    GsPollFd pfd;
    s32 r;
    pfd.fd = sock;
    pfd.events = 0;
    if (rd) {
        pfd.events |= 1;
    }
    if (wr) {
        pfd.events |= 8;
    }
    pfd.revents = 0;
    r = Sock_Poll(&pfd, 1, 0);
    if (r < 0) {
        return -1;
    }
    if (rd) {
        if (r > 0 && (pfd.revents & 0x41) != 0) {
            *rd = 1;
        } else {
            *rd = 0;
        }
    }
    if (wr) {
        if (r > 0 && (pfd.revents & 8) != 0) {
            *wr = 1;
        } else {
            *wr = 0;
        }
    }
    if (ex) {
        if (r > 0 && (pfd.revents & 0x20) != 0) {
            *ex = 1;
        } else {
            *ex = 0;
        }
    }
    return r;
}
}
}

namespace FB {
extern "C" {
s32 CanReceiveOnSocket(s32 a) {
    s32 out = 0;
    if (GSISocketSelect(a, &out, 0, 0) == 1) {
        return out;
    }
    return 0;
}
}
}

namespace FB {
extern "C" {
s32 CanSendOnSocket(s32 a) {
    s32 out = 0;
    if (GSISocketSelect(a, 0, &out, 0) == 1) {
        return out;
    }
    return 0;
}
}
}

namespace FB {
extern "C" {
SockHostEnt *getlocalhost() {
    localhost.hostName = (char *)"localhost";
    localhost.aliases = (char **)data_ov065_0229107c;
    localhost.addrType = 2;
    localhost.addrLength = 0;
    localhost.addrList = (char **)&data_ov065_022910a8;
    data_ov065_02291094.hostIp = 0;
    IpAddr_StoreBe32(SockCore_GetHostIp(), (u32 *)&data_ov065_02291094);
    if (data_ov065_02291094.hostIp == 0) {
        return NULL;
    }
    data_ov065_022910a8.firstAddr = (u32 *)&data_ov065_02291094;
    localhost.addrLength = 4;
    data_ov065_022910a8.listEnd = 0;
    return &localhost;
}
}
}

namespace FB {
extern "C" {
static inline u32 Unk_ov065_02278dfc_Ntohl(u32 x) {
    return ((x << 24) & 0xff000000) | (((x << 8) & 0xff0000) | (((x >> 24) & 0xff) | ((x >> 8) & 0xff00)));
}

s32 IsPrivateIP(u32 *p) {
    u32 v = Unk_ov065_02278dfc_Ntohl(*p);
    u32 a = (v >> 24) & 0xff;
    s32 b = (v >> 16) & 0xff;
    if (a == 10) {
        return TRUE;
    }
    if (a == 0xac && b >= 0x10 && b <= 0x1f) {
        return TRUE;
    }
    if (a == 0xc0 && b == 0xa8) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace FB {
extern "C" {
s32 CheckRcode(s32 a, s32 b) {
    if (a >= 0) {
        return a;
    }
    GSINitroErrno = a;
    return b;
}
}
}

namespace FB {
extern "C" {
s32 socket(s32 a, s32 b, s32 protocol) {
    return CheckRcode(Sock_Create(a, b), -1);
}
}
}

namespace FB {
extern "C" {
s32 closesocket(s32 a) {
    return CheckRcode(Sock_Close(a), -1);
}
}
}

namespace FB {
extern "C" {
s32 shutdown(s32 a, s32 how) {
    return CheckRcode(Sock_Shutdown(a), -1);
}
}
}

namespace FB {
extern "C" {
s32 bind(s32 a, const SockAddrIn *src, u32 len) {
    SockAddrIn l;
    if (src->port == 0) {
        return 0;
    }
    l = *src;
    l.len = len;
    return CheckRcode(Sock_Bind(a, &l), -1);
}
}
}

namespace FB {
extern "C" {
s32 connect(s32 a, const SockAddrIn *src, u32 len) {
    SockAddrIn l;
    l = *src;
    l.len = len;
    return CheckRcode(Sock_Connect(a, &l), -1);
}
}
}

namespace FB {
extern "C" {
s32 listen(s32 a, s32 backlog) {
    return CheckRcode(Sock_Listen(a), -1);
}
}
}

namespace FB {
extern "C" {
s32 accept(s32 a, u8 *sa, s32 *len) {
    s32 r;
    *sa = *len;
    r = Sock_Accept(a, sa);
    *len = *sa;
    return CheckRcode(r, -1);
}
}
}

namespace FB {
extern "C" {
s32 recv(s32 a, void *b, s32 c, u32 d) {
    return CheckRcode(Sock_Recv(a, b, c, d), -1);
}
}
}

namespace FB {
extern "C" {
s32 recvfrom(s32 a, void *b, s32 c, u32 d, SockAddrIn *sa, s32 *len) {
    s32 r;
    sa->len = *len;
    r = Sock_RecvFrom(a, b, c, d, sa);
    *len = sa->len;
    return CheckRcode(r, -1);
}
}
}

namespace FB {
extern "C" {
s32 send(s32 a, const void *b, s32 c, u32 d) {
    return CheckRcode(Sock_Send(a, b, c, d), -1);
}
}
}

namespace FB {
extern "C" {
s32 sendto(s32 a, const void *b, s32 c, u32 d, const SockAddrIn *addr, u32 len) {
    SockAddrIn l;
    *(len ? &l : &l) = *addr;
    l.len = len;
    return CheckRcode(Sock_SendTo(a, b, c, d, &l), -1);
}
}
}

namespace FB {
extern "C" {
s32 getsockopt(s32 a, s32 b, s32 c, void *val, s32 *len) {
    MI_CpuFill8(val, 0, *len);
    return CheckRcode(0, -1);
}
}
}

namespace FB {
extern "C" {
s32 setsockopt(s32 a, s32 b, s32 c, const void *d, s32 e) {
    return CheckRcode(0, -1);
}
}
}

namespace FA {
extern "C" {
s32 getsockname(s32 a, SockAddrIn *p1, s32 *p2) {
    p1->len = *p2;
    a = Sock_GetSockName(a, p1);
    *p2 = p1->len;
    return CheckRcode(a, -1);
}
}
}

namespace FA {
extern "C" {
s32 inet_addr(const char *a) {
    u32 v;
    if (Sock_InetAtoN(a, &v) == 0) {
        return -1;
    }
    return v;
}
}
}

namespace FA {
extern "C" {
s32 GOAGetLastError(s32 s) {
    return GSINitroErrno;
}
}
}

namespace FA {
extern "C" {
s32 time(s32 *timer) {
    s32 t = (s32)((OS_GetTick() << 6) / 0x1ff6210);
    if (timer != NULL) {
        *timer = t;
    }
    return t;
}
}
}

namespace FA {
extern "C" {
u32 nextlongrand(u32 x) {
    u32 hi;
    u32 r = (x & 0xffff) * 0x41a7;
    hi = (x >> 16) * 0x41a7;
    r += (hi & 0x7fff) << 16;
    if (r > 0x7fffffff) {
        r = (r & 0x7fffffff) + 1;
    }
    r += hi >> 15;
    if (r > 0x7fffffff) {
        r = (r & 0x7fffffff) + 1;
    }
    return r;
}
}
}

namespace FA {
extern "C" {
s32 longrand(void) {
    s32 r = nextlongrand(randomnum);
    randomnum = r;
    return r;
}
}
}

namespace FA {
extern "C" {
void Util_RandSeed(u32 seed) {
    if (seed != 0) {
        seed &= 0x7fffffff;
    } else {
        seed = 1;
    }
    randomnum = seed;
}
}
}

namespace FA {
extern "C" {
s32 Util_RandInt(s32 a, s32 b) {
    s32 d = b - a;
    if (d == 0) {
        return a;
    }
    s32 q = longrand();
    s32 m = DS_MOD(q, d);
    return m + a;
}
}
}

namespace FA {
extern "C" {
void TripToQuart(char *in, char *out, s32 n) {
    u8 buf[3];
    s32 i = 0;
    u8 *p;
    if (n > 0) {
        p = buf;
        do {
            *p = in[i];
            p++;
            i++;
        } while (i < n);
    }
    if (i < 3) {
        p = buf + i;
        do {
            *p = 0;
            p++;
            i++;
        } while (i < 3);
    }
    out[0] = buf[0] >> 2;
    out[1] = ((buf[0] & 3) << 4) | (buf[1] >> 4);
    out[2] = ((buf[1] & 0xf) << 2) | (buf[2] >> 6);
    out[3] = buf[2] & 0x3f;
}
}
}

namespace FA {
extern "C" {
void B64Encode(char *in, char *out, s32 n, s32 mode) {
    char *start = out;
    s32 rem = n;
    const char *tbl;
    char *end;
    s32 m;
    switch (mode) {
    case 1:
        tbl = alternateEncoding;
        break;
    case 2:
        tbl = urlSafeEncodeing;
        break;
    default:
        tbl = defaultEncoding;
        break;
    }
    while (rem > 0) {
        TripToQuart(in, out, n >= 3 ? 3 : n);
        out += 4;
        in += 3;
        rem -= 3;
    }
    end = out;
    m = n % 3;
    if (m == 1) {
        end = out - 2;
    } else if (m == 2) {
        end = out - 1;
    }
    *out = 0;
    if (out > start) {
        do {
            char c;
            out--;
            if (out >= end) {
                *out = tbl[2];
            } else {
                c = *out;
                if (c <= 0x19) {
                    *out = c + 0x41;
                } else if (c <= 0x33) {
                    *out = c + 0x47;
                } else if (c <= 0x3d) {
                    *out = c - 4;
                } else if (c == 0x3e) {
                    *out = tbl[0];
                } else if (c == 0x3f) {
                    *out = tbl[1];
                }
            }
        } while (out > start);
    }
}
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_022789fc) {
    HOST_OVERLAY_VAR(randomnum),
    HOST_OVERLAY_VAR(GSINitroErrno),
    HOST_OVERLAY_VAR(data_ov065_0229107c),
    HOST_OVERLAY_VAR(localhost),
    HOST_OVERLAY_VAR(data_ov065_02291094),
    HOST_OVERLAY_VAR(data_ov065_022910a8),
    HOST_OVERLAY_VARS_END
};
