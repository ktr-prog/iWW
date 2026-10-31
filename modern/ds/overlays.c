
#include "types.h"
#include "host_shared_calls.h"

#define MODERN_MAX_OVERLAYS 160

static u8 sOverlayLoaded[MODERN_MAX_OVERLAYS];
static u32 sOverlayStart[MODERN_MAX_OVERLAYS];
static u32 sOverlayEnd[MODERN_MAX_OVERLAYS];

void Modern_OverlayStarted(u32 id, u32 start, u32 end) {
    u32 i;
    for (i = 0; i < MODERN_MAX_OVERLAYS; i++) {
        if (sOverlayLoaded[i] && sOverlayStart[i] < end && start < sOverlayEnd[i]) {
            sOverlayLoaded[i] = 0;
        }
    }
    if (id < MODERN_MAX_OVERLAYS) {
        sOverlayLoaded[id] = 1;
        sOverlayStart[id] = start;
        sOverlayEnd[id] = end;
    }
}

void Modern_OverlayEnded(u32 id) {
    if (id < MODERN_MAX_OVERLAYS) {
        sOverlayLoaded[id] = 0;
    }
}

BOOL Modern_IsOverlayLoaded(u32 id) {
    return id < MODERN_MAX_OVERLAYS && sOverlayLoaded[id];
}

void *Modern_SharedResolve(const HostSharedCall *call) {
    u32 i;
    for (i = 0; i < call->count; i++) {
        if (Modern_IsOverlayLoaded(call->cands[i].overlay)) {
            return (void *)call->cands[i].addr;
        }
    }
    return (void *)call->cands[0].addr;
}
