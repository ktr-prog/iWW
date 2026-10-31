#ifndef NET_DWCMATCHCOMMANDHEADER_H
#define NET_DWCMATCHCOMMANDHEADER_H

#include "types.h"


struct DwcMatchCommandHeader {
    /* 0x00 */ u8 magic[4];
    /* 0x04 */ u32 version;
    /* 0x08 */ u8 command;
    /* 0x09 */ u8 argsSize;
    /* 0x0a */ u16 senderPort;
    /* 0x0c */ u32 senderIp;
    /* 0x10 */ u32 senderProfileId;
};

#endif
