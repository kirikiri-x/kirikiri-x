#include "window_instance.h"
#include "../../window_manager.h"
#include "../../rendering/layer_tree.h"
#include <algorithm>
#include "../../event_manager.h"

using namespace LibRuntime::TJSClasses;

WindowInstance::WindowInstance() {

}

tjs_error TJS_INTF_METHOD WindowInstance::Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) {
    this->window = SDL_CreateWindow(TJS_N("Window"), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->layer_tree = std::make_shared<Rendering::LayerTree>();
    WindowManager::register_window(this);
    EventManager::add_window_instance(this);
    return TJS_S_OK;
}

void TJS_INTF_METHOD WindowInstance::Invalidate() {
    for (auto &obj : objects) {
        obj.Release();
    }
    objects.clear();

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    WindowManager::unregister_window(this);
    EventManager::remove_window_instance(this);
}

void WindowInstance::add_object(tTJSVariantClosure clo) {
    if (objects.end() != std::find(objects.begin(), objects.end(), clo)) return;

    objects.push_back(clo);
    clo.AddRef();
}

void WindowInstance::remove_object(tTJSVariantClosure clo) {
    auto it = std::find(objects.begin(), objects.end(), clo);
    if (it == objects.end()) return;

    objects.erase(it);
    clo.Release();
}

void WindowInstance::update() {
    SDL_RenderClear(this->renderer);
    layer_tree->render(this->renderer);
    SDL_RenderPresent(this->renderer);
}

void WindowInstance::bring_to_front() {
    SDL_RaiseWindow(this->window);
}

std::shared_ptr<LibRuntime::Rendering::LayerTree> WindowInstance::get_layer_tree() {
    return layer_tree;
}

