#ifndef GFX_TEXVRAMTASK_H
#define GFX_TEXVRAMTASK_H

#include "types.h"
#include "gfx/VramTask.h"
#include "gfx/TexTransfer.h"

class TexVramTask : public VramTask {
public:
    /* 0x10 */ TexTransfer xfer;

    TexVramTask();
    virtual BOOL execute();
    BOOL requestMatTex(void *a, u32 b, void *c);
    void cancel(void);
    void prepare(void);
    BOOL requestTexResource(u32 *a, u8 b);
    BOOL requestPltt(void *src, u32 dst, u32 size, u8 prio);
    BOOL requestTex(void *src, u32 dst, u32 size, u8 prio);
    void clear(void);
};

#endif
