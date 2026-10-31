#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02128C60_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02128C60_H


#include "types.h"
#include "ds_stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_strcspn
u32 strcspn(const char *str, const char *set);
#endif
#ifndef PROTO_LOCAL_strstr
char *strstr(const char *str, const char *pat);
#endif
#ifndef PROTO_LOCAL_raise
int raise(int sig);
#endif
#ifndef PROTO_LOCAL___StringRead
int __StringRead(void *ctx, int ch, int action);
#endif
#ifndef PROTO_LOCAL_vsscanf
int vsscanf(const char *s, const char *fmt, va_list ap);
#endif
#ifndef PROTO_LOCAL_sscanf
int sscanf(const char *s, const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_rand
int rand(void);
#endif
#ifndef PROTO_LOCAL_srand
void srand(u32 seed);
#endif
#ifndef PROTO_LOCAL_data_0213c4fc
extern u32 data_0213c4fc;
#endif
#ifdef __cplusplus
}
#endif

#endif
