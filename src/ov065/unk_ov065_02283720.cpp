
#include "ds_div.h"
#include "types.h"
#include "net/darray.h"
#include "net/SockAddrIn.h"
#include "net/SockHostEnt.h"
#include "net/gpersist.h"
#include "net/gt2Main.h"
#include "net/gpiCallback.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_02283720.h"




namespace N02282f90 {
extern "C" {














extern char data_ov065_0228dd84[];
extern char data_ov065_0228db1c[];
extern char data_ov065_0228dd98[];
extern char data_ov065_0228ddc0[];
extern char data_ov065_0228dadc[];
extern char data_ov065_0228ddf4[];
extern char data_ov065_0228de24[];
extern char data_ov065_0228de4c[];
extern char data_ov065_0228de54[];
extern char data_ov065_0228de60[];
extern char data_ov065_0228de64[];
extern char data_ov065_0228de7c[];
extern char data_ov065_0228de84[];
extern char data_ov065_0228deb4[];
extern char data_ov065_0228dec4[];
extern char data_ov065_0228ded4[];
extern char data_ov065_0228dee8[];
extern char data_ov065_0228df20[];
extern char data_ov065_0228df38[];
extern char data_ov065_0228df50[];
extern char data_ov065_0228df58[];
extern char data_ov065_0228df60[];
extern char data_ov065_0228df6c[];
extern DArrayImplementation *serverreqs;

extern "C" {
void _strlwr(char *);
s32 gpiAddOperation(void *, s32, void *, void *, s32, GPCallback, void *);
s32 gpiProcess(void *, s32);
s32 socket(s32, s32, s32);
s32 SetSockBlocking(s32, s32);
SockHostEnt *Sock_GetHostByName(const char *);
s32 connect(s32, void *, s32);
s32 GOAGetLastError(s32);
void gpiCallErrorCallback(void *, s32, s32);
s32 gpiPeerStartTransferMessage(void *, s32, s32, void *);
s32 gpiSendOrBufferString(void *, s32, char *);
s32 gpiPeerFinishTransferMessage(void *, s32, const char *, s32);
s32 gpiAddCallback(void *, GPICallback, void *, void *, s32);
void gpiRemoveOperation(void *, void *);
s32 GSISocketSelect(s32, s32, s32 *, s32 *);
char *strncpy(char *dst, const char *src, u32 n);
s32 strncmp(const char *, const char *, u32);
s32 OS_SPrintf(char *buf, const char *fmt, ...);

void gpiSetErrorString(void *, const char *);
void gpiSetError(void *, s32, const char *);
s32 gpiValueForKey(const char *, const char *, char *, s32);
s32 gpiCheckForError(void *, const char *, s32);
s32 gpiInitSearchData(void *, void *, s32);
s32 gpiStartSearch(void *, void *, s32, void *, void *);
s32 gpiStartProfileSearch(void *, void *);
s32 gpiSendTransferReply(void *, s32 *, s32, s32, const char *);
}

static inline BOOL Unk_ov065_02283684_B(char *p) {
    if (p != NULL) {
        return TRUE;
    }
    return FALSE;
}

extern "C" {




















}

}
}

namespace N022838c4 {
extern "C" {






extern "C" {
extern DArrayImplementation *serverreqs;



s32 strncmp(const char *, const char *, u32);

s32 CanReceiveOnSocket(s32);
s32 recv(s32, char *, s32, s32);
void shutdown(s32, s32);
void closesocket(s32);
void gti2CloseSocket(GTI2Socket *);

s32 gti2VerifyChallenge(u8 *);



























}

}
}

namespace N022838c4 { extern "C" {
u8 *gti2GetResponse(u8 *out, u8 *in) {
    s32 ok;
    s32 klen;
    s32 i;
    s32 j;
    klen = STD_GetStringLength("3b8dd8995f7c40a9a5c5b7dd5b481341");
    ok = gti2VerifyChallenge(in);
    i = 0;
    j = 0;
    for (; i < 0x20; i++) {
        if (ok == 0 || i == 0 || i == 0xd) {
            out[i] = rand() % 0x5d + 0x21;
        } else {
            s8 c;
            s32 t;
            s32 x;
            if (i == 1 || i == 0xe) {
                c = in[i];
            } else {
                c = in[i - 1];
            }
            t = (u8)in[i];
            x = ("3b8dd8995f7c40a9a5c5b7dd5b481341"[DS_MOD((i + t), klen)] + i * t) % 0x20;
            out[i] = abs((u8)in[x] ^ "3b8dd8995f7c40a9a5c5b7dd5b481341"[DS_MOD((c * j), klen)]) % 0x5d + 0x21;
        }
        j += 0x4647;
    }
    return out;
}
} }

extern "C" char *sGsPersistXorKey = (char *)enc1;
extern "C" { s32 rcvmax; }
namespace N022838c4 { extern "C" {
BOOL gti2CheckResponse(u8 *a, u8 *b) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        if (i == 0 || i == 0xd) {
            continue;
        }
        if (a[i] != b[i]) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

extern "C" u8 data_ov065_0228df7c[16] = {0x13, 0x1d, 0x01, 0x04, 0x00, 0x00, 0x00, 0x28, 0x1f, 0x06, 0x45, 0x34, 0x3f, 0x01, 0x1b, 0x00};
namespace N022838c4 { extern "C" {
void CloseStatsConnection() {
    if (sGsPersistSocket != -1) {
        shutdown(sGsPersistSocket, 2);
        closesocket(sGsPersistSocket);
    }
    sGsPersistSocket = -1;
    ClosePendingCallbacks();
    if (rcvbuffer != 0) {
        GsUtil_Free(rcvbuffer);
        rcvbuffer = 0;
        rcvmax = 0;
        rcvlen = 0;
    }
}
} }

extern "C" { char data_ov065_02291104[0x100]; }
namespace N022838c4 { extern "C" {
s32 PersistThink() {
    s32 r;
    if (sGsPersistSocket == -1) {
        return 0;
    }
    if (stats_initstate != 5) {
        return 0;
    }
    if (SocketReadable(sGsPersistSocket) != 0) {
        do {
            if (rcvmax - rcvlen < 0x80) {
                if (rcvmax < 0x100) {
                    rcvmax = 0x100;
                } else {
                    rcvmax = rcvmax * 2;
                }
                rcvbuffer = (char *)GsUtil_Realloc(rcvbuffer, rcvmax + 1);
                if (rcvbuffer == 0) {
                    return 0;
                }
            }
            r = recv(sGsPersistSocket, rcvbuffer + rcvlen, rcvmax - rcvlen, 0);
            if (r <= 0) {
                CloseStatsConnection();
                return 0;
            }
            rcvlen += r;
            rcvbuffer[rcvlen] = 0;
            r = ProcessInBuffer(rcvbuffer, rcvlen);
            if (r == rcvlen) {
                rcvlen = 0;
            } else {
                memmove(rcvbuffer, rcvbuffer + r, rcvlen - r);
                rcvlen -= r;
            }
        } while (SocketReadable(sGsPersistSocket) != 0);
    }
    if (sGsPersistSocket == -1) {
        return 0;
    }
    return 1;
}
} }

extern "C" { s32 rcvlen; }
namespace N022838c4 { extern "C" {
void xcode_buf(char *p, s32 n) {
    s32 i;
    char *k;
    k = sGsPersistXorKey;
    for (i = 0; i < n; i++) {
        p[i] ^= *k++;
        if (k[0] == 0) {
            k = sGsPersistXorKey;
        }
    }
}
} }

namespace N022838c4 { extern "C" {
char *value_for_key(char *s, char *key) {
    char buf[256] = "\\";
    char *f;
    char *d;
    data_ov065_022910fc ^= 1;
    STD_ConcatenateString(buf, key);
    STD_ConcatenateString(buf, "\\");
    f = strstr(s, buf);
    if (f == 0) {
        return 0;
    }
    f += STD_GetStringLength(buf);
    {
        char *r = data_ov065_02291304 + (data_ov065_022910fc << 8);
        d = r;
        while (*f != 0 && *f != '\\') {
            *d++ = *f++;
        }
        *d = 0;
        return r;
    }
}
} }

extern "C" u8 enc1[16] = {0x00, 0x61, 0x6d, 0x65, 0x53, 0x70, 0x79, 0x33, 0x44, 0, 0, 0, 0, 0, 0, 0};
namespace N022838c4 { extern "C" {
char *value_for_key_safe(char *s, char *key) {
    char *r = value_for_key(s, key);
    if (r == 0) {
        r = "";
    }
    return r;
}
} }

namespace N022838c4 { extern "C" {
s32 SocketReadable(s32 a) {
    return CanReceiveOnSocket(a);
}
} }

namespace N022838c4 { extern "C" {
char *FindFinal(char *s, s32 len) {
    char *p = s;
    s32 n = len - 6;
    if (n > 0) {
        do {
            if (p[0] == '\\' && p[1] == 'f' && p[2] == 'i' && p[3] == 'n' && p[4] == 'a' && p[5] == 'l' && p[6] == '\\') {
                return p;
            }
            p++;
        } while (p - s < n);
    }
    return 0;
}
} }

namespace N022838c4 { extern "C" {
s32 FindRequest(s32 a, s32 b, s32 c) {
    s32 i;
    if (serverreqs == 0) {
        return -1;
    }
    i = 0;
    if (i < ArrayLength(serverreqs)) {
        do {
            s32 *e = (s32 *)ArrayNth(serverreqs, i);
            if (e[0] == a && e[1] == b && e[2] == c) {
                return i;
            }
            i++;
        } while (i < ArrayLength(serverreqs));
    }
    return -1;
}
} }

extern "C" u8 enc3[16] = {0x00, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x41, 0x70, 0x68, 0x65, 0x78, 0, 0, 0, 0};
namespace N022838c4 { extern "C" {
void ProcessPlayerAuth(char *s, s32 len) {
    s32 a = atol(value_for_key_safe(s, "pauthr"));
    s32 b = atol(value_for_key_safe(s, "lid"));
    char *m = value_for_key_safe(s, "errmsg");
    s32 i = FindRequest(0, b, 0);
    if (i != -1) {
        s32 *e = (s32 *)ArrayNth(serverreqs, i);
        e[2] = a;
        CallReqCallback(i, a > 0 ? 1 : 0, 0, m, 0);
    }
}
} }

namespace N022838c4 { extern "C" {
void ProcessGetPid(char *s, s32 len) {
    s32 i;
    s32 a = atol(value_for_key_safe(s, "getpidr"));
    s32 b = atol(value_for_key_safe(s, "lid"));
    i = FindRequest(3, b, 0);
    if (i != -1) {
        s32 *e = (s32 *)ArrayNth(serverreqs, i);
        e[2] = a;
        CallReqCallback(i, a > 0 ? 1 : 0, 0, 0, 0);
    }
}
} }

extern "C" { s32 stats_initstate; }
namespace N022838c4 { extern "C" {
void ProcessGetData(char *s, s32 len) {
    s32 a = atol(value_for_key_safe(s, "getpdr"));
    s32 b = atol(value_for_key_safe(s, "lid"));
    s32 c = atol(value_for_key_safe(s, "pid"));
    s32 d = atol(value_for_key_safe(s, "mod"));
    s32 i = FindRequest(1, b, c);
    if (i != -1) {
        s32 e = atol(value_for_key_safe(s, "length"));
        char *p = strstr(s, "\\data\\");
        char *q;
        if (p == 0) {
            e = 0;
            q = "";
        } else {
            q = p + 6;
        }
        CallReqCallback(i, a, d, q, e);
    }
}
} }

namespace N022838c4 { extern "C" {
void ProcessSetData(char *s, s32 len) {
    s32 a = atol(value_for_key_safe(s, "setpdr"));
    s32 b = atol(value_for_key_safe(s, "pid"));
    s32 c = atol(value_for_key_safe(s, "lid"));
    s32 d = atol(value_for_key_safe(s, "mod"));
    s32 i = FindRequest(2, c, b);
    if (i != -1) {
        CallReqCallback(i, a, d, 0, 0);
    }
}
} }

extern "C" { char data_ov065_02291304[0x200]; }
namespace N022838c4 { extern "C" {
void ProcessStatement(char *s, s32 len) {
    s[len] = 0;
    if (strncmp(s, "\\pauthr\\", 8) == 0) {
        ProcessPlayerAuth(s, len);
    } else if (strncmp(s, "\\getpidr\\", 9) == 0) {
        ProcessGetPid(s, len);
    } else if (strncmp(s, "\\getpidr\\", 9) == 0) {
        ProcessGetPid(s, len);
    } else if (strncmp(s, "\\getpdr\\", 8) == 0) {
        ProcessGetData(s, len);
    } else if (strncmp(s, "\\setpdr\\", 8) == 0) {
        ProcessSetData(s, len);
    }
}
} }

extern "C" s32 sGsPersistSocket = -1;
namespace N02282f90 { extern "C" {
s32 ProcessInBuffer(char *p, s32 n) {
    s32 total = n;
    char *q = (char *)FindFinal(p, n);
    while (n > 0 && q != NULL) {
        s32 len;
        sGsPersistXorKey = (char *)enc1;
        len = q - p;
        xcode_buf(p, len);
        ProcessStatement(p, len);
        n -= len + 7;
        p = q + 7;
        if (n > 0) {
            q = (char *)FindFinal(p, n);
        }
    }
    return total - n;
}
} }

namespace N02282f90 { extern "C" {
void CallReqCallback(s32 idx, s32 a, s32 b, void *p3, s32 p4) {
    if (idx >= 0 && idx < ArrayLength(serverreqs)) {
        serverreq_t *e = (serverreq_t *)ArrayNth(serverreqs, idx);
        void *cb = e->callback;
        if (cb != NULL) {
            switch (e->reqtype) {
            case 0:
                ((PersAuthCallbackFn)cb)(e->localid, e->profileid, a, p3, e->instance);
                break;
            case 1:
                ((PersDataCallbackFn)cb)(e->localid, e->profileid, e->pdtype, e->pdindex, a, b, p3, p4, e->instance);
                break;
            case 2:
                ((PersDataSaveCallbackFn)cb)(e->localid, e->profileid, e->pdtype, e->pdindex, a, b, e->instance);
                break;
            case 3:
                ((ProfileCallbackFn)cb)(e->localid, e->profileid, a, e->instance);
                break;
            }
        }
        ArrayDeleteAt(serverreqs, idx);
    }
}
} }

extern "C" { volatile s32 data_ov065_022910fc; }
extern "C" { char *rcvbuffer; }
namespace N02282f90 { extern "C" {
void ClosePendingCallbacks(void) {
    if (serverreqs != NULL) {
        s32 i = ArrayLength(serverreqs) - 1;
        if (i >= 0) {
            do {
                GsPersistErrorMsg buf = *(GsPersistErrorMsg *)data_ov065_0228df7c;
                sGsPersistXorKey = (char *)enc3;
                xcode_buf((char *)&buf, 15);
                CallReqCallback(i, 0, 0, &buf, 0);
                i--;
            } while (i >= 0);
        }
        ArrayFree(serverreqs);
        serverreqs = NULL;
    }
}
} }

namespace N02282f90 { extern "C" {
void strzcpy(char *dst, const char *src, s32 n) {
    strncpy(dst, src, n);
    *(dst + n - 1) = 0;
}
} }

namespace N02282f90 { extern "C" {
void gpiDebug(void *h, const char *fmt, ...) {
}
} }

extern "C" { char data_ov065_02291204[0x100]; }

extern "C" { DArrayImplementation *serverreqs; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02283720) {
    HOST_OVERLAY_VAR(sGsPersistXorKey),
    HOST_OVERLAY_VAR(rcvmax),
    HOST_OVERLAY_VAR(data_ov065_0228df7c),
    HOST_OVERLAY_VAR(data_ov065_02291104),
    HOST_OVERLAY_VAR(rcvlen),
    HOST_OVERLAY_VAR(enc1),
    HOST_OVERLAY_VAR(enc3),
    HOST_OVERLAY_VAR(stats_initstate),
    HOST_OVERLAY_VAR(data_ov065_02291304),
    HOST_OVERLAY_VAR(sGsPersistSocket),
    HOST_OVERLAY_VAR(data_ov065_022910fc),
    HOST_OVERLAY_VAR(rcvbuffer),
    HOST_OVERLAY_VAR(data_ov065_02291204),
    HOST_OVERLAY_VAR(serverreqs),
    HOST_OVERLAY_VARS_END
};
