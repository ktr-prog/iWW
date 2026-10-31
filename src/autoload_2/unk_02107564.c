

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef struct ResDict { u8 revision; u8 numEntry; u16 sizeDictBlk; u16 dummy_; u16 ofsEntry; } ResDict;
typedef struct ResDictEntryHeader { u16 sizeUnit; u16 ofsName; u8 data[4]; } ResDictEntryHeader;
typedef struct ResMatCAnm { u8 hdr[8]; ResDict dict; } ResMatCAnm;
typedef struct ResDictMatCAnmData { u32 Diffuse, Ambient, Specular, Emission, PolygonAlpha; } ResDictMatCAnmData;
typedef struct MatAnmResult { u32 flag; u32 prmMatColor0; u32 prmMatColor1; u32 prmPolygonAttr; } MatAnmResult;
typedef struct AnmObj { s32 frame; s32 ratio; void *resAnm; } AnmObj;

extern u16 GetMatColAnmValue_(const ResMatCAnm *, u32, u32);
extern u16 GetMatColAnmuAlphaValue_(const ResMatCAnm *, u32, u32);

static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return (void *)&hdr->data[hdr->sizeUnit * idx];
}
static inline const ResDictMatCAnmData *GetData(const ResMatCAnm *c, u32 idx)
{
    return (const ResDictMatCAnmData *)GetResDataByIdx(&c->dict, idx);
}

void NNSi_G3dAnmCalcNsBma(MatAnmResult *pResult, const AnmObj *pAnmObj, u32 dataIdx)
{
    const ResMatCAnm *cAnm = (const ResMatCAnm *)pAnmObj->resAnm;
    u32 frame = (u32)(pAnmObj->frame >> 12);
    const ResDictMatCAnmData *pAnmData = GetData(cAnm, (u16)dataIdx);
    {
        u32 a, b;
        a = GetMatColAnmValue_(cAnm, pAnmData->Diffuse, frame);
        b = GetMatColAnmValue_(cAnm, pAnmData->Ambient, frame);
        pResult->prmMatColor0 = (pResult->prmMatColor0 & 0x8000) | a | (b << 16);
        a = GetMatColAnmValue_(cAnm, pAnmData->Emission, frame);
        b = GetMatColAnmValue_(cAnm, pAnmData->Specular, frame);
        pResult->prmMatColor1 = (pResult->prmMatColor1 & 0x8000) | b | (a << 16);
        pResult->prmPolygonAttr = (pResult->prmPolygonAttr & ~0x1f0000) |
            (GetMatColAnmuAlphaValue_(cAnm, pAnmData->PolygonAlpha, frame) << 16);
    }
}
