#include "types.h"
#include "net/gpi.h"
#include "net/gpiProfile.h"
#include "net/gpiInfo.h"
#include "net/gsPlatformUtil.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_0227bd20.h"
#include "proto/ov065/unk_ov065_02283720.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_022789fc.h"
#include "proto/ov065/unk_ov065_0227c6f0.h"
#include "proto/ov065/unk_ov065_0227cd34.h"
#include "proto/ov065/unk_ov065_0227d96c.h"
#include "proto/ov065/unk_ov065_0227df0c.h"
#include "proto/ov065/unk_ov065_0227e160.h"
#include "proto/ov065/unk_ov065_0227f2a4.h"
#include "proto/ov065/unk_ov065_02280740.h"
#include "proto/ov065/unk_ov065_02280c08.h"
#include "proto/ov065/unk_ov065_0228176c.h"
#include "proto/ov065/unk_ov065_02281a5c.h"
#include "proto/ov065/unk_ov065_02283304.h"
extern "C" {
int strncmp(const char *a, const char *b, u32 n);
}

namespace Nb {








typedef void (*GPCallback)(void *, void *, void *);
extern "C" {
}
}

namespace Nc {
extern "C" {


typedef s32 (*GsGpConnectCallback)(GPConnection *, void *, void *);

void gpiProfileMap(GPConnection *, s32 (*)(GPConnection *, GPIProfile *, s32), s32);


}
}

namespace Nc {
extern "C" {
s32 gpInitialize(GPConnection *h, s32 a, s32 b) {
    if (__GSIACResult != 1) {
        return 2;
    }
    if (h == NULL) {
        return 2;
    }
    return gpiInitialize(h, a, b);
}
}
}

namespace Nc {
extern "C" {
void gpDestroy(GPConnection *h) {
    if (h != NULL && *h != NULL) {
        gpiDestroy(h);
    }
}
}
}

namespace Nc {
extern "C" {
s32 gpProcess(GPConnection *h) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    return gpiProcess(h, 0);
}
}
}

namespace Nc {
extern "C" {
s32 gpSetCallback(GPConnection *h, s32 i, GPCallback x, void *y) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (i < 0 || i >= 6) {
        gpiSetErrorString(h, "Invalid func.");
        return 2;
    }
    c->callbacks[i].callback = x;
    c->callbacks[i].param = y;
    return 0;
}
}
}

namespace Nc {
extern "C" {
s32 gpConnectPreAuthenticatedA(GPConnection *h, char *a, char *b, s32 c, s32 d, GsGpConnectCallback cb, void *e) {
    GPIConnection *ctx;
    if (h == NULL || (ctx = *h) == NULL) {
        return 2;
    }
    if (a == NULL || *a == 0) {
        return 2;
    }
    if (b == NULL || *b == 0) {
        return 2;
    }
    if (cb == NULL) {
        gpiSetErrorString(h, "No callback.");
        return 2;
    }
    if (ctx->simulation != 0) {
        s32 z[8] = {0};
        cb(h, z, e);
        return 0;
    }
    return gpiConnect(h, "", "", "",
                               "", a, b, NULL, c, 0, d, (GPCallback)cb, e);
}
}
}

namespace Nc {
extern "C" {
void gpDisconnect(GPConnection *h) {
    GPIConnection *c;
    if (h != NULL) {
        c = *h;
        if (c != NULL) {
            if (c->simulation == 0) {
                gpiDisconnect(h, 1);
                gpiReset(h);
            }
        }
    }
}
}
}

namespace Nb {
extern "C" {
s32 gpProfileSearchA(GPConnection *h, char *a1, char *a2, char *a3, char *a4, char *a5, s32 a6, s32 a7, GPCallback cb, void *arg) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (cb == NULL) {
        gpiSetErrorString(h, "No callback.");
        return 2;
    }
    if (c->simulation != 0) {
        GPProfileSearchResponseArg l = {0, 0, 0, 0};
        l.more = 0x601;
        cb(h, &l, arg);
        return 0;
    }
    return gpiProfileSearch(h, a1, a2, a3, a4, a5, a6, 0, a7, cb, arg);
}
}
}

namespace Nb {
extern "C" {
s32 gpGetInfo(GPConnection *h, s32 a1, s32 a2, s32 a3, GPCallback cb, void *arg) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL || a1 == 0) {
        return 2;
    }
    if (cb == NULL) {
        gpiSetErrorString(h, "No callback.");
        return 2;
    }
    if (c->simulation != 0) {
        GPGetInfoResponseArg b = {0};
        cb(h, &b, arg);
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    return gpiGetInfo(h, a1, a2, a3, cb, arg);
}
}
}

namespace Nb {
extern "C" {
s32 gpSetInfosA(GPConnection *h, s32 a, char *b) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    return gpiSetInfos(h, a, b);
}
}
}

namespace Nb {
extern "C" {
s32 gpSendBuddyRequestA(GPConnection *h, s32 v, const char *s) {
    GPIConnection *c;
    char b[0x401];
    char *p;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    if (s == NULL) {
        gpiSetErrorString(h, "Invalid reason.");
        return 2;
    }
    strzcpy(b, s, 0x401);
    if (b[0] != 0) {
        p = b;
        do {
            if (*p == '\\') {
                *p = '/';
            }
            p++;
        } while (*p != 0);
    }
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\addbuddy\\");
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\sesskey\\");
    gpiAppendIntToBuffer(h, &c->outputBuffer, c->sessKey);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\newprofileid\\");
    gpiAppendIntToBuffer(h, &c->outputBuffer, v);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\reason\\");
    gpiAppendStringToBuffer(h, &c->outputBuffer, b);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\final\\");
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpAuthBuddyRequest(GPConnection *h, s32 a) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    return gpiAuthBuddyRequest(h, a);
}
}
}

namespace Nb {
extern "C" {
s32 gpDenyBuddyRequest(GPConnection *h, s32 a) {
    GPIConnection *c;
    GPIProfile *e;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    if (gpiGetProfile(h, a, &e) == 0) {
        return 0;
    }
    e->requestCount--;
    if (c->infoCaching == 0 && e->requestCount <= 0) {
        GsUtil_Free(e->authSig);
        e->authSig = 0;
        if (gpiCanFreeProfile(e) != 0) {
            gpiRemoveProfile(h, e);
        }
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpGetNumBuddies(GPConnection *h, s32 *out) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        *out = 0;
        return 0;
    }
    *out = c->numBuddies;
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpGetBuddyStatus(GPConnection *h, s32 idx, GPBuddyStatus *out) {
    GPIConnection *c;
    GPIProfile *ent;
    GPIBuddyStatus *s;
    s32 n;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        memset(out, 0, 0x210);
        return 0;
    }
    if (out == NULL) {
        gpiSetErrorString(h, "Invalid status.");
        return 2;
    }
    n = c->numBuddies;
    if (idx < 0 || idx >= n) {
        gpiSetErrorString(h, "Invalid index.");
        return 2;
    }
    ent = (GPIProfile *)gpiFindBuddy(h, idx);
    if (ent == NULL) {
        gpiSetErrorString(h, "Invalid index.");
        return 2;
    }
    s = ent->buddyStatus;
    out->profile = ent->profileId;
    out->status = s->status;
    if (s->statusString != NULL) {
        strzcpy(out->statusString, s->statusString, 0x100);
    } else {
        *s->statusString = 0;
    }
    if (s->locationString != NULL) {
        strzcpy(out->locationString, s->locationString, 0x100);
    } else {
        *s->locationString = 0;
    }
    out->ip = s->ip;
    out->port = s->port;
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpGetBuddyIndex(GPConnection *h, s32 a, s32 *out) {
    GPIConnection *c;
    GPIProfile *e;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        *out = 0;
        return 0;
    }
    if (gpiGetProfile(h, a, &e) != 0 && e->buddyStatus != 0) {
        *out = e->buddyStatus->buddyIndex;
    } else {
        *out = -1;
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpIsBuddy(GPConnection *h, s32 a) {
    GPIConnection *c;
    GPIProfile *e;
    if (h == NULL || (c = *h) == NULL) {
        return 0;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (gpiGetProfile(h, a, &e) != 0 && e->buddyStatus != 0) {
        return 1;
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpDeleteBuddy(GPConnection *h, s32 a) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    {
        s32 r = gpiDeleteBuddy(h, a);
        if (r != 0) {
            return r;
        }
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpSetStatusA(GPConnection *h, s32 v, const char *s1, const char *s2) {
    GPIConnection *c;
    char b1[0x100];
    char b2[0x100];
    char *p;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    if (s1 == NULL) {
        gpiSetErrorString(h, "Invalid statusString.");
        return 2;
    }
    if (s2 == NULL) {
        gpiSetErrorString(h, "Invalid locationString.");
        return 2;
    }
    strzcpy(b1, s1, 0x100);
    if (b1[0] != 0) {
        p = b1;
        do {
            if (*p == '\\') {
                *p = '/';
            }
            p++;
        } while (*p != 0);
    }
    strzcpy(b2, s2, 0x100);
    if (b2[0] != 0) {
        p = b2;
        do {
            if (*p == '\\') {
                *p = '/';
            }
            p++;
        } while (*p != 0);
    }
    if (v == c->lastStatus && strcmp(b1, c->lastStatusString) == 0 && strcmp(b2, c->lastLocationString) == 0) {
        return 0;
    }
    c->lastStatus = v;
    strzcpy(c->lastStatusString, b1, 0x100);
    strzcpy(c->lastLocationString, b2, 0x100);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\status\\");
    gpiAppendIntToBuffer(h, &c->outputBuffer, v);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\sesskey\\");
    gpiAppendIntToBuffer(h, &c->outputBuffer, c->sessKey);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\statstring\\");
    gpiAppendStringToBuffer(h, &c->outputBuffer, b1);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\locstring\\");
    gpiAppendStringToBuffer(h, &c->outputBuffer, b2);
    gpiAppendStringToBuffer(h, &c->outputBuffer, "\\final\\");
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpSendBuddyMessageA(GPConnection *h, s32 a, const char *b) {
    GPIConnection *c;
    if (h == NULL || (c = *h) == NULL) {
        return 2;
    }
    if (c->simulation != 0) {
        return 0;
    }
    if (c->connectState == 4) {
        gpiSetErrorString(h, "The connection has already been disconnected.");
        return 2;
    }
    if (b == 0) {
        gpiSetErrorString(h, "Invalid message.");
        return 2;
    }
    return gpiSendBuddyMessage(h, a, 1, b);
}
}
}

namespace Nb {
extern "C" {
__declspec(weak) void Unk_ov065_0227bd20_pool_order(void) {
    gpiSetErrorString(0, "The connection has already been disconnected.");
    gpiSetErrorString(0, "\\sesskey\\");
    gpiSetErrorString(0, "\\final\\");
    gpiSetErrorString(0, "No callback.");
}
}
}
