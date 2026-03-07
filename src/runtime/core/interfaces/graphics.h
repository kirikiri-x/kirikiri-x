#pragma once
#include <cstdint>
#include <memory>

namespace LibRuntime::Interfaces {

    struct Rect {
        int x, y, w, h;
    };

    // GPU常駐テクスチャのハンドル
    // 各バックエンドがこれを継承して実装する
    class ITextureHandle {
    public:
        virtual ~ITextureHandle() = default;
        virtual int width() const = 0;
        virtual int height() const = 0;
    };

    // ウィンドウ＋描画バックエンド
    // 移植者はこのインターフェースを実装する
    class IGraphicsWindow {
    public:
        virtual ~IGraphicsWindow() = default;

        // --- テクスチャ管理 ---
        // CPUバッファと同サイズのGPUテクスチャを生成する
        virtual std::unique_ptr<ITextureHandle> create_texture(int w, int h) = 0;

        // CPUピクセルバッファをGPUテクスチャへアップロードする（dirty時のみ呼ぶ）
        // pixels: ARGB8888 フォーマット (0xAARRGGBB)、横幅 w ピクセルの連続配列
        virtual void update_texture(ITextureHandle* handle, const uint32_t* pixels) = 0;

        // --- フレーム描画 ---
        virtual void begin_frame() = 0;

        // GPUテクスチャを指定矩形へ描画する
        virtual void draw_texture(ITextureHandle* handle, const Rect& dst) = 0;

        virtual void end_frame() = 0;

        // --- ウィンドウ操作 ---
        virtual void set_title(const char* title) = 0;
        virtual void raise() = 0;
    };

    // グラフィックスシステム全体の初期化・管理
    // 移植者はこのインターフェースを実装し、KrkrRuntime::graphics にセットする
    class IGraphicsSystem {
    public:
        virtual ~IGraphicsSystem() = default;

        virtual void init() = 0;
        virtual void shutdown() = 0;

        // イベントをポーリングする。false を返したら終了要求
        virtual bool poll_events() = 0;

        virtual std::unique_ptr<IGraphicsWindow> create_window(const char* title, int w, int h) = 0;
    };

} // namespace LibRuntime::Interfaces
