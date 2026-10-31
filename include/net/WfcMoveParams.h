#ifndef NET_WFCMOVEPARAMS_H
#define NET_WFCMOVEPARAMS_H

#include "types.h"

struct WfcMoveParams {
    /* 0x00 */ const char *romFilePath;
    /* 0x04 */ u16 *gameName;
    /* 0x08 */ u16 *gameIntroduction;
    /* 0x0c */ const char *iconCharPath;
    /* 0x10 */ const char *iconPalettePath;
    /* 0x14 */ u32 ggid;
    /* 0x18 */ u8 languageCode;
};

#endif
