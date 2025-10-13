#include "window_manager.h"
#include <algorithm>

using namespace LibRuntime;
using namespace LibRuntime::TJSClasses;

std::vector<WindowInstance*> WindowManager::windows;
TJSClasses::WindowInstance *WindowManager::main_window;

void WindowManager::register_window(WindowInstance *window) {
    if (main_window == nullptr && windows.size() == 0) {
        main_window = window;
    }
    windows.push_back(window);
}

void WindowManager::unregister_window(WindowInstance *window) {
    auto it = std::find(windows.begin(), windows.end(), window);
    if (it == windows.end()) return;

    windows.erase(it);
    if (main_window == window) {
        main_window = nullptr;
    }
}

bool WindowManager::has_windows() {
    return windows.size() > 0;
}