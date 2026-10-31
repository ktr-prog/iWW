#ifndef GAME_STARSKYVIEW_H
#define GAME_STARSKYVIEW_H

#include "types.h"
#include "gfx/BgVramTask.h"

class StarSkyView {
public:
    StarSkyView();
    ~StarSkyView();
    /* 0x0000 */ BgVramTask screenTask;
    /* 0x0024 */ u16 skyScreen[0x800];
    /* 0x1024 */ u16 skyScreenWork[0x800];
    /* 0x2024 */ u16 scopeScreen[0x400];
    /* 0x2824 */ s16 scrollX;
    /* 0x2826 */ s16 scrollY;
    /* 0x2828 */ s16 overscroll;
    /* 0x282a */ s16 targetScrollX;
    /* 0x282c */ s16 targetScrollY;
    /* 0x282e */ s16 clipRows;
    /* 0x2830 */ u16 flags;
    /* 0x2832 */ u8 skyLayer;
    /* 0x2833 */ u8 scopeLayer;
    /* 0x2834 */ u8 activeArrow;
    /* 0x2835 */ u8 bounceDir;
    /* 0x2836 */ u8 bounceTimer;
};

#endif
