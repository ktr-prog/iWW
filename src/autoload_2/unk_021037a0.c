typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
#define NULL 0

extern u8 *NNS_G3dGetResDataByName(void *dict, void *name);
extern void bindMdlPltt_Internal_(u8 *, u8 *, u8 *, u8 *);

static inline u8 *Ent(u8 *dict, u32 i)
{
    u8 *p = dict + *(u16 *)(dict + 6);
    return p + 4 + *(u16 *)p * i;
}

BOOL NNS_G3dBindMdlPltt(u8 *mdl, u8 *tex)
{
    u8 *set = mdl + *(u32 *)(mdl + 8);
    u8 *dict = set + *(u16 *)(set + 2);
    u32 i;
    BOOL ret;
    ret = 1;
    i = 0;
    while (i < dict[1]) {
        u8 *ents = dict + *(u16 *)(dict + 6);
        u8 *res = NNS_G3dGetResDataByName(tex + *(u16 *)(tex + 0x34), ents + *(u16 *)(ents + 2) + i * 16);
        if (res != NULL) {
            u8 *e = dict + *(u16 *)(dict + 6);
            e = e + 4 + *(u16 *)e * i;
            if ((e[3] & 1) == 0) {
                bindMdlPltt_Internal_(set, e, tex, res);
            }
        } else {
            ret = 0;
        }
        i++;
    }
    return ret;
}

BOOL NNS_G3dForceBindMdlPltt(u8 *mdl, u8 *tex, u32 i, u32 j)
{
    u8 *set = mdl + *(u32 *)(mdl + 8);
    u8 *dict = set + *(u16 *)(set + 2);
    u8 *tdict = tex + *(u16 *)(tex + 0x34);
    u8 *t = Ent(tdict, j);
    u8 *e = Ent(dict, i);
    if (e != NULL && (e[3] & 1) == 0) {
        bindMdlPltt_Internal_(set, e, tex, t);
        return 1;
    }
    return 0;
}

u16 NNSi_G2dSplitCharUTF16(const u16 **pp)
{
    const u16 *p = *pp;
    u16 v = *p++;
    *pp = p;
    return v;
}
