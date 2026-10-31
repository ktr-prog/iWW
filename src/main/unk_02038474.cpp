#include "uptr.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "text/Unk_02050288.h"
#include "net/CommManager.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "talk/ChatBalloonText.h"
#include "talk/MsgString9B.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"

#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020116e0.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_0209c37c.h"

extern "C" const s32 data_020c8cb4;
extern "C" const s32 data_020c8cb8;
extern "C" const s32 data_020c8cbc;
extern "C" const s32 data_020c8cc0;



class ChatQuickMsgInput {
public:
    ChatQuickMsgInput();
    virtual ~ChatQuickMsgInput();
    void update();
    void shutdown();
    void init();
};

class ChatBalloonName : public MsgStringBase {
public:
    ChatBalloonName();
    virtual ~ChatBalloonName();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x04 */ u8 text[9];
};

class ChatBalloon : public UiWidget {
public:
    ChatBalloon();
    virtual ~ChatBalloon();
    virtual void draw();
    virtual void update();

    void destroyTextLabel();
    void createTextLabel();
    void destroyNameLabel();
    void createNameLabel();
    void fitToText();
    void initSprites();
    void execClose();
    void enterClose();
    void execShow();
    void enterShow();
    void execOpen();
    void enterOpen();
    void execHidden();
    void enterHidden();
    void reset();
    void refreshLabelsUnk();
    BOOL requestClose();
    BOOL requestOpen();
    void setup(s32 a, s32 b, s32 c);
    void setMessage(StrBuf *a, MsgString *b, s32 c);
    void updateSlideOffset();

    /* 0x0c */ s32 localIndex;
    /* 0x10 */ s32 palette;
    /* 0x14 */ s32 nameSeqIndex;
    /* 0x18 */ s32 textSeqIndex;
    /* 0x1c */ SpriteAnim nameAnim;
    /* 0x30 */ SpriteAnim textAnim;
    /* 0x44 */ s32 stackTargetY;
    /* 0x48 */ s32 stackY;
    /* 0x4c */ s32 popOffsetY;
    /* 0x50 */ s32 slideY;
    /* 0x54 */ ChatBalloonText text;
    /* 0x88 */ ChatBalloonName name;
    /* 0x98 */ TextLabel *nameLabel;
    /* 0x9c */ TextLabel *textLabel;
    /* 0xa0 */ s32 state;
    /* 0xa4 */ s32 stateTimer;
    /* 0xa8 */ s32 cooldown;
    /* 0xac */ s32 request;
    /* 0xb0 */ u8 visible;
};

class ChatBalloonList {
public:
    ChatBalloonList();
    virtual ~ChatBalloonList();

    void clear();
    void refreshLabelsUnk();
    void draw();
    void update();
    void shutdown();
    void init();
    BOOL isShown(ChatBalloon *p);
    BOOL isQueued(ChatBalloon *p);
    void removeFinished();
    void layoutShown();
    void showQueued();
    BOOL tryShow(ChatBalloon *p);
    BOOL enqueue(ChatBalloon *p);
    void dismiss(s32 idx);
    s32 getColorIndex(s32 idx);
    s32 toLocalIndex(s32 idx);
    void post(s32 idx, StrBuf *a, MsgString *b);

    /* 0x004 */ ChatBalloon balloons[4];
    /* 0x2d4 */ ChatBalloon *queue[4];
    /* 0x2e4 */ ChatBalloon *shown[4];
};

typedef void (ChatBalloon::*Unk_020d9194_Fn)();

class EncodedStringBaseRef : public EncodedStringBase {
public:
    EncodedStringBaseRef(u8 *data, u32 size);
    virtual ~EncodedStringBaseRef();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x04 */ u8 *buffer;
    /* 0x08 */ u32 bufferSize;
};

class ChatBalloonReceiver {
public:
    ChatBalloonReceiver();
    virtual ~ChatBalloonReceiver();
    void update();
    void shutdown();
    void init();
};

class ChatBalloonProc : public GameProc {
public:
    ChatBalloonProc();
    virtual ~ChatBalloonProc();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    /* 0x050 */ ChatQuickMsgInput quickMsgInput;
    /* 0x054 */ ChatBalloonList balloonList;
    /* 0x348 */ ChatBalloonReceiver receiver;
};

class EncodedStringRef : public EncodedString {
public:
    EncodedStringRef(u8 *data, u32 size);
    virtual ~EncodedStringRef();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x10 */ u8 *buffer;
    /* 0x14 */ u32 bufferSize;
};

extern const u8 data_020c8ce4;
extern const u32 sChatBalloonNameSeqs[4];

extern "C" {
extern CommManager *gCommManager;
extern u16 gPad[];
extern void *const gSpriteSeqTable[45];
extern s32 gGfxMainOnTop;

BOOL TalkRequest_IsActive();
s32 Scene_GetCurrent();
void MI_CpuCopy8(const void *src, void *dst, u32 n);
TextLabel *MsgTextLabel_CreateVram(u32 a, s32 b, s32 c);
void MsgTextLabel_Destroy(TextLabel *obj);
void Math_StepS32(void *p, s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
}

static inline BOOL IsPositive(s32 v) {
    if (v > 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL IsZero(BOOL v) {
    if (v == 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_02038f10_Pos(s32 v) {
    if (v > 0) {
        return TRUE;
    }
    return FALSE;
}

ChatBalloonText::ChatBalloonText() { clear(); }

ChatBalloonText::~ChatBalloonText() {}

u32 ChatBalloonText::capacity() { return 0x21; }

u8 *ChatBalloonText::data() { return text; }

EncodedStringRef::EncodedStringRef(u8 *data, u32 size) : buffer(data), bufferSize(size) {}

EncodedStringRef::~EncodedStringRef() {}

u32 EncodedStringRef::capacity() { return bufferSize; }

u8 *EncodedStringRef::data() { return buffer; }

ChatBalloonName::ChatBalloonName() { StrBuf_Clear((StrBuf *)this); }

ChatBalloonName::~ChatBalloonName() {}

u32 ChatBalloonName::capacity() { return 9; }

u8 *ChatBalloonName::data() { return text; }

EncodedStringBaseRef::EncodedStringBaseRef(u8 *data, u32 size) : buffer(data), bufferSize(size) {}

EncodedStringBaseRef::~EncodedStringBaseRef() {}

u32 EncodedStringBaseRef::capacity() { return bufferSize; }

u8 *EncodedStringBaseRef::data() { return buffer; }

ChatBalloon::ChatBalloon()
    : localIndex(0), palette(0), nameSeqIndex(0), textSeqIndex(0), stackTargetY(0), stackY(0), popOffsetY(0), slideY(0) {
    nameLabel = 0;
    textLabel = 0;
    state = 0;
    stateTimer = 0;
    cooldown = 0;
    request = 0;
    visible = 0;
}

ChatBalloon::~ChatBalloon() {
    destroyNameLabel();
    destroyTextLabel();
}

void ChatBalloon::draw() {
    if (visible != 0) {
        if (localIndex == 0) {
            GXOamAttr *h = textAnim.getCell();
            s32 x = getOriginX() + textAnim.getFrameX(-1);
            s32 y = slideY + (popOffsetY + (stackY + getOriginY()) + textAnim.getFrameY(-1));
            Oam_DrawCell(0, h, x, y, palette, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            GXOamAttr *h1 = nameAnim.getCell();
            s32 x1 = getOriginX() + nameAnim.getFrameX(-1);
            s32 y1 = slideY + (popOffsetY + (stackY + getOriginY()) + nameAnim.getFrameY(-1));
            GXOamAttr *h2 = textAnim.getCell();
            s32 x2 = getOriginX() + textAnim.getFrameX(-1);
            s32 y2 = slideY + (popOffsetY + (stackY + getOriginY()) + textAnim.getFrameY(-1));
            Oam_DrawCell(2, h1, x1, y1, palette, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            Oam_DrawCell(2, h2, x2, y2, palette, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}
extern const s32 data_020c8cb8;
extern const s32 data_020c8cbc;
extern const u32 sChatBalloonNameSeqs[4];
extern const s32 data_020c8cb4;
extern const s32 data_020c8cc0;
extern const u32 sChatBalloonTextSeqs[4];

const s32 data_020c8cb8 = 0x20000;

const s32 data_020c8cbc = 0x20000;

void ChatBalloon::update() {
    if (cooldown > 0) {
        cooldown--;
    }
    static Unk_020d9194_Fn tbl[4] = {&ChatBalloon::execHidden, &ChatBalloon::execOpen,
                                     &ChatBalloon::execShow, &ChatBalloon::execClose};
    (this->*tbl[state])();
    if (state != 0) {
        if (localIndex != 0) {
            nameAnim.update();
        }
        textAnim.update();
    }
}
extern const u32 sChatBalloonTextSeqs[4];

void ChatBalloon::updateSlideOffset() {
    s32 a, t, t2;
    if (localIndex == 0) {
        a = MenuCtrl_GetTransitionProgressOrFull();
        t = func_01ffcb0c(0x4c000, a);
        t2 = func_01ffcb0c(0xc0000, 0x1000 - a);
        slideY = (t + t2) >> 12;
    } else {
        a = MenuCtrl_GetTransitionProgress();
        t = func_01ffcb0c(-0x5c000, a);
        t2 = func_01ffcb0c(0x30000, 0x1000 - a);
        slideY = (t + t2) >> 12;
    }
}

void ChatBalloon::setMessage(StrBuf *a, MsgString *b, s32 c) {
    StrBuf_Copy((StrBuf *)&name, a);
    text.copy(b);
    palette = c + 5;
}

void ChatBalloon::setup(s32 a, s32 b, s32 c) {
    localIndex = a;
    nameSeqIndex = b;
    textSeqIndex = c;
    initSprites();
}

BOOL ChatBalloon::requestOpen() {
    BOOL r = state == 0 ? TRUE : FALSE;
    if (r) {
        request = 2;
    }
    return r;
}

BOOL ChatBalloon::requestClose() {
    BOOL r = state != 0 ? TRUE : FALSE;
    if (r) {
        request = 0;
    }
    return r;
}

void ChatBalloon::refreshLabelsUnk() {
    if (nameLabel != NULL) {
        nameLabel->copyMode = 3;
        nameLabel->requestRedraw();
    }
    if (textLabel != NULL) {
        textLabel->copyMode = 3;
        textLabel->requestRedraw();
    }
}

void ChatBalloon::reset() {
    text.clear();
    StrBuf_Clear((StrBuf *)&name);
    destroyNameLabel();
    destroyTextLabel();
    stateTimer = 0;
    cooldown = 0;
    request = 0;
    enterHidden();
}

void ChatBalloon::enterHidden() {
    state = 0;
    visible = 0;
}

void ChatBalloon::execHidden() {
    if (request != 0) {
        createNameLabel();
        createTextLabel();
        fitToText();
        enterOpen();
    }
}

void ChatBalloon::enterOpen() {
    s32 a, b;
    state = 1;
    visible = 1;
    if (localIndex == 0) {
        a = DebugVar_GetStub() + 3;
    } else {
        a = DebugVar_GetStub() + 3;
    }
    if (localIndex == 0) {
        b = DebugVar_GetStub() + 5;
    } else {
        b = DebugVar_GetStub() - 5;
    }
    stateTimer = a;
    popOffsetY = b;
    if (localIndex != 0) {
        Snd_PlaySe(0x3f);
    }
}

void ChatBalloon::execOpen() {
    s32 a, b, c;
    if (localIndex == 0) {
        a = DebugVar_GetStub() + 2;
    } else {
        a = DebugVar_GetStub() + 2;
    }
    if (localIndex == 0) {
        b = DebugVar_GetStub() - 6;
    } else {
        b = DebugVar_GetStub() + 6;
    }
    if (localIndex == 0) {
        c = DebugVar_GetStub() + 2;
    } else {
        c = DebugVar_GetStub() - 2;
    }
    if (stateTimer > a) {
        popOffsetY += b;
    } else {
        popOffsetY += c;
    }
    stateTimer--;
    if (stateTimer <= 0) {
        popOffsetY = 0;
        enterShow();
    }
}

void ChatBalloon::enterShow() {
    s32 t;
    state = 2;
    visible = 1;
    if (localIndex == 0) {
        t = DebugVar_GetStub() + 0x258;
    } else {
        t = DebugVar_GetStub() + 0x258;
    }
    stateTimer = t;
}

void ChatBalloon::execShow() {
    s32 t;
    if (localIndex == 0) {
        t = DebugVar_GetStub() + 6;
    } else {
        t = DebugVar_GetStub() + 6;
    }
    Math_StepS32(&stackY, stackTargetY, t);
    stateTimer--;
    if (stateTimer <= 0) {
        request = 0;
    }
    if (request == 0) {
        enterClose();
    }
}

void ChatBalloon::enterClose() {
    s32 t;
    state = 3;
    visible = 1;
    if (localIndex == 0) {
        t = DebugVar_GetStub() + 2;
    } else {
        t = DebugVar_GetStub() + 2;
    }
    stateTimer = t;
}

void ChatBalloon::execClose() {
    s32 t;
    if (localIndex == 0) {
        t = DebugVar_GetStub() + 0xb;
    } else {
        t = DebugVar_GetStub() - 0xb;
    }
    popOffsetY += t;
    stateTimer--;
    if (stateTimer <= 0) {
        destroyNameLabel();
        destroyTextLabel();
        enterHidden();
        if (localIndex == 0) {
            t = DebugVar_GetStub();
        } else {
            t = DebugVar_GetStub() + 0xa;
        }
        cooldown = t;
    }
}

void ChatBalloon::initSprites() {
    u8 *t = (u8 *)gSpriteSeqTable[textSeqIndex];
    if (localIndex != 0) {
        ((SpriteAnim *)(&nameAnim))->setSeq((SpriteAnimSeq *)((u8 *)gSpriteSeqTable[nameSeqIndex]));
        ((SpriteAnim *)(&nameAnim))->setPlayOnce(1);
        ((SpriteAnim *)(&nameAnim))->setSpeed(0);
    }
    ((SpriteAnim *)(&textAnim))->setSeq((SpriteAnimSeq *)(t));
    ((SpriteAnim *)(&textAnim))->setPlayOnce(1);
    ((SpriteAnim *)(&textAnim))->setSpeed(0);
}

void ChatBalloon::fitToText() {
    u32 w, n, w2, n2;
    s32 pad, hi, lo;
    if (nameLabel != NULL) {
        w = nameLabel->measureWidth();
        n = (w + 7) >> 3;
        pad = n * 8 - w;
        hi = nameAnim.getSeq()->frameCount - 1;
        lo = n - 1;
        if (lo < 0) {
            hi = 0;
        } else if (lo <= hi) {
            hi = lo;
        }
        ((SpriteAnim *)(&nameAnim))->setFrame(hi, 0);
        nameLabel->xOffset = pad;
    }
    w2 = textLabel->measureWidth();
    n2 = (w2 + 7) >> 3;
    hi = textAnim.getSeq()->frameCount - 1;
    lo = n2 - 1;
    if (lo < 0) {
        hi = 0;
    } else if (lo <= hi) {
        hi = lo;
    }
    ((SpriteAnim *)(&textAnim))->setFrame(hi, 0);
    if (localIndex == 0 && textLabel != NULL) {
        textLabel->xOffset = (n2 * 8 - w2) >> 1;
    }
}

void ChatBalloon::createNameLabel() {
    if (localIndex != 0 && nameLabel == NULL) {
        nameLabel = MsgTextLabel_CreateVram((*(volatile s32 *)&localIndex << 3) + 0x1c0, 8, 2);
        if (nameLabel != NULL) {
            nameLabel->vramLoader = 4;
            TextLabel *t = nameLabel;
            t->textStart = ((StrBuf *)&name)->data();
            if (gGfxMainOnTop == 0) {
                nameLabel->copyMode = 3;
            } else {
                nameLabel->copyMode = 2;
            }
            nameLabel->group = 1;
            nameLabel->rowStride1K = 1;
            nameLabel->bgColor = 0xe;
            nameLabel->fgColor = 0xd;
            nameLabel->requestRedraw();
        }
    }
}

void ChatBalloon::destroyNameLabel() {
    if (nameLabel != NULL) {
        MsgTextLabel_Destroy(nameLabel);
        nameLabel = NULL;
    }
}

void ChatBalloon::createTextLabel() {
    if (textLabel == NULL) {
        textLabel = MsgTextLabel_CreateVram((localIndex << 6) + 0xc0, 0x14, 2);
        if (textLabel != NULL) {
            textLabel->vramLoader = 4;
            TextLabel *t = textLabel;
            t->textStart = ((MsgString *)&text)->data();
            if (gGfxMainOnTop == 0) {
                textLabel->copyMode = 3;
            } else {
                textLabel->copyMode = 2;
            }
            textLabel->group = 1;
            textLabel->rowStride1K = 1;
            textLabel->bgColor = 0xf;
            textLabel->fgColor = 0xd;
            textLabel->requestRedraw();
        }
    }
}

void ChatBalloon::destroyTextLabel() {
    if (textLabel != NULL) {
        MsgTextLabel_Destroy(textLabel);
        textLabel = NULL;
    }
}

extern "C" void ChatBalloon_Post(s32 idx, StrBuf *a, MsgString *b) { sChatBalloonList->post(idx, a, b); }

extern "C" void ChatBalloon_Dismiss(s32 idx) { sChatBalloonList->dismiss(idx); }

extern "C" void ChatBalloon_DismissAll(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        sChatBalloonList->dismiss(i);
    }
}

extern "C" BOOL ChatBalloon_IsRemoteBusy(void) {
    BOOL r = FALSE;
    s32 i = 0;
    for (; i < 4; i++) {
        ChatBalloon *p = &sChatBalloonList->balloons[i];
        if ((p->localIndex != 0 && p->state != 0) || Unk_02038f10_Pos(p->cooldown)) {
            r = TRUE;
            break;
        }
    }
    return r;
}

extern "C" BOOL ChatBalloon_IsOwnBusy(void) {
    BOOL r = FALSE;
    s32 i = 0;
    for (; i < 4; i++) {
        ChatBalloon *p = &sChatBalloonList->balloons[i];
        if ((p->localIndex == 0 && p->state != 0) || Unk_02038f10_Pos(p->cooldown)) {
            r = TRUE;
            break;
        }
    }
    return r;
}

extern "C" void ChatBalloon_RefreshLabelsUnk(void) { sChatBalloonList->refreshLabelsUnk(); }

extern "C" void ChatBalloon_ClearAll(void) { sChatBalloonList->clear(); }

ChatBalloonList::ChatBalloonList() {
    s32 i;
    for (i = 0; i < 4; i++) {
        queue[i] = NULL;
        shown[i] = NULL;
    }
}

ChatBalloonList::~ChatBalloonList() {}

void ChatBalloonList::post(s32 idx, StrBuf *a, MsgString *b) {
    if (idx <= 4) {
        ChatBalloon *p = &balloons[toLocalIndex(idx)];
        if (enqueue(p)) {
            p->setMessage(a, b, getColorIndex(idx));
            if (p->localIndex == 0) {
                ChatBalloon_SendSyncVar(idx, p);
            }
        }
    }
}

s32 ChatBalloonList::toLocalIndex(s32 idx) {
    return (idx - gCommManager->myAid + 4) % 4;
}

s32 ChatBalloonList::getColorIndex(s32 idx) {
    if (idx == 4) {
        idx = 0;
    }
    return idx;
}

void ChatBalloonList::dismiss(s32 idx) {
    s32 i;
    if (idx <= 4) {
        s32 v = toLocalIndex(idx);
        for (i = 0; i < 4; i++) {
            ChatBalloon *p = queue[i];
            if (p != NULL && v == p->localIndex) {
                queue[i] = NULL;
                break;
            }
        }
        for (i = 0; i < 4; i++) {
            ChatBalloon *p = shown[i];
            if (p != NULL && v == p->localIndex) {
                p->requestClose();
                break;
            }
        }
    }
}

BOOL ChatBalloonList::enqueue(ChatBalloon *p) {
    BOOL ok = FALSE;
    s32 i;
    if (isQueued(p)) {
        ok = TRUE;
    } else {
        for (i = 0; i < 4; i++) {
            if (queue[i] == NULL) {
                queue[i] = p;
                ok = TRUE;
                break;
            }
        }
    }
    return ok;
}

BOOL ChatBalloonList::tryShow(ChatBalloon *p) {
    BOOL result = FALSE;
    s32 z, i;
    if (isShown(p)) {
        p->requestClose();
    } else if (!IsPositive(p->cooldown)) {
        for (i = 3, z = 0; i >= 0; i--) {
            if (shown[i]) {
                if (shown[i]->localIndex) {
                    z += 0x10;
                }
            } else {
                shown[i] = p;
                if (p->localIndex == 0) {
                    z = 0;
                }
                p->stackY = z;
                p->stackTargetY = z;
                p->updateSlideOffset();
                p->requestOpen();
                result = TRUE;
                break;
            }
        }
    }
    return result;
}

void ChatBalloonList::showQueued() {
    s32 i, j, k;
    for (i = 0; i < 4; i++) {
        if (queue[i] && tryShow(queue[i])) {
            queue[i] = NULL;
        }
    }
    for (j = 0; j < 4; j++) {
        if (queue[j] == NULL) {
            for (k = j + 1; k < 4; k++) {
                if (queue[k]) {
                    queue[j] = queue[k];
                    queue[k] = NULL;
                    break;
                }
            }
        }
    }
}

void ChatBalloonList::layoutShown() {
    s32 i, z;
    for (i = 3, z = 0; i >= 0; i--) {
        ChatBalloon *p = shown[i];
        if (p && p->localIndex) {
            p->stackTargetY = z;
            z += 0x10;
        }
    }
}

void ChatBalloonList::removeFinished() {
    s32 i, j, k;
    for (i = 0; i < 4; i++) {
        ChatBalloon *p = shown[i];
        if (p && p->state == 0 && p->request == 0) {
            shown[i] = NULL;
        }
    }
    for (j = 0; j < 4; j++) {
        if (shown[j] == NULL) {
            for (k = j + 1; k < 4; k++) {
                if (shown[k]) {
                    shown[j] = shown[k];
                    shown[k] = NULL;
                    break;
                }
            }
        }
    }
}

BOOL ChatBalloonList::isQueued(ChatBalloon *p) {
    BOOL r = FALSE;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (queue[i] == p) {
            r = TRUE;
            break;
        }
    }
    return r;
}

BOOL ChatBalloonList::isShown(ChatBalloon *p) {
    BOOL r = FALSE;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (shown[i] == p) {
            r = TRUE;
            break;
        }
    }
    return r;
}

void ChatBalloonList::init() {
    s32 i;
    sChatBalloonList = this;
    for (i = 0; i < 4; i++) {
        balloons[i].setup(i, sChatBalloonNameSeqs[i], sChatBalloonTextSeqs[i]);
    }
}

void ChatBalloonList::shutdown() {
    clear();
    sChatBalloonList = NULL;
}

void ChatBalloonList::update() {
    s32 i;
    showQueued();
    layoutShown();
    for (i = 0; i < 4; i++) {
        balloons[i].update();
    }
    removeFinished();
}

void ChatBalloonList::draw() {
    s32 i;
    for (i = 3; i >= 0; i--) {
        ChatBalloon *p = shown[i];
        if (p) {
            p->updateSlideOffset();
            p->draw();
        }
    }
}

void ChatBalloonList::refreshLabelsUnk() {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (shown[i]) {
            shown[i]->refreshLabelsUnk();
        }
    }
}

void ChatBalloonList::clear() {
    s32 i;
    for (i = 0; i < 4; i++) {
        balloons[i].reset();
        queue[i] = NULL;
        shown[i] = NULL;
    }
}

ChatBalloonReceiver::ChatBalloonReceiver() {}

ChatBalloonReceiver::~ChatBalloonReceiver() {}

void ChatBalloonReceiver::init() {}

void ChatBalloonReceiver::shutdown() {}

void ChatBalloonReceiver::update() { ChatBalloon_ReceiveRemote(); }

extern "C" void ChatBalloon_SendSyncVar(s32 i, ChatBalloon *x) {
    if (i < 4) {
        CommManager *g = gCommManager;
        if ((g)->isOnline() && (g)->isSlotActive(i)) {
            CommSyncVar_SetVar(i + 0x14, x, 0, 1);
        }
    }
}

extern "C" void ChatBalloon_ReceiveRemote() {
    CommManager *g = gCommManager;
    s32 n = g->myAid;
    s32 i;
    if ((g)->isOnline()) {
        for (i = 0; i < 4; i++) {
            if (i != n && (g)->isSlotActive(i) && ChatBalloon_ReadSyncVar(i)) {
                EncodedStringBaseRef s((sChatBalloonSyncBuf + 1), 8);
                EncodedStringRef b((sChatBalloonSyncBuf + 9), 0x20);
                ChatBalloonName t;
                ChatBalloonText u;
                StrBuf_GameToAscii((StrBuf *)&t, (StrBuf *)&s);
                u.fromEncoded(&b, 0, 0);
                ChatBalloon_Post(i, (StrBuf *)&t, &u);
            }
        }
    }
}

extern "C" u8 ChatBalloon_ReadSyncVar(s32 idx) {
    u8 *p = (gCommManager)->getSyncVar(idx + 0x14);
    u8 c = *p;
    if (c != 0) {
        s32 r = Scene_GetCurrent();
        if (r == 0x2e || r == 0xc || r == 0xd || r == 0xe || r == 0x2f) {
            c = 0;
        } else {
            MI_CpuCopy8(p, sChatBalloonSyncBuf, 0x29);
        }
        MI_CpuCopy8((void *)&data_020c8ce4, p, 1);
    }
    return c;
}

extern "C" void ChatBalloon_PackSyncVar(u8 *a, u32 b, ChatBalloon *c) {
    EncodedStringRef buf((sChatBalloonSyncBuf + 9), 0x20);
    EncodedStringBaseRef s((sChatBalloonSyncBuf + 1), 8);
    StrBuf_ClearAlt((StrBuf *)&buf);
    StrBuf_ClearAlt((StrBuf *)&s);
    buf.fromMsgString(&c->text);
    StrBuf_AsciiToGame((StrBuf *)&s, (StrBuf *)&c->name);
    sChatBalloonSyncBuf[0] = 1;
    MI_CpuCopy8(sChatBalloonSyncBuf, a, CommSyncVar_GetVarSize(b));
}

extern "C" void ChatQuickMsg_PostWantToSave() {
    void *p = PlayerData_GetCurrent();
    if (sChatQuickMsgCooldown <= 0 && p != NULL) {
        MsgString9B t;
        ChatBalloonText buf;
        u8 code;
        ((PlayerId *)(((PlayerData *)(p))->getPlayerId()))->getNameString((MsgString *)(void *)(&t));
        code = 0xef;
        String_Load2d(&buf, &code, 0);
        ChatBalloon_Post(gCommManager->myAid, (StrBuf *)&t, &buf);
        Snd_PlaySe(0x32);
        sChatQuickMsgCooldown = 0x1e;
    }
}

ChatQuickMsgInput::ChatQuickMsgInput() {}

ChatQuickMsgInput::~ChatQuickMsgInput() {}

void ChatQuickMsgInput::init() {}

void ChatQuickMsgInput::shutdown() {}

void ChatQuickMsgInput::update() {
    if (sChatQuickMsgCooldown > 0) {
        sChatQuickMsgCooldown--;
    }
    ChatQuickMsg_CheckButtons(this);
}

extern "C" void ChatQuickMsg_CheckButtons(void *self) {
    BOOL a, ready, modeOk, any;
    CommManager *g;
    BOOL b, c, d, e;
    BOOL idle;
    u32 keys;
    s32 mode = PlayerActor_GetAction(4);
    modeOk = TRUE;
    if (mode != 0x28 && mode != 0x2b && mode != 8 && mode != 9) {
        modeOk = FALSE;
    }
    keys = gPad[1];
    if (keys & 4) {
        a = TRUE;
    } else {
        a = FALSE;
    }
    if (keys & 0x400) {
        b = TRUE;
    } else {
        b = FALSE;
    }
    if (keys & 0x800) {
        c = TRUE;
    } else {
        c = FALSE;
    }
    if (keys & 1) {
        d = TRUE;
    } else {
        d = FALSE;
    }
    if (keys & 2) {
        e = TRUE;
    } else {
        e = FALSE;
    }
    any = TRUE;
    if (!(keys & 8) && !a && !b && !c && !d && !e) {
        any = FALSE;
    }
    g = gCommManager;
    ready = (g)->isOnline();
    if (TalkRequest_IsActive()) {
        idle = FALSE;
    } else {
        idle = TRUE;
    }
    if (sChatQuickMsgCooldown <= 0 && modeOk && any && ready && idle) {
        ChatBalloonText buf;
        s32 code;
        BOOL skip = FALSE;
        if (a) {
            code = 0xf0;
        } else if (b) {
            code = 0xf1;
        } else if (c) {
            code = 0xf2;
        } else if (d) {
            code = 0xf3;
        } else if (e) {
            code = 0xf4;
        } else {
            code = 0xef;
            if (g->myAid) {
                skip = TRUE;
            }
        }
        if (!skip) {
            u8 ch = code;
            String_Load2d(&buf, &ch, 0);
            MsgString9B t;
            ((PlayerId *)(PlayerData_GetCurrent()->getPlayerId()))->getNameString((MsgString *)(void *)(&t));
            ChatBalloon_Post(g->myAid, (StrBuf *)&t, &buf);
            Snd_PlaySe(0x32);
            sChatQuickMsgCooldown = 0x1e;
        }
    }
}

extern "C" ChatBalloonProc *ChatBalloonProc_Create() { return new ChatBalloonProc(); }

ChatBalloonProc::ChatBalloonProc() {}

ChatBalloonProc::~ChatBalloonProc() {}

BOOL ChatBalloonProc::onCreate() {
    quickMsgInput.init();
    balloonList.init();
    receiver.init();
    return TRUE;
}

BOOL ChatBalloonProc::onExecute() {
    quickMsgInput.update();
    if (HudObjGfx_IsMsgUiActive()) {
        balloonList.update();
    }
    receiver.update();
    return TRUE;
}

BOOL ChatBalloonProc::onDraw() {
    if (HudObjGfx_IsMsgUiActive()) {
        balloonList.draw();
    }
    return TRUE;
}

BOOL ChatBalloonProc::onDelete() {
    receiver.shutdown();
    balloonList.shutdown();
    quickMsgInput.shutdown();
    return TRUE;
}

const u32 sChatBalloonNameSeqs[4] = {7, 7, 8, 9};

const s32 data_020c8cb4 = 0x10000;

const s32 data_020c8cc0 = 0x10000;

u8 sChatBalloonSyncBuf[0x29];

ProcProfile sChatBalloonProcProfile = {(void *(*)())ChatBalloonProc_Create, 0xcb, 0x8d};

const u32 sChatBalloonTextSeqs[4] = {10, 11, 12, 13};

ChatBalloonList *sChatBalloonList;

s32 sChatQuickMsgCooldown;
