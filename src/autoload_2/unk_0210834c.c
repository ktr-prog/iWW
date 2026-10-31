

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
#include "types64.h"
#include "host_labels.h"
typedef int BOOL;
typedef struct VecFx32 { s32 x, y, z; } VecFx32;
#include "nnsys/g3d_rt.h"
typedef G3dRS RS;
typedef struct ScaleCache { VecFx32 s; VecFx32 inv; } ScaleCache;
typedef struct JntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
} JntAnmResult;
extern RS *data_021f5cc0;
#define data_021f6ac4 HOST_LABEL(ScaleCache (*)[], data_021f6ac4)
extern void MIi_CpuCopy32(const void *, void *, u32);
static inline s32 FX_Mul(s32 a, s32 b) { return (s32)(((s64)a * b) >> 12); }
static inline BOOL BitVecCheck(const u32 *vec, u32 idx) { return (BOOL)(vec[idx >> 5] & (1 << (idx & 31))); }
static inline void BitVecSet(u32 *vec, u32 idx) { vec[idx >> 5] |= 1 << (idx & 31); }
static inline void BitVecReset(u32 *vec, u32 idx) { vec[idx >> 5] &= ~(1 << (idx & 31)); }

void NNSi_G3dGetJointScaleSi3d(JntAnmResult *pResult, const s32 *p, const u8 *cmd, u32 srtflag)
{
    u32 nodeID = *(cmd + 1);
    u32 parentID = *(cmd + 2);
    if (srtflag & 4) {
        pResult->flag |= 1;
        if (BitVecCheck(&data_021f5cc0->isScaleCacheOne[0], parentID)) {
            BitVecSet(&data_021f5cc0->isScaleCacheOne[0], nodeID);
            pResult->flag |= 0x18;
        } else {
            MIi_CpuCopy32(&data_021f6ac4[parentID], &data_021f6ac4[nodeID], sizeof(ScaleCache));
            MIi_CpuCopy32(&data_021f6ac4[parentID], &pResult->scaleEx0, sizeof(ScaleCache));
        }
    } else {
        pResult->scale.x = *(p + 0);
        pResult->scale.y = *(p + 1);
        pResult->scale.z = *(p + 2);
        if (BitVecCheck(&data_021f5cc0->isScaleCacheOne[0], parentID)) {
            MIi_CpuCopy32(p, &data_021f6ac4[nodeID], sizeof(ScaleCache));
            BitVecReset(&data_021f5cc0->isScaleCacheOne[0], nodeID);
            pResult->flag |= 0x18;
        } else {
            BitVecReset(&data_021f5cc0->isScaleCacheOne[0], nodeID);
            data_021f6ac4[nodeID].s.x = FX_Mul(*(p + 0), data_021f6ac4[parentID].s.x);
            data_021f6ac4[nodeID].s.y = FX_Mul(*(p + 1), data_021f6ac4[parentID].s.y);
            data_021f6ac4[nodeID].s.z = FX_Mul(*(p + 2), data_021f6ac4[parentID].s.z);
            data_021f6ac4[nodeID].inv.x = FX_Mul(*(p + 3), data_021f6ac4[parentID].inv.x);
            data_021f6ac4[nodeID].inv.y = FX_Mul(*(p + 4), data_021f6ac4[parentID].inv.y);
            data_021f6ac4[nodeID].inv.z = FX_Mul(*(p + 5), data_021f6ac4[parentID].inv.z);
            MIi_CpuCopy32(&data_021f6ac4[parentID], &pResult->scaleEx0, sizeof(ScaleCache));
        }
    }
}
