#include "ds_div.h"
#include "uptr.h"
#include "types.h"
#include "net/sb_crypt.h"
#include "net/SockAddrIn.h"
#include "net/sb_internal.h"
#include "net/hashtable.h"
#include "net/gsPlatformUtil.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/autoload_2/unk_0212fa54.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02288c78.h"
#include "proto/ov065/unk_ov065_022789fc.h"
extern "C" s32 NTSLengthSB(const u8 *s, s32 n);

extern "C" {
char *data_ov065_0228e928[2] = {"queryid", "final"};
HashImplementation *g_SBRefStrList;
char *thestr;
}

namespace F022884fc {










extern "C" {
extern u8 data_ov065_0228e8fc[];
extern GsSrvQueryBasicInfoStr data_ov065_0228e904;
extern GsSrvQueryStatusStr data_ov065_0228e914;
extern _SBServer *SBNullServer;
extern u8 data_0213a410[];

u32 func_0213335c(u32 a, u32 b);
void SocketStartUp(void);
s32 CanReceiveOnSocket(s32 s);
s32 closesocket(s32 s);
s32 socket(s32 a, s32 b, s32 c);
HashImplementation *TableNew2(s32 a, s32 b, s32 c, void *cmp, void *hash, void *free);
void SBReleaseStr(SBServerList *a, const char *p);
}

typedef GOACryptState Cipher;
typedef SBQueryEngine Mgr;
typedef _SBServer Ent;
typedef SBServerFIFO List;
typedef SockAddrIn Sa;

extern "C" {
u32 GOADecryptByte(Cipher *c, u32 x);
void GOAHashInit(Cipher *c);
u32 keyrand(Cipher *c, u32 n, u8 *key, u32 keylen, u8 *j, u32 *idx);
s32 FIFORemove(List *l, Ent *e);
void ProcessIncomingReplies(Mgr *m, s32 flag);
void TimeoutOldQueries(Mgr *m);
void QueueNextQueries(Mgr *m);
void QEStartQuery(Mgr *m, Ent *e);
s32 ParseSingleICMPReply(Mgr *m, Ent *e, u8 *buf, s32 n);
void ParseSingleGOAReply(Mgr *m, Ent *e, u8 *buf, s32 n);
void ParseSingleQR2Reply(Mgr *m, Ent *e, u8 *buf, s32 n);
void FIFOClear(List *l);
Ent *FIFOGetFirst(List *l);
void FIFOAddFront(List *l, Ent *e);
void FIFOAddRear(List *l, Ent *e);
s32 KeyValCompareKey(SBKeyValuePair *a, SBKeyValuePair *b);
u32 KeyValHashKey(SBKeyValuePair *p, u32 n);
void KeyValFree(SBKeyValuePair *p);

}
}

namespace F02288e2c {














static inline u16 Unk_ov065_02289044_Htons(u16 x) {
    return (x >> 8 & 0xff) | ((x << 8) & 0xff00);
}

extern "C" {
extern char *thestr;
extern HashImplementation *g_SBRefStrList;
extern char *data_ov065_0228e928[2];
extern char *qr2_registered_key_list[];
extern u16 data_0213a510[];
extern _SBServer *SBNullServer;

s32 OS_SPrintf(char *, const char *, ...);

s32 ArrayLength(void *);
void *TableLookup(void *, void *);
s32 TableEnter(void *, void *);
s32 TableCount(void *);
s32 TableFree(void *);
HashImplementation *TableNew2(s32, s32, s32, void *, void *, void *);
s32 closesocket(s32);
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
void SBServerSetFlags(_SBServer *, u32);
_SBServer *SBAllocServer(SBServerList *, u32, u32);
u32 SBServerGetPing(_SBServer *);
s32 SBServerListCleanup(void *);
s32 SBServerListDisconnect(void *);
s32 SBServerListInit(void *, s32, s32, s32, s32, s32, void *, void *);
char *SBRefStr(SBServerList *, const char *);
s32 SBServerListClear(void *);
s32 SBFreeDeadList(void *);
_SBServer *SBServerListNth(void *, s32);
s32 SBServerListCount(void *);
s32 SBServerListRemoveAt(void *, s32);
s32 SBServerListFindServerByIP(void *, u32, u32);
s32 SBServerListFindServer(void *c, _SBServer *key);
void SBServerListAppendServer(void *, _SBServer *);
void SBServerListSort(void *c, s32 a, char *b, u32 mode);
s32 ProcessIncomingData(void *);

char *mytok(char *s, s32 ch);
s32 CheckValidKey(char *s);
char *SBServerGetStringValueA(void *a, char *k, char *d);
s32 ServerBrowserHalt(void *o);
s32 ServerBrowserThink(void *o);
s32 ServerBrowserBeginUpdate2(_ServerBrowser *o, s32 a, s32 b, u8 *data, s32 n, const char *c, s32 d, s32 e);
s32 inet_addr(const char *a);
s32 SBServerListConnectAndQuery(SBServerList *ctx, const char *user, const char *pass, u32 flags, u32 extra);
s32 SBSendMessageToServer(SBServerList *c, u32 a1, u32 a2, u8 *data, s32 len);
s32 SBSendNatNegotiateCookieToServer(SBServerList *c, u32 a1, u32 a2, u32 ip);
void EngineCallback(void *, s32, _SBServer *, _ServerBrowser *);
void ListCallback(SBServerList *, s32, _SBServer *, _ServerBrowser *);
s32 SBListThink(void *);
s32 ProcessLanData(SBServerList *);
s32 RefStringCompare(char **, char **);
void RefStringFree(void **);
s32 RefStringHash(SBRefString *, s32);

}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserBeginUpdate2(_ServerBrowser *o, s32 a, s32 b, u8 *data, s32 n, const char *c, s32 d, s32 e) {
    char buf[0x100] = {0};
    s32 i;
    s32 j;
    s32 r;
    s32 t;
    i = 0;
    o->disconnectFlag = b;
    o->engine.numserverkeys = 0;
    j = 0;
    if (n > 0) {
        do {
            u8 *pj = data + j;
            if (i + (s32)STD_GetStringLength(qr2_registered_key_list[*pj]) + 1 >= 0x100) {
                break;
            }
            i += OS_SPrintf(buf + i, "\\%s", qr2_registered_key_list[*pj]);
            SBQueryEngineAddQueryKey(o, *pj);
            j++;
        } while (j < n);
    }
    r = SBServerListConnectAndQuery(&o->list, buf, c, d, e);
    if (r == 0 && a == 0) {
        t = 10;
        while (o->list.state == 3 || (o->engine.querylist.count > 0 && r == 0)) {
            msleep(t);
            r = ServerBrowserThink(o);
        }
    }
    return r;
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserLimitUpdateA(_ServerBrowser *o, s32 a, s32 b, u8 *c, s32 e, const char *f, s32 g) {
    return ServerBrowserBeginUpdate2(o, a, b, c, e, f, 0x80, g);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserSendMessageToServerA(_ServerBrowser *o, const char *a, u16 b, u8 *c, s32 e) {
    s32 x = inet_addr(a);
    return SBSendMessageToServer(&o->list, x, Unk_ov065_02289044_Htons(b), c, e);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserSendNatNegotiateCookieToServerA(_ServerBrowser *o, const char *a, u16 b, s32 c) {
    s32 x = inet_addr(a);
    return SBSendNatNegotiateCookieToServer(&o->list, x, Unk_ov065_02289044_Htons(b), c);
}
}
}

namespace F02288e2c {
extern "C" {
void ServerBrowserRemoveServer(_ServerBrowser *o, _SBServer *key) {
    s32 r = SBServerListFindServer(&o->list, key);
    if (r != -1) {
        SBServerListRemoveAt(&o->list, r);
    }
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserThink(void *o) {
    SBQueryEngineThink(o);
    return SBListThink(&((_ServerBrowser *)o)->list);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserHalt(void *o) {
    SBServerListDisconnect(&((_ServerBrowser *)o)->list);
    return SBEngineHaltUpdates(o);
}
}
}

namespace F02288e2c {
extern "C" {
void ServerBrowserClear(_ServerBrowser *o) {
    ServerBrowserHalt(o);
    SBServerListClear(&o->list);
}
}
}

namespace F02288e2c {
extern "C" {
_SBServer *ServerBrowserGetServer(_ServerBrowser *o, s32 index) {
    return SBServerListNth(&o->list, index);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserCount(_ServerBrowser *o) {
    return SBServerListCount(&o->list);
}
}
}

namespace F02288e2c {
extern "C" {
void ServerBrowserSortA(_ServerBrowser *o, s32 a, char *b, u32 mode) {
    GsSrvSortStackPad pad;
    SBServerListSort(&o->list, a, b, mode);
}
}
}

namespace F02288e2c {
extern "C" {
s32 ServerBrowserGetMyPublicIPAddr(_ServerBrowser *o) {
    return o->list.mypublicip;
}
}
}

namespace F02288e2c {
extern "C" {
s32 RefStringHash(SBRefString *p, s32 numBuckets) {
    return StringHash(p->str, numBuckets);
}
}
}

namespace F02288e2c {
extern "C" {
s32 RefStringCompare(char **a, char **b) {
    return func_02130b04(*a, *b);
}
}
}

namespace F02288e2c {
extern "C" {
void RefStringFree(void **p) {
    GsUtil_Free(*p);
}
}
}

namespace F02288e2c {
extern "C" {
HashImplementation *SBRefStrHash() {
    if (g_SBRefStrList == NULL) {
        g_SBRefStrList = TableNew2(sizeof(SBRefString), 100, 2, (void *)RefStringHash, (void *)RefStringCompare, (void *)RefStringFree);
    }
    return g_SBRefStrList;
}
}
}

namespace F02288e2c {
extern "C" {
void SBRefStrHashCleanup() {
    if (g_SBRefStrList != NULL) {
        if (TableCount(g_SBRefStrList) == 0) {
            TableFree(g_SBRefStrList);
            g_SBRefStrList = NULL;
        }
    }
}
}
}

namespace F02288e2c {
extern "C" {
void SBServerFree(_SBServer **pp) {
    _SBServer *q = *pp;
    TableFree(q->keyvals);
    q->keyvals = NULL;
    GsUtil_Free(q);
}
}
}

namespace F02288e2c {
extern "C" {
s32 SBServerAddKeyValue(_SBServer *a, char *k, char *v) {
    SBKeyValuePair kv;
    kv.key = SBRefStr(0, k);
    kv.value = SBRefStr(0, v);
    return TableEnter(a->keyvals, &kv);
}
}
}

namespace F02288e2c {
extern "C" {
void SBServerAddIntKeyValue(_SBServer *a, char *b, s32 v) {
    char buf[0x14];
    OS_SPrintf(buf, "%d", v);
    SBServerAddKeyValue(a, b, buf);
}
}
}

namespace F02288e2c {
extern "C" {
char *SBServerGetStringValueA(void *a, char *k, char *d) {
    SBKeyValuePair *e;
    SBKeyValuePair key;
    if (a == NULL) {
        return 0;
    }
    key.key = k;
    e = (SBKeyValuePair *)TableLookup(((_SBServer *)a)->keyvals, &key);
    if (e != NULL) {
        d = e->value;
    }
    return d;
}
}
}

namespace F02288e2c {
extern "C" {
s32 SBServerGetIntValueA(_SBServer *a, char *b, s32 c) {
    char *v;
    s32 t;
    if (strcmp(b, "ping") == 0) {
        return SBServerGetPing(a);
    }
    v = (char *)SBServerGetStringValueA(a, b, 0);
    if (v != NULL) {
        s32 ch = *(u8 *)v;
        if (ch < 0 || ch >= 0x80) {
            t = 0;
        } else {
            t = data_0213a510[ch] & 8;
        }
        if (t != 0) {
            goto call;
        }
    }
    return c;
call:
    return atol(v);
}
}
}

namespace F02288e2c {
extern "C" {
double SBServerGetFloatValueA(_SBServer *a, char *b, double v) {
    SBServerGetStringValueA(a, b, 0);
    return v;
}
}
}

namespace F02288e2c {
extern "C" {
u32 SBServerGetPublicInetAddress(_SBServer *o) {
    return o->publicip;
}
}
}

namespace F02288e2c {
extern "C" {
u16 SBServerGetPublicQueryPort(_SBServer *o) {
    return Unk_ov065_02289044_Htons(o->publicport);
}
}
}

namespace F02288e2c {
extern "C" {
u16 SBServerGetPublicQueryPortNBO(_SBServer *o) {
    return o->publicport;
}
}
}

namespace F02288e2c {
extern "C" {
BOOL SBServerHasPrivateAddress(_SBServer *o) {
    if ((o->flags & 2) == 2) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace F02288e2c {
extern "C" {
u32 SBServerGetPrivateInetAddress(_SBServer *o) {
    return o->privateip;
}
}
}

namespace F02288e2c {
extern "C" {
u16 SBServerGetPrivateQueryPort(_SBServer *o) {
    return Unk_ov065_02289044_Htons(o->privateport);
}
}
}

namespace F02288e2c {
extern "C" {
void SBServerSetNext(_SBServer *o, _SBServer *v) {
    o->next = v;
}
}
}

namespace F02288e2c {
extern "C" {
_SBServer *SBServerGetNext(_SBServer *o) {
    return o->next;
}
}
}

namespace F02288e2c {
extern "C" {
s32 CheckValidKey(char *s) {
    GsServerIgnoredKeys l = *(GsServerIgnoredKeys *)data_ov065_0228e928;
    u32 i;
    char **p = l.v;
    for (i = 0; i < 2; i++) {
        if (strcmp(s, *p) == 0) {
            return 0;
        }
        p++;
    }
    return 1;
}
}
}

namespace F02288e2c {
extern "C" {
char *mytok(char *s, s32 ch) {
    char *start;
    char *p;
    s8 c;
    if (s != NULL) {
        thestr = s;
    }
    start = thestr;
    goto test;
loop:
    thestr++;
test:
    p = thestr;
    c = *p;
    if (c == 0) {
        goto out;
    }
    if (c != ch) {
        goto loop;
    }
out:
    if (p == start) {
        start = NULL;
    }
    if (c != 0) {
        thestr++;
        *p = 0;
    }
    return start;
}
}
}

namespace F02288e2c {
extern "C" {
void SBServerParseKeyVals(_SBServer *c, char *s) {
    char *k;
    char *v;
    k = mytok(s + 1, 0x5c);
    if (k != NULL) {
        do {
            v = mytok(NULL, 0x5c);
            if (v == NULL) {
                v = "";
            }
            if (CheckValidKey(k) != 0) {
                SBServerAddKeyValue(c, k, v);
            }
            k = mytok(NULL, 0x5c);
        } while (k != NULL);
    }
}
}
}

namespace F02288e2c {
extern "C" {
void SBServerParseQR2FullKeysSingle(_SBServer *c, char *p, s32 len) {
    s32 r;
    char *q;
    char *name;
    char *val;
    char *s;
    u16 cnt;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    char buf[0x80];
    while (*p != 0) {
        r = NTSLengthSB((const u8 *)p, len);
        if (r < 0) {
            return;
        }
        name = p;
        p += r;
        len -= r;
        r = NTSLengthSB((const u8 *)p, len);
        if (r < 0) {
            return;
        }
        val = p;
        p += r;
        len -= r;
        SBServerAddKeyValue(c, name, val);
    }
    p++;
    len--;
    for (i = 0; i < 2; i++) {
        if (len < 2) {
            return;
        }
        {
            u8 *b = (u8 *)&cnt;
            b[0] = ((u8 *)p)[0];
            b[1] = ((u8 *)p)[1];
        }
        cnt = Unk_ov065_02289044_Htons(cnt);
        p += 2;
        len -= 2;
        q = p;
        n = 0;
        while (*p != 0) {
            r = NTSLengthSB((const u8 *)p, len);
            if (r < 0 || r > 100) {
                return;
            }
            n++;
            p += r;
            len -= r;
        }
        p++;
        len--;
        for (j = 0; j < cnt; j++) {
            s = q;
            for (k = 0; k < n; k++) {
                r = NTSLengthSB((const u8 *)p, len);
                if (r < 0) {
                    return;
                }
                OS_SPrintf(buf, "%s%d", s, j);
                SBServerAddKeyValue(c, buf, p);
                p += r;
                len -= r;
                s += STD_GetStringLength(s) + 1;
            }
        }
    }
}
}
}

namespace F022884fc {
extern "C" {
u32 StringHash(const char *s, u32 n) {
    s32 c;
    u32 h = 0;
    c = *s;
    if (c != 0) {
        do {
            if (c >= 0 && c < 0x80) {
                c = data_0213a410[c];
            }
            h = h * 0x9ccf9319;
            h += c;
            s++;
            c = *s;
        } while (c != 0);
    }
    return DS_UMOD(h, n);
}
}
}

namespace F022884fc {
extern "C" {
void KeyValFree(SBKeyValuePair *p) {
    SBReleaseStr(0, p->key);
    SBReleaseStr(0, p->value);
}
}
}

namespace F022884fc {
extern "C" {
u32 KeyValHashKey(SBKeyValuePair *p, u32 n) {
    return StringHash(p->key, n);
}
}
}

namespace F022884fc {
extern "C" {
s32 KeyValCompareKey(SBKeyValuePair *a, SBKeyValuePair *b) {
    return func_02130b04(a->key, b->key);
}
}
}

namespace F022884fc {
extern "C" {
u32 SBServerGetPing(Ent *e) {
    return e->updatetime;
}
}
}

namespace F022884fc {
extern "C" {
Ent *SBAllocServer(SBServerList *unused, u32 addr, u32 port) {
    Ent *e = (Ent *)GsUtil_Alloc(sizeof(Ent));
    if (e == 0) {
        return 0;
    }
    e->keyvals = TableNew2(sizeof(SBKeyValuePair), 8, 4, (void *)KeyValHashKey, (void *)KeyValCompareKey, (void *)KeyValFree);
    if (e->keyvals == 0) {
        GsUtil_Free(e);
        return 0;
    }
    e->state = 0;
    e->flags = 0;
    e->next = 0;
    e->updatetime = 0;
    e->icmpip = 0;
    e->publicip = addr;
    e->publicport = port;
    e->privateip = 0;
    e->privateport = 0;
    return e;
}
}
}

namespace F022884fc {
extern "C" {
void SBServerSetFlags(Ent *e, u32 v) {
    e->flags = v;
}
}
}

namespace F022884fc {
extern "C" {
void SBServerSetPrivateAddr(Ent *e, u32 addr, u32 port) {
    e->privateip = addr;
    e->privateport = port;
}
}
}

namespace F022884fc {
extern "C" {
void SBServerSetICMPIP(Ent *e, s32 v) {
    e->icmpip = v;
}
}
}

namespace F022884fc {
extern "C" {
void SBServerSetState(Ent *e, u32 v) {
    e->state = v;
}
}
}

namespace F022884fc {
extern "C" {
u32 SBServerGetState(Ent *e) {
    return e->state;
}
}
}

namespace F022884fc {
extern "C" {
BOOL SBIsNullServer(_SBServer *v) {
    if (v == SBNullServer) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace F022884fc {
extern "C" {
void FIFOAddRear(List *l, Ent *e) {
    if (l->last != 0) {
        l->last->next = e;
    }
    l->last = e;
    e->next = 0;
    if (l->first == 0) {
        l->first = e;
    }
    l->count = l->count + 1;
}
}
}

namespace F022884fc {
extern "C" {
void FIFOAddFront(List *l, Ent *e) {
    e->next = l->first;
    l->first = e;
    if (l->last == 0) {
        l->last = e;
    }
    l->count = l->count + 1;
}
}
}

namespace F022884fc {
extern "C" {
Ent *FIFOGetFirst(List *l) {
    Ent *e = l->first;
    if (e != 0) {
        l->first = e->next;
        if (l->first == 0) {
            l->last = 0;
        }
        l->count = l->count - 1;
    }
    return e;
}
}
}

namespace F022884fc {
extern "C" {
s32 FIFORemove(List *l, Ent *e) {
    Ent *cur;
    Ent *prev;
    prev = 0;
    cur = l->first;
    if (cur != 0) {
        do {
            if (cur == e) {
                if (prev != 0) {
                    prev->next = cur->next;
                }
                if (l->first == cur) {
                    l->first = cur->next;
                }
                if (l->last == cur) {
                    l->last = prev;
                }
                l->count = l->count - 1;
                return 1;
            }
            prev = cur;
            cur = cur->next;
        } while (cur != 0);
    }
    return 0;
}
}
}

namespace F022884fc {
extern "C" {
void FIFOClear(List *l) {
    l->last = 0;
    l->first = l->last;
    l->count = 0;
}
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02288c78) {
    HOST_OVERLAY_VAR(data_ov065_0228e928),
    HOST_OVERLAY_VAR(g_SBRefStrList),
    HOST_OVERLAY_VAR(thestr),
    HOST_OVERLAY_VARS_END
};
