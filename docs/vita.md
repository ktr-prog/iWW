# PS Vita port

A native PlayStation Vita build of iWW, packaged as a homebrew `.vpk`. It is built from the same shared game core
as the iOS and desktop builds (`src/`, `include/`, `modern/`), so bug fixes made once apply everywhere — the Vita
adds only its own frontend glue, toolchain wiring, and packaging.

**Status: work in progress.** The build, the 32-bit ARM support, the stack switch, and the packaging are in place
and the game core compiles cleanly for ARMv7; what remains is validation on real hardware (see "What still needs
doing").

## How it fits together

The Vita has no WebGPU/Vulkan/Metal, so — exactly like the iOS build — it does **not** use the GPU 3D renderer
(`modern/host/gpu3d_wgpu.c`). Instead it uses the CPU renderers (`modern/host/gpu2d`, `gpu3d`) and presents the
finished frame through SDL2's own renderer, which on the Vita is backed by GXM. SDL2 (from the VitaSDK) also
provides the window, audio, the controller (the Vita's physical buttons), and the front touchscreen (the DS
stylus), so the shared `modern/host/frontend_sdl.c` runs almost unchanged — the Vita takes the same non-iOS code
path the desktop build uses.

Vita-specific parts:

- `modern/host/vita/vita_glue.c` — the entry point. The `.vpk` launches with no arguments, so this finds the
  player's `.nds` under `ux0:/data/iWW`, opens a log beside it, and calls `host_main` (the shared main in
  `modern/host/main.c`, renamed there for `--os vita`, as on iOS).
- `modern/host/vita/sce_sys/` — LiveArea assets (icon, backgrounds) bundled into the `.vpk`.
- `modern/host/coro_switch.S` / `coro.c` — an ARMv7 (EABI) path for the game thread's stack switch.
- `tools/configure_host.py --os vita` — the VitaSDK cross build.
- `tools/vita_package.py` — turns the built ELF into a `.vpk`.
- `.github/workflows/vita.yml` — CI that installs the VitaSDK, builds, and uploads `iWW-Vita` (the `.vpk`).

## Building locally

Needs the [VitaSDK](https://vitasdk.org) with SDL2 installed (`vdpm sdl2` and its dependencies), and `$VITASDK`
set:

```sh
export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH
python3 tools/configure_host.py --os vita      # writes build_host_vita.ninja
ninja -f build_host_vita.ninja                 # builds build/hostvita_usa/acww (an ARM ELF)
python3 tools/vita_package.py build/hostvita_usa/acww build/vita/iWW.vpk
```

CI does the same (it installs the VitaSDK first) — download the `iWW-Vita` artifact from an Actions run for a
ready `.vpk`.

## Installing and running

1. Install `iWW.vpk` on the Vita (e.g. with VitaShell: press `Circle`/`X` on the file and install).
2. Copy your own dump of Animal Crossing: Wild World (USA, Rev 1 — `ADME`,
   SHA-1 `77fde3e30e1e6068395d1f96ea63be569b61c351`) into `ux0:/data/iWW/`, as a single file ending in `.nds`.
3. Launch iWW. The game saves next to the ROM (same name, ending in `.sav`) — keep a backup.

Controls: the Vita's buttons map through SDL's controller; the front touchscreen is the DS touch screen/stylus;
the left stick is the Circle Pad.

## What still needs doing (on-hardware iteration)

These are the parts that can only be shaken out on a device or against the real SDK:

- **ABI validation.** The ARM build uses the AAPCS small-struct return convention (the i386 reference uses
  `-fpcc-struct-return`). The game's struct layouts are checked by its `static_assert`s, but struct *return*
  behaviour should be validated against the reference build the way iOS's arm64 ABI was (`tools/apple_abi_cc.py`,
  `docs/portability.md`). If something misbehaves subtly, this is the first suspect.
- **The SDL2-vita link set and input mapping.** `configure_host.py` takes the libraries from the VitaSDK's
  `arm-vita-eabi-pkg-config --libs sdl2`; the exact controller/touch behaviour may need tuning for the Vita's
  single screen (the two DS screens are letterboxed into 960×544 by SDL's logical size).
- **The stack switch** (`coro_switch.S` ARMv7 path) assembles and matches the layout `coro.c` builds, but has not
  yet been run on hardware.
- **Online play.** Wiimmfi needs the Vita's sockets — add `-lSceNet_stub -lSceNetCtl_stub` (and the matching init)
  to the link in `configure_host.py` when bringing that up.
- **LiveArea art.** CI generates a placeholder `icon0.png`; drop real assets into `modern/host/vita/sce_sys/`.
- **Screen-dim/suspend.** Consider a per-frame `sceKernelPowerTick` so the screen doesn't dim during play.
