#include "types.h"
#include "gfx/VecFx32.h"
#include "text/Unk_02050288.h"
#include "gfx/Mtx43.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "ui/LabelString.h"
#include "talk/EncodedString41.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_0206f804.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_0206fc44.h"
#include "proto/main/unk_0206fde4.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"



class MsgString;




extern "C" {
BOOL EncodedString_SetRaw(EncodedString41 *buf, const void *src, s32 len);
u32 Msg_MeasureWidth(u8 *text);
TextLabel *MsgTextLabel_CreateBuffer(void *buf, s32 widthTiles, s32 heightTiles);
TextLabel *MsgTextLabel_CreateVram(u32 tileIndex, s32 widthTiles, s32 heightTiles);
}




void LabelString::setLayerColors(u32 id, u8 x, u8 y) {
    s32 t = Gfx2d_GetLayerBgIndex(id);
    if (label != NULL) {
        label->vramLoader = t;
        if (Gfx2d_IsMainScreenLayer(id) != 0) {
            label->copyMode = 2;
        } else {
            label->copyMode = 1;
        }
        if (t == 4) {
            label->rowStride1K = 1;
        } else {
            label->rowStride1K = 0;
        }
        label->bgColor = y;
        label->fgColor = x;
    }
}

void LabelString::createLabel(u32 id, u32 a, u32 b, u8 x, u8 y, s32 flag) {
    if (label != NULL) {
        destroyLabel();
    }
    label = MsgTextLabel_CreateVram(a, b, 2);
    setLayerColors(id, x, y);
    if (flag != 0) {
        label->font = (GameFontDesc *)&gFontC;
    }
}

void LabelString::createSmallLabel(u32 id, u32 a, u32 b, u8 x, u8 y, s32 flag) {
    if (label != NULL) {
        destroyLabel();
    }
    label = MsgTextLabel_CreateVram(a, b, 1);
    setLayerColors(id, x, y);
    if (flag != 0) {
        label->font = (GameFontDesc *)&gFontD;
    } else {
        label->font = (GameFontDesc *)&gFontB;
    }
}

void LabelString::createBufferLabel(void *buf, s32 widthTiles, u8 x, u8 y) {
    if (label != NULL) {
        destroyLabel();
    }
    label = MsgTextLabel_CreateBuffer(buf, widthTiles, 2);
    if (label != NULL) {
        label->bgColor = y;
        label->fgColor = x;
        label->group = 2;
    }
}

void LabelString::redrawAligned(s32 a, s32 b) {
    TextLabel *o = label;
    if (o != NULL) {
        o->textStart = data();
        if (b != 0) {
            label->underline = 1;
        } else {
            label->underline = 0;
        }
        if (a != 0) {
            label->alignCenter();
        } else {
            label->xOffset = 0;
        }
        label->requestRedraw();
    }
}

void LabelString::redrawOffset(s32 a, s32 b) {
    TextLabel *o = label;
    if (o != NULL) {
        o->textStart = data();
        if (a != 0) {
            label->alignCenter();
        } else {
            label->xOffset = 0;
        }
        label->xOffset = label->xOffset + b;
        label->requestRedraw();
    }
}

void LabelString::redrawRight() {
    TextLabel *o = label;
    if (o != NULL) {
        o->textStart = data();
        label->alignRight();
        label->requestRedraw();
    }
}

void LabelString::redrawAt(s32 v) {
    TextLabel *o = label;
    if (o != NULL) {
        o->textStart = data();
        label->xOffset = v;
        label->requestRedraw();
    }
}

u32 LabelString::getTextWidth() { return Msg_MeasureWidth(text); }

void String_Load2dMenuByRef(void *a, u8 *p) { String_Load2d((MsgString *)a, p, NULL); }

void String_Load2dMenu(void *a, u8 v) {
    u8 t = v;
    String_Load2dMenuByRef(a, &t);
}

void String_LoadByIndex(void *a, const char *c, u8 v) {
    u8 t = v;
    String_Load((MsgString *)a, &t, (const char *)c);
}

void String_FormatNumberWrapper(void *o, s32 a, s32 b, s32 c, s32 d, u8 e) { String_FormatNumber((MsgString *)o, a, b, c, d, e); }

void String_FromEncodedBytes(MsgString *dst, const void *s, s32 len) {
    EncodedString41 l;
    EncodedString_SetRaw(&l, s, len);
    dst->fromEncoded(&l, 0, 0);
}

void String_ToEncodedBytes(MsgString *a, u8 *b) {
    EncodedString41 l;
    l.fromMsgString(a);
    StrBuf_GetBytes((StrBuf *)&l, b, 0x29);
}

void String_FromEncodedBytesEx(MsgString *dst, const void *s, s32 len, BOOL a, u8 b) {
    if (a == 0) {
        b = 0;
    }
    EncodedString41 l;
    EncodedString_SetRaw(&l, s, len);
    dst->fromEncoded(&l, a, b);
}

void LabelString::setHighlight(u8 a, u8 b, u32 c, u32 d) {
    if (label != NULL) {
        label->setHighlight(a, b, c, d);
    }
}

BOOL String_EqualsEncodedBytes(MsgString *a, u8 *b, s32 len) {
    EncodedString41 l;
    l.fromMsgString(a);
    s32 n = Text_GetTrimmedLength(b, len);
    if (n != Text_GetTrimmedLength(l.text, len)) {
        return FALSE;
    }
    s32 i = 0;
    while (i < n) {
        u32 x = b[i];
        u32 y = l.text[i];
        if (x == 0x8d) {
            x = 0xb1;
        }
        if (y == 0x8d) {
            y = 0xb1;
        }
        if (x != y) {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

EncodedString41::EncodedString41() {}

EncodedString41::~EncodedString41() {}

u32 EncodedString41::capacity() { return 0x29; }

u8 *EncodedString41::data() { return text; }

static inline u32 Unk_0206fe34_Id(u32 i) {
    if (i < 0x34) {
        return i * 4 + 0x450c;
    }
    return 0x450c;
}
