#ifndef NET_IPHEADER_H
#define NET_IPHEADER_H

#include "types.h"


struct IpHeader {
    u8 verIhl;
    u8 b1;
    u16 totalLength;
    u8 b4;
    u8 b5;
    u16 fragField;
    u8 b8;
    u8 b9;
    u16 ha;
    u16 srcAddrHi;
    u16 srcAddrLo;
    u16 dstAddrHi;
    u16 dstAddrLo;
};

struct UdpHeader {
    u16 srcPort;
    u16 dstPort;
    u16 length;
    u16 checksum;
};

struct TcpHeader {
    u16 srcPort;
    u16 dstPort;
    u16 h4;
    u16 h6;
    u16 ackHi;
    u16 ackLo;
    u8 dataOffset;
    u8 tcpFlags;
    u16 window;
};

#endif
