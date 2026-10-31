#ifndef UI_WFCAPLIST_H
#define UI_WFCAPLIST_H

#include "types.h"
#include "nitro/gxoam.h"
#include "net/WfcApScanEntry.h"

struct WfcTextCanvas;

struct WfcApList {
    /* 0x00 */ WfcApScanEntry *apEntries;
    /* 0x04 */ void *bgMapFile;
    /* 0x08 */ void *paletteFile;
    /* 0x0c */ WfcTextCanvas *textCanvas;
    /* 0x10 */ GXOamAttr *securityIcons[5];
    /* 0x24 */ GXOamAttr *signalIcons[5];
    /* 0x38 */ void *scrollTask;
    /* 0x3c */ void *bgScrollTask;
    /* 0x40 */ u16 maxScroll;
    /* 0x42 */ u16 securityIconTiles[3];
    /* 0x48 */ u16 signalIconTiles[4];
    /* 0x50 */ s8 touchRow;
    /* 0x51 */ u8 apCount;
    /* 0x52 */ u8 selectedAp;
    /* 0x53 */ u8 scrollBarRange;
    /* 0x54 */ u8 isConfirmed;
    /* 0x55 */ u8 dragRedrawDelay;
    /* 0x56 */ u8 bgScrollPending;
    /* 0x57 */ u8 isDragging;
    /* 0x58 */ u8 scrollEndSoundPlayed;
    /* 0x59 */ u8 errorSoundPlayed;
};

#endif
