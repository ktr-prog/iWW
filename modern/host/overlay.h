#ifndef HOST_OVERLAY_H
#define HOST_OVERLAY_H

#include "host_overlay_vars.h"

typedef struct {
    unsigned id;
    const HostOverlayVar *vars;
    void (*staticInit)(void);
} HostOverlayUnit;

extern const HostOverlayUnit gHostOverlayUnits[];
extern const unsigned gHostOverlayUnitCount;

void HostOverlay_Init(void);

void HostOverlay_Load(unsigned id);

#endif
