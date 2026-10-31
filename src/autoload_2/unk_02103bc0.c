typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02103bc0.h"
#include "proto/autoload_2/unk_02111ccc.h"
#include "proto/autoload_2/unk_0211220c.h"
typedef struct Node { int frame, ratio; void *resAnm; void *funcAnm; struct Node *next; void *resTex; u8 prio; } Node;
#define NODE_RES_KIND(n) (*(u8 *)(n)->resAnm)
#define RO(o) ((G3dRenderObj *)(o))

typedef struct TexData {
    u32 sig;
    u32 pad4;
    u32 pltt08;
    u16 plttSize;
    u16 pad0e;
    u16 plttFlag;
    u16 pad12;
    u32 plttOfs;
    u32 pltt18;
    u16 pltt4Size;
    u16 pad1e;
    u16 pltt4Flag;
    u16 pad22;
    u32 pltt4Ofs;
    u32 pltt4Ofs2;
    u32 tex2c;
    u16 texSize;
    u16 texFlag;
    u8 pad34[4];
    u32 texOfs;
} TexData;

extern void GX_LoadTexPltt(void *, u32, u32);
extern void GX_LoadTex(void *, u32, u32);
BOOL removeLink_(Node **head, Node *n);

BOOL removeLink_(Node **head, Node *n)
{
    Node *c;
    Node *prev = *head;
    if (prev == NULL) return 0;
    if (prev == n) {
        *head = prev->next;
        n->next = NULL;
        return 1;
    }
    for (c = prev->next; c != NULL; c = c->next) {
        if (c == n) {
            prev->next = c->next;
            c->next = NULL;
            return 1;
        }
        prev = c;
    }
    return 0;
}

void NNS_G3dRenderObjRemoveAnmObj(u8 *o, Node *n)
{
    if (removeLink_((Node **)&RO(o)->anmMat, n) || removeLink_((Node **)&RO(o)->anmJnt, n) ||
        removeLink_((Node **)&RO(o)->anmVis, n)) {
        RO(o)->flag |= 0x10;
    }
}

void NNS_G3dRenderObjSetCallBack(u8 *o, void *a, u8 *b, u32 c, u32 d)
{
    RO(o)->cbFunc = a;
    RO(o)->cbCmd = c;
    RO(o)->cbTiming = d;
}

void NNS_G3dRenderObjSetInitFunc(u8 *o, void *v) { RO(o)->cbInitFunc = v; }

u32 NNS_G3dTexGetRequiredSize(TexData *o) { return o->plttSize << 3; }

u32 NNS_G3dTex4x4GetRequiredSize(TexData *o) { return o->pltt4Size << 3; }

void NNS_G3dTexSetTexKey(TexData *o, u32 a, u32 b)
{
    if (a != 0) o->pltt08 = a;
    if (b != 0) o->pltt18 = b;
}

void NNS_G3dTexLoad(TexData *o, BOOL lock)
{
    u32 size;
    u32 size4;
    if (lock) GX_BeginLoadTex();
    size = o->plttSize << 3;
    if (size != 0) {
        GX_LoadTex((u8 *)o + o->plttOfs, (o->pltt08 & 0xffff) << 3, size);
        o->plttFlag |= 1;
    }
    size4 = o->pltt4Size << 3;
    if (size4 != 0) {
        u32 a = o->pltt18 & 0xffff;
        u32 b = a << 3;
        u8 *p = (u8 *)o + o->pltt4Ofs2;
        GX_LoadTex((u8 *)o + o->pltt4Ofs, b, size4);
        GX_LoadTex(p, (((a << 3) & 0x1ffff) >> 1) + 0x20000 + ((b & 0x40000) >> 2), size4 >> 1);
        o->pltt4Flag |= 1;
    }
    if (lock) GX_EndLoadTex();
}

u32 NNS_G3dPlttGetRequiredSize(TexData *o) { return o->texSize << 3; }

void NNS_G3dPlttSetPlttKey(TexData *o, u32 v) { o->tex2c = v; }

void NNS_G3dPlttLoad(TexData *o, BOOL lock)
{
    if (lock) GX_BeginLoadTexPltt();
    GX_LoadTexPltt((u8 *)o + o->texOfs, (o->tex2c & 0xffff) << 3, o->texSize << 3);
    o->texFlag |= 1;
    if (lock) GX_EndLoadTexPltt();
}
