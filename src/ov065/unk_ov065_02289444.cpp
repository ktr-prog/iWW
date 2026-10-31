#include "ds_div.h"
#include "types.h"
#include "net/GsBytes.h"
#include "net/darray.h"
#include "net/sb_internal.h"
#include "net/gsPlatformUtil.h"
#include "net/SockHostEnt.h"
#include "net/SockAddrIn.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/autoload_2/unk_0212fa54.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_022884fc.h"
#include "proto/ov065/unk_ov065_02289444.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_022789fc.h"
#include "proto/ov065/unk_ov065_02288c78.h"

extern "C" {
_SBServer *SBAllocServer(SBServerList *unused, u32 addr, u32 port);
void SBServerSetFlags(_SBServer *e, u32 v);
}

extern "C" {
char *data_ov065_0228e954 = "Query Error: ";
char *SBOverrideMasterServer;
SBServerList *g_sortserverlist;
_SBServer *SBNullServer;
}

namespace F02288e2c {














static inline u16 Unk_ov065_02289044_Htons(u16 x) {
    return (x >> 8 & 0xff) | ((x << 8) & 0xff00);
}

extern "C" {
extern char *data_ov065_0228e928[2];
extern u16 data_0213a510[];
extern _SBServer *SBNullServer;

s32 OS_SPrintf(char *, const char *, ...);

s32 CanReceiveOnSocket(s32);
s32 SBQueryEngineRemoveServerFromFIFOs(void *, void *);
s32 SBQueryEngineAddQueryKey(void *, s32);
s32 SBQueryEngineThink(void *);
s32 SBQueryEngineUpdateServer(void *, void *, s32, s32);
s32 SBEngineCleanup(void *);
s32 SBEngineHaltUpdates(void *);
s32 SBQueryEngineSetPublicIP(void *, s32);
s32 SBQueryEngineInit(void *, s32, s32, s32, void *, void *);
s32 SBIsNullServer(_SBServer *);
s32 SBServerGetPing(void *);
char *SBRefStr(SBServerList *, const char *);

char *mytok(char *s, s32 ch);
s32 CheckValidKey(char *s);
char *SBServerGetStringValueA(void *a, char *k, char *d);
s32 ServerBrowserHalt(void *o);
s32 ServerBrowserThink(void *o);
void EngineCallback(void *, s32, _SBServer *, _ServerBrowser *);
void ListCallback(SBServerList *, s32, _SBServer *, _ServerBrowser *);
s32 SBListThink(SBServerList *sub);
s32 ProcessLanData(SBServerList *);
s32 RefStringCompare(char **, char **);
void RefStringFree(void **);

}
}

namespace F02289808 {



extern "C" {
extern _SBServer *SBNullServer;
s32 CanReceiveOnSocket(s32);
void ErrorDisconnect(SBServerList *);
void GOADecrypt(void *, void *, s32);
s32 SBIsNullServer(_SBServer *server);
s32 ParseServer(SBServerList *, _SBServer *, u8 *, s32, s32);
char *SBRefStr(SBServerList *, const char *);
void SBSetLastListErrorPtr(SBServerList *, const char *);
s32 IncomingListParseServer(SBServerList *, u8 *, s32);

s32 ProcessAdHocData(SBServerList *c);

s32 ProcessPushServer(SBServerList *c, u8 *p, s32 n);
s32 ProcessDeleteServer(SBServerList *c, u8 *p, s32 n);
s32 ProcessMaploop(SBServerList *c, u8 *p, s32 n);
s32 ProcessPlayerSearch(SBServerList *c, u8 *p, s32 n);
s32 ProcessPushKeyList(SBServerList *c, u8 *p, s32 n);
s32 ProcessMainListData(SBServerList *c);
}

static inline void Cpy2(u8 *d, u8 *s) {
    d[0] = s[0];
    d[1] = s[1];
}
static inline void Cpy4(u8 *d, u8 *s) {
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
}
#define HTONS(x) ((u16)((((x) >> 8) & 0xff) | (((x) << 8) & 0xff00)))
static inline void Get16(u8 *d, u8 *s) {
    d[0] = s[0];
    d[1] = s[1];
}
static inline void Get16b(u16 *dd, u8 *s) {
    u8 *d = (u8 *)dd;
    d[0] = s[0];
    d[1] = s[1];
}
static inline u32 Swap32(u32 x) {
    return ((x << 24) & 0xff000000) | (((x << 8) & 0xff0000) | (((x >> 24) & 0xff) | ((x >> 8) & 0xff00)));
}
#define HTONL(x) Swap32(x)

extern "C" {

}
}

namespace F0228a20c {


extern "C" {

s32 func_02133150(s32, s32);

void GOACryptInit(void *, void *, s32);
u32 SBServerGetState(_SBServer *);
void SBServerSetState(_SBServer *, u8);
void SBServerSetICMPIP(_SBServer *, u32);
void SBServerSetPrivateAddr(_SBServer *, u32, u32);
s32 SBIsNullServer(_SBServer *);
s32 ServerListConnect(SBServerList *);
void ErrorDisconnect(SBServerList *);
void SBReleaseStr(SBServerList *, const char *);

void SBSetLastListErrorPtr(SBServerList *ctx, const char *v);
s32 IncomingListParseServer(SBServerList *ctx, u8 *buf, s32 n);
s32 ParseServer(SBServerList *ctx, _SBServer *ent, u8 *buf, s32 n, s32 flag);
s32 AllKeysPresent(SBServerList *ctx, u8 *buf, s32 n);
s32 FullRulesPresent(u8 *buf, s32 n);
s32 ServerSizeForFlags(u32 flags);
void FreePopularValues(SBServerList *ctx);
void SetupListChallenge(SBServerList *ctx);
void BufferAddData(u8 **cur, const void *src, s32 n, s32 *len);
void BufferAddInt(u8 **cur, u32 v, s32 *len);

}
}

namespace F0228ab3c {




static inline void Cp4(GsBytes4 *d, GsBytes4 *s) {
    *d = *s;
}


extern "C" {
extern char *SBOverrideMasterServer;
extern char *data_ov065_0228e954;
extern _SBServer *SBNullServer;
extern u8 data_0213a410[];
s32 OS_SPrintf(char *buf, const char *fmt, ...);
s32 strncmp(const char *a, const char *b, u32 n);

SockHostEnt *Sock_GetHostByName(char *name);
void SBSetLastListErrorPtr(SBServerList *c, const char *v);
char *SBServerGetStringValueA(void *rec, char *key, char *dflt);
s32 SBServerGetIntValueA(_SBServer *rec, char *key, s32 a);
void SocketStartUp();

s32 ServerListConnect(SBServerList *c);
u32 StringHash__sb_serverlist(const char *s, u32 n);
void ErrorDisconnect(SBServerList *c);
void SBReleaseStr(SBServerList *c, const char *key);
char *SBRefStr(SBServerList *c, const char *key);
void SBAllocateServerList(SBServerList *c);
void AddServerToDeadlist(SBServerList *c, _SBServer *x);
void SBServerListSort(SBServerList *c, s32 a, char *b, u32 mode);
s32 StrNoCaseKeyCompare(void *a, void *b);
s32 StrCaseKeyCompare(void *a, void *b);
s32 FloatKeyCompare(void *a, void *b);
s32 IntKeyCompare(void *a, void *b);

}
}

namespace F0228ab3c {
extern "C" {
s32 IntKeyCompare(void *a, void *b) {
    _SBServer *ra = *(_SBServer *volatile *)a;
    _SBServer *rb = *(_SBServer **)b;
    s32 r = SBServerGetIntValueA(ra, g_sortserverlist->sortkey, 0);
    r -= SBServerGetIntValueA(rb, g_sortserverlist->sortkey, 0);
    if (g_sortserverlist->sortascending == 0) {
        r = -r;
    }
    return r;
}
}
}

namespace F0228ab3c {
extern "C" {
s32 FloatKeyCompare(void *a, void *b) {
    _SBServer *ra = *(_SBServer *volatile *)a;
    _SBServer *rb = *(_SBServer **)b;
    double d1 = SBServerGetFloatValueA(ra, g_sortserverlist->sortkey, 0);
    double d2 = SBServerGetFloatValueA(rb, g_sortserverlist->sortkey, 0);
    double d = d1 - d2;
    if (g_sortserverlist->sortascending == 0) {
        d = 0 - d;
    }
    if ((float)d > 0) {
        return 1;
    }
    return (float)d < 0 ? -1 : 0;
}
}
}

namespace F0228ab3c {
extern "C" {
s32 StrCaseKeyCompare(void *a, void *b) {
    char *s1 = SBServerGetStringValueA(*(_SBServer **)a, g_sortserverlist->sortkey, "");
    char *s2 = SBServerGetStringValueA(*(_SBServer **)b, g_sortserverlist->sortkey, "");
    s32 r = strcmp(s1, s2);
    if (g_sortserverlist->sortascending == 0) {
        r = -r;
    }
    return r;
}
}
}

namespace F0228ab3c {
extern "C" {
s32 StrNoCaseKeyCompare(void *a, void *b) {
    char *s1 = SBServerGetStringValueA(*(_SBServer **)a, g_sortserverlist->sortkey, "");
    char *s2 = SBServerGetStringValueA(*(_SBServer **)b, g_sortserverlist->sortkey, "");
    s32 r = func_02130b04(s1, s2);
    if (g_sortserverlist->sortascending == 0) {
        r = -r;
    }
    return r;
}
}
}

namespace F0228ab3c {
extern "C" {
void SBServerListSort(SBServerList *c, s32 a, char *b, u32 mode) {
    ArrayCompareFn cmp;
    switch (mode) {
    case 0:
        cmp = IntKeyCompare;
        break;
    case 1:
        cmp = FloatKeyCompare;
        break;
    case 2:
        cmp = StrCaseKeyCompare;
        break;
    case 3:
        cmp = StrNoCaseKeyCompare;
        break;
    default:
        cmp = StrNoCaseKeyCompare;
        break;
    }
    c->sortkey = b;
    c->sortascending = a;
    g_sortserverlist = c;
    ArraySort(c->servers, cmp);
}
}
}

namespace F0228ab3c {
extern "C" {
void SBServerListAppendServer(SBServerList *c, _SBServer *a) {
    ArrayAppend(c->servers, &a);
    c->ListCallback(c, 0, a, c->instance);
}
}
}

namespace F0228ab3c {
extern "C" {
s32 SBServerListFindServer(SBServerList *c, _SBServer *key) {
    s32 n = ArrayLength(c->servers);
    s32 i;
    for (i = 0; i < n; i++) {
        if (key == *(_SBServer **)ArrayNth(c->servers, i)) {
            return i;
        }
    }
    return -1;
}
}
}

namespace F0228ab3c {
extern "C" {
s32 SBServerListFindServerByIP(SBServerList *c, s32 a, s32 b) {
    _SBServer *e;
    s32 i;
    s32 n = ArrayLength(c->servers);
    for (i = 0; i < n; i++) {
        e = *(_SBServer **)ArrayNth(c->servers, i);
        if ((u32)a == SBServerGetPublicInetAddress(e) && (u32)b == SBServerGetPublicQueryPortNBO(e)) {
            return i;
        }
    }
    return -1;
}
}
}

namespace F0228ab3c {
extern "C" {
void AddServerToDeadlist(SBServerList *c, _SBServer *x) {
    _SBServer *t = c->deadlist;
    if (t == NULL) {
        SBServerSetNext(x, NULL);
    } else {
        SBServerSetNext(x, t);
    }
    c->deadlist = x;
}
}
}

namespace F0228ab3c {
extern "C" {
void SBServerListRemoveAt(SBServerList *c, s32 i) {
    _SBServer *v = *(_SBServer **)ArrayNth(c->servers, i);
    c->ListCallback(c, 2, v, c->instance);
    ArrayDeleteAt(c->servers, i);
    AddServerToDeadlist(c, v);
}
}
}

namespace F0228ab3c {
extern "C" {
s32 SBServerListCount(SBServerList *c) {
    return ArrayLength(c->servers);
}
}
}

namespace F0228ab3c {
extern "C" {
_SBServer *SBServerListNth(SBServerList *c, s32 i) {
    return *(_SBServer **)ArrayNth(c->servers, i);
}
}
}

namespace F0228ab3c {
extern "C" {
void SBFreeDeadList(SBServerList *c) {
    if (c->deadlist != NULL) {
        _SBServer *cur = c->deadlist;
        while (cur != NULL) {
            _SBServer *next = (_SBServer *)SBServerGetNext(cur);
            SBServerFree(&cur);
            cur = next;
        }
        c->deadlist = NULL;
    }
}
}
}

namespace F0228ab3c {
extern "C" {
void SBServerListClear(SBServerList *c) {
    s32 n = ArrayLength(c->servers);
    s32 i;
    for (i = 0; i < n; i++) {
        void *p = ArrayNth(c->servers, i);
        AddServerToDeadlist(c, *(_SBServer **)p);
    }
    ArrayClear(c->servers);
    SBFreeDeadList(c);
}
}
}

namespace F0228ab3c {
extern "C" {
void SBAllocateServerList(SBServerList *c) {
    c->servers = ArrayNew(sizeof(_SBServer *), 0x64, 0);
    c->deadlist = NULL;
}
}
}

namespace F0228ab3c {
extern "C" {
char *SBRefStr(SBServerList *c, const char *key) {
    SBRefString l;
    SBRefString *e;
    l.str = (char *)key;
    e = (SBRefString *)TableLookup(SBRefStrHash(), &l);
    if (e != NULL) {
        e->refcount++;
        return e->str;
    }
    l.str = goastrdup((char *)key);
    l.refcount = 1;
    TableEnter(SBRefStrHash(), &l);
    return l.str;
}
}
}

namespace F0228ab3c {
extern "C" {
void SBReleaseStr(SBServerList *c, const char *key) {
    const char *k = key;
    SBRefString *e = (SBRefString *)TableLookup(SBRefStrHash(), &k);
    if (e != NULL) {
        e->refcount--;
        if (e->refcount == 0) {
            TableRemove(SBRefStrHash(), &k);
        }
    }
}
}
}

namespace F0228ab3c {
extern "C" {
s32 NTSLengthSB(const u8 *s, s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        if (s[i] == 0) {
            return i + 1;
        }
    }
    return -1;
}
}
}

namespace F0228ab3c {
extern "C" {
void SBServerListInit(SBServerList *c, char *a, char *b, char *d, s32 e, s32 f, void *g, void *h) {
    if (f != 0 || __GSIACResult == 1) {
        s32 neg = -1;
        c->state = 1;
        SBAllocateServerList(c);
        SBRefStrHash();
        STD_CopyString(c->queryforgamename, a);
        STD_CopyString(c->queryfromgamename, b);
        STD_CopyString(c->queryfromkey, d);
        c->ListCallback = (SBListCallBackFn)g;
        c->MaploopCallback = 0;
        c->instance = h;
        c->sortkey = "";
        c->mypublicip = 0;
        c->slsocket = neg;
        c->inbuffer = 0;
        c->inbufferlen = 0;
        c->keylist = 0;
        c->expectedelements = neg;
        c->numpopularvalues = 0;
        c->srcip = 0;
        c->fromgamever = e;
        SBSetLastListErrorPtr(c, "");
        c->unk_5cc = 0;
        srand(current_time());
        SocketStartUp();
    }
}
}
}

namespace F0228ab3c {
extern "C" {
void ErrorDisconnect(SBServerList *c) {
    if (c->inbufferlen > 0 && (u32)c->inbufferlen > (u32)STD_GetStringLength(data_ov065_0228e954)) {
        char *s = data_ov065_0228e954;
        s32 len = STD_GetStringLength(s);
        if (strncmp((char *)c->inbuffer, s, len) == 0) {
            SBSetLastListErrorPtr(c, (const char *)c->inbuffer + STD_GetStringLength(s));
            c->ListCallback(c, 5, SBNullServer, c->instance);
        }
    }
    c->ListCallback(c, 4, SBNullServer, c->instance);
    SBServerListDisconnect(c);
}
}
}

namespace F0228ab3c {
extern "C" {
u32 StringHash__sb_serverlist(const char *s, u32 n) {
    s32 ch;
    u32 h = 0;
    ch = *s;
    while (ch != 0) {
        if (ch >= 0 && ch < 0x80) {
            ch = data_0213a410[ch];
        }
        h = h * 0x9ccf9319;
        h += ch;
        s++;
        ch = *s;
    }
    return DS_UMOD(h, n);
}
}
}

namespace F0228ab3c {
extern "C" {
s32 ServerListConnect(SBServerList *c) {
    struct {
        SockAddrIn sa;
        char host[0x80];
    } l;
    u32 h = StringHash__sb_serverlist(c->queryforgamename, 0x14);
    if (SBOverrideMasterServer != NULL) {
        STD_CopyString(l.host, SBOverrideMasterServer);
    } else {
        OS_SPrintf(l.host, "%s.ms%d.gs.nintendowifi.net", c->queryforgamename, h);
    }
    l.sa.family = 2;
    l.sa.port = 0xee70;
    l.sa.addr = inet_addr(l.host);
    if (l.sa.addr == (u32)-1) {
        SockHostEnt *ent = Sock_GetHostByName(l.host);
        if (ent == NULL) {
            return 2;
        }
        u8 *d = (u8 *)&l.sa.addr;
        u8 *s2 = (u8 *)*ent->addrList;
        d[0] = s2[0];
        d[1] = s2[1];
        d[2] = s2[2];
        d[3] = s2[3];
    }
    if (c->slsocket == -1) {
        c->slsocket = socket(2, 1, 0);
        if (c->slsocket == -1) {
            return 1;
        }
    }
    if (connect(c->slsocket, &l.sa, 8) != 0) {
        closesocket(c->slsocket);
        c->slsocket = -1;
        return 3;
    }
    return 0;
}
}
}

namespace F0228ab3c {
extern "C" {
void BufferAddNTS(u8 **p, const char *s, s32 *n) {
    s32 len;
    if (s == NULL) {
        s = "";
    }
    len = STD_GetStringLength(s) + 1;
    memcpy(*p, s, len);
    *n += len;
    *p += len;
}
}
}

namespace F0228ab3c {
extern "C" {
void BufferAddByte(u8 **p, u8 c, s32 *n) {
    **p = c;
    ++*n;
    ++*p;
}
}
}

namespace F0228a20c {
extern "C" {
void BufferAddInt(u8 **cur, u32 v, s32 *len)
{
    u8 *d = *cur;
    u8 *sp = (u8 *)&v;
    d[0] = sp[0];
    d[1] = sp[1];
    d[2] = sp[2];
    d[3] = sp[3];
    *len += 4;
    *cur += 4;
}
}
}

namespace F0228a20c {
extern "C" {
void BufferAddData(u8 **cur, const void *src, s32 n, s32 *len)
{
    memcpy(*cur, src, n);
    *len += n;
    *cur += n;
}
}
}

namespace F0228a20c {
extern "C" {
void SetupListChallenge(SBServerList *ctx)
{
    s32 acc, i;
    s32 b, a, ta, tb;

    ctx->mychallenge[0] = (s8)(rand() % 0x5d + 0x21);
    acc = 0;
    i = 1;
    do {
        a = ctx->mychallenge[i - 1];
        b = ctx->mychallenge[0];
        ta = a < b;
        tb = b < 0x4f;
        b &= 1;
        acc ^= (i ^ a) & 1;
        b ^= acc;
        b ^= tb;
        acc = b;
        acc ^= ta;
        ctx->mychallenge[i] = (s8)(rand() % 0x5d + 0x21);
        if ((acc != 0 && (ctx->mychallenge[i] & 1) == 0) || (acc == 0 && (ctx->mychallenge[i] & 1) == 1)) {
            ctx->mychallenge[i]++;
        }
        i++;
    } while (i < 8);
}
}
}

namespace F0228a20c {
extern "C" {
s32 SendWithRetry(SBServerList *ctx, const void *buf, s32 n)
{
    s32 tries = 1;
    s32 r;
    s32 res;

    do {
        tries--;
        r = send(ctx->slsocket, buf, n, 0);
        if (r > 0) {
            break;
        }
        if (tries < 0) {
            break;
        }
        SBServerListDisconnect(ctx);
        res = SBServerListConnectAndQuery(ctx, 0, 0, 2, 0);
        if (res != 0) {
            ErrorDisconnect(ctx);
            return res;
        }
    } while (tries >= 0);
    if (r <= 0) {
        return 3;
    }
    return 0;
}
}
}

namespace F0228a20c {
extern "C" {
s32 SBServerListConnectAndQuery(SBServerList *ctx, const char *user, const char *pass, u32 flags, u32 extra)
{
    u16 tmp;
    s32 len;
    u8 *cur;
    u8 buf[0x300];
    s32 r;
    u8 *d;
    u8 *sp;

    if (user == 0) {
        user = (const char *)"";
    }
    if (pass == 0) {
        pass = (const char *)"";
    }
    if (STD_GetStringLength(user) > 0x100) {
        return 6;
    }
    if (STD_GetStringLength(pass) > 0x100) {
        return 6;
    }
    r = ServerListConnect(ctx);
    if (r != 0) {
        goto end;
    }
    ctx->queryoptions = flags;
    SetupListChallenge(ctx);
    len = 2;
    cur = &buf[2];
    BufferAddByte(&cur, 0, &len);
    BufferAddByte(&cur, 1, &len);
    BufferAddByte(&cur, 3, &len);
    BufferAddInt(&cur, ctx->fromgamever, &len);
    BufferAddNTS(&cur, (const char *)ctx->queryforgamename, &len);
    BufferAddNTS(&cur, (const char *)ctx->queryfromgamename, &len);
    BufferAddData(&cur, ctx->mychallenge, 8, &len);
    BufferAddNTS(&cur, pass, &len);
    BufferAddNTS(&cur, user, &len);
    BufferAddInt(&cur, ((flags >> 24) & 0xff) | ((flags >> 8) & 0xff00) | ((flags << 8) & 0xff0000) | ((flags << 24) & 0xff000000), &len);
    if (ctx->queryoptions & 8) {
        BufferAddInt(&cur, ctx->srcip, &len);
    }
    if (ctx->queryoptions & 0x80) {
        BufferAddInt(&cur, extra, &len);
    }
    {
        u16 l = (u16)*(volatile s32 *)&len;
        tmp = (u16)(((l >> 8) & 0xff) | ((l << 8) & 0xff00));
    }
    u8 *da;
    da = buf;
    sp = (u8 *)&tmp;
    da[0] = sp[0];
    da[1] = sp[1];
    if (send(ctx->slsocket, da, len, 0) <= 0) {
        SBServerListDisconnect(ctx);
        return 3;
    }
    ctx->state = 3;
    ctx->pstate = 0;
    if (ctx->inbuffer == 0) {
        ctx->inbuffer = (u8 *)GsUtil_Alloc(0x1000);
        if (ctx->inbuffer == 0) {
            return 5;
        }
        ctx->inbufferlen = 0;
    }
    r = 0;
end:
    return r;
}
}
}

namespace F0228a20c {
extern "C" {
void FreePopularValues(SBServerList *ctx)
{
    s32 i = 0;
    s32 *pn = &ctx->numpopularvalues;
    char **p;

    if (*pn > 0) {
        p = ctx->popularvalues;
        do {
            SBReleaseStr(ctx, *p);
            p++;
            i++;
        } while (i < *pn);
    }
    ctx->numpopularvalues = 0;
}
}
}

namespace F0228a20c {
extern "C" {
void FreeKeyList(SBServerList *ctx)
{
    s32 i;
    KeyInfo *rec;

    if (ctx->keylist != 0) {
        i = 0;
        if (ArrayLength(ctx->keylist) > 0) {
            do {
                rec = (KeyInfo *)ArrayNth(ctx->keylist, i);
                SBReleaseStr(ctx, rec->keyName);
                i++;
            } while (i < ArrayLength(ctx->keylist));
        }
        ArrayFree(ctx->keylist);
        ctx->keylist = 0;
    }
}
}
}

namespace F0228a20c {
extern "C" {
void SBServerListDisconnect(SBServerList *ctx)
{
    if (ctx->inbuffer != 0) {
        GsUtil_Free(ctx->inbuffer);
    }
    ctx->inbuffer = 0;
    ctx->inbufferlen = 0;
    if (ctx->slsocket != -1) {
        closesocket(ctx->slsocket);
    }
    ctx->slsocket = -1;
    ctx->state = 1;
    FreeKeyList(ctx);
    ctx->expectedelements = -1;
    FreePopularValues(ctx);
}
}
}

namespace F0228a20c {
extern "C" {
void SBServerListCleanup(SBServerList *ctx)
{
    SBServerListDisconnect(ctx);
    SBServerListClear(ctx);
    SBRefStrHashCleanup();
    if (ctx->servers != 0) {
        ArrayFree((DArrayImplementation *)ctx->servers);
    }
    ctx->servers = 0;
}
}
}

namespace F0228a20c {
extern "C" {
void InitCryptKey(SBServerList *ctx, const u8 *key, s32 n)
{
    s32 len;
    s8 *pw;
    s32 i;
    s32 j;

    len = STD_GetStringLength((const char *)ctx->queryfromkey);
    pw = (s8 *)ctx->queryfromkey;
    for (i = 0; i < n; i++) {
        s32 c = pw[DS_MOD(i, len)];
        j = (i * c) % 8;
        ctx->mychallenge[j] = (s8)(ctx->mychallenge[j] ^ (s8)(ctx->mychallenge[i % 8] ^ key[i]));
    }
    GOACryptInit(&ctx->cryptkey, ctx->mychallenge, 8);
}
}
}

namespace F0228a20c {
extern "C" {
s32 ServerSizeForFlags(u32 flags)
{
    s32 sz = 5;
    if (flags & 2) {
        sz += 4;
    }
    if (flags & 8) {
        sz += 4;
    }
    if (flags & 0x10) {
        sz += 2;
    }
    if (flags & 0x20) {
        sz += 2;
    }
    return sz;
}
}
}

namespace F0228a20c {
extern "C" {
s32 FullRulesPresent(u8 *buf, s32 n)
{
    s32 l;
    s32 z = 0;

    while (n > 0 && ((s8 *)buf)[z] != 0) {
        l = NTSLengthSB(buf, n);
        if (l < 0) {
            return 0;
        }
        buf += l;
        n -= l;
        l = NTSLengthSB(buf, n);
        if (l < 0) {
            return 0;
        }
        buf += l;
        n -= l;
    }
    if (n == 0) {
        return 0;
    }
    if (*(s8 *)buf == 0) {
        return 1;
    }
    return 0;
}
}
}

namespace F0228a20c {
extern "C" {
s32 AllKeysPresent(SBServerList *ctx, u8 *buf, s32 n)
{
    s32 cnt;
    s32 i;
    KeyInfo *rec;
    u32 c;
    s32 l;

    cnt = ArrayLength(ctx->keylist);
    i = 0;
    if (cnt > 0) {
        do {
            rec = (KeyInfo *)ArrayNth(ctx->keylist, i);
            switch (rec->keyType) {
            case 1:
                buf += 1;
                n -= 1;
                break;
            case 2:
                buf += 2;
                n -= 2;
                break;
            case 0:
                if (n < 1) {
                    return 0;
                }
                c = *buf;
                buf++;
                n--;
                if (c == 0xff) {
                    l = NTSLengthSB(buf, n);
                    if (l == -1) {
                        return 0;
                    }
                    buf += l;
                    n -= l;
                }
                break;
            default:
                return 0;
            }
            if (n < 0) {
                return 0;
            }
            i++;
        } while (i < cnt);
    }
    return 1;
}
}
}

namespace F0228a20c {
extern "C" {
void ParseServerIPPort(SBServerList *ctx, u8 *buf, s32 n, u32 *ip, u16 *volatile port)
{
    u32 f;
    u8 *p;

    if (n < 5) {
        goto end;
    }
    f = buf[0];
    p = buf + 1;
    ((u8 *)ip)[0] = buf[1];
    ((u8 *)ip)[1] = p[1];
    ((u8 *)ip)[2] = p[2];
    ((u8 *)ip)[3] = p[3];
    if (f & 0x10) {
        if (n - 5 < 2) {
            goto end;
        }
        u8 *d = (u8 *)port;
        p = buf + 5;
        d[0] = *(p - 5 + 5);
        d[1] = p[1];
        return;
    }
    *port = ctx->defaultport;
end:;
}
}
}

namespace F0228a20c {
extern "C" {
s32 ParseServer(SBServerList *ctx, _SBServer *ent, u8 *buf, s32 n, s32 flag)
{
    s32 cnt;
    s32 orig;
    u32 flags;
    s32 i;
    u16 tmp;
    u16 port;
    u32 ip;
    u8 *d;
    KeyInfo *rec;

    orig = n;
    flags = buf[0];
    SBServerSetFlags(ent, flags);
    buf += 5;
    n -= 5;
    if (flags & 0x10) {
        buf += 2;
        n -= 2;
    }
    if (flags & 2) {
        d = (u8 *)&ip;
        d[0] = buf[0];
        d[1] = buf[1];
        d[2] = buf[2];
        d[3] = buf[3];
        buf += 4;
        n -= 4;
    } else {
        ip = 0;
    }
    if (flags & 0x20) {
        d = (u8 *)&port;
        d[0] = buf[0];
        d[1] = buf[1];
        buf += 2;
        n -= 2;
    } else {
        port = ctx->defaultport;
    }
    SBServerSetPrivateAddr(ent, ip, port);
    if (flags & 8) {
        d = (u8 *)&ip;
        d[0] = buf[0];
        d[1] = buf[1];
        d[2] = buf[2];
        d[3] = buf[3];
        buf += 4;
        n -= 4;
        SBServerSetICMPIP(ent, ip);
    }
    if (flags & 0x40) {
        cnt = ArrayLength(ctx->keylist);
        i = 0;
        if (cnt > 0) {
            do {
                rec = (KeyInfo *)ArrayNth(ctx->keylist, i);
                switch (rec->keyType) {
                case 1:
                    SBServerAddIntKeyValue(ent, rec->keyName, *buf);
                    buf++;
                    n--;
                    break;
                case 2: {
                    u16 sw;
                    d = (u8 *)&tmp;
                    d[0] = buf[0];
                    d[1] = buf[1];
                    sw = (u16)(((tmp >> 8) & 0xff) | ((tmp << 8) & 0xff00));
                    SBServerAddIntKeyValue(ent, rec->keyName, sw);
                    buf += 2;
                    n -= 2;
                    break;
                }
                case 0: {
                    u32 c;
                    if (flag != 0) {
                        c = *buf;
                        buf++;
                        n--;
                    } else {
                        c = 0xff;
                    }
                    if (c == 0xff) {
                        s32 l;
                        SBServerAddKeyValue(ent, rec->keyName, (char *)buf);
                        l = STD_GetStringLength((const char *)buf) + 1;
                        buf += l;
                        n -= l;
                    } else {
                        SBServerAddKeyValue(ent, rec->keyName, ctx->popularvalues[c]);
                    }
                    break;
                }
                }
                i++;
            } while (i < cnt);
        }
        SBServerSetState(ent, (u8)(SBServerGetState(ent) | 1));
    }
    flags = flags & 0x80;
    if (flags) {
        goto test;
        while (1) {
            char *p;
            s32 l;
            p = (char *)buf;
            l = STD_GetStringLength((const char *)buf) + 1;
            buf += l;
            n -= l;
            SBServerAddKeyValue(ent, p, (char *)buf);
            l = STD_GetStringLength((const char *)buf) + 1;
            buf += l;
            n -= l;
        test:
            if (*(s8 *)buf == 0) {
                break;
            }
            if (n <= 0) {
                break;
            }
        }
        n--;
        SBServerSetState(ent, (u8)(SBServerGetState(ent) | 2));
    }
    return orig - n;
}
}
}

namespace F0228a20c {
extern "C" {
s32 IncomingListParseServer(SBServerList *ctx, u8 *buf, s32 n)
{
    s32 off;
    u32 flags;
    u32 ip;
    u16 port;
    _SBServer *ent;
    s32 r;

    if (n < 1) {
        return 0;
    }
    flags = buf[0];
    off = ServerSizeForFlags(flags);
    if (n < off) {
        return 0;
    }
    if (flags & 0x40) {
        if (AllKeysPresent(ctx, buf + off, n - off) == 0) {
            return 0;
        }
    }
    flags = flags & 0x80;
    if (flags) {
        if (FullRulesPresent(buf + off, n - off) == 0) {
            return 0;
        }
    }
    if (memcmp(buf + 1, (void *)"\377\377\377\377", 4) == 0) {
        return -1;
    }
    ParseServerIPPort(ctx, buf, n, &ip, &port);
    ent = SBAllocServer(ctx, ip, port);
    if (SBIsNullServer(ent) != 0) {
        return -2;
    }
    r = ParseServer(ctx, ent, buf, n, 1);
    SBServerListAppendServer(ctx, ent);
    return r;
}
}
}

namespace F0228a20c {
extern "C" {
void SBSetLastListErrorPtr(SBServerList *ctx, const char *v)
{
    ctx->lasterror = v;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessMainListData(SBServerList *c) {
    u8 *p = c->inbuffer;
    s32 n = c->inbufferlen;
    s32 a, b, l, r;
    u8 *dd;
    u8 *sp;
    KeyInfo e;
    switch (c->pstate) {
    case 0:
        if (n < 1) goto end;
        a = (p[0] ^ 0xec) + 2;
        if (n < a) goto end;
        l = p[a - 1] ^ 0xea;
        b = a + l;
        if (n < b) goto end;
        InitCryptKey(c, p + a, l);
        c->pstate = 1;
        p += b;
        n -= b;
        GOADecrypt(&c->cryptkey, p, n);
    case 1:
        if (n < 6) goto end;
        dd = (u8 *)&c->mypublicip;
        dd[0] = p[0];
        dd[1] = p[1];
        dd[2] = p[2];
        dd[3] = p[3];
        c->ListCallback(c, 6, SBNullServer, c->instance);
        dd = (u8 *)&c->defaultport;
        sp = p + 4;
        dd[0] = sp[0];
        sp++;
        dd[1] = sp[0];
        if (*(u16 *)dd == 0xffff) {
            if (NTSLengthSB(p + 6, n - 6) == -1) goto end;
            SBSetLastListErrorPtr(c, (const char *)(p + 6));
            c->ListCallback(c, 5, SBNullServer, c->instance);
            if (c->inbuffer == 0) goto end;
        }
        p += 6;
        n -= 6;
        if ((c->queryoptions & 2) != 0 || c->defaultport == 0xffff) {
            c->pstate = 5;
            c->state = 2;
            goto end;
        }
        c->pstate = 2;
        c->expectedelements = -1;
    case 2:
        if (c->expectedelements == -1) {
            if (n < 1) goto end;
            c->expectedelements = p[0];
            c->keylist = ArrayNew(sizeof(KeyInfo), c->expectedelements, 0);
            if (c->keylist == 0) return 5;
            p++;
            n--;
        }
        while (c->expectedelements > ArrayLength(c->keylist)) {
            if (n < 2) break;
            l = NTSLengthSB(p + 1, n - 1);
            if (l == -1) break;
            e.keyType = p[0];
            e.keyName = SBRefStr(c, (const char *)(p + 1));
            ArrayAppend(c->keylist, &e);
            l = l + 1;
            p += l;
            n -= l;
        }
        if (c->expectedelements > ArrayLength(c->keylist)) goto end;
        c->pstate = 3;
        c->expectedelements = -1;
    case 3:
        if (c->expectedelements == -1) {
            if (n < 1) goto end;
            c->expectedelements = p[0];
            c->numpopularvalues = 0;
            p++;
            n--;
        }
        while (c->expectedelements > c->numpopularvalues) {
            l = NTSLengthSB(p, n);
            if (l == -1) break;
            char *pv = SBRefStr(c, (const char *)p);
            c->popularvalues[c->numpopularvalues++] = pv;
            p += l;
            n -= l;
        }
        if (c->expectedelements > c->numpopularvalues) goto end;
        c->pstate = 4;
    case 4:
        if (n < 5) goto end;
        r = 0;
        do {
            l = IncomingListParseServer(c, p, n);
            if (l == -2) return 5;
            if (l == -1) {
                n -= 5;
                p += 5;
                c->pstate = 5;
                c->state = 2;
                c->ListCallback(c, 3, SBNullServer, c->instance);
                goto end;
            }
            p += l;
            n -= l;
            if (c->inbuffer == 0) l = 0;
        } while (l != 0);
        break;
    default:
        break;
    }
end:
    if (c->inbuffer == 0) {
        return 0;
    }
    if (n != 0) {
        memmove(c->inbuffer, p, n);
    }
    c->inbufferlen = n;
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessPushKeyList(SBServerList *c, u8 *p, s32 n) {
    s32 cnt;
    s32 i;
    s32 l;
    KeyInfo e;
    cnt = p[0];
    p++;
    n--;
    if (c->keylist != 0) {
        FreeKeyList(c);
    }
    c->keylist = ArrayNew(sizeof(KeyInfo), cnt, 0);
    if (c->keylist == 0) {
        return 5;
    }
    i = 0;
    if (cnt > 0) {
        do {
            if (n < 2) {
                return 4;
            }
            l = NTSLengthSB(p + 1, n - 1);
            if (l == -1) {
                return 4;
            }
            e.keyType = p[0];
            e.keyName = SBRefStr(c, (const char *)(p + 1));
            ArrayAppend(c->keylist, &e);
            l = l + 1;
            p += l;
            n -= l;
            i++;
        } while (i < cnt);
    }
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessPlayerSearch(SBServerList *c, u8 *p, s32 n) {
    s32 l;
    u32 flag;
    s32 i;
    s32 cnt;
    s32 l2;
    u8 *s1;
    u8 *dd;
    u8 *s;
    u16 y;
    u32 x;
    u32 z;
    if (n < 2) {
        return 4;
    }
    flag = p[0];
    cnt = p[1];
    p += 2;
    n -= 2;
    i = 0;
    if (cnt > 0) {
        do {
            s1 = p;
            l = NTSLengthSB(p, n);
            if (l == -1) {
                return 4;
            }
            p += l;
            n -= l;
            if (n < 11) {
                return 4;
            }
            dd = (u8 *)&x;
            dd[0] = p[0];
            dd[1] = p[1];
            dd[2] = p[2];
            dd[3] = p[3];
            dd = (u8 *)&y;
            s = p + 4;
            dd[0] = s[0];
            s++;
            dd[1] = s[0];
            dd = (u8 *)&z;
            s = p + 6;
            dd[0] = s[0];
            dd[1] = s[1];
            dd[2] = s[2];
            dd[3] = s[3];
            z = HTONL(z);
            p += 10;
            n -= 10;
            l2 = NTSLengthSB(p, n);
            if (l2 == -1) {
                return 4;
            }
            c->PlayerSearchCallback(c, s1, x, y, z, p, c->instance);
            p += l2;
            n -= l2;
            i++;
        } while (i < cnt);
    }
    if (flag != 0) {
        c->PlayerSearchCallback(c, 0, 0, 0, 0, 0, c->instance);
    }
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessMaploop(SBServerList *c, u8 *p, s32 n) {
    u16 b;
    u32 d;
    u32 a;
    u8 *ptrs[16];
    u8 *dd;
    u8 *s;
    s32 r;
    _SBServer *x;
    s32 cnt;
    s32 i;
    s32 l;
    if (n < 11) {
        return 4;
    }
    dd = (u8 *)&a;
    dd[0] = p[0];
    dd[1] = p[1];
    dd[2] = p[2];
    dd[3] = p[3];
    dd = (u8 *)&b;
    s = p + 4;
    dd[0] = s[0];
    s++;
    dd[1] = s[0];
    r = SBServerListFindServerByIP(c, a, b);
    if (r == -1) {
        return 0;
    }
    x = SBServerListNth(c, r);
    dd = (u8 *)&d;
    s = p + 6;
    dd[0] = s[0];
    s++;
    dd[1] = s[0];
    dd[2] = s[1];
    dd[3] = s[2];
    d = HTONL(d);
    cnt = p[10];
    p += 11;
    n -= 11;
    i = 0;
    while (i < cnt && i < 16) {
        if (n < 1) {
            break;
        }
        l = NTSLengthSB(p, n);
        if (l == -1) {
            return 4;
        }
        ptrs[i] = p;
        p += l;
        n -= l;
        i++;
    }
    if (c->MaploopCallback == 0) {
        return 0;
    }
    c->MaploopCallback(c, x, d, i, ptrs, c->instance);
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessDeleteServer(SBServerList *c, u8 *p, s32 n) {
    u32 a;
    u16 b;
    u8 *d;
    u8 *s;
    s32 r;
    if (n < 6) {
        return 4;
    }
    d = (u8 *)&a;
    d[0] = p[0];
    d[1] = p[1];
    d[2] = p[2];
    d[3] = p[3];
    d = (u8 *)&b;
    s = p + 4;
    d[0] = s[0];
    s++;
    d[1] = s[0];
    r = SBServerListFindServerByIP(c, a, b);
    if (r != -1) {
        SBServerListRemoveAt(c, r);
        return 0;
    }
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessPushServer(SBServerList *c, u8 *p, s32 n) {
    u32 a;
    u16 b;
    s32 r4;
    _SBServer *r6;
    if (n < 5) {
        return 4;
    }
    ParseServerIPPort(c, p, n, &a, &b);
    r4 = SBServerListFindServerByIP(c, a, b);
    if (r4 == -1) {
        r6 = SBAllocServer(c, a, b);
        if (SBIsNullServer(r6) != 0) {
            return 5;
        }
    } else {
        r6 = SBServerListNth(c, r4);
    }
    if (ParseServer(c, r6, p, n, 0) < 0) {
        return 4;
    }
    if (r4 == -1) {
        SBServerListAppendServer(c, r6);
    }
    c->ListCallback(c, 1, r6, c->instance);
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessAdHocData(SBServerList *c) {
    u8 *d;
    s32 r = 0;
    u16 ml;
    u8 *p;
    while (c->inbufferlen >= 3) {
        {
            d = (u8 *)&ml;
            Get16(d, c->inbuffer);
            ml = HTONS(ml);
            if (ml > 0x1000) {
                r = 4;
                break;
            }
            if (c->inbufferlen < ml) {
                return 0;
            }
            p = c->inbuffer;
            switch ((s8)p[2]) {
            case 0:
                break;
            case 1:
                r = ProcessPushKeyList(c, p + 3, ml - 3);
                break;
            case 2:
                r = ProcessPushServer(c, p + 3, ml - 3);
                break;
            case 3:
                if (send(c->slsocket, p, ml, 0) <= 0) {
                    return 3;
                }
                break;
            case 4:
                r = ProcessDeleteServer(c, p + 3, ml - 3);
                break;
            case 5:
                r = ProcessMaploop(c, p + 3, ml - 3);
                break;
            case 6:
                r = ProcessPlayerSearch(c, p + 3, ml - 3);
                break;
            }
            c->inbufferlen = c->inbufferlen - ml;
            if (c->inbufferlen != 0 && c->inbuffer != 0) {
                memmove(c->inbuffer, c->inbuffer + ml, c->inbufferlen);
            }
        }
        if (r != 0) break;
    }
    if (r != 0) {
        ErrorDisconnect(c);
    }
    return r;
}
}
}

namespace F02289808 {
extern "C" {
s32 ProcessIncomingData(SBServerList *c) {
    s32 old;
    s32 r;
    s32 res;
    if (CanReceiveOnSocket(c->slsocket) == 0) {
        return 0;
    }
    old = c->inbufferlen;
    r = recv(c->slsocket, c->inbuffer + old, 0x1000 - old, 0);
    if (r == 0 || r == -1) {
        ErrorDisconnect(c);
        return 3;
    }
    c->inbufferlen = c->inbufferlen + r;
    res = 0;
    if (c->state == 2 || c->pstate > 0) {
        GOADecrypt(&c->cryptkey, c->inbuffer + old, c->inbufferlen - old);
    }
    if (c->state == 3) {
        res = ProcessMainListData(c);
    }
    if (res != 0) {
        return res;
    }
    if (c->state == 2 && c->inbufferlen > 0) {
        return ProcessAdHocData(c);
    }
    return 0;
}
}
}

namespace F02289808 {
extern "C" {
s32 SBSendMessageToServer(SBServerList *c, u32 a1, u32 a2, u8 *data, s32 len) {
    struct {
        u16 t;
        u8 pkt[9];
        u8 pad[13];
    } l;
    u8 *d;
    u8 *sp;
    s32 r;
    if (c->state == 1) {
        SBServerListConnectAndQuery(c, 0, 0, 2, 0);
    }
    if (c->state == 1) {
        return 3;
    }
    l.t = HTONS((u16)(len + 9));
    d = l.pkt;
    sp = (u8 *)&l.t;
    d[0] = sp[0];
    d[1] = sp[1];
    l.pkt[2] = 2;
    d = &l.pkt[3];
    sp = (u8 *)&a1;
    d[0] = sp[0];
    d[1] = sp[1];
    d[2] = sp[2];
    d[3] = sp[3];
    d = &l.pkt[7];
    sp = (u8 *)&a2;
    d[0] = sp[0];
    d[1] = sp[1];
    r = SendWithRetry(c, l.pkt, 9);
    if (r == 0) {
        if (send(c->slsocket, data, len, 0) < 0) {
            return 3;
        }
        r = 0;
    }
    return r;
}
}
}

namespace F02289808 {
extern "C" {
s32 SBSendNatNegotiateCookieToServer(SBServerList *c, u32 a1, u32 a2, u32 ip) {
    u8 buf[10];
    u8 *d;
    u8 *s;
    buf[0] = 0xfd;
    buf[1] = 0xfc;
    buf[2] = 0x1e;
    buf[3] = 0x66;
    buf[4] = 0x6a;
    buf[5] = 0xb2;
    ip = HTONL(ip);
    d = &buf[6];
    s = (u8 *)&ip;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    return SBSendMessageToServer(c, a1, a2, buf, 10);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ProcessLanData(SBServerList *s) {
    SockAddrIn addr;
    s32 len;
    u8 buf[0x5dc];
    s32 r;
    _SBServer *e;
    len = 8;
    if (CanReceiveOnSocket(s->slsocket) != 0) {
        do {
            r = recvfrom(s->slsocket, buf, 0x5db, 0, &addr, &len);
            if (r != -1) {
                r = SBServerListFindServerByIP(s, addr.addr, addr.port);
                if (r == -1) {
                    e = SBAllocServer(s, addr.addr, addr.port);
                    if (SBIsNullServer(e) != 0) {
                        return 5;
                    }
                    SBServerSetFlags(e, 0x11);
                    SBServerListAppendServer(s, e);
                }
            }
        } while (CanReceiveOnSocket(s->slsocket) != 0);
    }
    if (current_time() - s->lanstarttime > 2000) {
        closesocket(s->slsocket);
        s->slsocket = -1;
        s->state = 1;
        s->ListCallback(s, 3, SBNullServer, s->instance);
    }
    return 0;
}
}
}

namespace F02288e2c {
extern "C" {
s32 SBListThink(SBServerList *sub) {
    SBFreeDeadList(sub);
    switch (sub->state) {
    case 2:
    case 3:
        return ProcessIncomingData(sub);
    case 0:
        return ProcessLanData((SBServerList *)sub);
    case 1:
        break;
    }
    return 0;
}
}
}

namespace F02288e2c {
extern "C" {
void ListCallback(SBServerList *s, s32 code, _SBServer *p, _ServerBrowser *o) {
    switch (code) {
    case 0:
        o->BrowserCallback(o, 0, p, o->instance);
        if ((p->state & 3) != 0) {
            if ((p->state & 0x40) != 0) {
                break;
            }
        }
        if ((p->state & 0x2c) != 0) {
            break;
        }
        if (o->dontUpdate != 0) {
            break;
        }
        {
            s32 m;
            if ((p->flags & 1) != 0) {
                if (o->list.state == 0 || o->engine.numserverkeys == 0) {
                    m = 1;
                } else {
                    m = 0;
                }
            } else {
                m = 2;
            }
            SBQueryEngineUpdateServer(o, p, 0, m);
        }
        break;
    case 1:
        if ((p->state & 0x43) == 0) {
            o->BrowserCallback(o, 2, p, o->instance);
        } else {
            o->BrowserCallback(o, 1, p, o->instance);
        }
        break;
    case 2:
        if ((p->state & 0x2c) != 0) {
            SBQueryEngineRemoveServerFromFIFOs(o, p);
        }
        o->BrowserCallback(o, 3, p, o->instance);
        break;
    case 3:
        if (o->disconnectFlag != 0) {
            SBServerListDisconnect(s);
        }
        if (ArrayLength(s->servers) == 0 || o->engine.querylist.count == 0) {
            o->BrowserCallback(o, 4, NULL, o->instance);
        }
        break;
    case 4:
        break;
    case 5:
        o->BrowserCallback(o, 5, NULL, o->instance);
        break;
    case 6:
        SBQueryEngineSetPublicIP(o, o->list.mypublicip);
        break;
    }
    if (p != NULL) {
        if (p->publicip == o->triggerIP && p->publicport == o->triggerPort) {
            o->triggerIP = 0;
        }
    }
}
}
}

namespace F02288e2c {
extern "C" {
void EngineCallback(void *a, s32 code, _SBServer *p, _ServerBrowser *o) {
    switch (code) {
    case 1:
        o->BrowserCallback(o, 2, p, o->instance);
        break;
    case 0:
        o->BrowserCallback(o, 1, p, o->instance);
        break;
    case 2:
        o->BrowserCallback(o, 4, p, o->instance);
        break;
    }
    if (p != NULL) {
        if (p->publicip == o->triggerIP && p->publicport == o->triggerPort) {
            o->triggerIP = 0;
        }
    }
}
}
}

namespace F02288e2c {
extern "C" {
_ServerBrowser *ServerBrowserNewA(char *a, char *b, char *c, s32 d, s32 s5, s32 s6, s32 s7, void *s8, void *s9) {
    _ServerBrowser *o;
    if (s7 == 0 && __GSIACResult != 1) {
        return NULL;
    }
    o = (_ServerBrowser *)GsUtil_Alloc(sizeof(_ServerBrowser));
    if (o == NULL) {
        return NULL;
    }
    o->BrowserCallback = (void (*)(_ServerBrowser *, s32, void *, void *))s8;
    o->instance = s9;
    o->dontUpdate = 0;
    SBServerListInit(&o->list, a, b, c, d, s7, (void *)ListCallback, o);
    SBQueryEngineInit(o, s5, s6, s7, (void *)EngineCallback, o);
    return o;
}
}
}

namespace F02288e2c {
extern "C" {
void ServerBrowserFree(_ServerBrowser *o) {
    SBServerListCleanup(&o->list);
    SBEngineCleanup(o);
    GsUtil_Free(o);
}
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02289444) {
    HOST_OVERLAY_VAR(data_ov065_0228e954),
    HOST_OVERLAY_VAR(SBOverrideMasterServer),
    HOST_OVERLAY_VAR(g_sortserverlist),
    HOST_OVERLAY_VAR(SBNullServer),
    HOST_OVERLAY_VARS_END
};
