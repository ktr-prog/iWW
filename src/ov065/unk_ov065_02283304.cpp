#include "types.h"
#include "net/gpi.h"
#include "net/SockAddrIn.h"
#include "net/SockHostEnt.h"
#include "net/gpersist.h"
#include "net/gpiOperation.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02283304.h"
#include "net/gpiTransfer.h"
#include "proto/ov065/unk_ov065_0227d96c.h"
#include "proto/ov065/unk_ov065_02280c08.h"
#include "proto/ov065/unk_ov065_02283720.h"


namespace Na {












extern char data_ov065_0228dd84[];
extern char data_ov065_0228db1c[];
extern char data_ov065_0228dd98[];
extern char data_ov065_0228ddc0[];
extern char data_ov065_0228dadc[];
extern char data_ov065_0228ddf4[];
extern char data_ov065_0228de24[];

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
s32 gpiAddCallback(void *, GPICallback, void *, void *, s32);
void gpiRemoveOperation(void *, void *);
s32 GSISocketSelect(s32, s32, s32 *, s32 *);
s32 ArrayLength(void *);
void ArrayFree(void *);
void *ArrayNth(void *, s32);
void ArrayDeleteAt(void *, s32);
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
s32 gpiSendTransferReply(GPConnection *, GPITransferID *, GPIPeer *, s32, const char *);
}

static inline BOOL Unk_ov065_02283684_B(char *p) {
    if (p != NULL) {
        return TRUE;
    }
    return FALSE;
}

extern "C" {




















}
extern "C" {
void gpiHandleTransferMessage(GPConnection *h, GPIPeer *p1, s32 p2, const char *p3);
s32 gpiSendTransferReply(GPConnection *h, GPITransferID *a, GPIPeer *b, s32 c, const char *dflt);
s32 gpiProcessRegisterUniqueNick(void *h, GPIOperation *s, char *str);
void gpiSetErrorString(void *h, const char *msg);
void gpiSetError(void *h, s32 code, const char *msg);
s32 gpiReadKeyAndValue(void *h, char *buf, s32 *pos, char *out1, char *out2);
s32 gpiCheckSocketConnect(void *h, s32 x, s32 *out);
s32 gpiValueForKey(const char *hay, const char *needle, char *out, s32 n);
s32 gpiCheckForError(void *h, const char *str, s32 flag);
}
}

namespace Na {
extern "C" {
s32 gpiCheckForError(void *h, const char *str, s32 flag) {
    GPIConnection *ctx = *(GPConnection *)h;
    char buf[16];
    if (strncmp(str, "\\error\\", 7) == 0) {
        if (gpiValueForKey(str, "\\err\\", buf, 0x10) != 0) {
            ctx->errorCode = atol(buf);
        }
        if (gpiValueForKey(str, "\\errmsg\\", ctx->errorString, 0x100) == 0) {
            ctx->errorString[0] = 0;
        }
        if (flag != 0) {
            BOOL t = Unk_ov065_02283684_B(strstr(str, "\\fatal\\"));
            gpiCallErrorCallback(h, 4, t ? 1 : 0);
        }
        return 1;
    }
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiValueForKey(const char *hay, const char *needle, char *out, s32 n) {
    s32 c = *needle;
    char *p = strstr(hay, needle);
    s32 i;
    s32 ch;
    if (p == NULL) {
        return 0;
    }
    p += STD_GetStringLength(needle);
    i = 0;
    while (i < n - 1 && (ch = p[i]) != 0 && ch != c) {
        out[i] = ch;
        i++;
    }
    out[i] = 0;
    return 1;
}
}
}

namespace Na {
extern "C" {
s32 gpiCheckSocketConnect(void *h, s32 x, s32 *out) {
    s32 a = 0;
    s32 b = 0;
    s32 r = GSISocketSelect(x, 0, &a, &b);
    if (r == -1) {
        gpiDebug(h, "Error connecting\n");
        gpiSetError(h, 5, "There was an error checking for a completed connection.");
        gpiCallErrorCallback(h, 3, 1);
        return 3;
    }
    if (r > 0) {
        if (b != 0) {
            gpiDebug(h, "Connection rejected\n");
            *out = 4;
            return 0;
        }
        if (a != 0) {
            gpiDebug(h, "Connection accepted\n");
            *out = 3;
            return 0;
        }
    }
    *out = 0;
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiReadKeyAndValue(void *h, char *buf, s32 *pos, char *out1, char *out2) {
    s32 c;
    s32 i = *pos;
    char *p = buf + i;
    if (buf[i] != '\\') {
        gpiSetError(h, 1, "Parse Error.");
        gpiCallErrorCallback(h, 3, 1);
        return 3;
    }
    i = 0;
    buf = p + 2;
    c = p[1];
    if (c != '\\') {
        do {
            if (c == 0) {
                gpiSetError(h, 1, "Parse Error.");
                gpiCallErrorCallback(h, 3, 1);
                return 3;
            }
            if (i == 0x1ff) {
                gpiSetError(h, 1, "Parse Error.");
                gpiCallErrorCallback(h, 3, 1);
                return 3;
            }
            *out1 = c;
            out1++;
            i++;
            c = *buf;
            buf++;
        } while (c != '\\');
    }
    *out1 = 0;
    {
        s32 j = 0;
        s32 d;
        while ((d = *buf++) != '\\' && d != 0) {
            if (j == 0x1ff) {
                gpiSetError(h, 1, "Parse Error.");
                gpiCallErrorCallback(h, 3, 1);
                return 3;
            }
            *out2 = d;
            out2++;
            j++;
        }
    }
    *out2 = 0;
    *pos = *pos + (buf - p - 1);
    return 0;
}
}
}

namespace Na {
extern "C" {
void gpiSetError(void *h, s32 code, const char *msg) {
    GPIConnection *c = *(GPConnection *)h;
    strzcpy(c->errorString, msg, 0x100);
    c->errorCode = code;
}
}
}

namespace Na {
extern "C" {
void gpiSetErrorString(void *h, const char *msg) {
    strzcpy((*(GPConnection *)h)->errorString, msg, 0x100);
}
}
}

namespace Na {
extern "C" {
s32 gpiProcessRegisterUniqueNick(void *h, GPIOperation *s, char *str) {
    GPICallbackCopy pr;
    s32 *p;
    s32 r;
    if (gpiCheckForError(h, str, 1) != 0) {
        return 4;
    }
    if (strncmp(str, "\\rn\\", 4) != 0) {
        gpiSetError(h, 1, "Unexpected data was received from the server.");
        gpiCallErrorCallback(h, 3, 1);
        return 3;
    }
    pr = s->callback;
    if (pr.p.callback != 0) {
        p = (s32 *)GsUtil_Alloc(4);
        if (p == NULL) {
            gpiSetErrorString(h, "Out of memory.");
            return 1;
        }
        *p = 0;
        r = gpiAddCallback(h, pr.p, p, s, 0);
        if (r != 0) {
            return r;
        }
    }
    gpiRemoveOperation(h, s);
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiSendTransferReply(GPConnection *h, GPITransferID *a, GPIPeer *b, s32 c, const char *dflt) {
    char buf[0x24];
    s32 r;
    if (dflt == NULL) {
        dflt = "";
    }
    r = gpiPeerStartTransferMessage(h, b, 0xc9, a);
    if (r != 0) {
        return r;
    }
    OS_SPrintf(buf, "\\version\\%d\\result\\%d", 1, c);
    r = gpiSendOrBufferString(h, b, buf);
    if (r != 0) {
        return r;
    }
    r = gpiPeerFinishTransferMessage(h, b, (char *)dflt, -1);
    if (r != 0) {
        return r;
    }
    return 0;
}
}
}

namespace Na {
extern "C" {
void gpiHandleTransferMessage(GPConnection *h, GPIPeer *p1, s32 p2, const char *p3) {
    char buf[0x40];
    GPITransferID v;
    if (gpiValueForKey(p3, "\\xfer\\", buf, 0x40) != 0) {
        if (sscanf(buf, "%d %u %u", &v.profileid, &v.count, &v.time) == 3) {
            gpiSendTransferReply(h, &v, p1, 2, NULL);
        }
    }
}
}
}
