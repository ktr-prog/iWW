char gHostGameDataBegin[1] = {1};
char gHostGameBssBegin[1];
static char sGameStaticBssBegin[1] __attribute__((used));
char *host_game_static_bss_begin(void) { return sGameStaticBssBegin; }
