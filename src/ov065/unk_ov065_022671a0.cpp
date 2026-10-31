#include "types.h"
#include "net/IpSocket.h"
#include "net/SslConnection.h"
#include "net/SslSession.h"
#include "net/SslSha1Context.h"
#include "net/SslMd5Context.h"
#include "nitro/os_rtc.h"
#include "proto/autoload_2/unk_0211d20c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/ov065/unk_ov065_022671a0.h"
#include "proto/ov065/unk_ov065_0226795c.h"



extern OSThreadInfo data_021fcc2c;

extern "C" {

void MI_CpuFill8(void *dst, s32 v, s32 n);
void MI_CpuCopy8(const void *src, void *dst, s32 n);
void RTC_GetDate(RTCDate *);
void RTC_GetTime(RTCTime *);

u8 sSslMd5WordIndex[0x40] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x01, 0x06, 0x0b, 0x00, 0x05, 0x0a, 0x0f, 0x04, 0x09, 0x0e, 0x03, 0x08, 0x0d, 0x02, 0x07, 0x0c, 0x05, 0x08, 0x0b, 0x0e, 0x01, 0x04, 0x07, 0x0a, 0x0d, 0x00, 0x03, 0x06, 0x09, 0x0c, 0x0f, 0x02, 0x00, 0x07, 0x0e, 0x05, 0x0c, 0x03, 0x0a, 0x01, 0x08, 0x0f, 0x06, 0x0d, 0x04, 0x0b, 0x02, 0x09};
u8 sSslMd5Padding[0x40] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
u32 sSslMd5SineTable[0x40] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
SslSession sSslSessionCache[4] = {0};

void SslMd5_Final(SslMd5Context *ctx, void *out);
void SslMd5_Init(SslMd5Context *ctx);

#define Unk_ov065_02267540_ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define Unk_ov065_02267540_F(b, c, d) ((d) ^ ((b) & ((c) ^ (d))))
#define Unk_ov065_02267540_G(b, c, d) (((b) & (d)) | ((c) & ~(d)))
#define Unk_ov065_02267540_H(b, c, d) ((b) ^ (c) ^ (d))
#define Unk_ov065_02267540_I(b, c, d) ((c) ^ ((b) | ~(d)))
#define Unk_ov065_02267540_STEP(f, a, b, c, d, k, sh) \
    a += f(b, c, d) + X[sSslMd5WordIndex[k]] + sSslMd5SineTable[k]; \
    a = b + Unk_ov065_02267540_ROL(a, sh);

void SslMd5_Transform(SslMd5Context *ctx, const u8 *block)
{
    u32 a = ctx->st[0];
    u32 b = ctx->st[1];
    u32 c = ctx->st[2];
    u32 d = ctx->st[3];
    u32 X[16];
    s32 t;
    s32 i;
    SslMd5_Decode(X, block, 0x40);
    t = 0;
    for (i = 0; i < 4; i++) {
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_F, a, b, c, d, t + 0, 7)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_F, d, a, b, c, t + 1, 12)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_F, c, d, a, b, t + 2, 17)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_F, b, c, d, a, t + 3, 22)
        t += 4;
    }
    for (i = 0; i < 4; i++) {
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_G, a, b, c, d, t + 0, 5)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_G, d, a, b, c, t + 1, 9)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_G, c, d, a, b, t + 2, 14)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_G, b, c, d, a, t + 3, 20)
        t += 4;
    }
    for (i = 0; i < 4; i++) {
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_H, a, b, c, d, t + 0, 4)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_H, d, a, b, c, t + 1, 11)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_H, c, d, a, b, t + 2, 16)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_H, b, c, d, a, t + 3, 23)
        t += 4;
    }
    for (i = 0; i < 4; i++) {
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_I, a, b, c, d, t + 0, 6)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_I, d, a, b, c, t + 1, 10)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_I, c, d, a, b, t + 2, 15)
        Unk_ov065_02267540_STEP(Unk_ov065_02267540_I, b, c, d, a, t + 3, 21)
        t += 4;
    }
    ctx->st[0] += a;
    ctx->st[1] += b;
    ctx->st[2] += c;
    ctx->st[3] += d;
}

void SslMd5_Init(SslMd5Context *ctx)
{
    MI_CpuFill8(ctx, 0, sizeof(*ctx));
    ctx->st[0] = 0x67452301;
    ctx->st[1] = 0xefcdab89;
    ctx->st[2] = 0x98badcfe;
    ctx->st[3] = 0x10325476;
}

void SslMd5_Update(SslMd5Context *ctx, const u8 *data, u32 n)
{
    u32 idx = (ctx->lo >> 3) & 0x3f;
    u32 bits = n << 3;
    u32 part;
    u32 i;
    ctx->lo += bits;
    if (ctx->lo < bits) {
        ctx->hi++;
    }
    ctx->hi += n >> 29;
    part = 64 - idx;
    if (n >= part) {
        MI_CpuCopy8(data, ctx->buf + idx, part);
        idx = 0;
        SslMd5_Transform(ctx, ctx->buf);
        for (i = part; i + 63 < n; i += 64) {
            SslMd5_Transform(ctx, data + i);
        }
    } else {
        i = 0;
    }
    MI_CpuCopy8(data + i, ctx->buf + idx, n - i);
}

void SslMd5_Final(SslMd5Context *ctx, void *out)
{
    u32 idx;
    SslMd5_Encode(out, &ctx->lo, 8);
    idx = (ctx->lo >> 3) & 0x3f;
    if ((s32)idx < 0x38) {
        idx = 0x38 - idx;
    } else {
        idx = 0x78 - idx;
    }
    SslMd5_Update(ctx, sSslMd5Padding, idx);
    SslMd5_Update(ctx, (u8 *)out, 8);
    SslMd5_Encode(out, ctx, 0x10);
}

SslSession *SslSession_FindById(const void *p)
{
    s32 i = 0;
    SslSession *e = sSslSessionCache;
    for (; i < 4; e++, i++) {
        if (e->inUse != 0 && memcmp(e, p, 0x20) == 0) {
            e->lastUsed = (u32)(OS_GetTick() >> 16);
            return e;
        }
    }
    return 0;
}

SslSession *SslSession_FindByPeer(u32 a, u32 b)
{
    s32 i = 0;
    SslSession *e = sSslSessionCache;
    for (; i < 4; e++, i++) {
        if (e->inUse != 0 && e->peerAddr == a && e->peerPort == b) {
            e->lastUsed = (u32)(OS_GetTick() >> 16);
            return e;
        }
    }
    return 0;
}

SslSession *SslSession_Add(const void *src)
{
    SslSession *pick;
    u32 tick;
    s32 i;
    u32 best;
    SslSession *e;
    tick = (u32)(OS_GetTick() >> 16);
    best = 0;
    pick = sSslSessionCache;
    i = 0;
    e = pick;
    for (; i < 4; e++, i++) {
        u32 age;
        if (e->inUse == 0) {
            pick = e;
            break;
        }
        age = tick - e->lastUsed;
        if (age > best) {
            best = age;
            pick = e;
        }
    }
    MI_CpuCopy8(src, pick, 0x20);
    pick->lastUsed = tick;
    pick->inUse = 1;
    return pick;
}

u32 Ssl_GetUnixTime(void)
{
    RTCDate a;
    RTCTime b;
    RTC_GetDate(&a);
    RTC_GetTime(&b);
    return RTC_ConvertDateTimeToSecond(&a, &b) + 0x386d4380;
}

void Ssl_SetRootCaList(SslRootCa **a, s32 b)
{
    IpSocket *q = (IpSocket *)data_021fcc2c.current->specific[0];
    if (q != 0) {
        SslConnection *t = q->sslCtx;
        if (t != 0) {
            t->rootCaList = a;
            t->numRootCas = b;
        }
    }
}

SslRootCa *SslCert_FindRootCa(SslConnection *o, const char *name)
{
    s32 i = 0;
    s32 n = o->numRootCas;
    SslRootCa **p;
    SslRootCa **arr;
    if (n > 0) {
        p = arr = o->rootCaList;
        do {
            if (strcmp((*p)->name, name) == 0) {
                return arr[i];
            }
            p++;
            i++;
        } while (i < n);
    }
    return 0;
}

s32 SslCert_ReadDerLength(u8 **pp)
{
    u8 *p = *pp;
    u32 b = *p++;
    u32 len = b;
    if (b & 0x80) {
        s32 n = b & 0x7f;
        len = 0;
        while (n-- != 0) {
            if (len & 0xff000000) {
                return -1;
            }
            len = (len << 8) + *p++;
        }
    }
    *pp = p;
    return len;
}

void SslCert_AppendName(char *p, const char *src, s32 n)
{
    char *dst = p;
    if (*p != 0) {
        do {
            p++;
        } while (*p != 0);
        if (p - dst >= 0xff) {
            return;
        }
        *p++ = ',';
        *p++ = ' ';
    }
    while (n-- != 0 && p - dst < 0xff) {
        *p++ = *src++;
    }
    *p = 0;
}

u32 SslCert_ParseTime(const u8 *p, s32 mode)
{
    u32 a = p[1] + p[0] * 10 - 0x210;
    u32 y;
    p += 2;
    if (mode == 0x17) {
        if (a < 0x32) {
            y = a + 0x7d0;
        } else {
            y = a + 0x76c;
        }
    } else {
        y = a * 100 + (p[1] + p[0] * 10 - 0x210);
        p += 2;
    }
    return (y << 16) + ((p[1] + p[0] * 10 - 0x210) << 8) + (p[3] + p[2] * 10 - 0x210);
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_022671a0) {
    HOST_OVERLAY_VAR(sSslMd5WordIndex),
    HOST_OVERLAY_VAR(sSslMd5Padding),
    HOST_OVERLAY_VAR(sSslMd5SineTable),
    HOST_OVERLAY_VAR(sSslSessionCache),
    HOST_OVERLAY_VARS_END
};
