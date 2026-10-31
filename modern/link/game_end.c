char gHostGameDataEnd[1] = {1};
char gHostGameBssEnd[1];
static char sGameStaticBssEnd[1] __attribute__((used));
char *host_game_static_bss_end(void) { return sGameStaticBssEnd; }
