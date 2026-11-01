#include "uptr.h"
#include "host_tick.h"
#include "host_labels.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/MsgTextLabel.h"
#include "talk/MsgString.h"
#include "gfx/TexVramTask.h"
#include "gfx/G3dMatData.h"
#include "talk/MsgString25.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "nitro/io_access.h"
#include "gfx/Model.h"
#include "net/CommManager.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020af258.h"
#include "proto/main/unk_020b2c50.h"




class CautionMsgString64 : public MsgString {
public:
    CautionMsgString64();
    virtual ~CautionMsgString64();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x40];
};

class CautionMsgString128 : public MsgString {
public:
    CautionMsgString128();
    virtual ~CautionMsgString128();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x80];
};

class CautionMsgString256 : public MsgString {
public:
    CautionMsgString256();
    virtual ~CautionMsgString256();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x100];
};


extern "C" {
u8 *Msg_SkipLines(u8 *p, u32 n);
void OS_ResetSystem(u32 parameter);
u32 TextLabel_MeasureMsgWidth(MsgString *obj);
MsgTextLabel *MsgTextLabel_CreateBuffer(void *a, s32 b, s32 c);
void MsgTextLabel_Destroy(MsgTextLabel *obj);
void MI_CpuFill8(void *p, u32 v, u32 n);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void G3i_PerspectiveW_(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, void *h);
void G3i_LookAt_(void *a, void *b, void *c, s32 d, void *e);
s32 func_01ffcb0c(s32 a, s32 b);
}

extern Mtx43 data_021f47e0;
extern u8 gFieldSceneKind;


struct Unk_02037ea0_G {
    u8 pad[0x40];
    VecFx32 a, c, b;
};
extern VecFx32 gVec3Zero;
#define data_027e02c8 HOST_LABEL(Unk_02037ea0_G *, data_027e02c8)
#define data_027e00d0 HOST_LABEL(u8 (*)[], data_027e00d0)
#define data_027e0114 HOST_LABEL(u8 (*)[], data_027e0114)
#define data_027e0148 HOST_LABEL(u32 (*)[], data_027e0148)

struct Unk_02037b90_S {
    u8 a, b, c;
};

class CommCautionWindow {
public:
    CommCautionWindow();
    virtual ~CommCautionWindow();

    void restorePlanes();
    void hidePlanes();
    void clearPlaneState();
    void buildLine(u32 a, u32 b);
    void renderCountdown(void *buf, s32 x);
    void renderLine();
    void clearLines();
    void uploadLine(s32 i);
    void setupModelMatrix();
    void updateBlendRegs();
    void draw();
    void update(u8 a);
    void release();
    void init();

    void execReset();
    void enterReset();
    void execEnded();
    void enterEnded();
    void execShutdown();
    void enterShutdown();
    void execCountdown();
    void enterCountdown();
    void execPrepare();
    void enterPrepare();
    void execDelay();
    void enterDelay();
    void execWatch();
    void enterWatch();
    void muteSound();
    void execIdle();
    void enterIdle();
    void checkNetError();

    /* 0x004 */ CachedModel model;
    /* 0x0a0 */ TexVramTask texUpload;
    /* 0x0bc */ s32 state;
    /* 0x0c0 */ s32 timer;
    /* 0x0c4 */ s32 lineIndex;
    /* 0x0c8 */ u8 modelVisible;
    /* 0x0c9 */ u8 errorPending;
    /* 0x0ca */ u8 planesHidden;
    /* 0x0cb */ u8 blendRegsDirty;
    /* 0x0cc */ u16 savedMainBldCnt;
    /* 0x0ce */ u16 savedSubBldCnt;
    /* 0x0d0 */ u32 savedMainPlanes;
    /* 0x0d4 */ u32 savedSubPlanes;
    /* 0x0d8 */ u32 savedMainWindows;
    /* 0x0dc */ u32 savedSubWindows;
    /* 0x0e0 */ s32 countdownX;
    /* 0x0e4 */ s32 seconds;
    /* 0x0e8 */ CautionMsgString256 message;
    /* 0x1fc */ CautionMsgString64 secondsText;
    /* 0x250 */ CautionMsgString128 lineText;
    /* 0x2e4 */ u8 lineTiles[0x800];
};


extern "C" {
void Backup_CancelAndWait(void);
s32 _s32_div_f(s32, s32);
}

extern CommManager *gCommManager;
extern u16 gPad[];

u32 sCommCautionErrorCode;
CommCautionWindow sCommCautionWindow;
u8 sCommCautionNumberGap[4] = {0xa0, 0xa0, 0, 0};
u8 sCommCautionShowErrorCode;
u8 sCommCautionErrorCodeText[0x20];
CautionMsgString256 sCommCautionLagMsg;
CautionMsgString64 sCommCautionSecondsMsg;
CautionMsgString256 sCommCautionEndedMsg;

static inline BOOL Unk_02038058_IsZero(u8 v) {
    return v == 0 ? TRUE : FALSE;
}

static inline BOOL Unk_02038058_IsOne(u8 v) {
    return v == 1 ? TRUE : FALSE;
}

extern "C" void Comm_SetShutdownErrorFlag() {
    CommManager *g = gCommManager;
    u32 v = g->getErrorFlags() | 0x20;
    g->setErrorFlags(v);
}

CautionMsgString256::CautionMsgString256() { clear(); }

CautionMsgString256::~CautionMsgString256() {}

u32 CautionMsgString256::capacity() { return 0x100; }

u8 *CautionMsgString256::data() { return text; }

CautionMsgString64::CautionMsgString64() { clear(); }

CautionMsgString64::~CautionMsgString64() {
}

u32 CautionMsgString64::capacity() {
    return 0x40;
}

u8 *CautionMsgString64::data() {
    return text;
}

CautionMsgString128::CautionMsgString128() {
    clear();
}

CautionMsgString128::~CautionMsgString128() {
}

u32 CautionMsgString128::capacity() {
    return 0x80;
}

u8 *CautionMsgString128::data() {
    return text;
}

extern "C" void CommCaution_SaveErrorCode() {
    sCommCautionErrorCode = Net_GetLastErrorCode();
    u8 f;
    switch (Net_GetMode()) {
    case 3:
    case 4:
        f = 1;
        break;
    default:
        f = 0;
        break;
    }
    sCommCautionShowErrorCode = f;
}

extern "C" void CommCaution_CopyString(void *a, void *b) {
    strcpy((char *)a, (const char *)b);
}

u8 *CommCaution_FormatErrorCode() {
    u8 buf[0x14];
    Str_SPrintf((char *)buf, " <%d>", sCommCautionErrorCode);
    CommCaution_CopyString(sCommCautionErrorCodeText, buf);
    return sCommCautionErrorCodeText;
}

CommCautionWindow::CommCautionWindow()
    : state(0), timer(0), lineIndex(0), modelVisible(0), errorPending(0), planesHidden(0), blendRegsDirty(0), savedMainBldCnt(0), savedSubBldCnt(0), savedMainPlanes(0),
      savedSubPlanes(0), savedMainWindows(0), savedSubWindows(0), countdownX(0), seconds(0) {
    MI_CpuFill8(lineTiles, 0x11, 0x800);
}

CommCautionWindow::~CommCautionWindow() {
}

extern "C" u8 CommCaution_ArePlanesHidden() {
    return sCommCautionWindow.planesHidden;
}

extern "C" BOOL CommCaution_IsShutDown() {
    if (sCommCautionWindow.state >= 5) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void CommCaution_Init() {
    sCommCautionWindow.init();
}

extern "C" void CommCaution_Release() {
    sCommCautionWindow.release();
}

extern "C" void CommCaution_Update(u8 a) {
    sCommCautionWindow.update(a);
}

extern "C" void CommCaution_Draw() {
    sCommCautionWindow.draw();
}

extern "C" void CommCaution_UpdateBlendRegs() {
    sCommCautionWindow.updateBlendRegs();
}

extern "C" void CommCaution_LoadMessages() {
    u8 c[3];
    c[0] = 0xe3;
    c[1] = 0xe4;
    c[2] = 0xe5;
    String_Load2d(&sCommCautionLagMsg, &c[0], 0);
    String_Load2d(&sCommCautionSecondsMsg, &c[1], 0);
    String_Load2d(&sCommCautionEndedMsg, &c[2], 0);
}

void CommCautionWindow::init() {
    BOOL a = TRUE;
    u8 v = gFieldSceneKind;
    if (!Unk_02038058_IsZero(v)) {
        if (!Unk_02038058_IsOne(v)) {
            a = FALSE;
        }
    }
    BOOL b;
    if (gActorDefaultParent->profile == 5) {
        b = TRUE;
    } else {
        b = FALSE;
    }
    clearPlaneState();
    if (a || b) {
        ((CachedModel *)(&model))->loadCached(0x43617557, (void *)"caution/caution_window.nsbmd");
        setupModelMatrix();
        lineIndex = 0;
        modelVisible = 0;
        enterWatch();
    } else {
        enterIdle();
    }
}

void CommCautionWindow::release() {
    if (state != 0) {
        ((CachedModel *)(&model))->release();
        state = 0;
    }
}

void CommCautionWindow::update(u8 a) {
    errorPending = a;
    checkNetError();
    static void (CommCautionWindow::*tbl[8])() = {
        &CommCautionWindow::execIdle, &CommCautionWindow::execWatch, &CommCautionWindow::execDelay,
        &CommCautionWindow::execPrepare, &CommCautionWindow::execCountdown, &CommCautionWindow::execShutdown,
        &CommCautionWindow::execEnded, &CommCautionWindow::execReset,
    };
    (this->*tbl[state])();
}

void CommCautionWindow::draw() {
    if (modelVisible) {
        G3i_PerspectiveW_(0x424, 0xf74, 0x1548, 0xf6, 0x3e800, 0x1000, 0, data_027e00d0);
        data_027e0148[0x7c / 4] &= ~0x50;
        VecFx32 a, b, c, d;
        a = gVec3Zero;
        b.x = 0;
        b.y = 0;
        b.z = -0x1000;
        c.x = 0;
        c.y = 0x1000;
        c.z = 0;
        data_027e02c8.a = a;
        data_027e02c8.c = c;
        data_027e02c8.b = b;
        G3i_LookAt_(&a, &c, &b, 0, data_027e0114);
        data_027e0148[0x7c / 4] &= ~0xe8;
        s32 r = func_01ffcb0c(0xb7, 0xf6d);
        d.x = r;
        d.y = r;
        d.z = 0x1000;
        ((Model *)(&model))->drawScaled((s32 *)(&d));
    }
}

void CommCautionWindow::updateBlendRegs() {
    if (blendRegsDirty) {
        if (planesHidden) {
            savedMainBldCnt = IO_R((volatile u16 *)0x4000050);
            savedSubBldCnt = IO_R((volatile u16 *)0x4001050);
            IO_W((volatile u16 *)0x4000050, 0);
            IO_W((volatile u16 *)0x4001050, 0);
        } else {
            IO_W((volatile u16 *)0x4000050, savedMainBldCnt);
            IO_W((volatile u16 *)0x4001050, savedSubBldCnt);
        }
        blendRegsDirty = 0;
    }
}

void CommCautionWindow::setupModelMatrix() {
    Mtx43_SetTranslate(&data_021f47e0, 0, 0, -0x1000);
    model.mtx = data_021f47e0;
}

void CommCautionWindow::uploadLine(s32 i) {
    u8 *b = (u8 *)model.resMdl;
    b += *(s32 *)(b + 8);
    u8 *c = b + *(u16 *)(b + 0xa);
    u32 v = reinterpret_cast<G3dMatData *>(b + *(s32 *)(c + 8))->getTexAddr();
    texUpload.requestTex(lineTiles, v + (i << 11), 0x800, 2);
}

void CommCautionWindow::clearLines() {
    MI_CpuFill8(lineTiles, 0x11, 0x800);
    for (s32 i = 0; i < 4; i++) {
        uploadLine(i);
    }
}

void CommCautionWindow::renderLine() {
    void *buf = Mem_AllocTail(0x800);
    if (buf != NULL) {
        MsgTextLabel *o = MsgTextLabel_CreateBuffer(buf, 0x20, 2);
        if (o != NULL) {
            o->vramLoader = 5;
            o->textStart = lineText.data();
            o->group = 2;
            o->copyMode = 0;
            o->font = (GameFontDesc *)&gFontA;
            o->rowStride1K = 0;
            o->alignCenter();
            o->bgColor = 1;
            o->fgColor = 0;
            o->requestRedraw();
            u32 w = o->xOffset;
            MsgTextLabel_Destroy(o);
            if (seconds >= 0 && countdownX != 0) {
                renderCountdown(buf, w);
            }
            Gfx2d_TilesToLinear4bpp((u32 *)buf, (u32 *)lineTiles, 0x20, 2);
        }
        Mem_Free(buf);
    }
}

void CommCautionWindow::renderCountdown(void *buf, s32 x) {
    MsgString25 t;
    String_FormatNumber(&t, seconds, 2, 0, 0, 0);
    u32 w = TextLabel_MeasureMsgWidth(&t);
    u32 off;
    if (w < 0x10) {
        off = (0x10 - w) >> 1;
    } else {
        off = 0;
    }
    s32 px = x + countdownX + off;
    MsgTextLabel *o = MsgTextLabel_CreateBuffer(buf, 0x20, 2);
    if (o != NULL) {
        o->vramLoader = 5;
        o->textStart = ((MsgString *)&t)->data();
        o->group = 2;
        o->copyMode = 0;
        o->font = (GameFontDesc *)&gFontA;
        o->rowStride1K = 0;
        o->xOffset = px;
        o->bgColor = 1;
        o->fgColor = 0;
        o->blendOverBg = 1;
        o->requestRedraw();
        MsgTextLabel_Destroy(o);
    }
}

void CommCautionWindow::buildLine(u32 a, u32 b) {
    lineText.clear();
    countdownX = 0;
    u8 *r = Msg_SkipLines(message.data(), a);
    if (r != NULL) {
        lineText.setLine(r);
        if (seconds >= 0 && a == 3) {
            countdownX = TextLabel_MeasureMsgWidth(&lineText);
            Unk_02037b90_S s = *(Unk_02037b90_S *)sCommCautionNumberGap;
            lineText.append((u8 *)&s);
            lineText.appendString(&secondsText);
        }
        if (b != 0 && a == 3 && sCommCautionShowErrorCode != 0) {
            lineText.append(CommCaution_FormatErrorCode());
        }
    }
}

void CommCautionWindow::clearPlaneState() {
    planesHidden = 0;
    savedMainPlanes = 0;
    savedSubPlanes = 0;
    savedMainWindows = 0;
    savedSubWindows = 0;
}

void CommCautionWindow::hidePlanes() {
    if (!planesHidden) {
        planesHidden = 1;
        savedMainPlanes = Gfx2d_GetMainPlanes();
        savedSubPlanes = Gfx2d_GetSubPlanes();
        savedMainWindows = Gfx2d_GetMainWindows();
        savedSubWindows = Gfx2d_GetSubWindows();
        Gfx2d_SetMainPlanes(1);
        Gfx2d_SetSubPlanes(0);
        Gfx2d_SetMainWindows(0);
        Gfx2d_SetSubWindows(0);
        blendRegsDirty = 1;
    }
}

void CommCautionWindow::restorePlanes() {
    if (planesHidden) {
        planesHidden = 0;
        Gfx2d_SetMainPlanes(savedMainPlanes);
        Gfx2d_SetSubPlanes(savedSubPlanes);
        Gfx2d_SetMainWindows(savedMainWindows);
        Gfx2d_SetSubWindows(savedSubWindows);
        blendRegsDirty = 1;
    }
}

void CommCautionWindow::muteSound() {
    LidSleep_KeepSoundOff();
    Snd_VolumeOff();
}

void CommCautionWindow::checkNetError() {
    s32 s = Net_GetMode();
    if (s != 0 && s != 6) {
        s32 r4 = gCommManager->getErrorMode();
        s32 v = Net_GetError();
        if ((r4 == 0 && v != 0 && v != 0x800c && v != 0x400b) ||
            (r4 == 1 && v != 0 && v != 0x80ff && v != 0x800c && v != 0x4006 && v != 0x400a && v != 0x400b)) {
            CommManager *o = gCommManager;
            u32 f = o->getErrorFlags() | 0x10;
            o->setErrorFlags(f);
        }
    }
}

void CommCautionWindow::enterIdle() {
    state = 0;
}

void CommCautionWindow::execIdle() {}

void CommCautionWindow::enterWatch() {
    state = 1;
    modelVisible = 0;
    restorePlanes();
}

void CommCautionWindow::execWatch() {
    if (errorPending != 0) {
        if ((gCommManager->getLatchedErrorFlags() & 0x7c) != 0) {
            hidePlanes();
            enterShutdown();
        } else {
            enterDelay();
        }
    }
}

void CommCautionWindow::enterDelay() {
    state = 2;
    timer = 0x14;
    modelVisible = 0;
}

void CommCautionWindow::execDelay() {
    if (errorPending == 0) {
        enterWatch();
    } else {
        timer = timer - (TICK_STEP_ENDS() ? 1 : 0);
        if (timer <= 0) {
            enterPrepare();
        }
    }
}

void CommCautionWindow::enterPrepare() {
    state = 3;
    modelVisible = 0;
    clearLines();
    hidePlanes();
}

void CommCautionWindow::execPrepare() {
    message.copy(&sCommCautionLagMsg);
    secondsText.copy(&sCommCautionSecondsMsg);
    enterCountdown();
}

void CommCautionWindow::enterCountdown() {
    state = 4;
    timer = 0x12c;
    lineIndex = 0;
    modelVisible = 1;
    countdownX = 0;
    seconds = 0xf;
}

void CommCautionWindow::execCountdown() {
    s32 q = _s32_div_f(timer + 0x13, 0x14);
    BOOL changed;
    if (seconds != q) {
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    seconds = q;
    if (lineIndex < 4) {
        buildLine(lineIndex, 0);
        renderLine();
        uploadLine(lineIndex);
        lineIndex = lineIndex + 1;
    } else if (changed) {
        buildLine(3, 0);
        renderLine();
        uploadLine(3);
    }
    if (errorPending == 0) {
        enterWatch();
    } else {
        timer = timer - (TICK_STEP_ENDS() ? 1 : 0);
        if (timer <= -0x14) {
            enterShutdown();
        }
    }
}

void CommCautionWindow::enterShutdown() {
    state = 5;
    modelVisible = 1;
    clearLines();
    muteSound();
    CommCaution_SaveErrorCode();
    Backup_CancelAndWait();
    Comm_Shutdown();
}

void CommCautionWindow::execShutdown() {
    message.copy(&sCommCautionEndedMsg);
    enterEnded();
}

void CommCautionWindow::enterEnded() {
    state = 6;
    lineIndex = 0;
    modelVisible = 1;
    countdownX = 0;
    seconds = -1;
    timer = 0x14;
}

void CommCautionWindow::execEnded() {
    if (lineIndex < 4) {
        buildLine(lineIndex, 1);
        renderLine();
        uploadLine(lineIndex);
        lineIndex = lineIndex + 1;
    }
    timer = timer - (TICK_STEP_ENDS() ? 1 : 0);
    if (timer <= 0) {
        BOOL b, a;
        if (gTouchHeld != 0 && gTouchChanged != 0) {
            a = TRUE;
        } else {
            a = FALSE;
        }
        b = (gPad[1] & 1) ? TRUE : FALSE;
        if (a != 0 || b != 0) {
            enterReset();
        }
    }
}

void CommCautionWindow::enterReset() {
    state = 7;
    timer = 1;
    modelVisible = 1;
}

void CommCautionWindow::execReset() {
    timer = timer - (TICK_STEP_ENDS() ? 1 : 0);
    if (timer <= 0) {
        OS_ResetSystem(0);
    }
}

