typedef unsigned char u8;
typedef unsigned int u32;
#include "uptr.h"
#include "types64.h"
typedef signed int s32;

typedef struct {
    u32 a, b, c, d;
    u64 total;
    u8 buffer[64];
} MD5Context;

typedef struct {
    u32 h[5];
    u32 totalLo;
    u32 totalHi;
    s32 blockLen;
    u8 block[64];
    u32 reserved[2];
} SHA1Context;

typedef void (*SHA1Compress)(SHA1Context *ctx, const void *data, u32 len);

extern const u32 data_0213c0c8[64];
extern const u32 data_0213c008[48];
extern const u8 data_0213c004[1];
extern SHA1Compress data_0213c1c8;

extern void MIi_CpuClear32(u32 data, void *dest, u32 size);
extern void MI_CpuFill8(void *dest, u32 data, u32 size);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);

void DGT_Hash2Reset(SHA1Context *ctx);
void DGT_Hash2SetSource(SHA1Context *ctx, const void *data, u32 len);
void DGT_Hash2GetDigest(SHA1Context *ctx, u8 *hash, ...);
void DGT_Hash2CalcHmac(u8 *out, const u8 *data, u32 dataLen, const u8 *key, s32 keyLen);
void DGT_Hash1Reset(MD5Context *ctx);
void DGT_Hash1SetSource(MD5Context *ctx, const void *data, u32 len);
void DGT_Hash1GetDigest_R(u8 *out, MD5Context *ctx);
void ProcessBlock(MD5Context *ctx);

void DGT_Hash2Reset(SHA1Context *ctx) {
    ctx->h[0] = 0x67452301;
    ctx->h[1] = 0xefcdab89;
    ctx->h[2] = 0x98badcfe;
    ctx->h[3] = 0x10325476;
    ctx->h[4] = 0xc3d2e1f0;
    ctx->totalLo = 0;
    ctx->totalHi = 0;
    ctx->blockLen = 0;
}

void DGT_Hash2SetSource(SHA1Context *ctx, const void *data, u32 len) {
    u8 *buf = ctx->block;
    u32 n;
    if (len == 0) {
        return;
    }
    {
        u32 lo = ctx->totalLo + (len << 3);
        if (lo < ctx->totalLo) {
            ctx->totalHi++;
        }
        ctx->totalHi += len >> 29;
        ctx->totalLo = lo;
    }
    if (ctx->blockLen != 0) {
        if (ctx->blockLen + len >= 64) {
            n = 64 - ctx->blockLen;
            MI_CpuCopy8(data, buf + ctx->blockLen, n);
            len -= n;
            data = (const u8 *)data + n;
            data_0213c1c8(ctx, buf, 64);
            ctx->blockLen = 0;
        } else {
            MI_CpuCopy8(data, buf + ctx->blockLen, len);
            ctx->blockLen += len;
            return;
        }
    }
    if (len >= 64) {
        n = len & ~63;
        len -= n;
        if (((uptr)data & 3) == 0) {
            data_0213c1c8(ctx, data, n);
            data = (const u8 *)data + n;
        } else {
            do {
                MI_CpuCopy8(data, buf, 64);
                data = (const u8 *)data + 64;
                data_0213c1c8(ctx, buf, 64);
                n -= 64;
            } while ((s32)n > 0);
        }
    }
    ctx->blockLen = len;
    if (len == 0) {
        return;
    }
    MI_CpuCopy8(data, buf, len);
}

void DGT_Hash2GetDigest(SHA1Context *ctx, u8 *hash, ...) {
    u32 *w = (u32 *)ctx->block;
    s32 i = ctx->blockLen;
    s32 j = i >> 2;
    u8 *buf;
    volatile u32 zero;
    u32 t;
    if ((i & 3) == 0) {
        w[j] = 0;
    }
    buf = ctx->block;
    buf[i] = 0x80;
    i++;
    while ((i & 3) != 0) {
        buf[i] = 0;
        i++;
    }
    j++;
    if (ctx->blockLen >= 56) {
        while (j < 16) {
            w[j] = 0;
            j++;
        }
        data_0213c1c8(ctx, w, 64);
        j = 0;
    }
    while (j < 14) {
        w[j] = 0;
        j++;
    }
    t = ctx->totalLo;
    buf[63] = t;
    buf[62] = t >> 8;
    buf[61] = t >> 16;
    buf[60] = t >> 24;
    t = ctx->totalHi;
    buf[59] = t;
    buf[58] = t >> 8;
    buf[57] = t >> 16;
    buf[56] = t >> 24;
    data_0213c1c8(ctx, w, 64);
    t = ctx->h[0];
    hash[0] = t >> 24;
    hash[1] = t >> 16;
    hash[2] = t >> 8;
    hash[3] = t;
    t = ctx->h[1];
    hash[4] = t >> 24;
    hash[5] = t >> 16;
    hash[6] = t >> 8;
    hash[7] = t;
    t = ctx->h[2];
    hash[8] = t >> 24;
    hash[9] = t >> 16;
    hash[10] = t >> 8;
    hash[11] = t;
    t = ctx->h[3];
    hash[12] = t >> 24;
    hash[13] = t >> 16;
    hash[14] = t >> 8;
    hash[15] = t;
    t = ctx->h[4];
    hash[16] = t >> 24;
    hash[17] = t >> 16;
    hash[18] = t >> 8;
    hash[19] = t;
    ctx->blockLen = 0;
    zero = 0;
    MIi_CpuClear32(zero, &ctx, 4);
}

void DGT_Hash2CalcHmac(u8 *out, const u8 *data, u32 dataLen, const u8 *key, s32 keyLen) {
    u8 ipad[64];
    u8 opad[64];
    u8 digest[20];
    SHA1Context ctx;
    u8 *hash = digest;
    s32 i;
    if (out == 0 || data == 0 || dataLen == 0 || key == 0 || keyLen == 0) {
        return;
    }
    if (keyLen > 64) {
        DGT_Hash2Reset(&ctx);
        DGT_Hash2SetSource(&ctx, key, keyLen);
        DGT_Hash2GetDigest(&ctx, hash);
        key = hash;
        keyLen = 20;
    }
    for (i = 0; i < keyLen; i++) {
        ipad[i] = *key ^ 0x36;
        opad[i] = *key++ ^ 0x5c;
    }
    for (; i < 64; i++) {
        ipad[i] = 0x36;
        opad[i] = 0x5c;
    }
    DGT_Hash2Reset(&ctx);
    DGT_Hash2SetSource(&ctx, ipad, 64);
    DGT_Hash2SetSource(&ctx, data, dataLen);
    DGT_Hash2GetDigest(&ctx, hash);
    DGT_Hash2Reset(&ctx);
    DGT_Hash2SetSource(&ctx, opad, 64);
    DGT_Hash2SetSource(&ctx, hash, 20);
    DGT_Hash2GetDigest(&ctx, out);
}

void DGT_Hash1Reset(MD5Context *ctx) {
    ctx->a = 0x67452301;
    ctx->b = 0xefcdab89;
    ctx->c = 0x98badcfe;
    ctx->d = 0x10325476;
    ctx->total = 0;
}

void DGT_Hash1SetSource(MD5Context *ctx, const void *data, u32 len) {
    u32 idx = (u32)ctx->total & 63;
    u32 room;
    s32 blocks;
    const u8 *p;
    ctx->total += len;
    room = 64 - idx;
    if (room > len) {
        if (len == 0) {
            return;
        }
        MI_CpuCopy8(data, ctx->buffer + idx, len);
        return;
    }
    MI_CpuCopy8(data, ctx->buffer + idx, room);
    ProcessBlock(ctx);
    len -= room;
    blocks = len >> 6;
    p = (const u8 *)data + room;
    while (blocks > 0) {
        MI_CpuCopy8(p, ctx->buffer, 64);
        p += 64;
        ProcessBlock(ctx);
        blocks--;
    }
    if (len & 63) {
        MI_CpuCopy8(p, ctx->buffer, len & 63);
    }
}

void DGTi_hash2_arm4_small(SHA1Context *ctx, const void *data, u32 len);
SHA1Compress data_0213c1c8 = DGTi_hash2_arm4_small;
