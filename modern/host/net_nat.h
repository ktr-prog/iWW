#ifndef HOST_NET_NAT_H
#define HOST_NET_NAT_H

#include "host.h"

#define NAT_AP_SSID "ACWW Wiimmfi"
extern const u8 kNatGatewayMac[6];

int nat_supported(void);
void nat_start(const u8 dsMac[6]);
void nat_stop(void);
void nat_from_ds(const u8 dst[6], const u8 *llc, u32 len);
void nat_poll(void);
int nat_take(u8 *buf, u32 cap, u32 *len);

#endif
