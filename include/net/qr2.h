#ifndef NET_QR2_H
#define NET_QR2_H

#include "types.h"
#include "net/SockAddrIn.h"


struct qr2_buffer_s {
    /* 0x00 */ u8 buffer[0x800];
    /* 0x800 */ s32 len;
};

struct qr2_keybuffer_s {
    /* 0x00 */ u8 keys[0x100];
    /* 0x100 */ s32 numkeys;
};

typedef void (*qr2_serverkeycallback_t)(u32, qr2_buffer_s *, void *);
typedef void (*qr2_playerteamkeycallback_t)(u32, s32, qr2_buffer_s *, void *);
typedef void (*qr2_keylistcallback_t)(s32, qr2_keybuffer_s *, void *);
typedef s32 (*qr2_countcallback_t)(s32, void *);
typedef void (*qr2_adderrorcallback_t)(s32, const char *, void *);
typedef void (*qr2_publicaddresscallback_t)(u32, u32, void *);
typedef void (*qr2_natnegcallback_t)(u32, void *);
typedef void (*qr2_clientmessagecallback_t)(u8 *, u32, void *);
typedef void (*qr2_cdkeyprocesscallback_t)(u8 *, u32, void *);

struct qr2_implementation_s {
    /* 0x00 */ s32 hbsock;
    /* 0x04 */ char gamename[0x40];
    /* 0x44 */ char secret_key[0x40];
    /* 0x84 */ u8 instance_key[4];
    /* 0x88 */ qr2_serverkeycallback_t server_key_callback;
    /* 0x8c */ qr2_playerteamkeycallback_t player_key_callback;
    /* 0x90 */ qr2_playerteamkeycallback_t team_key_callback;
    /* 0x94 */ qr2_keylistcallback_t key_list_callback;
    /* 0x98 */ qr2_countcallback_t playerteam_count_callback;
    /* 0x9c */ qr2_adderrorcallback_t adderror_callback;
    /* 0xa0 */ qr2_natnegcallback_t nn_callback;
    /* 0xa4 */ qr2_clientmessagecallback_t cm_callback;
    /* 0xa8 */ qr2_publicaddresscallback_t pa_callback;
    /* 0xac */ u32 lastheartbeat;
    /* 0xb0 */ u32 lastka;
    /* 0xb4 */ s32 userstatechangerequested;
    /* 0xb8 */ s32 listed_state;
    /* 0xbc */ s32 ispublic;
    /* 0xc0 */ s32 qport;
    /* 0xc4 */ s32 read_socket;
    /* 0xc8 */ s32 nat_negotiate;
    /* 0xcc */ SockAddrIn hbaddr;
    /* 0xd4 */ qr2_cdkeyprocesscallback_t cdkeyprocess;
    /* 0xd8 */ s32 client_message_keys[10];
    /* 0x100 */ s32 cur_message_key;
    /* 0x104 */ u32 publicip;
    /* 0x108 */ u16 publicport;
    /* 0x10c */ void *udata;
};

#endif
