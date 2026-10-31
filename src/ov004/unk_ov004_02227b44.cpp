#include "types.h"
#include "host_labels.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/G3dResAccess.h"
#include "gfx/Model.h"
#include "save/MuseumData.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/ov004/unk_ov004_02227b44.h"


struct MuseumDisplayKind {
    u16 (*getItemId)(u32);
    u32 numItems;
    const char *arcPath;
    const char *texPath;
};

class MuseumDisplay : public RoomObjActor {
public:
    MuseumDisplay();
    virtual ~MuseumDisplay();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    BOOL isShownNode(s32 c);
    void selectNodes();
    void setNodeVisibility(s32 c, void *o);

    s8 *shownNodes;
};

extern "C" {
#define data_021ed0a0 HOST_LABEL(u8 (*)[], data_021ed0a0)
void MuseumDisplay_NodeCallback(NNSG3dRS *o);
u16 Item_MakeInsect(u32 x);
}

extern "C" { extern DebugColor data_ov004_02250e08; }
extern "C" { extern DebugColor data_ov004_02250e18; }
extern "C" { extern char sMuseumPictureTexPath[0x20]; }
extern "C" { extern char sMuseumDisplayNodeName[0x28]; }
extern "C" { extern DebugColor data_ov004_02250e14; }
extern "C" { extern char sMuseumInsectTexPath[0x20]; }
extern "C" { extern char sMuseumInsectArcPath[0x1c]; }
extern "C" { extern DebugColor data_ov004_02250e1c; }
extern "C" { extern DebugColor data_ov004_02250e10; }
extern "C" { extern const MuseumDisplayKind sMuseumDisplayKinds[2]; }
extern "C" { extern DebugColor data_ov004_02250e0c; }
extern "C" { extern char sMuseumPictureArcPath[0x1c]; }
extern "C" { extern ActorProfile sMuseumDisplayProfile; }

extern "C" DebugColor data_ov004_02250e08(31, 20, 20, 31);

extern "C" DebugColor data_ov004_02250e18(20, 20, 31, 31);

extern "C" char sMuseumPictureTexPath[0x20] = "/roomObj/obj_ms_picture.nsbtx";

extern "C" char sMuseumDisplayNodeName[0x28] = {0};

extern "C" DebugColor data_ov004_02250e14(31, 31, 20, 31);

extern "C" char sMuseumInsectTexPath[0x20] = "/roomObj/obj_ms_insectA.nsbtx";

extern "C" char sMuseumInsectArcPath[0x1c] = "/roomObj/obj_ms_insectA.arc";

extern "C" DebugColor data_ov004_02250e1c(20, 31, 20, 31);

extern "C" DebugColor data_ov004_02250e10(20, 31, 31, 31);

extern "C" const MuseumDisplayKind sMuseumDisplayKinds[2] = {
    {MuseumDisplay_GetPaintingItem, 0x14, sMuseumPictureArcPath, sMuseumPictureTexPath},
    {Item_MakeInsect, 0x38, sMuseumInsectArcPath, sMuseumInsectTexPath},
};

extern "C" DebugColor data_ov004_02250e0c(20, 24, 24, 31);

extern "C" char sMuseumPictureArcPath[0x1c] = "/roomObj/obj_ms_picture.arc";

extern "C" ActorProfile sMuseumDisplayProfile = {(void *(*)())MuseumDisplay_Create, 0x14, 0x18, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" MuseumDisplay *MuseumDisplay_Create() {
    return new MuseumDisplay();
}

extern "C" u16 MuseumDisplay_GetPaintingItem(u32 i) {
    return i < 0x14 ? i * 4 + 0x3894 : 0x3894;
}

extern "C" const MuseumDisplayKind *MuseumDisplay_GetKindInfo(u32 i) {
    if (i < 2) {
        return &sMuseumDisplayKinds[i];
    }
    return &sMuseumDisplayKinds[0];
}

extern "C" void MuseumDisplay_NodeCallback(NNSG3dRS *o) {
    MuseumDisplay *b = (MuseumDisplay *)o->pRenderObj->ptrUser;
    if (b != 0) {
        b->setNodeVisibility(o->c[1], o);
    }
}

extern "C" void MuseumDisplay_InitRenderObj(void *p) {
    NNSG3dRS *o = (NNSG3dRS *)p;
    o->cbVecFunc[2] = (void *)MuseumDisplay_NodeCallback;
    o->cbVecTiming[2] = 2;
}

MuseumDisplay::MuseumDisplay() {}

MuseumDisplay::~MuseumDisplay() {}

BOOL MuseumDisplay::onCreate() {
    const MuseumDisplayKind *r = MuseumDisplay_GetKindInfo(param);
    loadResources((char *)r->arcPath, (char *)r->texPath);
    model.setInitCallback((void (*)(NNSG3dRS *))MuseumDisplay_InitRenderObj, this);
    selectNodes();
    return TRUE;
}

BOOL MuseumDisplay::onExecute() {
    return TRUE;
}

BOOL MuseumDisplay::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL MuseumDisplay::onDelete() {
    releaseResources();
    return TRUE;
}

void MuseumDisplay::setNodeVisibility(s32 c, void *o) {
    *(s32 *)((NNSG3dRS *)o)->pVisAnmResult = isShownNode(c);
}

void MuseumDisplay::selectNodes() {
    const MuseumDisplayKind *r = MuseumDisplay_GetKindInfo(param);
    shownNodes = (s8 *)Heap_Alloc((Heap *)gBgHeap, r->numItems);
    u32 z = 0;
    u32 i;
    for (i = 0; i < r->numItems; i++) {
        u16 v = r->getItemId(i);
        u32 f = z;
        if (((MuseumData *)(data_021ed0a0))->isDonated(&v) != 0) {
            f = 1;
        }
        Str_SPrintf(sMuseumDisplayNodeName, "p%d_%d", i, f);
        shownNodes[i] = ((G3dResAccess *)model.resMdl)->findNodeIdx(sMuseumDisplayNodeName);
    }
}

BOOL MuseumDisplay::isShownNode(s32 c) {
    const MuseumDisplayKind *r = MuseumDisplay_GetKindInfo(param);
    u32 i = 0;
    u32 n = r->numItems;
    for (; i < n; i++) {
        if (c == shownNodes[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02227b44) {
    HOST_OVERLAY_VAR(data_ov004_02250e08),
    HOST_OVERLAY_VAR(data_ov004_02250e18),
    HOST_OVERLAY_VAR(sMuseumPictureTexPath),
    HOST_OVERLAY_VAR(sMuseumDisplayNodeName),
    HOST_OVERLAY_VAR(data_ov004_02250e14),
    HOST_OVERLAY_VAR(sMuseumInsectTexPath),
    HOST_OVERLAY_VAR(sMuseumInsectArcPath),
    HOST_OVERLAY_VAR(data_ov004_02250e1c),
    HOST_OVERLAY_VAR(data_ov004_02250e10),
    HOST_OVERLAY_VAR(data_ov004_02250e0c),
    HOST_OVERLAY_VAR(sMuseumPictureArcPath),
    HOST_OVERLAY_VAR(sMuseumDisplayProfile),
    HOST_OVERLAY_VARS_END
};
