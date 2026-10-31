#ifndef SYS_CMDSEQ_H
#define SYS_CMDSEQ_H

#include "types.h"

class CmdSeq {
public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual s32 vfunc_08(void *p);
    virtual void vfunc_0c(void *p);

    /* 0x04 */ s16 state;
    /* 0x06 */ s16 cmdIndex;
    /* 0x08 */ void **cmds;
    /* 0x0c */ u32 unk_0c;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ s16 cmdStep;
};

#endif
