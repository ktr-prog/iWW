// Offline stubs for vitaShaRK's runtime GLSL shader compiler (shark_*).
//
// vitaGL links the shark_* API, which otherwise drags in vitaShaRK -> SceShaccCgExt -> taiHEN and, at runtime,
// the on-device Cg compiler libshacccg.suprx. For stage 1 we present the DS image with vitaGL's PRECOMPILED
// blit + clear shaders (glBlitFramebuffer / glClear) and never drive the fixed-function or programmable pipeline,
// so shark is never actually invoked. These stubs satisfy the linker (shark stays "offline"); if any path ever
// did call shark it would get a clean failure (NULL / -1) rather than a bogus success. Stage 2's GPU geometry
// will revisit real shader compilation (which needs libshacccg) deliberately.

#include <stddef.h>
#include <stdint.h>

#include <vitashark.h>

int shark_init(const char *path) { (void)path; return -1; }
int shark_init_simple(const char *path) { (void)path; return -1; }
void shark_end(void) {}
void shark_set_allocators(void *(*malloc_func)(size_t), void (*free_func)(void *)) { (void)malloc_func; (void)free_func; }

SceGxmProgram *shark_compile_shader_extended(const char *src, uint32_t *size, shark_type type, shark_opt opt,
                                             int32_t use_fastmath, int32_t use_fastprecision, int32_t use_fastint) {
    (void)src; (void)size; (void)type; (void)opt; (void)use_fastmath; (void)use_fastprecision; (void)use_fastint;
    return NULL;
}
SceGxmProgram *shark_compile_shader(const char *src, uint32_t *size, shark_type type) {
    (void)src; (void)size; (void)type;
    return NULL;
}
void shark_clear_output(void) {}
const SceShaccCgCompileOutput *shark_get_internal_compile_output(void) { return NULL; }

void shark_install_log_cb(void (*cb)(const char *, shark_log_level, int)) { (void)cb; }
void shark_set_warnings_level(shark_warn_level level) { (void)level; }
void shark_set_shader_association_path(const char *path) { (void)path; }
void shark_set_locale(shark_locale locale) { (void)locale; }
