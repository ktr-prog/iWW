
#include "ds_div.h"
#include "types.h"
#include "net/gt2Main.h"
#include "net/GsInAddr.h"
#include "net/natneg.h"
#include "net/SockHostEnt.h"
#include "net/gsPlatformUtil.h"
#include "net/SockAddrIn.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02283720.h"
#include "proto/ov065/unk_ov065_02285778.h"
#include "proto/ov065/unk_ov065_02286934.h"
#include "proto/ov065/unk_ov065_0225fdf0.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_022789fc.h"
#include "proto/ov065/unk_ov065_02283f34.h"


extern "C" { s32 data_ov065_02291504; }
extern "C" { char data_ov065_02291508[0x2c]; }

namespace N02285630 {
extern "C" {









typedef GTI2Connection Cn;
typedef GTI2IncomingBufferMessage It;

extern "C" {
extern u8 data_ov065_0228e150[];
s32 gti2PingCallback(Cn *, s32);
s32 gti2ConnectedCallback(Cn *, s32, u8 *, s32);
void gti2ConnectionClosed(Cn *, ...);
s32 gti2SendClosed(Cn *);
s32 gti2ConnectionMemoryError(Cn *);
s32 gti2ConnectionCommunicationError(Cn *);
s32 gti2ConnectionError(Cn *, s32, s32);
BOOL gti2HandleESN(Cn *, u32);

s32 gti2HandleAck(Cn *c, u8 *p, s32 n);
s32 gti2HandleNack(Cn *c, u8 *p, s32 n);
s32 gti2HandlePing(Cn *c, u8 *p, s32 n);
s32 gti2HandlePong(Cn *c, u8 *p, s32 n);
s32 gti2HandleClosed(Cn *c);
void gti2SetPendingAck(Cn *c);
s32 gti2DeliverHoldMessages(Cn *c);
void gti2RemoveHoldMessage(Cn *c, It *e, s32 i);
s32 gti2BufferIncomingMessage(Cn *c, s32 a, u32 seq, u8 *p, s32 n, s32 *out);
s32 gti2IncomingBufferMessageCompare(void *a, void *b);
s32 gti2DeliverReliableMessage(Cn *c, s32 mode, u8 *p, s32 n);
s32 gti2HandleClose(Cn *c);
s32 gti2HandleReject(Cn *c, u8 *p, s32 n);
s32 gti2HandleAccept(Cn *c);
s32 gti2HandleClientResponse(Cn *c, u8 *p, s32 n);
s32 gti2HandleServerChallenge(Cn *c, u8 *p, s32 n);
s32 gti2HandleClientChallenge(Cn *c, u8 *p, s32 n);
BOOL gti2HandleAppReliable(Cn *c, u8 *p, s32 n);



















}

}
}

namespace N02285f3c {
extern "C" {



typedef GTI2Connection Conn062;
typedef GTI2Socket Sock062;
typedef SockAddrIn Sa062;


extern u16 data_0213a510[];

extern "C" {
s32 GOAGetLastError(s32 fd);
s32 closesocket(s32 fd);
s32 CanSendOnSocket(s32 fd);
void SocketShutDown();
void SocketStartUp();
s32 gti2ClosedCallback(Conn062 *p, s32 a);
s32 gti2ConnectedCallback(Conn062 *p, s32 a, u8 *b, s32 c);
s32 gti2SocketErrorCallback(Sock062 *c);
void gti2ConnectionCleanup(Conn062 *p);
void gti2ConnectionClosed(Conn062 *p, ...);
s32 gti2ConnectionThink(Conn062 *p, u32 now);
s32 gti2SendClosed(Conn062 *p);
void gt2CloseAllConnectionsHard(Sock062 *c);
s32 gti2ConnectionCommunicationError(Conn062 *p);
s32 gti2ConnectionError(Conn062 *p, s32 a, s32 b);
void gti2SocketError(Sock062 *c);
void gti2FreeSocketConnection(Conn062 *p);
Conn062 *gti2SocketFindConnection(Sock062 *c, u32 ip, u16 port);
void gti2CloseSocket(Sock062 *c);
}

extern "C" {












BOOL gti2SocketConnectionsThinkMap(void *elem, void *arg);









s32 gti2ConnectionHash(void *elem, s32 n);
s32 gti2ConnectionCompare(void *a, void *b);
void gti2ConnectionFree(void *elem);








}

}
}

namespace N022868b0 {
extern "C" {



#define SWAP32(x) ((((x) << 24) & 0xff000000) | ((((x) << 8) & 0xff0000) | ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00))))
#define SWAP16(x) ((((x) >> 8) & 0xff) | (((x) << 8) & 0xff00))












extern "C" {



extern char data_ov065_0228e174[];
extern char data_ov065_0228e190[];
extern char data_ov065_0228e1ac[];

s32 OS_SPrintf(char *buf, const char *fmt, ...);
s32 OS_SNPrintf(char *buf, s32 n, const char *fmt, ...);

s32 closesocket(s32 fd);
SockHostEnt *getlocalhost();
s32 CanReceiveOnSocket(s32 fd);
_NATNegotiator *FindNegotiatorForCookie(u32 cookie);

void SendInitPackets(_NATNegotiator *ctx);
void SendPingPacket(_NATNegotiator *ctx);
void NegotiateThink(_NATNegotiator *ctx);
void SendConnectAck(_NATNegotiator *ctx, SockAddrIn *sa);
}


















}
}

namespace N022868b0 { extern "C" {
extern "C" char *gt2AddressToString(u32 ip, u16 port, char *buf) {
    GsInAddr a;
    if (buf == NULL) {
        data_ov065_02291504 = data_ov065_02291504 ^ 1;
        buf = data_ov065_02291508 + data_ov065_02291504 * 0x16;
    }
    if (ip != 0) {
        a.addr = ip;
        if (port != 0) {
            OS_SPrintf(buf, "%s:%d", Sock_InetNtoA(a.addr), port);
        } else {
            OS_SPrintf(buf, "%s", Sock_InetNtoA(a.addr));
        }
    } else if (port != 0) {
        OS_SPrintf(buf, ":%d", port);
    } else {
        buf[0] = 0;
    }
    return buf;
}
} }

namespace N02285f3c { extern "C" {
BOOL gt2StringToAddress(char *s, u32 *pip, u16 *pport) {
    char host[0x100];
    u32 ip;
    u32 port;
    char *colon;
    char *q;
    s32 c, r;
    if (s == 0 || *s == 0) {
        ip = 0;
        port = 0;
    } else {
        colon = strchr(s, ':');
        if (colon == 0) {
            port = 0;
        } else {
            if (colon == s) {
                s = 0;
                ip = 0;
            } else {
                s32 n = colon - s;
                memcpy(host, s, n);
                host[n] = 0;
                s = host;
            }
            q = colon + 1;
            c = *q;
            if (c != 0) {
                do {
                    if (c < 0 || c >= 0x80) {
                        c = 0;
                    } else {
                        c = data_0213a510[c] & 8;
                    }
                    if (c == 0) {
                        return FALSE;
                    }
                    q++;
                    c = *q;
                } while (c != 0);
            }
            r = atol(colon + 1);
            if (r < 0 || r > 0xffff) {
                return FALSE;
            }
            port = (u16)r;
        }
        if (s != 0) {
            ip = inet_addr(s);
            if (ip == -1) {
                SockHostEnt *h = Sock_GetHostByName(s);
                if (h == 0) {
                    return FALSE;
                }
                ip = *(u32 *)*h->addrList;
            }
        }
    }
    if (pip != 0) {
        *pip = ip;
    }
    if (pport != 0) {
        *pport = port;
    }
    return TRUE;
}
} }

namespace N02285f3c { extern "C" {
void gti2MessageCheck(u8 **s, s32 *len) {
    u8 *p = *s;
    if (p == 0) {
        *s = (u8 *)"";
        *len = 0;
    } else if (*len == -1) {
        *len = STD_GetStringLength((char *)p) + 1;
    }
}
} }

namespace N02285f3c { extern "C" {
s32 gti2ConnectionHash(void *elem, s32 n) {
    Conn062 *p = *(Conn062 **)elem;
    return DS_UMOD(p->ip * p->port, (u32)n);
}
} }

namespace N02285f3c { extern "C" {
s32 gti2ConnectionCompare(void *a, void *b) {
    Conn062 *x = *(Conn062 **)a;
    Conn062 *y = *(Conn062 **)b;
    if (x->ip != y->ip) {
        return x->ip - y->ip;
    }
    return (s16)(x->port - y->port);
}
} }

namespace N02285f3c { extern "C" {
void gti2ConnectionFree(void *elem) {
    gti2ConnectionCleanup(*(Conn062 **)elem);
}
} }

namespace N02285f3c { extern "C" {
Conn062 *gti2SocketFindConnection(Sock062 *c, u32 ip, u16 port) {
    Conn062 *key;
    Conn062 tmp;
    Conn062 **e;
    tmp.ip = ip;
    tmp.port = port;
    key = &tmp;
    e = (Conn062 **)TableLookup(c->connections, &key);
    if (e != 0) {
        return *e;
    }
    return 0;
}
} }

namespace N02285f3c { extern "C" {
s32 gti2CreateSocket(Sock062 **out, char *addr, u32 rsz, u32 ssz, gt2SocketErrorCallback arg) {
    struct {
        u16 port;
        Sa062 sa;
        s32 ip;
        s32 len;
    } l;
    Sock062 *c;
    u32 *w;
    SocketStartUp();
    if (ssz == 0) {
        ssz = 0x10000;
    }
    if (rsz == 0) {
        rsz = 0x10000;
    }
    if (gt2StringToAddress(addr, (u32 *)&l.ip, &l.port) == 0) {
        return 4;
    }
    c = (Sock062 *)GsUtil_Alloc(sizeof(Sock062));
    if (c == 0) {
        return 1;
    }
    memset(c, 0, sizeof(Sock062));
    c->socket = -1;
    c->incomingBufferSize = ssz;
    c->outgoingBufferSize = rsz;
    c->socketErrorCallback = arg;
    c->connections = TableNew2(sizeof(Conn062 *), 0x20, 2, gti2ConnectionHash, gti2ConnectionCompare, 0);
    if (c->connections == 0) {
        GsUtil_Free(c);
        return 1;
    }
    c->closedConnections = ArrayNew(sizeof(Conn062 *), 4, gti2ConnectionFree);
    if (c->closedConnections == 0) {
        TableFree(c->connections);
        GsUtil_Free(c);
        return 1;
    }
    c->socket = socket(2, 2, 0);
    if (c->socket == -1) {
        TableFree(c->connections);
        ArrayFree(c->closedConnections);
        GsUtil_Free(c);
        return 3;
    }
    w = (u32 *)&l.sa;
    w[0] = 0;
    w[1] = 0;
    l.sa.family = 2;
    l.sa.addr = l.ip;
    {
        u16 t = l.port;
        l.sa.port = ((t >> 8) & 0xff) | ((t << 8) & 0xff00);
    }
    if (bind(c->socket, (Sa062 *)w, 8) == -1) {
        closesocket(c->socket);
        TableFree(c->connections);
        ArrayFree(c->closedConnections);
        GsUtil_Free(c);
        return 3;
    }
    l.len = 8;
    getsockname(c->socket, &l.sa, &l.len);
    c->ip = l.sa.addr;
    {
        u16 t = l.sa.port;
        c->port = ((t >> 8) & 0xff) | ((t << 8) & 0xff00);
    }
    *out = c;
    return 0;
}
} }

namespace N02285f3c { extern "C" {
void gti2CloseSocket(Sock062 *c) {
    if (c->callbackLevel != 0) {
        c->close = 1;
        return;
    }
    closesocket(c->socket);
    TableFree(c->connections);
    ArrayFree(c->closedConnections);
    GsUtil_Free(c);
    SocketShutDown();
}
} }

namespace N02285f3c { extern "C" {
void gti2Listen(Sock062 *c, gt2ConnectAttemptCallback v) {
    c->connectAttemptCallback = v;
}
} }

namespace N02285f3c { extern "C" {
void *gti2CreateConnectionObject() {
    return GsUtil_Alloc(sizeof(Conn062));
}
} }

namespace N02285f3c { extern "C" {
s32 gti2NewSocketConnection(Sock062 *c, Conn062 **out, u32 ip, u16 port) {
    Conn062 *p = NULL;
    if (gti2SocketFindConnection(c, ip, port) != 0) {
        return 5;
    }
    p = (Conn062 *)gti2CreateConnectionObject();
    if (p != 0) {
        memset(p, 0, sizeof(Conn062));
        p->ip = ip;
        p->port = port;
        p->socket = c;
        p->startTime = current_time();
        p->lastSend = p->startTime;
        p->serialNumber = 0;
        p->expectedSerialNumber = 0;
        if (gti2AllocateBuffer(&p->incomingBuffer, c->incomingBufferSize) != 0 && gti2AllocateBuffer(&p->outgoingBuffer, c->outgoingBufferSize) != 0) {
            p->incomingBufferMessages = ArrayNew(sizeof(GTI2IncomingBufferMessage), 0x40, 0);
            if (p->incomingBufferMessages != 0) {
                p->outgoingBufferMessages = ArrayNew(sizeof(GTI2OutgoingBufferMessage), 0x40, 0);
                if (p->outgoingBufferMessages != 0) {
                    p->sendFilters = ArrayNew(sizeof(GsTransportFilterCallback), 2, 0);
                    if (p->sendFilters != 0) {
                        p->receiveFilters = ArrayNew(sizeof(GsTransportFilterCallback), 2, 0);
                        if (p->receiveFilters != 0) {
                            TableEnter(c->connections, &p);
                            *out = gti2SocketFindConnection(c, ip, port);
                            if (*out != 0) {
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if (p != 0) {
        GsUtil_Free(p->incomingBuffer.buffer);
        GsUtil_Free(p->outgoingBuffer.buffer);
        if (p->incomingBufferMessages != 0) {
            ArrayFree(p->incomingBufferMessages);
        }
        if (p->outgoingBufferMessages != 0) {
            ArrayFree(p->outgoingBufferMessages);
        }
        if (p->sendFilters != 0) {
            ArrayFree(p->sendFilters);
        }
        if (p->receiveFilters != 0) {
            ArrayFree(p->receiveFilters);
        }
        GsUtil_Free(p);
    }
    return 1;
}
} }

namespace N02285f3c { extern "C" {
void gti2FreeSocketConnection(Conn062 *p) {
    if (p->freeAtAcceptReject == 0 && p->callbackLevel == 0) {
        if (p->state == 7) {
            s32 n = ArrayLength(p->socket->closedConnections);
            s32 i = 0;
            for (; i < n; i++) {
                Conn062 *q = p;
                if (q == *(Conn062 **)ArrayNth(q->socket->closedConnections, i)) {
                    ArrayDeleteAt(q->socket->closedConnections, i);
                    return;
                }
            }
        } else {
            TableRemove(p->socket->connections, &p);
        }
    }
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2SocketSend(Sock062 *c, u32 ip, u16 port, u8 *buf, s32 len) {
    Sa062 sa;
    u32 *w;
    s32 r;
    gti2MessageCheck(&buf, &len);
    if (CanSendOnSocket(c->socket) == 0) {
        return TRUE;
    }
    w = (u32 *)&sa;
    w[0] = 0;
    w[1] = 0;
    sa.family = 2;
    sa.addr = ip;
    sa.port = ((port >> 8) & 0xff) | ((port << 8) & 0xff00);
    r = sendto(c->socket, (char *)buf, len, 0, (Sa062 *)w, 8);
    if (r == -1) {
        r = GOAGetLastError(c->socket);
        if (r == -15) {
            if (gti2HandleConnectionReset(c, ip, port) == 0) {
                return FALSE;
            }
        } else if (r == -42 || r == -6) {
            return TRUE;
        } else if (r != -35) {
            gti2SocketError(c);
            return FALSE;
        }
    } else if (c->sendDumpCallback != 0) {
        Conn062 *p = gti2SocketFindConnection(c, ip, port);
        if (gti2DumpCallback(c, p, ip, port, 0, buf, len, 1) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2SocketConnectionsThinkMap(void *elem, void *arg) {
    Conn062 *p = *(Conn062 **)elem;
    u32 now = *(u32 *)arg;
    if (p->state != 7) {
        if (gti2ConnectionThink(p, now) == 0) {
            return FALSE;
        }
    }
    if (p->state == 7 && p->freeAtAcceptReject == 0 && p->callbackLevel == 0) {
        gti2FreeSocketConnection(p);
    }
    return TRUE;
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2SocketConnectionsThink(Sock062 *c) {
    u32 now = current_time();
    if (TableMapSafe2(c->connections, gti2SocketConnectionsThinkMap, &now) == 0) {
        return TRUE;
    }
    return FALSE;
}
} }

namespace N02285f3c { extern "C" {
void gti2FreeClosedConnections(Sock062 *c) {
    s32 i = ArrayLength(c->closedConnections) - 1;
    for (; i >= 0; i--) {
        gti2FreeSocketConnection(*(Conn062 **)ArrayNth(c->closedConnections, i));
    }
}
} }

namespace N02285f3c { extern "C" {
void gti2SocketError(Sock062 *c) {
    if (c->error == 0) {
        c->error = 1;
        gt2CloseAllConnectionsHard(c);
        if (gti2SocketErrorCallback(c) != 0) {
            gti2CloseSocket(c);
        }
    }
}
} }

namespace N02285f3c { extern "C" {
u32 gti2UShortFromBuffer(u8 *buf, s32 off) {
    u16 t = (buf[off] << 8) & 0xff00;
    return t | buf[off + 1];
}
} }

namespace N02285f3c { extern "C" {
void gti2UShortToBuffer(u8 *buf, s32 off, s32 v) {
    buf[off] = v >> 8;
    buf[off + 1] = v;
}
} }

namespace N02285f3c { extern "C" {
s16 gti2SNDiff(u32 a, u32 b) {
    return a - b;
}
} }

namespace N02285f3c { extern "C" {
s32 gti2ConnectionError(Conn062 *p, s32 a, s32 b) {
    s32 st = p->state;
    if (st < 5) {
        if (p->initiated != 0) {
            gti2ConnectionClosed(p);
            if (gti2ConnectedCallback(p, a, 0, 0) == 0) {
                return FALSE;
            }
        } else {
            if (st == 4) {
                p->freeAtAcceptReject = 1;
            }
            gti2ConnectionClosed(p);
        }
    } else if (st != 7) {
        gti2ConnectionClosed(p);
        if (gti2ClosedCallback(p, b) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02285f3c { extern "C" {
s32 gti2ConnectionCommunicationError(Conn062 *p) {
    return gti2ConnectionError(p, 7, 2);
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2ConnectionMemoryError(Conn062 *p) {
    if (gti2SendClosed(p) != 0) {
        return gti2ConnectionError(p, 1, 4);
    }
    return FALSE;
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2HandleESN(Conn062 *p, u32 ack) {
    s32 n, i, base;
    n = ArrayLength(p->outgoingBufferMessages);
    if (n == 0) {
        return TRUE;
    }
    for (i = 0; i < n; i++) {
        GTI2OutgoingBufferMessage *e = (GTI2OutgoingBufferMessage *)ArrayNth(p->outgoingBufferMessages, i);
        if (gti2SNDiff(e->serialNumber, ack) >= 0) {
            break;
        }
    }
    if (i == 0) {
        return TRUE;
    }
    while (i-- != 0) {
        ArrayDeleteAt(p->outgoingBufferMessages, i);
    }
    n = ArrayLength(p->outgoingBufferMessages);
    if (n == 0) {
        p->outgoingBuffer.len = 0;
        return TRUE;
    }
    base = ((GTI2OutgoingBufferMessage *)ArrayNth(p->outgoingBufferMessages, 0))->start;
    for (i = 0; i < n; i++) {
        GTI2OutgoingBufferMessage *e = (GTI2OutgoingBufferMessage *)ArrayNth(p->outgoingBufferMessages, i);
        e->start = e->start - base;
    }
    gti2BufferShorten(&p->outgoingBuffer, 0, base);
    return TRUE;
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2HandleAppUnreliable(Conn062 *p, u8 *x, s32 y) {
    if (p->state != 5 && p->state != 6) {
        return TRUE;
    }
    if (ArrayLength(p->receiveFilters) != 0) {
        if (gti2ReceiveFilterCallback(p, 0, x, y, 0) != 0) {
            return TRUE;
        }
        return FALSE;
    }
    if (gti2ReceivedCallback(p, x, y, 0) != 0) {
        return TRUE;
    }
    return FALSE;
}
} }

namespace N02285f3c { extern "C" {
BOOL gti2HandleAppReliable(Conn062 *p, u8 *x, s32 y) {
    if (p->state != 5 && p->state != 6) {
        if (gti2ConnectionCommunicationError(p) == 0) {
            return FALSE;
        }
    } else {
        if (ArrayLength(p->receiveFilters) != 0) {
            if (gti2ReceiveFilterCallback(p, 0, x, y, 1) != 0) {
                return TRUE;
            }
            return FALSE;
        }
        if (gti2ReceivedCallback(p, x, y, 1) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleClientChallenge(Cn *c, u8 *p, s32 n)
{
    u8 a[0x20];
    u8 b[0x20];
    if (c->state != 2) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (n < 0x20) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    gti2GetResponse(a, p);
    gti2GetChallenge(b);
    gti2GetResponse(c->response, b);
    if (gti2SendServerChallenge(c, a, b) == 0) return FALSE;
    c->state = 3;
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleServerChallenge(Cn *c, u8 *p, s32 n)
{
    u8 buf[0x20];
    if (c->state != 0) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (n < 0x40) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (gti2CheckResponse(p, c->response) == 0) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    gti2GetResponse(buf, p + 0x20);
    if (gti2SendClientResponse(c, buf, c->initialMessage, c->initialMessageLen) == 0) return FALSE;
    if (c->initialMessage != 0) {
        GsUtil_Free(c->initialMessage);
        c->initialMessage = 0;
    }
    c->state = 1;
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleClientResponse(Cn *c, u8 *p, s32 n)
{
    if (c->state != 3) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (n < 0x20) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (gti2CheckResponse(p, c->response) == 0) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (c->socket->connectAttemptCallback == 0) {
        if (gti2SendClosed(c) == 0) return FALSE;
        gti2ConnectionClosed(c);
        return TRUE;
    }
    c->state = 4;
    if (gti2ConnectAttemptCallback(c->socket, c, c->ip, c->port, current_time() - c->challengeTime, (u8 *)p + 0x20, n - 0x20) != 0) return TRUE;
    return FALSE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleAccept(Cn *c)
{
    if (c->state != 1) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    c->state = 5;
    if (gti2ConnectedCallback(c, 0, 0, 0) != 0) return TRUE;
    return FALSE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleReject(Cn *c, u8 *p, s32 n)
{
    if (c->state != 1) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    gti2ConnectionClosed(c);
    if (gti2SendClosed(c) == 0) return FALSE;
    if (gti2ConnectedCallback(c, 2, p, n) != 0) return TRUE;
    return FALSE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleClose(Cn *c)
{
    if (gti2SendClosed(c) == 0) return FALSE;
    s32 f;
    switch (c->state) { case 6: f = 0; break; default: f = 1; break; }
    if (gti2ConnectionError(c, 2, f) == 0) return FALSE;
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2DeliverReliableMessage(Cn *c, s32 mode, u8 *p, s32 n)
{
    c->expectedSerialNumber = c->expectedSerialNumber + 1;
    if (mode == 0) {
        if (gti2HandleAppReliable(c, p, n) == 0) return FALSE;
    } else if (mode == 1) {
        if (gti2HandleClientChallenge(c, p, n) == 0) return FALSE;
    } else if (mode == 2) {
        if (gti2HandleServerChallenge(c, p, n) == 0) return FALSE;
    } else if (mode == 3) {
        if (gti2HandleClientResponse(c, p, n) == 0) return FALSE;
    } else if (mode == 4) {
        if (gti2HandleAccept(c) == 0) return FALSE;
    } else if (mode == 5) {
        if (gti2HandleReject(c, p, n) == 0) return FALSE;
    } else if (mode == 6) {
        if (gti2HandleClose(c) == 0) return FALSE;
    }
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
s32 gti2IncomingBufferMessageCompare(void *a, void *b)
{
    return gti2SNDiff(((It *)a)->serialNumber, ((It *)b)->serialNumber);
}
} }

namespace N02285630 { extern "C" {
BOOL gti2BufferIncomingMessage(Cn *c, s32 a, u32 seq, u8 *p, s32 n, s32 *out)
{
    s32 cnt = ArrayLength(c->incomingBufferMessages);
    s32 i;
    It rec;
    for (i = 0; i < cnt; i++) {
        It *q = (It *)ArrayNth(c->incomingBufferMessages, i);
        if (q->serialNumber == seq) {
            *out = 0;
            return TRUE;
        }
        if (gti2SNDiff(q->serialNumber, seq) > 0) break;
    }
    if (gti2GetBufferFreeSpace(&c->incomingBuffer) < n) {
        *out = 1;
        return TRUE;
    }
    rec.start = c->incomingBuffer.len;
    rec.len = n;
    rec.type = a;
    rec.serialNumber = seq;
    ArrayInsertSorted(c->incomingBufferMessages, &rec, gti2IncomingBufferMessageCompare);
    if (cnt + 1 != ArrayLength(c->incomingBufferMessages)) {
        *out = 1;
        return TRUE;
    }
    gti2BufferWriteData(&c->incomingBuffer, p, n);
    if (cnt == 0) {
        if (gti2SendNack(c, c->expectedSerialNumber, seq - 1) == 0) return FALSE;
    } else {
        It *q = (It *)ArrayNth(c->incomingBufferMessages, cnt);
        if (q->serialNumber == seq) {
            It *r = (It *)ArrayNth(c->incomingBufferMessages, cnt - 1);
            if ((u16)gti2SNDiff(seq, r->serialNumber) > 1) {
                if (gti2SendNack(c, r->serialNumber + 1, seq - 1) == 0) return FALSE;
            }
        }
    }
    *out = 0;
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
void gti2RemoveHoldMessage(Cn *c, It *e, s32 idx)
{
    s32 mx = 0;
    s32 start = e->start;
    s32 len = e->len;
    s32 n;
    s32 i;
    ArrayDeleteAt(c->incomingBufferMessages, idx);
    n = ArrayLength(c->incomingBufferMessages);
    for (i = 0; i < n; i++) {
        It *q = (It *)ArrayNth(c->incomingBufferMessages, i);
        if (q->start > start) {
            q->start = q->start - len;
            {
                s32 t = q->start + q->len;
                if (mx <= t) mx = t;
            }
        }
    }
    gti2BufferShorten(&c->incomingBuffer, start, len);
}
} }

namespace N02285630 { extern "C" {
BOOL gti2DeliverHoldMessages(Cn *c)
{
    s32 i;
    It *e;
again:
    i = ArrayLength(c->incomingBufferMessages) - 1;
    while (i >= 0) {
        e = (It *)ArrayNth(c->incomingBufferMessages, i);
        if (e->serialNumber == c->expectedSerialNumber) {
            if (gti2DeliverReliableMessage(c, e->type, c->incomingBuffer.buffer + e->start, e->len) == 0) return FALSE;
            gti2RemoveHoldMessage(c, e, i);
            goto again;
        }
        i--;
    }
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
void gti2SetPendingAck(Cn *c)
{
    if (c->pendingAck == 0) {
        c->pendingAck = 1;
        c->pendingAckTime = current_time();
    }
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleReliableMessage(Cn *c, s32 a, u8 *p, s32 n)
{
    u32 v;
    if (n < 7) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    v = gti2UShortFromBuffer(p, 3);
    if (gti2HandleESN(c, gti2UShortFromBuffer(p, 5)) == 0) return FALSE;
    if (v == c->expectedSerialNumber) {
        gti2SetPendingAck(c);
        if (gti2DeliverReliableMessage(c, a, (u8 *)p + 7, n - 7) == 0) return FALSE;
        if (gti2DeliverHoldMessages(c) != 0) return TRUE;
        return FALSE;
    }
    if (gti2SNDiff(v, c->expectedSerialNumber) < 0) {
        gti2SetPendingAck(c);
        return TRUE;
    }
    {
        s32 flag;
        if (gti2BufferIncomingMessage(c, a, v, (u8 *)p + 7, n - 7, &flag) == 0) return FALSE;
        if (flag != 0) {
            if (gti2ConnectionMemoryError(c) == 0) return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleAck(Cn *c, u8 *p, s32 n)
{
    if (n != 2) {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    if (gti2HandleESN(c, gti2UShortFromBuffer(p, 0)) != 0) return TRUE;
    return FALSE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleNack(Cn *c, u8 *p, s32 n)
{
    s32 lo = gti2UShortFromBuffer(p, 0);
    s32 hi;
    s32 cnt;
    s32 i;
    if (n == 2) {
        hi = lo;
    } else if (n == 4) {
        hi = gti2UShortFromBuffer(p, 2);
    } else {
        if (gti2ConnectionCommunicationError(c) != 0) return TRUE;
        return FALSE;
    }
    cnt = ArrayLength(c->outgoingBufferMessages);
    for (i = 0; i < cnt; i++) {
        GTI2OutgoingBufferMessage *e = (GTI2OutgoingBufferMessage *)ArrayNth(c->outgoingBufferMessages, i);
        if (gti2SNDiff(e->serialNumber, lo) >= 0 && gti2SNDiff(e->serialNumber, hi) <= 0) {
            if (gti2ResendMessage(c, e) == 0) return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
s32 gti2HandlePing(Cn *c, u8 *p, s32 n)
{
    return gti2SendPong(c, p, n);
}
} }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02285778) {
    HOST_OVERLAY_VAR(data_ov065_02291504),
    HOST_OVERLAY_VAR(data_ov065_02291508),
    HOST_OVERLAY_VARS_END
};
