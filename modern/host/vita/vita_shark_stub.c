// Offline stubs for vitaShaRK's runtime GLSL shader compiler.
//
// vitaGL hard-links against the vitaShaRK API (shark_*), but vitaShaRK itself pulls in SceShaccCgExt and taiHEN,
// which we don't want to build - and we never compile GLSL at runtime (we use vitaGL's precompiled fixed-function
// shaders). So instead of building vitaShaRK, we vendor its header (vitashark.h) and provide these stubs: shark
// stays "offline" (shark_init returns failure), vitaGL sees is_shark_online == false and uses its precompiled
// shaders, and the custom-GLSL path (never taken) compiles to no-ops. No on-device libshacccg.suprx is needed.

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
