#ifndef GFX_STARTWINKLE_H
#define GFX_STARTWINKLE_H

#include "types.h"
#include "gfx/BgVramTask.h"

class StarTwinkle {
public:
    StarTwinkle();
    ~StarTwinkle();
    /* 0x000 */ BgVramTask task;
    /* 0x024 */ u8 palette[0x80];
    /* 0x0a4 */ u8 palettes[5][0x80];
    /* 0x324 */ u8 timer[4];
    /* 0x328 */ u8 state[4];
    /* 0x32c */ u8 bgPalette;
};

#endif
