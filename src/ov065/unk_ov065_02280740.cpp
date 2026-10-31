#include "types.h"
#include "net/gpiInfo.h"
#include "net/gpiSearch.h"
#include "net/gpi.h"
#include "net/gp.h"
#include "net/gpiPeer.h"
#include "net/gpiTransfer.h"
#include "net/gsPlatformUtil.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02280740.h"
#include "proto/ov065/unk_ov065_02283720.h"


namespace Na {












extern "C" {
void gpiSetErrorString(void *, const char *);
void gpiSetError(void *, s32, const char *);
s32 gpiProcessConnect(void *, void *, char *);
s32 gpiProcessNewProfile(void *, void *, char *);
s32 gpiProcessGetInfo(void *, void *, char *);
s32 gpiProcessRegisterUniqueNick(void *, void *, char *);
s32 shutdown(s32, s32);
s32 closesocket(s32);
s32 gpiAddCallback(void *, GPICallback, void *, void *, s32);
s32 OS_SPrintf(char *, const char *, ...);
s32 gpiSendOrBufferString(void *, void *, const char *);
s32 gpiSendOrBufferStringLen(void *, void *, const char *, s32);
s32 gpiSendOrBufferChar(void *, void *, s32);
s32 gpiAppendStringToBuffer(void *, void *, const char *);
s32 gpiAppendIntToBuffer(void *, void *, s32);
s32 gpiAppendStringToBufferLen(void *, void *, const char *, s32);
s32 gpiAppendCharToBuffer(void *, void *, s32);
void ArrayAppend(void *, void *);
s32 gpiGetProfile(void *, s32, void *);
s32 socket(s32, s32, s32);
s32 SetSockBlocking(s32, s32);
void GsGpPeer_SetSocketBuffers(s32);
s32 connect(s32, void *, s32);
s32 GOAGetLastError(s32);
void gpiCallErrorCallback(void *, s32, s32);

extern char data_ov065_0228d884[];
extern char data_ov065_0228d8ec[];
extern char data_ov065_0228d8f0[];
extern char data_ov065_0228d900[];
extern char data_ov065_0228d914[];
extern char data_ov065_0228d918[];
extern char data_ov065_0228d920[];
extern char data_ov065_0228d928[];
extern char data_ov065_0228d944[];
extern char data_ov065_0228d96c[];
extern char data_ov065_0228d9a0[];


s32 gpiIsValidDate(s32 day, s32 mon, s32 year);






void gpiDestroyOperation(GPConnection *h, GPIOperation *n);














}
extern "C" {
s32 gpiIsValidDate(s32 day, s32 mon, s32 year);
s32 gpiProcessOperation(void *h, GPIOperation *n, char *x);
s32 gpiOperationsAreBlocking(GPConnection *h);
s32 gpiFindOperationByID(GPConnection *h, GPIOperation **out, s32 id);
void gpiRemoveOperation(GPConnection *h, GPIOperation *n);
void gpiDestroyOperation(GPConnection *h, GPIOperation *n);
s32 gpiAddOperation(GPConnection *h, s32 a, void *b, GPIOperation **out, s32 e, GPCallback f, void *g);
s32 gpiFailedOpCallback(void *h, GPIOperation *n);
}
}

namespace Na {
extern "C" {
s32 gpiFailedOpCallback(void *h, GPIOperation *n) {
    GPIConnection *c = *(GPIConnection **)h;
    GPICallbackCopy w;
    s32 r;
    w = n->callback;
    if (w.p.callback != 0) {
        {
            switch (n->type) {
            case 0: {
                GPConnectResponseArg *m = (GPConnectResponseArg *)GsUtil_Alloc(sizeof(GPConnectResponseArg));
                if (m == 0) {
                    gpiSetErrorString(h, "Out of memory.");
                    return 1;
                }
                memset(m, 0, sizeof(GPConnectResponseArg));
                m->result = n->result;
                if (c->errorCode == 0x201) {
                    m->profile = c->profileid;
                    c->profileid = 0;
                }
                r = gpiAddCallback(h, w.p, m, n, 0);
                if (r == 0) {
                    break;
                }
                return r;
            }
            case 1: {
                GPNewProfileResponseArg *m = (GPNewProfileResponseArg *)GsUtil_Alloc(sizeof(GPNewProfileResponseArg));
                if (m == 0) {
                    gpiSetErrorString(h, "Out of memory.");
                    return 1;
                }
                memset(m, 0, sizeof(GPNewProfileResponseArg));
                m->result = n->result;
                r = gpiAddCallback(h, w.p, m, n, 0);
                if (r == 0) {
                    break;
                }
                return r;
            }
            case 2: {
                GPGetInfoResponseArg *m = (GPGetInfoResponseArg *)GsUtil_Alloc(sizeof(GPGetInfoResponseArg));
                if (m == 0) {
                    gpiSetErrorString(h, "Out of memory.");
                    return 1;
                }
                memset(m, 0, sizeof(GPGetInfoResponseArg));
                m->result = n->result;
                r = gpiAddCallback(h, w.p, m, n, 0);
                if (r == 0) {
                    break;
                }
                return r;
            }
            case 3: {
                GPProfileSearchResponseArg *m = (GPProfileSearchResponseArg *)GsUtil_Alloc(sizeof(GPProfileSearchResponseArg));
                if (m == 0) {
                    gpiSetErrorString(h, "Out of memory.");
                    return 1;
                }
                memset(m, 0, sizeof(GPProfileSearchResponseArg));
                m->result = n->result;
                m->matches = NULL;
                r = gpiAddCallback(h, w.p, m, n, 0);
                if (r == 0) {
                    break;
                }
                return r;
            }
            case 4: {
                GPRegisterUniqueNickResponseArg *m = (GPRegisterUniqueNickResponseArg *)GsUtil_Alloc(sizeof(GPRegisterUniqueNickResponseArg));
                if (m == 0) {
                    gpiSetErrorString(h, "Out of memory.");
                    return 1;
                }
                memset(m, 0, sizeof(GPRegisterUniqueNickResponseArg));
                m->result = n->result;
                r = gpiAddCallback(h, w.p, m, n, 0);
                if (r == 0) {
                    break;
                }
                return r;
            }
            }
        }
    }
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiAddOperation(GPConnection *h, s32 a, void *b, GPIOperation **out, s32 e, GPCallback f, void *g) {
    GPIConnection *c = *h;
    GPIOperation *n = (GPIOperation *)GsUtil_Alloc(sizeof(GPIOperation));
    if (n == 0) {
        gpiSetErrorString(h, "Out of memory.");
        return 1;
    }
    n->type = a;
    n->data = b;
    n->blocking = e;
    n->state = 0;
    if (a == 0) {
        n->id = 1;
    } else {
        s32 t = c->nextOperationID++;
        n->id = t;
        if (c->nextOperationID < 2) {
            c->nextOperationID = 2;
        }
    }
    n->result = 0;
    n->callback.p.callback = f;
    n->callback.p.param = g;
    n->pnext = c->operationList;
    c->operationList = n;
    *out = n;
    return 0;
}
}
}

namespace Na {
extern "C" {
void gpiDestroyOperation(GPConnection *h, GPIOperation *n) {
    GPIConnection *c = *h;
    if (n->type == 3) {
        GPISearchData *s = (GPISearchData *)n->data;
        c->numSearches--;
        shutdown(s->sock, 2);
        closesocket(s->sock);
        GsUtil_Free(s->outputBuffer);
        s->outputBuffer = 0;
        GsUtil_Free(s->inputBuffer);
        s->inputBuffer = 0;
    }
    GsUtil_Free((void *)n->data);
    n->data = 0;
    GsUtil_Free(n);
}
}
}

namespace Na {
extern "C" {
void gpiRemoveOperation(GPConnection *h, GPIOperation *n) {
    GPIConnection *c = *h;
    GPIOperation *p = c->operationList;
    GPIOperation *prev = 0;
    for (; p; prev = p, p = p->pnext) {
        if (p == n) {
            if (prev == 0) {
                c->operationList = p->pnext;
            } else {
                prev->pnext = n->pnext;
            }
            gpiDestroyOperation(h, n);
            return;
        }
    }
}
}
}

namespace Na {
extern "C" {
s32 gpiFindOperationByID(GPConnection *h, GPIOperation **out, s32 id) {
    GPIOperation *n = (*h)->operationList;
    for (; n; n = n->pnext) {
        if (n->id == id) {
            if (out) {
                *out = n;
            }
            return 1;
        }
    }
    if (out) {
        *out = 0;
    }
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiOperationsAreBlocking(GPConnection *h) {
    GPIOperation *n = (*h)->operationList;
    for (; n; n = n->pnext) {
        if (n->blocking != 0 && n->type != 3) {
            return 1;
        }
    }
    return 0;
}
}
}

namespace Na {
extern "C" {
s32 gpiProcessOperation(void *h, GPIOperation *n, char *x) {
    s32 r = 0;
    s32 t = n->type;
    switch (t) {
    case 0:
        r = gpiProcessConnect(h, n, x);
        break;
    case 1:
        r = gpiProcessNewProfile(h, n, x);
        break;
    case 2:
        r = gpiProcessGetInfo(h, n, x);
        break;
    case 4:
        r = gpiProcessRegisterUniqueNick(h, n, x);
        break;
    default:
        gpiDebug(h, "gpiProcessOperation was passed an operation with an invalid type (%d)\n", t);
        break;
    }
    if (r != 0) {
        n->result = r;
    }
    return r;
}
}
}

namespace Na {
extern "C" {
s32 gpiIsValidDate(s32 day, s32 mon, s32 year) {
    if (day == 0 && mon == 0 && year == 0) {
        return 1;
    }
    if (day < 0 || mon < 0 || year < 0) {
        return 0;
    }
    switch (mon) {
    case 0:
        if (day != 0) {
            return 0;
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (day > 31) {
            return 0;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30) {
            return 0;
        }
        break;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (day > 29) {
                return 0;
            }
        } else {
            if (day > 28) {
                return 0;
            }
        }
        break;
    default:
        return 0;
    }
    if (year < 0x76c) {
        return 0;
    }
    if (year > 0x81f) {
        return 0;
    }
    if (year == 0x81f) {
        if (mon > 6) {
            return 0;
        }
        if (mon == 6) {
            if (day > 6) {
                return 0;
            }
        }
    }
    return 1;
}
}
}
