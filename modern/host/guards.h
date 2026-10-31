#ifndef HOST_GUARDS_H
#define HOST_GUARDS_H

typedef struct HostGuard {
    char *at;
    unsigned kind;
    unsigned size;
    const char *name;
    const char *file;
} HostGuard;

extern const unsigned host_guard_size, host_guard_count;
extern const HostGuard host_guard_table[];

void host_guards_init(void);
void host_guards_frame(void);
void host_guards_exit(void);

#endif
