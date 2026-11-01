#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "touch_controls.h"

static int sFails;
#define CHECK(c, ...) do { if (!(c)) { sFails++; printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

typedef struct {
    const char *name;
    int w, h;
    float scale;
    float up[4];
    float side[4];
} Device;

static const Device kDevices[] = {
    {"iPhone SE (3rd gen)", 375, 667, 2, {0, 20, 0, 0}, {0, 0, 0, 0}},
    {"iPhone 13 mini", 375, 812, 3, {0, 50, 0, 34}, {50, 0, 50, 21}},
    {"iPhone 16", 393, 852, 3, {0, 59, 0, 34}, {59, 0, 59, 21}},
    {"iPhone 16 Pro Max", 440, 956, 3, {0, 62, 0, 34}, {62, 0, 62, 21}},
    {"iPhone 11", 414, 896, 2, {0, 48, 0, 34}, {48, 0, 48, 21}},
    {"iPad mini (6th gen)", 744, 1133, 2, {0, 24, 0, 20}, {0, 24, 0, 20}},
    {"iPad (10th gen)", 820, 1180, 2, {0, 24, 0, 20}, {0, 24, 0, 20}},
    {"iPad Pro 13-inch", 1032, 1376, 2, {0, 24, 0, 20}, {0, 24, 0, 20}},
};

static int contains(TcRect outer, TcRect r, float slack) {
    return r.x >= outer.x - slack && r.y >= outer.y - slack && r.x + r.w <= outer.x + outer.w + slack &&
           r.y + r.h <= outer.y + outer.h + slack;
}
static int overlap(TcRect a, TcRect b) {
    return a.x < b.x + b.w && b.x < a.x + a.w && a.y < b.y + b.h && b.y < a.y + a.h;
}
static int overlap_controls(int i, int j, TcRect a, TcRect b) {
    if (i <= TC_Y && j <= TC_Y) {
        float dx = (a.x + a.w / 2) - (b.x + b.w / 2), dy = (a.y + a.h / 2) - (b.y + b.h / 2);
        return sqrtf(dx * dx + dy * dy) < (a.w + b.w) / 2;
    }
    return overlap(a, b);
}
static float cx(TcRect r) { return r.x + r.w / 2; }
static float cy(TcRect r) { return r.y + r.h / 2; }

static const char *kName[TC_COUNT] = {"A", "B", "X", "Y", "L", "R", "START", "SELECT", "MENU", "DPAD"};

static void write_preview(const char *dir, const char *dev, const char *orient, int controls, const TcLayout *l,
                          float pt, const float safe[4]) {
    int W = l->w, H = l->h;
    uint32_t *img = calloc((size_t)W * H, 4);
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            int unsafe = x < safe[0] || y < safe[1] || x >= W - safe[2] || y >= H - safe[3];
            img[y * W + x] = unsafe ? 0x202020 : 0x000000;
        }
    for (int y = 0; y < (int)l->screens.h; y++)
        for (int x = 0; x < (int)l->screens.w; x++) {
            int X = (int)l->screens.x + x, Y = (int)l->screens.y + y;
            int top = y < l->screens.h / 2;
            int u = x * 256 / (int)l->screens.w, v = (y % (int)(l->screens.h / 2)) * 192 / (int)(l->screens.h / 2);
            uint32_t c = top ? (0x3a7d44u + ((u / 32 + v / 32) % 2) * 0x101010u) : (0x6b8fc2u + ((u / 32 + v / 32) % 2) * 0x101010u);
            if (X >= 0 && X < W && Y >= 0 && Y < H) img[Y * W + X] = c;
        }
    if (controls) {
        for (int b = 0; b < TC_COUNT; b++) {
            TcRect r = l->button[b];
            int bw = (int)lroundf(r.w), bh = (int)lroundf(r.h), bx = (int)lroundf(r.x), by = (int)lroundf(r.y);
            uint32_t *px = malloc((size_t)bw * bh * 4);
            tc_draw(px, bw, bh, b, b == TC_A, b == TC_DPAD ? (1u << 4 | 1u << 6) : 0);
            for (int y = 0; y < bh; y++)
                for (int x = 0; x < bw; x++) {
                    int X = bx + x, Y = by + y;
                    if (X < 0 || X >= W || Y < 0 || Y >= H) continue;
                    uint32_t s = px[y * bw + x], d = img[Y * W + X];
                    float a = (float)(s >> 24) / 255.0f;
                    uint32_t o = 0;
                    for (int sh = 0; sh < 24; sh += 8)
                        o |= (uint32_t)((float)(s >> sh & 255) * a + (float)(d >> sh & 255) * (1 - a) + 0.5f) << sh;
                    img[Y * W + X] = o;
                }
            free(px);
        }
    }
    char path[1024], name[256];
    snprintf(name, sizeof name, "%s_%s_%s", dev, orient, controls ? "buttons" : "controller");
    for (char *p = name; *p; p++) if (*p == ' ' || *p == '(' || *p == ')') *p = '_';
    snprintf(path, sizeof path, "%s/%s.ppm", dir, name);
    FILE *f = fopen(path, "wb");
    if (f) {
        fprintf(f, "P6\n%d %d\n255\n", W, H);
        for (int i = 0; i < W * H; i++) { unsigned char rgb[3] = {img[i] >> 16, img[i] >> 8, img[i]}; fwrite(rgb, 1, 3, f); }
        fclose(f);
    }
    free(img);
    (void)pt;
}

static void check_layout(const Device *d, int side, int controls, const char *dir) {
    float pt = d->scale;
    int w = (int)((side ? d->h : d->w) * pt), h = (int)((side ? d->w : d->h) * pt);
    const float *in = side ? d->side : d->up;
    float safe[4] = {in[0] * pt, in[1] * pt, in[2] * pt, in[3] * pt};
    TcLayout l;
    tc_layout(&l, w, h, pt, safe, controls);
    TcRect sr = {safe[0], safe[1], w - safe[0] - safe[2], h - safe[1] - safe[3]};
    const char *o = side ? "side" : "upright";
    CHECK(contains(sr, l.screens, 0.5f), "%s %s: screens outside the safe area", d->name, o);
    CHECK(fabsf(l.screens.h - l.screens.w * 1.5f) < 1.0f, "%s %s: screens not 2:3 (%.1f x %.1f)", d->name, o,
          l.screens.w, l.screens.h);
    float sw = l.screens.w / pt;
    if (controls) {
        CHECK(sw >= 230, "%s %s: screens only %.0f pt wide", d->name, o, sw);
        for (int i = 0; i < TC_COUNT; i++) {
            TcRect a = l.button[i];
            if (i == TC_SELECT || i == TC_L || i == TC_R || i == TC_X || i == TC_Y) {
                CHECK(a.w == 0 && a.h == 0, "%s %s: a %s button", d->name, o, kName[i]);
                continue;
            }
            CHECK(a.w > 0 && a.h > 0, "%s %s: %s has no size", d->name, o, kName[i]);
            CHECK(contains(sr, a, 0.5f), "%s %s: %s outside the safe area", d->name, o, kName[i]);
            CHECK(!overlap(a, l.screens), "%s %s: %s over the screens", d->name, o, kName[i]);
            for (int j = i + 1; j < TC_COUNT; j++)
                CHECK(i == TC_DPAD || j == TC_DPAD || !overlap_controls(i, j, a, l.button[j]), "%s %s: %s and %s overlap",
                      d->name, o, kName[i], kName[j]);
            float minSide = (i <= TC_Y ? 44 : i == TC_DPAD ? 120 : 26) * pt;
            if (i == TC_DPAD) CHECK(l.stick_size >= 110 * pt, "%s %s: circle pad only %.0f pt", d->name, o, l.stick_size / pt);
            CHECK(a.h >= minSide - 0.5f && a.w >= minSide - 0.5f, "%s %s: %s too small (%.0f x %.0f pt)", d->name, o,
                  kName[i], a.w / pt, a.h / pt);
        }
        printf("  %-22s %-7s screens %3.0fx%3.0f pt (DS x%.2f), A/B %2.0f pt, circle pad %3.0f pt\n", d->name, o,
               l.screens.w / pt, l.screens.h / pt, l.screens.w / 256.0f, l.button[TC_A].w / pt, l.stick_size / pt);
    } else {
        CHECK(fabsf(l.screens.w - sr.w) < 1 || fabsf(l.screens.h - sr.h) < 1, "%s %s: screens not as large as they fit",
              d->name, o);
    }
    if (dir) write_preview(dir, d->name, o, controls, &l, pt, safe);
}

static void check_touch(void) {
    const Device *d = &kDevices[2];
    float pt = d->scale, safe[4] = {0, d->up[1] * pt, 0, d->up[3] * pt};
    int w = (int)(d->w * pt), h = (int)(d->h * pt);
    TcLayout l;
    tc_layout(&l, w, h, pt, safe, 1);
    TcState s;
    tc_reset(&s);
    static const uint32_t kBits[] = {1u << 0, 1u << 1, 1u << 10, 1u << 11, 1u << 9, 1u << 8, 1u << 3, 1u << 2, 0, 0, 0};
    for (int b = 0; b < TC_DPAD; b++) {
        if (l.button[b].w <= 0) continue;
        tc_pointer(&s, &l, 7, TC_DOWN, cx(l.button[b]), cy(l.button[b]));
        CHECK(tc_keys(&s) == kBits[b], "button %s gives keys %#x", kName[b], tc_keys(&s));
        CHECK(tc_held(&s) == 1u << b, "button %s held %#x", kName[b], tc_held(&s));
        tc_pointer(&s, &l, 7, TC_UP, cx(l.button[b]), cy(l.button[b]));
        CHECK(tc_keys(&s) == 0, "button %s not released", kName[b]);
    }
    tc_pointer(&s, &l, 1, TC_DOWN, cx(l.button[TC_A]), cy(l.button[TC_A]));
    tc_pointer(&s, &l, 1, TC_MOVE, cx(l.button[TC_B]), cy(l.button[TC_B]));
    CHECK(tc_keys(&s) == (1u << 1), "slide A -> B: keys %#x", tc_keys(&s));
    tc_pointer(&s, &l, 1, TC_MOVE, l.button[TC_B].x + l.button[TC_B].w * 3, (float)h - 1);
    CHECK(tc_keys(&s) == 0, "slid off: keys %#x", tc_keys(&s));
    tc_pointer(&s, &l, 1, TC_MOVE, cx(l.button[TC_A]), cy(l.button[TC_A]));
    CHECK(tc_keys(&s) == 1, "slid back onto A: keys %#x", tc_keys(&s));
    TcRect dp = l.button[TC_DPAD];
    float pcx = dp.x + dp.w / 2, pcy = dp.y + dp.h / 2;
    tc_pointer(&s, &l, 1, TC_UP, 0, 0);
    {
        TcLayout st = l;
        float range = l.stick_size * TC_KNOB_TRAVEL, sx, sy, scx, scy;
        tc_pointer(&s, &st, 2, TC_DOWN, pcx, pcy);
        CHECK(tc_stick_center(&s, &scx, &scy) && fabsf(scx - pcx) < 1 && fabsf(scy - pcy) < 1, "circle pad where touched");
        tc_pointer(&s, &st, 2, TC_MOVE, pcx + range * 0.05f, pcy);
        CHECK(tc_stick(&s, &sx, &sy) && sx == 0 && sy == 0 && tc_keys(&s) == 0, "stick dead zone: %f %f keys %#x", sx, sy,
              tc_keys(&s));
        tc_pointer(&s, &st, 2, TC_MOVE, pcx + range * 0.3f, pcy);
        CHECK(tc_stick(&s, &sx, &sy) && sx > 0.15f && sx < 0.3f && fabsf(sy) < 1e-4f && tc_keys(&s) == 0,
              "stick small push: %f %f keys %#x", sx, sy, tc_keys(&s));
        struct { float a; uint32_t k; } sd[] = {
            {0, 1u << 4}, {90, 1u << 6}, {180, 1u << 5}, {270, 1u << 7},
            {45, 1u << 4 | 1u << 6}, {135, 1u << 5 | 1u << 6}, {225, 1u << 5 | 1u << 7}, {315, 1u << 4 | 1u << 7},
        };
        for (unsigned i = 0; i < sizeof sd / sizeof sd[0]; i++) {
            float a = sd[i].a * 3.14159265f / 180;
            tc_pointer(&s, &st, 2, TC_MOVE, pcx + range * 2 * cosf(a), pcy - range * 2 * sinf(a));
            int held = tc_stick(&s, &sx, &sy);
            CHECK(held && fabsf(sqrtf(sx * sx + sy * sy) - 1) < 1e-3f && fabsf(sx - cosf(a)) < 1e-3f &&
                  fabsf(sy - sinf(a)) < 1e-3f && tc_keys(&s) == sd[i].k,
                  "stick full at %.0f degrees: %f %f keys %#x, want %#x", sd[i].a, sx, sy, tc_keys(&s), sd[i].k);
        }
        tc_pointer(&s, &st, 2, TC_UP, 0, 0);
        CHECK(!tc_stick(&s, &sx, &sy) && sx == 0 && sy == 0 && tc_keys(&s) == 0, "stick released");
        CHECK(!tc_stick_center(&s, &scx, &scy), "circle pad gone when released");
    }
    TcRect sc = l.screens;
    int x, y;
    tc_pointer(&s, &l, 3, TC_DOWN, sc.x + 0.1f, sc.y + sc.h / 2 + 0.1f);
    CHECK(tc_stylus(&s, &x, &y) && x == 0 && y == 0, "stylus top-left: %d,%d", x, y);
    tc_pointer(&s, &l, 3, TC_MOVE, sc.x + sc.w - 0.1f, sc.y + sc.h - 0.1f);
    CHECK(tc_stylus(&s, &x, &y) && x == 255 && y == 191, "stylus bottom-right: %d,%d", x, y);
    tc_pointer(&s, &l, 3, TC_MOVE, sc.x + sc.w / 2, sc.y + sc.h * 0.75f);
    CHECK(tc_stylus(&s, &x, &y) && x == 128 && y == 96, "stylus middle: %d,%d", x, y);
    tc_pointer(&s, &l, 3, TC_MOVE, sc.x - 50, sc.y);
    CHECK(tc_stylus(&s, &x, &y) && x == 0 && y == 0, "stylus dragged off: %d,%d", x, y);
    unsigned presses = tc_stylus_presses(&s);
    tc_pointer(&s, &l, 4, TC_DOWN, sc.x + sc.w / 4, sc.y + sc.h * 0.9f);
    CHECK(tc_stylus(&s, &x, &y) && x == 64 && y == 153 && tc_stylus_presses(&s) == presses + 1,
          "the second finger takes the stylus (a new press): %d,%d", x, y);
    tc_pointer(&s, &l, 3, TC_MOVE, sc.x + sc.w / 2, sc.y + sc.h * 0.75f);
    CHECK(tc_stylus(&s, &x, &y) && x == 64 && y == 153, "the first finger moving changes nothing: %d,%d", x, y);
    tc_pointer(&s, &l, 3, TC_UP, 0, 0);
    CHECK(tc_stylus(&s, &x, &y) && x == 64 && y == 153, "the first finger lifted: the second still holds it");
    tc_pointer(&s, &l, 4, TC_UP, 0, 0);
    CHECK(!tc_stylus(&s, &x, &y) && tc_stylus_presses(&s) == presses + 1, "both lifted");
    tc_pointer(&s, &l, 5, TC_DOWN, sc.x + sc.w / 2, sc.y + sc.h / 4);
    CHECK(!tc_stylus(&s, &x, &y) && tc_keys(&s) == 0, "the top screen does nothing");
    tc_pointer(&s, &l, 5, TC_UP, 0, 0);
    CHECK(tc_pointer(&s, &l, 6, TC_DOWN, cx(l.button[TC_A]), cy(l.button[TC_A])) == 0, "a button: not 'show'");
    tc_pointer(&s, &l, 6, TC_UP, 0, 0);
    TcLayout hidden;
    tc_layout(&hidden, w, h, pt, safe, 0);
    CHECK(tc_pointer(&s, &hidden, 8, TC_DOWN, 2, (float)h - safe[3] - 2) == 1, "hidden: a touch below asks for the buttons");
    tc_pointer(&s, &hidden, 8, TC_UP, 0, 0);
    CHECK(tc_pointer(&s, &hidden, 9, TC_DOWN, cx(hidden.screens), hidden.screens.y + hidden.screens.h * 0.75f) == 0 &&
          tc_stylus(&s, &x, &y), "hidden: the stylus works");
    tc_pointer(&s, &hidden, 9, TC_UP, 0, 0);
    tc_pointer(&s, &l, 99, TC_MOVE, 10, 10);
    tc_pointer(&s, &l, 99, TC_UP, 10, 10);
    CHECK(tc_keys(&s) == 0, "unknown pointers ignored");
    for (int i = 0; i < 20; i++) tc_pointer(&s, &l, 100 + i, TC_DOWN, cx(l.button[TC_B]), cy(l.button[TC_B]));
    CHECK(tc_keys(&s) == 2, "many fingers on B: keys %#x", tc_keys(&s));
    for (int i = 0; i < 20; i++) tc_pointer(&s, &l, 100 + i, TC_UP, 0, 0);
    CHECK(tc_keys(&s) == 0, "many fingers released: keys %#x", tc_keys(&s));
}

int main(int argc, char **argv) {
    const char *dir = argc > 1 ? argv[1] : NULL;
    for (unsigned i = 0; i < sizeof kDevices / sizeof kDevices[0]; i++)
        for (int side = 0; side < 2; side++)
            for (int controls = 1; controls >= 0; controls--) check_layout(&kDevices[i], side, controls, dir);
    check_touch();
    printf(sFails ? "touch_controls_test: %d FAILED\n" : "touch_controls_test: all passed\n", sFails);
    return sFails != 0;
}
