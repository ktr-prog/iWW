char gHostStateDataEnd[1] = {1};
char gHostStateBssEnd[1];
static char sStateStaticBssEnd[1] __attribute__((used));
char *host_state_static_bss_end(void) { return sStateStaticBssEnd; }
