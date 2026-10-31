#include "types.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "town/TownBlockMap.h"
#include "game/Unk_02095774_Ent.h"
#include "net/PlayerNetSync.h"
#include "item/ItemPickSpec.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095b1c.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"


inline BOOL Unk_0209579c_IsTwo(u8 v) {
    if (v == 2) return TRUE;
    return FALSE;
}

inline u16 Unk_02095f38_F(u32 v) {
    if (v < 5) return (u16)(v + 0x1518);
    return 0x1518;
}

extern CommManager *gCommManager;


extern "C" {
}

inline BOOL Unk_02095dcc_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

static inline void Unk_0209579c_Set(s16 *d, s16 a, s16 b, s16 c) {
    d[0] = a;
    d[1] = b;
    d[2] = c;
}

ProcProfile sPlayerNetSyncProfile = {(void *(*)())&PlayerNetSync::create, 10, 14};

GameProc *PlayerNetSync::create() { return new PlayerNetSync(); }

PlayerNetSync::PlayerNetSync() {}

PlayerNetSync::~PlayerNetSync() {}

BOOL PlayerNetSync::onCreate() { return TRUE; }

BOOL PlayerNetSync::onExecute() {
    CommManager *g;
    s32 i, m1;
    s32 *p8;
    u8 *pc;
    VecFx32 *r4;
    s16 *p10;
    s32 idx;
    u8 c;
    s16 s;
    s32 v, x, y;
    i = 3;
    g = gCommManager;
    m1 = -1;
    do {
        if ((g)->isSlotActive(i) && !(g)->isMyAid(i)) {
            idx = i;
            c = NetArea_GetSlotScene(i);
            p8 = PlayerSession_GetLastAction(idx);
            pc = PlayerSession_GetLastScene(idx);
            r4 = PlayerSession_GetLastPos(idx);
            p10 = PlayerSession_GetLastAngle(idx);
            if (c != 0xc && c != 0xd && c != 0xe && c != 0x2f && c != 0x2e) {
                if (PlayerActor_GetSlotAction((u32 *)&v, m1, idx)) {
                    if (PlayerActor_GetSlotPosXZ(&c, &x, &y, m1, idx)) {
                        if (PlayerActor_GetSlotAngle(&s, m1, idx)) {
                            PlayerSession_RemovePitfallOnClimbOut(&idx, &c, p8, &v, &x, &y);
                            *p8 = v;
                            *pc = c;
                            s32 yt = y;
                            r4->x = x;
                            r4->y = 0;
                            r4->z = yt;
                            *p10 = s;
                        }
                    }
                }
            }
        }
        i--;
    } while (i >= 0);
    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
        Actor *o = (Actor *)PlayerActor_GetActor(4);
        if (o) {
            s32 n = g->localSlot;
            if (n < 4) {
                CommSyncVar_SetVar(n + 4, &o->rotY, 0, 0);
                CommSyncVar_SetVar(n, &o->position, 0, 0);
                CommSyncVar_SetVar(n + 8, 0, 0, 0);
            }
        }
    }
    return TRUE;
}

BOOL PlayerNetSync::onDraw() { return TRUE; }

BOOL PlayerNetSync::onDelete() { return TRUE; }

