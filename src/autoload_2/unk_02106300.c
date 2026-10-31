

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
#define NULL 0
typedef union ResName { char name[16]; u32 val[4]; } ResName;
typedef struct ResDictTreeNode { u8 refBit; u8 idxLeft; u8 idxRight; u8 idxEntry; } ResDictTreeNode;
typedef struct ResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    ResDictTreeNode node[1];
} ResDict;
typedef struct ResDictEntryHeader { u16 sizeUnit; u16 ofsName; u8 data[4]; } ResDictEntryHeader;

static inline const ResName *GetResNameByIdx(const ResDict *dict, u32 idx)
{
    const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    const ResName *name = (const ResName *)((u8 *)hdr + hdr->ofsName);
    return &name[idx];
}
static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return (void *)&hdr->data[hdr->sizeUnit * idx];
}

void *NNS_G3dGetResDataByName(const ResDict *dict, const ResName *name)
{
    if (dict->numEntry < 16) {
        u32 i;
        u32 v0 = name->val[0];
        u32 v1 = name->val[1];
        u32 v2 = name->val[2];
        u32 v3 = name->val[3];
        for (i = 0; i < dict->numEntry; ++i) {
            const ResName *n = GetResNameByIdx(dict, i);
            if (n->val[0] == v0 && n->val[1] == v1 && n->val[2] == v2 && n->val[3] == v3) {
                return GetResDataByIdx(dict, i);
            }
        }
    } else {
        const ResDictTreeNode *x = &dict->node[0];
        const ResDictTreeNode *p;
        const ResDictTreeNode *q;
        if (x->idxLeft != 0) {
            p = x;
            q = x + x->idxLeft;
            while (p->refBit > q->refBit) {
                p = q;
                q = x + *(&q->idxLeft + ((name->val[q->refBit >> 5] >> (q->refBit & 31)) & 1));
            }
            {
                const ResName *n = GetResNameByIdx(dict, q->idxEntry);
                if (n->val[0] == name->val[0] && n->val[1] == name->val[1] &&
                    n->val[2] == name->val[2] && n->val[3] == name->val[3]) {
                    return GetResDataByIdx(dict, q->idxEntry);
                }
            }
        }
    }
    return NULL;
}

int NNS_G3dGetResDictIdxByName(const ResDict *dict, const ResName *name)
{
    if (dict->numEntry < 16) {
        u32 i;
        u32 v0 = name->val[0];
        u32 v1 = name->val[1];
        u32 v2 = name->val[2];
        u32 v3 = name->val[3];
        for (i = 0; i < dict->numEntry; ++i) {
            const ResName *n = GetResNameByIdx(dict, i);
            if (n->val[0] == v0 && n->val[1] == v1 && n->val[2] == v2 && n->val[3] == v3) {
                return (int)i;
            }
        }
    } else {
        const ResDictTreeNode *x = &dict->node[0];
        const ResDictTreeNode *p;
        const ResDictTreeNode *q;
        if (x->idxLeft != 0) {
            p = x;
            q = x + x->idxLeft;
            while (p->refBit > q->refBit) {
                p = q;
                q = x + *(&q->idxLeft + ((name->val[q->refBit >> 5] >> (q->refBit & 31)) & 1));
            }
            {
                const ResName *n = GetResNameByIdx(dict, q->idxEntry);
                if (n->val[0] == name->val[0] && n->val[1] == name->val[1] &&
                    n->val[2] == name->val[2] && n->val[3] == name->val[3]) {
                    return q->idxEntry;
                }
            }
        }
    }
    return -1;
}
