#ifndef GFX_VRAMTASK_H
#define GFX_VRAMTASK_H

#include "types.h"
#include "sys/PrioListNode.h"

class VramTask : public PrioListNode {
public:
    u8 state;
    u8 kind;
    u8 cost;

    VramTask();
    virtual BOOL execute() = 0;
    void dequeueTex(void);
    BOOL enqueueTex(void);
    void resetState(void);
};

#endif
