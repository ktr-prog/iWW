#ifndef GFX_MODEL_H
#define GFX_MODEL_H

#include "types.h"
#include "gfx/Mtx43.h"
#include "uptr.h"
#include "nnsys/g3d_rt.h"

struct NNSG3dResMdl;
struct NNSG3dResTex;
struct NNSG3dAnmObj;
struct NNSG3dRS;
class TexVramSlot;

class ModelBaseDecl {
public:
    ModelBaseDecl() {}
    virtual ~ModelBaseDecl() {}
};

class Model : public ModelBaseDecl {
public:
    Model();
    virtual ~Model();
    void setAlpha(u32 v);
    void setPolygonId(u32 v);
    void setInitCallback(void (*fn)(NNSG3dRS *), void *user);
    void setCallback(void (*fn)(NNSG3dRS *), s32 cmd, s32 timing, void *user, u8 *addr);
    void *getRenderObj();
    void draw();
    void applyTransform(s32 *p);
    void drawNoGeCmd();
    void drawScaled(s32 *p);
    void drawShapesDirect(s32 *p);
    BOOL clearResource();
    BOOL setResource(NNSG3dResMdl *a, NNSG3dResTex *b);
    BOOL setResourceAndBind(NNSG3dResMdl *a, NNSG3dResTex *b);
    void initRenderObj();
    void reset();

    /* 0x04 */ u16 modelFlags;
    /* 0x06 */ u16 unk_06;
    union {
        u8 unk_08[sizeof(G3dRenderObj)];
        G3dRenderObj ro;
        struct {
            u32 renderObj;
            u8 *renderResMdl;
            void *pad_10[2];
            NNSG3dAnmObj *renderAnmJnt;
            sptr unk_1c;
            NNSG3dAnmObj *renderAnmVis;
            void *pad_24[2];
            u8 pad_24b[4];
            void *pad_28;
            void *renderUserPtr;
            u8 *pad_30;
            void *renderJntRecord;
        };
    };
    /* 0x5c */ NNSG3dResMdl *resMdl;
    /* 0x60 */ NNSG3dResTex *resTex;
    union {
        /* 0x64 */ Mtx43 mtx;
        struct {
            /* 0x64 */ u8 unk_64[0x24];
            /* 0x88 */ u8 baseTrans[0xc];
        };
    };
    /* 0x94 */ TexVramSlot *texVramSlot;
};

#define MODEL_AT_MTX(p) (((Model *)(p))->mtx)

#endif
