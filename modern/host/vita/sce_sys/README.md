# LiveArea assets (sce_sys)

`tools/vita_package.py` bundles everything in this directory (except notes like this one) into the `.vpk` under
`sce_sys/`. Drop the PS Vita LiveArea assets here and they are picked up automatically:

- `icon0.png` — 128×128 app icon
- `livearea/contents/template.xml` — the LiveArea layout
- `livearea/contents/bg.png` — 840×500 background
- `livearea/contents/startup.png` — 280×158 startup image

None are strictly required to install and run, so the Vita CI (`.github/workflows/vita.yml`) generates a plain
placeholder `icon0.png` when none is committed here. Replace it with real artwork whenever you like.
