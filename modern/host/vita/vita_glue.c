// PS Vita entry point. The VPK's eboot.bin starts here with no arguments, so this finds the player's game
// under ux0:/data/vitaWW, sets up a log file next to it, and hands the path to host_main (modern/host/main.c).
// Everything after that - the window, input, audio, the frame loop - is the shared SDL frontend
// (modern/host/frontend_sdl.c), the same code the desktop and iOS builds use.
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "vita.h"

// CI writes build_id.h with the commit short SHA so every log says exactly which build produced it
#if defined(__has_include)
#  if __has_include("build_id.h")
#    include "build_id.h"
#  endif
#endif
#ifndef VITA_BUILD
#define VITA_BUILD "dev"
#endif

#define DATA_DIR "ux0:/data/vitaWW"
#define README   DATA_DIR "/Put your Animal Crossing Wild World .nds file here.txt"

void vita_fatal_message(const char *text) {
    // the message box needs SDL's video subsystem; bring it up if the game never got that far
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "vitaWW", text, NULL);
}

static int ends_with_nds(const char *name) {
    size_t n = strlen(name);
    return n > 4 && strcasecmp(name + n - 4, ".nds") == 0;
}

// the first .nds in the folder, by name (the iOS glue likewise expects a single game file there)
static int find_rom(char *out, size_t cap) {
    DIR *d = opendir(DATA_DIR);
    if (!d) return 0;
    struct dirent *e;
    char best[256] = "";
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.' || !ends_with_nds(e->d_name)) continue;
        if (best[0] == 0 || strcmp(e->d_name, best) < 0)
            snprintf(best, sizeof best, "%s", e->d_name);
    }
    closedir(d);
    if (best[0] == 0) return 0;
    snprintf(out, cap, DATA_DIR "/%s", best);
    return 1;
}

static void open_log(void) {
    rename(DATA_DIR "/acww-log.txt", DATA_DIR "/acww-log-previous.txt");
    // (newlib on the Vita has no dup2: the game logs to stderr, so only stderr is redirected to the file)
    if (!freopen(DATA_DIR "/acww-log.txt", "w", stderr)) return;
    setvbuf(stderr, NULL, _IONBF, 0);
    fprintf(stderr, "vita: vitaWW starting (build %s)\n", VITA_BUILD);
}

static void ensure_readme(void) {
    FILE *f = fopen(README, "r");
    if (f) { fclose(f); return; }
    f = fopen(README, "w");
    if (!f) return;
    fputs("Copy your own dump of Animal Crossing: Wild World (USA, Rev 1) into ux0:/data/vitaWW -\n"
          "one file ending in .nds - then start vitaWW again.\n\n"
          "The game saves next to it (same name, ending in .sav). Keep a backup of that file somewhere safe.\n", f);
    fclose(f);
}

int main(int argc, char **argv) {
    SDL_SetMainReady();
    mkdir("ux0:/data", 0777);
    mkdir(DATA_DIR, 0777);
    open_log();
    ensure_readme();
    chdir(DATA_DIR);

    static char path[1024];
    if (!find_rom(path, sizeof path)) {
        fprintf(stderr, "vita: no .nds found in %s\n", DATA_DIR);
        vita_fatal_message("No game found.\n\nCopy your Animal Crossing: Wild World (USA) .nds file into\n"
                           "ux0:/data/vitaWW (for example with VitaShell), then start vitaWW again.");
        return 1;
    }
    fprintf(stderr, "vita: the game: %s\n", path);

    static char *args[3];
    args[0] = (argc > 0 && argv && argv[0]) ? argv[0] : "vitaWW";
    args[1] = path;
    args[2] = NULL;
    return host_main(2, args);
}
