#include "window_instance.h"
#include "../window_manager.h"
#include "../rendering/layer_tree.h"
#include "../libruntime.h"
#include <algorithm>
#include "../event_manager.h"

using namespace LibRuntime::NativeInstances;

WindowNativeInstance::WindowNativeInstance() {}

tjs_error TJS_INTF_METHOD WindowNativeInstance::Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) {
    _graphics_window = KrkrRuntime::graphics->create_window("Window", 300, 300);
    this->layer_tree = std::make_shared<Rendering::LayerTree>();
    WindowManager::register_window(this);
    EventManager::add_window_instance(this);
    return TJS_S_OK;
}

void TJS_INTF_METHOD WindowNativeInstance::Invalidate() {
    for (auto &obj : objects) {
        obj.Release();
    }
    objects.clear();

    _graphics_window.reset();

    WindowManager::unregister_window(this);
    EventManager::remove_window_instance(this);
}

void WindowNativeInstance::add_object(tTJSVariantClosure clo) {
    if (objects.end() != std::find(objects.begin(), objects.end(), clo)) return;
    objects.push_back(clo);
    clo.AddRef();
}

void WindowNativeInstance::remove_object(tTJSVariantClosure clo) {
    auto it = std::find(objects.begin(), objects.end(), clo);
    if (it == objects.end()) return;
    objects.erase(it);
    clo.Release();
}

void WindowNativeInstance::update() {
    layer_tree->render(_graphics_window.get());
}

void WindowNativeInstance::bring_to_front() {
    _graphics_window->raise();
}

std::shared_ptr<LibRuntime::Rendering::LayerTree> WindowNativeInstance::get_layer_tree() {
    return layer_tree;
}
