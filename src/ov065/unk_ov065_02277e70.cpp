#include "types.h"
#include "net/DwcGsHttpCallbackCtx.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_0227931c.h"
#include "proto/ov065/unk_ov065_02277e70.h"



struct GsAvailQuery {
    s32 sock;
    u8 serverAddr[2];
    u16 serverPort;
    u8 serverIp[4];
    u8 queryPacket;
    u8 unk_0d[4];
    char gameName[0x3b];
    u32 packetLen;
    u32 sendTime;
    u32 retryCount;
};

extern "C" {

s32 OS_SPrintf(char *, const char *, ...);


GsAvailQuery AC;

s32 CanReceiveOnSocket(s32 fd);
s32 recvfrom(s32, void *, s32, s32, void *, void *);
void closesocket(s32);
u32 current_time();
void SocketStartUp();
s32 socket(s32, s32, s32);
s32 get_sockaddrin(const char *, s32, void *);

void DwcCore_SetError(s32, s32);
s32 sendto(s32, void *, s32, s32, void *, s32);
}

extern "C" {

void SendPacket() {
    sendto(AC.sock, &AC.queryPacket, AC.packetLen, 0,
                        AC.serverAddr, 8);
    AC.sendTime = current_time();
}

void GSIStartAvailableCheckA(char *url) {
    char buf[0x44];
    s8 c;
    STD_CopyString(__GSIACGamename, url);
    AC.sock = -1;
    SocketStartUp();
    c = GSIACHostname[0];
    if (c == 0) {
        OS_SPrintf(buf, "%s.available.gs.nintendowifi.net", url);
    }
    if (get_sockaddrin(c != 0 ? GSIACHostname : buf, 0x6cfc, AC.serverAddr) != 0) {
        s32 s = socket(2, 2, 0);
        AC.sock = s;
        if (s != -1) {
            s32 n;
            AC.queryPacket = 9;
            n = STD_GetStringLength(url);
            memcpy(AC.gameName, url, n + 1);
            AC.packetLen = n + 6;
            SendPacket();
            AC.retryCount = 0;
        }
    }
}

s32 HandlePacket(s8 *b, s32 n, u8 *addr, u32 *out) {
    if (n < 7) {
        return 1;
    }
    if (memcmp(addr + 4, AC.serverIp, 4) != 0) {
        return 1;
    }
    if (*(u16 *)(addr + 2) != AC.serverPort) {
        return 1;
    }
    if (memcmp(b, "\xfe\xfd\x09", 3) != 0) {
        return 1;
    }
    u32 v = ((s32)b[3] << 24) & 0xff000000;
    v |= ((s32)b[4] << 16) & 0xff0000;
    v |= ((s32)b[5] << 8) & 0xff00;
    v |= (s32)b[6] & 0xff;
    *out = v;
    return 0;
}

s32 GSIAvailableCheckThink() {
    u32 addr[2];
    s32 len;
    u32 flags;
    u8 buf[0x40];
    len = 8;
    if (AC.sock == -1) {
        __GSIACResult = 1;
        return 1;
    }
    if (CanReceiveOnSocket(AC.sock) != 0) {
        s32 n = recvfrom(AC.sock, buf, 0x40, 0, addr, &len);
        if (HandlePacket((s8 *)buf, n, (u8 *)addr, &flags) == 0) {
            closesocket(AC.sock);
            if ((flags & 1) != 0) {
                __GSIACResult = 2;
            } else if ((flags & 2) != 0) {
                __GSIACResult = 3;
            } else {
                __GSIACResult = 1;
            }
            return __GSIACResult;
        }
    }
    if (current_time() > AC.sendTime + 0x7d0) {
        if (AC.retryCount == 1) {
            closesocket(AC.sock);
            __GSIACResult = 1;
            return 1;
        }
        SendPacket();
        AC.retryCount++;
    }
    return 0;
}

s32 DwcGsHttp_Startup() {
    ghttpStartup();
    return 1;
}

s32 DwcGsHttp_Cleanup() {
    ghttpCleanup();
    return 1;
}

s32 DwcGsHttp_Process() {
    ghttpThink();
    return 1;
}

s32 DwcGsHttp_OnRequestDone(u32 request, u32 e, char *c, u32 d, void *param) {
    DwcGsHttpCallbackCtx *p = (DwcGsHttpCallbackCtx *)param;
    DwcGsHttpCallback cb = p->callback;
    if (cb != NULL) {
        if (e == 0) {
            cb(c, d, e, p->userData);
        } else {
            DwcGsHttp_ReportError(e);
            cb(0, 0, e, p->userData);
        }
    }
    DwcNet_Free(4, p, 0);
    return 1;
}

void DwcGsHttp_PostCreate(GHIPost **p) {
    *p = ghttpNewPost();
}

s32 DwcGsHttp_PostAddString(GHIPost **p, const char *name, const char *value) {
    return ghttpPostAddStringA(*p, name, value);
}

s32 DwcGsHttp_Post(const char *a, GHIPost **pa, DwcGsHttpCallback cb, void *ud) {
    DwcGsHttpCallbackCtx *p;
    s32 r;
    p = (DwcGsHttpCallbackCtx *)DwcNet_Alloc(4, sizeof(DwcGsHttpCallbackCtx));
    if (p == NULL) {
        DwcGsHttp_ReportError(0x14);
        cb(0, 0, 0x14, p->userData);
        return 0x14;
    }
    p->userData = ud;
    p->callback = cb;
    r = ghttpPostA(a, *pa, 0, DwcGsHttp_OnRequestDone, p);
    if (r < 0) {
        DwcGsHttp_ReportError(r);
        cb(0, 0, r, p->userData);
        DwcNet_Free(4, p, 0);
    }
    return r;
}

s32 DwcGsHttp_Get(const char *a, DwcGsHttpCallback cb, void *ud) {
    DwcGsHttpCallbackCtx *p;
    s32 r;
    p = (DwcGsHttpCallbackCtx *)DwcNet_Alloc(4, sizeof(DwcGsHttpCallbackCtx));
    if (p == NULL) {
        DwcGsHttp_ReportError(0x14);
        cb(0, 0, 0x14, p->userData);
        return 0x14;
    }
    p->userData = ud;
    p->callback = cb;
    r = ghttpGetA(a, 0, DwcGsHttp_OnRequestDone, p);
    if (r < 0) {
        DwcGsHttp_ReportError(r);
        cb(0, 0, r, p->userData);
        DwcNet_Free(4, p, 0);
    }
    return r;
}

s32 DwcGsHttp_ReportError(s32 e) {
    s32 b = -0x17ed0;
    s32 a = 6;
    if (e == 0) {
        return 0;
    }
    switch (e) {
    case -7:
        b -= 0x320;
        break;
    case -6:
        b -= 0x32a;
        break;
    case -5:
        b -= 0x348;
        break;
    case -4:
    case -3:
    case -2:
        b -= 0x334;
        break;
    case -1:
        b -= 0x33e;
        break;
    case 1:
    case 20:
        a = 8;
        b -= 1;
        break;
    case 2:
        b -= 0x348;
        break;
    case 3:
        b -= 0x352;
        break;
    case 4:
        b -= 0x1e;
        break;
    case 5:
        b -= 0x32;
        break;
    case 6:
    case 11:
    case 12:
        b -= 0x14;
        break;
    case 7:
        b -= 0x35c;
        break;
    case 8:
    case 9:
    case 10:
        b -= 0x366;
        break;
    case 13:
    case 14:
        b -= 0x370;
        break;
    case 15:
        b -= 0x37a;
        break;
    case 16:
        b -= 0x384;
        break;
    case 17:
        b -= 0x38e;
        break;
    case 0:
    case 18:
    case 19:
        break;
    }
    DwcCore_SetError(a, b);
    return e;
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02277e70) {
    HOST_OVERLAY_VAR(AC),
    HOST_OVERLAY_VARS_END
};
