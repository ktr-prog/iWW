#ifndef NITRO_FS_H
#define NITRO_FS_H

#include "types.h"
#include "sys/OSThread.h"


typedef struct FSArc FSArc;
typedef struct FSFile FSFile;

typedef int (*FSIoFunc)(FSArc *, void *, u32, u32);

typedef struct FSDirPos {
    /* 0x0 */ FSArc *arc;
    /* 0x4 */ union {
        u32 file_id;
        struct {
            u16 own_id;
            u16 index;
        } d;
    } u;
    /* 0x8 */ u32 pos;
} FSDirPos;

typedef struct FSFileID {
    /* 0x0 */ FSArc *arc;
    /* 0x4 */ u32 file_id;
} FSFileID;

typedef struct FSEntry {
    /* 0x00 */ FSDirPos pos;
    /* 0x0c */ u32 is_dir;
    /* 0x10 */ u32 name_len;
    /* 0x14 */ char name[128];
} FSEntry;

typedef struct FSStream {
    /* 0x0 */ FSArc *arc;
    /* 0x4 */ u32 pos;
} FSStream;

typedef struct FSROMTable {
    /* 0x0 */ u32 offset;
    /* 0x4 */ u32 length;
} FSROMTable;

typedef struct FSOvtCache {
    /* 0x0 */ u8 *ptr;
    /* 0x4 */ u32 size;
} FSOvtCache;

typedef struct FSOverlayInfoHeader {
    /* 0x00 */ u32 id;
    /* 0x04 */ u32 ram_address;
    /* 0x08 */ u32 ram_size;
    /* 0x0c */ u32 bss_size;
    /* 0x10 */ void (**sinit_init)(void);
    /* 0x14 */ void (**sinit_init_end)(void);
    /* 0x18 */ u32 file_id;
    /* 0x1c */ u32 compressed : 24;
    /* 0x1f */ u32 flag : 8;
} FSOverlayInfoHeader;

typedef struct FSOverlayInfo {
    /* 0x00 */ FSOverlayInfoHeader header;
    /* 0x20 */ u32 target;
    /* 0x24 */ u32 start;
    /* 0x28 */ u32 length;
} FSOverlayInfo;

struct FSFile {
    /* 0x00 */ FSFile *prev;
    /* 0x04 */ FSFile *next;
    /* 0x08 */ FSArc *arc;
    /* 0x0c */ volatile u32 stat;
    /* 0x10 */ u32 command;
    /* 0x14 */ u32 error;
    /* 0x18 */ OSThreadQueue queue;
    /* 0x20 */ union {
        struct {
            /* 0x20 */ u32 own_id;
            /* 0x24 */ s32 start;
            /* 0x28 */ s32 end;
            /* 0x2c */ s32 pos;
        } file;
        struct {
            /* 0x20 */ FSDirPos pos;
            /* 0x2c */ u32 parent;
        } dir;
    } prop;
    /* 0x30 */ union {
        struct {
            /* 0x30 */ u32 w30;
            /* 0x34 */ u32 w34;
            /* 0x38 */ u32 w38;
            /* 0x3c */ u32 w3c;
            /* 0x40 */ u32 w40;
            /* 0x44 */ FSDirPos *w44;
        } w;
        FSDirPos pos;
        struct {
            void *dst;
            u32 len_org;
            u32 len;
        } readfile;
        struct {
            FSDirPos pos;
            const char *path;
            u32 find_directory;
            void *result;
        } findpath;
        struct {
            FSFileID id;
        } openfilefast;
        struct {
            u32 top;
            u32 bottom;
            u32 index;
        } openfiledirect;
        struct {
            void *buf;
            u32 buf_size;
            u16 len;
            u16 dirid;
        } path;
        struct {
            FSEntry *ent;
            u32 skip;
        } rdent;
        struct {
            u32 a30;
            u16 id34;
            u16 id36;
            u32 a38;
        } rd;
    } arg;
};

struct FSArc {
    /* 0x00 */ u32 name;
    /* 0x04 */ FSArc *next;
    /* 0x08 */ FSArc *prev;
    /* 0x0c */ OSThreadQueue queue;
    /* 0x14 */ OSThreadQueue queue2;
    /* 0x1c */ volatile u32 flag;
    /* 0x20 */ struct {
        FSFile *prev;
        FSFile *next;
    } list;
    /* 0x28 */ uptr base;
    /* 0x2c */ u32 fat;
    /* 0x30 */ u32 fat_size;
    /* 0x34 */ u32 fnt;
    /* 0x38 */ u32 fnt_size;
    /* 0x3c */ u32 fat_orig;
    /* 0x40 */ u32 fnt_orig;
    /* 0x44 */ void *load_mem;
    /* 0x48 */ FSIoFunc read_orig;
    /* 0x4c */ FSIoFunc write;
    /* 0x50 */ FSIoFunc read;
    /* 0x54 */ int (*proc)(FSFile *, u32);
    /* 0x58 */ u32 proc_mask;
};

#endif
