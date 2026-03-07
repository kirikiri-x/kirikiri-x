#include <algorithm>
#include <tjs.h>
#include <tjsNative.h>
#include "layer_instance.h"
#include "window_instance.h"
#include "../libruntime.h"
#include "../native_classes/window.h"
#include "../native_classes/layer.h"
#include "../rendering/layer_tree.h"
#include "../rendering/layer_compositor.h"

using namespace LibRuntime::NativeInstances;
using namespace LibRuntime::Interfaces;
using namespace LibRuntime::Rendering;

LayerNativeInstance::LayerNativeInstance() {}

tjs_error LayerNativeInstance::Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) {
    if (numparams < 2) return TJS_E_BADPARAMCOUNT;

    auto window = param[0]->AsObjectClosure();
    if (window.Object == nullptr) return TJS_E_INVALIDPARAM;

    auto parent_layer = param[1]->AsObjectClosure();
    if (parent_layer.Object == nullptr) {
        parent_layer.Release();

        // 親レイヤーが Null の場合、自身がプライマリレイヤーとなる
        WindowNativeInstance *window_instance;
        auto nis_result = window.ObjThis->NativeInstanceSupport(
            TJS_NIS_GETINSTANCE,
            NativeClasses::WindowNativeClass::ClassID,
            reinterpret_cast<iTJSNativeInstance **>(&window_instance)
        );
        if (TJS_FAILED(nis_result)) return TJS_E_INVALIDPARAM;

        auto layer_tree = window_instance->get_layer_tree();
        if (layer_tree == nullptr) return TJS_E_INVALIDPARAM;
        layer_tree->add_primary_layer(this);
    } else {
        LayerNativeInstance *parent_layer_instance;
        auto nis_result = parent_layer.ObjThis->NativeInstanceSupport(
            TJS_NIS_GETINSTANCE,
            NativeClasses::LayerNativeClass::ClassID,
            reinterpret_cast<iTJSNativeInstance **>(&parent_layer_instance)
        );
        if (TJS_FAILED(nis_result)) return TJS_E_INVALIDPARAM;

        parent_layer_instance->add_children(this);
        _parent_layer = parent_layer;
    }

    _owner_window = window;
    return TJS_S_OK;
}

void LayerNativeInstance::Invalidate() {
    for (auto child : _children) {
        child->Invalidate();
    }
    _owner_window.Release();
    _parent_layer.Release();
    _owner_window = nullptr;
    _parent_layer = nullptr;
    tTJSNativeInstance::Invalidate();
}

void LayerNativeInstance::add_children(LayerNativeInstance *child) {
    if (std::find(_children.begin(), _children.end(), child) != _children.end()) return;
    _children.push_back(child);
}

void LayerNativeInstance::remove_children(LayerNativeInstance *child) {
    auto iter = std::find(_children.begin(), _children.end(), child);
    if (iter == _children.end()) return;
    _children.erase(iter);
}

void LayerNativeInstance::set_position(tjs_int x, tjs_int y) {
    _rect.x = x;
    _rect.y = y;
}

void LayerNativeInstance::set_size(tjs_int width, tjs_int height) {
    if (_rect.w == width && _rect.h == height) return;
    _rect.w = width;
    _rect.h = height;
    resize_pixels(width, height);
}

void LayerNativeInstance::set_visible(bool /*visible*/) {
    // TODO: visible フラグの実装
}

void LayerNativeInstance::resize_pixels(int w, int h) {
    _pixels.assign(static_cast<size_t>(w) * h, 0x00000000);
    _texture.reset();  // サイズが変わったのでGPUテクスチャも再生成が必要
    _dirty = true;
}

ITextureHandle* LayerNativeInstance::render(IGraphicsWindow* gfx) {
    if (_rect.w <= 0 || _rect.h <= 0) return nullptr;

    // GPUテクスチャが未生成、またはウィンドウが変わった場合は再生成
    if (_texture == nullptr || _last_gfx != gfx) {
        _texture = gfx->create_texture(_rect.w, _rect.h);
        _last_gfx = gfx;
        _dirty = true;
    }

    if (_dirty) {
        // 背景色で塗りつぶす
        // TODO: 背景色は外部から設定できるようにする
        LayerCompositor::fill_rect(
            _pixels.data(), _rect.w, _rect.h,
            0, 0, _rect.w, _rect.h,
            0xFF282828  // ARGB: 不透明の濃いグレー
        );

        // 子レイヤーを自身のCPUバッファへアルファ合成する
        for (auto* child : _children) {
            auto* child_texture = child->render(gfx);
            if (child_texture == nullptr) continue;

            auto child_rect = child->get_render_rect();
            LayerCompositor::composite_alpha(
                _pixels.data(), _rect.w, _rect.h,
                child->pixels(), child_rect.w, child_rect.h,
                child_rect.x, child_rect.y
            );
        }

        // CPUバッファをGPUテクスチャへアップロード
        gfx->update_texture(_texture.get(), _pixels.data());
        _dirty = false;
    }

    return _texture.get();
}
