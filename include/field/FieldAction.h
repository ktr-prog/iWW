#ifndef FIELD_FIELDACTION_H
#define FIELD_FIELDACTION_H

#include "types.h"


struct FieldActionRequestMsg {
    /* 0x00 */ u8 aid : 2;
    /*      */ u8 requestIndex : 2;
    /*      */ u8 unitFlag : 2;
    /*      */ u8 unk_00_6 : 2;
    /* 0x01 */ u8 kind : 5;
    /*      */ u8 mode : 2;
    /*      */ u8 layer : 1;
    /* 0x02 */ u16 unit;
    /* 0x04 */ u16 oldItem;
    /* 0x06 */ u16 item;
};

struct FieldActionResultMsg {
    /* 0x00 */ u8 hasDrops : 1;
    /*      */ u8 aid : 2;
    /*      */ u8 kind : 5;
    /* 0x01 */ u8 requestIndex : 2;
    /*      */ u8 accepted : 1;
    /*      */ u8 unitFlag : 2;
    /*      */ u8 mode : 2;
    /*      */ u8 layer : 1;
    /* 0x02 */ u16 unit;
    /* 0x04 */ u16 item;
    /* 0x06 */ union {
        u16 dropUnits[3];
        u8 dropUnitBytes[3][2];
    };
    /* 0x0c */ u16 dropItem;
};

union PackedUnitPos {
    u16 v;
    struct {
        u8 z;
        u8 x;
    } b;
};

struct PendingUnit {
    /* 0x00 */ u8 aid : 3;
    /*      */ u8 kind : 5;
    /* 0x01 */ u8 unitFlag : 2;
    /*      */ u8 slot : 3;
    /*      */ u8 mode : 2;
    /*      */ u8 committed : 1;
    /* 0x02 */ u8 pending : 1;
    /*      */ u8 layer : 1;
    /*      */ s8 unk_02_c : 4;
    /*      */ s8 unk_02_d : 2;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ PackedUnitPos unit;
    /* 0x0a */ u16 item;
    /* 0x0c */ u16 oldItem;
    /* 0x0e */ u16 unk_0e;
};

#endif
