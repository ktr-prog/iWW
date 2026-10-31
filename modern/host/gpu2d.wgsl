// The 2D renderer (modern/host/gpu2d/) on the GPU: per pixel of the two screens, gpu2d.h gpu2d_deferred's two words,
// from what gpu2d records (Gpu2dGpuFrame), by the same rules as gpu2d.c / gpu2d_bg.c / gpu2d_obj.c (each function
// names the C one it follows). Embedded into wgpu_display.c at build time.

@group(0) @binding(0) var<storage, read> vram: array<u32>;
@group(0) @binding(1) var<storage, read> lines: array<u32>;   // [engine][line][GPU2D_LINE_WORDS]
@group(0) @binding(2) var<storage, read> tabs: array<u32>;    // [engine][64]
@group(0) @binding(3) var<storage, read> pals: array<u32>;    // [version][0x200]
@group(0) @binding(4) var<storage, read> oams: array<u32>;    // [version][0x200]
@group(0) @binding(5) var<storage, read> obj0: array<u32>;    // [engine][256]

const LINE_WORDS = 40u;
const VRAM_ZERO = 0xa4000u;

// the engine and line being drawn
var<private> E: u32;
var<private> LB: u32;   // its line's words
var<private> TB: u32;   // its tables
var<private> PB: u32;   // its palettes (engine A's BG palette at +0, OBJ +0x80 words; engine B's +0x100, +0x180)
var<private> OB: u32;   // its OAM

fn v8(off: u32) -> u32 { return (vram[off >> 2u] >> ((off & 3u) * 8u)) & 0xffu; }
fn v16(off: u32) -> u32 { return (vram[off >> 2u] >> ((off & 2u) * 8u)) & 0xffffu; }
fn reg16(o: u32) -> u32 { return (lines[LB + (o >> 2u)] >> ((o & 2u) * 8u)) & 0xffffu; }
fn reg32(o: u32) -> u32 { return lines[LB + (o >> 2u)]; }
fn bgMask() -> u32 { if (E == 0u) { return 0x7ffffu; } return 0x1ffffu; }
fn objMask() -> u32 { if (E == 0u) { return 0x3ffffu; } return 0x1ffffu; }
fn bgOff(a0: u32) -> u32 { let a = a0 & bgMask(); return tabs[TB + (a >> 14u)] + (a & 0x3fffu); }
fn objOff(a0: u32) -> u32 { let a = a0 & objMask(); return tabs[TB + 32u + (a >> 14u)] + (a & 0x3fffu); }
fn bg8(a: u32) -> u32 { return v8(bgOff(a)); }
fn bg16(a: u32) -> u32 { return v16(bgOff(a & ~1u)); }
fn obj8(a: u32) -> u32 { return v8(objOff(a)); }
fn obj16(a: u32) -> u32 { return v16(objOff(a & ~1u)); }
// the palettes as the line sees them: BG colour i, OBJ colour i
fn pal(word: u32, i: u32) -> u32 { return (pals[word + (i >> 1u)] >> ((i & 1u) * 16u)) & 0xffffu; }
fn bgPal(i: u32) -> u32 { return pal(PB, i & 0xffu); }
fn objPal(i: u32) -> u32 { return pal(PB + 0x80u, i & 0xffu); }
fn opaque(c: u32) -> u32 { return (c & 0x7fffu) | 0x8000u; }

// ---- BGs (gpu2d_bg.c)
fn charBase(cnt: u32) -> u32 {
  var b = ((cnt >> 2u) & 15u) * 0x4000u;
  if (E == 0u) { b += ((reg32(0u) >> 24u) & 7u) * 0x10000u; }
  return b;
}
fn mapBase(cnt: u32) -> u32 {
  var b = ((cnt >> 8u) & 31u) * 0x800u;
  if (E == 0u) { b += ((reg32(0u) >> 27u) & 7u) * 0x10000u; }
  return b;
}
// ext_palette: the slot's VRAM offset, or ~0 for the standard palette
fn extPalette(n: u32, cnt: u32) -> u32 {
  if ((reg32(0u) & (1u << 30u)) == 0u) { return 0xffffffffu; }
  var slot = n;
  if (n < 2u && (cnt & 0x2000u) != 0u) { slot += 2u; }
  return tabs[TB + 48u + slot];
}
fn tile8Pixel(cb: u32, entry: u32, px0: u32, py0: u32, ext: u32) -> u32 {
  var px = px0; var py = py0;
  if ((entry & 0x400u) != 0u) { px = 7u - px; }
  if ((entry & 0x800u) != 0u) { py = 7u - py; }
  let idx = bg8(cb + (entry & 0x3ffu) * 64u + py * 8u + px);
  if (idx == 0u) { return 0u; }
  if (ext != 0xffffffffu) { return opaque(v16(ext + ((entry >> 12u) * 256u + idx) * 2u)); }
  return opaque(bgPal(idx));
}
fn textPixel(n: u32, x: u32, line: u32) -> u32 {
  let cnt = reg16(0x08u + 2u * n);
  let hofs = reg16(0x10u + 4u * n) & 0x1ffu; let vofs = reg16(0x12u + 4u * n) & 0x1ffu;
  let cb = charBase(cnt); let mb = mapBase(cnt);
  var wide = 256u; if ((cnt & 0x4000u) != 0u) { wide = 512u; }
  var tall = 256u; if ((cnt & 0x8000u) != 0u) { tall = 512u; }
  let y = (line + vofs) & (tall - 1u);
  var rowBase = mb + (y & 255u) / 8u * 64u;
  if (y >= 256u) { if (wide == 512u) { rowBase += 0x1000u; } else { rowBase += 0x800u; } }
  let sx = (x + hofs) & (wide - 1u);
  var ea = rowBase + (sx & 255u) / 8u * 2u;
  if (sx >= 256u) { ea += 0x800u; }
  let entry = bg16(ea);
  let tile = entry & 0x3ffu;
  var py = y & 7u; if ((entry & 0x800u) != 0u) { py = 7u - py; }
  var px = sx & 7u; if ((entry & 0x400u) != 0u) { px = 7u - px; }
  if ((cnt & 0x80u) != 0u) {
    let idx = bg8(cb + tile * 64u + py * 8u + px);
    if (idx == 0u) { return 0u; }
    let ext = extPalette(n, cnt);
    if (ext != 0xffffffffu) { return opaque(v16(ext + (entry >> 12u) * 512u + idx * 2u)); }
    return opaque(bgPal(idx));
  }
  let b = bg8(cb + tile * 32u + py * 4u + px / 2u);
  var idx = b & 15u; if ((px & 1u) != 0u) { idx = b >> 4u; }
  if (idx == 0u) { return 0u; }
  return opaque(bgPal((entry >> 12u) * 16u + idx));
}
// affine_start + the step to pixel x: the texture coordinates (integer pixels)
fn affineCoords(n: u32, x: u32, mline: u32, line: u32) -> vec2i {
  let r = 0x20u + (n - 2u) * 0x10u;
  let pa = i32(i32(reg16(r) << 16u) >> 16u); let pb = i32(i32(reg16(r + 2u) << 16u) >> 16u);
  let pc = i32(i32(reg16(r + 4u) << 16u) >> 16u); let pd = i32(i32(reg16(r + 6u) << 16u) >> 16u);
  let d = i32(mline) - i32(line);
  let x0 = i32(lines[LB + 28u + 2u * (n - 2u)]) + pb * d;
  let y0 = i32(lines[LB + 29u + 2u * (n - 2u)]) + pd * d;
  return vec2i((x0 + pa * i32(x)) >> 8u, (y0 + pc * i32(x)) >> 8u);
}
fn affineCoord(c: i32, w: i32, wrap: bool) -> i32 {
  if (wrap) { return c & (w - 1); }
  if (c >= 0 && c < w) { return c; }
  return -1;
}
fn affinePixel(n: u32, x: u32, mline: u32, line: u32) -> u32 {
  let cnt = reg16(0x08u + 2u * n);
  let size = 128 << (cnt >> 14u);
  let wrap = (cnt & 0x2000u) != 0u;
  let t = affineCoords(n, x, mline, line);
  let tx = affineCoord(t.x, size, wrap); let ty = affineCoord(t.y, size, wrap);
  if (tx < 0 || ty < 0) { return 0u; }
  let tile = bg8(mapBase(cnt) + u32(ty / 8 * (size / 8) + tx / 8));
  let idx = bg8(charBase(cnt) + tile * 64u + u32(ty & 7) * 8u + u32(tx & 7));
  if (idx == 0u) { return 0u; }
  return opaque(bgPal(idx));
}
fn bitmapPixel(n: u32, x: u32, mline: u32, line: u32, base: u32, w: i32, h: i32, direct: bool) -> u32 {
  let cnt = reg16(0x08u + 2u * n);
  let wrap = (cnt & 0x2000u) != 0u;
  let t = affineCoords(n, x, mline, line);
  let tx = affineCoord(t.x, w, wrap); let ty = affineCoord(t.y, h, wrap);
  if (tx < 0 || ty < 0) { return 0u; }
  let at = u32(ty * w + tx);
  if (direct) {
    let c = bg16(base + at * 2u);
    if ((c & 0x8000u) != 0u) { return opaque(c); }
    return 0u;
  }
  let idx = bg8(base + at);
  if (idx == 0u) { return 0u; }
  return opaque(bgPal(idx));
}
fn extendedPixel(n: u32, x: u32, mline: u32, line: u32) -> u32 {
  let cnt = reg16(0x08u + 2u * n);
  let sz = cnt >> 14u;
  if ((cnt & 0x80u) != 0u) {
    var kW = array<i32, 4>(128, 256, 512, 512); var kH = array<i32, 4>(128, 256, 256, 512);
    return bitmapPixel(n, x, mline, line, ((cnt >> 8u) & 31u) * 0x4000u, kW[sz], kH[sz], (cnt & 4u) != 0u);
  }
  let size = 128 << sz;
  let wrap = (cnt & 0x2000u) != 0u;
  let t = affineCoords(n, x, mline, line);
  let tx = affineCoord(t.x, size, wrap); let ty = affineCoord(t.y, size, wrap);
  if (tx < 0 || ty < 0) { return 0u; }
  let entry = bg16(mapBase(cnt) + u32(ty / 8 * (size / 8) + tx / 8) * 2u);
  return tile8Pixel(charBase(cnt), entry, u32(tx & 7), u32(ty & 7), extPalette(n, cnt));
}
// gpu2d_render_bg_line: BG n's pixel x (BGR555 | 0x8000, 0 transparent)
fn bgPixel(n: u32, x0: u32, line0: u32) -> u32 {
  let dispcnt = reg32(0u);
  let mode = dispcnt & 7u;
  let cnt = reg16(0x08u + 2u * n);
  if ((dispcnt & (0x100u << n)) == 0u) { return 0u; }
  if (E == 1u && mode > 5u) { return 0u; }
  if (n == 0u && E == 0u && (dispcnt & 8u) != 0u) { return 0u; }
  var line = line0; var x = x0;
  if ((cnt & 0x40u) != 0u) {
    let mos = reg16(0x4cu);
    line -= line % (((mos >> 4u) & 15u) + 1u);
    x -= x % ((mos & 15u) + 1u);
  }
  // the kinds (gpu2d_bg.c kBgKinds): 1 text, 2 affine, 3 extended, 4 large
  var kinds = array<u32, 8>(0x1111u, 0x2111u, 0x2211u, 0x3111u, 0x3211u, 0x3311u, 0x0400u, 0u);
  let kind = (kinds[mode] >> (n * 4u)) & 15u;
  if (kind == 1u) { return textPixel(n, x, line); }
  if (kind == 2u) { return affinePixel(n, x, line, line0); }
  if (kind == 3u) { return extendedPixel(n, x, line, line0); }
  if (kind == 4u) {
    var kW = array<i32, 4>(512, 1024, 512, 512); var kH = array<i32, 4>(1024, 512, 256, 512);
    return bitmapPixel(n, x, line, line0, 0u, kW[cnt >> 14u], kH[cnt >> 14u], false);
  }
  return 0u;
}

// ---- OBJs (gpu2d_obj.c): a pixel packed as Gpu2dGpuFrame.obj0's
fn objTexel(dispcnt: u32, a0: u32, a2: u32, u: u32, v: u32, w: u32) -> u32 {
  let tile = a2 & 0x3ffu;
  if (((a0 >> 10u) & 3u) == 3u) {
    var addr: u32;
    if ((dispcnt & 0x40u) != 0u) {
      var step = 128u; if (E == 0u && (dispcnt & (1u << 22u)) != 0u) { step = 256u; }
      addr = tile * step + (v * w + u) * 2u;
    } else if ((dispcnt & 0x20u) != 0u) {
      addr = (tile & 0x1fu) * 0x10u + (tile & 0x3e0u) * 0x80u + v * 512u + u * 2u;
    } else {
      addr = (tile & 0xfu) * 0x10u + (tile & 0x3f0u) * 0x80u + v * 256u + u * 2u;
    }
    let c = obj16(addr);
    if ((c & 0x8000u) != 0u) { return (1u << 16u) | (c & 0x7fffu); }
    return 0u;
  }
  let c256 = (a0 & 0x2000u) != 0u;
  var tb = 32u; if (c256) { tb = 64u; }
  var addr: u32;
  if ((dispcnt & 0x10u) != 0u) { addr = tile * (32u << ((dispcnt >> 20u) & 3u)) + (v / 8u * (w / 8u) + u / 8u) * tb; }
  else { addr = tile * 32u + v / 8u * 1024u + u / 8u * tb; }
  if (c256) {
    let idx = obj8(addr + (v & 7u) * 8u + (u & 7u));
    if (idx == 0u) { return 0u; }
    if ((dispcnt & (1u << 31u)) != 0u) { return (3u << 16u) | ((a2 >> 12u) * 256u + idx); }
    return (2u << 16u) | idx;
  }
  let b = obj8(addr + (v & 7u) * 4u + (u & 7u) / 2u);
  var idx = b & 15u; if ((u & 1u) != 0u) { idx = b >> 4u; }
  if (idx == 0u) { return 0u; }
  return (2u << 16u) | ((a2 >> 12u) * 16u + idx);
}
fn oam16(i: u32) -> u32 { return (oams[OB + (i >> 1u)] >> ((i & 1u) * 16u)) & 0xffffu; }
fn s16(v: u32) -> i32 { return i32(v << 16u) >> 16u; }
// gpu2d_render_obj_line at one pixel
fn objPixel(x: u32, line: u32) -> u32 {
  if (line == 0u) { return obj0[E * 256u + x]; }
  let dispcnt = reg32(0u);
  if ((dispcnt & 0x1000u) == 0u) { return 0u; }
  var kW = array<i32, 12>(8, 16, 32, 64, 16, 32, 32, 64, 8, 8, 16, 32);
  var kH = array<i32, 12>(8, 16, 32, 64, 8, 8, 16, 32, 16, 32, 32, 64);
  var best = 0u; var bestPrio = 4u; var window = 0u;
  var coverKey = 0u; var coverMosaic = 0u;
  for (var i = 0u; i < 128u; i++) {
    let a0 = oam16(i * 4u); let a1 = oam16(i * 4u + 1u); let a2 = oam16(i * 4u + 2u);
    let affine = (a0 & 0x100u) != 0u; let mode = (a0 >> 10u) & 3u; let shape = a0 >> 14u;
    if ((!affine && (a0 & 0x200u) != 0u) || shape == 3u) { continue; }
    let w = kW[shape * 4u + (a1 >> 14u)]; let h = kH[shape * 4u + (a1 >> 14u)];
    var bw = w; var bh = h;
    if (affine && (a0 & 0x200u) != 0u) { bw *= 2; bh *= 2; }
    var rel = i32((line - (a0 & 0xffu)) & 0xffu);
    if (rel >= bh) { continue; }
    var x0 = i32(a1 & 0x1ffu); if (x0 >= 256) { x0 -= 512; }
    let px = i32(x) - x0;
    if (px < 0 || px >= bw) { continue; }
    let mosaic = (a0 & 0x1000u) != 0u && mode != 2u;
    if (mosaic) { rel = i32((lines[LB + 33u] - (a0 & 0xffu)) & 0xffu); }
    let prio = (a2 >> 10u) & 3u;
    if (mode == 3u) {
      if ((a2 >> 12u) == 0u) { continue; }
      if ((dispcnt & 0x60u) == 0x60u) { continue; }
    }
    var u: i32; var v: i32;
    if (affine) {
      let g = ((a1 >> 9u) & 31u) * 16u;
      let pa = s16(oam16(g + 3u)); let pb = s16(oam16(g + 7u)); let pc = s16(oam16(g + 11u)); let pd = s16(oam16(g + 15u));
      let dx = px - bw / 2; let dy = rel - bh / 2;
      u = ((pa * dx + pb * dy) >> 8u) + w / 2;
      v = ((pc * dx + pd * dy) >> 8u) + h / 2;
      if (u < 0 || u >= w || v < 0 || v >= h) { continue; }
    } else {
      u = px; if ((a1 & 0x1000u) != 0u) { u = w - 1 - px; }
      v = rel; if ((a1 & 0x2000u) != 0u) { v = h - 1 - rel; }
    }
    let c = objTexel(dispcnt, a0, a2, u32(u), u32(v), u32(w));
    if (mode != 2u) {
      let key = prio * 128u + i + 1u;
      if (key > coverKey) { coverKey = key; coverMosaic = select(0u, 1u, mosaic); }
    }
    if (c == 0u) { continue; }
    if (mode == 2u) { window = 1u; continue; }
    if (best != 0u && prio >= bestPrio) { continue; }
    var kind = 0u; if (mode == 1u) { kind = 1u; } else if (mode == 3u) { kind = 2u; }
    best = c | (prio << 18u) | (kind << 20u) | ((a2 >> 12u) << 22u) | (select(0u, 1u, mosaic) << 26u);
    bestPrio = prio;
  }
  if (best == 0u) { best = coverMosaic << 26u; }
  return best | (window << 27u);
}
// obj_mosaic_x: a mosaic OBJ pixel shows the first pixel of its run of mosaic pixels in its block
fn objPixelMosaic(x: u32, line: u32, here: u32) -> u32 {
  let w = ((reg16(0x4cu) >> 8u) & 15u) + 1u;
  if (w == 1u || ((here >> 26u) & 1u) == 0u) { return here; }
  var p = x; var o = here;
  loop {
    if (p == 0u || p % w == 0u) { break; }
    let left = objPixel(p - 1u, line);
    if (((left >> 26u) & 1u) == 0u) { break; }
    p -= 1u; o = left;
  }
  if (p == x) { return here; }
  return (o & ~(1u << 26u) & ~(1u << 27u)) | (here & ((1u << 26u) | (1u << 27u)));
}

// ---- compositing (gpu2d.c compose_line, render_line)
fn rgb6(c: u32) -> u32 { return ((c & 31u) << 1u) | (((c >> 5u) & 31u) << 9u) | (((c >> 10u) & 31u) << 17u); }
fn chan(c: u32, i: u32) -> u32 { return (c >> (8u * i)) & 0x3fu; }
fn blend(a: u32, b: u32, eva: u32, evb: u32) -> u32 {
  var o = 0u;
  for (var i = 0u; i < 3u; i++) { o |= min(63u, (chan(a, i) * eva + chan(b, i) * evb + 8u) >> 4u) << (8u * i); }
  return o;
}
fn brighten(c: u32, ev: u32, bias: u32) -> u32 {
  var o = 0u;
  for (var i = 0u; i < 3u; i++) { o |= (chan(c, i) + (((63u - chan(c, i)) * ev + bias) >> 4u)) << (8u * i); }
  return o;
}
fn darken(c: u32, ev: u32, bias: u32) -> u32 {
  var o = 0u;
  for (var i = 0u; i < 3u; i++) { o |= (chan(c, i) - ((chan(c, i) * ev + bias) >> 4u)) << (8u * i); }
  return o;
}
fn pack18(c: u32) -> u32 { return (c & 0x3fu) | (((c >> 8u) & 0x3fu) << 6u) | (((c >> 16u) & 0x3fu) << 12u); }
fn objColor(dispcnt: u32, o: u32) -> u32 {
  let src = (o >> 16u) & 3u; let value = o & 0xffffu;
  if (src == 1u) { return value; }
  if (src == 3u && (dispcnt & (1u << 31u)) != 0u) { return v16(tabs[TB + 52u] + (value & 0xfffu) * 2u); }
  return objPal(value & 0xffu);
}
// the windows' horizontal flag of window w at x (gpu2d.c window_line): cleared at X2, else set at X1, from the
// state at the line's start
fn winHorizontal(w: u32, x: u32) -> bool {
  var h = reg16(0x40u); if (w == 1u) { h = reg16(0x42u); }
  let x1 = h >> 8u; let x2 = h & 0xffu;
  var lastClear = -1; if (x2 <= x) { lastClear = i32(x2); }
  var lastSet = -1; if (x1 <= x && x1 != x2) { lastSet = i32(x1); }
  if (lastClear < 0 && lastSet < 0) { return ((lines[LB + 32u] >> (2u * w + 1u)) & 1u) != 0u; }
  return lastSet > lastClear;
}
fn deferred3d(objKind: u32, objAlpha: u32, at: i32, col0: u32, lay0: u32, effOk: bool, first: u32, second: u32,
              effect: u32, eva: u32, evb: u32, evy: u32) -> u32 {
  let below3d = (second & 1u) != 0u;
  if (at == 1) {
    if (lay0 == 4u && objKind != 0u) {
      if (!below3d) { return (1u << 30u) | pack18(col0); }
      var a = eva; var b = evb;
      if (objKind == 2u) { a = objAlpha + 1u; b = 15u - objAlpha; }
      return (2u << 30u) | pack18(col0) | (a << 18u) | (b << 23u);
    }
    if (effOk && ((first >> lay0) & 1u) != 0u) {
      if (effect == 1u && below3d) { return (2u << 30u) | pack18(col0) | (eva << 18u) | (evb << 23u); }
      if (effect == 2u) { return (1u << 30u) | pack18(brighten(col0, evy, 8u)); }
      if (effect == 3u) { return (1u << 30u) | pack18(darken(col0, evy, 7u)); }
    }
    return (1u << 30u) | pack18(col0);
  }
  if (((second >> lay0) & 1u) != 0u) { return (3u << 30u) | pack18(col0) | (1u << 28u); }
  if (effOk && (first & 1u) != 0u && (effect == 2u || effect == 3u)) { return (3u << 30u) | (evy << 18u) | (effect << 28u); }
  return 3u << 30u;
}
// compose_line at x: the colour (6 bits a channel, r | g << 8 | b << 16) and gpu2d_deferred's word 1
fn compose(x: u32, line: u32) -> vec2u {
  let dispcnt = reg32(0u);
  let objHere = objPixel(x, line);
  // the window mask (from the OBJs before their mosaic)
  var m = 0x3fu;
  if ((dispcnt & 0xe000u) != 0u) {
    let winin = reg16(0x48u); let winout = reg16(0x4au);
    m = winout & 0x3fu;
    if ((dispcnt & 0x8000u) != 0u && ((objHere >> 27u) & 1u) != 0u) { m = (winout >> 8u) & 0x3fu; }
    for (var k = 0; k < 2; k++) {
      let w = u32(1 - k);
      if ((dispcnt & (0x2000u << w)) == 0u) { continue; }
      if (((lines[LB + 32u] >> (2u * w)) & 1u) != 0u && winHorizontal(w, x)) { m = (winin >> (8u * w)) & 0x3fu; }
    }
  }
  let obj = objPixelMosaic(x, line, objHere);
  let defer3d = E == 0u && (dispcnt & 8u) != 0u && (dispcnt & 0x100u) != 0u;
  var hofs3d = i32(reg16(0x10u) & 0x1ffu); if ((hofs3d & 0x100) != 0) { hofs3d -= 0x200; }
  let bldcnt = reg16(0x50u); let bldalpha = reg16(0x52u);
  let effect = (bldcnt >> 6u) & 3u; let first = bldcnt & 0x3fu; let second = (bldcnt >> 8u) & 0x3fu;
  let eva = min(bldalpha & 0x1fu, 16u); let evb = min((bldalpha >> 8u) & 0x1fu, 16u); let evy = min(reg16(0x54u) & 0x1fu, 16u);
  let backdrop = rgb6(bgPal(0u));
  var bg: array<u32, 4>;
  for (var n = 0u; n < 4u; n++) { bg[n] = bgPixel(n, x, line); }
  var col = array<u32, 2>(backdrop, backdrop);
  var lay = array<u32, 2>(5u, 5u);
  var found = 0u; var at3d = -1;
  let objSrc = (obj >> 16u) & 3u; let objPrio = (obj >> 18u) & 3u;
  for (var p = 0u; p < 4u && found < 2u; p++) {
    if ((dispcnt & 0x1000u) != 0u && found < 2u) {
      if ((m & 0x10u) != 0u && objSrc != 0u && objPrio == p) {
        col[found] = rgb6(objColor(dispcnt, obj)); lay[found] = 4u; found++;
      }
    }
    for (var n = 0u; n < 4u && found < 2u; n++) {
      if ((reg16(0x08u + 2u * n) & 3u) != p || (dispcnt & (0x100u << n)) == 0u) { continue; }
      if ((m & (1u << n)) == 0u) { continue; }
      if (n == 0u && defer3d) {
        let sx = i32(x) + hofs3d;
        if (sx >= 0 && sx < 256 && at3d < 0) { at3d = i32(found); }
      } else if ((bg[n] & 0x8000u) != 0u) {
        col[found] = rgb6(bg[n]); lay[found] = n; found++;
      }
    }
  }
  let lay0 = lay[0];
  if (found == 0u) { lay[1] = 7u; }
  var out = col[0];
  let effOk = (m & 0x20u) != 0u;
  let below2nd = ((second >> lay[1]) & 1u) != 0u;
  let objKind = (obj >> 20u) & 3u; let objAlpha = (obj >> 22u) & 15u;
  if (lay[0] == 4u && objKind != 0u && below2nd) {
    if (objKind == 2u) { out = blend(col[0], col[1], objAlpha + 1u, 15u - objAlpha); }
    else { out = blend(col[0], col[1], eva, evb); }
  } else if (effOk && ((first >> lay[0]) & 1u) != 0u) {
    if (effect == 1u && below2nd) { out = blend(col[0], col[1], eva, evb); }
    else if (effect == 2u) { out = brighten(col[0], evy, 8u); }
    else if (effect == 3u) { out = darken(col[0], evy, 7u); }
  }
  var word1 = 0u;
  if (defer3d && at3d >= 0) {
    word1 = deferred3d(objKind, objAlpha, at3d, col[0], lay0, effOk, first, second, effect, eva, evb, evy);
  }
  return vec2u(out, word1);
}
// render_line at x: the words
fn engineWords(x: u32, line: u32) -> vec2u {
  let dispcnt = reg32(0u);
  if (E == 1u && (lines[LB + 36u] & 0x200u) == 0u) { return vec2u(pack18(0x3f3f3fu), 0u); }
  var c = vec2u(0x3f3f3fu, 0u);
  if ((dispcnt & 0x80u) == 0u) { c = compose(x, line); }
  var mask = 3u; if (E == 1u) { mask = 1u; }
  let mode = (dispcnt >> 16u) & mask;
  var dst = c.x;
  if (mode == 0u) { return vec2u(pack18(0x3f3f3fu), 0u); }
  if (mode != 1u) { c.y = 0u; }
  if (mode == 2u) {
    let bank = tabs[TB + 53u + ((dispcnt >> 18u) & 3u)];
    dst = 0u;
    if (bank != 0xffffffffu) { dst = rgb6(v16(bank + (line * 256u + x) * 2u)); }
  } else if (mode == 3u) {
    dst = 0u;
  }
  if (c.y != 0u) { return vec2u(pack18(dst), c.y); }  // (before master brightness: the compositor applies it)
  let mb = reg16(0x6cu); let f = min(mb & 31u, 16u);
  if ((mb >> 14u) == 1u && f != 0u) { dst = brighten(dst, f, 0u); }
  else if ((mb >> 14u) == 2u && f != 0u) { dst = darken(dst, f, 15u); }
  return vec2u(pack18(dst), 0u);
}

@vertex fn vfull2d(@builtin(vertex_index) i: u32) -> @builtin(position) vec4f {
  let p = vec2f(f32((i << 1u) & 2u), f32(i & 2u)); return vec4f(p * 2.0 - 1.0, 0.0, 1.0);
}
@fragment fn f2d(@builtin(position) fp: vec4f) -> @location(0) vec4u {
  let x = u32(fp.x); let sy = u32(fp.y);
  let screen = sy / 192u; let line = sy % 192u;
  E = select(1u, 0u, screen == tabs[63u]);
  LB = (E * 192u + line) * LINE_WORDS;
  TB = E * 64u;
  PB = lines[LB + 34u] * 0x200u + E * 0x100u;
  OB = lines[LB + 35u] * 0x200u + E * 0x100u;
  let w = engineWords(x, line);
  return vec4u(w, 0u, 0u);
}
