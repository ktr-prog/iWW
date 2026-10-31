#include "types.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/ModelAnim.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02055bcc.h"



extern "C" {
u32 NNS_G3dAnmObjCalcSizeRequired(const char *a, NNSG3dResMdl *b);
}

char sMatAnmHeader[4] = {'M', 0, 'A', 'T'};

extern "C" void *Gfx3d_AllocAnmObj(NNSG3dResMdl *a, const char *b, void *c) {
    if (a == NULL) {
        return NULL;
    }
    u32 n = NNS_G3dAnmObjCalcSizeRequired(b, a);
    Heap *heap = static_cast<Heap *>(c);
    if (heap == NULL) {
        heap = gCurrentHeap;
    }
    return Heap_Alloc(heap, n);
}

BOOL ModelAnim::allocMatAnm(NNSG3dResMdl *a, void *c) {
    if (anmObj != NULL || resMdl != NULL) {
        return FALSE;
    }
    anmObj = (NNSG3dAnmObj *)Gfx3d_AllocAnmObj(a, sMatAnmHeader, c);
    resMdl = a;
    if (anmObj != NULL) {
        return TRUE;
    }
    return FALSE;
}
