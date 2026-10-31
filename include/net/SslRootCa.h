#ifndef NET_SSLROOTCA_H
#define NET_SSLROOTCA_H

#include "types.h"


typedef struct SslRootCa SslRootCa;
struct SslRootCa {
    /* 0x00 */ const char *name;
    /* 0x04 */ s32 modulusLen;
    /* 0x08 */ u8 *modulus;
    /* 0x0c */ s32 exponentLen;
    /* 0x10 */ u8 *exponent;
};

#endif
