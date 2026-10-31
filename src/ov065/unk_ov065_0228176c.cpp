#include "types.h"
#include "net/darray.h"
#include "net/gpiPeer.h"
#include "net/gpiProfile.h"
#include "net/gpiOperation.h"
#include "net/gpiSearch.h"
#include "net/gpi.h"
#include "net/gp.h"
#include "net/gsPlatformUtil.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_0228176c.h"
#include "proto/ov065/unk_ov065_02283720.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_022789fc.h"
#include "proto/ov065/unk_ov065_0227cd34.h"
#include "proto/ov065/unk_ov065_0227d96c.h"
#include "proto/ov065/unk_ov065_0227df0c.h"
#include "proto/ov065/unk_ov065_0227e160.h"
#include "proto/ov065/unk_ov065_0227f2a4.h"
#include "proto/ov065/unk_ov065_02280740.h"
#include "proto/ov065/unk_ov065_02280c08.h"
#include "proto/ov065/unk_ov065_02281a5c.h"
#include "proto/ov065/unk_ov065_02283304.h"


namespace Na {

extern char data_ov065_0228d928[];
extern char data_ov065_0228d9c8[];
extern char data_ov065_0228d9ec[];
extern char data_ov065_0228d9f0[];
extern char data_ov065_0228da00[];
extern char data_ov065_0228da04[];
extern char data_ov065_0228da0c[];
extern char data_ov065_0228da14[];
extern char data_ov065_0228da1c[];
extern char data_ov065_0228da24[];
extern char data_ov065_0228da2c[];
extern char data_ov065_0228da34[];
extern char data_ov065_0228da3c[];
extern char data_ov065_0228da44[];
extern char data_ov065_0228da68[];

extern "C" {

s32 strncmp(const char *, const char *, s32);
s32 OS_SPrintf(char *, const char *, ...);

















}
extern "C" {
}
}

namespace Nb {


extern "C" {

extern char data_ov065_0228db1c[];

typedef s32 (*gpiProfileMapFunc)(GPConnection *, GPIProfile *, void *);

s32 strncmp(const char *, const char *, s32);

s32 gpiProfileMap(GPConnection *, gpiProfileMapFunc, void *);




struct GPIProfileMapData {
    GPConnection *connection;
    gpiProfileMapFunc func;
    void *data;
};



struct GPIFindProfileByUserData {
    char *nick;
    char *email;
    GPIProfile **profile;
    s32 found;
};






static inline void Unk_ov065_022818f4_Zero(GPIProfile *e) {
    e->profileId = 0;
    e->userId = 0;
    e->buddyStatus = 0;
    e->cache = 0;
    e->authSig = 0;
    e->requestCount = 0;
    e->peerSig = 0;
}









extern char data_ov065_0228db30[];
extern char data_ov065_0228db5c[];
extern char data_ov065_0228db68[];
extern char data_ov065_0228db74[];
extern char data_ov065_0228db80[];
extern char data_ov065_0228db90[];
extern char data_ov065_0228db98[];
extern char data_ov065_0228dba8[];
extern char data_ov065_0228dbb0[];
extern char data_ov065_0228dbbc[];
extern char data_ov065_0228dbc8[];
extern char data_ov065_0228dbd4[];
extern char data_ov065_0228dbdc[];
extern char data_ov065_0228dbe4[];
extern char data_ov065_0228dbec[];
extern char data_ov065_0228dbf4[];
extern char data_ov065_0228dc00[];
extern char data_ov065_0228dc0c[];
extern char data_ov065_0228dc14[];
extern char data_ov065_0228dc20[];
extern char data_ov065_0228dc2c[];
extern char data_ov065_0228dc34[];
extern char data_ov065_0228dc40[];
extern char data_ov065_0228dc50[];
extern char data_ov065_0228dc60[];
extern char data_ov065_0228dc6c[];
extern char data_ov065_0228dc74[];
extern char data_ov065_0228dca0[];
extern char data_ov065_0228dca8[];
extern char data_ov065_0228dcb0[];
extern char data_ov065_0228dcb4[];
extern char data_ov065_0228dcb8[];
extern char data_ov065_0228dcc0[];
extern char data_ov065_0228dccc[];
extern char data_ov065_0228dcd8[];
extern char data_ov065_0228dce4[];
extern char data_ov065_0228dcec[];
extern char data_ov065_0228dd14[];
extern char data_ov065_0228dd18[];
extern char data_ov065_0228dd1c[];
extern char data_ov065_0228dd24[];
extern char data_ov065_0228dd2c[];
extern char data_ov065_0228dd30[];
extern char data_ov065_0228dd38[];
extern char data_ov065_0228dd44[];
extern char data_ov065_0228dd48[];
extern char data_ov065_0228dd50[];
extern char data_ov065_0228dd54[];
extern char data_ov065_0228dd5c[];
extern char data_ov065_0228dd64[];
extern char data_ov065_0228dd68[];
extern char data_ov065_0228dd70[];
extern char data_ov065_0228dd78[];
extern char data_ov065_0228dd7c[];
extern char data_ov065_0228db2c[];
extern char data_ov065_0228db1c[];











#define ERR3() { gpiSetError(h, 1, data_ov065_0228dcec); gpiCallErrorCallback(h, 3, 1); return 3; }
#define ERRMEM(m) { gpiSetErrorString(h, m); return 1; }
#define GETTOK(t) r = gpiReadKeyAndValue(h, c->inputBuffer, &pos, t, buf); if (r != 0) { return r; }


}
extern "C" {
s32 gpiProfileMap(GPConnection *h, gpiProfileMapFunc cb, void *arg);
}
}

namespace Nb {
extern "C" {
s32 gpiProcessNewProfile(GPConnection *h, GPIOperation *n, char *s) {
    char buf[0x10];
    s32 v;
    GPICallbackCopy pr;
    void *p;
    if (gpiCheckForError(h, s, 1) != 0) {
        return 4;
    }
    if (strncmp(s, "\\npr\\", 5) != 0) {
        gpiSetError(h, 1, "Unexpected data was received from the server.");
        gpiCallErrorCallback(h, 3, 1);
        return 3;
    }
    if (gpiValueForKey(s, "\\profileid\\", buf, 0x10) == 0) {
        gpiSetError(h, 1, "Unexpected data was received from the server.");
        gpiCallErrorCallback(h, 3, 1);
        return 3;
    }
    v = atol(buf);
    pr = n->callback;
    if (pr.p.callback != 0) {
        p = GsUtil_Alloc(8);
        if (p == 0) {
            gpiSetErrorString(h, "Out of memory.");
            return 1;
        }
        ((s32 *)p)[1] = v;
        ((s32 *)p)[0] = 0;
        s32 r = gpiAddCallback(h, pr, p, n, 0);
        if (r != 0) {
            return r;
        }
    }
    gpiRemoveOperation(h, n);
    return 0;
}
}
}

namespace Nb {
extern "C" {
GPIProfile *gpiProfileListAdd(GPConnection *h, s32 a) {
    GPIProfile *out;
    GPIConnection *c = *h;
    if (a <= 0) {
        return 0;
    }
    if (gpiGetProfile(h, a, &out) != 0) {
        return out;
    }
    GPIProfile tmp;
    GPIProfile *ad = &tmp;
    Unk_ov065_022818f4_Zero(ad);
    tmp.profileId = a;
    tmp.userId = 0;
    tmp.cache = 0;
    tmp.authSig = 0;
    tmp.peerSig = 0;
    tmp.requestCount = 0;
    TableEnter(c->profileTable, ad);
    c->numProfiles++;
    if (gpiGetProfile(h, a, &out) != 0) {
        return out;
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpiGetProfile(GPConnection *h, s32 a, void *out) {
    GPIProfile key;
    void *r;
    GPIConnection *c = *h;
    key.profileId = a;
    r = TableLookup(c->profileTable, &key);
    if (out != 0) {
        *(void **)out = r;
    }
    if (r != 0) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace Nb {
extern "C" {
void gpiRemoveProfileByID(GPConnection *h, s32 a) {
    GPIConnection *c = *h;
    void *out;
    if (gpiGetProfile(h, a, &out) != 0) {
        TableRemove(c->profileTable, out);
    }
}
}
}

namespace Nb {
extern "C" {
s32 gpiRemoveProfile(GPConnection *h, void *n) {
    return TableRemove((*h)->profileTable, n);
}
}
}

namespace Nb {
extern "C" {
s32 gpiCheckProfileForUser(GPConnection *, GPIProfile *n, void *arg) {
    GPIFindProfileByUserData *l = (GPIFindProfileByUserData *)arg;
    char **e = (char **)n->cache;
    if (e != 0) {
        if (strcmp(l->nick, e[0]) == 0) {
            if (strcmp(l->email, e[2]) == 0) {
                *l->profile = n;
                l->found = 1;
                return 0;
            }
        }
    }
    return 1;
}
}
}

namespace Nb {
extern "C" {
s32 gpiFindProfileByUser(GPConnection *h, char *a, char *b, GPIProfile **out) {
    GPIFindProfileByUserData l;
    l.nick = a;
    l.email = b;
    l.profile = out;
    l.found = 0;
    gpiProfileMap(h, gpiCheckProfileForUser, &l);
    if (l.found == 0) {
        *out = NULL;
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpiProfileMapCallback(GPIProfile *n, void *p) {
    GPIProfileMapData *a = (GPIProfileMapData *)p;
    return a->func(a->connection, n, a->data);
}
}
}

namespace Nb {
extern "C" {
s32 gpiProfileMap(GPConnection *h, gpiProfileMapFunc cb, void *arg) {
    GPIProfileMapData a;
    GPIConnection *c = *h;
    a.connection = h;
    a.func = cb;
    a.data = arg;
    if (TableMapSafe2(c->profileTable, (s32 (*)(void *, void *))gpiProfileMapCallback, &a) == 0) {
        return 1;
    }
    return 0;
}
}
}

namespace Nb {
extern "C" {
s32 gpiCheckForBuddy(GPConnection *, GPIProfile *n, void *arg) {
    GPIFindProfileData *l = (GPIFindProfileData *)arg;
    if (n->buddyStatus != 0 && l->index == n->buddyStatus->buddyIndex) {
        l->profile = n;
        return 0;
    }
    return 1;
}
}
}

namespace Nb {
extern "C" {
void *gpiFindBuddy(GPConnection *h, s32 a) {
    GPIFindProfileData l;
    l.index = a;
    l.profile = 0;
    gpiProfileMap(h, gpiCheckForBuddy, &l);
    return l.profile;
}
}
}

namespace Na {
extern "C" {
s32 gpiCanFreeProfile(GPIProfile *e) {
    if (e != NULL && e->cache == 0 && e->buddyStatus == 0 && e->peerSig == NULL && e->authSig == 0) {
        return 1;
    }
    return 0;
}
}
}
