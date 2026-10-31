#ifndef NET_DWCMATCHUSERKEY_H
#define NET_DWCMATCHUSERKEY_H

#include "types.h"


struct DwcMatchUserKey {
    /* 0x00 */ u8 keyId;
    /* 0x01 */ u8 isString;
    /* 0x02 */ u8 unk_02[2];
    /* 0x04 */ char *keyName;
    /* 0x08 */ const void *value;
};

#endif
