#pragma once
#include "tjsVariant.h"
#include <vector>
#include <algorithm>

#include "tjs_classes/window/window_instance.h"

namespace LibRuntime {
    class EventManager {
    public:
        static bool init();

        static void add_continuous_handler(tTJSVariantClosure clo);
        static void remove_continuous_handler(tTJSVariantClosure clo);

        static void add_window_instance(TJSClasses::WindowInstance *instance);
        static void remove_window_instance(TJSClasses::WindowInstance *instance);

        static void dispatch_continuous_event();
        static void dispatch_window_update_event();
        static void dispatch_all_events();

        static bool is_event_enabled;

        static void set_exception_handler(tTJSVariantClosure clo);
        static const tTJSVariantClosure& get_exception_handler(); // 参照を返すことでコピーを防ぐ
        static bool call_exception_handler(tTJSVariant *exception);

    private:
        static std::vector<tTJSVariantClosure> continuous_handlers;
        static std::vector<TJSClasses::WindowInstance*> window_instances;
        static tTJSVariantClosure exception_handler;
    };
}
