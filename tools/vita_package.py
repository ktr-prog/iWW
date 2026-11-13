#!/usr/bin/env python3
"""Package the Vita build into a .vpk for installation (docs/vita.md).

Input: the ELF built by build_host_vita.ninja (e.g. build/hostvita_usa/acww), which must keep its relocations
(configure_host.py links it with -Wl,-q). Output: a .vpk - a zip holding eboot.bin, sce_sys/param.sfo and whatever
LiveArea assets (icon, backgrounds) are in --assets.

Needs VitaSDK's vita-elf-create, vita-make-fself, vita-mksfoex and vita-pack-vpk (on the PATH, or under $VITASDK/bin).
No game data is used or needed: the player adds their own copy of the game under ux0:/data/iWW on the device.
"""
import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def tool(name):
    vs = os.environ.get("VITASDK")
    if vs and os.path.exists(f"{vs}/bin/{name}"):
        return f"{vs}/bin/{name}"
    found = shutil.which(name)
    if found:
        return found
    sys.exit(f"vita_package.py: {name} not found (set $VITASDK, or add VitaSDK's bin to the PATH)")


def run(*argv):
    print("  " + " ".join(str(a) for a in argv))
    subprocess.run([str(a) for a in argv], check=True)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("elf", help="the ELF from build_host_vita.ninja")
    p.add_argument("out", help="the .vpk to write")
    p.add_argument("--title-id", default="VWWW00001", help="9-character title id (default VWWW00001)")
    p.add_argument("--title", default="vitaWW", help="the name shown in the LiveArea")
    p.add_argument("--assets", default="modern/host/vita/sce_sys",
                   help="a sce_sys directory (icon0.png, livearea/...); whatever is there is bundled")
    args = p.parse_args()
    if not os.path.exists(args.elf):
        sys.exit(f"vita_package.py: no {args.elf} (build it: ninja -f build_host_vita.ninja)")
    if len(args.title_id) != 9:
        sys.exit("vita_package.py: --title-id must be exactly 9 characters")

    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        velf = f"{tmp}/eboot.velf"
        eboot = f"{tmp}/eboot.bin"
        sfo = f"{tmp}/param.sfo"
        # the ELF -> a Vita ELF (velf) -> a signed fake-self eboot.bin (-s: no extra permissions, for homebrew)
        run(tool("vita-elf-create"), args.elf, velf)
        run(tool("vita-make-fself"), "-s", velf, eboot)
        run(tool("vita-mksfoex"), "-s", f"TITLE_ID={args.title_id}", args.title, sfo)

        pack = [tool("vita-pack-vpk"), "-s", sfo, "-b", eboot]
        assets = Path(args.assets)
        if assets.is_dir():
            for f in sorted(assets.rglob("*")):
                # skip notes and dotfiles; bundle everything else at sce_sys/<its path under assets>
                if not f.is_file() or f.name.startswith(".") or f.suffix in (".md", ".txt"):
                    continue
                dst = Path("sce_sys") / f.relative_to(assets)
                pack += ["-a", f"{f}={dst.as_posix()}"]
        pack.append(str(out))
        run(*pack)
    print(f"vita_package.py: wrote {out}")


if __name__ == "__main__":
    main()
