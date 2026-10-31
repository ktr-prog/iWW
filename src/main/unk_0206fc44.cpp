#include "types.h"
#include "gfx/VecFx32.h"
#include "text/Unk_02050288.h"
#include "gfx/Mtx43.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "ui/LabelString.h"
#include "talk/EncodedString41.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_0206f804.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_0206fc44.h"
#include "proto/main/unk_0206fde4.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"

Mtx43 data_021cb69c;

extern "C" {
void MsgTextLabel_Destroy(TextLabel *obj);
void MTX_Copy33To43_(void *a, void *b);
s32 func_01ffcb0c(s32 a, s32 b);
void MTX_Concat43(void *a, void *b, void *c);
void MTX_Identity43_(void *p);
}

void CpuMtx_MultRotTrans(void *a, VecFx32 *v) {
    Mtx43 m;
    MTX_Copy33To43_(a, &m);
    m.m[9] = v->x;
    m.m[10] = v->y;
    m.m[11] = v->z;
    MTX_Concat43(&m, &data_021cb69c, &data_021cb69c);
}

void CpuMtx_MultTrans(VecFx32 *v) {
    Mtx43 m;
    MTX_Identity43_(&m);
    m.m[9] = v->x;
    m.m[10] = v->y;
    m.m[11] = v->z;
    MTX_Concat43(&m, &data_021cb69c, &data_021cb69c);
}

void CpuMtx_MultRot(void *a) {
    Mtx43 m;
    MTX_Copy33To43_(a, &m);
    MTX_Concat43(&m, &data_021cb69c, &data_021cb69c);
}

void CpuMtx_MultRotScaledTrans(void *a, VecFx32 *v, VecFx32 *w) {
    Mtx43 m;
    MTX_Copy33To43_(a, &m);
    if (w == NULL) {
        m.m[9] = v->x;
        m.m[10] = v->y;
        m.m[11] = v->z;
    } else {
        m.m[9] = func_01ffcb0c(v->x, w->x);
        m.m[10] = func_01ffcb0c(v->y, w->y);
        m.m[11] = func_01ffcb0c(v->z, w->z);
    }
    MTX_Concat43(&m, &data_021cb69c, &data_021cb69c);
}

LabelString::LabelString() {
    clear();
    label = NULL;
}

LabelString::~LabelString() { destroyLabel(); }

u32 LabelString::capacity() { return 0x2a; }

u8 *LabelString::data() { return text; }

void LabelString::destroyLabel() {
    if (label != NULL) {
        MsgTextLabel_Destroy(label);
        label = NULL;
    }
}

static inline u32 Unk_0206fe34_Id(u32 i) {
    if (i < 0x34) {
        return i * 4 + 0x450c;
    }
    return 0x450c;
}
