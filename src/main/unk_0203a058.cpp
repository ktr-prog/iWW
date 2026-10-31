#include "types.h"
#include "gfx/ViewFrustum.h"


ViewFrustum::ViewFrustum() {
    setPerspective(0x1555, 0xe38, 0x1000, 0x1388000);
}

void ViewFrustum::setPerspective(s32 a, u16 b, s32 c, s32 d) {
    aspect = a;
    fovy = b;
    nearClip = c;
    farClip = d;
    (this)->calcPlanes();
}
