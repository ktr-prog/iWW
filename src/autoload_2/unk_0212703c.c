#include "ds_div.h"
#include "host_mem.h"
#include "types.h"
#include "nitro/io_access.h"

typedef struct { u32 c1; u32 c2; } Cycle;
typedef struct { u16 a; u8 b[3]; u8 pad; u16 c; u32 d; } Work;
typedef struct { u8 pad[0xac]; u32 f_ac; u16 f_b0; u8 pad2[3]; u8 f_b5[3]; u8 pad3[6]; u16 f_be; } Buf;

u16 data_02200054[2];
u32 data_02200058;
u32 data_0220005c;
BOOL (*data_02200060)(void);
_Alignas(32) Buf data_02200080;
#define data_02200084 ((u8 *)&data_02200080 + 4)
#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02128c60.h"
#include "proto/autoload_2/unk_02133ad0.h"
#include "proto/autoload_2/unk_0213510c.h"
#include "proto/main/unk_0206d49c.h"
extern OSThreadInfo data_021fcc2c;
extern OSMutex data_02200298[9];
extern u32 data_02200250;
extern s32 data_02200274;
void (*data_02200140)(void);
void (*data_02200144)(void);
s32 data_02200148;
u32 data_0220014c;
void (*data_02200150[64])(void);
extern BOOL OS_TryLockMutex(OSMutex *mutex);

extern void CpuSet(void *src, void *dst, u32 mode);
extern void WaitByLoop(u32);
extern BOOL PXI_IsCallbackReady(u32, u32);
extern void PXI_SetFifoRecvCallback(u32, void *);
extern u32 OS_SetIrqMask(u32);
extern u32 OS_GetLockID(void);
extern void DC_FlushAll(void);
extern void DC_InvalidateRange(void *, u32);
extern void MI_DmaCopy16(u32, uptr, void *, u32);
extern void MIi_CpuCopy32(u32, void *, u32);
extern void DGT_Hash2GetDigest(void *, void *, ...);
extern void DGT_Hash2SetSource(void *, const void *, u32);
extern void DGT_Hash2Reset(void *);
extern void CTRDGi_SendtoPxi(u32);
extern void CTRDGi_UnlockByProcessor(u32, void *);
extern void CTRDGi_LockByProcessor(u32, void *);

#define REG300 (*(volatile u16 *)0x04000300)
#define REG208 (*(volatile u16 *)0x04000208)
#define REG204 (*(volatile u16 *)0x04000204)


/* MSL C FILE (layout recovered from the code) */
typedef struct {
    u32 open_mode : 2;
    u32 io_mode : 3;
    u32 buffer_mode : 2;
    u32 file_kind : 3;
    u32 file_orientation : 2;
    u32 binary_io : 1;
} file_modes;
typedef struct {
    u32 io_state : 3;
    u32 free_buffer : 1;
} file_state;
typedef struct _FILE {
    u32 handle;
    file_modes mode;
    file_state state;
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
    u32 save_buffer_len;
    u32 buffer_pos;
    int (*position_proc)();
    int (*read_proc)(u32 handle, u8 *buf, size_t *count, void *ref);
    int (*write_proc)(u32 handle, u8 *buf, size_t *count, void *ref);
    int (*close_proc)(u32 handle);
    void *ref_con;
} FILE;
extern FILE data_0213c238[3];
extern s32 fflush(FILE *);
extern void *memcpy(void *dst, const void *src, u32 n);
extern u32 data_0213c320;
extern double _f2d(u32);
extern void __prep_buffer(FILE *);
extern s32 fwide(FILE *, s32);
extern u32 func_0213335c(u32, u32);
extern s32 __load_buffer(FILE *, u32 *, s32);
/* prototypes */
u32 __fread(void *ptr, u32 memb_size, u32 num_memb, FILE *file);
void __prep_buffer(FILE *file);
s32 __load_buffer(FILE *file, u32 *bytes_loaded, s32 alignment);
s32 __flush_buffer(FILE *file, u32 *bytes_flushed);
void CTRDGi_ChangeLatestAccessCycle(Cycle *p);
void CTRDGi_RestoreAccessCycle(Cycle *p);

u32 __fread(void *ptr, u32 memb_size, u32 num_memb, FILE *file) {
    u8 *read_ptr = ptr;
    u32 num_bytes;
    u32 bytes_to_go;
    u32 bytes_read;
    s32 ioresult;
    u32 always_buffer;

    if (fwide(file, 0) == 0) fwide(file, -1);
    bytes_to_go = memb_size * num_memb;
    if (bytes_to_go == 0 || file->error != 0 || file->mode.file_kind == 0) return 0;

    always_buffer = 1;
    if (file->mode.binary_io) {
        if (file->mode.buffer_mode != 2) always_buffer = 0;
    }

    if (file->state.io_state == 0) {
        if (file->mode.io_mode & 1) {
            file->state.io_state = 2;
            file->buffer_len = 0;
        }
    }

    if (file->state.io_state < 2) {
        file->error = 1;
        file->buffer_len = 0;
        return 0;
    }

    if (file->mode.buffer_mode & 1) {
        if (__flush_line_buffered_output_files() != 0) {
            file->error = 1;
            file->buffer_len = 0;
            return 0;
        }
    }

    bytes_read = 0;
    if (bytes_to_go != 0 && file->state.io_state >= 3) {
        do {
            if (fwide(file, 0) == 1) {
                bytes_read += 2;
                *(u16 *)read_ptr = file->ungetc_wide_buffer[file->state.io_state - 3];
                bytes_to_go -= 2;
                read_ptr += 2;
            } else {
                bytes_read++;
                *read_ptr = file->ungetc_buffer[file->state.io_state - 3];
                bytes_to_go--;
                read_ptr++;
            }
            file->state.io_state--;
        } while (bytes_to_go != 0 && file->state.io_state >= 3);
        if (file->state.io_state == 2) file->buffer_len = file->save_buffer_len;
    }

    if (bytes_to_go != 0 && (file->buffer_len != 0 || always_buffer)) {
        do {
            if (file->buffer_len == 0) {
                ioresult = __load_buffer(file, NULL, 0);
                if (ioresult != 0) {
                    if (ioresult == 1) {
                        file->error = 1;
                        file->buffer_len = 0;
                    } else {
                        file->state.io_state = 0;
                        file->eof = 1;
                        file->buffer_len = 0;
                    }
                    bytes_to_go = 0;
                    break;
                }
            }
            num_bytes = file->buffer_len;
            if (num_bytes > bytes_to_go) num_bytes = bytes_to_go;
            memcpy(read_ptr, file->buffer_ptr, num_bytes);
            read_ptr += num_bytes;
            bytes_read += num_bytes;
            bytes_to_go -= num_bytes;
            file->buffer_ptr += num_bytes;
            file->buffer_len -= num_bytes;
        } while (bytes_to_go != 0 && always_buffer);
    }

    if (bytes_to_go != 0 && !always_buffer) {
        u8 *save_buffer = file->buffer;
        u32 save_size = file->buffer_size;
        file->buffer = read_ptr;
        file->buffer_size = bytes_to_go;
        ioresult = __load_buffer(file, &num_bytes, 1);
        if (ioresult != 0) {
            if (ioresult == 1) {
                file->error = 1;
                file->buffer_len = 0;
            } else {
                file->state.io_state = 0;
                file->eof = 1;
                file->buffer_len = 0;
            }
        }
        bytes_read += num_bytes;
        file->buffer = save_buffer;
        file->buffer_size = save_size;
        __prep_buffer(file);
        file->buffer_len = 0;
    }

    return DS_UDIV(bytes_read, memb_size);
}

void __convert_from_newlines(u8 *buf, u32 *count) {
}

void __convert_to_newlines(u8 *buf, u32 *count) {
}

void __prep_buffer(FILE *file) {
    file->buffer_ptr = file->buffer;
    file->buffer_len = file->buffer_size;
    file->buffer_len = file->buffer_len - (file->position & file->buffer_alignment);
    file->buffer_pos = file->position;
}

s32 __load_buffer(FILE *file, u32 *bytes_loaded, s32 alignment) {
    s32 ret;
    __prep_buffer(file);
    if (alignment == 1) file->buffer_len = file->buffer_size;
    {
        size_t n = file->buffer_len;
        ret = file->read_proc(file->handle, file->buffer, &n, file->ref_con);
        file->buffer_len = n;
    }
    if (ret == 2) file->buffer_len = 0;
    if (bytes_loaded) *bytes_loaded = file->buffer_len;
    if (ret != 0) return ret;
    file->position += file->buffer_len;
    if (!file->mode.binary_io) __convert_to_newlines(file->buffer, &file->buffer_len);
    return 0;
}

s32 __flush_buffer(FILE *file, u32 *bytes_flushed) {
    s32 ret;
    u32 n = file->buffer_ptr - file->buffer;
    if (n != 0) {
        file->buffer_len = n;
        if (!file->mode.binary_io) __convert_from_newlines(file->buffer, &file->buffer_len);
        {
            size_t len = file->buffer_len;
            ret = file->write_proc(file->handle, file->buffer, &len, file->ref_con);
            file->buffer_len = len;
        }
        if (bytes_flushed) *bytes_flushed = file->buffer_len;
        if (ret != 0) return ret;
        file->position += file->buffer_len;
    }
    __prep_buffer(file);
    return 0;
}

s32 abs(s32 x) {
    if (x < 0) x = -x;
    return x;
}

s32 __flush_all(void) {
    s32 result = 0;
    s32 i = 1;
    FILE *file = &data_0213c238[0];
    do {
        if (file->mode.file_kind != 0) {
            if (fflush(file) != 0) result = -1;
        }
        file = (i < 3) ? &data_0213c238[i++] : NULL;
    } while (file != NULL);
    return result;
}

s32 __flush_line_buffered_output_files(void) {
    s32 result = 0;
    s32 i = 1;
    FILE *file = &data_0213c238[0];
    do {
        if (file->mode.file_kind != 0 && (file->mode.buffer_mode & 1) != 0 && file->state.io_state == 1) {
            if (fflush(file) != 0) result = -1;
        }
        file = (i < 3) ? &data_0213c238[i++] : NULL;
    } while (file != NULL);
    return result;
}

double nan(const char *unused) {
    return _f2d(data_0213c320);
}

void abort(void) {
    raise(1);
    data_0220014c = 1;
    exit(1);
}

void exit(s32 status) {
    if (data_0220014c == 0) {
        __destroy_global_chain();
        if (data_02200144 != NULL) {
            data_02200144();
            data_02200144 = NULL;
        }
    }
    __exit(status);
}

void __exit(s32 status) {
    if (OS_TryLockMutex(&data_02200298[0]) == 0) {
        data_02200250 = data_021fcc2c.list->id;
        data_02200274 = 1;
    } else if (data_02200250 == data_021fcc2c.list->id) {
        data_02200274++;
    } else {
        OS_LockMutex(&data_02200298[0]);
        data_02200250 = data_021fcc2c.list->id;
        data_02200274 = 1;
    }
    while (data_02200148 > 0) {
        data_02200150[--data_02200148]();
    }
    if (--data_02200274 == 0) {
        OS_UnlockMutex(&data_02200298[0]);
    }
    if (data_02200140 != NULL) {
        data_02200140();
        data_02200140 = NULL;
    }
    fflush(0);
    _ExitProcess();
}

char *STD_CopyString(char *dst, const char *src) {
    char *r = dst;
    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return r;
}

void STD_CopyLString(char *dst, const char *src, s32 n) {
    s32 i = 0;
    s32 m = n - 1;
    if (m > 0) {
        do {
            dst[i] = *src;
            i++;
            if (*src != 0) src++;
        } while (i < m);
    }
    dst[i] = 0;
}

u32 STD_GetStringLength(const char *s) {
    u32 n = 0;
    while (s[n] != 0) {
        n++;
    }
    return n;
}

char *STD_ConcatenateString(char *dst, const char *src) {
    STD_CopyString(dst + STD_GetStringLength(dst), src);
    return dst;
}

static inline u32 fold16(u32 s) {
    s = (s & 0xffff) + (s >> 16);
    s = s + (s >> 16);
    return (u16)s;
}

u8 MATH_CalcChecksum8(const u8 *p, u32 len) {
    u32 k;
    u32 n;
    u32 blk;
    u32 sum = 0;
    if ((uptr)p & 1) {
        sum += *p++;
        len--;
    }
    n = len >> 17;
    if (n != 0) {
        blk = 0x10000;
        do {
            k = blk;
            n--;
            len -= 0x20000;
            do {
                sum += *(const u16 *)p;
                p += 2;
            } while (--k != 0);
            sum = fold16(sum);
        } while (n != 0);
    }
    n = len >> 1;
    if (n != 0) {
        do {
            sum += *(const u16 *)p;
            p += 2;
        } while (--n != 0);
    }
    if (len & 1) {
        sum += *p;
    }
    sum = fold16(sum);
    sum = (sum & 0xff) + (sum >> 8);
    sum = sum + (sum >> 8);
    return ~sum;
}

void MATHi_CRC8InitTable(u8 *table, u32 poly) {
    u32 r, i, j;
    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 0x80) r = poly ^ (r << 1);
            else r = r << 1;
        }
        table[i] = r;
    }
}

void MATHi_CRC8Update(const u8 *table, u8 *crc, const u8 *data, u32 len) {
    u32 c = *crc;
    u32 i;
    for (i = 0; i < len; i++) {
        c = table[(c ^ *data) & 0xff];
        data++;
    }
    *crc = c;
}

void MATHi_CRC16InitTableRev(u16 *table, u32 poly) {
    u32 r, i, j;
    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) r = poly ^ (r >> 1);
            else r = r >> 1;
        }
        table[i] = r;
    }
}

void MATHi_CRC16UpdateRev(const u16 *table, u16 *crc, const u8 *data, u32 len) {
    u32 c = *crc;
    u32 i;
    for (i = 0; i < len; i++) {
        c = table[(c ^ *data) & 0xff] ^ (c >> 8);
        data++;
    }
    *crc = c;
}

void MATHi_CRC32InitTableRev(u32 *table, u32 poly) {
    u32 r, i, j;
    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) r = poly ^ (r >> 1);
            else r = r >> 1;
        }
        table[i] = r;
    }
}

void MATHi_CRC32UpdateRev(const u32 *table, u32 *crc, const u8 *data, u32 len) {
    u32 c = *crc;
    u32 i;
    for (i = 0; i < len; i++) {
        c = table[(c ^ *data) & 0xff] ^ (c >> 8);
        data++;
    }
    *crc = c;
}

u8 MATH_CalcCRC8(const u8 *table, const void *data, u32 len) {
    u8 crc = 0;
    MATHi_CRC8Update(table, &crc, data, len);
    return crc;
}

u16 MATH_CalcCRC16(const u16 *table, const void *data, u32 len) {
    u16 crc = 0;
    MATHi_CRC16UpdateRev(table, &crc, data, len);
    return crc;
}

u32 MATH_CalcCRC32(const u32 *table, const void *data, u32 len) {
    u32 crc = 0xffffffff;
    MATHi_CRC32UpdateRev(table, &crc, data, len);
    return ~crc;
}

void MATH_CalcSHA1(void *digest, const void *data, u32 len) {
    u8 ctx[0x68];
    DGT_Hash2Reset(ctx);
    DGT_Hash2SetSource(ctx, data, len);
    DGT_Hash2GetDigest(ctx, digest);
}

u32 MATH_CountPopulation(u32 x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0xff;
}

void CTRDG_Init(void) {
    if (data_0220005c) return;
    data_0220005c = 1;
    CTRDGi_InitCommon();
    PXI_Init();
    while (PXI_IsCallbackReady(13, 1) == 0) {
    }
    PXI_SetFifoRecvCallback(13, CTRDGi_CallbackForInitModuleInfo);
    CTRDGi_InitModuleInfo();
    PXI_SetFifoRecvCallback(13, 0);
    PXI_SetFifoRecvCallback(13, CTRDGi_PulledOutCallback);
    data_02200060 = 0;
}

void CTRDGi_InitModuleInfo(void) {
    u32 saved[2];
    Cycle cyc;
    u32 irq;
    u32 ex;
    u32 ime;
    int i;
    Work *w;
    Buf *b;
    if (data_02200058) return;
    data_02200058 = 1;
    if ((IO_R(&REG300) & 1) == 0) return;
    irq = OS_SetIrqMask(0x40000);
    ime = IO_R(&REG208);
    IO_W(&REG208, 1);
    CTRDGi_LockByProcessor(data_02200054[1], saved);
    ex = (IO_R(&REG204) & 0x8000) >> 15;
    CTRDGi_ChangeLatestAccessCycle(&cyc);
    IO_W(&REG204, (u16)(IO_R(&REG204) & ~0x8000));
    DC_InvalidateRange((u8 *)&data_02200080 + 0x80, 0x40);
    MI_DmaCopy16(1, 0x08000080, (u8 *)&data_02200080 + 0x80, 0x40);
    IO_W(&REG204, (u16)((IO_R(&REG204) & ~0x8000) | (ex << 15)));
    CTRDGi_RestoreAccessCycle(&cyc);
    CTRDGi_UnlockByProcessor(data_02200054[1], saved);
    b = &data_02200080;
    *HW_SYSWORK(u16, ctrdgModuleInfo) = b->f_be;
    for (i = 0; i < 3; i++) {
        (HW_SYSWORK_AT(u8, ctrdgModuleInfo, 0x2))[i] = b->f_b5[i];
    }
    w = HW_SYSWORK(Work, ctrdgModuleInfo);
    w->c = b->f_b0;
    w->d = b->f_ac;
    MIi_CpuCopy32(0xffff0020, data_02200084, 0x9c);
    DC_FlushAll();
    CTRDGi_SendtoPxi(((((uptr)&data_02200080 - 0x02000000) >> 5) << 6) | 1);
    while (data_02200054[0] != 1) {
        WaitByLoop(1);
    }
    (void)IO_R(&REG208);
    IO_W(&REG208, (u16)ime);
    OS_SetIrqMask(irq);
}

void CTRDGi_CallbackForInitModuleInfo(u32 tag, u32 data) {
    if ((data & 0x3f) == 1) {
        data_02200054[0] = 1;
    } else {
        Fatal_Trap();
    }
}

void CTRDGi_PulledOutCallback(u32 tag, u32 data) {
    if ((data & 0x3f) == 0x11) {
        BOOL r = 0;
        if (data_02200060) r = data_02200060();
        if (r == 0) return;
        CTRDG_TerminateForPulledOut();
    } else {
        Fatal_Trap();
    }
}

void CTRDG_TerminateForPulledOut(void) {
    CTRDGi_SendtoPxi(2);
    Fatal_Trap();
}

void CTRDGi_InitCommon(void) {
    u32 zero = 0;
    CpuSet(&zero, data_02200054, 0x05000001);
    data_02200054[1] = (u16)OS_GetLockID();
}

void CTRDGi_ChangeLatestAccessCycle(Cycle *p) {
    p->c1 = (IO_R(&REG204) & 0xc) >> 2;
    p->c2 = (IO_R(&REG204) & 0x10) >> 4;
    IO_W(&REG204, (u16)((IO_R(&REG204) & ~0xc) | 0xc));
    IO_W(&REG204, (u16)(IO_R(&REG204) & ~0x10));
}

void CTRDGi_RestoreAccessCycle(Cycle *p) {
    IO_W(&REG204, (u16)((p->c1 << 2) | (IO_R(&REG204) & ~0xc)));
    IO_W(&REG204, (u16)((p->c2 << 4) | (IO_R(&REG204) & ~0x10)));
}

extern u8 data_0220034c[0x100], data_0220044c[0x100], data_0220054c[0x100];
int __read_console(u32 handle, u8 *buffer, size_t *count, void *idle_proc);
int __write_console(u32 handle, u8 *buffer, size_t *count, void *idle_proc);
int __close_console(u32 handle);
u8 data_0220054c[0x100];
u8 data_0220044c[0x100];
u8 data_0220034c[0x100];
FILE data_0213c238[3] = {
    {0, {0, 1, 1, 2, 0, 0}, {0, 0}, 0, 0, {0}, {0}, {0}, 0, data_0220054c, 0x100, data_0220054c, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0},
    {1, {0, 2, 1, 2, 0, 0}, {0, 0}, 0, 0, {0}, {0}, {0}, 0, data_0220044c, 0x100, data_0220044c, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0},
    {2, {0, 2, 0, 2, 0, 0}, {0, 0}, 0, 0, {0}, {0}, {0}, 0, data_0220034c, 0x100, data_0220034c, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0},
};
