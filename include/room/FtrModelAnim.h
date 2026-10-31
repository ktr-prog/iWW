#ifndef ROOM_FTRMODELANIM_H
#define ROOM_FTRMODELANIM_H

#include "types.h"
#include "gfx/ModelAnim.h"

class FtrModelAnim : public ModelAnim {
public:
    FtrModelAnim();
    virtual ~FtrModelAnim();
    NNSG3dAnmObj *getAnmObj();
};

#endif
