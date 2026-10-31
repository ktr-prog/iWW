#include "types.h"
#include "sys/PrioListNode.h"
#include "gfx/TexVramSlot.h"
#include "gfx/TexTransfer.h"
#include "gfx/VramTask.h"
#include "gfx/TexVramTask.h"
#include "gfx/ModelResource.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205500c.h"
#include "proto/main/unk_02063f3c.h"


extern "C" {
void *NNS_G3dGetMdlSet(void *h);
void *NNS_G3dGetTex(void *h);
void NNS_G3dBindMdlTex(void *a, void *b);
void NNS_G3dBindMdlPltt(void *a, void *b);
void *Gfx3d_CopyModel(void *a, void *b);
void *Gfx3d_CopyTex(void *a, void *b);
}


static inline u8 *Unk_02054b70_Off(u8 *p) {
    return p + *(u32 *)(p + *(u16 *)(p + 0xe) + 0xc);
}

static inline BOOL Unk_02055014_IsTwo(u8 v) {
    return v == 2 ? TRUE : FALSE;
}

void TexVramSlot::setKeys(u32 a, u32 b, u32 c) {
    texKeyBase = a;
    tex4x4KeyBase = b;
    plttKeyBase = c;
    unk_11 = 1;
}

ModelResource::ModelResource() {
    fileData = 0;
    fileHeap = NULL;
    model = NULL;
    texture = NULL;
    loadState = 0;
    unk_31 = 0;
}

ModelResource::~ModelResource() {}

void ModelResource::release(void) {
    if (fileData != 0) {
        Heap_Free(fileHeap, fileData);
    }
    fileData = 0;
    fileHeap = NULL;
    model = NULL;
    texture = NULL;
    loadState = 0;
    texVramTask.cancel();
}

u32 ModelResource::loadModel(void *res, TexVramSlot *b, void *tex, void *heap) {
    u32 st = loadState;
    if (st == 3) {
        return st;
    }
    Heap *h = static_cast<Heap *>(heap);
    if (h == NULL) {
        h = gCurrentHeap;
    }
    if (st == 0) {
        fileData = File_LoadAlloc((const char *)res, h, -4, 0);
        fileHeap = h;
        void *q = NNS_G3dGetTex(fileData);
        b->relocateTexture(q);
        texVramTask.requestTexResource((u32 *)q, 1);
        loadState = 1;
        return loadState;
    }
    if (st == 1) {
        if (!Unk_02055014_IsTwo(texVramTask.state)) {
            return st;
        }
        loadState = 2;
    }
    if (loadState == 2) {
        u8 *p = Unk_02054b70_Off((u8 *)NNS_G3dGetMdlSet(fileData));
        model = Gfx3d_CopyModel(p, tex);
        void *q = NNS_G3dGetTex(fileData);
        NNS_G3dBindMdlTex(model, q);
        NNS_G3dBindMdlPltt(model, q);
        Heap_Free(fileHeap, fileData);
        fileHeap = NULL;
        fileData = 0;
        loadState = 3;
    }
    return loadState;
}

u32 ModelResource::loadTexture(void *a, TexVramSlot *b, void *c) {
    u32 st = loadState;
    if (st == 3) {
        return st;
    }
    if (st == 0) {
        b->relocateTexture(a);
        texVramTask.requestTexResource((u32 *)a, 1);
        loadState = 1;
        return loadState;
    }
    if (st == 1) {
        if (!Unk_02055014_IsTwo(texVramTask.state)) {
            return st;
        }
        loadState = 2;
    }
    if (loadState == 2) {
        texture = Gfx3d_CopyTex(a, c);
        loadState = 3;
    }
    return loadState;
}

void *ModelResource::getModel(void) {
    return model;
}

void *ModelResource::getTexture(void) {
    return texture;
}

