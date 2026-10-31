
#include <stdio.h>
#include <stdlib.h>

#include "gpu3d/gpu3d.h"
#include "render.h"

static void no_melon(void) __attribute__((noreturn));
static void no_melon(void) {
    fprintf(stderr, "render: this build has no melonDS (the reference renderer): ACWW_RENDERER=melon, "
                    "ACWW_RENDERER3D=melon, ACWW_RENDER_COMPARE and the render self-tests need the oracle build "
                    "(tools/configure_host.py --oracle)\n");
    exit(1);
}

void melon_init(void) { no_melon(); }
void melon_write8(u32 addr, u8 v) { (void)addr, (void)v; no_melon(); }
void melon_write16(u32 addr, u16 v) { (void)addr, (void)v; no_melon(); }
void melon_write32(u32 addr, u32 v) { (void)addr, (void)v; no_melon(); }
u32 melon_read32(u32 addr) { (void)addr; no_melon(); }
void melon_frame(void) { no_melon(); }
const u32 *melon_screen(int screen) { (void)screen; no_melon(); }
int melon_gx_fifo_irq_level(void) { no_melon(); }
void melon_debug(void) { no_melon(); }
void melon_3d_lines(u32 *out) { (void)out; no_melon(); }
int melon_3d_buffers(u32 *depth, u32 *attr) { (void)depth, (void)attr; no_melon(); }
int melon_3d_poly_count(void) { no_melon(); }
int melon_3d_poly_get(int i, Gpu3dVertexOut *v, u32 *attr, u32 *texparam, u32 *texpal, int *flags) {
    (void)i, (void)v, (void)attr, (void)texparam, (void)texpal, (void)flags; no_melon();
}
void melon_3d_state(Gpu3dState *s) { (void)s; no_melon(); }
