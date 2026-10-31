#include "types.h"
#include "gfx/VecFx32.h"
#include "sys/TreeNode.h"
#include "proto/itcm/unk_01ffcfc0.h"



extern "C" {
}

extern "C" void Vec_Add(VecFx32 *out, const VecFx32 *a, const VecFx32 *b) {
    s32 ax = a->x, bx = b->x, az = a->z, bz = b->z, ay = a->y, by = b->y;
    out->x = ax + bx;
    out->y = ay + by;
    out->z = az + bz;
}

extern "C" s64 Vec_DistSq(VecFx32 *a, VecFx32 *b) {
    s64 s = (s64)(a->x - b->x) * (a->x - b->x);
    s += (s64)(a->y - b->y) * (a->y - b->y);
    s += (s64)(a->z - b->z) * (a->z - b->z);
    return s >> 12;
}

extern "C" TreeNode *TreeNode_GetNextPreOrder(TreeNode *n) {
    TreeNode *r = n->child;
    if (r == 0) {
        r = TreeNode_GetNextSkipChildren(n);
    }
    return r;
}

extern "C" TreeNode *TreeNode_GetNextSkipChildren(TreeNode *n) {
    if (n->next != 0) {
        return n->next;
    }
    for (TreeNode *p = n->parent; p != 0; p = p->parent) {
        if (p->next != 0) {
            return p->next;
        }
    }
    return 0;
}

