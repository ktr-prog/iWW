#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0212B770_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0212B770_H


#include "types.h"
#include "types64.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL___strtoul
u32 __strtoul(int base, int max_width, int (*ReadProc)(void *, int, int), void *ReadProcArg, int *chars_scanned, int *negative, int *overflow);
#endif
#ifndef PROTO_LOCAL___strtoull
u64 __strtoull(int base, int max_width, int (*ReadProc)(void *, int, int), void *ReadProcArg, int *chars_scanned, int *negative, int *overflow);
#endif
#ifndef PROTO_LOCAL_strtoul
u32 strtoul(const char *str, char **end, int base);
#endif
#ifndef PROTO_LOCAL_strtol
int strtol(const char *str, char **end, int base);
#endif
#ifndef PROTO_LOCAL_atol
int atol(const char *str);
#endif
#ifdef __cplusplus
}
#endif

#endif
