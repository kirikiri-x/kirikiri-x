#pragma once
#include <cstdint>

namespace LibRuntime::Rendering {

    // CPUサイドのレイヤー合成処理
    // ピクセルフォーマット: ARGB8888 (0xAARRGGBB)
    class LayerCompositor {
    public:
        // dst バッファの指定座標に src をアルファ合成する
        // dst_x, dst_y: dst バッファ上の描画開始座標
        static void composite_alpha(
            uint32_t* dst, int dst_w, int dst_h,
            const uint32_t* src, int src_w, int src_h,
            int dst_x, int dst_y
        );

        // 矩形を単色で塗りつぶす
        static void fill_rect(
            uint32_t* dst, int dst_w, int dst_h,
            int x, int y, int w, int h,
            uint32_t color // ARGB8888
        );
    };

} // namespace LibRuntime::Rendering
