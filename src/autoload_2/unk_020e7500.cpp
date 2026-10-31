#include "ds_div.h"
#include "host_mem.h"
#include "types.h"
#include "sys/TreeNode.h"
#include "gfx/VecFx32.h"
#include "sys/ListNode.h"
#include "nitro/io_access.h"

struct Tree {
    TreeNode *root;
};
struct MtxFx43 {
    s32 m[4][3];
};
struct TPData {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
};
struct TPCalibrateParam {
    s16 x0, xDotSize, y0, yDotSize;
};
struct PadState {
    u16 cur;
    u16 trig;
    s16 dir;
};

extern "C" {
s32 func_02133150(s32, s32);
s32 FX_Div(s32, s32);
s32 VEC_Mag(const VecFx32 *v);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
void MTX_RotZ43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_RotY43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_RotX43_(MtxFx43 *m, s32 sin, s32 cos);
void MTX_Scale43_(MtxFx43 *m, s32 x, s32 y, s32 z);
void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
void Vec_Sub(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
s32 Vec_MagXZ(const VecFx32 *v);
void Vec_Scale(VecFx32 *v, s32 s);
u16 TP_GetLatestIndexInAuto(void);
void TP_GetCalibratedPoint(TPData *dst, const TPData *src);
void TP_Init(void);
BOOL TP_GetUserInfo(TPCalibrateParam *p);
void TP_SetCalibrateParam(const TPCalibrateParam *p);
void TP_RequestSetStabilityAsync(u32, u32);
void TP_WaitBusy(u32);
u32 TP_CheckError(u32);
void TP_RequestAutoSamplingStartAsync(u32, u32, TPData *, u32);
void Fatal_Trap(void);

extern u16 data_0213a748[];
extern const s16 kPadDirAngleTable[];
extern const s16 data_02135f44[];
extern s32 gFrameCounter;
extern s32 data_021f476c;
extern u8 gTouchHeld;
extern u8 gTouchChanged;
extern u16 gTouchX;
extern u16 gTouchY;
extern TPData sTouchPoint;
extern TPData sTouchSampleBuf[9];
extern u8 data_021f47d0;
extern u16 sPadPrevHeld;
extern PadState gPad;

BOOL List_PushFront(List *list, ListNode *node);
void TreeNode_Init(TreeNode *n);
u32 Random_Next(u32 *seed);
void Mtx43_SetRotZ(MtxFx43 *m, s32 angle);
void Mtx43_SetRotY(MtxFx43 *m, s32 angle);
void Mtx43_SetRotX(MtxFx43 *m, s32 angle);
void Mtx43_SetTranslate(MtxFx43 *m, s32 x, s32 y, s32 z);
}

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

static inline u16 PAD_Read(void) {
    return (u16)(((IO_R((vu16 *)0x04000130) | *HW_SYSWORK(vu16, buttonXY)) ^ 0x2fff) & 0x2fff);
}
static inline BOOL PAD_DetectFold(void) {
    return (*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15;
}

#define FX_SinIdx(a) data_02135f44[((a) >> 4) * 2]
#define FX_CosIdx(a) data_02135f44[((a) >> 4) * 2 + 1]
extern "C" void Random_SetSeed(u32 *seed, u32 v) {
    *seed = v;
}

extern "C" u32 Random_Next(u32 *seed) {
    *seed = *seed * 0x0019660d + 0x3c6ef35f;
    return *seed;
}

extern "C" u32 Random_NextBelow(u32 *seed, u32 n) {
    return (u32)(((u64)n * Random_Next(seed)) >> 32);
}

extern "C" s32 Math_ApproachVec(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min) {
    VecFx32 d;
    s32 len;
    s32 step;

    if (p->x == target->x && p->z == target->z) return 0;
    Vec_Sub(&d, target, p);
    len = VEC_Mag(&d);
    if (len < min) {
        *p = *target;
        return 0;
    }
    step = FX_Mul(len, ratio);
    if (step == 0) {
        *p = *target;
        return 0;
    }
    if (step > max) {
        step = max;
    } else if (step < min) {
        step = min;
    }
    Vec_Scale(&d, FX_Div(step, len));
    VEC_Add(p, &d, p);
    return len - step;
}

extern "C" s32 Math_ApproachVecXZ(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min) {
    VecFx32 d;
    s32 len;
    s32 step;

    if (p->x == target->x && p->z == target->z) return 0;
    Vec_Sub(&d, target, p);
    len = Vec_MagXZ(&d);
    if (len < min) {
        p->x = target->x;
        p->z = target->z;
        return 0;
    }
    step = FX_Mul(len, ratio);
    if (step == 0) {
        p->x = target->x;
        p->z = target->z;
        return 0;
    }
    if (step > max) {
        step = max;
    } else if (step < min) {
        step = min;
    }
    Vec_Scale(&d, FX_Div(step, len));
    p->x += d.x;
    p->z += d.z;
    return len - step;
}

extern "C" void Main_ResetFrameCounter(void) {
    gFrameCounter = 0;
    data_021f476c = 0;
}

extern "C" s16 Math_Atan2(s32 x, s32 y) {
    s32 r;
    if (x == 0) {
        r = y >= 0 ? 0 : 0x8000;
    } else if (y == 0) {
        r = x >= 0 ? 0x4000 : 0xc000;
    } else if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                r = data_0213a748[FX_Div(x, y) >> 2];
            } else {
                r = 0x4000 - data_0213a748[FX_Div(y, x) >> 2];
            }
        } else {
            y = -y;
            if (y < x) {
                r = data_0213a748[FX_Div(y, x) >> 2] + 0x4000;
            } else {
                r = 0x8000 - data_0213a748[FX_Div(x, y) >> 2];
            }
        }
    } else {
        if (y < 0) {
            if (y <= x) {
                r = data_0213a748[FX_Div(-x, -y) >> 2] + 0x8000;
            } else {
                r = 0xc000 - data_0213a748[FX_Div(-y, -x) >> 2];
            }
        } else {
            x = -x;
            if (y < x) {
                r = data_0213a748[FX_Div(y, x) >> 2] + 0xc000;
            } else {
                r = -data_0213a748[FX_Div(x, y) >> 2];
            }
        }
    }
    return r;
}

extern "C" TreeNode *TreeNode_Construct(TreeNode *n) {
    TreeNode_Init(n);
    return n;
}

extern "C" void TreeNode_Init(TreeNode *n) {
    n->parent = NULL;
    n->child = NULL;
    n->prev = NULL;
    n->next = NULL;
}

extern "C" BOOL TreeNode_Attach(Tree *tree, TreeNode *node, TreeNode *parent) {
    if (node != NULL) {
        if (parent != NULL) {
            TreeNode *c;
            node->parent = parent;
            c = parent->child;
            if (c == NULL) {
                parent->child = node;
            } else {
                while (c->next != NULL) c = c->next;
                c->next = node;
                node->prev = c;
            }
        } else {
            if (tree->root != NULL) return FALSE;
            tree->root = node;
        }
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL TreeNode_Detach(Tree *tree, TreeNode *node) {
    if (node != NULL) {
        if (node->child != NULL) return FALSE;
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else if (node->parent != NULL) {
            node->parent->child = node->next;
        } else {
            tree->root = NULL;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        node->prev = NULL;
        node->next = NULL;
        node->parent = NULL;
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL List_InsertAfter(List *list, ListNode *node, ListNode *after) {
    if (after == NULL) {
        return List_PushFront(list, node);
    }
    if (node != NULL) {
        node->next = after->next;
        node->prev = after;
        after->next = node;
        if (node->next != NULL) {
            node->next->prev = node;
        } else {
            list->tail = node;
        }
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL List_Remove(List *list, ListNode *node) {
    if (node != NULL) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else if (node == list->head) {
            list->head = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        } else if (node == list->tail) {
            list->tail = node->prev;
        }
        node->prev = NULL;
        node->next = NULL;
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL List_PushBack(List *list, ListNode *node) {
    if (node != NULL) {
        if (list->tail != NULL) {
            list->tail->next = node;
            node->prev = list->tail;
        } else {
            list->head = node;
        }
        list->tail = node;
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL List_PushFront(List *list, ListNode *node) {
    if (node != NULL) {
        if (list->head != NULL) {
            list->head->prev = node;
            node->next = list->head;
        } else {
            list->tail = node;
        }
        list->head = node;
    } else {
        return FALSE;
    }
    return TRUE;
}

extern "C" s32 Math_ApproachS32(s32 *p, s32 target, s32 ratio, s32 max, s32 min) {
    s32 cur = *p;
    s32 d;
    if (cur != target) {
        d = FX_Mul(target - cur, ratio);
        if (d >= min || d <= -min) {
            if (d > max) d = max;
            if (d < -max) d = -max;
            *p += d;
        } else if (d > 0) {
            if (d < min) {
                *p = cur + min;
                if (*p > target) *p = target;
            }
        } else {
            s32 n = -min;
            if (d > n) {
                *p = cur + n;
                if (*p < target) *p = target;
            }
        }
    }
    d = target - *p;
    return d < 0 ? -d : d;
}

extern "C" void Math_ApproachS32Max(s32 *p, s32 target, s32 ratio, s32 max) {
    s32 d;
    if (*p == target) return;
    d = FX_Mul(target - *p, ratio);
    if (d > max) {
        d = max;
    } else if (d < -max) {
        d = -max;
    }
    *p += d;
}

extern "C" s32 Math_AngleDiffAbs(s32 a, s32 b) {
    s16 d = a - b;
    return d < 0 ? -d : d;
}

extern "C" BOOL Math_IsInRange(s32 v, s32 a, s32 b) {
    if (a < b) {
        BOOL r = FALSE;
        do {
            if (v < a) break;
            if (v <= b) r = TRUE;
        } while (0);
        return r;
    } else {
        BOOL r = FALSE;
        do {
            if (v < b) break;
            if (v <= a) r = TRUE;
        } while (0);
        return r;
    }
}

extern "C" void Math_ApproachS16Div(s16 *p, s16 target, s16 div, s16 max) {
    s16 d = DS_DIV((s16)(target - *p), div);
    if (d > max) {
        *p += max;
        return;
    }
    if (d < -max) {
        *p -= max;
    } else {
        *p += d;
    }
}

extern "C" BOOL Math_StepU8(u8 *p, s16 target, s16 step) {
    if (step != 0) {
        s16 v;
        if (*p > target) step = -step;
        v = *p + step;
        if (step * (v - target) >= 0) {
            *p = target;
            return TRUE;
        }
        *p = v;
    } else if (*p == target) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Math_StepS16(s16 *p, s16 target, s16 step) {
    if (step != 0) {
        if (*p > target) step = -step;
        *p += step;
        if (step * (*p - target) >= 0) {
            *p = target;
            return TRUE;
        }
    } else if (*p == target) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Math_StepS32(s32 *p, s32 target, s32 step) {
    if (step != 0) {
        if (*p > target) step = -step;
        *p += step;
        if ((s64)step * (*p - target) >= 0) {
            *p = target;
            return TRUE;
        }
    } else if (*p == target) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Math_StepS32Alt(s32 *p, s32 target, s32 step) {
    if (step != 0) {
        if (*p > target) step = -step;
        *p += step;
        if ((s64)step * (*p - target) >= 0) {
            *p = target;
            return TRUE;
        }
    } else if (*p == target) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Math_StepAngle(s16 *p, s16 target, s16 step) {
    if (step != 0) {
        if ((s16)(*p - target) > 0) step = -step;
        *p += step;
        if (step * (s16)(*p - target) >= 0) {
            *p = target;
            return TRUE;
        }
    } else if (*p == target) {
        return TRUE;
    }
    return FALSE;
}

extern "C" u8 Math_CountDownU8(u8 *p) {
    if (*p != 0) (*p)--;
    return *p;
}

extern "C" u16 Math_CountDownU16(u16 *p) {
    if (*p != 0) (*p)--;
    return *p;
}

u16 data_0213a748[1025] = {
    0, 10, 20, 31, 41, 51, 61, 71, 81, 92, 102, 112, 122, 132, 143, 153,
    163, 173, 183, 194, 204, 214, 224, 234, 244, 255, 265, 275, 285, 295, 305, 316,
    326, 336, 346, 356, 367, 377, 387, 397, 407, 417, 428, 438, 448, 458, 468, 478,
    489, 499, 509, 519, 529, 539, 550, 560, 570, 580, 590, 600, 610, 621, 631, 641,
    651, 661, 671, 681, 692, 702, 712, 722, 732, 742, 752, 763, 773, 783, 793, 803,
    813, 823, 833, 844, 854, 864, 874, 884, 894, 904, 914, 924, 935, 945, 955, 965,
    975, 985, 995, 1005, 1015, 1025, 1036, 1046, 1056, 1066, 1076, 1086, 1096, 1106, 1116, 1126,
    1136, 1146, 1156, 1166, 1177, 1187, 1197, 1207, 1217, 1227, 1237, 1247, 1257, 1267, 1277, 1287,
    1297, 1307, 1317, 1327, 1337, 1347, 1357, 1367, 1377, 1387, 1397, 1407, 1417, 1427, 1437, 1447,
    1457, 1467, 1477, 1487, 1497, 1507, 1517, 1527, 1537, 1547, 1557, 1567, 1577, 1587, 1597, 1607,
    1617, 1627, 1637, 1646, 1656, 1666, 1676, 1686, 1696, 1706, 1716, 1726, 1736, 1746, 1756, 1765,
    1775, 1785, 1795, 1805, 1815, 1825, 1835, 1845, 1854, 1864, 1874, 1884, 1894, 1904, 1914, 1923,
    1933, 1943, 1953, 1963, 1973, 1982, 1992, 2002, 2012, 2022, 2031, 2041, 2051, 2061, 2071, 2080,
    2090, 2100, 2110, 2120, 2129, 2139, 2149, 2159, 2168, 2178, 2188, 2198, 2207, 2217, 2227, 2237,
    2246, 2256, 2266, 2275, 2285, 2295, 2305, 2314, 2324, 2334, 2343, 2353, 2363, 2372, 2382, 2392,
    2401, 2411, 2421, 2430, 2440, 2450, 2459, 2469, 2478, 2488, 2498, 2507, 2517, 2526, 2536, 2546,
    2555, 2565, 2574, 2584, 2594, 2603, 2613, 2622, 2632, 2641, 2651, 2660, 2670, 2679, 2689, 2699,
    2708, 2718, 2727, 2737, 2746, 2756, 2765, 2775, 2784, 2793, 2803, 2812, 2822, 2831, 2841, 2850,
    2860, 2869, 2879, 2888, 2897, 2907, 2916, 2926, 2935, 2944, 2954, 2963, 2973, 2982, 2991, 3001,
    3010, 3019, 3029, 3038, 3047, 3057, 3066, 3075, 3085, 3094, 3103, 3113, 3122, 3131, 3141, 3150,
    3159, 3168, 3178, 3187, 3196, 3206, 3215, 3224, 3233, 3243, 3252, 3261, 3270, 3279, 3289, 3298,
    3307, 3316, 3325, 3335, 3344, 3353, 3362, 3371, 3380, 3390, 3399, 3408, 3417, 3426, 3435, 3444,
    3453, 3463, 3472, 3481, 3490, 3499, 3508, 3517, 3526, 3535, 3544, 3553, 3562, 3571, 3580, 3589,
    3599, 3608, 3617, 3626, 3635, 3644, 3653, 3662, 3670, 3679, 3688, 3697, 3706, 3715, 3724, 3733,
    3742, 3751, 3760, 3769, 3778, 3787, 3796, 3804, 3813, 3822, 3831, 3840, 3849, 3858, 3867, 3875,
    3884, 3893, 3902, 3911, 3920, 3928, 3937, 3946, 3955, 3964, 3972, 3981, 3990, 3999, 4007, 4016,
    4025, 4034, 4042, 4051, 4060, 4069, 4077, 4086, 4095, 4103, 4112, 4121, 4129, 4138, 4147, 4155,
    4164, 4173, 4181, 4190, 4199, 4207, 4216, 4224, 4233, 4242, 4250, 4259, 4267, 4276, 4284, 4293,
    4302, 4310, 4319, 4327, 4336, 4344, 4353, 4361, 4370, 4378, 4387, 4395, 4404, 4412, 4421, 4429,
    4438, 4446, 4454, 4463, 4471, 4480, 4488, 4497, 4505, 4513, 4522, 4530, 4539, 4547, 4555, 4564,
    4572, 4580, 4589, 4597, 4605, 4614, 4622, 4630, 4639, 4647, 4655, 4663, 4672, 4680, 4688, 4697,
    4705, 4713, 4721, 4730, 4738, 4746, 4754, 4762, 4771, 4779, 4787, 4795, 4803, 4812, 4820, 4828,
    4836, 4844, 4852, 4860, 4869, 4877, 4885, 4893, 4901, 4909, 4917, 4925, 4933, 4941, 4949, 4958,
    4966, 4974, 4982, 4990, 4998, 5006, 5014, 5022, 5030, 5038, 5046, 5054, 5062, 5070, 5078, 5086,
    5094, 5101, 5109, 5117, 5125, 5133, 5141, 5149, 5157, 5165, 5173, 5181, 5188, 5196, 5204, 5212,
    5220, 5228, 5235, 5243, 5251, 5259, 5267, 5275, 5282, 5290, 5298, 5306, 5313, 5321, 5329, 5337,
    5344, 5352, 5360, 5368, 5375, 5383, 5391, 5398, 5406, 5414, 5421, 5429, 5437, 5444, 5452, 5460,
    5467, 5475, 5483, 5490, 5498, 5505, 5513, 5521, 5528, 5536, 5543, 5551, 5559, 5566, 5574, 5581,
    5589, 5596, 5604, 5611, 5619, 5626, 5634, 5641, 5649, 5656, 5664, 5671, 5679, 5686, 5694, 5701,
    5708, 5716, 5723, 5731, 5738, 5745, 5753, 5760, 5768, 5775, 5782, 5790, 5797, 5804, 5812, 5819,
    5826, 5834, 5841, 5848, 5856, 5863, 5870, 5878, 5885, 5892, 5899, 5907, 5914, 5921, 5928, 5936,
    5943, 5950, 5957, 5964, 5972, 5979, 5986, 5993, 6000, 6008, 6015, 6022, 6029, 6036, 6043, 6050,
    6058, 6065, 6072, 6079, 6086, 6093, 6100, 6107, 6114, 6121, 6128, 6135, 6142, 6150, 6157, 6164,
    6171, 6178, 6185, 6192, 6199, 6206, 6213, 6220, 6227, 6234, 6240, 6247, 6254, 6261, 6268, 6275,
    6282, 6289, 6296, 6303, 6310, 6317, 6323, 6330, 6337, 6344, 6351, 6358, 6365, 6371, 6378, 6385,
    6392, 6399, 6406, 6412, 6419, 6426, 6433, 6440, 6446, 6453, 6460, 6467, 6473, 6480, 6487, 6493,
    6500, 6507, 6514, 6520, 6527, 6534, 6540, 6547, 6554, 6560, 6567, 6574, 6580, 6587, 6594, 6600,
    6607, 6613, 6620, 6627, 6633, 6640, 6646, 6653, 6660, 6666, 6673, 6679, 6686, 6692, 6699, 6705,
    6712, 6718, 6725, 6731, 6738, 6744, 6751, 6757, 6764, 6770, 6777, 6783, 6790, 6796, 6803, 6809,
    6815, 6822, 6828, 6835, 6841, 6848, 6854, 6860, 6867, 6873, 6879, 6886, 6892, 6898, 6905, 6911,
    6917, 6924, 6930, 6936, 6943, 6949, 6955, 6962, 6968, 6974, 6980, 6987, 6993, 6999, 7005, 7012,
    7018, 7024, 7030, 7037, 7043, 7049, 7055, 7061, 7068, 7074, 7080, 7086, 7092, 7098, 7105, 7111,
    7117, 7123, 7129, 7135, 7141, 7147, 7154, 7160, 7166, 7172, 7178, 7184, 7190, 7196, 7202, 7208,
    7214, 7220, 7226, 7232, 7238, 7244, 7250, 7256, 7262, 7268, 7274, 7280, 7286, 7292, 7298, 7304,
    7310, 7316, 7322, 7328, 7334, 7340, 7346, 7352, 7358, 7363, 7369, 7375, 7381, 7387, 7393, 7399,
    7405, 7411, 7416, 7422, 7428, 7434, 7440, 7446, 7451, 7457, 7463, 7469, 7475, 7480, 7486, 7492,
    7498, 7503, 7509, 7515, 7521, 7526, 7532, 7538, 7544, 7549, 7555, 7561, 7566, 7572, 7578, 7584,
    7589, 7595, 7601, 7606, 7612, 7618, 7623, 7629, 7635, 7640, 7646, 7651, 7657, 7663, 7668, 7674,
    7679, 7685, 7691, 7696, 7702, 7707, 7713, 7718, 7724, 7730, 7735, 7741, 7746, 7752, 7757, 7763,
    7768, 7774, 7779, 7785, 7790, 7796, 7801, 7807, 7812, 7818, 7823, 7828, 7834, 7839, 7845, 7850,
    7856, 7861, 7866, 7872, 7877, 7883, 7888, 7893, 7899, 7904, 7910, 7915, 7920, 7926, 7931, 7936,
    7942, 7947, 7952, 7958, 7963, 7968, 7974, 7979, 7984, 7990, 7995, 8000, 8005, 8011, 8016, 8021,
    8026, 8032, 8037, 8042, 8047, 8053, 8058, 8063, 8068, 8074, 8079, 8084, 8089, 8094, 8100, 8105,
    8110, 8115, 8120, 8125, 8131, 8136, 8141, 8146, 8151, 8156, 8161, 8166, 8172, 8177, 8182, 8187,
    8192,
};
s32 gFrameCounter;
s32 data_021f476c;
