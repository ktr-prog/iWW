#include "uptr.h"

#include "types.h"
#include "net/darray.h"
#include "net/gt2Main.h"
#include "net/GsBytes.h"
#include "net/gsPlatformUtil.h"
#include "net/SockAddrIn.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_02283720.h"
#include "proto/ov065/unk_ov065_02283f34.h"
#include "proto/ov065/unk_ov065_02285778.h"
#include "proto/ov065/unk_ov065_02278328.h"
#include "proto/ov065/unk_ov065_022789fc.h"

extern "C" {
void gti2CloseSocket(GTI2Socket *c);
BOOL gti2SocketSend(GTI2Socket *c, u32 ip, u16 port, u8 *buf, s32 len);
}

extern "C" { u8 data_ov065_0228e14c[4] = {0xfe, 0xfe, 0, 0}; }



namespace N022838c4 {
extern "C" {






extern "C" {
extern DArrayImplementation *serverreqs;
extern char data_ov065_0228e128[];
extern char data_ov065_0228e108[];

s32 strncmp(const char *, const char *, u32);

s32 CanReceiveOnSocket(s32);

s32 gti2VerifyChallenge(u8 *);



























}

}
}

namespace N02284240 {
extern "C" {



namespace Unk_ov065_02284a80_Ns {
extern "C" s32 gti2NewOutgoingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port);
}

extern "C" {
extern void msleep(s32);

extern s32 gti2FreeSocketConnection(void *);
extern s32 gti2NewSocketConnection(void *, void *, u32, u32);

extern s32 gti2SendPing(GTI2Connection *);

s32 gti2ReceiveFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel);
s32 gti2SendFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel);
s32 gti2ClosedCallback(GTI2Connection *c, s32 a);
void gti2CloseConnection(GTI2Connection *c, s32 x);
s32 gti2CheckKeepAlive(GTI2Connection *c, u32 t);
s32 gti2CheckPendingAck(GTI2Connection *c, u32 t);
s32 gti2SendRetries(GTI2Connection *c, u32 t);
s32 gti2CheckTimeout(GTI2Connection *c, u32 t);
s32 gti2ConnectionSendData(GTI2Connection *c, u8 *a, s32 b);
s32 gti2StartConnectionAttempt(GTI2Connection *c, u8 *msg, s32 len, GsTransportConnCallbacks *x);
s32 gti2NewOutgoingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port);
void gt2CloseConnectionHard(GTI2Connection *c);



































}

}
}

namespace N02284b8c {
extern "C" {





extern "C" {
extern u8 data_ov065_0228e14c[];



void gti2RejectConnection(GTI2Connection *, u8 *, s32);
void gti2Listen(GTI2Socket *, gt2ConnectAttemptCallback callback);
s32 gti2SocketConnectionsThink(GTI2Socket *);
s32 gti2FreeClosedConnections(GTI2Socket *);
s32 gti2SocketError(GTI2Socket *);
void gt2CloseAllConnectionsHard(GTI2Socket *);
s32 gti2CreateSocket(GTI2Socket **, char *, u32, u32, gt2SocketErrorCallback);
s32 gti2ConnectionSendData(GTI2Connection *, u8 *, s32);
s32 gti2ConnectionMemoryError(GTI2Connection *);
s32 CanReceiveOnSocket(s32);
GTI2Connection *gti2SocketFindConnection(GTI2Socket *, s32, s32);
s32 gti2DumpCallback(GTI2Socket *, GTI2Connection *, s32, s32, s32, u8 *, s32, s32);
s32 gti2UnrecognizedMessageCallback(GTI2Socket *, s32, s32, u8 *, s32, s32 *);
s32 gti2ConnectionError(GTI2Connection *, s32, s32);
s32 gti2HandleAppUnreliable(GTI2Connection *, u8 *, s32);
s32 gti2ConnectionCommunicationError(GTI2Connection *);
s32 gti2HandleReliableMessage(GTI2Connection *, s32, u8 *, s32);
s32 gti2HandleUnreliableMessage(GTI2Connection *, s32, u8 *, s32);

s32 gti2SendClosedOnSocket(GTI2Socket *, s32, s32);
s32 gti2BeginReliableMessage(GTI2Connection *, u32, s32, s32 *);
s32 gti2EndReliableMessage(GTI2Connection *);
s32 gti2StoreOutgoingReliableMessageInfo(GTI2Connection *, u32, s32);
s32 gti2ReceiveMessages(GTI2Socket *);
s32 gti2HandleConnectionReset(GTI2Socket *, s32, u32);
s32 gti2HandleMessage(GTI2Socket *, u8 *, s32, s32, s32);
s32 gti2SendAppReliable(GTI2Connection *, u8 *, s32);
s32 gti2SendAppUnreliable(GTI2Connection *, u8 *, s32);



























static inline u16 Swap16(u16 p) {
    return ((p >> 8) & 0xff) | ((p << 8) & 0xff00);
}



}

}
}

namespace N02285630 {
extern "C" {










extern "C" {

s32 gti2PingCallback(GTI2Connection *, s32);
s32 gti2ConnectionMemoryError(GTI2Connection *);
s32 gti2ConnectionCommunicationError(GTI2Connection *);
s32 gti2ConnectionError(GTI2Connection *, s32, s32);
s32 gti2HandleESN(GTI2Connection *, s32);

s32 gti2HandleAck(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleNack(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandlePing(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandlePong(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleClosed(GTI2Connection *c);
void gti2SetPendingAck(GTI2Connection *c);
s32 gti2DeliverHoldMessages(GTI2Connection *c);
void gti2RemoveHoldMessage(GTI2Connection *c, GTI2IncomingBufferMessage *e, s32 i);
s32 gti2BufferIncomingMessage(GTI2Connection *c, s32 a, u32 seq, u8 *p, s32 n, s32 *out);
s32 gti2IncomingBufferMessageCompare(GTI2IncomingBufferMessage *a, GTI2IncomingBufferMessage *b);
s32 gti2DeliverReliableMessage(GTI2Connection *c, s32 mode, u8 *p, s32 n);
s32 gti2HandleClose(GTI2Connection *c);
s32 gti2HandleReject(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleAccept(GTI2Connection *c);
s32 gti2HandleClientResponse(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleServerChallenge(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleClientChallenge(GTI2Connection *c, u8 *p, s32 n);
s32 gti2HandleAppReliable(GTI2Connection *c, u8 *p, s32 n);



















}

}
}

namespace N02285630 { extern "C" {
BOOL gti2HandlePong(GTI2Connection *c, u8 *p, s32 n)
{
    GsBytes4 t;
    s32 now;
    if (c->pingCallback == 0) return TRUE;
    if (n != 8) return TRUE;
    if (memcmp(p, (u8 *)"time", 4) != 0) return TRUE;
    GsBytes4 *a = &t;
    GsBytes4 *q = (GsBytes4 *)(p + 4);
    a->b[0] = q->b[0];
    a->b[1] = q->b[1];
    a->b[2] = q->b[2];
    a->b[3] = q->b[3];
    now = ((s32 (*)(void *))current_time)(a);
    if (gti2PingCallback(c, now - *(s32 *)&t) != 0) return TRUE;
    return FALSE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleClosed(GTI2Connection *c)
{
    if (c->state == 7) return TRUE;
    s32 f;
    switch (c->state) { case 6: f = 0; break; default: f = 1; break; }
    if (gti2ConnectionError(c, 2, f) == 0) return FALSE;
    return TRUE;
}
} }

namespace N02285630 { extern "C" {
BOOL gti2HandleUnreliableMessage(GTI2Connection *c, s32 t, u8 *a, s32 b)
{
    u8 *x = a + 3;
    s32 y = b - 3;
    if (t == 100) {
        if (gti2HandleAck(c, x, y) == 0) return FALSE;
    } else if (t == 101) {
        if (gti2HandleNack(c, x, y) == 0) return FALSE;
    } else if (t == 102) {
        if (gti2HandlePing(c, a, b) == 0) return FALSE;
    } else if (t == 103) {
        if (gti2HandlePong(c, x, y) == 0) return FALSE;
    } else if (t == 104) {
        if (gti2HandleClosed(c) == 0) return FALSE;
    }
    return TRUE;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2HandleMessage(GTI2Socket *s, u8 *data, s32 n, s32 addr, s32 port) {
    GTI2Connection *c = gti2SocketFindConnection(s, addr, port);
    s32 flag;
    s32 out;
    if (s->receiveDumpCallback != 0) {
        if (gti2DumpCallback(s, c, addr, port, 0, data, n, 0) == 0) {
            return 0;
        }
    }
    if (n > 2 && memcmp(data, data_ov065_0228e14c, 2) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (c == 0) {
        if (gti2UnrecognizedMessageCallback(s, addr, port, data, n, &out) == 0) {
            return 0;
        }
        if (out != 0) {
            return 1;
        }
        if (!(flag != 0 && data[2] == 1)) {
            if (flag == 0 || data[2] != 0x68) {
                if (gti2SendClosedOnSocket(s, addr, port) == 0) {
                    return 0;
                }
            }
            return 1;
        } else {
            if (s->connectAttemptCallback == 0) {
                return 1;
            }
            s32 r = gti2NewIncomingConnection(s, &c, addr, port);
            if (r != 0) {
                if (r != 5) {
                    if (gti2SendClosedOnSocket(s, addr, port) == 0) {
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    GTI2Connection *k = c;
    if (k->state == 7) {
        if (flag == 0 || data[2] != 0x68) {
            if (gti2SendClosed(k) == 0) {
                return 0;
            }
        }
        return 1;
    }
    if (flag != 0 && n >= 4 && memcmp(data + 2, data_ov065_0228e14c, 2) == 0) {
        data += 2;
        n -= 2;
        flag = 0;
    }
    if (flag == 0) {
        if (gti2HandleAppUnreliable(k, data, n) != 0) {
            return 1;
        }
        return 0;
    }
    s32 t = data[2];
    if (t < 0) {
        if (gti2ConnectionCommunicationError(k) != 0) {
            return 1;
        }
        return 0;
    }
    if (t < 8) {
        if (gti2HandleReliableMessage(k, t, data, n) != 0) {
            return 1;
        }
        return 0;
    }
    if (gti2HandleUnreliableMessage(k, t, data, n) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2HandleConnectionReset(GTI2Socket *s, s32 addr, u32 port) {
    GTI2Connection *c = gti2SocketFindConnection(s, addr, port);
    if (s->receiveDumpCallback != 0) {
        if (gti2DumpCallback(s, c, addr, port, 1, 0, 0, 0) == 0) {
            return 0;
        }
    }
    if (c == 0) {
        return 1;
    }
    if (c->state == 0) {
        if (c->timeout == 0 || (u32)(current_time() - c->startTime) < c->timeout) {
            return 1;
        }
        if (gti2ConnectionError(c, 6, 1) == 0) {
            return 0;
        }
    } else {
        if (gti2ConnectionError(c, 2, 1) == 0) {
            return 0;
        }
    }
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2ReceiveMessages(GTI2Socket *s) {
    SockAddrIn a;
    s32 len;
    u8 buf[0x5dc];
    if (CanReceiveOnSocket(s->socket) != 0) {
        do {
            len = 8;
            s32 n = recvfrom(s->socket, buf, 0x5dc, 0, &a, &len);
            s32 m = -1;
            if (n == m) {
                s32 e = GOAGetLastError(s->socket);
                if (e == -15) {
                    if (gti2HandleConnectionReset(s, a.addr, Swap16(a.port)) == 0) {
                        return 0;
                    }
                } else if (e != -35) {
                    gti2SocketError(s);
                    return 0;
                }
            } else {
                if (gti2HandleMessage(s, buf, n, a.addr, Swap16(a.port)) == 0) {
                    return 0;
                }
            }
        } while (CanReceiveOnSocket(s->socket) != 0);
    }
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2StoreOutgoingReliableMessageInfo(GTI2Connection *o, u32 seq, s32 need) {
    GTI2OutgoingBufferMessage r = {0, 0, 0, 0};
    r.start = o->outgoingBuffer.len;
    r.len = need;
    *(u16 *)&r.serialNumber = seq;
    r.lastSend = current_time();
    s32 c = ArrayLength(o->outgoingBufferMessages);
    ArrayAppend(o->outgoingBufferMessages, &r);
    if (c + 1 == ArrayLength(o->outgoingBufferMessages)) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2BeginReliableMessage(GTI2Connection *o, u32 type, s32 need, s32 *out) {
    if (gti2GetBufferFreeSpace(&o->outgoingBuffer) < need) {
        if (gti2ConnectionMemoryError(o) == 0) {
            return 0;
        }
        *out = 1;
        return 1;
    }
    if (gti2StoreOutgoingReliableMessageInfo(o, o->serialNumber, need) == 0) {
        if (gti2ConnectionMemoryError(o) == 0) {
            return 0;
        }
        *out = 1;
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, data_ov065_0228e14c, 2);
    gti2BufferWriteByte(&o->outgoingBuffer, (u8)type);
    s32 seq = o->serialNumber;
    o->serialNumber = *(volatile u16 *)&o->serialNumber + 1;
    gti2BufferWriteUShort(&o->outgoingBuffer, seq);
    gti2BufferWriteUShort(&o->outgoingBuffer, o->expectedSerialNumber);
    *out = 0;
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2EndReliableMessage(GTI2Connection *o) {
    s32 c = ArrayLength(o->outgoingBufferMessages);
    s32 *it = (s32 *)ArrayNth(o->outgoingBufferMessages, c - 1);
    if (gti2ConnectionSendData(o, o->outgoingBuffer.buffer + it[0], it[1]) == 0) {
        return 0;
    }
    o->pendingAck = 0;
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendAppReliable(GTI2Connection *o, u8 *a, s32 n) {
    s32 r;
    if (gti2BeginReliableMessage(o, 0, n + 7, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, a, n);
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendClientChallenge(GTI2Connection *o, u8 *a) {
    s32 r;
    if (gti2BeginReliableMessage(o, 1, 0x27, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, a, 0x20);
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendServerChallenge(GTI2Connection *o, u8 *a, u8 *b) {
    s32 r;
    if (gti2BeginReliableMessage(o, 2, 0x47, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, a, 0x20);
    gti2BufferWriteData(&o->outgoingBuffer, b, 0x20);
    if (gti2EndReliableMessage(o) == 0) {
        return 0;
    }
    o->challengeTime = o->lastSend;
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendClientResponse(GTI2Connection *o, u8 *a, u8 *b, s32 n) {
    s32 r;
    if (gti2BeginReliableMessage(o, 3, n + 0x27, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, a, 0x20);
    gti2BufferWriteData(&o->outgoingBuffer, b, n);
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendAccept(GTI2Connection *o) {
    s32 r;
    if (gti2BeginReliableMessage(o, 4, 7, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendReject(GTI2Connection *o, u8 *a, s32 n) {
    s32 r;
    if (gti2BeginReliableMessage(o, 5, n + 7, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    gti2BufferWriteData(&o->outgoingBuffer, a, n);
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendClose(GTI2Connection *o) {
    s32 r;
    if (gti2BeginReliableMessage(o, 6, 7, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendKeepAlive(GTI2Connection *o) {
    s32 r;
    if (gti2BeginReliableMessage(o, 7, 7, &r) == 0) {
        return 0;
    }
    if (r != 0) {
        return 1;
    }
    if (gti2EndReliableMessage(o) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendAppUnreliable(GTI2Connection *o, u8 *data, s32 n) {
    u8 *t;
    s32 total;
    if (n < 2 || memcmp(data, data_ov065_0228e14c, 2) != 0) {
        if (gti2ConnectionSendData(o, data, n) == 0) {
            return 0;
        }
        return 1;
    }
    total = n + 2;
    if (gti2GetBufferFreeSpace(&o->outgoingBuffer) < total) {
        return 1;
    }
    t = o->outgoingBuffer.buffer + o->outgoingBuffer.len;
    gti2BufferWriteData(&o->outgoingBuffer, data_ov065_0228e14c, 2);
    gti2BufferWriteData(&o->outgoingBuffer, data, n);
    if (gti2ConnectionSendData(o, t, total) == 0) {
        return 0;
    }
    gti2BufferShorten(&o->outgoingBuffer, -1, total);
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendAck(GTI2Connection *o) {
    u8 buf[5];
    u8 *const p = buf;
    const u8 *const s = data_ov065_0228e14c;
    p[0] = s[0];
    p[1] = s[1];
    buf[2] = 0x64;
    gti2UShortToBuffer(buf, 3, o->expectedSerialNumber);
    if (gti2ConnectionSendData(o, buf, 5) == 0) {
        return 0;
    }
    o->pendingAck = 0;
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendNack(GTI2Connection *o, s32 a, s32 b) {
    u8 buf[8];
    s32 n = 0;
    u8 *const p = buf;
    const u8 *const s = data_ov065_0228e14c;
    p[0] = s[0];
    p[1] = s[1];
    buf[2] = 0x65;
    gti2UShortToBuffer(buf, 3, a);
    n += 5;
    if (a != b) {
        gti2UShortToBuffer(buf, n, b);
        n += 2;
    }
    if (gti2ConnectionSendData(o, buf, n) == 0) {
        return 0;
    }
    return 1;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendPing(GTI2Connection *o) {
    u32 t;
    u8 buf[11];
    u8 *const p = buf;
    const u8 *const s = data_ov065_0228e14c;
    p[0] = s[0];
    p[1] = s[1];
    buf[2] = 0x66;
    u8 *const q = buf + 3;
    const u8 *const r = (u8 *)"time";
    q[0] = r[0];
    q[1] = r[1];
    q[2] = r[2];
    q[3] = r[3];
    t = current_time();
    u8 *const x = buf + 7;
    const u8 *const y = (u8 *)&t;
    x[0] = y[0];
    x[1] = y[1];
    x[2] = y[2];
    x[3] = y[3];
    if (gti2ConnectionSendData(o, buf, 11) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendPong(GTI2Connection *o, u8 *b, s32 n) {
    b[2] = 0x67;
    return gti2ConnectionSendData(o, b, n);
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendClosed(GTI2Connection *o) {
    return gti2SendClosedOnSocket(o->socket, o->ip, o->port);
}
} }

namespace N02284b8c { extern "C" {
s32 gti2SendClosedOnSocket(GTI2Socket *a, s32 b, s32 c) {
    u8 buf[3];
    u8 *const p = buf;
    const u8 *const s = data_ov065_0228e14c;
    p[0] = s[0];
    p[1] = s[1];
    buf[2] = 0x68;
    if (gti2SocketSend(a, b, c, buf, 3) != 0) {
        return 1;
    }
    return 0;
}
} }

namespace N02284b8c { extern "C" {
s32 gti2ResendMessage(GTI2Connection *o, GTI2OutgoingBufferMessage *m) {
    gti2UShortToBuffer(o->outgoingBuffer.buffer, m->start + 5, o->expectedSerialNumber);
    if (gti2ConnectionSendData(o, o->outgoingBuffer.buffer + m->start, m->len) == 0) {
        return 0;
    }
    m->lastSend = o->lastSend;
    if (o->outgoingBuffer.buffer[m->start + 2] == 2) {
        o->challengeTime = o->lastSend;
    }
    return 1;
}
} }

namespace N02284b8c { extern "C" {
void gti2Send(GTI2Connection *o, u8 *a, s32 b, s32 mode) {
    if (mode != 0) {
        gti2SendAppReliable(o, a, b);
    } else {
        gti2SendAppUnreliable(o, a, b);
    }
}
} }

namespace N02284b8c { extern "C" {
s32 gt2CreateSocket(GTI2Socket **a, char *b, s32 c, s32 d, gt2SocketErrorCallback e) {
    return gti2CreateSocket(a, b, c, d, e);
}
} }

namespace N02284b8c { extern "C" {
void gt2CloseSocket(GTI2Socket *o) {
    gt2CloseAllConnectionsHard(o);
    gti2CloseSocket(o);
}
} }

namespace N02284b8c { extern "C" {
void gt2Think(GTI2Socket *s) {
    if (gti2ReceiveMessages(s) != 0) {
        if (gti2SocketConnectionsThink(s) != 0) {
            gti2FreeClosedConnections(s);
        }
    }
}
} }

namespace N02284b8c { extern "C" {
void gt2Listen(GTI2Socket *p, gt2ConnectAttemptCallback callback) {
    gti2Listen(p, callback);
}
} }

namespace N02284b8c { extern "C" {
s32 gt2Accept(GTI2Connection *o, GsTransportConnCallbacks *x) {
    return gti2AcceptConnection(o, x);
}
} }

namespace N02284b8c { extern "C" {
void gt2Reject(GTI2Connection *o, u8 *a, s32 b) {
    return gti2RejectConnection(o, a, b);
}
} }

namespace N02284240 { extern "C" {
s32 gt2Connect(GTI2Socket *s, GTI2Connection **out, char *host, u8 *p3, s32 p4, s32 p5, GsTransportConnCallbacks *p6, s32 p7)
{
    u32 port;
    u16 port16;
    GTI2Connection *conn;
    u32 ip;
    s32 r;

    if (gt2StringToAddress(host, &ip, &port16) == 0 || ip == 0 || (port = port16) == 0) {
        return 4;
    }
    u32 sw = ((ip << 24) & 0xff000000) | (((ip << 8) & 0xff0000) | (((ip >> 24) & 0xff) | ((ip >> 8) & 0xff00)));
    if ((sw & 0xe0000000) == 0xe0000000) {
        return 4;
    }
    r = gti2NewOutgoingConnection(s, &conn, ip, port);
    if (r != 0) {
        return r;
    }
    conn->timeout = p5;
    r = gti2StartConnectionAttempt(conn, p3, p4, p6);
    if (r != 0) {
        gti2FreeSocketConnection(conn);
        return r;
    }
    if (p7 == 0) {
        if (out != NULL) {
            *out = conn;
        }
        return 0;
    }
    conn->callbackLevel++;
    BOOL one = TRUE;
    BOOL done;
    do {
        gt2Think(s);
        if (conn->state >= 5) {
            done = one;
        } else {
            done = FALSE;
        }
        if (done == 0) {
            msleep(one);
        }
    } while (done == 0);
    conn->callbackLevel--;
    if (conn->state == 5) {
        *out = conn;
    }
    return conn->connectionResult;
}
} }

namespace N02284240 { extern "C" {
void gt2Send(GTI2Connection *c, u8 *msg, s32 len, s32 p3)
{
    if (c->state == 5) {
        gti2MessageCheck(&msg, &len);
        if (ArrayLength(c->sendFilters) != 0) {
            gti2SendFilterCallback(c, 0, msg, len, p3);
        } else {
            gti2Send(c, msg, len, p3);
        }
    }
}
} }

namespace N02284240 { extern "C" {
s32 gt2Ping(GTI2Connection *c)
{
    return gti2SendPing(c);
}
} }

namespace N02284240 { extern "C" {
void gt2CloseConnectionHard(GTI2Connection *c)
{
    gti2CloseConnection(c, 1);
}
} }

namespace N02284240 { extern "C" {
s32 gti2CloseAllConnectionsHardMap(void *elem, void *arg)
{
    gt2CloseConnectionHard(*(GTI2Connection **)elem);
    return 1;
}
} }

namespace N02284240 { extern "C" {
void gt2CloseAllConnectionsHard(GTI2Socket *s)
{
    TableMapSafe(s->connections, gti2CloseAllConnectionsHardMap, NULL);
}
} }

namespace N02284240 { extern "C" {
s32 gt2GetConnectionState(GTI2Connection *c)
{
    s32 s = c->state;
    if (s < 5) {
        return 0;
    }
    if (s == 5) {
        return 1;
    }
    if (s == 6) {
        return 2;
    }
    return 3;
}
} }

namespace N02284240 { extern "C" {
u32 gt2GetLocalPort(GTI2Socket *c)
{
    return c->port;
}
} }

namespace N02284240 { extern "C" {
s32 gt2GetOutgoingBufferFreeSpace(GTI2Connection *c)
{
    return c->outgoingBuffer.size - c->outgoingBuffer.len;
}
} }

namespace N02284240 { extern "C" {
s32 gt2GetRemoteIP(GTI2Connection *c)
{
    return c->ip;
}
} }

namespace N02284240 { extern "C" {
void gt2SetUnrecognizedMessageCallback(GTI2Socket *c, gt2UnrecognizedMessageCallback v)
{
    c->unrecognizedMessageCallback = v;
}
} }

namespace N02284240 { extern "C" {
void gt2SetConnectionData(GTI2Connection *c, void *v)
{
    c->data = v;
}
} }

namespace N02284240 { extern "C" {
void *gt2GetConnectionData(GTI2Connection *c)
{
    return c->data;
}
} }

namespace N02284240 { extern "C" {
s32 gti2NewOutgoingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port)
{
    s32 r = gti2NewSocketConnection(s, pc, ip, port);
    if (r != 0) {
        return r;
    }
    (*pc)->state = 0;
    (*pc)->initiated = 1;
    return 0;
}
} }

namespace N02284240 { extern "C" {
s32 gti2NewIncomingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port)
{
    s32 r = gti2NewSocketConnection(s, pc, ip, port);
    if (r != 0) {
        return r;
    }
    (*pc)->state = 2;
    (*pc)->initiated = 0;
    return 0;
}
} }

namespace N02284240 { extern "C" {
s32 gti2StartConnectionAttempt(GTI2Connection *c, u8 *msg, s32 len, GsTransportConnCallbacks *x)
{
    GsTransportChallengeBuf buf;
    gti2MessageCheck(&msg, &len);
    if (len > 0) {
        c->initialMessage = (u8 *)GsUtil_Alloc(len);
        if (c->initialMessage == NULL) {
            return TRUE;
        }
        memcpy(c->initialMessage, msg, len);
        c->initialMessageLen = len;
    }
    if (x != NULL) {
        c->connectedCallback = x->connected;
        c->receivedCallback = x->received;
        c->closedCallback = x->closed;
        c->pingCallback = x->ping;
    }
    gti2GetChallenge(buf.bytes);
    gti2GetResponse(c->response, buf.bytes);
    gti2SendClientChallenge(c, buf.bytes);
    c->state = 0;
    return FALSE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2AcceptConnection(GTI2Connection *c, GsTransportConnCallbacks *x)
{
    if (c->freeAtAcceptReject != 0) {
        c->freeAtAcceptReject = 0;
        return FALSE;
    }
    s32 z = 0;
    c->freeAtAcceptReject = z;
    if (c->state != 4) {
        return z;
    }
    gti2SendAccept(c);
    c->state = 5;
    if (x != NULL) {
        *(GsTransportConnCallbacks *)&c->connectedCallback = *x;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
void gti2RejectConnection(GTI2Connection *c, u8 *msg, s32 len)
{
    c->freeAtAcceptReject = 0;
    if (c->state == 4) {
        gti2MessageCheck(&msg, &len);
        gti2SendReject(c, msg, len);
        c->state = 6;
    }
}
} }

namespace N02284240 { extern "C" {
s32 gti2ConnectionSendData(GTI2Connection *c, u8 *a, s32 b)
{
    if (gti2SocketSend(c->socket, c->ip, c->port, a, b) == 0) {
        return FALSE;
    }
    c->lastSend = current_time();
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2CheckTimeout(GTI2Connection *c, u32 t)
{
    if (c->state < 5) {
        BOOL r = FALSE;
        if (c->initiated != 0) {
            u32 to = c->timeout;
            if (to != 0) {
                if (t - c->startTime > to) {
                    r = TRUE;
                }
            }
        } else if (c->state < 4) {
            if (t - c->startTime > 60000) {
                r = TRUE;
            }
        }
        if (r != 0) {
            gti2SendClosed(c);
            gti2ConnectionClosed(c);
            if (gti2ConnectedCallback(c, 6, 0, 0) == 0) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2SendRetries(GTI2Connection *c, u32 t)
{
    s32 n = ArrayLength(c->outgoingBufferMessages);
    s32 i;
    for (i = 0; i < n; i++) {
        GTI2OutgoingBufferMessage *e = (GTI2OutgoingBufferMessage *)ArrayNth(c->outgoingBufferMessages, i);
        u32 d = t - e->lastSend;
        if (d > 1000) {
            if (gti2ResendMessage(c, e) == 0) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2CheckPendingAck(GTI2Connection *c, u32 t)
{
    if (c->pendingAck == 0) {
        return TRUE;
    }
    u32 d = t - c->pendingAckTime;
    if (d > 100) {
        if (gti2SendAck(c) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2CheckKeepAlive(GTI2Connection *c, u32 t)
{
    u32 d = t - c->lastSend;
    if (d > 30000) {
        if (gti2SendKeepAlive(c) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ConnectionThink(GTI2Connection *c, u32 t)
{
    if (gti2CheckTimeout(c, t) == 0) {
        return FALSE;
    }
    if (gti2CheckKeepAlive(c, t) == 0) {
        return FALSE;
    }
    if (gti2SendRetries(c, t) == 0) {
        return FALSE;
    }
    if (gti2CheckPendingAck(c, t) != 0) {
        return TRUE;
    }
    return FALSE;
}
} }

namespace N02284240 { extern "C" {
void gti2CloseConnection(GTI2Connection *c, s32 x)
{
    if (x != 0) {
        if (c->state < 7) {
            gti2ConnectionClosed(c);
            gti2SendClosed(c);
            gti2ClosedCallback(c, 0);
            gti2FreeSocketConnection(c);
        }
    } else {
        c->state = 6;
        gti2SendClose(c);
    }
}
} }

namespace N02284240 { extern "C" {
void gti2ConnectionClosed(GTI2Connection *c, ...)
{
    if (c->state != 7) {
        c->state = 7;
        TableRemove(c->socket->connections, &c);
        ArrayAppend(c->socket->closedConnections, &c);
    }
}
} }

namespace N02284240 { extern "C" {
void gti2ConnectionCleanup(GTI2Connection *c)
{
    if (c->initialMessage != NULL) {
        GsUtil_Free(c->initialMessage);
    }
    if (c->incomingBuffer.buffer != NULL) {
        GsUtil_Free(c->incomingBuffer.buffer);
    }
    if (c->outgoingBuffer.buffer != NULL) {
        GsUtil_Free(c->outgoingBuffer.buffer);
    }
    if (c->incomingBufferMessages != NULL) {
        ArrayFree(c->incomingBufferMessages);
    }
    if (c->outgoingBufferMessages != NULL) {
        ArrayFree(c->outgoingBufferMessages);
    }
    if (c->sendFilters != NULL) {
        ArrayFree(c->sendFilters);
    }
    if (c->receiveFilters != NULL) {
        ArrayFree(c->receiveFilters);
    }
    GsUtil_Free(c);
}
} }

namespace N02284240 { extern "C" {
s32 gti2SocketErrorCallback(GTI2Socket *s)
{
    if (s == NULL) {
        return TRUE;
    }
    if (s->socketErrorCallback == NULL) {
        return TRUE;
    }
    s->callbackLevel++;
    s->socketErrorCallback(s);
    s->callbackLevel--;
    if (s->close != 0 && s->callbackLevel == 0) {
        gti2CloseSocket(s);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ConnectAttemptCallback(GTI2Socket *s, GTI2Connection *c, s32 a, s32 b, s32 p4, u8 *p5, s32 p6)
{
    if (s == NULL || c == NULL) {
        return TRUE;
    }
    if (s->connectAttemptCallback == NULL) {
        return TRUE;
    }
    if (p6 == 0 || p5 == 0) {
        p5 = 0;
        p6 = 0;
    }
    s->callbackLevel++;
    c->callbackLevel++;
    s->connectAttemptCallback(s, c, a, b, p4, p5, p6);
    s->callbackLevel--;
    c->callbackLevel--;
    if (s->close != 0 && s->callbackLevel == 0) {
        gti2CloseSocket(s);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ConnectedCallback(GTI2Connection *c, s32 a, u8 *b, s32 d)
{
    if (c == NULL) {
        return TRUE;
    }
    c->connectionResult = a;
    if (c->connectedCallback == NULL) {
        return TRUE;
    }
    if (d == 0 || b == 0) {
        b = 0;
        d = 0;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    c->connectedCallback(c, a, b, d);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ReceivedCallback(GTI2Connection *c, u8 *a, s32 b, s32 d)
{
    if (c == NULL) {
        return TRUE;
    }
    if (c->receivedCallback == NULL) {
        return TRUE;
    }
    if (b == 0 || a == 0) {
        a = 0;
        b = 0;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    c->receivedCallback(c, a, b, d);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ClosedCallback(GTI2Connection *c, s32 a)
{
    if (c == NULL) {
        return TRUE;
    }
    if (c->closedCallback == NULL) {
        return TRUE;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    c->closedCallback(c, a);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2PingCallback(GTI2Connection *c, s32 a)
{
    if (c == NULL) {
        return TRUE;
    }
    if (c->pingCallback == NULL) {
        return TRUE;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    c->pingCallback(c, a);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2SendFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel)
{
    GsTransportFilterCallback *f;
    if (c == NULL) {
        return TRUE;
    }
    f = (GsTransportFilterCallback *)ArrayNth(c->sendFilters, a);
    if (f == NULL) {
        return TRUE;
    }
    if (len == 0 || msg == 0) {
        msg = 0;
        len = 0;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    (*f)(c, a, msg, len, rel);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N02284240 { extern "C" {
s32 gti2ReceiveFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel)
{
    GsTransportFilterCallback *f;
    if (c == NULL) {
        return TRUE;
    }
    f = (GsTransportFilterCallback *)ArrayNth(c->receiveFilters, a);
    if (f == NULL) {
        return TRUE;
    }
    if (len == 0 || msg == 0) {
        msg = 0;
        len = 0;
    }
    c->callbackLevel++;
    c->socket->callbackLevel++;
    (*f)(c, a, msg, len, rel);
    c->callbackLevel--;
    c->socket->callbackLevel--;
    if (c->socket->close != 0 && c->socket->callbackLevel == 0) {
        gti2CloseSocket(c->socket);
        return FALSE;
    }
    return TRUE;
}
} }

namespace N022838c4 { extern "C" {
s32 gti2DumpCallback(GTI2Socket *o, GTI2Connection *x, s32 u2, s32 u3, s32 s4, u8 *s5, s32 s6, s32 s7) {
    gt2DumpCallback f;
    if (o == 0) {
        return 1;
    }
    if (s7 != 0) {
        f = o->sendDumpCallback;
    } else {
        f = o->receiveDumpCallback;
    }
    if (f == 0) {
        return 1;
    }
    if (s6 == 0 || s5 == 0) {
        s5 = 0;
        s6 = 0;
    }
    o->callbackLevel++;
    if (x != 0) {
        x->callbackLevel++;
    }
    f(o, x, u2, u3, s4, s5, s6);
    o->callbackLevel--;
    if (x != 0) {
        x->callbackLevel--;
    }
    if (o->close != 0 && o->callbackLevel == 0) {
        gti2CloseSocket(o);
        return 0;
    }
    return 1;
}
} }

namespace N022838c4 { extern "C" {
s32 gti2UnrecognizedMessageCallback(GTI2Socket *o, s32 a1, s32 a2, u8 *a3, s32 a4, s32 *out) {
    *out = 0;
    if (o == 0) {
        return 1;
    }
    if (o->unrecognizedMessageCallback == 0) {
        return 1;
    }
    if (a4 == 0 || a3 == 0) {
        a3 = 0;
        a4 = 0;
    }
    o->callbackLevel++;
    *out = o->unrecognizedMessageCallback(o, a1, a2, a3, a4);
    o->callbackLevel--;
    if (o->close != 0 && o->callbackLevel == 0) {
        gti2CloseSocket(o);
        return 0;
    }
    return 1;
}
} }

namespace N022838c4 { extern "C" {
s32 gti2AllocateBuffer(GTI2Buffer *b, s32 size) {
    b->buffer = (u8 *)GsUtil_Alloc(size);
    if (b->buffer == 0) {
        return 0;
    }
    b->size = size;
    return 1;
}
} }

namespace N022838c4 { extern "C" {
s32 gti2GetBufferFreeSpace(GTI2Buffer *b) {
    return b->size - b->len;
}
} }

namespace N022838c4 { extern "C" {
void gti2BufferWriteByte(GTI2Buffer *b, s32 v) {
    b->buffer[b->len++] = v;
}
} }

namespace N022838c4 { extern "C" {
void gti2BufferWriteUShort(GTI2Buffer *b, s32 v) {
    b->buffer[b->len++] = v >> 8;
    b->buffer[b->len++] = v;
}
} }

namespace N022838c4 { extern "C" {
void gti2BufferWriteData(GTI2Buffer *b, const u8 *s, s32 n) {
    if (s != 0 && n != 0) {
        if (n == -1) {
            n = STD_GetStringLength((const char *)s);
        }
        memcpy(b->buffer + b->len, s, n);
        b->len += n;
    }
}
} }

namespace N022838c4 { extern "C" {
void gti2BufferShorten(GTI2Buffer *b, s32 pos, s32 n) {
    if (pos == -1) {
        pos = b->len - n;
    }
    memmove(b->buffer + pos, b->buffer + pos + n, b->len - pos - n);
    b->len -= n;
}
} }

namespace N022838c4 { extern "C" {
BOOL gti2VerifyChallenge(u8 *p) {
    u32 t2;
    u32 t1;
    u32 v[8];
    u32 acc;
    s32 i;
    u32 c;
    u32 b;
    u32 x;
    acc = 0;
    i = 1;
    c = p[0];
    v[0] = c;
    v[0] &= i;
    v[2] = 0;
    v[1] = 1;
    v[4] = 0;
    v[3] = 1;
    v[6] = 1;
    v[5] = 1;
    v[7] = 1;
    for (; i < 0x20; i++) {
        b = p[i - 1];
        if (b < c) {
            t1 = v[1];
        } else {
            t1 = v[2];
        }
        if (c < 0x4f) {
            t2 = v[3];
        } else {
            t2 = v[4];
        }
        x = i;
        x ^= b;
        x &= v[5];
        acc ^= x;
        b = v[0];
        b ^= acc;
        b ^= t2;
        acc = b;
        acc ^= t1;
        if ((acc != 0 && (p[i] & v[6]) == 0) || (acc == 0 && (p[i] & v[7]) == 1)) {
            return FALSE;
        }
    }
    return TRUE;
}
} }

namespace N022838c4 { extern "C" {
char *gti2GetChallenge(u8 *out) {
    u32 t2;
    u32 b;
    u8 *p;
    u32 c;
    s32 i;
    u32 t1;
    u32 v[9];
    u32 acc;
    srand(current_time());
    out[0] = rand() % 0x5d + 0x21;
    acc = 0;
    i = 1;
    v[1] = 0;
    v[0] = 1;
    v[3] = 0;
    v[2] = 1;
    v[5] = 1;
    v[4] = 1;
    v[6] = 1;
    v[7] = 1;
    for (; i < 0x20; i++) {
        b = out[i - 1];
        c = out[0];
        if (b < c) {
            t1 = v[0];
        } else {
            t1 = v[1];
        }
        if (c < 0x4f) {
            t2 = v[2];
        } else {
            t2 = v[3];
        }
        c &= v[5];
        v[8] = i;
        v[8] = v[8] ^ b;
        v[8] = v[8] & v[4];
        acc ^= v[8];
        c ^= acc;
        c ^= t2;
        acc = c;
        acc ^= t1;
        p = out + i;
        out[i] = rand() % 0x5d + 0x21;
        if ((acc != 0 && (*p & v[6]) == 0) || (acc == 0 && (*p & v[7]) == 1)) {
            (*p)++;
        }
    }
    return (char *)out;
}
} }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_02283f34) {
    HOST_OVERLAY_VAR(data_ov065_0228e14c),
    HOST_OVERLAY_VARS_END
};
