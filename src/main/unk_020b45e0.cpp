#include "types.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "sys/SceneBase.h"
#include "proto/main/unk_020029e8.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_0208e6d8.h"
#include "proto/main/unk_0209c08c.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b45e0.h"

extern "C" {
void Scene_ShutdownGraphics(void);
void Scene_SetupGraphics(void);
}

extern CommManager *gCommManager;

class FieldEntryScene : public SceneBase {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~FieldEntryScene() {}

    void idle();
    void requestField();
    void waitAreaMove();

    /* 0x50 */ s32 step;
};

extern "C" FieldEntryScene *FieldEntryScene_Create(void) { return new FieldEntryScene; }

ProcProfile sFieldEntrySceneProfile = {(void *(*)())FieldEntryScene_Create, 0x5, 0x4};

void FieldEntryScene::waitAreaMove() {
    if (NetArea_GetMoveState() == 0xb) {
        NetArea_SetMoveState(0xc);
        requestField();
    }
}

void FieldEntryScene::requestField() {
    Scene_Request(6, 3, Scene_GetSavedFadeIn(), 1);
    step = 2;
}

void FieldEntryScene::idle() {}

BOOL FieldEntryScene::onCreate() {
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        step = 0;
    } else {
        step = 1;
    }
    Snd_CreateScene();
    Scene_SetupGraphics();
    AbAllObjGfx_Upload();
    TransitionCommIcon_Resume();
    return TRUE;
}

BOOL FieldEntryScene::onDelete() {
    gGfxFrameHooks = NULL;
    Scene_ShutdownGraphics();
    return TRUE;
}

BOOL FieldEntryScene::onExecute() {
    typedef void (FieldEntryScene::*Fn)();
    static Fn table[3] = {&FieldEntryScene::waitAreaMove, &FieldEntryScene::requestField, &FieldEntryScene::idle};
    (this->*table[step])();
    return TRUE;
}

BOOL FieldEntryScene::onDraw() { return TRUE; }
