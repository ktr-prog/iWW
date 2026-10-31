#ifndef SYS_TREENODE_H
#define SYS_TREENODE_H

#include "types.h"

class ProcBase;

struct TreeNode {
    /* 0x00 */ TreeNode *parent;
    /* 0x04 */ TreeNode *child;
    /* 0x08 */ TreeNode *prev;
    /* 0x0c */ TreeNode *next;
    /* 0x10 */ ProcBase *owner;
};

#endif
