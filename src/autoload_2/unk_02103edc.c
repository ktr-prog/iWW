typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02103edc.h"
#include "proto/autoload_2/unk_02104000.h"

extern void MIi_CpuClear32(u32 data, void *dest, u32 size);

void NNS_G3dRenderObjInit(G3dRenderObj *o, void *resMdl)
{
    volatile u32 zero = 0;
    MIi_CpuClear32(zero, o, sizeof(G3dRenderObj));
    o->funcBlendMat = data_0213bcd4;
    o->funcBlendJnt = data_0213bcd0;
    o->funcBlendVis = data_0213bccc;
    o->resMdl = resMdl;
}

void addLink_(G3dAnmObj **head, G3dAnmObj *n)
{
    G3dAnmObj *h = *head;
    G3dAnmObj *c;
    if (h == NULL) {
        *head = n;
        return;
    }
    c = h->next;
    if (c == NULL) {
        if (h->priority > n->priority) {
            G3dAnmObj *t = n;
            while (t->next != NULL) t = t->next;
            t->next = h;
            *head = n;
        } else {
            h->next = n;
        }
        return;
    }
    while (c != NULL) {
        if (c->priority >= n->priority) {
            G3dAnmObj *t = n;
            while (t->next != NULL) t = t->next;
            h->next = n;
            t->next = c;
            return;
        }
        h = c;
        c = c->next;
    }
    h->next = n;
}

