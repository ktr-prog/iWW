# vitaWW

A native PlayStation Vita port of *Animal Crossing: Wild World*, built from the DS decompilation recompiled to native ARM (not an emulator).

**Work in progress.**

## Goals

- Single-screen view, 4:3, running on real Vita hardware
- GPU (GXM) accelerated rendering, targeting 60 FPS
- Accepts EU and US `.sav` files

## Installing

Install the `.vpk` (from the latest **Vita** CI run's artifacts) with VitaShell. Put your own copy of the game at:

```
ux0:/data/vitaWW/<your game>.nds
```

See [`docs/vita.md`](docs/vita.md) for details and options (`ux0:/data/vitaWW/acww-options.txt`).

## Building

```
python3 tools/configure_host.py --os vita
ninja -f build_host_vita.ninja
python3 tools/vita_package.py
```

Requires [VitaSDK](https://vitasdk.org/) (`$VITASDK` set) and SDL2 built for `arm-vita-eabi`.

## Legal

This project contains no game assets. You must supply your own legally-obtained copy of the game.
