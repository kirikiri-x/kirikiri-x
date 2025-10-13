#include "event_manager.h"

using namespace LibRuntime;

std::vector<tTJSVariantClosure> EventManager::continuous_handlers;
std::vector<TJSClasses::WindowInstance*> EventManager::window_instances;
bool EventManager::is_event_enabled = true;
tTJSVariantClosure EventManager::exception_handler;

bool EventManager::init() {
    return true;
}

void EventManager::add_continuous_handler(tTJSVariantClosure clo) {
    auto iter = std::find(continuous_handlers.begin(), continuous_handlers.end(), clo);
    if (iter != continuous_handlers.end()) return;  //ハンドラがすでにある場合は追加しない

    continuous_handlers.push_back(clo);
    clo.AddRef();
}

void EventManager::remove_continuous_handler(tTJSVariantClosure clo) {
    auto iter = std::find(continuous_handlers.begin(), continuous_handlers.end(), clo);
    if (iter == continuous_handlers.end()) return;  //ハンドラが存在しない場合は何もしない

    continuous_handlers.erase(iter);
    clo.Release();
}

void EventManager::add_window_instance(TJSClasses::WindowInstance *instance) {
    window_instances.push_back(instance);
}

void EventManager::remove_window_instance(TJSClasses::WindowInstance *instance) {
    auto iter = std::find(window_instances.begin(), window_instances.end(), instance);
    if (iter == window_instances.end()) return;  //インスタンスが存在しない場合は何もしない

    window_instances.erase(iter);
}

void EventManager::dispatch_continuous_event() {
    for (auto clo: continuous_handlers) {
        try {
            clo.FuncCall(0, nullptr, nullptr, nullptr, 0, nullptr, nullptr);
        } catch (...) {

        }
    }
}

void EventManager::dispatch_window_update_event() {
    for (auto window: window_instances) {
        window->update();
    }
}

void EventManager::dispatch_all_events() {
    dispatch_window_update_event();
    dispatch_continuous_event();
}

void EventManager::set_exception_handler(tTJSVariantClosure clo) {
    exception_handler = clo;
}

const tTJSVariantClosure& EventManager::get_exception_handler() {
    return exception_handler;
}

bool EventManager::call_exception_handler(tTJSVariant *exception) {
    try {
        tTJSVariant result;
        exception_handler.FuncCall(0, nullptr, nullptr, &result, 1, &exception, nullptr);
        return result.AsInteger() == 1;
    } catch (...) {
        return false;
    }
}
