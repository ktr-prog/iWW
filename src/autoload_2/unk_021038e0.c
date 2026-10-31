typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef int BOOL;
#define NULL 0

typedef struct ResDict { u8 revision; u8 numEntry; u16 sizeDictBlk; u16 dummy_; u16 ofsEntry; } ResDict;
typedef struct ResDictEntryHeader { u16 sizeUnit; u16 ofsName; u8 data[4]; } ResDictEntryHeader;
typedef struct ResMat { u16 ofsDictTexToMatList; u16 ofsDictPlttToMatList; ResDict dict; } ResMat;
typedef struct ResDictMatData { u32 offset; } ResDictMatData;
typedef struct ResMatData {
    u8 pad[0x14];
    u32 texImageParam;
    u32 pad18;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth, origHeight;
    s32 magW, magH;
} ResMatData;
typedef struct BindData { u16 offset; u8 numIdx; u8 flag; } BindData;
typedef struct ResDictTexData { u32 texImageParam; u32 extraParam; } ResDictTexData;
typedef struct ResDictPlttData { u16 offset; u16 flag; } ResDictPlttData;
typedef struct ResTex {
    u8 pad0[8];
    u32 texKey;
    u8 pad0c[0xc];
    u32 tex4x4Key;
    u8 pad1c[0x10];
    u32 plttKey;
} ResTex;
extern s32 FX_Div(s32, s32);

static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return (void *)&hdr->data[hdr->sizeUnit * idx];
}
static inline ResMatData *GetMatDataByIdx(const ResMat *pResMat, u32 idx)
{
    ResDictMatData *pDictData = (ResDictMatData *)GetResDataByIdx(&pResMat->dict, idx);
    return (ResMatData *)((u8 *)pResMat + pDictData->offset);
}
#define KeyAddr(k) (((k) & 0xffff) << 3)


void bindMdlPltt_Internal_(ResMat *pMat, BindData *pBindData, const ResTex *pTex, const ResDictPlttData *pPlttData)
{
    u8 *base = (u8 *)pMat + pBindData->offset;
    u16 plttBase = pPlttData->offset;
    u16 vramOffset = (u16)(KeyAddr(pTex->plttKey) >> 3);
    u32 j;
    if (!(pPlttData->flag & 1)) {
        plttBase >>= 1;
        vramOffset >>= 1;
    }
    for (j = 0; j < pBindData->numIdx; ++j) {
        ResMatData *matData = GetMatDataByIdx(pMat, *(base + j));
        matData->texPlttBase = (u16)(plttBase + vramOffset);
    }
    pBindData->flag |= 1;
}
