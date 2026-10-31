#include "types.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/ModelAnim.h"
#include "proto/main/unk_02055b90.h"
#include "proto/main/unk_02055bcc.h"




char sJointAnmHeader[4] = {'J', 0, 'A', 'C'};

BOOL ModelAnim::allocJointAnm(NNSG3dResMdl *a, void *c) {
    if (anmObj != NULL || resMdl != NULL) {
        return FALSE;
    }
    anmObj = (NNSG3dAnmObj *)Gfx3d_AllocAnmObj(a, sJointAnmHeader, c);
    resMdl = a;
    if (anmObj != NULL) {
        return TRUE;
    }
    return FALSE;
}
