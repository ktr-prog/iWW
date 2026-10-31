
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wgpu_display.h"

#ifndef HOST_WGPU

int wdisp_init(int software_ok) {
    (void)software_ok;
    return 0;
}
void *wdisp_device(void) { return 0; }
void *wdisp_queue(void) { return 0; }
void wdisp_frame(const uint32_t *const deferred[2], const uint32_t *const lines[2], void *picture3d, int scale) {
    (void)deferred, (void)lines, (void)picture3d, (void)scale;
}
void wdisp_frame_2d(const void *gpuFrame, const uint8_t *const banks[9], const uint32_t *const lines[2],
                    void *picture3d, int scale) {
    (void)gpuFrame, (void)banks, (void)lines, (void)picture3d, (void)scale;
}
int wdisp_read_2d(uint32_t *out) {
    (void)out;
    return 0;
}
const uint32_t *wdisp_screens(void) {
    static uint32_t none[256 * 384];
    return none;
}
int wdisp_attach(int kind, void *display, uint64_t window, int vsync) {
    (void)kind, (void)display, (void)window, (void)vsync;
    return 0;
}
int wdisp_presenting(void) { return 0; }
void wdisp_present(int w, int h) { (void)w, (void)h; }
void wdisp_overlay(const uint32_t *argb, int changed) { (void)argb, (void)changed; }
int wdisp_read_window(int w, int h, uint32_t *out) {
    (void)w, (void)h, (void)out;
    return 0;
}

#else

#include <webgpu/webgpu.h>
#include <webgpu/wgpu.h>

#include "gpu2d/gpu2d.h"
#include "gpu2d_wgsl.h"

typedef uint32_t u32;
typedef uint64_t u64;

static WGPUInstance sInst;
static WGPUAdapter sAdapter;
static WGPUDevice sDev;
static WGPUQueue sQueue;

static WGPUStringView sv(const char *s) { return (WGPUStringView){s, WGPU_STRLEN}; }
static int svlen(WGPUStringView s) { return (int)(s.length == WGPU_STRLEN ? (s.data ? strlen(s.data) : 0) : s.length); }

static void on_error(const WGPUDevice *d, WGPUErrorType type, WGPUStringView msg, void *u1, void *u2) {
    (void)d, (void)u1, (void)u2;
    fprintf(stderr, "wgpu: error %d: %.*s\n", (int)type, svlen(msg), msg.data ? msg.data : "");
    exit(1);
}
static void on_adapter(WGPURequestAdapterStatus status, WGPUAdapter a, WGPUStringView msg, void *u1, void *u2) {
    (void)msg, (void)u2;
    if (status == WGPURequestAdapterStatus_Success) *(WGPUAdapter *)u1 = a;
}
static void on_device(WGPURequestDeviceStatus status, WGPUDevice d, WGPUStringView msg, void *u1, void *u2) {
    (void)u2;
    if (status == WGPURequestDeviceStatus_Success) *(WGPUDevice *)u1 = d;
    else fprintf(stderr, "wgpu: no device: %.*s\n", svlen(msg), msg.data ? msg.data : "");
}

int wdisp_init(int software_ok) {
    if (sDev) return 1;
    sInst = wgpuCreateInstance(NULL);
    if (!sInst) return 0;
    const char *want = getenv("ACWW_WGPU_ADAPTER");
    WGPURequestAdapterOptions ao = WGPU_REQUEST_ADAPTER_OPTIONS_INIT;
    ao.powerPreference = WGPUPowerPreference_HighPerformance;
    ao.forceFallbackAdapter = want && strcmp(want, "cpu") == 0;
    WGPURequestAdapterCallbackInfo ac = WGPU_REQUEST_ADAPTER_CALLBACK_INFO_INIT;
    ac.mode = WGPUCallbackMode_AllowSpontaneous;
    ac.callback = on_adapter;
    ac.userdata1 = &sAdapter;
    wgpuInstanceRequestAdapter(sInst, &ao, ac);
    for (int i = 0; !sAdapter && i < 1000; i++) wgpuInstanceProcessEvents(sInst);
    if (!sAdapter) {
        fprintf(stderr, "wgpu: no adapter\n");
        return 0;
    }
    WGPUAdapterInfo info = WGPU_ADAPTER_INFO_INIT;
    wgpuAdapterGetInfo(sAdapter, &info);
    int software = info.adapterType == WGPUAdapterType_CPU;
    if (software && !software_ok && !ao.forceFallbackAdapter) {
        wgpuAdapterInfoFreeMembers(info);
        return 0;
    }
    fprintf(stderr, "wgpu: %.*s (backend %d)\n", svlen(info.device), info.device.data ? info.device.data : "",
            (int)info.backendType);
    wgpuAdapterInfoFreeMembers(info);
    WGPUDeviceDescriptor dd = WGPU_DEVICE_DESCRIPTOR_INIT;
    dd.uncapturedErrorCallbackInfo.callback = on_error;
    WGPURequestDeviceCallbackInfo dc = WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT;
    dc.mode = WGPUCallbackMode_AllowSpontaneous;
    dc.callback = on_device;
    dc.userdata1 = &sDev;
    wgpuAdapterRequestDevice(sAdapter, &dd, dc);
    for (int i = 0; !sDev && i < 1000; i++) wgpuInstanceProcessEvents(sInst);
    if (!sDev) return 0;
    sQueue = wgpuDeviceGetQueue(sDev);
    return 1;
}
void *wdisp_device(void) { return sDev; }
void *wdisp_queue(void) { return sQueue; }

static const char kShader[] =
    "struct U { vp: vec4f, scale: u32, overlay: u32, pad1: u32, pad2: u32 };\n"
    "@group(0) @binding(0) var<uniform> u: U;\n"
    "@group(0) @binding(1) var deferred: texture_2d<u32>;\n"
    "@group(0) @binding(2) var<storage, read> lines: array<u32>;\n"
    "@group(0) @binding(3) var pic: texture_2d<u32>;\n"
    "@group(0) @binding(4) var overlay: texture_2d<f32>;\n"
    "@vertex fn vfull(@builtin(vertex_index) i: u32) -> @builtin(position) vec4f {\n"
    "  let p = vec2f(f32((i << 1u) & 2u), f32(i & 2u)); return vec4f(p * 2.0 - 1.0, 0.0, 1.0);\n"
    "}\n"
    "fn rgb18(c: u32) -> vec3u { return vec3u(c & 63u, (c >> 6u) & 63u, (c >> 12u) & 63u); }\n"
    "fn screens(p: vec2f) -> vec3u {\n"
    "  let ip = vec2u(p);\n"
    "  let d = textureLoad(deferred, ip, 0).xy;\n"
    "  var c = rgb18(d.x);\n"
    "  let kind = d.y >> 30u;\n"
    "  if (kind == 0u) { return c; }\n"
    "  let info = lines[ip.y];\n"
    "  var hofs = i32((info >> 16u) & 0x1ffu); if (hofs >= 256) { hofs -= 512; }\n"
    "  let top = f32(ip.y - ip.y % 192u);\n"
    "  let s = f32(u.scale);\n"
    "  let size = vec2i(256 * i32(u.scale), 192 * i32(u.scale));\n"
    "  let q = clamp(vec2i(floor(vec2f(p.x + f32(hofs), p.y - top) * s)), vec2i(0), size - 1);\n"
    "  let t = textureLoad(pic, q, 0).x;\n"
    "  let pa = (t >> 24u) & 31u;\n"
    "  if (pa != 0u) {\n"
    "    let pc = vec3u(t & 63u, (t >> 8u) & 63u, (t >> 16u) & 63u);\n"
    "    let cc = rgb18(d.y);\n"
    "    let p1 = (d.y >> 18u) & 31u; let p2 = (d.y >> 23u) & 31u; let e = (d.y >> 28u) & 3u;\n"
    "    if (kind == 1u) { c = cc; }\n"
    "    else if (kind == 2u) { c = min(vec3u(63u), (cc * p1 + pc * p2 + 8u) >> vec3u(4u)); }\n"
    "    else if (e == 0u) { c = pc; }\n"
    "    else if (e == 1u) { c = (pc * (pa + 1u) + cc * (31u - pa) + 16u) >> vec3u(5u); }\n"
    "    else if (e == 2u) { c = pc + (((63u - pc) * p1 + 8u) >> vec3u(4u)); }\n"
    "    else { c = pc - ((pc * p1 + 7u) >> vec3u(4u)); }\n"
    "  }\n"
    "  let mb = info & 0xffffu; let f = min(mb & 31u, 16u);\n"
    "  if ((mb >> 14u) == 1u && f != 0u) { c = c + (((63u - c) * f) >> vec3u(4u)); }\n"
    "  else if ((mb >> 14u) == 2u && f != 0u) { c = c - ((c * f + 15u) >> vec3u(4u)); }\n"
    "  return c;\n"
    "}\n"
    "@fragment fn fcomp(@builtin(position) fp: vec4f) -> @location(0) vec4f {\n"
    "  let px = vec2f(256.0, 384.0) / u.vp.zw;\n"
    "  let p = (fp.xy - u.vp.xy) * px;\n"
    "  if (p.x < 0.0 || p.y < 0.0 || p.x >= 256.0 || p.y >= 384.0) { return vec4f(0.0, 0.0, 0.0, 1.0); }\n"
    "  let n = u32(clamp(round(px.x * f32(u.scale)), 1.0, 4.0));\n"
    "  var sum = vec3f(0.0);\n"
    "  let corner = (floor(fp.xy) - u.vp.xy) * px;\n"
    "  for (var j = 0u; j < n; j++) {\n"
    "    for (var i = 0u; i < n; i++) {\n"
    "      let q = clamp(corner + (vec2f(f32(i), f32(j)) + 0.5) / f32(n) * px, vec2f(0.0), vec2f(255.99, 383.99));\n"
    "      let c = screens(q);\n"
    "      var c8 = vec3f((c << vec3u(2u)) | (c >> vec3u(4u)));\n"
    "      if (u.overlay != 0u) { let o = textureLoad(overlay, vec2i(q), 0); c8 = mix(c8, o.rgb * 255.0, o.a); }\n"
    "      sum += c8;\n"
    "    }\n"
    "  }\n"
    "  return vec4f(sum / f32(n * n) / 255.0, 1.0);\n"
    "}\n";

static WGPUShaderModule sShader;
static WGPUBindGroupLayout sLayout;
static WGPUPipelineLayout sPipeLayout;
static struct { WGPUTextureFormat fmt; WGPURenderPipeline pipe; } sPipes[4];
static WGPUTexture sDeferredTex;
static WGPUTextureView sDeferredView;
static WGPUBuffer sUniform, sLines;
static struct { WGPUTextureView pic; WGPUBindGroup group; } sGroups[2];
static WGPUTextureView sPic;
static int sScale = 1;
static u32 sFrames;
static WGPUTexture sOverlayTex;
static WGPUTextureView sOverlayView;
static int sOverlayOn;

static int setup(void) {
    if (sShader) return 1;
    if (!sDev) return 0;
    WGPUShaderSourceWGSL src = WGPU_SHADER_SOURCE_WGSL_INIT;
    src.code = sv(kShader);
    WGPUShaderModuleDescriptor md = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
    md.nextInChain = &src.chain;
    sShader = wgpuDeviceCreateShaderModule(sDev, &md);
    WGPUBindGroupLayoutEntry e[5];
    for (int i = 0; i < 5; i++) {
        e[i] = (WGPUBindGroupLayoutEntry)WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT;
        e[i].binding = (u32)i;
        e[i].visibility = WGPUShaderStage_Fragment;
    }
    e[0].buffer.type = WGPUBufferBindingType_Uniform;
    e[2].buffer.type = WGPUBufferBindingType_ReadOnlyStorage;
    e[1].texture.sampleType = e[3].texture.sampleType = WGPUTextureSampleType_Uint;
    e[1].texture.viewDimension = e[3].texture.viewDimension = WGPUTextureViewDimension_2D;
    e[4].texture.sampleType = WGPUTextureSampleType_Float;
    e[4].texture.viewDimension = WGPUTextureViewDimension_2D;
    WGPUBindGroupLayoutDescriptor ld = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT;
    ld.entryCount = 5;
    ld.entries = e;
    sLayout = wgpuDeviceCreateBindGroupLayout(sDev, &ld);
    WGPUPipelineLayoutDescriptor pd = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT;
    pd.bindGroupLayoutCount = 1;
    pd.bindGroupLayouts = &sLayout;
    sPipeLayout = wgpuDeviceCreatePipelineLayout(sDev, &pd);
    WGPUTextureDescriptor td = WGPU_TEXTURE_DESCRIPTOR_INIT;
    td.size = (WGPUExtent3D){256, 384, 1};
    td.format = WGPUTextureFormat_RG32Uint;
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst | WGPUTextureUsage_RenderAttachment |
               WGPUTextureUsage_CopySrc;
    sDeferredTex = wgpuDeviceCreateTexture(sDev, &td);
    sDeferredView = wgpuTextureCreateView(sDeferredTex, NULL);
    td.format = WGPUTextureFormat_BGRA8Unorm;
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    sOverlayTex = wgpuDeviceCreateTexture(sDev, &td);
    sOverlayView = wgpuTextureCreateView(sOverlayTex, NULL);
    WGPUBufferDescriptor bd = WGPU_BUFFER_DESCRIPTOR_INIT;
    bd.size = 32;
    bd.usage = WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst;
    sUniform = wgpuDeviceCreateBuffer(sDev, &bd);
    bd.size = 384 * 4;
    bd.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst;
    sLines = wgpuDeviceCreateBuffer(sDev, &bd);
    return 1;
}

static WGPURenderPipeline pipeline(WGPUTextureFormat fmt) {
    int i = 0;
    for (; i < 4 && sPipes[i].pipe; i++)
        if (sPipes[i].fmt == fmt) return sPipes[i].pipe;
    if (i == 4) i = 3;
    WGPURenderPipelineDescriptor rp = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
    rp.layout = sPipeLayout;
    rp.vertex.module = sShader;
    rp.vertex.entryPoint = sv("vfull");
    WGPUColorTargetState ct = WGPU_COLOR_TARGET_STATE_INIT;
    ct.format = fmt;
    WGPUFragmentState fs = WGPU_FRAGMENT_STATE_INIT;
    fs.module = sShader;
    fs.entryPoint = sv("fcomp");
    fs.targetCount = 1;
    fs.targets = &ct;
    rp.fragment = &fs;
    sPipes[i].fmt = fmt;
    return sPipes[i].pipe = wgpuDeviceCreateRenderPipeline(sDev, &rp);
}

static WGPUBindGroup group(WGPUTextureView pic) {
    for (int i = 0; i < 2; i++)
        if (sGroups[i].group && sGroups[i].pic == pic) return sGroups[i].group;
    int i = sGroups[0].group ? 1 : 0;
    if (sGroups[i].group) wgpuBindGroupRelease(sGroups[i].group);
    WGPUBindGroupEntry g[5];
    for (int k = 0; k < 5; k++) g[k] = (WGPUBindGroupEntry)WGPU_BIND_GROUP_ENTRY_INIT, g[k].binding = (u32)k;
    g[4].textureView = sOverlayView;
    g[0].buffer = sUniform, g[0].size = 32;
    g[1].textureView = sDeferredView;
    g[2].buffer = sLines, g[2].size = 384 * 4;
    g[3].textureView = pic;
    WGPUBindGroupDescriptor gd = WGPU_BIND_GROUP_DESCRIPTOR_INIT;
    gd.layout = sLayout;
    gd.entryCount = 5;
    gd.entries = g;
    sGroups[i].pic = pic;
    return sGroups[i].group = wgpuDeviceCreateBindGroup(sDev, &gd);
}

static void frame_lines(const uint32_t *const lines[2], void *picture3d, int scale) {
    for (int s = 0; s < 2; s++) wgpuQueueWriteBuffer(sQueue, sLines, (u64)s * 192 * 4, lines[s], 192 * 4);
    sPic = picture3d;
    sScale = scale;
    sFrames++;
}

void wdisp_frame(const uint32_t *const deferred[2], const uint32_t *const lines[2], void *picture3d, int scale) {
    if (!setup()) return;
    for (int s = 0; s < 2; s++) {
        WGPUTexelCopyTextureInfo dst = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
        dst.texture = sDeferredTex;
        dst.origin.y = 192u * (u32)s;
        WGPUTexelCopyBufferLayout l = WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT;
        l.bytesPerRow = 256 * 8;
        l.rowsPerImage = 192;
        WGPUExtent3D size = {256, 192, 1};
        wgpuQueueWriteTexture(sQueue, &dst, deferred[s], 256 * 192 * 8, &l, &size);
    }
    frame_lines(lines, picture3d, scale);
}

enum { VRAM_SIZE = GPU2D_VRAM_OVERLAP + 74 * 0x4000, BANKS_SIZE = GPU2D_VRAM_ZERO };
static WGPUShaderModule sShader2d;
static WGPURenderPipeline sPipe2d;
static WGPUBindGroup sGroup2d;
static WGPUBuffer s2dBuf[6];
static const u64 k2dSize[6] = {VRAM_SIZE, 2 * 192 * GPU2D_LINE_WORDS * 4, 2 * 64 * 4, GPU2D_MAX_VERSIONS * 0x800,
                               GPU2D_MAX_VERSIONS * 0x800, 2 * 256 * 4};
static uint8_t sBanksCopy[BANKS_SIZE];

static int setup2d(void) {
    if (sPipe2d) return 1;
    if (!setup()) return 0;
    WGPUShaderSourceWGSL src = WGPU_SHADER_SOURCE_WGSL_INIT;
    src.code = sv(kShader2d);
    WGPUShaderModuleDescriptor md = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
    md.nextInChain = &src.chain;
    sShader2d = wgpuDeviceCreateShaderModule(sDev, &md);
    WGPUBindGroupLayoutEntry e[6];
    WGPUBindGroupEntry g[6];
    for (int i = 0; i < 6; i++) {
        e[i] = (WGPUBindGroupLayoutEntry)WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT;
        e[i].binding = (u32)i;
        e[i].visibility = WGPUShaderStage_Fragment;
        e[i].buffer.type = WGPUBufferBindingType_ReadOnlyStorage;
        WGPUBufferDescriptor bd = WGPU_BUFFER_DESCRIPTOR_INIT;
        bd.size = k2dSize[i];
        bd.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst;
        s2dBuf[i] = wgpuDeviceCreateBuffer(sDev, &bd);
        g[i] = (WGPUBindGroupEntry)WGPU_BIND_GROUP_ENTRY_INIT;
        g[i].binding = (u32)i;
        g[i].buffer = s2dBuf[i];
        g[i].size = k2dSize[i];
    }
    WGPUBindGroupLayoutDescriptor ld = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT;
    ld.entryCount = 6;
    ld.entries = e;
    WGPUBindGroupLayout layout = wgpuDeviceCreateBindGroupLayout(sDev, &ld);
    WGPUBindGroupDescriptor gd = WGPU_BIND_GROUP_DESCRIPTOR_INIT;
    gd.layout = layout;
    gd.entryCount = 6;
    gd.entries = g;
    sGroup2d = wgpuDeviceCreateBindGroup(sDev, &gd);
    WGPUPipelineLayoutDescriptor pd = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT;
    pd.bindGroupLayoutCount = 1;
    pd.bindGroupLayouts = &layout;
    WGPURenderPipelineDescriptor rp = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
    rp.layout = wgpuDeviceCreatePipelineLayout(sDev, &pd);
    rp.vertex.module = sShader2d;
    rp.vertex.entryPoint = sv("vfull2d");
    WGPUColorTargetState ct = WGPU_COLOR_TARGET_STATE_INIT;
    ct.format = WGPUTextureFormat_RG32Uint;
    WGPUFragmentState fs = WGPU_FRAGMENT_STATE_INIT;
    fs.module = sShader2d;
    fs.entryPoint = sv("f2d");
    fs.targetCount = 1;
    fs.targets = &ct;
    rp.fragment = &fs;
    sPipe2d = wgpuDeviceCreateRenderPipeline(sDev, &rp);
    return 1;
}

static void upload_banks(const uint8_t *const banks[9]) {
    static const u32 kOffset[9] = GPU2D_BANK_OFFSET;
    static const u32 kSize[9] = {0x20000, 0x20000, 0x20000, 0x20000, 0x10000, 0x4000, 0x4000, 0x8000, 0x4000};
    enum { PIECE = 0x1000 };
    for (int b = 0; b < 9; b++) {
        uint8_t *copy = sBanksCopy + kOffset[b];
        for (u32 o = 0; o < kSize[b];) {
            if (!memcmp(copy + o, banks[b] + o, PIECE)) { o += PIECE; continue; }
            u32 end = o + PIECE;
            while (end < kSize[b] && memcmp(copy + end, banks[b] + end, PIECE)) end += PIECE;
            memcpy(copy + o, banks[b] + o, end - o);
            wgpuQueueWriteBuffer(sQueue, s2dBuf[0], kOffset[b] + o, banks[b] + o, end - o);
            o = end;
        }
    }
}

void wdisp_frame_2d(const void *gpuFrame, const uint8_t *const banks[9], const uint32_t *const lines[2],
                    void *picture3d, int scale) {
    const Gpu2dGpuFrame *f = gpuFrame;
    if (!setup2d()) return;
    upload_banks(banks);
    if (f->overlapSize) wgpuQueueWriteBuffer(sQueue, s2dBuf[0], GPU2D_VRAM_OVERLAP, f->overlap, f->overlapSize);
    wgpuQueueWriteBuffer(sQueue, s2dBuf[1], 0, f->lines, sizeof f->lines);
    wgpuQueueWriteBuffer(sQueue, s2dBuf[2], 0, f->tables, sizeof f->tables);
    wgpuQueueWriteBuffer(sQueue, s2dBuf[3], 0, f->palettes, (size_t)f->paletteCount * 0x800);
    wgpuQueueWriteBuffer(sQueue, s2dBuf[4], 0, f->oams, (size_t)f->oamCount * 0x800);
    wgpuQueueWriteBuffer(sQueue, s2dBuf[5], 0, f->obj0, sizeof f->obj0);
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(sDev, NULL);
    WGPURenderPassColorAttachment ca = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
    ca.view = sDeferredView;
    ca.loadOp = WGPULoadOp_Clear;
    ca.storeOp = WGPUStoreOp_Store;
    WGPURenderPassDescriptor rd = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    rd.colorAttachmentCount = 1;
    rd.colorAttachments = &ca;
    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(enc, &rd);
    wgpuRenderPassEncoderSetPipeline(pass, sPipe2d);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, sGroup2d, 0, NULL);
    wgpuRenderPassEncoderDraw(pass, 3, 1, 0, 0);
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, NULL);
    wgpuQueueSubmit(sQueue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);
    wgpuCommandEncoderRelease(enc);
    frame_lines(lines, picture3d, scale);
}

static void composite(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat fmt, int w, int h, int fill) {
    float vp[8] = {0, 0, (float)w, (float)h};
    if (!fill) wdisp_letterbox(w, h, vp);
    memcpy(&vp[4], &(u32){(u32)sScale}, 4);
    memcpy(&vp[5], &(u32){(u32)sOverlayOn}, 4);
    wgpuQueueWriteBuffer(sQueue, sUniform, 0, vp, sizeof vp);
    WGPURenderPassColorAttachment ca = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
    ca.view = view;
    ca.loadOp = WGPULoadOp_Clear;
    ca.storeOp = WGPUStoreOp_Store;
    ca.clearValue = (WGPUColor){0, 0, 0, 1};
    WGPURenderPassDescriptor rd = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    rd.colorAttachmentCount = 1;
    rd.colorAttachments = &ca;
    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(enc, &rd);
    if (sPic) {
        wgpuRenderPassEncoderSetPipeline(pass, pipeline(fmt));
        wgpuRenderPassEncoderSetBindGroup(pass, 0, group(sPic), 0, NULL);
        wgpuRenderPassEncoderDraw(pass, 3, 1, 0, 0);
    }
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
}

static void submit(WGPUCommandEncoder enc) {
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, NULL);
    wgpuQueueSubmit(sQueue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);
    wgpuCommandEncoderRelease(enc);
}

static WGPUTexture sReadTex;
static WGPUTextureView sReadView;
static WGPUBuffer sReadBuf;
static int sReadW, sReadH;
static void on_mapped(WGPUMapAsyncStatus status, WGPUStringView msg, void *u1, void *u2) {
    (void)msg, (void)u2;
    *(int *)u1 = status == WGPUMapAsyncStatus_Success ? 1 : -1;
}
static int read_back(int w, int h, int fill, uint32_t *out) {
    if (!setup() || w <= 0 || h <= 0) return 0;
    u32 stride = ((u32)w * 4 + 255) & ~255u;
    if (w != sReadW || h != sReadH) {
        if (sReadTex) wgpuTextureViewRelease(sReadView), wgpuTextureRelease(sReadTex), wgpuBufferRelease(sReadBuf);
        WGPUTextureDescriptor td = WGPU_TEXTURE_DESCRIPTOR_INIT;
        td.size = (WGPUExtent3D){(u32)w, (u32)h, 1};
        td.format = WGPUTextureFormat_BGRA8Unorm;
        td.usage = WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_CopySrc;
        sReadTex = wgpuDeviceCreateTexture(sDev, &td);
        sReadView = wgpuTextureCreateView(sReadTex, NULL);
        WGPUBufferDescriptor bd = WGPU_BUFFER_DESCRIPTOR_INIT;
        bd.size = (u64)stride * (u32)h;
        bd.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
        sReadBuf = wgpuDeviceCreateBuffer(sDev, &bd);
        sReadW = w, sReadH = h;
    }
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(sDev, NULL);
    composite(enc, sReadView, WGPUTextureFormat_BGRA8Unorm, w, h, fill);
    WGPUTexelCopyTextureInfo src = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
    src.texture = sReadTex;
    WGPUTexelCopyBufferInfo dst = WGPU_TEXEL_COPY_BUFFER_INFO_INIT;
    dst.buffer = sReadBuf;
    dst.layout.bytesPerRow = stride;
    dst.layout.rowsPerImage = (u32)h;
    WGPUExtent3D size = {(u32)w, (u32)h, 1};
    wgpuCommandEncoderCopyTextureToBuffer(enc, &src, &dst, &size);
    submit(enc);
    int mapped = 0;
    WGPUBufferMapCallbackInfo mc = WGPU_BUFFER_MAP_CALLBACK_INFO_INIT;
    mc.mode = WGPUCallbackMode_AllowSpontaneous;
    mc.callback = on_mapped;
    mc.userdata1 = &mapped;
    wgpuBufferMapAsync(sReadBuf, WGPUMapMode_Read, 0, (u64)stride * (u32)h, mc);
    while (!mapped) wgpuDevicePoll(sDev, 1, NULL);
    if (mapped < 0) return 0;
    const u32 *p = wgpuBufferGetConstMappedRange(sReadBuf, 0, (u64)stride * (u32)h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) out[y * w + x] = p[y * (stride / 4) + x] & 0xffffff;
    wgpuBufferUnmap(sReadBuf);
    return 1;
}

int wdisp_read_2d(uint32_t *out) {
    if (!sPipe2d) return 0;
    static WGPUBuffer buf;
    enum { SIZE = 256 * 384 * 8 };
    if (!buf) {
        WGPUBufferDescriptor bd = WGPU_BUFFER_DESCRIPTOR_INIT;
        bd.size = SIZE;
        bd.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
        buf = wgpuDeviceCreateBuffer(sDev, &bd);
    }
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(sDev, NULL);
    WGPUTexelCopyTextureInfo src = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
    src.texture = sDeferredTex;
    WGPUTexelCopyBufferInfo dst = WGPU_TEXEL_COPY_BUFFER_INFO_INIT;
    dst.buffer = buf;
    dst.layout.bytesPerRow = 256 * 8;
    dst.layout.rowsPerImage = 384;
    WGPUExtent3D size = {256, 384, 1};
    wgpuCommandEncoderCopyTextureToBuffer(enc, &src, &dst, &size);
    submit(enc);
    int mapped = 0;
    WGPUBufferMapCallbackInfo mc = WGPU_BUFFER_MAP_CALLBACK_INFO_INIT;
    mc.mode = WGPUCallbackMode_AllowSpontaneous;
    mc.callback = on_mapped;
    mc.userdata1 = &mapped;
    wgpuBufferMapAsync(buf, WGPUMapMode_Read, 0, SIZE, mc);
    while (!mapped) wgpuDevicePoll(sDev, 1, NULL);
    if (mapped < 0) return 0;
    memcpy(out, wgpuBufferGetConstMappedRange(buf, 0, SIZE), SIZE);
    wgpuBufferUnmap(buf);
    return 1;
}

const uint32_t *wdisp_screens(void) {
    static uint32_t screens[256 * 384];
    static u32 readFrame;
    if (readFrame != sFrames) {
        readFrame = sFrames;
        if (!read_back(256, 384, 1, screens)) memset(screens, 0, sizeof screens);
    }
    return screens;
}

int wdisp_read_window(int w, int h, uint32_t *out) { return read_back(w, h, 0, out); }

static WGPUSurface sSurface;
static WGPUSurfaceConfiguration sConfig;

int wdisp_attach(int kind, void *display, uint64_t window, int vsync) {
    if (!setup()) return 0;
    WGPUSurfaceSourceXlibWindow x11 = WGPU_SURFACE_SOURCE_XLIB_WINDOW_INIT;
    WGPUSurfaceSourceWaylandSurface wl = WGPU_SURFACE_SOURCE_WAYLAND_SURFACE_INIT;
    WGPUSurfaceSourceMetalLayer metal = WGPU_SURFACE_SOURCE_METAL_LAYER_INIT;
    WGPUSurfaceDescriptor sd = WGPU_SURFACE_DESCRIPTOR_INIT;
    if (kind == WDISP_METAL) {
        metal.layer = display;
        sd.nextInChain = &metal.chain;
    } else if (kind == WDISP_X11) {
        x11.display = display;
        x11.window = window;
        sd.nextInChain = &x11.chain;
    } else if (kind == WDISP_WAYLAND) {
        wl.display = display;
        wl.surface = (void *)(uintptr_t)window;
        sd.nextInChain = &wl.chain;
    } else {
        return 0;
    }
    sSurface = wgpuInstanceCreateSurface(sInst, &sd);
    if (!sSurface) return 0;
    WGPUSurfaceCapabilities caps = WGPU_SURFACE_CAPABILITIES_INIT;
    if (wgpuSurfaceGetCapabilities(sSurface, sAdapter, &caps) != WGPUStatus_Success || !caps.formatCount) {
        fprintf(stderr, "wgpu: the window can't be drawn into by this adapter\n");
        wgpuSurfaceRelease(sSurface);
        sSurface = 0;
        return 0;
    }
    WGPUTextureFormat fmt = caps.formats[0];
    for (size_t i = 0; i < caps.formatCount; i++)
        if (caps.formats[i] == WGPUTextureFormat_BGRA8Unorm || caps.formats[i] == WGPUTextureFormat_RGBA8Unorm) {
            fmt = caps.formats[i];
            break;
        }
    WGPUPresentMode mode = WGPUPresentMode_Fifo;
    for (size_t i = 0; !vsync && i < caps.presentModeCount; i++) {
        if (caps.presentModes[i] == WGPUPresentMode_Immediate) mode = WGPUPresentMode_Immediate;
        if (caps.presentModes[i] == WGPUPresentMode_Mailbox && mode != WGPUPresentMode_Immediate)
            mode = WGPUPresentMode_Mailbox;
    }
    wgpuSurfaceCapabilitiesFreeMembers(caps);
    sConfig = (WGPUSurfaceConfiguration)WGPU_SURFACE_CONFIGURATION_INIT;
    sConfig.device = sDev;
    sConfig.format = fmt;
    sConfig.usage = WGPUTextureUsage_RenderAttachment;
    sConfig.presentMode = mode;
    sConfig.alphaMode = WGPUCompositeAlphaMode_Auto;
    return 1;
}
int wdisp_presenting(void) { return sSurface != 0; }

void wdisp_overlay(const uint32_t *argb, int changed) {
    if (!setup()) return;
    sOverlayOn = argb != NULL;
    if (!argb || !changed) return;
    WGPUTexelCopyTextureInfo dst = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
    dst.texture = sOverlayTex;
    WGPUTexelCopyBufferLayout l = WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT;
    l.bytesPerRow = 256 * 4;
    l.rowsPerImage = 384;
    WGPUExtent3D size = {256, 384, 1};
    wgpuQueueWriteTexture(sQueue, &dst, argb, 256 * 384 * 4, &l, &size);
}

void wdisp_present(int w, int h) {
    if (!sSurface || w <= 0 || h <= 0) return;
    for (int tries = 0; tries < 2; tries++) {
        if (sConfig.width != (u32)w || sConfig.height != (u32)h) {
            sConfig.width = (u32)w, sConfig.height = (u32)h;
            wgpuSurfaceConfigure(sSurface, &sConfig);
        }
        WGPUSurfaceTexture st = WGPU_SURFACE_TEXTURE_INIT;
        wgpuSurfaceGetCurrentTexture(sSurface, &st);
        if (st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
            st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
            if (st.texture) wgpuTextureRelease(st.texture);
            if (st.status == WGPUSurfaceGetCurrentTextureStatus_Timeout) return;
            sConfig.width = 0;
            continue;
        }
        WGPUTextureView view = wgpuTextureCreateView(st.texture, NULL);
        WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(sDev, NULL);
        composite(enc, view, sConfig.format, w, h, 0);
        submit(enc);
        wgpuSurfacePresent(sSurface);
        wgpuTextureViewRelease(view);
        wgpuTextureRelease(st.texture);
        return;
    }
}

#endif
