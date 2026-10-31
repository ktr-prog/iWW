
#include <stdio.h>
#include <stdlib.h>

#include "plat.h"

void *host_plat_read_file(const char *path, size_t *size) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    unsigned char *buf = 0;
    size_t len = 0, cap = 0;
    for (;;) {
        if (len == cap) {
            size_t ncap = cap ? cap * 2 : 1 << 20;
            unsigned char *nb = realloc(buf, ncap);
            if (!nb) { free(buf); fclose(f); return 0; }
            buf = nb;
            cap = ncap;
        }
        size_t got = fread(buf + len, 1, cap - len, f);
        len += got;
        if (got == 0) break;
    }
    int err = ferror(f);
    fclose(f);
    if (err) { free(buf); return 0; }
    *size = len;
    return buf;
}
