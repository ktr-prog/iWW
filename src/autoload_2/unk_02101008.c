#include "uptr.h"
#include "proto/autoload_2/unk_02101008.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_0210169c.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct NNSFndLink { void *prev; void *next; } NNSFndLink;
typedef struct NNSFndList { void *head; void *tail; u16 num; u16 offset; } NNSFndList;
typedef struct Region { uptr start; uptr end; } Region;

typedef struct MBlock {
    u16 sig;
    union {
        u16 raw;
        struct { u16 groupID : 8; u16 alignment : 7; u16 allocDir : 1; } f;
    } attr;
    u32 size;
    struct MBlock *prev;
    struct MBlock *next;
} MBlock;

typedef struct FrmState { u32 tag; uptr head; uptr tail; struct FrmState *prev; } FrmState;

typedef struct FrmHead {
    uptr head;
    uptr tail;
    FrmState *state;
} FrmHead;

typedef struct HeapHead {
    u32 sig;
    NNSFndLink link;
    NNSFndList childList;
    uptr start;
    uptr end;
    union {
        u32 raw;
        struct { u32 optFlag : 8; u32 pad : 24; } f;
    } attr;
    union {
        struct {
            MBlock *freeHead, *freeTail;
            MBlock *usedHead, *usedTail;
            u16 groupID;
            union { u16 raw; struct { u16 allocMode : 1; u16 pad : 15; } f; } feature;
        } exp;
        FrmHead frm;
    } u;
} HeapHead;

extern s32 abs(s32 x);

static inline uptr RoundUp(uptr v, uptr a) { return (v + (a - 1)) & ~(a - 1); }

u32 NNS_FndGetAllocatableSizeForFrmHeapEx(HeapHead *heap, s32 alignment) {
    alignment = abs(alignment);
    {
        const FrmHead *f = &heap->u.frm;
        uptr block = RoundUp(f->head, alignment);
        if (block > f->tail) return 0;
        return (u32)(f->tail - block);
    }
}
