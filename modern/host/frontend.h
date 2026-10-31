#ifndef HOST_FRONTEND_H
#define HOST_FRONTEND_H

#include <stdint.h>

#define ACWW_SHM_MAGIC 0x41435757u
#define ACWW_SHM_NAME_DEFAULT "/acww-host"
#define ACWW_AUDIO_RATE 32728
#define ACWW_AUDIO_FRAMES 16384

typedef struct {
    uint32_t magic;
    uint32_t frame;
    uint32_t keys;
    int32_t touch_x, touch_y;
    uint32_t touch_down;
    uint32_t quit;
    uint32_t stick;
    uint32_t pad[8];
    uint32_t pixels[256 * 384];
    uint32_t audio_write;
    uint32_t audio_read;
    int16_t audio[ACWW_AUDIO_FRAMES * 2];
} AcwwShm;

AcwwShm *frontend_backend_open(const char *argv0);
void frontend_backend_frame(AcwwShm *shm);
void frontend_backend_close(void);
void frontend_backend_touch_read(int held);
void frontend_backend_turn(void);

#endif
