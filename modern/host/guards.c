#include "guards.h"
#include "host.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HOST_GUARDS
#include <sys/mman.h>
#include <unistd.h>

u64 host_frame(void);
static unsigned sFill = 0xa5, sAltLo, sAltHi, sAltFill;
static unsigned *sReports;
static int sCheck;

static unsigned fill_of(unsigned i) { return i >= sAltLo && i < sAltHi ? sAltFill : sFill; }

void host_guards_init(void) {
    const char *e = getenv("ACWW_GUARDS_FILL");
    if (e) sFill = (unsigned)strtoul(e, 0, 0) & 0xff;
    e = getenv("ACWW_GUARDS_ALT");
    if (e && sscanf(e, "%u-%u:%x", &sAltLo, &sAltHi, &sAltFill) != 3) sAltLo = sAltHi = 0;
    sAltFill &= 0xff;
    e = getenv("ACWW_GUARDS");
    sCheck = e && *e && *e != '0';
    long page = sysconf(_SC_PAGESIZE);
    for (unsigned i = 0; i < host_guard_count; i++) {
        const HostGuard *g = &host_guard_table[i];
        if (g->kind == 1) {
            uintptr_t lo = (uintptr_t)g->at & ~(uintptr_t)(page - 1), hi = ((uintptr_t)g->at + host_guard_size + page - 1) & ~(uintptr_t)(page - 1);
            mprotect((void *)lo, hi - lo, PROT_READ | PROT_WRITE);
            memset(g->at, (int)fill_of(i), host_guard_size);
            mprotect((void *)lo, hi - lo, PROT_READ);
        } else {
            memset(g->at, (int)fill_of(i), host_guard_size);
        }
    }
    sReports = calloc(host_guard_count, sizeof *sReports);
    if (sCheck)
        fprintf(stderr, "guards: %u guards of %u bytes, fill %#x\n", host_guard_count, host_guard_size, sFill);
}

void host_guards_frame(void) {
    if (!sCheck) return;
    for (unsigned i = 0; i < host_guard_count; i++) {
        const HostGuard *g = &host_guard_table[i];
        if (g->kind == 1) continue;
        const u8 *p = (const u8 *)g->at;
        u8 f = (u8)fill_of(i);
        if (p[0] == f && !memcmp(p, p + 1, host_guard_size - 1)) continue;
        unsigned first = host_guard_size, last = 0, n = 0;
        for (unsigned k = 0; k < host_guard_size; k++)
            if (p[k] != f) { if (first == host_guard_size) first = k; last = k; n++; }
        if (sReports[i]++ < 4) {
            fprintf(stderr, "guards: frame %llu: %s (%s, %#x bytes) written past its end: +%#x..+%#x (%u bytes) at %p:",
                    (unsigned long long)host_frame(), g->name, g->file, g->size, g->size + first, g->size + last, n,
                    (void *)(g->at + first));
            for (unsigned k = first; k <= last && k < first + 16; k++) fprintf(stderr, " %02x", p[k]);
            fprintf(stderr, "\n");
        }
        memset(g->at, f, host_guard_size);
    }
}

void host_guards_exit(void) {
    if (!sCheck || !sReports) return;
    unsigned n = 0;
    for (unsigned i = 0; i < host_guard_count; i++)
        if (sReports[i]) {
            fprintf(stderr, "guards: summary: %s (%s): %u frames\n", host_guard_table[i].name, host_guard_table[i].file,
                    sReports[i]);
            n++;
        }
    fprintf(stderr, "guards: summary: %u variables written past their end\n", n);
}

#else

void host_guards_init(void) {}
void host_guards_frame(void) {}
void host_guards_exit(void) {}

#endif
