#ifndef UI_WFCTEXTKB_H
#define UI_WFCTEXTKB_H

#include "types.h"
#include "nitro/gxoam.h"
#include "net/WfcObjGroup.h"

struct WfcTextCanvas;
typedef struct WfcTextCanvas WfcTextCanvas;
typedef struct WfcTextKb WfcTextKb;
typedef struct WfcNumPad WfcNumPad;

struct WfcTextKb {
    /* 0x000 */ WfcTextCanvas *rowCanvases[3][4];
    /* 0x030 */ GXOamAttr *charKeyOams[0x2f];
    /* 0x0ec */ GXOamAttr *funcKeyOams[4];
    /* 0x0fc */ WfcObjGroup *bottomButtons[2];
    /* 0x104 */ WfcObjGroup *rowTextObjs[4];
    /* 0x114 */ WfcObjGroup *cursorObj;
    /* 0x118 */ void *task;
    /* 0x11c */ u8 inputKey;
    /* 0x11d */ u8 caseMode;
    /* 0x11e */ s8 touchKey;
    /* 0x11f */ s8 highlightKey;
    /* 0x120 */ s8 prevCursorKey;
    /* 0x121 */ s8 cursorKey;
    /* 0x122 */ u8 deleteHoldTimer;
    /* 0x123 */ u8 deleteEnabled;
    /* 0x124 */ u8 insertEnabled;
    /* 0x125 */ u8 errorSoundPlayed;
};

struct WfcNumPad {
    /* 0x00 */ WfcTextCanvas *rowCanvases[4];
    /* 0x10 */ GXOamAttr *digitKeyOams[10];
    /* 0x38 */ GXOamAttr *funcKeyOams[2];
    /* 0x40 */ WfcObjGroup *bottomButtons[2];
    /* 0x48 */ WfcObjGroup *rowTextObjs[4];
    /* 0x58 */ WfcObjGroup *cursorObj;
    /* 0x5c */ void *task;
    /* 0x60 */ u8 inputKey;
    /* 0x61 */ s8 touchKey;
    /* 0x62 */ s8 highlightKey;
    /* 0x63 */ s8 cursorKey;
    /* 0x64 */ s8 prevCursorKey;
    /* 0x65 */ u8 deleteHoldTimer;
    /* 0x66 */ u8 deleteEnabled;
    /* 0x67 */ u8 insertEnabled;
    /* 0x68 */ u8 dotEnabled;
    /* 0x69 */ u8 errorSoundPlayed;
};

#endif
