#include "types.h"
#include "net/Unk_ov001_02221734_D.h"
#include "nitro/os_rtc.h"
#include "net/WfcMoveMbWork.h"
#include "nitro/fs.h"
#include "proto/autoload_2/unk_02115468.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02122e24.h"
#include "proto/autoload_2/unk_02124c40.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02220ad8.h"

#pragma thumb off

extern "C" WfcMoveMbWork *sWfcMoveMb;
extern "C" u16 *sWfcMoveMbMaskPtrs[6];

extern "C" {
u32 OS_DisableInterrupts();
void OS_RestoreInterrupts(u32);
void MI_CpuCopy8(void *, void *, u32);
s32 MB_CommResponseRequest(s32, s32);
s32 MB_CommIsBootable(s32);
const void *MB_CommGetChildUser(s32);
void MB_DisconnectChild(s32);
s32 FS_OpenFile(FSFile *, const char *);
s32 MB_GetSegmentLength(FSFile *);
s32 MB_ReadSegment(FSFile *, void *, u32);
s32 MB_RegisterFile(const MBGameRegistry *, void *);
void FS_CloseFile(FSFile *);
s32 MB_StartParentFromIdle(s32);
s32 MB_Init(void *, void *, s32, s32, s32);
void MB_SetParentCommParam(u32, u32);
void WfcMoveWh_SetWork(void *);
}

static_assert(sizeof(WfcMoveMbWork) <= WFC_MOVE_WH_WORK_OFFSET, "WfcMoveMbWork overlaps the WfcMoveWhWork");

void WfcMoveMb_SetWork(void *p) {
    sWfcMoveMb = (WfcMoveMbWork *)p;
    WfcMoveWh_SetWork((u8 *)p + WFC_MOVE_WH_WORK_OFFSET);
    sWfcMoveMb->mbWork = 0;
    sWfcMoveMb->segmentBuffer = 0;
}

void WfcMoveMb_Init(s32 a, s32 b) {
    Unk_ov001_02221734_D d;
    OSOwnerInfo buf;
    OS_GetOwnerInfo(&buf);
    d.lo = buf.favoriteColor;
    d.b1 = buf.nickNameLength;
    MI_CpuCopy8(buf.nickName, d.data, buf.nickNameLength * 2);
    d.hi = 0;
    WfcMoveMbStateCopy *zp = &d.z;
    zp->v[0] = 0;
    zp->v[1] = 0;
    zp->v[2] = 0;
    zp->v[3] = 0;
    zp->v[4] = 0;
    zp->v[5] = 0;
    zp->v[6] = 0;
    sWfcMoveMb->stateCopy = *zp;
    sWfcMoveMb->mbWork = sWfcMoveMb->mbSystemWork;
    if (MB_Init(sWfcMoveMb->mbWork, &d, a, b, 2) != 0) Fatal_Trap();
    MB_SetParentCommParam(0x100, 1);
    MB_CommSetParentStateCallback((void (*)())WfcMoveMb_ParentStateCallback);
    WfcMoveMb_SetState(1);
}

void WfcMoveMb_StartParent(MBGameRegistry *a, s32 b) {
    WfcMoveMb_SetState(2);
    if (MB_StartParentFromIdle(b) != 0) {
        WfcMoveMb_SetState(7);
        return;
    }
    if (WfcMoveMb_RegisterFile(a) != 0) return;
    Fatal_Trap();
}

s32 WfcMoveMb_RegisterFile(MBGameRegistry *p) {
    FSFile *q;
    s32 r = 0;
    FSFile file;
    if (p->romFilePathp == 0) {
        q = 0;
    } else {
        FS_InitFile(&file);
        if (FS_OpenFile(&file, p->romFilePathp) == 0) return r;
        q = &file;
    }
    if (MB_GetSegmentLength(q) != 0) {
        WfcMoveMbWork *g = sWfcMoveMb;
        g->segmentBuffer = g->segment;
        if (sWfcMoveMb->segmentBuffer != 0) {
            if (MB_ReadSegment(q, sWfcMoveMb->segmentBuffer, 0x10000) != 0) {
                if (MB_RegisterFile(p, sWfcMoveMb->segmentBuffer) != 0) r = 1;
            }
        }
    }
    if (q == &file) FS_CloseFile(&file);
    return r;
}

void WfcMoveMb_AcceptChild(u32 n) {
    if (MB_CommResponseRequest(n, 1) != 0) return;
    u16 m = ~(1 << n);
    s32 e = OS_DisableInterrupts();
    sWfcMoveMb->childMasks[0] &= m;
    sWfcMoveMb->childMasks[1] &= m;
    sWfcMoveMb->childMasks[2] &= m;
    sWfcMoveMb->childMasks[3] &= m;
    sWfcMoveMb->childMasks[4] &= m;
    sWfcMoveMb->childMasks[5] &= m;
    OS_RestoreInterrupts(e);
    MB_DisconnectChild(n);
}

void WfcMoveMb_KickChild(u32 n) {
    if (MB_CommResponseRequest(n, 0) == 0) {
        u16 m = ~(1 << n);
        s32 e = OS_DisableInterrupts();
        sWfcMoveMb->childMasks[0] &= m;
        sWfcMoveMb->childMasks[1] &= m;
        sWfcMoveMb->childMasks[2] &= m;
        sWfcMoveMb->childMasks[3] &= m;
        sWfcMoveMb->childMasks[4] &= m;
        sWfcMoveMb->childMasks[5] &= m;
        OS_RestoreInterrupts(e);
        MB_DisconnectChild(n);
    } else {
        s32 e = OS_DisableInterrupts();
        u32 m = ~(1 << n);
        sWfcMoveMb->childMasks[1] &= m;
        sWfcMoveMb->childMasks[0] &= m;
        OS_RestoreInterrupts(e);
    }
}

void WfcMoveMb_StartDownload(u32 id)
{
    if (MB_CommResponseRequest(id, 2) == 0) {
        u16 k = ~(1 << id);
        u32 r = OS_DisableInterrupts();
        sWfcMoveMb->childMasks[0] &= k;
        sWfcMoveMb->childMasks[1] &= k;
        sWfcMoveMb->childMasks[2] &= k;
        sWfcMoveMb->childMasks[3] &= k;
        sWfcMoveMb->childMasks[4] &= k;
        sWfcMoveMb->childMasks[5] &= k;
        OS_RestoreInterrupts(r);
        MB_DisconnectChild(id);
    } else {
        u32 r = OS_DisableInterrupts();
        u32 one = 1;
        WfcMoveMbWork *s = sWfcMoveMb;
        s->childMasks[2] = s->childMasks[2] & ~(one << id);
        s = sWfcMoveMb;
        s->childMasks[3] = s->childMasks[3] | (one << id);
        OS_RestoreInterrupts(r);
    }
}

void WfcMoveMb_StartDownloadAll()
{
    WfcMoveMb_SetState(3);
    u16 i;
    for (i = 1; i < 16; i++) {
        u32 bit = 1 << i;
        if (sWfcMoveMb->childMasks[0] & bit) {
            if (!(sWfcMoveMb->childMasks[1] & bit)) {
                if (!(sWfcMoveMb->childMasks[2] & bit)) {
                    u16 k = ~bit;
                    u32 r = OS_DisableInterrupts();
                    sWfcMoveMb->childMasks[0] &= k;
                    sWfcMoveMb->childMasks[1] &= k;
                    sWfcMoveMb->childMasks[2] &= k;
                    sWfcMoveMb->childMasks[3] &= k;
                    sWfcMoveMb->childMasks[4] &= k;
                    sWfcMoveMb->childMasks[5] &= k;
                    OS_RestoreInterrupts(r);
                    MB_DisconnectChild(i);
                } else {
                    WfcMoveMb_StartDownload(i);
                }
            }
        }
    }
}

u32 WfcMoveMb_IsAllBootable()
{
    if (sWfcMoveMb->childMasks[0] == 0) return 0;
    u16 i;
    for (i = 1; i < 16; i++) {
        if (sWfcMoveMb->childMasks[0] & (1 << i)) {
            if (MB_CommIsBootable(i) == 0) return 0;
        }
    }
    return 1;
}

void WfcMoveMb_StartRebootAll()
{
    u16 i, ok;
    ok = 0;
    for (i = 1; i < 16; i++) {
        u32 bit = 1 << i;
        if (sWfcMoveMb->childMasks[4] & bit) {
            if (MB_CommResponseRequest(i, 3)) {
                ok = ok | bit;
            } else {
                u16 k = ~bit;
                u32 r = OS_DisableInterrupts();
                sWfcMoveMb->childMasks[0] &= k;
                sWfcMoveMb->childMasks[1] &= k;
                sWfcMoveMb->childMasks[2] &= k;
                sWfcMoveMb->childMasks[3] &= k;
                sWfcMoveMb->childMasks[4] &= k;
                sWfcMoveMb->childMasks[5] &= k;
                OS_RestoreInterrupts(r);
                MB_DisconnectChild(i);
            }
        }
    }
    if (ok == 0) {
        WfcMoveMb_SetState(7);
    } else {
        WfcMoveMb_SetState(4);
    }
}

void WfcMoveMb_Cancel()
{
    WfcMoveMb_SetState(6);
    MB_End();
}

void WfcMoveMb_ParentStateCallback(u32 id, u32 cmd, u8 *data)
{
    switch (cmd) {
    case 1:
    case 4:
    case 5:
    case 6:
    case 8:
    case 11:
        break;
    case 2: {
        if (WfcMoveMb_GetState() != 2) return;
        WfcMoveMbWork *s = sWfcMoveMb;
        u32 r = OS_DisableInterrupts();
        s->childMasks[0] = s->childMasks[0] | (1 << id);
        OS_RestoreInterrupts(r);
        u8 *e = sWfcMoveMb->children[id - 1].mac;
        e[0] = data[0xa];
        e[1] = data[0xb];
        e[2] = data[0xc];
        e[3] = data[0xd];
        e[4] = data[0xe];
        e[5] = data[0xf];
        sWfcMoveMb->children[id - 1].aid = id;
        break;
    }
    case 3: {
        if (WfcMoveMb_GetChildState(id) == 6) return;
        u16 k = ~(1 << id);
        u32 r = OS_DisableInterrupts();
        sWfcMoveMb->childMasks[0] &= k;
        sWfcMoveMb->childMasks[1] &= k;
        sWfcMoveMb->childMasks[2] &= k;
        sWfcMoveMb->childMasks[3] &= k;
        sWfcMoveMb->childMasks[4] &= k;
        sWfcMoveMb->childMasks[5] &= k;
        OS_RestoreInterrupts(r);
        break;
    }
    case 10: {
        if (WfcMoveMb_GetState() != 2) {
            WfcMoveMb_KickChild(id);
            return;
        }
        WfcMoveMbWork *s = sWfcMoveMb;
        s->childMasks[1] = s->childMasks[1] | (1 << id);
        WfcMoveMb_AcceptChild(id);
        const void *r = MB_CommGetChildUser(id);
        if (r == 0) return;
        MI_CpuCopy8((void *)r, sWfcMoveMb->children[id - 1].userInfo, 0x16);
        break;
    }
    case 14: {
        WfcMoveMbWork *s = sWfcMoveMb;
        u32 one = 1;
        s->childMasks[1] = s->childMasks[1] & ~(one << id);
        s = sWfcMoveMb;
        s->childMasks[2] = s->childMasks[2] | (one << id);
        if (WfcMoveMb_GetState() != 3) return;
        WfcMoveMb_StartDownload(id);
        break;
    }
    case 7: {
        WfcMoveMbWork *s = sWfcMoveMb;
        u32 one = 1;
        s->childMasks[3] = s->childMasks[3] & ~(one << id);
        s = sWfcMoveMb;
        s->childMasks[4] = s->childMasks[4] | (one << id);
        break;
    }
    case 9: {
        WfcMoveMbWork *s = sWfcMoveMb;
        u32 one = 1;
        s->childMasks[4] = s->childMasks[4] & ~(one << id);
        s = sWfcMoveMb;
        s->childMasks[5] = s->childMasks[5] | (one << id);
        s = sWfcMoveMb;
        if (s->childMasks[0] != s->childMasks[5]) return;
        MB_End();
        break;
    }
    case 12: {
        if (WfcMoveMb_GetState() == 4) {
            WfcMoveMb_SetState(5);
        } else {
            WfcMoveMb_SetState(0);
        }
        WfcMoveMbWork *z = sWfcMoveMb;
        if (z->segmentBuffer != 0) z->segmentBuffer = 0;
        z = sWfcMoveMb;
        if (z->mbWork != 0) z->mbWork = 0;
        break;
    }
    case 13: {
        s32 v = *(u16 *)data;
        switch (v) {
        case 1:
        case 2:
        case 9:
            WfcMoveMb_SetState(7);
            break;
        case 8:
            break;
        }
        break;
    }
    default:
        Fatal_Trap();
        break;
    }
}

void WfcMoveMb_SetState(u32 v)
{
    sWfcMoveMb->state = v;
}

u32 WfcMoveMb_GetState()
{
    return sWfcMoveMb->state;
}

u32 WfcMoveMb_GetChildMask(u32 i)
{
    WfcMoveMbWork *s = sWfcMoveMb;
    sWfcMoveMbMaskPtrs[0] = &s->childMasks[0];
    sWfcMoveMbMaskPtrs[1] = &s->childMasks[1];
    sWfcMoveMbMaskPtrs[2] = &s->childMasks[2];
    sWfcMoveMbMaskPtrs[3] = &s->childMasks[3];
    sWfcMoveMbMaskPtrs[4] = &s->childMasks[4];
    sWfcMoveMbMaskPtrs[5] = &s->childMasks[5];
    return *sWfcMoveMbMaskPtrs[i];
}

u32 WfcMoveMb_GetChildState(u32 id)
{
    WfcMoveMbStateCopy st;
    u32 r = OS_DisableInterrupts();
    u16 bit = 1 << id;
    WfcMoveMbWork *s = sWfcMoveMb;
    if (!(s->childMasks[0] & bit)) {
        OS_RestoreInterrupts(r);
        return 0;
    }
    MI_CpuCopy8(&s->stateCopy, &st, sizeof(st));
    OS_RestoreInterrupts(r);
    u16 *masks = &st.v[1];
    if (masks[1] & bit) return 2;
    if (masks[2] & bit) return 3;
    if (masks[3] & bit) return 4;
    if (masks[4] & bit) return 5;
    if (masks[5] & bit) return 6;
    return 1;
}

u8 *WfcMoveMb_GetChildInfo(u32 id)
{
    WfcMoveMbWork *s = sWfcMoveMb;
    if (s->childMasks[0] & (1 << id)) {
        return s->children[id - 1].userInfo;
    }
    return 0;
}

u32 WfcMoveMb_FindAidByMac(u8 *mac)
{
    WfcMoveMbWork *s = sWfcMoveMb;
    u16 i;
    u16 mask = s->childMasks[0];
    for (i = 1; i < 2; i++) {
        if (mask & (1 << i)) {
            u8 *e = s->children[i - 1].mac;
            if (mac[0] == e[0] && mac[1] == e[1] && mac[2] == e[2] && mac[3] == e[3] && mac[4] == e[4] && mac[5] == e[5]) {
                return s->children[i - 1].aid;
            }
        }
    }
    return 0;
}

extern "C" WfcMoveMbWork *sWfcMoveMb = 0;
extern "C" u16 *sWfcMoveMbMaskPtrs[6] = {0, 0, 0, 0, 0, 0};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02220ad8) {
    HOST_OVERLAY_VAR(sWfcMoveMb),
    HOST_OVERLAY_VAR(sWfcMoveMbMaskPtrs),
    HOST_OVERLAY_VARS_END
};
