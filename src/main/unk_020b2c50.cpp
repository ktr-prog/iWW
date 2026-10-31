#include "uptr.h"
#include "types.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/MsgTag.h"
#include "talk/BmgReader.h"
#include "talk/MsgParser.h"
#include "talk/MsgString.h"
#include "talk/MsgRequest.h"
#include "talk/MsgWalker.h"
#include "talk/MsgString33.h"
#include "talk/MsgString25.h"
#include "talk/MsgString256.h"
#include "talk/ArticleCacheEntry.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020b2c50.h"

extern "C" {
u32 Msg_GetCharFromEnd(u8 *text, u32 n);
u32 Msg_GetCharAt(u8 *text, u32 n);
void MI_CpuFill8(void *dst, u32 value, u32 size);
s32 FX_Modf(s32 v, s32 *out);
u8 *Msg_SkipLines(u8 *text, u32 n);
}










class StringBank;

extern "C" {
}


class StringExpander : public MsgWalker {
public:
    StringExpander(StringBank *owner);
    virtual ~StringExpander();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    void setCapitalizeNext();
    BOOL differsFromName();
    BOOL canCheckName();
    BOOL differsFromLast(s32 c);
    void setAttr();
    void insertSlot();
    void handleTagFF02();
    void insertGlyphTag10();
    void insertGlyphTag9();
    void insertGlyphTag6();
    void insertNameLast2();
    void insertNameChar2();
    void insertNameChar1();
    void insertNameChar0();
    void appendTagTail();
    void appendRawTag();
    void appendChar();
    u8 expand(u8 a, u8 b);

    /* 0x24 */ StringBank *bank;
    /* 0x28 */ MsgTag tag;
    /* 0x3c */ s32 curChar;
    /* 0x40 */ u32 outLen;
    /* 0x44 */ u8 nameCharPending;
    /* 0x45 */ u8 success;
    /* 0x46 */ u8 resolveAltText;
    /* 0x47 */ u8 nicknameMode;
    /* 0x48 */ u8 capitalizeNext;
};

class TabooCensorWriter : public MsgWalker {
public:
    TabooCensorWriter();
    virtual ~TabooCensorWriter();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    u8 appendChar(u32 c);
    s32 readChar();
    void copyChar();
    void censorChars(s32 n);
    void restartScan();
    void setDest(MsgString *p);
    void setSource(MsgString *p);
    void resetWriter();

    /* 0x24 */ s32 mode;
    /* 0x28 */ MsgString *source;
    /* 0x2c */ MsgString *dest;
    /* 0x30 */ u8 *scanPos;
    /* 0x34 */ u8 atEnd;
    /* 0x38 */ s32 curChar;
    /* 0x3c */ s32 remaining;
};

class MsgCharReader : public MsgWalker {
public:
    MsgCharReader();
    virtual ~MsgCharReader();
    virtual void onBegin();
    virtual void onEnd();
    virtual void onChar(u32 c);
    virtual void onTag(u8 *p);
    virtual BOOL canContinue();

    /* 0x24 */ u8 *text;
    /* 0x28 */ s32 remaining;
    /* 0x2c */ u32 curChar;
};


class BmgReader1K : public BmgReader {
public:
    BmgReader1K();
    virtual ~BmgReader1K();
    virtual u8 *getBuffer();
    virtual u32 getBufferSize();
    void clearBuffer();

    /* 0xa4 */ u8 buffer[0x400];
};

class StringMsgRequest : public MsgRequest {
public:
    StringMsgRequest();
    virtual ~StringMsgRequest();
    virtual const char *getMsgDir();

    /* 0x20 */ u32 dirIndex;
    /* 0x24 */ MsgString *dest;
    /* 0x28 */ u8 resolveAltText;
    /* 0x29 */ u8 nicknameMode;
};



class StringBank {
public:
    StringBank();
    ~StringBank();

    s32 matchTabooWord();
    BOOL censorTaboo();
    BOOL beginTabooCheck(MsgString *buf);
    BOOL load(StringMsgRequest *req);
    void reset();

    /* 0x000 */ StringExpander expander;
    /* 0x04c */ BmgReader1K reader;
    /* 0x4f0 */ MsgStringAttr attr;
    /* 0x4fc */ u8 output[0x400];
    /* 0x8fc */ MsgString33 slots[11];
    /* 0xb38 */ MsgStringBase *nameSource;
    /* 0xb3c */ TabooCensorWriter censor;
    /* 0xb7c */ MsgCharReader charReader;
    /* 0xbac */ ArticleCacheEntry articles[16];
};

struct Empty {
    Empty() {}
    ~Empty() {}
};


StringBank gStringBank;

MsgString25::MsgString25() { clear(); }

MsgString25::~MsgString25() {}

u32 MsgString25::capacity() { return 0x19; }

u8 *MsgString25::data() { return text; }

MsgString256::MsgString256() { clear(); }

MsgString256::~MsgString256() {}

u32 MsgString256::capacity() { return 0x100; }

u8 *MsgString256::data() { return text; }

extern "C" MsgString256 *String_GetTabooScratch(void) {
    static MsgString256 inst;
    return &inst;
}

ArticleCacheEntry::ArticleCacheEntry() : isLoaded(0) { clear(); }

ArticleCacheEntry::~ArticleCacheEntry() {}

u32 ArticleCacheEntry::capacity() {
    return 10;
}

u8 *ArticleCacheEntry::data() {
    return text;
}

BmgReader1K::BmgReader1K() : BmgReader(0) {}

BmgReader1K::~BmgReader1K() {}

void BmgReader1K::clearBuffer() {
    MI_CpuFill8(buffer, 0, 0x400);
}

u8 *BmgReader1K::getBuffer() {
    return buffer;
}

u32 BmgReader1K::getBufferSize() {
    return 0x400;
}

StringExpander::StringExpander(StringBank *owner) : bank(owner) {
    curChar = 0;
    outLen = 0;
    nameCharPending = 0;
    success = 1;
    resolveAltText = 0;
    nicknameMode = 0;
    capitalizeNext = 0;
}

StringExpander::~StringExpander() {}

u8 StringExpander::expand(u8 a, u8 b) {
    success = 1;
    outLen = 0;
    resolveAltText = a;
    nicknameMode = b;
    capitalizeNext = 0;
    curChar = 0;
    reset();
    begin(bank->reader.getBuffer());
    run(FALSE);
    if (success && nicknameMode) {
        if (!canCheckName() || !differsFromName()) {
            success = 0;
        }
    }
    return success;
}

void StringExpander::onBegin() {}

void StringExpander::onEnd() {}

void StringExpander::onChar(u32 c) {
    if (capitalizeNext) {
        c = Text_ToUpper(c);
        capitalizeNext = 0;
    }
    if (nicknameMode && nameCharPending) {
        if (!differsFromLast(c)) {
            success = 0;
        }
        nameCharPending = 0;
    }
    if (success) {
        curChar = c;
        appendChar();
    }
}

void StringExpander::onTag(u8 *cmd) {
    typedef void (StringExpander::*Fn)();
    tag.parse(cmd);
    s32 a = tag.group;
    s32 b = tag.id;
    Fn fn = 0;
    if (a == 0 && b == 2) {
        fn = &StringExpander::insertNameChar0;
    } else if (a == 0 && b == 3) {
        fn = &StringExpander::insertNameChar1;
    } else if (a == 0 && b == 4) {
        fn = &StringExpander::insertNameChar2;
    } else if (a == 0 && b == 5) {
        fn = &StringExpander::insertNameLast2;
    } else if (a == 0 && b == 6) {
        fn = &StringExpander::insertGlyphTag6;
    } else if (a == 0 && b == 9) {
        fn = &StringExpander::insertGlyphTag9;
    } else if (a == 0 && b == 10) {
        fn = &StringExpander::insertGlyphTag10;
    } else if (a == 0xff && b == 2) {
        fn = &StringExpander::handleTagFF02;
    } else if (a == 4 && tag.isSlotTag()) {
        fn = &StringExpander::insertSlot;
    } else if (a == 0xb && b == 0) {
        fn = &StringExpander::setAttr;
    } else if (a == 0xb && b == 3) {
        fn = &StringExpander::setCapitalizeNext;
    }
    if (fn) {
        (this->*fn)();
    } else {
        success = 0;
    }
}

BOOL StringExpander::canContinue() {
    return success;
}

void StringExpander::appendChar() {
    s8 c = curChar;
    if (0x400 - outLen > 1) {
        u32 i = outLen++;
        bank->output[i] = c;
    } else {
        success = 0;
    }
}

void StringExpander::appendRawTag() {
    char *p = (char *)tag.raw;
    u32 n = tag.argLen + 5;
    if (0x400 - outLen > n) {
        for (u32 i = 0; i < n; i++) {
            (bank->output + outLen)[i] = p[i];
        }
        outLen += n;
    } else {
        success = 0;
    }
}

void StringExpander::appendTagTail() {
    u32 a;
    char *b, *c;
    tag.getAltTextArgs(&a, &b, &c);
    u32 n = tag.argLen - 1;
    BOOL ok = 0x400 - outLen > n;
    skip(a * 2);
    if (ok) {
        for (u32 i = 0; i < n; i++) {
            (bank->output + outLen)[i] = c[i];
        }
        outLen += n;
    } else {
        success = 0;
    }
}

void StringExpander::insertNameChar0() {
    if (nicknameMode) {
        u32 a = Msg_GetCharAt(bank->nameSource->data(), 0);
        if (capitalizeNext) {
            a = Text_ToUpper(a);
            capitalizeNext = 0;
        }
        if (String_IsNonNullChar(a)) {
            curChar = a;
            appendChar();
            nameCharPending = 1;
        } else {
            success = 0;
        }
    }
}

void StringExpander::insertNameChar1() {
    if (nicknameMode) {
        u32 a = Msg_GetCharAt(bank->nameSource->data(), 1);
        if (capitalizeNext) {
            a = Text_ToUpper(a);
            capitalizeNext = 0;
        }
        if (String_IsNonNullChar(a)) {
            curChar = a;
            appendChar();
            nameCharPending = 1;
        } else {
            success = 0;
        }
    }
}

void StringExpander::insertNameChar2() {
    if (nicknameMode) {
        u32 a = Msg_GetCharAt(bank->nameSource->data(), 2);
        if (capitalizeNext) {
            a = Text_ToUpper(a);
            capitalizeNext = 0;
        }
        if (String_IsNonNullChar(a)) {
            curChar = a;
            appendChar();
            nameCharPending = 1;
        } else {
            success = 0;
        }
    }
}

void StringExpander::insertNameLast2() {
    if (nicknameMode) {
        u32 b, a;
        u8 *v = bank->nameSource->data();
        a = Msg_GetCharFromEnd(v, 0);
        b = Msg_GetCharFromEnd(v, 1);
        if (capitalizeNext) {
            a = Text_ToUpper(a);
            capitalizeNext = 0;
        }
        if (capitalizeNext) {
            b = Text_ToUpper(b);
            capitalizeNext = 0;
        }
        if (String_IsNonNullChar(a) && String_IsNonNullChar(b)) {
            curChar = b;
            appendChar();
            curChar = a;
            appendChar();
            nameCharPending = 1;
        } else {
            success = 0;
        }
    }
}

void StringExpander::insertGlyphTag6() {
    pushText(Text_GetSpecialCharStr5());
}

void StringExpander::insertGlyphTag9() {
    pushText(Text_GetSpecialCharStr9());
}

void StringExpander::insertGlyphTag10() {
    pushText(Text_GetSpecialCharStr10());
}

void StringExpander::handleTagFF02() {
    if (resolveAltText) {
        appendTagTail();
    } else {
        appendRawTag();
    }
}

void StringExpander::insertSlot() {
    pushText(bank->slots[tag.getSlotIndex()].data());
}

void StringExpander::setAttr() {
    u8 a, b, c;
    tag.getArgs3(&a, &b, &c);
    MsgStringAttr *p = &bank->attr;
    s32 v = a;
    if (a >= 3) {
        v = -1;
    }
    p->form = v;
    p->attrA = b;
    p->attrB = c;
}

void StringExpander::setCapitalizeNext() {
    capitalizeNext = 1;
}

extern "C" BOOL String_IsNonNullChar(u32 x) {
    BOOL r = TRUE;
    if (x == 0) {
        r = FALSE;
    }
    return r;
}

BOOL StringExpander::differsFromLast(s32 c) {
    BOOL r = TRUE;
    if (curChar == c) {
        r = FALSE;
    }
    return r;
}

BOOL StringExpander::canCheckName() {
    return TRUE;
}

BOOL StringExpander::differsFromName() {
    u8 *p = bank->nameSource->data();
    return strcmp((const char *)p, (const char *)bank->output) != 0;
}

TabooCensorWriter::TabooCensorWriter() {
    mode = 0;
    source = 0;
    dest = 0;
    scanPos = 0;
    atEnd = 0;
    curChar = 0;
    remaining = 0;
}

TabooCensorWriter::~TabooCensorWriter() {}

void TabooCensorWriter::resetWriter() {
    mode = 0;
    source = 0;
    dest = 0;
    scanPos = 0;
    atEnd = 0;
    curChar = 0;
    remaining = 0;
    reset();
}

void TabooCensorWriter::setSource(MsgString *p) {
    source = p;
    scanPos = p->data();
}

void TabooCensorWriter::setDest(MsgString *p) {
    dest = p;
}

void TabooCensorWriter::restartScan() {
    reset();
    begin(scanPos);
}

void TabooCensorWriter::censorChars(s32 n) {
    mode = 2;
    remaining = n;
    run(FALSE);
    mode = 0;
}

void TabooCensorWriter::copyChar() {
    mode = 1;
    remaining = 1;
    run(FALSE);
    mode = 0;
}

s32 TabooCensorWriter::readChar() {
    mode = 3;
    remaining = 1;
    curChar = 0;
    run(FALSE);
    mode = 0;
    return curChar;
}

void TabooCensorWriter::onBegin() {}

void TabooCensorWriter::onEnd() {
    if (mode == 1 || mode == 2) {
        atEnd = 1;
    }
}

void TabooCensorWriter::onChar(u32 c) {
    curChar = c;
    if (mode == 1) {
        appendChar(c);
        if (c != 10) {
            remaining--;
        }
    } else if (mode == 2) {
        if (c == 10) {
            appendChar(10);
        } else {
            appendChar(0x20);
            remaining--;
        }
    } else if (mode == 3) {
        if (c != 10) {
            remaining--;
        }
    }
}

void TabooCensorWriter::onTag(u8 *p) {}

BOOL TabooCensorWriter::canContinue() {
    BOOL r = remaining > 0;
    if ((mode == 1 || mode == 2) && !r) {
        scanPos = cursor;
    }
    return r;
}

u8 TabooCensorWriter::appendChar(u32 c) {
    u8 buf[3];
    func_02133ef8(buf, 3);
    buf[0] = c;
    return dest->append(buf);
}

MsgCharReader::MsgCharReader() {
    text = 0;
    remaining = 0;
    curChar = 0;
}

MsgCharReader::~MsgCharReader() {}

void MsgCharReader::onBegin() {}

void MsgCharReader::onEnd() {}

void MsgCharReader::onChar(u32 c) {
    curChar = c;
    remaining--;
}

void MsgCharReader::onTag(u8 *p) {}

BOOL MsgCharReader::canContinue() {
    return remaining > 0;
}

extern "C" BOOL String_Load(MsgString *buf, u8 *key, const char *name) {
    StringMsgRequest req;
    req.setFileName(name);
    req.msgIndex = *key;
    req.dest = buf;
    gStringBank.reset();
    BOOL r = gStringBank.load(&req);
    return r;
}

extern "C" BOOL String_LoadResolveAltText(MsgString *buf, u8 *key, const char *name) {
    StringMsgRequest req;
    req.setFileName(name);
    req.msgIndex = *key;
    req.dest = buf;
    req.resolveAltText = 1;
    gStringBank.reset();
    BOOL r = gStringBank.load(&req);
    return r;
}

extern "C" BOOL String_Load2d(MsgString *buf, u8 *key, const char *name) {
    if (name == NULL) {
        name = "2d_menu";
    }
    StringMsgRequest req;
    req.dirIndex = 1;
    req.setFileName(name);
    req.msgIndex = *key;
    req.dest = buf;
    gStringBank.reset();
    BOOL r = gStringBank.load(&req);
    return r;
}

extern "C" u8 String_SetSlot(u32 idx, MsgString *other) {
    return gStringBank.slots[idx].copy(other);
}

extern "C" s32 Str_LenN(const char *s, u32 max) {
    u32 i = 0;
    while (i < max) {
        if (s[i] == 0) {
            break;
        }
        i++;
    }
    return i;
}

extern "C" void Str_ShiftRight(char *s, u32 size, s32 start, s32 shift) {
    if (shift != 0) {
        s32 i = size - shift - 1;
        char *d = s + shift;
        for (; i >= start; i--) {
            d[i] = s[i];
        }
    }
}

extern "C" void Str_WriteDigitsReversed(char *s, u32 size, s32 n, s32 maxDigits) {
    if (n == 0) {
        s[0] = '0';
    } else {
        for (s32 i = 0; i < maxDigits && n != 0; i++) {
            s32 q = n / 10;
            s[i] = n - q * 10 + '0';
            n = q;
        }
    }
}

extern "C" void Str_PadFrontSpaces(char *s, u32 size, s32 width) {
    s32 n = width - Str_LenN(s, size);
    Str_ShiftRight(s, size, 0, n);
    for (s32 i = n - 1; i >= 0; i--) {
        s[i] = ' ';
    }
}

extern "C" void Str_PadBackSpaces(char *s, u32 size, s32 width) {
    s32 len = Str_LenN(s, size);
    for (; len < width; len++) {
        s[len] = ' ';
    }
}

extern "C" void Str_PadBackZeros(char *s, u32 size, s32 width) {
    s32 len = Str_LenN(s, size);
    for (; len < width; len++) {
        s[len] = '0';
    }
}

extern "C" void Str_InsertThousandsSeparators(char *s, u32 size, s32 minRun) {
    s32 i = 0;
    s32 run = 0;
    while (s[i] != 0) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            run++;
            if (run >= minRun) {
                run = 0;
                u32 j = i + 1;
                if (j < size) {
                    char *p = s + j;
                    char d = s[j];
                    if (d >= '0' && d <= '9') {
                        Str_ShiftRight(s, size, i, 1);
                        *p = ',';
                    }
                }
            }
        }
        i++;
    }
}

extern "C" void Str_Reverse(char *s, u32 size) {
    u32 len = Str_LenN(s, size);
    u32 half = len >> 1;
    u32 i = 0;
    s32 j = len - 1;
    for (; i < half; i++, j--) {
        char a = s[i];
        char b = s[j];
        s[i] = b;
        s[j] = a;
    }
}

extern "C" BOOL String_AppendUnitSuffix(MsgString *out, s32 val, s32 kind) {
    static const u8 t6[10] = {9, 9, 7, 8, 7, 7, 9, 7, 7, 7};
    static const u8 t9[10] = {0xd, 0xd, 0xc, 0xd, 0xc, 0xc, 0xd, 0xc, 0xd, 0xc};
    static const u8 t3[10] = {3, 3, 2, 4, 2, 2, 3, 2, 3, 3};
    MsgString33 tmp;
    u8 v = 0;
    s32 rem = val % 10;
    if (kind == 1) {
    } else if (kind == 2) {
        v = 1;
    } else if (kind == 3) {
        v = t3[rem];
    } else if (kind == 4) {
        v = 5;
    } else if (kind == 5) {
        v = 6;
    } else if (kind == 6) {
        v = t6[rem];
    } else if (kind == 7) {
        v = 0xa;
    } else if (kind == 8) {
        v = 0xb;
    } else if (kind == 9) {
        v = t9[rem];
    } else if (kind == 10) {
        v = 0xe;
    }
    u8 c = v;
    BOOL r = String_Load(&tmp, &c, "st_unit");
    if (r) {
        r &= out->appendString(&tmp);
        if (r) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

extern "C" BOOL String_FormatNumber(MsgString *out, s32 val, s32 width, s32 mode, s32 kind, s32 unused) {
    char tmp[0xe];
    MI_CpuFill8(tmp, 0, 0xe);
    Str_WriteDigitsReversed(tmp, 0xe, val, width);
    switch (mode) {
    case 2:
    case 3:
        Str_PadFrontSpaces(tmp, 0xe, width);
    }
    switch (mode) {
    case 4:
    case 5:
        Str_PadBackSpaces(tmp, 0xe, width);
    }
    switch (mode) {
    case 6:
    case 7:
        Str_PadBackZeros(tmp, 0xe, width);
    }
    BOOL c = FALSE;
    u32 m = mode - 1;
    if (m <= 6 && ((1 << m) & 0x55)) {
        c = TRUE;
    }
    if (c) {
        Str_InsertThousandsSeparators(tmp, 0xe, 3);
    }
    Str_Reverse(tmp, 0xe);
    BOOL r = out->set((u8 *)tmp);
    if (kind != 0) {
        r &= String_AppendUnitSuffix(out, val, kind);
        if (r) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

extern "C" BOOL String_FormatFixedPoint(MsgString *out, s32 val, s32 digits) {
    static const u8 dot[2] = {0x2e, 0};
    BOOL ok;
    s32 i;
    BOOL r1;
    s32 frac;
    s32 ip;
    BOOL res;
    s32 ipart;
    frac = FX_Modf(val, &ip);
    for (i = 0; i < digits; i++) {
        frac *= 10;
    }
    ipart = ip >> 12;
    MsgString25 a, b;
    MsgString33 c;
    r1 = String_FormatNumber(&a, ipart, 10, 0, 0, 0);
    ok = TRUE;
    if (!(r1 & ok)) {
        ok = FALSE;
    }
    ok &= String_FormatNumber(&b, frac >> 12, 10, 0, 0, 0);
    if (ok) {
        res = TRUE;
    } else {
        res = FALSE;
    }
    res &= out->copy(&a);
    if (res) {
        res = TRUE;
    } else {
        res = FALSE;
    }
    res &= out->append((u8 *)dot);
    if (res) {
        res = TRUE;
    } else {
        res = FALSE;
    }
    res &= out->appendString(&b);
    if (res) {
        res = TRUE;
    } else {
        res = FALSE;
    }
    return res;
}

extern "C" BOOL String_GetWeekdayName(MsgString *buf, u32 idx, BOOL flag) {
    static const u8 tbl[8] = {0x17, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0};
    u8 c = tbl[idx];
    const char *name = "st_general";
    BOOL r;
    if (flag) {
        r = String_LoadResolveAltText(buf, &c, name);
    } else {
        r = String_Load(buf, &c, name);
    }
    return r;
}

extern "C" BOOL String_GetMonthName(MsgString *buf, u8 v) {
    u8 c = v - 1;
    return String_Load(buf, &c, "st_day_month");
}

extern "C" BOOL String_GetDayOrdinal(MsgString *buf, u8 v) {
    u8 c = v + 0xc;
    return String_Load(buf, &c, "st_day_month");
}

extern "C" BOOL String_MakeNickname(MsgString *buf, MsgStringBase *name, u8 *key) {
    StringMsgRequest req;
    req.setFileName("st_nickn");
    req.msgIndex = *key;
    req.dest = buf;
    req.nicknameMode = 1;
    gStringBank.nameSource = name;
    gStringBank.reset();
    BOOL r = gStringBank.load(&req);
    gStringBank.nameSource = 0;
    return r;
}

extern "C" BOOL String_CensorTaboo(MsgString *buf) {
    BOOL r = FALSE;
    if (gStringBank.beginTabooCheck(buf)) {
        r = gStringBank.censorTaboo();
    }
    return r;
}

extern "C" ArticleCacheEntry *String_GetArticle(u8 *key) {
    ArticleCacheEntry *r = NULL;
    s32 i = *key;
    if (i < 0x10) {
        ArticleCacheEntry *e = &gStringBank.articles[i];
        if (e->isLoaded != 0) {
            r = e;
        } else if (String_Load(e, key, "st_article")) {
            e->isLoaded = 1;
            r = e;
        }
    }
    return r;
}

void StringBank::reset() {
    reader.clearBuffer();
    attr.reset();
    MI_CpuFill8(output, 0, 0x400);
}

BOOL StringBank::load(StringMsgRequest *req) {
    char path[0x44];
    Str_SPrintf(path, "%s/%s.bmg", req->getMsgDir(), req->fileName);
    BOOL ok = reader.open(path);
    BOOL t = ok ? reader.loadMessage(&req->msgIndex) : FALSE;
    ok = ok & t;
    if (ok) {
        ok = TRUE;
    } else {
        ok = FALSE;
    }
    reader.close();
    if (ok) {
        MsgString *dst = req->dest;
        ok &= expander.expand(req->resolveAltText, req->nicknameMode);
        if (ok) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
        if (dst) {
            ok &= dst->set(output);
            if (ok) {
                ok = TRUE;
            } else {
                ok = FALSE;
            }
            dst->attr.copyFrom(&attr);
        }
    }
    return ok;
}

BOOL StringBank::beginTabooCheck(MsgString *buf) {
    Empty e;
    StringMsgRequest req;
    req.setFileName("st_taboo");
    req.msgIndex = 0;
    reset();
    BOOL r = gStringBank.load(&req);
    if (r) {
        String_GetTabooScratch()->copy(buf);
        buf->clear();
        censor.resetWriter();
        censor.setSource(String_GetTabooScratch());
        censor.setDest(buf);
        charReader.text = NULL;
        charReader.remaining = 0;
        charReader.curChar = 0;
        charReader.reset();
    }
    return r;
}

BOOL StringBank::censorTaboo() {
    BOOL result = FALSE;
    censor.restartScan();
    u8 *start = output;
    while (censor.atEnd == 0) {
        u8 *s = start;
        s32 n = 0;
        for (; s != NULL && *s != 0xa; s = Msg_SkipLines(s, 1)) {
            charReader.text = s;
            n = matchTabooWord();
            if (n > 0) {
                break;
            }
        }
        censor.restartScan();
        if (n > 0) {
            censor.censorChars(n);
            result = TRUE;
        } else {
            censor.copyChar();
        }
    }
    return result;
}

s32 StringBank::matchTabooWord() {
    s32 count = 0;
    censor.restartScan();
    charReader.reset();
    charReader.begin(charReader.text);
    for (;;) {
        charReader.remaining = 1;
        charReader.curChar = 0;
        charReader.run(FALSE);
        u32 c = charReader.curChar;
        if (c == 0xa || c == 0) {
            break;
        }
        if (String_CharEqualsIgnoreCase((u32)censor.readChar(), c)) {
            count++;
        } else {
            count = 0;
            break;
        }
    }
    return count;
}

extern "C" BOOL String_CharEqualsIgnoreCase(u32 a, u32 b) {
    BOOL r = FALSE;
    if (a == b) {
        r = TRUE;
    } else {
        u32 c = Text_ToUpper(a);
        if (c == b) {
            r = TRUE;
        }
    }
    return r;
}

StringBank::StringBank() : expander(this), nameSource(0) {
    MI_CpuFill8(output, 0, 0x400);
}

StringBank::~StringBank() {}

StringMsgRequest::StringMsgRequest() : dirIndex(0), dest(0), resolveAltText(0), nicknameMode(0) {}

StringMsgRequest::~StringMsgRequest() {}

const char *StringMsgRequest::getMsgDir() {
    static const char *const tbl[2] = {"/script/ENG/string", "/script/ENG/2d"};
    return tbl[dirIndex];
}

