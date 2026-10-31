#ifndef HOST_SAVESTATE_H
#define HOST_SAVESTATE_H

#include <stddef.h>

void host_state_track(void *p, size_t n);
void host_state_track_stack(void *p, size_t n);
void host_state_untrack(void *p);
void host_state_keep(void *p, size_t n);
void host_state_foreign(const void *p, size_t n);

#define HOST_STATE_KEEP(var) \
    static void __attribute__((constructor)) host_state_keep_##var(void) { host_state_keep(&(var), sizeof(var)); }

int host_state_save(void *const *gameSp);
int host_state_load(void **gameSp);
int host_state_have(void);
const char *host_state_message(void);

#endif
