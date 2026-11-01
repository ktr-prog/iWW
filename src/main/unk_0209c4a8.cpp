#include "types.h"
#include "gfx/VecFx32.h"
#include "net/CommManager.h"
#include "room/Unk_0209c41c_Actor.h"
#include "actor/Actor.h"
#include "game/FxVec3.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_0209c4a8.h"
#include "proto/main/unk_0204cc1c.h"


struct SceneExitResolveOut {
    u8 scene, fadeIn, fadeOut, unk_03;
};

class RoomEntryRequest {
public:
    RoomEntryRequest();
    ~RoomEntryRequest();

    /* 0x00 */ u8 scene;
    /* 0x04 */ VecFx32 pos;
    /* 0x10 */ VecFx32 retreatPos;
    /* 0x1c */ u16 angle;
    /* 0x1e */ u8 exitId;
    /* 0x1f */ u8 result;
    /* 0x20 */ u8 doorKind;
};

struct SceneOccupantBits {
    u8 occupantBits;
};

class SceneOccupants : public SceneOccupantBits {
public:
    SceneOccupants();
    ~SceneOccupants();
};

extern "C" CommManager *gCommManager;


extern "C" {
extern u8 gFieldSceneKind;
extern const u8 sExclusiveRoomScenes[4];


s32 Scene_GetCurrent();
u8 Scene_GetPrevious();

void SceneOccupantTable_Clear(SceneOccupantBits *t);
void SceneOccupants_Clear(SceneOccupantBits *t);
}

class SceneOccupantTable {
public:
    SceneOccupantTable() { SceneOccupantTable_Clear(e); }
    ~SceneOccupantTable();

    SceneOccupants e[0x33];
};


extern const u8 sExclusiveRoomScenes[4];
const u8 sExclusiveRoomScenes[4] = {0x1f, 0x1d, 0x22, 0x20};


RoomEntryRequest sRoomEntryRequest;
SceneOccupantTable sSceneOccupantTable;


SceneOccupants::SceneOccupants() {
    SceneOccupants_Clear(this);
}

SceneOccupantTable::~SceneOccupantTable() {}

extern "C" void SceneOccupants_Clear(SceneOccupantBits *t) {
    t->occupantBits = 0;
}

extern "C" void SceneOccupants_Add(SceneOccupantBits *t, u32 i) {
    t->occupantBits |= 1 << (i & 3);
}

extern "C" void SceneOccupants_Remove(SceneOccupantBits *t, u32 i) {
    t->occupantBits &= ~(1 << (i & 3));
}

extern "C" u32 SceneOccupants_Has(SceneOccupantBits *t, u32 i) {
    return ((t->occupantBits >> (i & 3)) & 1) != 0 ? TRUE : FALSE;
}

extern "C" s32 SceneOccupants_Count(SceneOccupantBits *t) {
    s32 n = 0;
    u32 i = n;
    for (; i < 4; i++) {
        if (SceneOccupants_Has(t, i)) {
            n++;
        }
    }
    return n;
}

SceneOccupants::~SceneOccupants() {}

extern "C" s32 SceneOccupants_CountWith(SceneOccupantBits *t, u32 b) {
    SceneOccupantBits c;
    c.occupantBits = t->occupantBits;
    SceneOccupants_Add(&c, b);
    return SceneOccupants_Count(&c);
}

extern "C" void SceneOccupantTable_Clear(SceneOccupantBits *t) {
    u32 i;
    for (i = 0; i < 0x33; i++) {
        SceneOccupants_Clear(t + i);
    }
}

extern "C" void SceneOccupantTable_Add(SceneOccupantBits *t, u32 i, u32 b) {
    if (i < 0x33) {
        SceneOccupants_Add(t + i, b);
    }
}

extern "C" void SceneOccupantTable_Remove(SceneOccupantBits *t, u32 i, u32 b) {
    if (i < 0x33) {
        SceneOccupants_Remove(t + i, b);
    }
}

extern "C" s32 SceneOccupantTable_CountWith(SceneOccupantBits *t, u32 i, u32 b) {
    if (i < 0x33) {
        return SceneOccupants_CountWith(t + i, b);
    }
    return 0;
}

RoomEntryRequest::RoomEntryRequest() {
    RoomEntryRequest_Init(this);
}

RoomEntryRequest::~RoomEntryRequest() {}

extern "C" void RoomEntryRequest_Init(RoomEntryRequest *t) {
    RoomEntryRequest_SetResult(t, 2);
    RoomEntryRequest_SetExitId(t, -1);
    RoomEntryRequest_SetDoorKind(t, 0);
    RoomEntryRequest_SetScene(t, 0);
    RoomEntryRequest_SetPos(t, &gVec3Zero);
    RoomEntryRequest_SetAngle(t, 0);
    RoomEntryRequest_SetRetreatPos(t, &gVec3Zero);
}

extern "C" u32 RoomEntryRequest_GetResult(RoomEntryRequest *t) {
    return t->result;
}

extern "C" u32 RoomEntryRequest_GetDoorKind(RoomEntryRequest *t) {
    return t->doorKind;
}

extern "C" void *RoomEntryRequest_GetPos(RoomEntryRequest *t) {
    return &t->pos;
}

extern "C" void *RoomEntryRequest_GetRetreatPos(RoomEntryRequest *t) {
    return &t->retreatPos;
}

extern "C" void RoomEntryRequest_SetResult(RoomEntryRequest *t, u32 v) {
    t->result = v;
}

extern "C" void RoomEntryRequest_SetExitId(RoomEntryRequest *t, u32 v) {
    t->exitId = v;
}

extern "C" void RoomEntryRequest_SetDoorKind(RoomEntryRequest *t, u32 v) {
    t->doorKind = v;
}

extern "C" void RoomEntryRequest_SetScene(RoomEntryRequest *t, u32 v) {
    t->scene = v;
}

extern "C" void RoomEntryRequest_SetPos(RoomEntryRequest *t, VecFx32 *v) {
    t->pos.x = v->x;
    t->pos.y = v->y;
    t->pos.z = v->z;
}

extern "C" void RoomEntryRequest_SetAngle(RoomEntryRequest *t, u32 v) {
    t->angle = v;
}

extern "C" void RoomEntryRequest_SetRetreatPos(RoomEntryRequest *t, VecFx32 *v) {
    t->retreatPos.x = v->x;
    t->retreatPos.y = v->y;
    t->retreatPos.z = v->z;
}

extern "C" void RoomEntry_Reset() {
    RoomEntryRequest_Init(&sRoomEntryRequest);
    SceneOccupantTable_Clear(sSceneOccupantTable.e);
}

extern "C" u32 RoomEntry_IsExclusiveScene(u32 v) {
    s32 i;
    for (i = 0; (u32)i < 2; i++) {
        if (v == sExclusiveRoomScenes[i * 2]) {
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" s32 RoomEntry_IsExclusiveExit(u32 exitId) {
    SceneExitResolveOut t;
    s16 b;
    u32 a;
    VecFx32 c;
    if (SceneExit_Resolve(Scene_GetWarpRequest(), exitId, &t.scene, &c, &a, &b, &t.fadeOut, &t.fadeIn, NULL, NULL)) {
        return RoomEntry_IsExclusiveScene(t.scene);
    }
    return 0;
}

extern "C" BOOL RoomEntry_Request(u32 id) {
    Actor *p = (Actor *)PlayerActor_GetActor(4);
    SceneWarp *o = Scene_GetWarpRequest();
    SceneExitResult s;
    u32 a20, a24;
    VecFx32 v28, v34, v40, v4c;
    s32 r = SceneExit_Resolve(o, id, &s.scene, &v28, &a20, &s.e, &s.fadeOut, &s.fadeIn, NULL, NULL);
    RoomEntryRequest_SetResult(&sRoomEntryRequest, 0);
    if (r != 0 && p != 0) {
        VecFx32 *pv = (VecFx32 *)&p->position;
        v40.x = pv->x;
        v40.y = pv->y;
        v40.z = pv->z;
        s32 h = p->rotY;
        SceneExit_GetDoor(Scene_GetWarpRequest(), id, &a24, &s.f);
        SceneExit_SnapPos(Scene_GetWarpRequest(), id, &v34, &v40);
        RoomEntryRequest_SetExitId(&sRoomEntryRequest, id);
        RoomEntryRequest_SetDoorKind(&sRoomEntryRequest, a24);
        RoomEntryRequest_SetScene(&sRoomEntryRequest, s.scene);
        if (a24 != 0) {
            RoomEntryRequest_SetPos(&sRoomEntryRequest, &v34);
            RoomEntryRequest_SetAngle(&sRoomEntryRequest, s.f);
        } else {
            RoomEntryRequest_SetPos(&sRoomEntryRequest, &v40);
            RoomEntryRequest_SetAngle(&sRoomEntryRequest, h);
        }
        v4c.x = v40.x;
        v4c.y = v40.y;
        v4c.z = v40.z;
        v4c.z = v4c.z + 0x2000;
        FieldPos_SnapToUnitCenter(&v4c, &v4c);
        v4c.x = v40.x;
        RoomEntryRequest_SetRetreatPos(&sRoomEntryRequest, &v4c);
        if (RoomEntry_IsExclusiveScene(s.scene)) {
            CommManager *g = gCommManager;
            if (!g->isOnline() || g->isMyAid(0) != 0) {
                if ((u32)SceneOccupantTable_CountWith(sSceneOccupantTable.e, s.scene, 0) <= 1) {
                    SceneOccupantTable_Add(sSceneOccupantTable.e, s.scene, 0);
                    RoomEntryRequest_SetResult(&sRoomEntryRequest, 2);
                } else {
                    RoomEntryRequest_SetResult(&sRoomEntryRequest, 1);
                }
            } else {
                s.d = s.scene;
                g = gCommManager;
                g->beginRecord();
                g->writeRecord(&s.d, 1);
                g->endRecord(0x33, 0);
            }
        } else {
            RoomEntryRequest_SetResult(&sRoomEntryRequest, 2);
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" void *RoomEntry_GetRequest() {
    return &sRoomEntryRequest;
}

extern "C" void RoomEntry_Leave(u32 a, u32 b) {
    CommManager *g = gCommManager;
    if (!g->isOnline() || g->isMyAid(0) != 0 || g->isMyAid(4) != 0) {
        SceneOccupantTable_Remove(sSceneOccupantTable.e, a, b);
    } else {
        u8 v = a;
        g = gCommManager;
        g->beginRecord();
        g->writeRecord(&v, 1);
        g->endRecord(0x35, 0);
    }
}

extern "C" void RoomEntry_OnSceneLoad() {
    RoomEntryRequest_Init(&sRoomEntryRequest);
    BOOL is1;
    if (gFieldSceneKind == 1) is1 = TRUE;
    else is1 = FALSE;
    if (is1) {
        u32 r6 = Scene_GetCurrent();
        u32 r5 = Scene_GetPrevious();
        u32 i = 0;
        u32 z = i;
        for (; i < 2; i++) {
            const u8 *e = &sExclusiveRoomScenes[i * 2];
            if (r6 == e[1] && r5 == e[0]) RoomEntry_Leave(r5, z);
        }
    }
}

extern "C" void RoomEntry_RecvEnterRequest(u8 *p, u32 x) {
    u32 b = *p;
    u8 flag;
    if ((u32)SceneOccupantTable_CountWith(sSceneOccupantTable.e, b, x) <= 1) {
        SceneOccupantTable_Add(sSceneOccupantTable.e, b, x);
        flag = 1;
    } else {
        flag = 0;
    }
    CommManager *g = gCommManager;
    g->beginRecord();
    g->writeRecord(&flag, 1);
    g->endRecord(0x34, x);
}

extern "C" void RoomEntry_RecvEnterReply(u8 *p) {
    if (*p) {
        RoomEntryRequest_SetResult(&sRoomEntryRequest, 2);
    } else {
        RoomEntryRequest_SetResult(&sRoomEntryRequest, 1);
    }
}


extern "C" void RoomEntry_RecvLeave(u8 *p, u32 x) {
    SceneOccupantTable_Remove(sSceneOccupantTable.e, *p, x);
}

