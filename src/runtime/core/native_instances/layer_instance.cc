#include <algorithm>
#include <tjs.h>
#include <tjsNative.h>
#include "layer_instance.h"
#include "window_instance.h"
#include "../libruntime.h"
#include "../native_classes/window.h"
#include "../native_classes/layer.h"
#include "../rendering/layer_tree.h"

using namespace LibRuntime::NativeInstances;

LayerNativeInstance::LayerNativeInstance(): _renderRect()
{
}

tjs_error LayerNativeInstance::Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) {
    if (numparams < 2) return TJS_E_BADPARAMCOUNT;

    // ウィンドウのオブジェクトを取得
    auto window = param[0]->AsObjectClosure();
    if (window.Object == nullptr) return TJS_E_INVALIDPARAM;

    // 親レイヤーのオブジェクトを取得
    auto parent_layer = param[1]->AsObjectClosure();
    if (parent_layer.Object == nullptr) {
        parent_layer.Release();

        // 親レイヤーがNullの場合は，自身がプライマリレイヤーとなる
        WindowNativeInstance *window_instance;
        auto nis_result = window.ObjThis->NativeInstanceSupport(TJS_NIS_GETINSTANCE, NativeClasses::WindowNativeClass::ClassID, reinterpret_cast<iTJSNativeInstance **>(&window_instance));
        if (TJS_FAILED(nis_result)) return TJS_E_INVALIDPARAM;

        auto layer_tree = window_instance->get_layer_tree();
        if (layer_tree == nullptr) return TJS_E_INVALIDPARAM;
        layer_tree->add_primary_layer(this);
    } else {
        // 親レイヤーがある場合は，親レイヤーの子に自身を登録
        LayerNativeInstance *parent_layer_instance;
        auto nis_result = parent_layer.ObjThis->NativeInstanceSupport(TJS_NIS_GETINSTANCE, NativeClasses::LayerNativeClass::ClassID, reinterpret_cast<iTJSNativeInstance **>(&parent_layer_instance));
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
    _renderRect.x = x;
    _renderRect.y = y;
}

void LayerNativeInstance::set_size(tjs_int width, tjs_int height) {
    _renderRect.w = width;
    _renderRect.h = height;
}

SDL_Texture *LayerNativeInstance::render(SDL_Renderer *renderer) {
    auto base_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _renderRect.w, _renderRect.h);
    SDL_SetTextureBlendMode(base_texture, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(renderer, base_texture);

    // ソフトウェアレンダリングで背景などを塗りつぶす
    auto surface = SDL_CreateRGBSurface(0, _renderRect.w, _renderRect.h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 40, 40, 40));    //TODO: 色は外部から指定できるようにする

    // ソフトウェアレンダリングしたものをテクスチャに変換し、レンダラーに描画
    auto texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture2, nullptr, nullptr);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface);

    // 子レイヤーを描画
    for (auto child : _children) {
        auto child_texture = child->render(renderer);
        if (child_texture == nullptr) continue;

        // 子レイヤーから返されたテクスチャをベーステクスチャに上書き描画
        SDL_SetRenderTarget(renderer, base_texture);
        SDL_RenderCopy(renderer, child_texture, nullptr, &child->_renderRect);
        SDL_DestroyTexture(child_texture);
    }

    return base_texture;
}
