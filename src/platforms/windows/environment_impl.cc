#include "environment_impl.h"

#include <windows.h>
#include <ShlObj.h>

typedef void (WINAPI *RtlGetVersionFunc)(OSVERSIONINFOEX* );

bool WindowsEnvironment::get_execution_path(ttstr &out) {
    wchar_t path[MAX_PATH];
    if (GetModuleFileNameW(nullptr, path, MAX_PATH) == 0) {
        return false; // Failed to get the execution path
    }
    out = ttstr(path);
    return true;
}

bool WindowsEnvironment::get_personal_path(ttstr &out) {
    wchar_t path[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, 0, path) != S_OK) {
        return false; // Failed to get the personal path
    }
    out = ttstr(path);
    return true;
}

bool WindowsEnvironment::get_saved_games_path(ttstr &out) {
    PWSTR path = nullptr;

    if (SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr, &path) != S_OK) {
        return false; // Failed to get the saved games path
    }
    out = ttstr(path);
    return true;
}

bool WindowsEnvironment::get_platform_name(ttstr &out) {
    if constexpr (sizeof(void*) == 8) {
        out = TJS_W("Win64");
    } else {
        out = TJS_W("Win32");
    }
    return true;
}

bool WindowsEnvironment::get_os_name(ttstr &os_name) {
    RTL_OSVERSIONINFOEXW osvi;
    ZeroMemory(&osvi, sizeof(RTL_OSVERSIONINFOEXW));
    osvi.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);
    ttstr osname;

    const auto dll = LoadLibraryW(L"ntdll.dll");
    if (dll == nullptr) {
        os_name = TJS_W("Microsoft Windows");
    }


    auto func = reinterpret_cast<RtlGetVersionFunc>(GetProcAddress(dll, "RtlGetVersion"));
    if (!func) {
        FreeLibrary(dll);
        os_name = TJS_W("Microsoft Windows");
    }

    func(&osvi);
    FreeLibrary(dll);
    osname = TJS_W("Microsoft Windows ");
    switch (osvi.dwPlatformId)
    {
    case VER_PLATFORM_WIN32s:
        osname += TJS_W("32s");
        break;

    case VER_PLATFORM_WIN32_WINDOWS:
        osname += TJS_W("9x");
        break;

    case VER_PLATFORM_WIN32_NT:
        osname += TJS_W("NT");
        break;
    default:
        osname += TJS_W("Unknown");
    }
    osname += TJS_W(" ");
    osname += std::to_string(osvi.dwMajorVersion).c_str();
    osname += TJS_W(".");
    osname += std::to_string(osvi.dwMinorVersion).c_str();
    osname += TJS_W(".");
    osname += std::to_string(osvi.dwBuildNumber).c_str();
    osname += TJS_W(" (");
    if (osvi.wProductType == VER_NT_WORKSTATION) {
        osname += TJS_W("Workstation");
    } else {
        osname += TJS_W("Server");
    }
    osname += TJS_W(")");
    os_name = osname.AsStdString();
    return true;
}
