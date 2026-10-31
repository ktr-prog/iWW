#include "types.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "ui/LetterLayout.h"
#include "talk/BmgReader.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/TalkBmgReader.h"
#include "talk/EncodedString.h"
#include "talk/MsgString513.h"
#include "talk/MsgString33B.h"
#include "talk/MsgString129.h"
#include "talk/MsgString25B.h"
#include "ui/LetterTextLine.h"
#include "talk/EncodedString40.h"
#include "talk/EncodedString512.h"
#include "item/LetterView.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0206c768.h"
#include "proto/main/unk_020b2c50.h"

extern const u8 sMailCheckSeparators[8];




MsgString513::MsgString513() { clear(); }

MsgString513::~MsgString513() {}

u32 MsgString513::capacity() { return 0x201; }

u8 *MsgString513::data() { return text; }

extern "C" BOOL String_LoadByIndexB(MsgString *buf, const char *name, u32 key) {
    u8 k = key;
    return String_Load(buf, &k, name);
}

EncodedString512::EncodedString512() {}

EncodedString512::~EncodedString512() {}

u32 EncodedString512::capacity() { return 0x200; }

u8 *EncodedString512::data() { return text; }

extern "C" void MailCheck_LoadWordList() {
    MsgString513 src;
    EncodedString512 dst;
    s32 cnt = 0;
    u8 *out = sMailCheckWords;
    s32 i = 0;
    s32 z1 = 0, z2 = 0, z0 = 0;
    u8 *p;
    s32 j, n;
    for (; i < 0x1a; i++) {
        String_LoadByIndexB(&src, "st_mailcheck", i);
        dst.fromMsgString(&src);
        p = dst.text;
        while (*p != 0) {
            n = Text_GetLineEnd(p, 3, z0);
            if (n != 0) {
                if (cnt < 0x2fe) {
                    for (j = z1; j < n; j++) {
                        if (p[j] == 0x8d) p[j] = 0xb1;
                        out[j] = p[j];
                    }
                    for (; j < 3; j++) out[j] = z2;
                    out += 3;
                }
                cnt++;
            }
            p += n + 1;
        }
        sMailCheckWordEnds[i] = cnt;
    }
}

extern "C" s32 MailCheck_GradeLetter(LetterView *self) {
    u8 buf[0x80];
    s32 cnt, matched, n, i, prev, isSep;
    u8 *p;
    Mem_Copy(self->body, buf, 0x80);
    cnt = 0;
    matched = 0;
    n = Text_GetLength(buf, 0x80);
    for (i = 0; i < 0xc0; i++) sMailCheckWordUses[i] = 0;
    for (i = 0; i < n; i++) {
        if (buf[i] >= 1 && buf[i] <= 0x1a) buf[i] += 0x1a;
    }
    prev = 1;
    for (i = 0; i < n; i++) {
        p = buf + i;
        isSep = MailCheck_IsSeparator(buf[i]);
        if (prev == 1 && isSep == 0) {
            cnt++;
            if (MailCheck_MatchWord(p, n - i)) matched++;
        }
        prev = isSep;
    }
    if (cnt >= 3) {
        if (((cnt + 3) >> 2) <= matched) return 2;
    }
    if (cnt >= 2) return 1;
    return 0;
}

extern "C" s32 Letter_GetBodyLength(LetterView *self) {
    return Text_GetLength(self->body, 0x80);
}

extern "C" BOOL MailCheck_IsSeparator(u32 c) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (c == sMailCheckSeparators[i]) return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MailCheck_MatchWord(u8 *p, s32 n) {
    u32 c = p[0];
    s32 idx;
    s32 lo, hi, k, off;
    if (c >= 0x1b && c <= 0x34) {
        idx = c - 0x1b;
    } else {
        return FALSE;
    }
    if (idx > 0) lo = sMailCheckWordEnds[idx - 1]; else lo = 0;
    hi = sMailCheckWordEnds[idx];
    k = lo;
    off = lo * 3;
    for (; k < hi; off += 3, k++) {
        if (MailCheck_MatchWordAt(p, n, off)) {
            s32 w = k >> 2;
            s32 sh, m, v;
            k &= 3;
            sh = k * 2;
            m = 3 << sh;
            v = (sMailCheckWordUses[w] & m) >> sh;
            if (v >= 2) return FALSE;
            sMailCheckWordUses[w] &= ~m;
            sMailCheckWordUses[w] |= (v + 1) << sh;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL MailCheck_MatchWordAt(u8 *p, s32 n, s32 off) {
    s32 i;
    u8 *t = sMailCheckWords + off;
    for (i = 0; i < 3; i++) {
        if (i >= n) {
            u32 c = t[i];
            if (c == 0x85 || c == 0) return TRUE;
            return FALSE;
        }
        u32 a = t[i];
        u32 b = p[i];
        if (b != a) {
            if (a == 0x85 || a == 0) {
                if (b == 0x86 || b == 0) return TRUE;
            }
            return FALSE;
        }
        if (b == 0x85) return TRUE;
    }
    return TRUE;
}

extern const u8 sMailCheckSeparators[8] = {0x85, 0x86, 0x87, 0x9b, 0x94, 0x92, 0, 0};
u8 sMailCheckWords[0x8fc];
s16 sMailCheckWordEnds[0x1a];
u8 sMailCheckWordUses[0xc0];
