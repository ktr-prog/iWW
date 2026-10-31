#ifndef GFX_MATTEXVRAMTASK_H
#define GFX_MATTEXVRAMTASK_H

#include "types.h"
#include "gfx/VramTask.h"
#include "gfx/TexTransfer.h"

class MatTexVramTask : public VramTask {
public:
    /* 0x10 */ TexTransfer texXfer;
    /* 0x1c */ TexTransfer plttXfer;

    MatTexVramTask();
    virtual BOOL execute();
    BOOL request(void *mdl, const char *matName, void *tex, u32 texIdx, u32 plttIdx);
    void prepare(void);
    void cancel(void);
    void clear(void);
};

#endif
