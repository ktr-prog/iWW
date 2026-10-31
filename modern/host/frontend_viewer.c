#if !HOST_FRONTEND_SDL && !HOST_FRONTEND_NONE

#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "frontend.h"

static char sName[64];

AcwwShm *frontend_backend_open(const char *argv0) {
    if (!getenv("DISPLAY") && !getenv("WAYLAND_DISPLAY")) return 0;
    snprintf(sName, sizeof sName, "%s-%d", ACWW_SHM_NAME_DEFAULT, (int)getpid());
    int fd = shm_open(sName, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0 || ftruncate(fd, sizeof(AcwwShm)) < 0) { perror("frontend: shm"); return 0; }
    AcwwShm *shm = mmap(0, sizeof(AcwwShm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (shm == MAP_FAILED) return 0;
    memset(shm, 0, sizeof *shm);
    shm->magic = ACWW_SHM_MAGIC;
    char viewer[1024];
    const char *v = getenv("ACWW_VIEWER");
    if (v) snprintf(viewer, sizeof viewer, "%s", v);
    else {
        snprintf(viewer, sizeof viewer, "%s", argv0);
        char *slash = strrchr(viewer, '/');
        snprintf(slash ? slash + 1 : viewer, sizeof viewer - (slash ? slash + 1 - viewer : 0), "acww-viewer");
    }
    pid_t pid = fork();
    if (pid == 0) {
        unsetenv("LD_LIBRARY_PATH");
        execl(viewer, viewer, sName, (char *)0);
        perror(viewer);
        _exit(1);
    }
    return shm;
}

void frontend_backend_frame(AcwwShm *shm) { (void)shm; }

void frontend_backend_close(void) {
    if (sName[0]) shm_unlink(sName);
}

void frontend_backend_turn(void) {}
void frontend_backend_touch_read(int held) { (void)held; }
#endif
