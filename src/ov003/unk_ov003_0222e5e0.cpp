#include "types.h"
#include "net/CommManager.h"
#include "field/InsectNetSync.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov003/unk_ov003_0222e5e0.h"

struct InsectNetSyncRec {
    s32 x, y, z;
    s8 kind;
    u8 alarm;
    u8 pad[2];
    InsectNetSyncRec() {}
    ~InsectNetSyncRec() {}
};


extern "C" {
extern CommManager *gCommManager;

void MI_CpuCopy8(void *, void *, s32);
}

InsectNetSyncRec sInsectNetSync[8];

InsectNetSync::InsectNetSync() {}

InsectNetSync::~InsectNetSync() {}

extern "C" BOOL InsectNetSync_Set(void *unused, s32 idx, s32 v, s32 *p, u8 e, s32 f) {
    if (NetArea_IsLocalOwner()) {
        if (gCommManager->isOnline()) {
            CommSyncVar_SetVar(idx + 0x18, &f, 0, 0);
            InsectNetSyncRec *r = &sInsectNetSync[idx];
            r->kind = v;
            r->x = p[0];
            r->y = p[1];
            r->z = p[2];
            r->alarm = e;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void InsectNetSync_PackVar(void *dst, s32 idx) {
    InsectNetSyncRec *r = &sInsectNetSync[idx - 0x18];
    u8 rec[8];
    NetBuf_PackPair20(rec, r->x, r->z);
    rec[5] = r->kind;
    rec[6] = r->alarm;
    MI_CpuCopy8(rec, dst, CommSyncVar_GetVarSize(idx));
}

extern "C" BOOL InsectNetSync_Get(void *a, s32 b, s8 *c, s32 *d, s32 *e, u8 *f) {
    if (!NetArea_IsLocalOwner()) {
        CommManager *g = gCommManager;
        if (g->isOnline()) {
            u8 *r = g->getSyncVar(b + 0x18);
            if (r != 0) {
                NetBuf_UnpackPair20(r, (u32 *)d, (u32 *)e);
                if (*e > 0) {
                    *c = (s8)r[5];
                    *f = r[6];
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_0222e5e0) {
    HOST_OVERLAY_VAR(sInsectNetSync),
    HOST_OVERLAY_VARS_END
};
