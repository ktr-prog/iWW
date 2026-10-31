typedef unsigned char u8;
typedef unsigned int u32;
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

extern u32 data_0213c0c8[64];
extern u32 data_0213c008[48];
extern u8 data_0213c004[1];
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

static inline void MI_CpuClear8(void *dest, u32 size) {
    MI_CpuFill8(dest, 0, size);
}
void DGT_Hash1GetDigest_R(u8 *out, MD5Context *ctx) {
    u64 t = ctx->total << 3;
    u32 idx;
    u32 room;
    DGT_Hash1SetSource(ctx, data_0213c004, 1);
    idx = (u32)(ctx->total & 63);
    room = 64 - idx;
    if (room < 8) {
        MI_CpuClear8(ctx->buffer + idx, room);
        ProcessBlock(ctx);
        idx = 0;
        room = 64;
    }
    if (room > 8) {
        MI_CpuClear8(ctx->buffer + idx, room - 8);
    }
    *(u32 *)(ctx->buffer + 56) = (u32)t;
    *(u32 *)(ctx->buffer + 60) = (u32)(t >> 32);
    ProcessBlock(ctx);
    MI_CpuCopy8(ctx, out, 16);
    MI_CpuClear8(ctx, 88);
}
#define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define STEP(f, a, b, c, d, x, k, s) \
    (a) = (a) + f(b, c, d) + (x) + (k); \
    (a) = (b) + ROTL(a, s);

static inline u32 RotL(u32 x, int n) { return (x << n) | (x >> (32 - n)); }
static inline u32 FF(u32 a, u32 b, u32 c, u32 d, u32 x, u32 t, int s) { a = a + ((b & c) | (~b & d)) + x + t; return b + RotL(a, s); }
static inline u32 GG(u32 a, u32 b, u32 c, u32 d, u32 x, u32 t, int s) { a = a + ((b & d) | (c & ~d)) + x + t; return b + RotL(a, s); }
static inline u32 HH(u32 a, u32 b, u32 c, u32 d, u32 x, u32 t, int s) { a = a + (b ^ c ^ d) + x + t; return b + RotL(a, s); }
static inline u32 II(u32 a, u32 b, u32 c, u32 d, u32 x, u32 t, int s) { a = a + (c ^ (b | ~d)) + x + t; return b + RotL(a, s); }
void ProcessBlock(MD5Context *ctx) {
    const u32 *p;
    s32 i;
    const u32 *t;
    u32 a = ctx->a;
    u32 b = ctx->b;
    u32 c = ctx->c;
    u32 d = ctx->d;
    const u32 *x = (const u32 *)ctx->buffer;
    const u32 *k = data_0213c0c8;
    p = x;
    for (i = 0; i < 4; i++) {
        a = FF(a, b, c, d, *p++, *k++, 7);
        d = FF(d, a, b, c, *p++, *k++, 12);
        c = FF(c, d, a, b, *p++, *k++, 17);
        b = FF(b, c, d, a, *p++, *k++, 22);
    }
    t = data_0213c008;
    for (i = 0; i < 4; i++) {
        a = GG(a, b, c, d, x[*t++], *k++, 5);
        d = GG(d, a, b, c, x[*t++], *k++, 9);
        c = GG(c, d, a, b, x[*t++], *k++, 14);
        b = GG(b, c, d, a, x[*t++], *k++, 20);
    }
    for (i = 0; i < 4; i++) {
        a = HH(a, b, c, d, x[*t++], *k++, 4);
        d = HH(d, a, b, c, x[*t++], *k++, 11);
        c = HH(c, d, a, b, x[*t++], *k++, 16);
        b = HH(b, c, d, a, x[*t++], *k++, 23);
    }
    for (i = 0; i < 4; i++) {
        a = II(a, b, c, d, x[*t++], *k++, 6);
        d = II(d, a, b, c, x[*t++], *k++, 10);
        c = II(c, d, a, b, x[*t++], *k++, 15);
        b = II(b, c, d, a, x[*t++], *k++, 21);
    }
    ctx->a += a;
    ctx->b += b;
    ctx->c += c;
    ctx->d += d;
}

u8 data_0213c004[1] = {0x80};
u32 data_0213c008[48] = {
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9,
};
u32 data_0213c0c8[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};
