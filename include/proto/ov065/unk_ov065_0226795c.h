#ifndef PROTO_PROTO_OV065_UNK_OV065_0226795C_H
#define PROTO_PROTO_OV065_UNK_OV065_0226795C_H


#include "types.h"
#include "net/SslSha1Context.h"
#include "uptr.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SslBigNum_GetLength
s32 SslBigNum_GetLength(u16 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Sign
s32 SslBigNum_Sign(u16 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Add
void SslBigNum_Add(u16 *dst, u16 *a, u16 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_AddWord
void SslBigNum_AddWord(u16 *dst, u16 *src, u32 c, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Negate
void SslBigNum_Negate(u16 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Sub
void SslBigNum_Sub(u16 *dst, u16 *a, u16 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_SubWord
void SslBigNum_SubWord(u16 *dst, u16 *src, u32 v, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Compare
s32 SslBigNum_Compare(u16 *a, u16 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_AddWordAt
void SslBigNum_AddWordAt(u16 *a, u32 v, s32 i, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Mul
void SslBigNum_Mul(u16 *dst, u16 *a, u16 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_MulWord
void SslBigNum_MulWord(u16 *dst, u16 *a, u32 m, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_Square
void SslBigNum_Square(u16 *dst, u16 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_SslBigNum_DivMod
void SslBigNum_DivMod(u16 *q, u16 *a, u16 *b, u16 *r, s32 n, u16 *tmp);
#endif
#ifndef PROTO_LOCAL_SslBigNum_ModExp
void SslBigNum_ModExp(u16 *out, u16 *base, u16 *exp, s32 n, u16 *mod);
#endif
#ifndef PROTO_LOCAL_SslBigNum_ModInverse
void SslBigNum_ModInverse(u16 *res, u16 *a, u16 *b, s32 n, u16 *tmp);
#endif
#ifndef PROTO_LOCAL_SslBigNum_MontgomeryStep
void SslBigNum_MontgomeryStep(u16 *a, u16 *b, uptr mode, u32 n, u32 k, u16 *m, u16 *t1, u16 *t2, u16 *t3);
#endif
#ifndef PROTO_LOCAL_SslBigNum_ModExpMontgomery
void SslBigNum_ModExpMontgomery(u16 *x, u16 *y, u16 *z, u32 n, u16 *m);
#endif
#ifndef PROTO_LOCAL_SslBigNum_FromBytes
void SslBigNum_FromBytes(u16 *dst, u8 *src, s32 n, u32 m);
#endif
#ifndef PROTO_LOCAL_SslBigNum_ToBytes
void SslBigNum_ToBytes(u8 *dst, u16 *src, s32 n);
#endif
#ifndef PROTO_LOCAL_SslRc4_Init
void SslRc4_Init(u8 *st, u8 *key, s32 keylen);
#endif
#ifndef PROTO_LOCAL_SslRc4_Crypt
void SslRc4_Crypt(u8 *st, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SslSha1_ExpandWord
u32 SslSha1_ExpandWord(s32 i, u32 *w);
#endif
#ifndef PROTO_LOCAL_SslSha1_StoreBe32
void SslSha1_StoreBe32(u8 *dst, const u32 *src, u32 n);
#endif
#ifndef PROTO_LOCAL_SslSha1_LoadBe32
void SslSha1_LoadBe32(u32 *dst, const u8 *src, u32 n);
#endif
#ifndef PROTO_LOCAL_SslSha1_Transform
void SslSha1_Transform(u32 *ctx, const u8 *data);
#endif
#ifndef PROTO_LOCAL_sSslSha1Padding
extern u8 sSslSha1Padding[0x40];
#endif
#ifndef PROTO_LOCAL_SslSha1_Init
void SslSha1_Init(SslSha1Context *ctx);
#endif
#ifndef PROTO_LOCAL_SslSha1_Update
void SslSha1_Update(SslSha1Context *ctx, const u8 *data, u32 n);
#endif
#ifndef PROTO_LOCAL_SslSha1_Final
void SslSha1_Final(SslSha1Context *ctx, void *out);
#endif
#ifndef PROTO_LOCAL_SslSha1_FinalRaw
void SslSha1_FinalRaw(SslSha1Context *ctx, void *out);
#endif
#ifndef PROTO_LOCAL_SslMd5_Encode
void SslMd5_Encode(void *dst, const void *src, s32 n);
#endif
#ifndef PROTO_LOCAL_SslMd5_Decode
void SslMd5_Decode(void *dst, const void *src, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#endif
