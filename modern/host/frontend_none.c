#if HOST_FRONTEND_NONE

#include <stdio.h>

#include "frontend.h"

AcwwShm *frontend_backend_open(const char *argv0) {
    (void)argv0;
    fprintf(stderr, "host: built without a frontend (no SDL2): headless\n");
    return 0;
}

void frontend_backend_frame(AcwwShm *shm) { (void)shm; }

void frontend_backend_close(void) {}

void frontend_backend_turn(void) {}
void frontend_backend_touch_read(int held) { (void)held; }
#endif
