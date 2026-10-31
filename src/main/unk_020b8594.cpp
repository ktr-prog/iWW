#include "types.h"
#include "sys/PrioListNode.h"
#include "gfx/BgTransfer.h"
#include "gfx/TexTransfer.h"
#include "gfx/VramTask.h"
#include "gfx/MatTexVramTask.h"
#include "gfx/G3dResAccess.h"
#include "gfx/G3dMatData.h"
#include "proto/autoload_2/unk_02111ccc.h"
#include "proto/autoload_2/unk_0211220c.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020b8594.h"

extern "C" {
void DC_FlushRange(void *p, u32 x);
void NNS_G3dTexLoad(void *p, u32 x);
void NNS_G3dPlttLoad(void *p, u32 x);
void GX_LoadTexPltt(void *a, u32 b, u32 c);
void GX_LoadTex(void *a, u32 b, u32 c);
}


extern "C" {
u8 BgTransfer_GetPaletteRangeCost(BgTransfer *p);
u8 BgTransfer_GetPaletteCost(BgTransfer *p);
u8 BgTransfer_GetScreenCost(BgTransfer *p);
u8 TexTransfer_GetPlttCost(TexTransfer *p);
}


extern "C" {
void VramQueue2d_Dequeue(VramTask *p);
BOOL VramQueue2d_Enqueue(VramTask *p);
}


class TexVramTask : public VramTask {
public:
    TexTransfer xfer;

    TexVramTask();
    virtual BOOL execute();
    BOOL requestMatTex(void *a, u32 b, void *c);
    void cancel(void);
    void prepare(void);
    BOOL requestTexResource(u32 *a, u8 b);
    BOOL requestPltt(void *src, u32 dst, u32 size, u8 prio);
    BOOL requestTex(void *src, u32 dst, u32 size, u8 prio);
    void clear(void);
};

class BgVramTask : public VramTask {
public:
    BgTransfer xfer;

    BgVramTask();
    virtual BOOL execute();
    virtual void clear();
    BOOL requestPaletteRange(void *a, u8 b, u32 c, u8 d);
    BOOL requestPalette(void *a, u8 b, u32 c);
    BOOL requestScreen(void *a, u8 b, u32 c, u32 d);
    BOOL requestChars(void *a, u8 b, u32 c, u32 d, u32 e);
    void prepare(void);
    void cancel(void);
};

class BgVramTaskPair : public BgVramTask {
public:
    BgTransfer xfer2;

    BgVramTaskPair();
    virtual BOOL execute();
    virtual void clear();
    BOOL requestCharsAndPalette(void *a, u8 b, u32 c, u32 d, u32 e, void *f, u8 g);
    BOOL requestCharPair(void *a, void *b, u8 c, u32 d, u32 e, u32 f, u32 g);
};

void VramTask::resetState(void) {
    state = 0;
    kind = 0xa;
    cost = 1;
}

void TexTransfer::clear(void) {
    dstAddr = 0;
    src = 0;
    size = 0;
}

void TexTransfer::set(u32 a, void *b, u32 c) {
    dstAddr = a;
    src = b;
    size = c;
}

void TexTransfer::loadTex(void) {
    DC_FlushRange(src, size);
    GX_BeginLoadTex();
    GX_LoadTex(src, dstAddr, size);
    GX_EndLoadTex();
}

void TexTransfer::loadTexPltt(void) {
    DC_FlushRange(src, size);
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(src, dstAddr, size);
    GX_EndLoadTexPltt();
}

void TexTransfer::loadTexResource(void) {
    u32 *p = (u32 *)src;
    DC_FlushRange(p, p[1]);
    NNS_G3dTexLoad(p, 1);
    NNS_G3dPlttLoad(p, 1);
}

u8 TexTransfer::getTexCost(void) {
    u8 t = size >> 11;
    return t + 1;
}

extern "C" u8 TexTransfer_GetPlttCost(TexTransfer *p) {
    return 1;
}

u8 TexTransfer::getResCost(void) {
    u8 t = size >> 11;
    return t + 1;
}

void BgTransfer::clear(void) {
    buf = 0;
    layer = 0xff;
    loadArg0 = 0;
    loadArg1 = 0;
    loadArg2 = 0;
}

void BgTransfer::setChars(void *a, u8 b, u32 c, u32 d, u32 e) {
    buf = a;
    layer = b;
    loadArg0 = c;
    loadArg1 = d;
    loadArg2 = e;
}

void BgTransfer::loadChars(void) {
    Gfx2d_LoadCharRange((u8 *)buf, layer, loadArg0, loadArg1, loadArg2);
}

u8 BgTransfer::getCharCost(void) {
    return ((loadArg2 - loadArg1) + 0x3f) >> 6;
}

void BgTransfer::setScreen(void *a, u8 b, u32 c, u32 d) {
    buf = a;
    layer = b;
    loadArg0 = c;
    loadArg1 = d;
}

void BgTransfer::loadScreen(void) {
    Gfx2d_LoadScreen((u8 *)buf, layer, loadArg0, loadArg1);
}

extern "C" u8 BgTransfer_GetScreenCost(BgTransfer *p) {
    return 1;
}

void BgTransfer::setPalette(void *a, u8 b, u32 c) {
    buf = a;
    layer = b;
    loadArg0 = c;
}

void BgTransfer::loadPalette(void) {
    u32 t = (u8)loadArg0;
    Gfx2d_LoadPaletteRange((u8 *)buf, layer, t, t, t);
}

extern "C" u8 BgTransfer_GetPaletteCost(BgTransfer *p) {
    return 1;
}

void BgTransfer::setPaletteRange(void *a, u8 b, u32 c, u8 d) {
    buf = a;
    layer = b;
    loadArg0 = c;
    loadArg1 = d;
}

void BgTransfer::loadPaletteRange(void) {
    Gfx2d_LoadPaletteRange((u8 *)buf, layer, (u8)loadArg0, (u8)loadArg0, (u8)loadArg1);
}

extern "C" u8 BgTransfer_GetPaletteRangeCost(BgTransfer *p) {
    return 1;
}

TexVramTask::TexVramTask() {
    xfer.clear();
}

void TexVramTask::clear(void) {
    resetState();
    xfer.clear();
}

BOOL TexVramTask::execute() {
    switch (kind) {
    case 0:
        xfer.loadTexResource();
        break;
    case 1:
        xfer.loadTex();
        break;
    case 2:
        xfer.loadTexPltt();
        break;
    }
    return TRUE;
}

BOOL TexVramTask::requestTex(void *a, u32 b, u32 c, u8 d) {
    prepare();
    kind = 1;
    xfer.set(b, a, c);
    cost = xfer.getTexCost();
    priority = d;
    if (enqueueTex()) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BOOL TexVramTask::requestPltt(void *a, u32 b, u32 c, u8 d) {
    prepare();
    kind = 2;
    xfer.set(b, a, c);
    cost = TexTransfer_GetPlttCost(&xfer);
    priority = d;
    if (enqueueTex()) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BOOL TexVramTask::requestTexResource(u32 *a, u8 b) {
    prepare();
    kind = 0;
    xfer.set(0, a, a[1]);
    cost = xfer.getResCost();
    priority = b;
    if (enqueueTex()) {
        return TRUE;
    }
    clear();
    return FALSE;
}

void TexVramTask::prepare(void) {
    cancel();
    state = 1;
}

void TexVramTask::cancel(void) {
    dequeueTex();
    clear();
}

BOOL TexVramTask::requestMatTex(void *a, u32 b, void *c) {
    u8 *base = (u8 *)a + *(u32 *)((u8 *)a + 8);
    u8 *tbl = base + 4;
    u16 off = *(u16 *)(base + 0xa);
    u8 *ent = tbl + off;
    ent += *(u16 *)ent * b;
    G3dMatData *rec = reinterpret_cast<G3dMatData *>(base + *(u32 *)(ent + 4));
    u32 v1 = rec->getTexSize();
    u32 v2 = rec->getTexAddr();
    return requestTex(c, v2, v1, 2);
}

MatTexVramTask::MatTexVramTask() {
    texXfer.clear();
    plttXfer.clear();
}

void MatTexVramTask::clear(void) {
    texXfer.clear();
    plttXfer.clear();
}

void MatTexVramTask::cancel(void) {
    dequeueTex();
    clear();
}

BOOL MatTexVramTask::execute() {
    if (kind == 3) {
        texXfer.loadTex();
        plttXfer.loadTexPltt();
    }
    return TRUE;
}

void MatTexVramTask::prepare(void) {
    cancel();
    state = 1;
}

BOOL MatTexVramTask::request(void *a, const char *b, void *c, u32 d, u32 e) {
    prepare();
    u8 *base = (u8 *)a + *(u32 *)((u8 *)a + 8);
    u32 idx = ((G3dResAccess *)(a))->findMatIdx(b);
    u8 *tbl = base + 4;
    u16 off = *(u16 *)(base + 0xa);
    u8 *ent = tbl + off;
    ent += *(u16 *)ent * idx;
    G3dMatData *rec = reinterpret_cast<G3dMatData *>(base + *(u32 *)(ent + 4));
    void *v1 = ((G3dResAccess *)c)->getTexData(d);
    void *v2 = ((G3dResAccess *)c)->getPlttData(e);
    u32 v3 = rec->getTexSize();
    u32 v4 = ((G3dResAccess *)(c))->getPlttSize(e);
    kind = 3;
    texXfer.set(rec->getTexAddr(), v1, v3);
    plttXfer.set(rec->getPlttAddr(), v2, v4);
    cost = texXfer.getTexCost() + TexTransfer_GetPlttCost(&plttXfer);
    priority = 0;
    if (enqueueTex()) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BgVramTask::BgVramTask() {
    xfer.clear();
}

void BgVramTask::clear() {
    resetState();
    xfer.clear();
}

void BgVramTask::cancel(void) {
    VramQueue2d_Dequeue(this);
    clear();
}

BOOL BgVramTask::execute() {
    switch (kind) {
    case 4:
        xfer.loadChars();
        break;
    case 5:
        xfer.loadScreen();
        break;
    case 6:
        xfer.loadPalette();
        break;
    case 7:
        xfer.loadPaletteRange();
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

void BgVramTask::prepare(void) {
    cancel();
    state = 1;
}

BOOL BgVramTask::requestChars(void *a, u8 b, u32 c, u32 d, u32 e) {
    prepare();
    kind = 4;
    xfer.setChars(a, b, c, d, e);
    cost = xfer.getCharCost();
    priority = 4;
    if (VramQueue2d_Enqueue(this)) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BOOL BgVramTask::requestScreen(void *a, u8 b, u32 c, u32 d) {
    prepare();
    kind = 5;
    xfer.setScreen(a, b, c, d);
    cost = BgTransfer_GetScreenCost(&xfer);
    priority = 4;
    if (VramQueue2d_Enqueue(this)) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BOOL BgVramTask::requestPalette(void *a, u8 b, u32 c) {
    prepare();
    kind = 6;
    xfer.setPalette(a, b, c);
    cost = BgTransfer_GetPaletteCost(&xfer);
    priority = 4;
    if (VramQueue2d_Enqueue(this)) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BOOL BgVramTask::requestPaletteRange(void *a, u8 b, u32 c, u8 d) {
    prepare();
    kind = 7;
    xfer.setPaletteRange(a, b, c, d);
    cost = BgTransfer_GetPaletteRangeCost(&xfer);
    priority = 4;
    if (VramQueue2d_Enqueue(this)) {
        return TRUE;
    }
    clear();
    return FALSE;
}

BgVramTaskPair::BgVramTaskPair() {
    xfer2.clear();
}

void BgVramTaskPair::clear() {
    BgVramTask::clear();
    xfer2.clear();
}

BOOL BgVramTaskPair::execute() {
    if (BgVramTask::execute()) {
        return TRUE;
    }
    switch (kind) {
    case 8:
        xfer.loadChars();
        xfer2.loadChars();
        break;
    case 9:
        xfer.loadChars();
        xfer2.loadPalette();
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

