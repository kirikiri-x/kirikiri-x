#pragma once
#include "tjs_classes/window/window_instance.h"

namespace LibRuntime {
    class WindowManager {
    public:
        static void register_window(TJSClasses::WindowInstance *window);
        static void unregister_window(TJSClasses::WindowInstance *window);
        static bool has_windows();

    private:
        static std::vector<TJSClasses::WindowInstance*> windows;
        static TJSClasses::WindowInstance *main_window;
    };
}
