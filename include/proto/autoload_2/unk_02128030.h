#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02128030_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02128030_H


#include "types.h"
#include "types64.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_memcpy
void *memcpy(void *dst, const void *src, u32 n);
#endif
#ifndef PROTO_LOCAL_memmove
void *memmove(void *dst, const void *src, u32 n);
#endif
#ifndef PROTO_LOCAL_memset
void *memset(void *dst, int val, u32 n);
#endif
#ifndef PROTO_LOCAL_memchr
void *memchr(const void *src, int val, u32 n);
#endif
#ifndef PROTO_LOCAL_memcmp
int memcmp(const void *src1, const void *src2, u32 n);
#endif
#ifndef PROTO_LOCAL_mbtowc
int mbtowc(u16 *pwc, const char *s, u32 n);
#endif
#ifndef PROTO_LOCAL___mbtowc_noconv
int __mbtowc_noconv(u16 *pwc, const char *s, u32 n);
#endif
#ifndef PROTO_LOCAL___wctomb_noconv
int __wctomb_noconv(char *s, u16 wc);
#endif
#ifndef PROTO_LOCAL_mbstowcs
int mbstowcs(u16 *pwcs, const char *s, u32 n);
#endif
#ifndef PROTO_LOCAL_scalbn
double scalbn(double a, s32 delta);
#endif
#ifndef PROTO_LOCAL_data_0213c400
extern u16 data_0213c400[58];
#endif
#ifndef PROTO_LOCAL_data_0213c388
extern char *data_0213c388[8];
#endif
#ifdef __cplusplus
}
#endif

#endif
