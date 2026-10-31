#ifndef HOST_RENDER_H
#define HOST_RENDER_H

#include "host.h"

void render_init(void);
void render_write8(u32 addr, u8 v);
void render_write16(u32 addr, u16 v);
void render_write32(u32 addr, u32 v);
u32 render_read32(u32 addr);
void render_frame(void);
const u32 *render_screen(int screen);
int render_on_gpu(void);
int render_gx_fifo_irq_level(void);
void render_debug(void);
void render_exit_report(void);
int render_compare(const char *kind, u64 label);
int render_compare_3d(const char *kind, u64 label);
void render_selftest(long scenes) __attribute__((noreturn));
void render_selftest_gpu2d(long scenes) __attribute__((noreturn));
int render_check_gpu2d(void);

#endif
