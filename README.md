<img width="40" height="40" alt="image" src="https://github.com/user-attachments/assets/1ca8398f-cb7a-4fb6-ba98-5347d4bfa46d" />


iWW

Screenshots:

<img width="148" height="226" alt="image" src="https://github.com/user-attachments/assets/c66216a9-41ed-4e24-81d5-d5ba9b29e6d0" />
<img width="148" height="226" alt="image" src="https://github.com/user-attachments/assets/8fbf122f-96ae-457e-9c3f-002f8b3cfd42" />
<img width="148" height="226" alt="image" src="https://github.com/user-attachments/assets/60b5d1b0-c757-4e62-9cc6-0961cf06fbaf" />

(WIP)

Features:

- 60 FPS (Experimental WIP)
- Solo screen view (Experimental WIP)
- No screen borders
- Accepts EU and US .sav files
- Seamless transition between touchscreen and button input
- Improved touch input delay
- Improved drawing distance
- Local play - With other copies on the same Wi-Fi network
- Online play - Nintendo Wi-Fi Connection through [Wiimmfi](https://wiimmfi.de/)
- Various bug fixes
- Circle Pad - Credit/Source: [https://gbatemp.net/threads/circle-pad-patches-for-super-mario-64-ds-and-other-games-in-twilightmenu-with-twpatcher-and-rtcom.623267/)](https://gbatemp.net/threads/circle-pad-patches-for-super-mario-64-ds-and-other-games-in-twilightmenu-with-twpatcher-and-rtcom.623267/)
- Resetti Toggle

Supported version (user needs to provide .nds file in Files app):

| Version        | Game code | SHA-1                                      |
| -------------- | --------- | ------------------------------------------ |
| USA (Rev 1)    | `ADME`    | `77fde3e30e1e6068395d1f96ea63be569b61c351` |

Platforms:

- iOS (**iWW**) — an unsigned `.ipa` for sideloading (see `docs/ios.md`); CI: Actions > iOS.
- PS Vita (**vitaWW**) — a homebrew `.vpk` (see `docs/vita.md`); CI: Actions > Vita. **Work in progress** — the
  build and packaging are set up; it still needs validation on real hardware.

Both are built from the one shared game core in `src/`/`include/`/`modern/`, so a bug fix made once applies to
every platform.
