#include "uptr.h"
#include "host_labels.h"
#include "types.h"
#include "talk/EncodedString.h"
#include "talk/MsgString33B.h"
#include "talk/MsgString129.h"
#include "talk/MsgString25B.h"
#include "talk/EncodedString128.h"
#include "talk/MsgString9B.h"
#include "talk/EncodedString8.h"
#include "talk/EncodedString41.h"
#include "ui/LabelString.h"



#include "item/Letter.h"
#include "item/LetterView.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerInventory.h"
#include "save/VillagerData.h"
#include "text/Unk_02050288.h"
#include "proto/main/unk_020030d8.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"

struct LetterDefaults {
    /* 0x00 */ u8 greeting[0x18];
    /* 0x18 */ u8 futureSelfGreeting[0x18];
    /* 0x30 */ u8 signature[0x20];
    /* 0x50 */ u8 greetingNamePos;
    /* 0x51 */ u8 futureSelfNamePos;
};

struct VillagerIdLocal : VillagerId {
    VillagerIdLocal() { VillagerId_Construct(this); }
    ~VillagerIdLocal() { VillagerId_Destruct(this); }
};
struct PlayerIdLocal : PlayerId {
    PlayerIdLocal() : PlayerId((void *)NULL) {}
    ~PlayerIdLocal() { new (static_cast<PlayerId *>(this)) PlayerId(); }
};

#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)

extern "C" {
void *MI_CpuFill8(void *dst, u32 v, u32 n);
void *MI_CpuCopy8(const void *src, void *dst, u32 n);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
}

static LetterDefaults *Letter_GetPlayerDefaults(PlayerData *player) {
    return (LetterDefaults *)((PlayerInventory *)player->getInventory())->getUnk988();
}

extern "C" LetterView *Letter_Copy(LetterView *self, const LetterView *src) {
    MI_CpuCopy8(src, self, 0xf4);
    return self;
}

extern "C" void LetterParty_GetNameBytes(LetterParty *self, u8 *out) {
    MsgString9B a;
    EncodedString8 b;
    VillagerIdLocal c;
    LabelString d;
    switch (self->partyType) {
    case 0:
    case 4:
    case 5:
    case 6:
        break;
    case 1:
    case 2:
        Mem_Copy(((PlayerId *)self)->playerName, out, 8);
        break;
    case 3:
        VillagerId_CopyFrom(&c, (VillagerId *)self);
        c.getName(&a);
        b.fromMsgString(&a);
        b.copyTo(out, 8);
        break;
    case 7:
        String_Load2dMenu(&d, 0x43);
        String_ToEncodedBytes(&d, out);
        break;
    }
}

extern "C" void LetterParty_GetName(LetterParty *self, MsgString *out) {
    VillagerIdLocal a;
    PlayerIdLocal b;
    switch (self->partyType) {
    case 0:
    case 4:
        break;
    case 1:
    case 2:
    case 6:
        b.copyFrom((PlayerId *)self);
        b.getNameString(out);
        break;
    case 3:
    case 5:
        VillagerId_CopyFrom(&a, (VillagerId *)self);
        a.getName(out);
        break;
    }
}

extern "C" LetterParty *LetterParty_AsPlayer(LetterParty *self) {
    if (self->partyType != 1 && self->partyType != 2 && self->partyType != 6) return 0;
    return self;
}

extern "C" LetterParty *LetterParty_AsVillager(LetterParty *self) {
    if (self->partyType != 3 && self->partyType != 5) return 0;
    return self;
}

extern "C" void LetterParty_SetVillager(LetterParty *self, VillagerId *src) {
    self->partyType = 3;
    VillagerId_CopyTo(src, (VillagerId *)self);
}

extern "C" void LetterParty_SetPlayer(LetterParty *self, PlayerId *src) {
    self->partyType = 2;
    src->copyTo((PlayerId *)self);
}

extern "C" void LetterParty_SetFutureSelf(LetterParty *self, PlayerId *src) {
    self->partyType = 1;
    src->copyTo((PlayerId *)self);
}

extern "C" void LetterParty_SetBottle(LetterParty *self) { self->partyType = 7; }

extern "C" void LetterParty_SetType(LetterParty *self, u32 v) { self->partyType = v; }

extern "C" u32 LetterParty_IsType(LetterParty *self, u32 t) {
    if (self->partyType == t) return TRUE;
    return FALSE;
}

Letter::Letter() : dsVtable(LETTER_DS_VTABLE) {}

Letter::~Letter() {}

extern "C" void Letter_Clear(LetterView *self) {
    MI_CpuFill8(self, 0, 0xf4);
    self->present = 0xfff1;
}

extern "C" u32 Letter_GetPaper(LetterView *self) { return self->paper; }

extern "C" void Letter_InitDraft(LetterView *self, u32 v) {
    PlayerData *r = PlayerData_GetCurrent();
    Letter_Clear(self);
    self->paper = v;
    self->kind = 0;
    self->sender.partyType = 2;
    r->getPlayerId()->copyTo((PlayerId *)&self->sender);
    self->setState(1);
    Letter_SetSignature(self, Letter_GetPlayerDefaults(r)->signature);
}

extern "C" void Letter_InitBottleDraft(LetterView *self) {
    u8 c;
    Letter_InitDraft(self, 0xc);
    self->setState(4);
    LetterParty_SetBottle(&self->recipient);
    c = 0x23;
    Letter_LoadTemplate2d(&c, self->greeting, &self->namePos, 0);
}

extern "C" void Letter_SetRecipientVillager(LetterView *self, s32 idx) {
    VillagerId *r = ((VillagerData *)SaveVillagers_Get(gSaveVillagers, idx))->getVillagerId();
    self->loadDefaultGreeting();
    LetterParty_SetVillager(&self->recipient, r);
}

extern "C" void Letter_SetRecipientResident(LetterView *self, s32 idx) {
    PlayerId *r = ((PlayerData *)PlayerData_GetResident(gSavePlayers, idx))->getPlayerId();
    self->loadDefaultGreeting();
    LetterParty_SetPlayer(&self->recipient, r);
}

extern "C" void Letter_SetRecipientFutureSelf(LetterView *self) {
    PlayerData *a = PlayerData_GetCurrent();
    PlayerId *b = a->getPlayerId();
    if (self->recipient.partyType != 1) {
        LetterDefaults *c = Letter_GetPlayerDefaults(a);
        Mem_Copy(c->futureSelfGreeting, self->greeting, 0x18);
        self->namePos = c->futureSelfNamePos;
    }
    LetterParty_SetFutureSelf(&self->recipient, b);
}

extern "C" void Letter_MarkSent(LetterView *self) {
    switch (self->getState()) {
    case 1:
        self->setState(2);
        break;
    case 4:
        self->setState(5);
        break;
    default:
        return;
    }
    self->setPresentFlags(1);
}

extern "C" void Letter_MarkRead(LetterView *self) {
    switch (self->getState()) {
    case 2:
        self->setState(3);
        break;
    case 5:
        self->setState(6);
        break;
    case 7:
        self->setState(8);
        break;
    }
}

extern "C" void Letter_MarkReceived(LetterView *self) {
    self->setState(2);
    self->kind = 0x11;
    if (self->present != 0xfff1) {
        self->setPresentFlags(1);
    }
}

extern "C" void Letter_SetTexts(LetterView *self, s32 *pv, MsgString *a, MsgString *b, MsgString *c) {
    self->namePos = *pv;
    EncodedString41 l;
    l.fromMsgString(a);
    Mem_Copy(l.text, self->greeting, 0x18);
    static EncodedString128 s;
    StrBuf_ClearAlt((StrBuf *)&s);
    s.fromMsgString(b);
    Mem_Copy(s.text, self->body, 0x80);
    l.fromMsgString(c);
    Mem_Copy(l.text, self->signature, 0x20);
}

extern "C" void Letter_FillFromVillager(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const u8 *ped,
                                        VillagerId *s1, PlayerId *s2) {
    VillagerIdLocal l1;
    PlayerIdLocal l2;
    VillagerId_Copy(&l1, s1);
    l2.setRaw(s2);
    Letter_Clear(self);
    self->paper = *ped;
    self->kind = 0;
    LetterParty_SetVillager(&self->sender, &l1);
    LetterParty_SetPlayer(&self->recipient, &l2);
    if (v < 0) {
        LetterParty_SetType(&self->recipient, 5);
        v = 0;
    }
    self->setState(2);
    Letter_SetTexts(self, &v, a, b, c);
}

extern "C" void Letter_ComposeVillagerMail(LetterView *self, const u8 *a1, const char *a2, const u8 *a3, VillagerId *a4,
                                           PlayerId *a5, s32 a6) {
    u32 out;
    if (a6 != 0xb) {
        MsgString9B o;
        a4->getName(&o);
        MailText_SetSlot(a6, &o);
    }
    MailText_LoadLetter(&sMailGreeting, &sMailBody, &sMailSignature, &out, a1, a2);
    Letter_FillFromVillager(self, &sMailGreeting, &sMailBody, &sMailSignature, out, a3, a4, a5);
}

extern "C" void Letter_ComposeVillagerMailZ(LetterView *self, u8 *a1, u8 *a2, u8 *a3, u8 *a4, const char *a5, const u8 *a6,
                                            VillagerId *a7, PlayerId *a8, s32 a9) {
    u32 out;
    if (a9 != 0xb) {
        MsgString9B o;
        a7->getName(&o);
        MailText_SetSlot(a9, &o);
    }
    MailText_LoadLetterZ(&sMailGreeting, &sMailBody, &sMailSignature, &out, a1, a2, a3, a4, a5);
    Letter_FillFromVillager(self, &sMailGreeting, &sMailBody, &sMailSignature, out, a6, a7, a8);
}

extern "C" void Letter_FillVillagerToVillager(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const u8 *ped,
                                              VillagerId *s1, VillagerId *s2) {
    VillagerIdLocal l1;
    VillagerIdLocal l2;
    VillagerId_Copy(&l1, s1);
    VillagerId_Copy(&l2, s2);
    Letter_Clear(self);
    self->paper = *ped;
    self->kind = 0;
    LetterParty_SetVillager(&self->sender, &l1);
    LetterParty_SetVillager(&self->recipient, &l2);
    if (v < 0) {
        LetterParty_SetType(&self->recipient, 5);
        v = 0;
    }
    self->setState(7);
    Letter_SetTexts(self, &v, a, b, c);
}

extern "C" void Letter_ComposeVillagerToVillagerZ(LetterView *self, u8 *a1, u8 *a2, u8 *a3, u8 *a4, const char *a5,
                                                  const u8 *a6, VillagerId *a7, VillagerId *a8, s32 a9) {
    u32 out;
    if (a9 != 0xb) {
        MsgString9B o;
        a7->getName(&o);
        MailText_SetSlot(a9, &o);
    }
    MailText_LoadLetterZ(&sMailGreeting, &sMailBody, &sMailSignature, &out, a1, a2, a3, a4, a5);
    Letter_FillVillagerToVillager(self, &sMailGreeting, &sMailBody, &sMailSignature, out, a6, a7, a8);
}

extern "C" void Letter_FillSystemMail(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v, const void *kind,
                                      const void *paper, PlayerId *player) {
    PlayerIdLocal tmp;
    tmp.setRaw(player);
    Letter_Clear(self);
    self->paper = *(const u8 *)paper;
    self->kind = *(const u8 *)kind;
    LetterParty_SetType(&self->sender, 4);
    LetterParty_SetPlayer(&self->recipient, &tmp);
    if (v < 0) {
        LetterParty_SetType(&self->recipient, 6);
        v = 0;
    }
    self->setState(2);
    Letter_SetTexts(self, &v, a, b, c);
}

extern "C" void Letter_ComposeFromMail(LetterView *self, const u8 *msgIndex, const char *fileName, const void *kind,
                                       const void *paper, PlayerId *player) {
    u32 out;
    MailText_LoadLetter(&sMailGreeting, &sMailBody, &sMailSignature, &out, msgIndex, fileName);
    Letter_FillSystemMail(self, &sMailGreeting, &sMailBody, &sMailSignature, out, kind, paper, player);
}

extern "C" void Letter_FillBottleMail(LetterView *self, MsgString *a, MsgString *b, MsgString *c, s32 v) {
    Letter_Clear(self);
    self->paper = 0xc;
    self->setState(5);
    LetterParty_SetType(&self->sender, 4);
    LetterParty_SetBottle(&self->recipient);
    if (v < 0) {
        LetterParty_SetType(&self->recipient, 6);
        v = 0;
    }
    self->kind = 0xc;
    Letter_SetTexts(self, &v, a, b, c);
}

extern "C" void Letter_ComposeBottleMail(LetterView *self, const u8 *a, const char *b) {
    u32 out;
    MailText_LoadLetter(&sMailGreeting, &sMailBody, &sMailSignature, &out, a, b);
    Letter_FillBottleMail(self, &sMailGreeting, &sMailBody, &sMailSignature, out);
}

extern "C" LetterParty *Letter_GetSenderPlayer(LetterView *self) { return LetterParty_AsPlayer(&self->sender); }

extern "C" LetterParty *Letter_GetRecipientPlayer(LetterView *self) { return LetterParty_AsPlayer(&self->recipient); }

extern "C" LetterParty *Letter_GetRecipientVillager(LetterView *self) { return LetterParty_AsVillager(&self->recipient); }

extern "C" void Letter_GetSenderNameBytes(LetterView *self, u8 *out) { LetterParty_GetNameBytes(&self->sender, out); }

extern "C" void Letter_GetRecipientNameBytes(LetterView *self, u8 *out) { LetterParty_GetNameBytes(&self->recipient, out); }

extern "C" u32 Letter_GetKind(LetterView *self) { return self->kind; }

extern "C" void Letter_GetSenderName(LetterView *self, MsgString *out) { LetterParty_GetName(&self->sender, out); }

extern "C" void Letter_GetRecipientName(LetterView *self, MsgString *out) { LetterParty_GetName(&self->recipient, out); }

extern "C" u32 Letter_IsBottle(LetterView *self) { return LetterParty_IsType(&self->recipient, 7); }

u16 LetterView::getPresent() {
    return present;
}

u8 LetterView::getPresentFlags() {
    return (u8)((status & 0xc0) >> 6);
}

void LetterView::setPresentFlags(u32 v) {
    status = (status & 0x3f) | (v << 6);
}

u32 LetterView::setPresent(u16 v, u32 w) {
    u16 old = present;
    if (w == 0xff) w = 0;
    present = v;
    setPresentFlags(w);
    return old;
}

u8 LetterView::getState() {
    return status & 0x3f;
}

void LetterView::setState(u32 v) {
    status = (status & 0xc0) | v;
}

BOOL LetterView::isToFutureSelf() {
    if (recipient.partyType == 1) return TRUE;
    return FALSE;
}

void LetterView::loadDefaultGreeting() {
    if ((u8)(recipient.partyType + 0xfe) <= 1) return;
    LetterDefaults *p = Letter_GetPlayerDefaults(PlayerData_GetCurrent());
    Mem_Copy(p->greeting, greeting, 0x18);
    namePos = p->greetingNamePos;
}

extern "C" void Letter_SetSignature(LetterView *o, u8 *p) {
    u8 buf[0x10];
    if (p[0] != 0) {
        Mem_Copy(p, o->signature, 0x20);
    } else {
        Mem_Clear(buf + 2, 8);
        Letter_GetSenderNameBytes(o, buf + 2);
        buf[0] = 0x24;
        Letter_LoadTemplate2d(buf, o->signature, buf + 1, buf + 2);
    }
}

extern "C" void LetterDefaults_Store(LetterDefaults *a, LetterView *b) {
    Mem_Copy(b->signature, a->signature, 0x20);
    if (Letter_IsBottle(b) == 0) {
        u8 *dst;
        if (b->isToFutureSelf()) {
            dst = a->futureSelfGreeting;
            a->futureSelfNamePos = b->namePos;
        } else {
            dst = a->greeting;
            a->greetingNamePos = b->namePos;
        }
        Mem_Copy(b->greeting, dst, 0x18);
    }
}

extern "C" void Letter_LoadTemplate2d(u8 *code, u8 *dst, u8 *lenOut, u8 *extra) {
    LabelString src;
    EncodedString41 out;
    s32 n;
    s32 m;
    String_Load2d(&src, code, NULL);
    out.fromMsgString(&src);
    n = Text_GetLineEnd(out.text, 0x29, 0);
    *lenOut = n;
    if (n != 0) {
        Mem_Copy(out.text, dst, n);
    }
    m = n;
    if (extra != NULL) {
        s32 t = Text_GetLength(extra, 8);
        Mem_Copy(extra, dst + n, t);
        m = n + t;
    }
    if (out.text[n] == 0x86) {
        s32 off = n + 1;
        u8 *p = out.text + off;
        s32 k = Text_GetLineEnd(p, 0x29 - off, 0);
        if (k != 0) {
            Mem_Copy(p, dst + m, k);
        }
    }
}

extern "C" void LetterDefaults_Init(LetterDefaults *o) {
    u8 code[2];
    MI_CpuFill8(o, 0, 0x52);
    code[0] = 0x23;
    Letter_LoadTemplate2d(&code[0], (u8 *)o, &o->greetingNamePos, NULL);
    code[1] = 0x26;
    Letter_LoadTemplate2d(&code[1], o->futureSelfGreeting, &o->futureSelfNamePos, NULL);
}

EncodedString128::EncodedString128() {
}

EncodedString128::~EncodedString128() {
}

u32 EncodedString128::capacity() {
    return 0x80;
}


u8 *EncodedString128::data() {
    return text;
}

MsgString25B sMailGreeting;
MsgString129 sMailBody;
MsgString33B sMailSignature;
