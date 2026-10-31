#ifndef SYS_STACKPAD_H
#define SYS_STACKPAD_H

#include "types.h"

struct StackPad4 {
    /* 0x00 */ s32 v[1];
    StackPad4() {}
    ~StackPad4() {}
};

struct StackPad8 {
    /* 0x00 */ s32 v[2];
    StackPad8() {}
    ~StackPad8() {}
};

struct StackPad12 {
    /* 0x00 */ s32 v[3];
    StackPad12() {}
    ~StackPad12() {}
};

struct StackPad16 {
    /* 0x00 */ s32 v[4];
    StackPad16() {}
    ~StackPad16() {}
};

struct StackPad24 {
    /* 0x00 */ s32 v[6];
    StackPad24() {}
    ~StackPad24() {}
};

#endif
