#ifndef GFX_GFXFRAMEHOOKS_H
#define GFX_GFXFRAMEHOOKS_H

#include "types.h"

class GfxFrameHooks {
public:
    virtual inline void onPreTask() {}
    virtual inline void onPostTask() {}
    virtual void onVBlank();
};

#endif
