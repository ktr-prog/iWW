
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu3d_internal.h"

#ifndef HOST_WGPU

int g3w_init(void *device, void *queue, int scale) {
    (void)device, (void)queue, (void)scale;
    return 0;
}
void g3w_render(const G3RenderState *r, const u8 *img, const u8 *pal, u32 *out) {
    (void)r, (void)img, (void)pal, (void)out;
}
void *g3w_picture(void) { return 0; }

#else

#include <webgpu/webgpu.h>
#include <webgpu/wgpu.h>

enum { W = 256, H = 192, IMG_SIZE = 0x80000, PAL_SIZE = 0x20000 };

static WGPUDevice sDev;
static WGPUQueue sQueue;
static WGPUShaderModule sShader;
static int sScale = 1;
static WGPUTexture sColorTex, sFogTex, sDepthTex, sOutTex[2];
static WGPUTextureView sColorView, sFogView, sDepthView, sDepthOnlyView, sOutView[2];
static int sShown;
static int sSamples = 4;
static WGPUBuffer sState, sImg, sPal, sVerts, sIndices, sReadback;
static WGPUBindGroupLayout sDrawLayout, sResolveLayout;
static WGPUBindGroup sDrawGroup, sResolveGroup;
static WGPUPipelineLayout sDrawPipeLayout, sResolvePipeLayout;
static WGPURenderPipeline sPipes[32], sResolvePipe;

static WGPUStringView sv(const char *s) { return (WGPUStringView){s, WGPU_STRLEN}; }

static void fatal(const char *what) {
    fprintf(stderr, "gpu3d-wgpu: %s\n", what);
    exit(1);
}
static const char kShader[] =
    "struct State {\n"
    "  dispcnt: u32, alphaRef: u32, clearRgb: u32, fogColor: u32,\n"
    "  fogOffset: u32, pad0: u32, pad1: u32, pad2: u32,\n"
    "  fogTable: array<vec4<u32>, 8>,\n"
    "};\n"
    "@group(0) @binding(0) var<uniform> st: State;\n"
    "@group(0) @binding(1) var<storage, read> img: array<u32>;\n"
    "@group(0) @binding(2) var<storage, read> pal: array<u32>;\n"
    "struct VIn { @location(0) pos: vec4f, @location(1) col: vec4f, @location(2) tz: vec4f, @location(3) poly: vec4u };\n"
    "struct VOut { @builtin(position) pos: vec4f, @location(0) col: vec3f, @location(1) tex: vec2f,\n"
    "  @location(2) zw: f32, @location(3) @interpolate(flat) poly: vec4u };\n"
    "@vertex fn vs(v: VIn) -> VOut {\n"
    "  var o: VOut; o.pos = v.pos; o.col = v.col.xyz; o.tex = v.tz.xy; o.zw = v.tz.z; o.poly = v.poly; return o;\n"
    "}\n"
    "fn img8(a0: u32) -> u32 { let a = a0 & 0x7ffffu; return (img[a >> 2u] >> ((a & 3u) * 8u)) & 0xffu; }\n"
    "fn img16(a: u32) -> u32 { return img8(a) | (img8(a + 1u) << 8u); }\n"
    "fn img32(a: u32) -> u32 { return img16(a) | (img16(a + 2u) << 16u); }\n"
    "fn pal8(a0: u32) -> u32 { let a = a0 & 0x1ffffu; return (pal[a >> 2u] >> ((a & 3u) * 8u)) & 0xffu; }\n"
    "fn pal16(a: u32) -> u32 { return pal8(a) | (pal8(a + 1u) << 8u); }\n"
    "fn wrap(c: i32, size: i32, rep: bool, flip: bool) -> i32 {\n"
    "  if (!rep) { return clamp(c, 0, size - 1); }\n"
    "  if (flip && (c & size) != 0) { return size - 1 - (c & (size - 1)); }\n"
    "  return c & (size - 1);\n"
    "}\n"
    "fn opaque(c: u32) -> u32 { return (c & 0x7fffu) | (31u << 16u); }\n"
    "fn texel(tp: u32, tpal: u32, s0: i32, t0: i32) -> u32 {\n"
    "  let fmt = (tp >> 26u) & 7u;\n"
    "  let w = 8 << ((tp >> 20u) & 7u); let h = 8 << ((tp >> 23u) & 7u);\n"
    "  let s = wrap(s0, w, ((tp >> 16u) & 1u) != 0u, ((tp >> 18u) & 1u) != 0u);\n"
    "  let t = wrap(t0, h, ((tp >> 17u) & 1u) != 0u, ((tp >> 19u) & 1u) != 0u);\n"
    "  let base = (tp & 0xffffu) << 3u; let pb = (tpal & 0x1fffu) << 4u;\n"
    "  let zero = ((tp >> 29u) & 1u) != 0u;\n"
    "  let i = u32(t * w + s);\n"
    "  switch fmt {\n"
    "    case 1u: { let v = img8(base + i); let a = v >> 5u;\n"
    "      return (pal16(pb + (v & 31u) * 2u) & 0x7fffu) | (((a << 2u) + (a >> 1u)) << 16u); }\n"
    "    case 2u: { let c = (img8(base + (i >> 2u)) >> ((i & 3u) * 2u)) & 3u;\n"
    "      if (zero && c == 0u) { return 0u; } return opaque(pal16(((tpal & 0x1fffu) << 3u) + c * 2u)); }\n"
    "    case 3u: { let c = (img8(base + (i >> 1u)) >> ((i & 1u) * 4u)) & 15u;\n"
    "      if (zero && c == 0u) { return 0u; } return opaque(pal16(pb + c * 2u)); }\n"
    "    case 4u: { let c = img8(base + i);\n"
    "      if (zero && c == 0u) { return 0u; } return opaque(pal16(pb + c * 2u)); }\n"
    "    case 5u: {\n"
    "      let block = u32((t >> 2u) * (w >> 2u) + (s >> 2u)); let addr = base + block * 4u;\n"
    "      let c = (img32(addr) >> (u32((t & 3) * 4 + (s & 3)) * 2u)) & 3u;\n"
    "      var slot1 = 0x20000u + ((addr & 0x1ffffu) >> 1u); if ((addr >> 17u) == 2u) { slot1 += 0x10000u; }\n"
    "      let info = img16(slot1); let pbb = pb + (info & 0x3fffu) * 4u; let mode = info >> 14u;\n"
    "      if (c == 3u && mode < 2u) { return 0u; }\n"
    "      if (c < 2u || mode == 2u) { return opaque(pal16(pbb + c * 2u)); }\n"
    "      let c0 = pal16(pbb); let c1 = pal16(pbb + 2u);\n"
    "      let k0 = vec3u(c0 & 31u, (c0 >> 5u) & 31u, (c0 >> 10u) & 31u);\n"
    "      let k1 = vec3u(c1 & 31u, (c1 >> 5u) & 31u, (c1 >> 10u) & 31u);\n"
    "      var k: vec3u;\n"
    "      if (mode == 1u) { k = (k0 + k1) / 2u; } else if (c == 2u) { k = (k0 * 5u + k1 * 3u) / 8u; }\n"
    "      else { k = (k0 * 3u + k1 * 5u) / 8u; }\n"
    "      return k.x | (k.y << 5u) | (k.z << 10u) | (31u << 16u);\n"
    "    }\n"
    "    case 6u: { let v = img8(base + i); return (pal16(pb + (v & 7u) * 2u) & 0x7fffu) | ((v >> 3u) << 16u); }\n"
    "    case 7u: { let v = img16(base + i * 2u); if ((v & 0x8000u) != 0u) { return opaque(v); } return 0u; }\n"
    "    default: { return 31u << 16u; }\n"
    "  }\n"
    "}\n"
    "fn rgb56(c: u32) -> u32 { if (c == 0u) { return 0u; } return c * 2u + 1u; }\n"
    "fn shade(i: VOut) -> vec4f {\n"
    "  let attr = i.poly.x; let tp = i.poly.y;\n"
    "  let vc = vec3u(max(floor(i.col), vec3f(0.0))) >> vec3u(3u);\n"
    "  var pa = (attr >> 16u) & 31u; if (pa == 0u) { pa = 31u; }\n"
    "  var c = vc; var al = pa;\n"
    "  if (((tp >> 26u) & 7u) != 0u && (st.dispcnt & 1u) != 0u) {\n"
    "    let tx = texel(tp, i.poly.z, i32(floor(i.tex.x / 16.0)), i32(floor(i.tex.y / 16.0)));\n"
    "    let ta = (tx >> 16u) & 31u;\n"
    "    let tc = vec3u(rgb56(tx & 31u), rgb56((tx >> 5u) & 31u), rgb56((tx >> 10u) & 31u));\n"
    "    if (((attr >> 4u) & 3u) == 1u) {\n"
    "      if (ta == 31u) { c = tc; } else if (ta != 0u) { c = (tc * ta + vc * (31u - ta)) >> vec3u(5u); }\n"
    "    } else {\n"
    "      c = ((tc + 1u) * (vc + 1u) - 1u) >> vec3u(6u);\n"
    "      al = ((ta + 1u) * (pa + 1u) - 1u) >> 5u;\n"
    "    }\n"
    "  }\n"
    "  if (al == 0u) { discard; }\n"
    "  if ((st.dispcnt & 4u) != 0u && al <= st.alphaRef) { discard; }\n"
    "  let a = f32(al) / 31.0;\n"
    "  return vec4f(vec3f(c) / 63.0 * a, a);\n"
    "}\n"
    "struct FOut { @location(0) color: vec4f, @location(1) fog: f32 };\n"
    "struct FOutW { @location(0) color: vec4f, @location(1) fog: f32, @builtin(frag_depth) depth: f32 };\n"
    "@fragment fn fs(i: VOut) -> FOut {\n"
    "  var o: FOut; o.color = shade(i); o.fog = f32((i.poly.x >> 15u) & 1u); return o;\n"
    "}\n"
    "@fragment fn fsw(i: VOut) -> FOutW {\n"
    "  var o: FOutW; o.color = shade(i); o.fog = f32((i.poly.x >> 15u) & 1u);\n"
    "  o.depth = clamp(i.zw, 0.0, 1.0); return o;\n"
    "}\n"
    "@vertex fn vfull(@builtin(vertex_index) i: u32) -> @builtin(position) vec4f {\n"
    "  let p = vec2f(f32((i << 1u) & 2u), f32(i & 2u)); return vec4f(p * 2.0 - 1.0, 0.0, 1.0);\n"
    "}\n";
static const char kResolveTargets1[] =
    "@group(1) @binding(0) var colorTex: texture_2d<f32>;\n"
    "@group(1) @binding(1) var depthTex: texture_depth_2d;\n"
    "@group(1) @binding(2) var fogTex: texture_2d<f32>;\n"
    "const SAMPLES = 1u;\n"
    "fn ldColor(xy: vec2i, i: u32) -> vec4f { return textureLoad(colorTex, xy, 0); }\n"
    "fn ldDepth(xy: vec2i, i: u32) -> f32 { return textureLoad(depthTex, xy, 0); }\n"
    "fn ldFog(xy: vec2i, i: u32) -> f32 { return textureLoad(fogTex, xy, 0).r; }\n";
static const char kResolveTargetsN[] =
    "@group(1) @binding(0) var colorTex: texture_multisampled_2d<f32>;\n"
    "@group(1) @binding(1) var depthTex: texture_depth_multisampled_2d;\n"
    "@group(1) @binding(2) var fogTex: texture_multisampled_2d<f32>;\n"
    "const SAMPLES = 4u;\n"
    "fn ldColor(xy: vec2i, i: u32) -> vec4f { return textureLoad(colorTex, xy, i); }\n"
    "fn ldDepth(xy: vec2i, i: u32) -> f32 { return textureLoad(depthTex, xy, i); }\n"
    "fn ldFog(xy: vec2i, i: u32) -> f32 { return textureLoad(fogTex, xy, i).r; }\n";
static const char kResolve[] =
    "fn fogTab(n: u32) -> i32 { return i32(st.fogTable[n >> 2u][n & 3u]); }\n"
    "fn resolveSample(xy: vec2i, i: u32) -> vec4u {\n"
    "  let pc = ldColor(xy, i);\n"
    "  var a = u32(round(pc.a * 31.0));\n"
    "  var c = vec3u(st.clearRgb & 63u, (st.clearRgb >> 8u) & 63u, (st.clearRgb >> 16u) & 63u);\n"
    "  if (pc.a > 0.0) { c = vec3u(round(clamp(pc.rgb / pc.a, vec3f(0.0), vec3f(1.0)) * 63.0)); }\n"
    "  if ((st.dispcnt & 0x80u) != 0u && ldFog(xy, i) > 0.5) {\n"
    "    let shift = (st.dispcnt >> 8u) & 15u;\n"
    "    var step = 0; if (shift <= 10u) { step = 0x400 >> shift; }\n"
    "    let z = i32(u32(round(ldDepth(xy, i) * 16777215.0)) >> 9u);\n"
    "    let b0 = i32(st.fogOffset) + step;\n"
    "    var d: i32;\n"
    "    if (z < b0 || step == 0) { if (z < b0) { d = fogTab(0u); } else { d = fogTab(31u); } }\n"
    "    else {\n"
    "      let n = (z - b0) / step;\n"
    "      if (n >= 31) { d = fogTab(31u); }\n"
    "      else { let frac = (z - b0) - n * step;\n"
    "        d = fogTab(u32(n)) + (fogTab(u32(n) + 1u) - fogTab(u32(n))) * frac / step; }\n"
    "    }\n"
    "    if (d >= 127) { d = 128; }\n"
    "    let du = u32(d);\n"
    "    let fc = st.fogColor;\n"
    "    let f = vec3u(rgb56(fc & 31u), rgb56((fc >> 5u) & 31u), rgb56((fc >> 10u) & 31u));\n"
    "    a = (((fc >> 16u) & 31u) * du + a * (128u - du)) >> 7u;\n"
    "    if ((st.dispcnt & 0x40u) == 0u) { c = (f * du + c * (128u - du)) >> vec3u(7u); }\n"
    "  }\n"
    "  return vec4u(c, a);\n"
    "}\n"
    "@fragment fn fresolve(@builtin(position) fp: vec4f) -> @location(0) u32 {\n"
    "  let xy = vec2i(fp.xy);\n"
    "  var r = resolveSample(xy, 0u);\n"
    "  if (SAMPLES > 1u && (st.dispcnt & 0x10u) != 0u) {\n"
    "    var sc = vec3u(0u); var sa = 0u; var su = vec3u(0u);\n"
    "    for (var i = 0u; i < SAMPLES; i++) {\n"
    "      let k = resolveSample(xy, i); sc += k.xyz * k.w; sa += k.w; su += k.xyz;\n"
    "    }\n"
    "    if (sa > 0u) { r = vec4u((sc + sa / 2u) / sa, (sa + SAMPLES / 2u) / SAMPLES); }\n"
    "    else { r = vec4u((su + SAMPLES / 2u) / SAMPLES, 0u); }\n"
    "  }\n"
    "  return r.x | (r.y << 8u) | (r.z << 16u) | (r.w << 24u);\n"
    "}\n";

static WGPUTexture texture(WGPUTextureFormat fmt, WGPUTextureUsage usage, int samples) {
    WGPUTextureDescriptor d = WGPU_TEXTURE_DESCRIPTOR_INIT;
    d.sampleCount = (u32)samples;
    d.size = (WGPUExtent3D){W * (u32)sScale, H * (u32)sScale, 1};
    d.format = fmt;
    d.usage = usage;
    return wgpuDeviceCreateTexture(sDev, &d);
}
static WGPUBuffer buffer(u64 size, WGPUBufferUsage usage) {
    WGPUBufferDescriptor d = WGPU_BUFFER_DESCRIPTOR_INIT;
    d.size = size;
    d.usage = usage;
    return wgpuDeviceCreateBuffer(sDev, &d);
}

typedef struct {
    float pos[4];
    float col[4];
    float tz[4];
    u32 poly[4];
} GVertex;

int g3w_init(void *device, void *queue, int scale) {
    if (sDev) return 1;
    if (!device) return 0;
    sDev = device;
    sQueue = queue;
    sScale = scale < 1 ? 1 : scale > 8 ? 8 : scale;
    const char *ms = getenv("ACWW_MSAA");
    sSamples = ms && atoi(ms) <= 1 ? 1 : 4;
    static char code[sizeof kShader + sizeof kResolveTargetsN + sizeof kResolve];
    snprintf(code, sizeof code, "%s%s%s", kShader, sSamples > 1 ? kResolveTargetsN : kResolveTargets1, kResolve);
    WGPUShaderSourceWGSL src = WGPU_SHADER_SOURCE_WGSL_INIT;
    src.code = sv(code);
    WGPUShaderModuleDescriptor md = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
    md.nextInChain = &src.chain;
    sShader = wgpuDeviceCreateShaderModule(sDev, &md);

    WGPUTextureUsage tu = WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_TextureBinding;
    sColorTex = texture(WGPUTextureFormat_RGBA16Float, tu, sSamples);
    sFogTex = texture(WGPUTextureFormat_R8Unorm, tu, sSamples);
    sDepthTex = texture(WGPUTextureFormat_Depth24PlusStencil8, tu, sSamples);
    for (int i = 0; i < 2; i++) {
        sOutTex[i] = texture(WGPUTextureFormat_R32Uint, WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_CopySrc |
                                                            WGPUTextureUsage_TextureBinding, 1);
        sOutView[i] = wgpuTextureCreateView(sOutTex[i], NULL);
    }
    sColorView = wgpuTextureCreateView(sColorTex, NULL);
    sFogView = wgpuTextureCreateView(sFogTex, NULL);
    sDepthView = wgpuTextureCreateView(sDepthTex, NULL);
    WGPUTextureViewDescriptor dv = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT;
    dv.aspect = WGPUTextureAspect_DepthOnly;
    sDepthOnlyView = wgpuTextureCreateView(sDepthTex, &dv);

    sState = buffer(256, WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst);
    sImg = buffer(IMG_SIZE, WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst);
    sPal = buffer(PAL_SIZE, WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst);
    sVerts = buffer((u64)MAX_POLYGONS * 10 * sizeof(GVertex), WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst);
    sIndices = buffer((u64)MAX_POLYGONS * 24 * sizeof(u32), WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst);
    sReadback = buffer(W * H * 4, WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst);

    WGPUBindGroupLayoutEntry de[3] = {WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT, WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
                                      WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT};
    for (int i = 0; i < 3; i++) {
        de[i].binding = (u32)i;
        de[i].visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
        de[i].buffer.type = i ? WGPUBufferBindingType_ReadOnlyStorage : WGPUBufferBindingType_Uniform;
    }
    WGPUBindGroupLayoutDescriptor ld = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT;
    ld.entryCount = 3;
    ld.entries = de;
    sDrawLayout = wgpuDeviceCreateBindGroupLayout(sDev, &ld);
    WGPUBindGroupEntry ge[3] = {WGPU_BIND_GROUP_ENTRY_INIT, WGPU_BIND_GROUP_ENTRY_INIT, WGPU_BIND_GROUP_ENTRY_INIT};
    WGPUBuffer gb[3] = {sState, sImg, sPal};
    u64 gs[3] = {256, IMG_SIZE, PAL_SIZE};
    for (int i = 0; i < 3; i++) ge[i].binding = (u32)i, ge[i].buffer = gb[i], ge[i].size = gs[i];
    WGPUBindGroupDescriptor gd = WGPU_BIND_GROUP_DESCRIPTOR_INIT;
    gd.layout = sDrawLayout;
    gd.entryCount = 3;
    gd.entries = ge;
    sDrawGroup = wgpuDeviceCreateBindGroup(sDev, &gd);
    WGPUBindGroupLayoutEntry re[3] = {WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT, WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
                                      WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT};
    for (int i = 0; i < 3; i++) {
        re[i].binding = (u32)i;
        re[i].visibility = WGPUShaderStage_Fragment;
        re[i].texture.sampleType = i == 1 ? WGPUTextureSampleType_Depth : WGPUTextureSampleType_UnfilterableFloat;
        re[i].texture.viewDimension = WGPUTextureViewDimension_2D;
        re[i].texture.multisampled = sSamples > 1;
    }
    ld.entries = re;
    sResolveLayout = wgpuDeviceCreateBindGroupLayout(sDev, &ld);
    WGPUBindGroupEntry rg[3] = {WGPU_BIND_GROUP_ENTRY_INIT, WGPU_BIND_GROUP_ENTRY_INIT, WGPU_BIND_GROUP_ENTRY_INIT};
    rg[0].binding = 0, rg[0].textureView = sColorView;
    rg[1].binding = 1, rg[1].textureView = sDepthOnlyView;
    rg[2].binding = 2, rg[2].textureView = sFogView;
    gd.layout = sResolveLayout;
    gd.entries = rg;
    sResolveGroup = wgpuDeviceCreateBindGroup(sDev, &gd);

    WGPUPipelineLayoutDescriptor pd = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT;
    pd.bindGroupLayoutCount = 1;
    pd.bindGroupLayouts = &sDrawLayout;
    sDrawPipeLayout = wgpuDeviceCreatePipelineLayout(sDev, &pd);
    WGPUBindGroupLayout both[2] = {sDrawLayout, sResolveLayout};
    pd.bindGroupLayoutCount = 2;
    pd.bindGroupLayouts = both;
    sResolvePipeLayout = wgpuDeviceCreatePipelineLayout(sDev, &pd);

    WGPURenderPipelineDescriptor rp = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
    rp.layout = sResolvePipeLayout;
    rp.vertex.module = sShader;
    rp.vertex.entryPoint = sv("vfull");
    WGPUColorTargetState ct = WGPU_COLOR_TARGET_STATE_INIT;
    ct.format = WGPUTextureFormat_R32Uint;
    WGPUFragmentState fs = WGPU_FRAGMENT_STATE_INIT;
    fs.module = sShader;
    fs.entryPoint = sv("fresolve");
    fs.targetCount = 1;
    fs.targets = &ct;
    rp.fragment = &fs;
    sResolvePipe = wgpuDeviceCreateRenderPipeline(sDev, &rp);
    return 1;
}

static WGPURenderPipeline pipeline(int key) {
    if (sPipes[key]) return sPipes[key];
    int trans = key & 1;
    WGPUVertexAttribute va[4];
    for (int i = 0; i < 4; i++) {
        va[i] = (WGPUVertexAttribute)WGPU_VERTEX_ATTRIBUTE_INIT;
        va[i].shaderLocation = (u32)i;
        va[i].offset = (u64)i * 16;
        va[i].format = i == 3 ? WGPUVertexFormat_Uint32x4 : WGPUVertexFormat_Float32x4;
    }
    WGPUVertexBufferLayout vl = WGPU_VERTEX_BUFFER_LAYOUT_INIT;
    vl.arrayStride = sizeof(GVertex);
    vl.attributeCount = 4;
    vl.attributes = va;
    WGPURenderPipelineDescriptor rp = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
    rp.layout = sDrawPipeLayout;
    rp.vertex.module = sShader;
    rp.vertex.entryPoint = sv("vs");
    rp.vertex.bufferCount = 1;
    rp.vertex.buffers = &vl;
    rp.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rp.primitive.cullMode = WGPUCullMode_None;
    rp.multisample.count = (u32)sSamples;
    WGPUDepthStencilState ds = WGPU_DEPTH_STENCIL_STATE_INIT;
    ds.format = WGPUTextureFormat_Depth24PlusStencil8;
    ds.depthWriteEnabled = !trans || (key & 8) ? WGPUOptionalBool_True : WGPUOptionalBool_False;
    ds.depthCompare = key & 4 ? WGPUCompareFunction_LessEqual : WGPUCompareFunction_Less;
    WGPUStencilFaceState sf = WGPU_STENCIL_FACE_STATE_INIT;
    sf.compare = trans ? WGPUCompareFunction_NotEqual : WGPUCompareFunction_Always;
    sf.passOp = trans ? WGPUStencilOperation_Replace : WGPUStencilOperation_Keep;
    sf.failOp = sf.depthFailOp = WGPUStencilOperation_Keep;
    ds.stencilFront = ds.stencilBack = sf;
    ds.stencilReadMask = ds.stencilWriteMask = 0xff;
    rp.depthStencil = &ds;
    WGPUBlendState cb = WGPU_BLEND_STATE_INIT;
    int blend = trans && (key & 16);
    cb.color.operation = WGPUBlendOperation_Add;
    cb.color.srcFactor = WGPUBlendFactor_One;
    cb.color.dstFactor = blend ? WGPUBlendFactor_OneMinusSrcAlpha : WGPUBlendFactor_Zero;
    cb.alpha.operation = trans ? WGPUBlendOperation_Max : WGPUBlendOperation_Add;
    cb.alpha.srcFactor = WGPUBlendFactor_One;
    cb.alpha.dstFactor = trans ? WGPUBlendFactor_One : WGPUBlendFactor_Zero;
    WGPUBlendState fb = WGPU_BLEND_STATE_INIT;
    fb.color.operation = trans ? WGPUBlendOperation_Min : WGPUBlendOperation_Add;
    fb.color.srcFactor = WGPUBlendFactor_One;
    fb.color.dstFactor = trans ? WGPUBlendFactor_One : WGPUBlendFactor_Zero;
    fb.alpha = fb.color;
    WGPUColorTargetState ct[2] = {WGPU_COLOR_TARGET_STATE_INIT, WGPU_COLOR_TARGET_STATE_INIT};
    ct[0].format = WGPUTextureFormat_RGBA16Float;
    ct[0].blend = &cb;
    ct[1].format = WGPUTextureFormat_R8Unorm;
    ct[1].blend = &fb;
    WGPUFragmentState fs = WGPU_FRAGMENT_STATE_INIT;
    fs.module = sShader;
    fs.entryPoint = sv(key & 2 ? "fsw" : "fs");
    fs.targetCount = 2;
    fs.targets = ct;
    rp.fragment = &fs;
    return sPipes[key] = wgpuDeviceCreateRenderPipeline(sDev, &rp);
}

static u8 sImgCopy[IMG_SIZE], sPalCopy[PAL_SIZE];
static void upload(WGPUBuffer buf, u8 *copy, const u8 *src, u32 size) {
    enum { PIECE = 0x1000 };
    for (u32 o = 0; o < size;) {
        if (!memcmp(copy + o, src + o, PIECE)) { o += PIECE; continue; }
        u32 end = o + PIECE;
        while (end < size && memcmp(copy + end, src + end, PIECE)) end += PIECE;
        memcpy(copy + o, src + o, end - o);
        wgpuQueueWriteBuffer(sQueue, buf, o, src + o, end - o);
        o = end;
    }
}

static u32 rgb5_to_6(u32 c) { return c ? c * 2 + 1 : 0; }

static GVertex sV[MAX_POLYGONS * 10];
static u32 sI[MAX_POLYGONS * 24];

static void on_mapped(WGPUMapAsyncStatus status, WGPUStringView msg, void *u1, void *u2) {
    (void)msg, (void)u2;
    *(int *)u1 = status == WGPUMapAsyncStatus_Success ? 1 : -1;
}

void *g3w_picture(void) { return sDev ? sOutView[sShown] : NULL; }

void g3w_render(const G3RenderState *r, const u8 *img, const u8 *pal, u32 *out) {
    if (!sDev) fatal("no WebGPU device");
    int next = sShown ^ 1;
    u32 st[64] = {0};
    u32 cc = r->clearColor;
    u32 cr = rgb5_to_6(cc & 31), cg = rgb5_to_6(cc >> 5 & 31), cbl = rgb5_to_6(cc >> 10 & 31);
    st[0] = r->dispcnt;
    st[1] = r->alphaRef;
    st[2] = cr | cg << 8 | cbl << 16;
    st[3] = r->fogColor;
    st[4] = r->fogOffset;
    for (int i = 0; i < 32; i++) st[8 + i] = r->fogTable[i];
    wgpuQueueWriteBuffer(sQueue, sState, 0, st, sizeof st);
    upload(sImg, sImgCopy, img, IMG_SIZE);
    upload(sPal, sPalCopy, pal, PAL_SIZE);
    int nv = 0, ni = 0;
    for (int k = 0; k < r->npoly; k++) {
        const G3Polygon *p = r->poly[k];
        if (p->nv < 3) continue;
        for (int i = 0; i < p->nv; i++) {
            const G3Vertex *v = p->v[i];
            GVertex *g = &sV[nv + i];
            float w = (float)(p->w[i] > 0 ? p->w[i] : 1);
            float x = (float)v->hx / 16.0f / W * 2.0f - 1.0f, y = 1.0f - (float)v->hy / 16.0f / H * 2.0f;
            float z = (float)p->z[i] / 16777215.0f;
            if (z > 1.0f) z = 1.0f;
            if (z < 0.0f) z = 0.0f;
            g->pos[0] = x * w, g->pos[1] = y * w, g->pos[2] = z * w, g->pos[3] = w;
            for (int c = 0; c < 3; c++) g->col[c] = (float)v->color[c];
            g->col[3] = 0;
            g->tz[0] = v->tex[0], g->tz[1] = v->tex[1], g->tz[2] = z, g->tz[3] = 0;
            g->poly[0] = p->attr, g->poly[1] = p->texparam, g->poly[2] = p->texpal, g->poly[3] = 0;
        }
        for (int i = 1; i + 1 < p->nv; i++) sI[ni++] = (u32)nv, sI[ni++] = (u32)(nv + i), sI[ni++] = (u32)(nv + i + 1);
        nv += p->nv;
    }
    if (nv) wgpuQueueWriteBuffer(sQueue, sVerts, 0, sV, (size_t)nv * sizeof(GVertex));
    if (ni) wgpuQueueWriteBuffer(sQueue, sIndices, 0, sI, (size_t)ni * sizeof(u32));

    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(sDev, NULL);
    WGPURenderPassColorAttachment ca[2] = {WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT,
                                           WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT};
    float ca_ = (float)(r->clearAttrHi & 31) / 31.0f;
    ca[0].view = sColorView;
    ca[0].loadOp = WGPULoadOp_Clear;
    ca[0].storeOp = WGPUStoreOp_Store;
    ca[0].clearValue = (WGPUColor){cr / 63.0 * ca_, cg / 63.0 * ca_, cbl / 63.0 * ca_, ca_};
    ca[1].view = sFogView;
    ca[1].loadOp = WGPULoadOp_Clear;
    ca[1].storeOp = WGPUStoreOp_Store;
    ca[1].clearValue = (WGPUColor){cc & 0x8000 ? 1.0 : 0.0, 0, 0, 0};
    WGPURenderPassDepthStencilAttachment da = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
    da.view = sDepthView;
    da.depthLoadOp = WGPULoadOp_Clear;
    da.depthStoreOp = WGPUStoreOp_Store;
    u32 cd = (u32)(r->clearDepth & 0x7fff) * 0x200 + ((r->clearDepth & 0x7fff) == 0x7fff ? 0x1ff : 0);
    da.depthClearValue = (float)cd / 16777215.0f;
    da.stencilLoadOp = WGPULoadOp_Clear;
    da.stencilStoreOp = WGPUStoreOp_Store;
    da.stencilClearValue = 0;
    WGPURenderPassDescriptor rd = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    rd.colorAttachmentCount = 2;
    rd.colorAttachments = ca;
    rd.depthStencilAttachment = &da;
    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(enc, &rd);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, sDrawGroup, 0, NULL);
    if (nv) {
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0, sVerts, 0, (u64)nv * sizeof(GVertex));
        wgpuRenderPassEncoderSetIndexBuffer(pass, sIndices, WGPUIndexFormat_Uint32, 0, (u64)ni * sizeof(u32));
    }
    int first = 0, curKey = -1, curRef = -1;
    for (int k = 0; k < r->npoly; k++) {
        const G3Polygon *p = r->poly[k];
        if (p->nv < 3) continue;
        int key = (p->translucent ? 1 : 0) | (p->wbuffer ? 2 : 0) | (p->attr & 0x4000 ? 4 : 0) |
                  (p->attr & 0x800 ? 8 : 0) | (r->dispcnt & 8 ? 16 : 0);
        if (key != curKey) wgpuRenderPassEncoderSetPipeline(pass, pipeline(key)), curKey = key;
        int ref = p->translucent ? 0x40 | (int)(p->attr >> 24 & 63) : 0;
        if (ref != curRef) wgpuRenderPassEncoderSetStencilReference(pass, (u32)ref), curRef = ref;
        u32 count = (u32)(p->nv - 2) * 3;
        wgpuRenderPassEncoderDrawIndexed(pass, count, 1, (u32)first, 0, 0);
        first += (int)count;
    }
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    WGPURenderPassColorAttachment oa = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
    oa.view = sOutView[next];
    oa.loadOp = WGPULoadOp_Clear;
    oa.storeOp = WGPUStoreOp_Store;
    WGPURenderPassDescriptor od = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    od.colorAttachmentCount = 1;
    od.colorAttachments = &oa;
    pass = wgpuCommandEncoderBeginRenderPass(enc, &od);
    wgpuRenderPassEncoderSetPipeline(pass, sResolvePipe);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, sDrawGroup, 0, NULL);
    wgpuRenderPassEncoderSetBindGroup(pass, 1, sResolveGroup, 0, NULL);
    wgpuRenderPassEncoderDraw(pass, 3, 1, 0, 0);
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    sShown = next;
    if (!out || sScale != 1) {
        WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, NULL);
        wgpuQueueSubmit(sQueue, 1, &cmd);
        wgpuCommandBufferRelease(cmd);
        wgpuCommandEncoderRelease(enc);
        return;
    }
    WGPUTexelCopyTextureInfo src = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
    src.texture = sOutTex[next];
    WGPUTexelCopyBufferInfo dst = WGPU_TEXEL_COPY_BUFFER_INFO_INIT;
    dst.buffer = sReadback;
    dst.layout.bytesPerRow = W * 4;
    dst.layout.rowsPerImage = H;
    WGPUExtent3D size = {W, H, 1};
    wgpuCommandEncoderCopyTextureToBuffer(enc, &src, &dst, &size);
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, NULL);
    wgpuQueueSubmit(sQueue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);
    wgpuCommandEncoderRelease(enc);
    int mapped = 0;
    WGPUBufferMapCallbackInfo mc = WGPU_BUFFER_MAP_CALLBACK_INFO_INIT;
    mc.mode = WGPUCallbackMode_AllowSpontaneous;
    mc.callback = on_mapped;
    mc.userdata1 = &mapped;
    wgpuBufferMapAsync(sReadback, WGPUMapMode_Read, 0, W * H * 4, mc);
    while (!mapped) wgpuDevicePoll(sDev, 1, NULL);
    if (mapped < 0) fatal("readback failed");
    memcpy(out, wgpuBufferGetConstMappedRange(sReadback, 0, W * H * 4), W * H * 4);
    wgpuBufferUnmap(sReadback);
}

#endif
