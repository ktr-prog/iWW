#ifndef NET_GPIINFO_H
#define NET_GPIINFO_H

#include "types.h"


struct GPIInfoCache {
    /* 0x00 */ char *nick;
    /* 0x04 */ char *uniquenick;
    /* 0x08 */ char *email;
    /* 0x0c */ char *firstname;
    /* 0x10 */ char *lastname;
    /* 0x14 */ char *homepage;
    /* 0x18 */ s32 icquin;
    /* 0x1c */ char zipcode[0xb];
    /* 0x27 */ char countrycode[3];
    /* 0x2c */ s32 longitude;
    /* 0x30 */ s32 latitude;
    /* 0x34 */ char place[0x80];
    /* 0xb4 */ s32 birthday;
    /* 0xb8 */ s32 birthmonth;
    /* 0xbc */ s32 birthyear;
    /* 0xc0 */ s32 sex;
    /* 0xc4 */ s32 publicmask;
    /* 0xc8 */ char *aimname;
    /* 0xcc */ s32 pic;
    /* 0xd0 */ s32 occupationid;
    /* 0xd4 */ s32 industryid;
    /* 0xd8 */ s32 incomeid;
    /* 0xdc */ s32 marriedid;
    /* 0xe0 */ s32 childcount;
    /* 0xe4 */ s32 interests1;
    /* 0xe8 */ s32 ownership1;
    /* 0xec */ s32 conntypeid;
};

struct GPIInfoCacheCopy {
    /* 0x00 */ s64 v[30];
};

struct GPGetInfoResponseArg {
    /* 0x000 */ s32 result;
    /* 0x004 */ s32 profile;
    /* 0x008 */ char nick[0x1f];
    /* 0x027 */ char uniquenick[0x15];
    /* 0x03c */ char email[0x33];
    /* 0x06f */ char firstname[0x1f];
    /* 0x08e */ char lastname[0x1f];
    /* 0x0ad */ char homepage[0x4c];
    /* 0x0fc */ s32 icquin;
    /* 0x100 */ char zipcode[0xb];
    /* 0x10b */ char countrycode[3];
    /* 0x110 */ s32 longitude;
    /* 0x114 */ s32 latitude;
    /* 0x118 */ char place[0x80];
    /* 0x198 */ s32 birthday;
    /* 0x19c */ s32 birthmonth;
    /* 0x1a0 */ s32 birthyear;
    /* 0x1a4 */ s32 sex;
    /* 0x1a8 */ s32 publicmask;
    /* 0x1ac */ char aimname[0x33];
    /* 0x1df */ u8 pad_1df[1];
    /* 0x1e0 */ s32 pic;
    /* 0x1e4 */ s32 occupationid;
    /* 0x1e8 */ s32 industryid;
    /* 0x1ec */ s32 incomeid;
    /* 0x1f0 */ s32 marriedid;
    /* 0x1f4 */ s32 childcount;
    /* 0x1f8 */ s32 interests1;
    /* 0x1fc */ s32 ownership1;
    /* 0x200 */ s32 conntypeid;
};

#endif
