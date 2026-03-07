#include "layer_compositor.h"
#include <algorithm>

using namespace LibRuntime::Rendering;

// ARGB8888 ピクセルからアルファ・RGB成分を取得するヘルパー
static inline uint8_t alpha_of(uint32_t c) { return (c >> 24) & 0xFF; }
static inline uint8_t red_of(uint32_t c)   { return (c >> 16) & 0xFF; }
static inline uint8_t green_of(uint32_t c) { return (c >>  8) & 0xFF; }
static inline uint8_t blue_of(uint32_t c)  { return  c        & 0xFF; }

static inline uint32_t make_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return (static_cast<uint32_t>(a) << 24)
         | (static_cast<uint32_t>(r) << 16)
         | (static_cast<uint32_t>(g) <<  8)
         |  static_cast<uint32_t>(b);
}

void LayerCompositor::composite_alpha(
    uint32_t* dst, int dst_w, int dst_h,
    const uint32_t* src, int src_w, int src_h,
    int dst_x, int dst_y
) {
    for (int sy = 0; sy < src_h; sy++) {
        int dy = dst_y + sy;
        if (dy < 0 || dy >= dst_h) continue;

        for (int sx = 0; sx < src_w; sx++) {
            int dx = dst_x + sx;
            if (dx < 0 || dx >= dst_w) continue;

            uint32_t s = src[sy * src_w + sx];
            uint32_t d = dst[dy * dst_w + dx];

            uint8_t sa = alpha_of(s);
            if (sa == 0) continue;
            if (sa == 255) {
                dst[dy * dst_w + dx] = s;
                continue;
            }

            // Porter-Duff Source Over
            uint8_t da = alpha_of(d);
            uint32_t inv = 255 - sa;
            uint8_t out_a = static_cast<uint8_t>(sa + (da * inv + 127) / 255);
            uint8_t out_r = static_cast<uint8_t>((red_of(s)   * sa + red_of(d)   * da * inv / 255 + 127) / 255);
            uint8_t out_g = static_cast<uint8_t>((green_of(s) * sa + green_of(d) * da * inv / 255 + 127) / 255);
            uint8_t out_b = static_cast<uint8_t>((blue_of(s)  * sa + blue_of(d)  * da * inv / 255 + 127) / 255);

            dst[dy * dst_w + dx] = make_argb(out_a, out_r, out_g, out_b);
        }
    }
}

void LayerCompositor::fill_rect(
    uint32_t* dst, int dst_w, int dst_h,
    int x, int y, int w, int h,
    uint32_t color
) {
    int x_end = std::min(x + w, dst_w);
    int y_end = std::min(y + h, dst_h);
    int x_start = std::max(x, 0);
    int y_start = std::max(y, 0);

    for (int py = y_start; py < y_end; py++) {
        for (int px = x_start; px < x_end; px++) {
            dst[py * dst_w + px] = color;
        }
    }
}
