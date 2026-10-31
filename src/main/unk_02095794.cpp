#include "types.h"
#include "gfx/VecFx32.h"
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
#include "proto/main/unk_02095794.h"
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
s32 Scene_GetCurrent();
}

inline BOOL Unk_02095dcc_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

class RemotePlayerSpawner : public GameProc {
public:
    static GameProc *create();
    RemotePlayerSpawner();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~RemotePlayerSpawner();
};

static inline void Unk_0209579c_Set(s16 *d, s16 a, s16 b, s16 c) {
    d[0] = a;
    d[1] = b;
    d[2] = c;
}

ProcProfile sRemotePlayerSpawnerProfile = {(void *(*)())&RemotePlayerSpawner::create, 8, 12};

GameProc *RemotePlayerSpawner::create() { return new RemotePlayerSpawner(); }

RemotePlayerSpawner::RemotePlayerSpawner() {}

RemotePlayerSpawner::~RemotePlayerSpawner() {}

BOOL RemotePlayerSpawner::onCreate() { return TRUE; }

BOOL RemotePlayerSpawner::onExecute() {
    CommManager *g = gCommManager;
    s32 mode = g->myAid;
    u8 la, lb;
    s16 lc;
    s16 lr1[3];
    s32 lv1, lx1, ly1;
    s16 lr2[3], lr3[3];
    s32 lv2, lx2, ly2;
    VecFx32Ctor p1, p2, p3;
    s32 ob;
    s32 i;
    s32 j;
    if (Scene_GetCurrent() == 0x2e) goto ret1;
    if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f || Scene_GetCurrent() == 0xe) {
        if (SaveManager_IsGatePassed()) return TRUE;
        ProcBase *rec = (ProcBase *)Actor::findByProfile(0x72, NULL);
        if (rec == NULL) goto ret1;
        if (Unk_0209579c_IsTwo(rec->state)) goto ret1;
        if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f) {
            mode = Net_GetJoiningAid();
        } else {
            mode = NetSession_GetLastSyncSlot();
        }
        if (mode >= 4) goto ret1;
        if (PlayerActor_GetActor(mode)) goto ret1;
        p1.x = 0;
        p1.y = 0;
        p1.z = 0;
        lr1[0] = 0;
        lr1[1] = 0;
        lr1[2] = 0;
        if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f) {
            p1.x = 0x10000;
            p1.y = 2;
            p1.z = 0x5000;
            lr1[0] = 0;
            lr1[1] = 0;
            lr1[2] = 0;
        } else {
            p1.x = 0x10000;
            p1.y = 2;
            p1.z = 0x11800;
            lr1[0] = 0;
            lr1[1] = (s16)0x8000;
            lr1[2] = 0;
        }
        PlayerSession_SetGfxSlot(mode, PlayerSession_FindFreeGfxSlot());
        PlayerActor_Spawn(mode, &p1, lr1, 0x4000000);
        goto ret1;
    }
    if (!(g)->isSlotActive(mode)) goto ret1;
    if (!PlayerActor_GetActor(4)) goto ret1;
    ob = PlayerActor_GetLocalSessionSlot();
    i = 0;
    do {
        if (!(g)->isLocalSlot(i) && (g)->isSlotActive(i) && !PlayerActor_GetActor(i)) {
            if (PlayerActor_GetSlotAction((u32 *)&lv1, -1, i) && lv1 < 0x93 && PlayerActor_GetSlotPosXZ(&la, &lx1, &ly1, -1, i) &&
                la == Scene_GetCurrent() && PlayerActor_GetSlotAngle(&lc, -1, i)) {
                p2.x = lx1;
                p2.y = 2;
                p2.z = ly1;
                Unk_0209579c_Set(lr2, 0, lc, 0);
                PlayerSession_SetGfxSlot(i, PlayerSession_FindFreeGfxSlot());
                PlayerActor_Spawn(i, &p2, lr2, 0x800000);
            } else if (PlayerActor_TestSlotFlag(0x1b, ob)) {
                u8 *bp = PlayerSession_GetLastScene(i);
                s32 *ip = PlayerSession_GetLastAction(i);
                if (*bp == Scene_GetCurrent() && *ip != 0x93) {
                    VecFx32 *pp = PlayerSession_GetLastPos(i);
                    p3.x = pp->x;
                    p3.y = pp->y;
                    p3.z = pp->z;
                    Unk_0209579c_Set(lr3, 0, *PlayerSession_GetLastAngle(i), 0);
                    PlayerSession_SetGfxSlot(i, PlayerSession_FindFreeGfxSlot());
                    PlayerActor_Spawn(i, &p3, lr3, (*ip << 22) & 0x3fc00000);
                }
            }
        }
        i++;
    } while ((u32)i < 4);
    j = 0;
    do {
        if (!(g)->isLocalSlot(j) && !PlayerActor_TestSlotFlag(0x1b, ob)) {
            Actor *e = (Actor *)PlayerActor_GetActor(j);
            if (e) {
                if (!Unk_0209579c_IsTwo(((ProcBase *)e)->state)) {
                    if (PlayerActor_GetSlotAction((u32 *)&lv2, -1, j)) {
                        if (lv2 >= 0x93) {
                            ProcBase_RequestDelete(e);
                        } else if (PlayerActor_GetSlotPosXZ(&lb, &lx2, &ly2, -1, j)) {
                            if (lb != Scene_GetCurrent()) ProcBase_RequestDelete(e);
                        } else {
                            ProcBase_RequestDelete(e);
                        }
                    } else {
                        ProcBase_RequestDelete(e);
                    }
                }
            }
        }
        j++;
    } while ((u32)j < 4);
ret1:
    return TRUE;
}

BOOL RemotePlayerSpawner::onDraw() { return TRUE; }

BOOL RemotePlayerSpawner::onDelete() { return TRUE; }

