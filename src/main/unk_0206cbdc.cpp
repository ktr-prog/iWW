#include "uptr.h"
#include "types.h"
#include "text/Unk_02050288.h"
#include "sys/StackPad.h"
#include "item/LetterView.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"

extern "C" {
TextLabel *MsgTextLabel_CreateVram(u32 a, s32 b, s32 c);
void MsgTextLabel_Destroy(TextLabel *obj);
s32 EncodedString_SetRaw(void *buf, const void *src, s32 len);
}




class MsgString;



#include "talk/EncodedString40.h"
#include "ui/LetterTextLine.h"
#include "ui/LetterLayout.h"
#include "ui/LetterRenderer.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206cbdc.h"
#include "proto/ov002/unk_ov002_022025cc.h"







void LetterRenderer::setLayer(s32 v) {
    s32 i;
    greetingLine.setTarget(0x75, v);
    signatureLine.setTarget(0x180, v);
    for (i = 0; i < 4; i++) {
        bodyLines[i].setTarget(i * 0x28 + 0x9d, v);
    }
    recipientNameLength = 0;
}

void LetterRenderer::release() {
    freeAllLabels();
}

void LetterRenderer::redraw() {
    freeAllLabels();
    redrawAll();
}

void LetterRenderer::show(LetterView *src, u32 a, u32 b, s32 c) {
    Gfx2d_HideLayer(b);
    Gfx2d_SetLayerPriority(b, 1);
    Gfx2d_SetLayerControl(b, 0, 0, 0);
    Menu_LoadPaperBg(Letter_GetPaper(src), b);
    Gfx2d_SetLayerOffset(b, 0, 0);
    Gfx2d_HideLayer(a);
    Gfx2d_SetLayerPriority(a, c);
    Gfx2d_SetLayerControl(a, 0, 0, 0);
    loadRecipientName(src);
    setGreeting(src, 0);
    setBody(src->body, 0);
    setSignature(src->signature);
    loadLetterScreen(a);
    redraw();
    Gfx2d_SetLayerOffset(a, 0, 0);
}

s32 LetterRenderer::getRecipientNameLength() {
    return recipientNameLength;
}

void LetterRenderer::loadRecipientName(void *src) {
    Mem_Clear(recipientName, 0x28);
    Letter_GetRecipientNameBytes((LetterView *)src, recipientName);
    recipientNameLength = Text_GetLength(recipientName, 0x28);
    recipientNameWidth = Text_MeasureWidth(recipientName, 0x28);
}

void LetterRenderer::setGreeting(LetterView *src, u8 *out) {
    u8 tmp[0x28];
    s32 n, j, k;
    greetingLine.clearText();
    if (out == 0) {
        out = tmp;
    }
    n = 0;
    j = n;
    while (n < src->namePos) {
        out[n] = src->greeting[j];
        n++;
        j++;
    }
    k = 0;
    while (k < recipientNameLength) {
        out[n] = recipientName[k];
        n++;
        k++;
    }
    k = 0;
    while (n < 0x28) {
        if (j < 0x18) {
            out[n] = src->greeting[j];
        } else {
            out[n] = k;
        }
        n++;
        j++;
    }
    if (recipientNameLength > 0) {
        greetingLine.setNameHighlight(src->namePos, recipientNameLength);
    }
    EncodedString40 buf;
    EncodedString_SetRaw(&buf, out, 0x28);
    greetingLine.setText(&buf);
}

void LetterRenderer::setBody(u8 *src, BOOL flag) {
    LetterLayout_SplitBody(this, src, bodyLineStarts, &bodyLineCount);
    EncodedString40 buf;
    u8 z[0x28];
    s32 i;
    s32 zero;
    i = 0;
    z[0] = 0;
    zero = 0;
    for (; i < 4; i++) {
        s32 diff = bodyLineStarts[i + 1] - bodyLineStarts[i];
        LetterTextLine *cell = &bodyLines[i];
        cell->clearText();
        if (diff != 0) {
            EncodedString_SetRaw(&buf, src + bodyLineStarts[i], diff);
            if (flag) {
                cell->setTextWithMarks(&buf, i == bodyLineCount ? 1 : zero);
            } else {
                cell->setText(&buf);
            }
        } else if (flag && i == bodyLineCount) {
            EncodedString_SetRaw(&buf, z, 1);
            cell->setTextWithMarks(&buf, 1);
        } else {
            cell->clearText();
        }
    }
}

void LetterRenderer::setSignature(u8 *data) {
    EncodedString40 buf;
    signatureLine.clearText();
    EncodedString_SetRaw(&buf, data, 0x20);
    signatureLine.setText(&buf);
}

void LetterRenderer::highlightGreeting(u32 a, u32 b, u32 c) {
    StackPad4 pad;
    greetingLine.setHighlight(a, b, c);
}

void LetterLayout::highlightBodyRange(u32 a, u32 b, u32 c) {
    s32 i;
    u32 pos, cnt, end, len;
    pos = 0;
    for (i = 0; i < 4; i++) {
        len = bodyLineStarts[i + 1] - bodyLineStarts[i];
        if (len == 0) break;
        if (a >= pos) {
            end = pos + len;
            if (a < end) {
                if (end > a + b) cnt = b;
                else cnt = len - (a - pos);
                bodyLines[i].setHighlight(a - pos, cnt, c);
                a = (u8)end;
                b -= cnt;
                if (b == 0) break;
            }
        }
        pos += len;
    }
}

extern "C" void LetterLayout_HighlightSignature(LetterLayout *self, u32 a, u32 b, u32 c) {
    self->signatureLine.setHighlight(a, b, c);
}


extern "C" s32 LetterLayout_SplitBody(void *unused, u8 *a, s32 *b, s32 *c) {
    return Text_SplitLines(a, b, c, 0x80, 0x28, 0x96, 4);
}

extern "C" s32 Text_SplitLines(u8 *str, s32 *starts, s32 *cnt, s32 len, s32 maxw, s32 pxw, s32 maxLines) {
    s32 pos = 0;
    s32 w = maxw;
    s32 i;
    s32 outLen;
    *cnt = 0;
    for (i = 0; i < maxLines; i++) {
        s32 rem = len - pos;
        s32 r;
        if (w > rem) w = rem;
        r = Text_FitToWidth(str + pos, w, pxw, &outLen, 1);
        starts[i] = pos;
        pos += outLen;
        if (r != 0) {
            if (r == 3 && i == maxLines - 1) {
                starts[i + 1] = pos;
                return 0;
            }
            (*cnt)++;
        }
    }
    starts[i] = pos;
    if (pos == len || str[pos] == 0) return 1;
    return 0;
}

u8 *LetterLayout::getBodyLineStarts() { return (u8 *)bodyLineStarts; }
s32 LetterLayout::getBodyLineCount() { return bodyLineCount; }

s32 LetterLayout::getBodyLineOfPos(s32 v) {
    s32 n, i;
    for (i = 0, n = bodyLineCount; i < n; i++) {
        if (v < bodyLineStarts[i + 1]) return i;
    }
    if (n >= 4) n = 3;
    return n;
}

void LetterLayout::freeAllLabels() {
    s32 i;
    greetingLine.freeLabel();
    signatureLine.freeLabel();
    for (i = 0; i < 4; i++) {
        bodyLines[i].freeLabel();
    }
}

void LetterLayout::redrawAll() {
    s32 i;
    greetingLine.redrawIfDirty(0);
    signatureLine.redrawIfDirty(1);
    for (i = 0; i < 4; i++) {
        bodyLines[i].redrawIfDirty(0);
    }
}

u32 EncodedString40::capacity() { return 0x28; }
u8 *EncodedString40::data() { return text; }

LetterTextLine::LetterTextLine() {
    clear();
    textLabel = NULL;
    charBase = 0;
    highlightStart = 0;
    highlightLength = 0;
    nameHighlightStart = 0;
    nameHighlightLength = 0;
}

LetterTextLine::~LetterTextLine() { freeLabel(); }

u32 LetterTextLine::capacity() { return 0x29; }

void LetterTextLine::setTarget(u16 v, u32 x) {
    charBase = v;
    isDirty = 0;
    isSubScreen = Gfx2d_IsMainScreenLayer(x) == 0 ? 1 : 0;
    bgIndex = Gfx2d_GetLayerBgIndex(x);
}

u8 *LetterTextLine::data() { return text; }

void LetterTextLine::freeLabel() {
    if (textLabel != NULL) {
        MsgTextLabel_Destroy(textLabel);
        textLabel = NULL;
    }
}

void LetterTextLine::createLabel() {
    if (textLabel == NULL) {
        textLabel = MsgTextLabel_CreateVram(charBase, 0x14, 2);
        if (textLabel != NULL) {
            u8 a, b;
            textLabel->vramLoader = bgIndex;
            if (isSubScreen) textLabel->copyMode = 1;
            else textLabel->copyMode = 2;
            textLabel->rowStride1K = 0;
            textLabel->bgColor = 0;
            textLabel->fgColor = 0xf;
            if (highlightAlt) {
                a = 0xb;
                b = 0;
            } else {
                a = 0xe;
                b = 0xd;
            }
            if (highlightLength) {
                if (nameHighlightLength) {
                    textLabel->setHighlights(a, b, highlightStart, highlightLength, 0xc, 0, nameHighlightStart, nameHighlightLength);
                } else {
                    textLabel->setHighlight(a, b, highlightStart, highlightLength);
                }
            } else if (nameHighlightLength) {
                textLabel->setHighlight(0xc, 0, nameHighlightStart, nameHighlightLength);
            }
        }
    }
}

void LetterTextLine::redrawIfDirty(BOOL b) {
    if (isDirty) {
        createLabel();
        if (textLabel) {
            TextLabel *t;
            isDirty = 0;
            t = textLabel;
            t->textStart = data();
            if (b) textLabel->alignRight();
            textLabel->requestRedraw();
        }
    }
}

void LetterTextLine::setText(EncodedString *src) {
    fromEncoded(src, 0, 0);
    isDirty = 1;
}

void LetterTextLine::setTextWithMarks(EncodedString *src, BOOL b) {
    fromEncoded(src, 1, b);
    isDirty = 1;
}

void LetterTextLine::clearText() {
    clear();
    highlightStart = 0;
    highlightLength = 0;
    highlightAlt = 0;
    nameHighlightStart = 0;
    nameHighlightLength = 0;
    isDirty = 1;
}

void LetterTextLine::setHighlight(u8 a, u8 b, u32 c) {
    highlightStart = a;
    highlightLength = b;
    highlightAlt = c;
}

void LetterTextLine::setNameHighlight(u8 a, u8 b) {
    nameHighlightStart = a;
    nameHighlightLength = b;
}
