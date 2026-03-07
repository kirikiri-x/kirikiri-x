#pragma once
#include <vector>
#include <memory>
#include <tjs.h>
#include <tjsNative.h>
#include "interfaces/graphics.h"

namespace LibRuntime::NativeInstances {
    class LayerNativeInstance : public tTJSNativeInstance {
    public:
        LayerNativeInstance();
        tjs_error TJS_INTF_METHOD Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj);
        void TJS_INTF_METHOD Invalidate();

        void add_children(LayerNativeInstance *child);
        void remove_children(LayerNativeInstance *child);
        void set_position(tjs_int x, tjs_int y);
        void set_size(tjs_int width, tjs_int height);
        void set_visible(bool visible);

        // CPUバッファに子レイヤーを合成し、必要に応じてGPUテクスチャへアップロードする
        // 戻り値: GPUテクスチャハンドル (サイズが0の場合は nullptr)
        Interfaces::ITextureHandle* render(Interfaces::IGraphicsWindow* gfx);

        Interfaces::Rect get_render_rect() const {
            return { _rect.x, _rect.y, _rect.w, _rect.h };
        }

        // CPUバッファへの直接アクセス (TJS2スクリプトからのピクセル操作用)
        uint32_t* pixels() { return _pixels.data(); }
        void mark_dirty() { _dirty = true; }

    private:
        tTJSVariantClosure _owner_window;
        tTJSVariantClosure _parent_layer;
        std::vector<LayerNativeInstance*> _children;

        struct { int x, y, w, h; } _rect{};

        // CPUサイドのピクセルバッファ (ARGB8888)
        std::vector<uint32_t> _pixels;

        // GPUテクスチャハンドル
        std::unique_ptr<Interfaces::ITextureHandle> _texture;

        // CPUバッファがGPUより新しい場合 true (サイズ変更時も true にリセット)
        bool _dirty = true;

        // テクスチャを生成したウィンドウ。変わった場合は再生成する
        Interfaces::IGraphicsWindow* _last_gfx = nullptr;

        void resize_pixels(int w, int h);
    };
}
