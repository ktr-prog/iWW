typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"

#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128a20.h"
#include "proto/autoload_2/unk_0212ef04.h"

typedef struct FILE {
    u32 handle;
    struct {
        u32 open_mode : 2;
        u32 io_mode : 3;
        u32 buffer_mode : 2;
        u32 file_kind : 3;
        u32 binary_io : 1;
    } mode;
    struct {
        u32 io_state : 3;
        u32 free_buffer : 1;
    } state;
    u8 eof;
    u8 error;
    u8 pad0e[4];
    u8 ungetc_buffer[2];
    u16 ungetc_wide_buffer[2];
    u32 position;
    u8 *buffer;
    u32 buffer_size;
    u8 *buffer_ptr;
    u32 buffer_len;
    u32 buffer_alignment;
    u32 saved_buffer_len;
    u32 buffer_pos;
    int (*position_proc)(u32, u32 *, int, void *);
    int (*read_proc)(u32, u8 *, u32 *, void *);
    int (*write_proc)(u32, u8 *, u32 *, void *);
    int (*close_proc)(u32);
    void *ref_con;
} FILE;

extern FILE data_0213c238[3];
extern OSMutex data_02200298[9];
extern u32 data_02200250[9];
extern s32 data_02200274[9];
extern OSThreadInfo data_021fcc2c;
extern int data_0220064c;
typedef struct LocaleCtype { int (*mbtowc)(u16 *, const char *, u32); int (*wctomb)(char *, u16); } LocaleCtype;
typedef struct LocaleCase { u32 a; u32 b; u32 c; u16 *map; } LocaleCase;
typedef struct LocaleCmpt { char **time; LocaleCase *chars; LocaleCtype *ctype; } LocaleCmpt;
extern LocaleCmpt data_0213c350;

int OS_TryLockMutex(OSMutex *);
int __fread(const void *, u32, u32, FILE *);
int __flush_all(void);
int __flush_buffer(FILE *, u32 *);
u32 strlen(const char *);
int _fseek(FILE *, u32, int);
int fseek(FILE *, int, int);
int fflush(FILE *);
int _ftell(FILE *);

void *memcpy(void *dst, const void *src, u32 n) {
    const u8 *p = (const u8 *)src;
    u8 *q = (u8 *)dst;
    for (n++; --n;) *q++ = *p++;
    return dst;
}

void *memmove(void *dst, const void *src, u32 n) {
    const u8 *p;
    u8 *q;
    if (src >= dst) {
        p = (const u8 *)src;
        q = (u8 *)dst;
        for (n++; --n;) *q++ = *p++;
    } else {
        p = (const u8 *)src + n;
        q = (u8 *)dst + n;
        for (n++; --n;) *--q = *--p;
    }
    return dst;
}

void *memset(void *dst, int val, u32 n) {
    __fill_mem(dst, val, n);
    return dst;
}

void *memchr(const void *src, int val, u32 n) {
    const u8 *p = (const u8 *)src;
    u32 v = (u8)val;
    for (n++; --n;) {
        if (*p++ == v) return (void *)(p - 1);
    }
    return 0;
}

int memcmp(const void *src1, const void *src2, u32 n) {
    const u8 *p1 = (const u8 *)src1;
    const u8 *p2 = (const u8 *)src2;
    for (n++; --n;) {
        if (*p1++ != *p2++) return (*--p1 < *--p2) ? -1 : +1;
    }
    return 0;
}

int mbtowc(u16 *pwc, const char *s, u32 n) {
    return data_0213c350.ctype->mbtowc(pwc, s, n);
}

int __mbtowc_noconv(u16 *pwc, const char *s, u32 n) {
    if (s == 0) return 0;
    if (n == 0) return -1;
    if (pwc != 0) *pwc = *(u8 *)s;
    if (*(u8 *)s == 0) return 0;
    return 1;
}

int __wctomb_noconv(char *s, u16 wc) {
    if (s == 0) return 0;
    *s = (char)wc;
    return 1;
}

int mbstowcs(u16 *pwcs, const char *s, u32 n) {
    int i;
    int len = strlen(s);
    int r;
    if (pwcs != 0) {
        for (i = 0; i < n; i++) {
            if (*(u8 *)s != 0) {
                r = mbtowc(pwcs++, s, len);
                if (r > 0) {
                    s += r;
                    len -= r;
                } else {
                    return -1;
                }
            } else {
                *pwcs = 0;
                break;
            }
        }
    } else {
        i = 0;
    }
    return i;
}

double scalbn(double a, s32 delta) {
    s32 v;
    double r = frexp(a, &v);
    v += delta;
    return ldexp(r, v);
}

int _ftell(FILE *file) {
    int pos;
    u32 st;
    if ((u8)((u8)file->mode.file_kind + 255) > 1 || file->error != 0) {
        data_0220064c = 40;
        return -1;
    }
    st = file->state.io_state;
    if (st == 0) return file->position;
    pos = file->buffer_pos + (file->buffer_ptr - file->buffer);
    if (st >= 3) pos -= st - 2;
    return pos;
}

int ftell(FILE *file) {
    int idx;
    OSMutex *m;
    int r;
    OSThread *t;
    if (file == &data_0213c238[0]) idx = 2;
    else if (file == &data_0213c238[1]) idx = 3;
    else if (file == &data_0213c238[2]) idx = 4;
    else idx = 5;
    m = &data_02200298[idx];
    if (OS_TryLockMutex(m) == 0) {
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    } else if (data_02200250[idx] == (t = data_021fcc2c.list)->id) {
        data_02200274[idx]++;
    } else {
        OS_LockMutex(m);
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    }
    r = _ftell(file);
    data_02200274[idx]--;
    if (data_02200274[idx] == 0) OS_UnlockMutex(m);
    return r;
}

int _fseek(FILE *file, u32 offset, int whence) {
    if ((u8)file->mode.file_kind != 1 || file->error != 0) {
        data_0220064c = 40;
        return -1;
    }
    if (file->state.io_state == 1 && __flush_buffer(file, 0) != 0) {
        file->error = 1;
        file->buffer_len = 0;
        data_0220064c = 40;
        return -1;
    }
    if (whence == 1) {
        whence = 0;
        offset += _ftell(file);
    }
    if (whence != 2 && file->mode.io_mode != 3 && (u32)(file->state.io_state - 2) <= 1) {
        if (offset >= file->position || offset < file->buffer_pos) {
            file->state.io_state = 0;
        } else {
            file->buffer_ptr = file->buffer + (offset - file->buffer_pos);
            file->buffer_len = file->position - offset;
            file->state.io_state = 2;
        }
    } else {
        file->state.io_state = 0;
    }
    if (file->state.io_state == 0) {
        if (file->position_proc != 0 && file->position_proc(file->handle, &offset, whence, file->ref_con) != 0) {
            file->error = 1;
            file->buffer_len = 0;
            data_0220064c = 40;
            return -1;
        }
        file->eof = 0;
        file->position = offset;
        file->buffer_len = 0;
    }
    return 0;
}

int fseek(FILE *file, int offset, int whence) {
    int idx;
    OSMutex *m;
    int r;
    OSThread *t;
    if (file == &data_0213c238[0]) idx = 2;
    else if (file == &data_0213c238[1]) idx = 3;
    else if (file == &data_0213c238[2]) idx = 4;
    else idx = 5;
    m = &data_02200298[idx];
    if (OS_TryLockMutex(m) == 0) {
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    } else if (data_02200250[idx] == (t = data_021fcc2c.list)->id) {
        data_02200274[idx]++;
    } else {
        OS_LockMutex(m);
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    }
    r = _fseek(file, offset, whence);
    data_02200274[idx]--;
    if (data_02200274[idx] == 0) OS_UnlockMutex(m);
    return r;
}

void rewind(FILE *file) {
    file->error = 0;
    fseek(file, 0, 0);
    file->error = 0;
}

int fclose(FILE *file) {
    int r, r2;
    if (file == 0) return -1;
    if (file->mode.file_kind == 0) return 0;
    r = fflush(file);
    r2 = file->close_proc(file->handle);
    file->mode.file_kind = 0;
    file->handle = 0;
    if (file->state.free_buffer) return -1;
    return -(r != 0 || r2 != 0);
}

int fflush(FILE *file) {
    if (file == 0) return __flush_all();
    if (file->error || file->mode.file_kind == 0) return -1;
    if (file->mode.io_mode == 1) return 0;
    if (file->state.io_state >= 3) file->state.io_state = 2;
    if (file->state.io_state == 2) file->buffer_len = 0;
    if (file->state.io_state != 1) {
        file->state.io_state = 0;
        return 0;
    }
    if (__flush_buffer(file, 0) != 0) {
        file->error = 1;
        file->buffer_len = 0;
        return -1;
    }
    file->state.io_state = 0;
    file->position = 0;
    file->buffer_len = 0;
    return 0;
}

u32 fread(const void *ptr, u32 size, u32 n, FILE *file) {
    int idx;
    OSMutex *m;
    u32 r;
    OSThread *t;
    idx = (file == &data_0213c238[0]) ? 2 : 5;
    m = &data_02200298[idx];
    if (OS_TryLockMutex(m) == 0) {
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    } else if (data_02200250[idx] == (t = data_021fcc2c.list)->id) {
        data_02200274[idx]++;
    } else {
        OS_LockMutex(m);
        data_02200250[idx] = data_021fcc2c.list->id;
        data_02200274[idx] = 1;
    }
    r = __fread(ptr, size, n, file);
    data_02200274[idx]--;
    if (data_02200274[idx] == 0) OS_UnlockMutex(m);
    return r;
}

extern LocaleCase data_0213c378;
extern LocaleCtype data_0213c33c;
u16 data_0213c400[58] = {
    2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,
    34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 0, 0, 0, 0, 0, 0,
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
    33, 35, 37, 39, 41, 43, 45, 47, 49, 51,
};
LocaleCase data_0213c378 = {0x41, 0x3a, 0, data_0213c400};
LocaleCtype data_0213c33c = {__mbtowc_noconv, __wctomb_noconv};
LocaleCmpt data_0213c350 = {data_0213c388, &data_0213c378, &data_0213c33c};
char *data_0213c388[8] = {
    "AM|PM",
    "%a %b %e %T %Y",
    "%I:%M:%S %p",
    "%m/%d/%y",
    "%T",
    "Sun|Sunday|Mon|Monday|Tue|Tuesday|Wed|Wednesday|Thu|Thursday|Fri|Friday|Sat|Saturday",
    "Jan|January|Feb|February|Mar|March|Apr|April|May|May|Jun|June|Jul|July|Aug|August|Sep|September|Oct|October|Nov|November|Dec|December",
    "",
};

u32 data_02200250[9];
s32 data_02200274[9];
OSMutex data_02200298[9];

#include "host_labels.h"

HOST_LABEL_DEFINE(data_02200324, (char *)&data_02200298[5].prev);
