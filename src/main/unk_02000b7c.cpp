#include "types.h"

extern "C" {
extern const u8 sAxMailDigestKey[16];

const u8 *AxMail_GetDigestKey(void)
{
    return sAxMailDigestKey;
}
}
