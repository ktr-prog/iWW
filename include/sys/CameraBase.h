#ifndef SYS_CAMERABASE_H
#define SYS_CAMERABASE_H

#include "types.h"
#include "sys/ProcBase.h"

class CameraBase : public GameProc {
public:
    virtual BOOL onDraw();
};

#endif
