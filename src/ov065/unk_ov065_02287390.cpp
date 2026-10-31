#include "ds_div.h"
#include "types.h"
#include "net/darray.h"
#include "net/GsInAddr.h"
#include "net/natneg.h"
#include "net/SockAddrIn.h"
#include "net/qr2.h"
#include "net/GsBytes.h"
#include "net/gsPlatformUtil.h"
#include "net/SockHostEnt.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02287390.h"
#include "proto/ov065/unk_ov065_022884fc.h"

extern "C" {
extern qr2_implementation_s static_qr2_rec;
qr2_implementation_s *current_rec = &static_qr2_rec;
u8 data_ov065_0228e1b8[8] = {0xfd, 0xfc, 0x1e, 0x66, 0x6a, 0xb2, 0, 0};
qr2_implementation_s static_qr2_rec = {-1};
s32 num_local_ips;
GsInAddr local_ip_list[5];
char qr2_hostname[0x40];
char data_ov065_022917a0[0x100];
}

namespace F02287200 {










typedef qr2_implementation_s Qr;
typedef qr2_buffer_s Buf;
typedef _NATNegotiator Ent;
typedef DArrayImplementation Vec;

extern "C" {
extern Qr *current_rec;
extern u8 data_ov065_0228e1b8[];

s32 OS_SPrintf(char *, const char *, ...);
s32 sendto(s32, void *, s32, s32, void *, s32);
s32 closesocket(s32);
void ArrayFree(Vec *);
s32 ArrayLength(Vec *);
void *ArrayNth(Vec *, s32);
void ArrayAppend(Vec *, void *);
void ArrayRemoveAt(Vec *, s32);
Vec *ArrayNew(s32, s32, void *);
char *Sock_InetNtoA(GsInAddr);
void qr_add_packet_header(Buf *, s32, u8 *);
void qr2_buffer_addA(Buf *, const char *);
void qr2_buffer_add_int(Buf *, s32);

void GsNatNeg_FreeEntry(void *elem);
void qr_build_partial_old_query_reply(Qr *q, Buf *buf, s32 kind);
void qr_process_old_query(Qr *q, Buf *buf);
BOOL qr_got_recent_message(Qr *q, u32 v);
void qr_process_client_message(Qr *q, u8 *p, s32 n);
void qr_process_query(Qr *q, Buf *buf, u8 *p, s32 n);

#define HTONS(x) ((u16)((((x) >> 8) & 0xff) | (((x) << 8) & 0xff00)))
#define HTONL(x) (((x) >> 24 & 0xff) | ((x) >> 8 & 0xff00) | ((x) << 8 & 0xff0000) | ((x) << 24 & 0xff000000))

}
}

namespace F02287b18 {


extern "C" {
extern qr2_implementation_s *current_rec;
extern qr2_implementation_s static_qr2_rec;
extern char qr2_hostname[];
extern char data_ov065_022917a0[];

s32 func_02133150(s32, s32);
s32 OS_SPrintf(char *, const char *, ...);

SockHostEnt *getlocalhost();
s32 inet_addr(const char *);
s32 recvfrom(s32, void *, s32, s32, SockAddrIn *, s32 *);
s32 closesocket(s32);
s32 CanReceiveOnSocket(s32);
s32 SocketShutDown();
SockHostEnt *Sock_GetHostByName(const char *);
void send_heartbeat(qr2_implementation_s *, s32);
void send_keepalive(qr2_implementation_s *);
void qr2_parse_queryA(qr2_implementation_s *, char *, s32, SockAddrIn *);

void qr_build_partial_query_reply(qr2_implementation_s *q, qr2_buffer_s *b, s32 type, s32 count, u8 *list);
void qr_add_packet_header(qr2_buffer_s *b, s32 c, u8 *ip);
void gs_encrypt(u8 *key, s32 keylen, u8 *data, s32 datalen);
void gs_encode(u8 *in, s32 len, u8 *out);
u8 encode_ct(u8 c);
void swap_byte(u8 *a, u8 *b);
s32 get_sockaddrin__qr2(const char *name, u32 port, SockAddrIn *sa, SockHostEnt **hp);
void enum_local_ips();
void qr2_buffer_addA(qr2_buffer_s *b, const char *s);
void qr2_buffer_add_int(qr2_buffer_s *b, s32 v);
void qr2_keybuffer_add(qr2_keybuffer_s *k, s32 c);
void qr2_shutdown(qr2_implementation_s *q);
void qr2_send_statechanged(qr2_implementation_s *q);
void qr2_check_send_heartbeat(qr2_implementation_s *q);
void qr2_check_queries(qr2_implementation_s *q);
void qr2_think(qr2_implementation_s *q);
void qr2_register_publicaddress_callback(qr2_implementation_s *q, qr2_publicaddresscallback_t cb);
void qr2_register_clientmessage_callback(qr2_implementation_s *q, qr2_clientmessagecallback_t v);
void qr2_register_natneg_callback(qr2_implementation_s *q, qr2_natnegcallback_t v);
s32 qr2_init_socketA(qr2_implementation_s **out, s32 fd, s32 a2, const char *name, const char *secret, s32 a5, s32 a6, qr2_serverkeycallback_t cb88,
                        qr2_playerteamkeycallback_t cb8c, qr2_playerteamkeycallback_t cb90, qr2_keylistcallback_t cb94, qr2_countcallback_t cb98,
                        qr2_adderrorcallback_t cb9c, void *ud);

}
}

namespace F02287b18 {
extern "C" {
s32 qr2_init_socketA(qr2_implementation_s **out, s32 fd, s32 a2, const char *name, const char *secret, s32 a5, s32 a6, qr2_serverkeycallback_t cb88,
                        qr2_playerteamkeycallback_t cb8c, qr2_playerteamkeycallback_t cb90, qr2_keylistcallback_t cb94, qr2_countcallback_t cb98,
                        qr2_adderrorcallback_t cb9c, void *ud) {
    s32 i;
    qr2_implementation_s *q;
    char buf[0x40];
    s32 ok;
    if (out == NULL) {
        q = &static_qr2_rec;
    } else {
        *out = (qr2_implementation_s *)GsUtil_Alloc(sizeof(qr2_implementation_s));
        q = *out;
    }
    srand(current_time());
    STD_CopyString(q->gamename, name);
    STD_CopyString(q->secret_key, secret);
    q->qport = a2;
    i = 0;
    q->lastheartbeat = 0;
    q->lastka = 0;
    q->hbsock = fd;
    q->listed_state = 1;
    q->udata = ud;
    q->server_key_callback = cb88;
    q->player_key_callback = cb8c;
    q->team_key_callback = cb90;
    q->key_list_callback = cb94;
    q->playerteam_count_callback = cb98;
    q->adderror_callback = cb9c;
    q->nn_callback = NULL;
    q->cm_callback = NULL;
    q->cdkeyprocess = NULL;
    q->ispublic = a5;
    q->read_socket = i;
    q->nat_negotiate = a6;
    q->publicip = i;
    q->publicport = i;
    q->pa_callback = NULL;
    q->userstatechangerequested = i;
    for (; i < 4; i++) {
        q->instance_key[i] = rand() % 0xff;
    }
    for (i = 0; i < 10; i++) {
        q->client_message_keys[i] = -1;
    }
    q->cur_message_key = 0;
    if (num_local_ips == 0) {
        enum_local_ips();
    }
    if (a5 != 0) {
        char c = qr2_hostname[0];
        if (c == 0) {
            OS_SPrintf(buf, "%s.master.gs.nintendowifi.net", name);
        }
        ok = get_sockaddrin__qr2(c != 0 ? qr2_hostname : buf, 0x6cfc, &q->hbaddr, NULL);
    } else {
        ok = 1;
    }
    if (ok != 0) {
        return 0;
    }
    return 3;
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_register_natneg_callback(qr2_implementation_s *q, qr2_natnegcallback_t v) {
    if (q == NULL) {
        q = current_rec;
    }
    q->nn_callback = v;
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_register_clientmessage_callback(qr2_implementation_s *q, qr2_clientmessagecallback_t v) {
    if (q == NULL) {
        q = current_rec;
    }
    q->cm_callback = v;
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_register_publicaddress_callback(qr2_implementation_s *q, qr2_publicaddresscallback_t cb) {
    if (q == NULL) {
        q = current_rec;
    }
    q->pa_callback = cb;
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_think(qr2_implementation_s *q) {
    if (q == NULL) {
        q = current_rec;
    }
    if (q->ispublic != 0) {
        qr2_check_send_heartbeat(q);
    }
    qr2_check_queries(q);
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_check_queries(qr2_implementation_s *q) {
    struct {
        SockAddrIn sa;
        s32 len;
    } l;
    s32 z = 0;
    l.len = 8;
    if (q->read_socket != 0) {
        if (CanReceiveOnSocket(q->hbsock) != 0) {
            do {
                s32 r = recvfrom(q->hbsock, data_ov065_022917a0, 0xff, z, &l.sa, &l.len);
                if (r != ~z) {
                    data_ov065_022917a0[r] = z;
                    qr2_parse_queryA(q, data_ov065_022917a0, r, &l.sa);
                }
            } while (CanReceiveOnSocket(q->hbsock) != 0);
        }
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_check_send_heartbeat(qr2_implementation_s *q) {
    u32 now = current_time();
    if (q->hbsock != -1) {
        s32 r = q->listed_state;
        if (r > 0 && now - q->lastheartbeat > 0x2710) {
            if (r >= 4) {
                q->listed_state = 0;
                q->adderror_callback(5, "No challenge value was received from the master server.", q->udata);
                return;
            }
            send_heartbeat(q, 3);
            q->listed_state = q->listed_state + 1;
        } else if (q->userstatechangerequested != 0 && now - q->lastheartbeat > 0x2710) {
            send_heartbeat(q, 1);
        } else {
            u32 a = q->lastheartbeat;
            if (now - a > 0xea60 || a == 0 || now < a) {
                send_heartbeat(q, 0);
            }
        }
        if (now - q->lastka > 0x4e20) {
            send_keepalive(q);
        }
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_send_statechanged(qr2_implementation_s *q) {
    if (q == NULL) {
        q = current_rec;
    }
    if (q->ispublic != 0) {
        u32 d = current_time() - q->lastheartbeat;
        if (d < 0x2710) {
            q->userstatechangerequested = 1;
            return;
        }
        send_heartbeat(q, 1);
        q->userstatechangerequested = 0;
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_shutdown(qr2_implementation_s *q) {
    if (q == NULL) {
        q = current_rec;
    }
    if (q->ispublic != 0) {
        send_heartbeat(q, 2);
    }
    if (q->hbsock != -1 && q->read_socket != 0) {
        closesocket(q->hbsock);
    }
    q->hbsock = -1;
    q->lastheartbeat = 0;
    if (q->read_socket != 0) {
        SocketShutDown();
    }
    if (q != &static_qr2_rec) {
        GsUtil_Free(q);
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_keybuffer_add(qr2_keybuffer_s *k, s32 c) {
    s32 n = k->numkeys;
    if (n < 0xfe && c >= 1 && c <= 0xfe) {
        k->numkeys = n + 1;
        k->keys[n] = c;
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_buffer_add_int(qr2_buffer_s *b, s32 v) {
    char t[0x18];
    OS_SPrintf(t, "%d", v);
    qr2_buffer_addA(b, t);
}
}
}

namespace F02287b18 {
extern "C" {
void qr2_buffer_addA(qr2_buffer_s *b, const char *s) {
    s32 n = STD_GetStringLength(s) + 1;
    s32 len = b->len;
    s32 avail = 0x800 - len;
    if (n > avail) {
        n = avail;
    }
    if (n != 0) {
        memcpy(&b->buffer[len], s, n);
        b->len += n;
        b->buffer[b->len - 1] = 0;
    }
}
}
}

namespace F02287b18 {
extern "C" {
void enum_local_ips() {
    SockHostEnt *l = getlocalhost();
    if (l != NULL) {
        num_local_ips = 0;
        s32 t;
        do {
            s32 i = num_local_ips;
            u8 *e = (u8 *)l->addrList[i];
            if (e == NULL) {
                break;
            }
            local_ip_list[i] = *(GsInAddr *)e;
            t = num_local_ips + 1;
            num_local_ips = t;
        } while (t < 5);
    }
}
}
}

namespace F02287b18 {
extern "C" {
s32 get_sockaddrin__qr2(const char *name, u32 port, SockAddrIn *sa, SockHostEnt **hp) {
    SockHostEnt *h = NULL;
    s32 v;
    sa->family = 2;
    v = (u16)port;
    sa->port = (u16)(((v >> 8) & 0xff) | ((v << 8) & 0xff00));
    if (name == NULL) {
        sa->addr = 0;
    } else {
        sa->addr = inet_addr(name);
    }
    if (sa->addr == (u32)-1) {
        if (strcmp(name, "255.255.255.255") != 0) {
            h = Sock_GetHostByName(name);
            if (h == NULL) {
                return 0;
            }
            sa->addr = *(u32 *)*h->addrList;
        }
    }
    if (hp != NULL) {
        *hp = h;
    }
    return 1;
}
}
}

namespace F02287b18 {
extern "C" {
void swap_byte(u8 *a, u8 *b) {
    u8 t = *a;
    *a = *b;
    *b = t;
}
}
}

namespace F02287b18 {
extern "C" {
u8 encode_ct(u8 c) {
    if (c < 0x1a) {
        return c + 0x41;
    }
    if (c < 0x34) {
        return c + 0x47;
    }
    if (c < 0x3e) {
        return c - 4;
    }
    if (c == 0x3e) {
        return 0x2b;
    }
    if (c == 0x3f) {
        return 0x2f;
    }
    return 0;
}
}
}

namespace F02287b18 {
extern "C" {
void gs_encode(u8 *in, s32 len, u8 *out) {
    u8 t[7];
    s32 k;
    u8 *tp;
    s32 n = 0;
    if (len > 0) {
        do {
            for (k = 0, tp = t; k <= 2; tp++, k++, n++) {
                if (n < len) {
                    *tp = *in++;
                } else {
                    *tp = 0;
                }
            }
            {
                s32 a = t[0];
                s32 b;
                s32 c;
                t[3] = a >> 2;
                b = t[1];
                t[4] = ((a & 3) << 4) + (b >> 4);
                c = t[2];
                t[5] = ((b & 0xf) << 2) + (c >> 6);
                t[6] = c & 0x3f;
            }
            for (k = 0, tp = &t[3]; k <= 3; out++, tp++, k++) {
                *out = encode_ct(*tp);
            }
        } while (n < len);
    }
    *out = 0;
}
}
}

namespace F02287b18 {
extern "C" {
void gs_encrypt(u8 *key, s32 keylen, u8 *data, s32 datalen) {
    u8 state[0x100];
    s16 i;
    s16 k;
    u8 x;
    u8 j;
    u8 *volatile p;
    u8 *q;
    for (i = 0; i < 0x100; i++) {
        state[i] = i;
    }
    x = 0;
    j = 0;
    i = 0;
    q = state;
    p = q;
    for (; i < 0x100; i++) {
        j = (*q + key[x] + j) % 0x100;
        x = DS_MOD((x + 1), keylen);
        swap_byte(q, p + j);
        q++;
    }
    {
        u8 a = 0;
        u8 c = 0;
        for (k = 0; k < datalen; k++) {
            u8 *pa;
            a = (a + data[k] + 1) % 0x100;
            pa = &state[a];
            c = (state[a] + c) % 0x100;
            swap_byte(pa, &state[c]);
            data[k] ^= state[(u8)((state[a] + state[c]) % 0x100)];
        }
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr_add_packet_header(qr2_buffer_s *b, s32 c, u8 *ip) {
    u8 *d;
    b->buffer[0] = c;
    d = b->buffer + 1;
    d[-1 + 1] = ip[0];
    d[1] = ip[1];
    d[2] = ip[2];
    d[3] = ip[3];
    b->len = 5;
}
}
}

namespace F02287b18 {
extern "C" {
void compute_challenge_response(qr2_implementation_s *q, qr2_buffer_s *b, const char *s, s32 n) {
    char tmp[0x44];
    if (n >= 1 && n <= 0x41 && s[n - 1] == 0) {
        STD_CopyString(tmp, s);
        gs_encrypt((u8 *)q->secret_key, STD_GetStringLength(q->secret_key), (u8 *)tmp, n - 1);
        gs_encode((u8 *)tmp, n - 1, (u8 *)b + b->len);
        b->len += STD_GetStringLength((char *)b + b->len) + 1;
    }
}
}
}

namespace F02287b18 {
extern "C" {
void handle_public_address(qr2_implementation_s *q, const char *s) {
    u32 ip;
    u32 port;
    u32 pt;
    sscanf(s, "%08X%04X", &ip, &port);
    pt = (u16)port;
    ip = ((ip << 24) & 0xff000000) | (((ip << 8) & 0xff0000) | (((ip >> 24) & 0xff) | ((ip >> 8) & 0xff00)));
    if (ip != 0 && pt != 0) {
        if (q->publicip != ip || q->publicport != pt) {
            q->publicip = ip;
            q->publicport = pt;
            q->pa_callback(ip, pt, q->udata);
        }
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr_build_partial_query_reply(qr2_implementation_s *q, qr2_buffer_s *b, s32 type, s32 count, u8 *list) {
    qr2_keybuffer_s kb;
    s32 n;
    s32 i;
    s32 j;
    kb.numkeys = 0;
    if (count == 0) {
        return;
    }
    if ((u32)(type - 1) <= 1) {
        u16 t;
        s32 v;
        u32 avail = 0x800 - b->len;
        if (avail < 2) {
            return;
        }
        n = q->playerteam_count_callback(type, q->udata);
        v = (u16)n;
        t = (u16)(((v >> 8) & 0xff) | ((v << 8) & 0xff00));
        u8 *d = b->buffer + b->len;
        u8 *sp = (u8 *)&t;
        d[0] = sp[0];
        d[1] = sp[1];
        b->len += 2;
    } else {
        n = 1;
    }
    if (count == 0xff) {
        q->key_list_callback(type, &kb, q->udata);
        for (j = 0; j < kb.numkeys; j++) {
            const char *s = qr2_registered_key_list[kb.keys[j]];
            if (s == NULL) {
                s = "unknown";
            }
            qr2_buffer_addA(b, s);
            if (type == 0) {
                s32 sv = b->len;
                q->server_key_callback(kb.keys[j], b, q->udata);
                if (sv == b->len) {
                    qr2_buffer_addA(b, "");
                }
            }
        }
        if (0x800 - b->len < 1) {
            return;
        }
        b->buffer[b->len++] = 0;
        count = kb.numkeys;
        list = kb.keys;
        if (type == 0) {
            return;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < count; j++) {
            s32 save = b->len;
            if (type == 0) {
                q->server_key_callback(list[j], b, q->udata);
            } else if (type == 1) {
                q->player_key_callback(list[j], i, b, q->udata);
            } else if (type == 2) {
                q->team_key_callback(list[j], i, b, q->udata);
            }
            if (save == b->len) {
                qr2_buffer_addA(b, "");
            }
        }
    }
}
}
}

namespace F02287b18 {
extern "C" {
void qr_build_query_reply(qr2_implementation_s *q, qr2_buffer_s *b, s32 c0, u8 *l0, s32 c1, u8 *l1, s32 c2, u8 *l2) {
    qr_build_partial_query_reply(q, b, 0, c0, l0);
    qr_build_partial_query_reply(q, b, 1, c1, l1);
    qr_build_partial_query_reply(q, b, 2, c2, l2);
}
}
}

namespace F02287200 {
extern "C" {
void qr_process_query(Qr *q, Buf *buf, u8 *p, s32 n) {
    u32 l1, l2, l3;
    u8 *p1 = NULL;
    u8 *p2 = p1;
    u8 *p3 = p1;
    if (n >= 3) {
        l1 = *p++;
        n--;
        if (l1 != 0 && l1 != 0xff) {
            p1 = p;
            p += l1;
            n -= l1;
        }
        if (n >= 2) {
            l2 = *p++;
            n--;
            if (l2 != 0 && l2 != 0xff) {
                p2 = p;
                p += l2;
                n -= l2;
            }
            if (n >= 1) {
                l3 = *p;
                n--;
                if (l3 != 0 && l3 != 0xff) {
                    p3 = p + 1;
                    n -= l3;
                }
                if (n >= 0) {
                    qr_build_query_reply(q, buf, l1, p1, l2, p2, l3, p3);
                }
            }
        }
    }
}
}
}

namespace F02287200 {
extern "C" {
void qr_build_partial_old_query_reply(Qr *q, Buf *buf, s32 kind) {
    char tmp[0x80];
    struct Keys {
        u8 b[0x100];
        s32 n;
    } k;
    s32 cnt;
    s32 i;
    s32 j;
    s32 mark;
    char *name;
    u8 *p;
    k.n = 0;
    if ((u32)(kind - 1) <= 1) {
        cnt = q->playerteam_count_callback(kind, q->udata);
    } else {
        cnt = 1;
    }
    q->key_list_callback(kind, (qr2_keybuffer_s *)&k, q->udata);
    i = 0;
    if (i < k.n) {
      p = k.b;
      do {
        name = qr2_registered_key_list[*p];
        if (name == NULL) {
            name = "unknown";
        }
        if (kind == 0) {
            qr2_buffer_addA(buf, name);
            buf->buffer[buf->len - 1] = 0x5c;
            mark = buf->len;
            q->server_key_callback(*p, buf, q->udata);
            if (mark == buf->len) {
                qr2_buffer_addA(buf, "");
            }
            buf->buffer[buf->len - 1] = 0x5c;
        } else {
            for (j = 0; j < cnt; j++) {
                OS_SPrintf(tmp, "%s%d", name, j);
                qr2_buffer_addA(buf, tmp);
                buf->buffer[buf->len - 1] = 0x5c;
                mark = buf->len;
                if (kind == 1) {
                    q->player_key_callback(*p, j, buf, q->udata);
                } else if (kind == 2) {
                    q->team_key_callback(*p, j, buf, q->udata);
                }
                if (mark == buf->len) {
                    qr2_buffer_addA(buf, "");
                }
                buf->buffer[buf->len - 1] = 0x5c;
            }
        }
        p++;
      } while (++i < k.n);
    }
}
}
}

namespace F02287200 {
extern "C" {
void qr_process_old_query(Qr *q, Buf *buf) {
    buf->len = 1;
    buf->buffer[0] = 0x5c;
    qr_build_partial_old_query_reply(q, buf, 0);
    qr_build_partial_old_query_reply(q, buf, 1);
    qr_build_partial_old_query_reply(q, buf, 2);
    qr2_buffer_addA(buf, "final\\\\queryid\\1.1");
    buf->len--;
}
}
}

namespace F02287200 {
extern "C" {
void qr_process_client_message(Qr *q, u8 *p, s32 n) {
    struct Hdr {
        u8 b[6];
    };
    struct B4 {
        u8 b[4];
    };
    Hdr hdr = *(Hdr *)data_ov065_0228e1b8;
    u32 l;
    s32 j;
    BOOL ok = TRUE;
    u8 *h;
    if (n >= 10) {
        h = hdr.b;
        for (j = 0; j < 6; j++) {
            if (*h != p[j]) {
                ok = FALSE;
                break;
            }
            h++;
        }
    } else {
        ok = FALSE;
    }
    if (ok) {
        qr2_natnegcallback_t cb;
        B4 *a = (B4 *)&l;
        B4 *s = (B4 *)(p + 6);
        a->b[0] = s->b[0];
        a->b[1] = s->b[1];
        a->b[2] = s->b[2];
        a->b[3] = s->b[3];
        cb = q->nn_callback;
        if (cb != NULL) {
            u32 v = l;
            cb(HTONL(v), q->udata);
        }
    } else {
        qr2_clientmessagecallback_t cb = q->cm_callback;
        if (cb != NULL) {
            cb(p, n, q->udata);
        }
    }
}
}
}

namespace F02287200 {
extern "C" {
BOOL qr_got_recent_message(Qr *q, u32 v) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (v == q->client_message_keys[i]) {
            return TRUE;
        }
    }
    q->cur_message_key = (q->cur_message_key + 1) % 10;
    q->client_message_keys[q->cur_message_key] = v;
    return FALSE;
}
}
}

namespace F02287200 {
extern "C" {
void qr2_parse_queryA(Qr *q, char *data, s32 n, SockAddrIn *addr) {
    struct {
        s32 x;
        Buf out;
    } l;
    s32 type;
    s32 c;
    l.out.len = 0;
    if (q == NULL) {
        q = current_rec;
    }
    c = data[0];
    if (c == 0x3b) {
        qr2_cdkeyprocesscallback_t cb = q->cdkeyprocess;
        if (cb != NULL) {
            cb((u8 *)data, n, addr);
            return;
        }
        return;
    }
    if (c == 0x5c) {
        qr_process_old_query(q, &l.out);
        sendto(q->hbsock, &l.out, l.out.len, 0, addr, 8);
        return;
    }
    if (n < 7) {
        return;
    }
    if ((u8)c != 0xfe) {
        return;
    }
    if (((u8 *)data)[1] != 0xfd) {
        return;
    }
    if (q->listed_state > 0) {
        q->listed_state = 0;
    }
    type = data[2];
    {
        char *hdr = data + 3;
        char *body = data + 7;
        n -= 7;
        qr_add_packet_header(&l.out, type, (u8 *)hdr);
        switch (type) {
        case 0:
            qr_process_query(q, &l.out, (u8 *)body, n);
            break;
        case 1:
            if (n >= 13 && q->pa_callback != 0) {
                handle_public_address(q, body + n - 13);
            }
            compute_challenge_response(q, &l.out, body, n);
            break;
        case 2:
            if (n > 0x20) {
                n = 0x20;
            }
            l.out.buffer[0] = 5;
            memcpy(l.out.buffer + l.out.len, body, n);
            l.out.len += n;
            break;
        case 4: {
            if (q->listed_state == -1) {
                return;
            }
            l.x = 0;
            do {
                if (hdr[l.x] != ((s8 *)q->instance_key)[l.x]) {
                    return;
                }
                l.x++;
            } while (l.x < 4);
            if (n < 2) {
                return;
            }
            q->listed_state = -1;
            q->adderror_callback(body[0], (const char *)body + 1, q->udata);
            return;
        }
        case 6: {
            l.x = 0;
            do {
                if (hdr[l.x] != ((s8 *)q->instance_key)[l.x]) {
                    return;
                }
                l.x++;
            } while (l.x < 4);
            if (n < 4) {
                return;
            }
            l.out.buffer[0] = 7;
            *(n ? (GsBytes4 *)(l.out.buffer + l.out.len) : (GsBytes4 *)(l.out.buffer + l.out.len)) = *(GsBytes4 *)body;
            l.out.len = l.out.len + 4;
            *(n ? (GsBytes4 *)&l.x : (GsBytes4 *)&l.x) = *(GsBytes4 *)body;
            if (qr_got_recent_message(q, l.x) == 0) {
                qr_process_client_message(q, (u8 *)body + 4, n - 4);
            }
            break;
        }
        case 3:
        case 5:
        case 7:
        case 8:
            return;
        default:
            return;
        }
        sendto(q->hbsock, &l.out, l.out.len, 0, addr, 8);
    }
}
}
}

namespace F02287200 {
extern "C" {
void send_keepalive(Qr *q) {
    Buf buf;
    buf.len = 0;
    qr_add_packet_header(&buf, 8, q->instance_key);
    sendto(q->hbsock, &buf, buf.len, 0, &q->hbaddr, 8);
    q->lastka = current_time();
}
}
}

namespace F02287200 {
extern "C" {
void send_heartbeat(Qr *q, s32 mode) {
    Buf buf;
    char tmp[20];
    s32 i;
    GsInAddr *p;
    buf.len = 0;
    qr_add_packet_header(&buf, 3, q->instance_key);
    i = 0;
    if (i < num_local_ips) {
        p = local_ip_list;
        do {
            OS_SPrintf(tmp, "localip%d", i);
            qr2_buffer_addA(&buf, tmp);
            qr2_buffer_addA(&buf, Sock_InetNtoA(*p));
            p++;
        } while (++i < num_local_ips);
    }
    qr2_buffer_addA(&buf, "localport");
    qr2_buffer_add_int(&buf, q->qport);
    qr2_buffer_addA(&buf, "natneg");
    qr2_buffer_addA(&buf, q->nat_negotiate != 0 ? "1" : "0");
    if (mode != 0) {
        qr2_buffer_addA(&buf, "statechanged");
        qr2_buffer_add_int(&buf, mode);
    }
    qr2_buffer_addA(&buf, "gamename");
    qr2_buffer_addA(&buf, (char *)q->gamename);
    if (q->pa_callback != 0) {
        qr2_buffer_addA(&buf, "publicip");
        qr2_buffer_add_int(&buf, q->publicip);
        qr2_buffer_addA(&buf, "publicport");
        qr2_buffer_add_int(&buf, q->publicport);
    }
    if (mode != 2) {
        qr_build_query_reply(q, &buf, 0xff, NULL, 0xff, NULL, 0xff, NULL);
    } else if (0x800 - buf.len >= 1) {
        buf.buffer[buf.len++] = 0;
    }
    sendto(q->hbsock, &buf, buf.len, 0, &q->hbaddr, 8);
    q->lastheartbeat = current_time();
    q->lastka = q->lastheartbeat;
    if (mode != 0) {
        q->userstatechangerequested = 0;
    }
}
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02287390) {
    HOST_OVERLAY_VAR(current_rec),
    HOST_OVERLAY_VAR(data_ov065_0228e1b8),
    HOST_OVERLAY_VAR(static_qr2_rec),
    HOST_OVERLAY_VAR(num_local_ips),
    HOST_OVERLAY_VAR(local_ip_list),
    HOST_OVERLAY_VAR(qr2_hostname),
    HOST_OVERLAY_VAR(data_ov065_022917a0),
    HOST_OVERLAY_VARS_END
};
