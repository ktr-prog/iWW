// Frontend helper stubs for the 32-bit Vita build.
//
// The game defines these "*_Host*" helper functions only under #ifdef HOST64 (src/, e.g. PlayerActor_Host*,
// Scene_Host*, Heap_Host*), because every build with the modern SDL frontend has so far been 64-bit. The Vita is
// the first 32-bit host with that frontend, so the game compiles them out while modern/host/frontend.c and
// gpu2d.c still reference them. These stubs satisfy the link and let the game boot; the features they back
// (the warp/emotion/fishing/show-off/pocket debug overlay, heap tracing, the outdoor check) are inert on the
// Vita until the host-helper interface is ported to 32-bit for real (docs/vita.md). The signatures match the
// prototypes frontend.c/gpu2d.c declare (C linkage, so only the names need to agree). Compiled for --os vita only
// (modern/host/vita/ is a Vita-only directory); the real HOST64 definitions are the sole ones everywhere else.
#include <stdint.h>

int Scene_HostWarp(uint32_t id, int32_t x, int32_t z) { (void)id; (void)x; (void)z; return 0; }
int Scene_HostIsOutdoor(void) { return 0; }

int PlayerActor_HostEmotionState(void *o, int32_t *action, uint32_t *anim, uint32_t *mode, int32_t *effects) {
    (void)o; (void)action; (void)anim; (void)mode; (void)effects; return 0;
}
int PlayerActor_HostStartFishing(void *o) { (void)o; return 0; }
int PlayerActor_HostBobberFishState(void *o) { (void)o; return 0; }
int PlayerActor_HostShowOff(void *o, uint32_t kind, uint32_t item) { (void)o; (void)kind; (void)item; return 0; }
int PlayerActor_HostSetPocket(int idx, uint32_t item) { (void)idx; (void)item; return 0; }

int Building_HostSetLit(uint32_t item) { (void)item; return 0; }
void Actor_HostDump(void) {}

void *Heap_HostHandle(void *h) { (void)h; return 0; }
void Heap_HostTrace(void *h, void (*a)(void *, void *, uint32_t, int32_t), void (*f)(void *, void *)) {
    (void)h; (void)a; (void)f;
}
void Heap_HostFreeSpace(void *h, uint32_t *all, uint32_t *largest) {
    (void)h;
    if (all) *all = 0;
    if (largest) *largest = 0;
}
