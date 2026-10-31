#include "types.h"
#include "net/gpiOperation.h"
#include "net/gpi.h"
#include "net/gpiPeer.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_0227d96c.h"
#include "proto/ov065/unk_ov065_02283720.h"















extern "C" {
s32 strncmp(const char *, const char *, s32);
s32 OS_SPrintf(char *, const char *, ...);
s32 gpiValueForKey(const char *, const char *, char *, s32);
void gpiSetErrorString(void *, const char *);
void gpiSetError(void *, s32, const char *);
s32 recv(s32, void *, s32, s32);
s32 send(s32, void *, s32, s32);
s32 GOAGetLastError(s32);
s32 ArrayLength(DArrayImplementation *);
s32 shutdown(s32, s32);
s32 closesocket(s32);
s32 gpiRemoveOperation(void *, void *);
s32 gpiDestroyPeer(void *, void *);
s32 gpiProfileMap(void *, s32, s32);
s32 gpiDisconnectCleanupProfile(void);

s32 gpiSendData(GPConnection *, s32, char *, s32, s32 *, s32 *, const char *);
s32 gpiAppendIntToBuffer(GPConnection *, GPIBuffer *, s32);
s32 gpiAppendStringToBuffer(GPConnection *, GPIBuffer *, const char *);
s32 gpiAppendStringToBufferLen(GPConnection *, GPIBuffer *, const char *, s32);
s32 gpiAppendCharToBuffer(GPConnection *, GPIBuffer *, char);
s32 gpiSendOrBufferStringLen(GPConnection *, GPIPeer *, const char *, s32);
s32 gpiSendFromBuffer(GPConnection *, s32, GPIBuffer *, s32 *, s32, const char *);
s32 gpiCallCallback(GPConnection *, GPICallbackData *);
s32 gpiAddCallback(GPConnection *, GPICallbackCopy, GPICallbackData *, GPIOperation *, s32);
void gpiCallErrorCallback(GPConnection *, s32, s32);
}

extern "C" {
s32 gpiAppendCharToBuffer(GPConnection *h, GPIBuffer *b, char c) {
    s32 len = b->len;
    s32 cap = b->size;
    char *data = b->buffer;
    if (cap == len) {
        cap += 0x800;
        data = (char *)GsUtil_Realloc(data, cap + 1);
        if (data == NULL) {
            gpiSetErrorString(h, "Out of memory.");
            return 1;
        }
    }
    data[len] = c;
    data[len + 1] = 0;
    b->len = b->len + 1;
    b->size = cap;
    b->buffer = data;
    return 0;
}
}

extern "C" {
s32 gpiAppendStringToBufferLen(GPConnection *h, GPIBuffer *b, const char *s, s32 n) {
    s32 len;
    s32 cap;
    char *data;
    if (s == NULL) {
        return 0;
    }
    len = b->len;
    cap = b->size;
    data = b->buffer;
    if (cap - len < n) {
        cap += (n < 0x800) ? 0x800 : n;
        data = (char *)GsUtil_Realloc(data, cap + 1);
        if (data == NULL) {
            gpiSetErrorString(h, "Out of memory.");
            return 1;
        }
    }
    memcpy(data + len, s, n);
    data[len + n] = 0;
    b->len = b->len + n;
    b->size = cap;
    b->buffer = data;
    return 0;
}
}

extern "C" {
s32 gpiAppendStringToBuffer(GPConnection *h, GPIBuffer *b, const char *s) {
    return gpiAppendStringToBufferLen(h, b, s, STD_GetStringLength(s));
}
}

extern "C" {
s32 gpiAppendIntToBuffer(GPConnection *h, GPIBuffer *b, s32 n) {
    char tmp[0x14];
    OS_SPrintf(tmp, "%d", n);
    return gpiAppendStringToBuffer(h, b, tmp);
}
}

extern "C" {
s32 gpiSendData(GPConnection *h, s32 fd, char *buf, s32 len, s32 *pflag, s32 *pcnt, const char *str) {
    s32 n;
    s32 e;
    n = send(fd, buf, len, 0);
    if (n == -1) {
        e = GOAGetLastError(fd);
        if (e != -6 && e != -0x1a && e != -0x4c) {
            if (str[0] == 'P' && str[1] == 'R') {
                return 3;
            }
            gpiSetError(h, 5, "There was an error sending on a socket.");
            gpiCallErrorCallback(h, 3, 0);
            return 3;
        }
        *pcnt = 0;
        *pflag = 0;
    } else if (n == 0) {
        gpiDebug(h, "SENDXXXX(%s): Connection closed\n", str);
        *pcnt = 0;
        *pflag = 1;
    } else {
        *pcnt = n;
        *pflag = 0;
    }
    return 0;
}
}

extern "C" {
s32 gpiSendOrBufferChar(GPConnection *h, GPIPeer *c, char ch) {
    s32 flag;
    s32 cnt;
    s32 r;
    if (c->outputBuffer.len - c->outputBuffer.pos == 0 && ArrayLength(c->messages) == 0) {
        r = gpiSendData(h, c->sock, &ch, 1, &flag, &cnt, "PT");
        if (r != 0) {
            return r;
        }
        if (cnt != 0) {
            return 0;
        }
    }
    return gpiAppendCharToBuffer(h, &c->outputBuffer, ch);
}
}

extern "C" {
s32 gpiSendOrBufferStringLen(GPConnection *h, GPIPeer *c, const char *s, s32 n) {
    s32 sent = 0;
    s32 flag;
    s32 cnt;
    s32 r;
    if (n == 0) {
        return sent;
    }
    if (c->outputBuffer.len - c->outputBuffer.pos == 0 && ArrayLength(c->messages) == 0) {
        do {
            r = gpiSendData(h, c->sock, (char *)s + sent, n, &flag, &cnt, "PT");
            if (r != 0) {
                return r;
            }
            if (cnt != 0) {
                sent += cnt;
                n -= cnt;
            }
        } while (cnt != 0 && n != 0);
    }
    if (n != 0) {
        r = gpiAppendStringToBufferLen(h, &c->outputBuffer, s + sent, n);
        if (r != 0) {
            return r;
        }
    }
    return 0;
}
}

extern "C" {
s32 gpiSendOrBufferString(GPConnection *h, GPIPeer *c, const char *s) {
    return gpiSendOrBufferStringLen(h, c, s, STD_GetStringLength(s));
}
}

extern "C" {
__declspec(weak) void Unk_ov065_0227dc00_pool_order(void) {
    OS_SPrintf((char *)0, "%d");
}
}

extern "C" {
s32 gpiRecvToBuffer(GPConnection *h, s32 fd, GPIBuffer *b, s32 *pout, s32 *pflag, const char *str) {
    char *data = b->buffer;
    s32 len = b->len;
    s32 cap = b->size;
    s32 total = 0;
    s32 flag = 0;
    volatile s32 z0 = 0;
    volatile s32 z1 = 0;
    volatile s32 z2 = 0;
    volatile s32 z3 = 0;
    s32 n;
    s32 e;
    for (;;) {
        if (len + 0x800 > cap) {
            cap = len + 0x800;
            data = (char *)GsUtil_Realloc(data, cap + 1);
            if (data == NULL) {
                gpiSetErrorString(h, "Out of memory.");
                return 1;
            }
        }
        n = recv(fd, data + len, cap - len, z0);
        if (n == ~z2) {
            e = GOAGetLastError(fd);
            if (e != -6 && e != -0x1a && e != -0x4c) {
                gpiSetErrorString(h, "There was an error reading from a socket.");
                return 3;
            }
        } else if (n == 0) {
            flag = 1;
            gpiDebug(h, "RECVXXXX(%s): Connection closed\n", str);
        } else {
            len += n;
            total += n;
        }
        data[len] = z1;
        if (n == ~z3 || flag != 0 || total >= 0x20000) {
            break;
        }
    }
    if (total != 0) {
        gpiDebug(h, "RECVTOTL(%s): %d\n", str, total);
    }
    b->buffer = data;
    b->len = len;
    b->size = cap;
    *pout = total;
    s32 *pf = pflag;
    *pf = flag;
    return 0;
}
}

extern "C" {
s32 gpiSendFromBuffer(GPConnection *h, s32 fd, GPIBuffer *b, s32 *pout, s32 compact, const char *str) {
    char *data = b->buffer;
    s32 len = b->len;
    s32 pos = b->pos;
    s32 sent;
    s32 rem = len - pos;
    sent = 0;
    s32 flag;
    s32 cnt;
    s32 r;
    if (rem == 0) {
        return sent;
    }
    do {
        r = gpiSendData(h, fd, data + (pos + sent), rem, &flag, &cnt, str);
        if (r != 0) {
            return r;
        }
        if (cnt != 0) {
            sent += cnt;
            rem -= cnt;
        }
    } while (cnt != 0 && rem != 0);
    if (compact != 0) {
        if (sent > 0) {
            memmove(data, data + sent, rem + 1);
            len -= sent;
        }
    } else {
        pos += sent;
    }
    b->len = len;
    b->pos = pos;
    if (pout != NULL) {
        *pout = flag;
    }
    return 0;
}
}

extern "C" {
s32 gpiReadMessageFromBuffer(void *h, GPIBuffer *b, char **pp, s32 *plen, s32 *pval) {
    char line[16];
    char *p;
    s32 n;
    s32 k;
    *pp = NULL;
    if (b->len < 5) {
        return 0;
    }
    {
        p = strchr(b->buffer, 10);
        if (p != NULL) {
            if (strncmp(p - 5, "\\msg\\", 5) != 0) {
                return 3;
            }
            *p = 0;
            if (gpiValueForKey(b->buffer, "\\m\\", line, 16) == 0) {
                return 3;
            }
            *plen = atol(line);
            if (gpiValueForKey(b->buffer, "\\len\\", line, 16) == 0) {
                return 3;
            }
            n = atol(line);
            k = n + 1;
            if (b->len > k + (p - b->buffer)) {
                if (p[k] != 0) {
                    return 3;
                }
                *pp = p + 1;
                *pval = n;
                b->pos = k + (p - b->buffer) + 1;
            } else {
                *p = 10;
            }
        }
    }
    return 0;
}
}

extern "C" {
s32 gpiClipBufferToPosition(void *h, GPIBuffer *b) {
    if (b == NULL || b->buffer == NULL || b->pos == 0) {
        return 0;
    }
    b->len = b->len - b->pos;
    if (b->len != 0) {
        memmove(b->buffer, b->buffer + b->pos, b->len);
    }
    b->buffer[b->len] = 0;
    b->pos = 0;
    return 0;
}
}
