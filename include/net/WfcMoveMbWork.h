#ifndef NET_WFCMOVEMBWORK_H
#define NET_WFCMOVEMBWORK_H

#include "types.h"
#include "net/Unk_ov001_02221734_D.h"

struct MBGameRegistry {
    /* 0x00 */ const char *romFilePathp;
    /* 0x04 */ u16 *gameNamep;
    /* 0x08 */ u16 *gameIntroductionp;
    /* 0x0c */ const char *iconCharPathp;
    /* 0x10 */ const char *iconPalettePathp;
    /* 0x14 */ u32 ggid;
    /* 0x18 */ u8 maxPlayerNum;
    /* 0x19 */ u8 pad[3];
    /* 0x1c */ u8 userParam[32];
};

struct WfcMoveMbChild {
    /* 0x00 */ u8 userInfo[0x16];
    /* 0x16 */ u8 mac[6];
    /* 0x1c */ u16 aid;
};

struct WfcMoveMbWork {
    union {
        struct {
            /* 0x00000 */ u16 state;
            /* 0x00002 */ u16 childMasks[6];
        };
        WfcMoveMbStateCopy stateCopy;
    };
    /* 0x0000e */ WfcMoveMbChild children[1];
    /* 0x0002c */ u8 segment[0x10014];
    /* 0x10040 */ u8 mbSystemWork[0xb100];
    /* 0x1b140 */ void *mbWork;
    /* 0x1b144 */ void *segmentBuffer;
};

#define WFC_MOVE_WH_WORK_OFFSET 0x1b160

#endif
