#ifndef PROTO_PROTO_OV065_UNK_OV065_0226F9E0_H
#define PROTO_PROTO_OV065_UNK_OV065_0226F9E0_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sNasBase64Alphabet
extern char sNasBase64Alphabet[0x44];
#endif
#ifndef PROTO_LOCAL_sNasBase64AlphabetPtr
extern char *sNasBase64AlphabetPtr;
#endif
#ifndef PROTO_LOCAL_NasBase64_Encode
s32 NasBase64_Encode(u8 *in, u32 len, u8 *out, u32 cap);
#endif
#ifndef PROTO_LOCAL_NasBase64_Decode
s32 NasBase64_Decode(s8 *in, u32 len, u8 *out, u32 cap);
#endif
#ifdef __cplusplus
}
#endif

#endif
