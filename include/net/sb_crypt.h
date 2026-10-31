#ifndef NET_SB_CRYPT_H
#define NET_SB_CRYPT_H

#include "types.h"


struct GOACryptState {
    /* 0x00 */ u8 cards[0x100];
    /* 0x100 */ u8 rotor;
    /* 0x101 */ u8 ratchet;
    /* 0x102 */ u8 avalanche;
    /* 0x103 */ u8 last_plain;
    /* 0x104 */ u8 last_cipher;
};

#endif
