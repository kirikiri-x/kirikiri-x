//TODO: include関連を整理する
#include <tjsCommHead.h>
#include <tjsTypes.h>
#include "libruntime.h"
#include "messages.h"
#include "event_manager.h"
#include <tjsError.h>
#include "script_manager.h"
#include "window_manager.h"

using namespace LibRuntime;

// --- Init global variables ---
Interfaces::IFileSystem* KrkrRuntime::filesystem = new Interfaces::FileSystemFallbackImpl();
Interfaces::IConsole* KrkrRuntime::console = new Interfaces::ConsoleFallbackImpl();
Interfaces::ISysFunc* KrkrRuntime::sysfunc = new Interfaces::SysFuncFallbackImpl();
Interfaces::ISystemUI* KrkrRuntime::system_ui = new Interfaces::SystemUIFallbackImpl();
Interfaces::IEnvironment* KrkrRuntime::environment = new Interfaces::EnvironmentFallbackImpl();
std::map<ttstr, ttstr> KrkrRuntime::arguments;
bool KrkrRuntime::quit_required = false;
int KrkrRuntime::quit_code = 0;

int KrkrRuntime::start_runtime(int argc, char *argv[]) {
    console->write(TJS_W("--- Kirikiri X Runtime ---\n"));
    console->write(TJS_W("Initializing runtime\n"));

    SDL_Init(SDL_INIT_VIDEO);

    parse_args(argc, argv);
    Messages::init_tjs_messages();
    Messages::init_libruntime_messages();
    ScriptManager::init(TJS_W("startup.tjs"), TJS_W("UTF-8"), 1);

    interpreter();

    if (WindowManager::has_windows()) {
        SDL_Event event;
        while (true) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
                EventManager::dispatch_all_events();
            }
        }
    }

    SDL_Quit();
    return 0;
}

void KrkrRuntime::parse_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (*argv[i] != '-') continue;

        char* name = strtok(argv[i], "=");
        char* value = strtok(nullptr, "=");

        if (value == nullptr) {
            arguments.emplace(ttstr(name), ttstr(TJS_W("yes")));
        } else {
            arguments.emplace(ttstr(name), ttstr(value));
        }
    }
}

bool KrkrRuntime::get_argument(const ttstr &name, ttstr &result) {
    if (auto iter = arguments.find(name); iter != std::end(arguments)) {
        result = iter->second;
        return true;
    }
    return false;
}

void KrkrRuntime::set_argument(const ttstr& name, const ttstr &value) {
    arguments[name] = value;
}

void KrkrRuntime::get_runtime_version(ttstr &verstr) {
    ttstr version_major(LIBRUNTIME_VERSION_MAJOR);
    ttstr version_minor(LIBRUNTIME_VERSION_MINOR);
    ttstr version_patch(LIBRUNTIME_VERSION_PATCH);

    ttstr verstr2 = version_major + TJS_W(".") + version_minor + TJS_W(".") + version_patch;
    verstr = verstr2.AsStdString();
}

void KrkrRuntime::get_runtime_version_full(ttstr &verstr) {
    ttstr runtime_version;
    get_runtime_version(runtime_version);
    verstr = TJS_W("Kirikiri X Runtime ") + runtime_version;
}

ttstr KrkrRuntime::get_about_text()
{
    ttstr verstr;
    ttstr osname;
    get_runtime_version(verstr);
    environment->get_os_name(osname);
    ttstr about_text;
    about_text += TJS_W("吉里吉里X ランタイム version ") + verstr + TJS_W(" (TJS Version ") + ScriptManager::get_script_engine_version().c_str() + TJS_W(")\n");
    about_text += TJS_W("OS: ") + osname + TJS_W("\n");
    about_text += TJS_W("Copyright (C) 2025 Kirikiri X\n\n");
    about_text += TJS_W("吉里吉里Xランタイムは，Apache License 2.0 に従って使用/改変/再頒布などを行えます．\n");
    about_text += TJS_W("https://www.apache.org/licenses/LICENSE-2.0.txt\n");
    about_text += TJS_W("----------------------------------------------------------------------------\n");
    return about_text;
}

bool KrkrRuntime::interpreter() {
    console->write(ttstr(Messages::LRInterpreterMode));
    while (!quit_required) {
        EventManager::dispatch_continuous_event();
        ttstr readresult;
        console->write(TJS_W(">> "));
        console->readline(readresult);

        if (readresult == TJS_W("exit();")) break;

        try {
            ScriptManager::run(readresult);

        } catch (eTJSError &err) {
            console->error(TJS_W("[ERR] "));
            console->error(err.GetMessage().c_str());
            console->error(TJS_W("\n"));
        }
    }

    return true;
}

void KrkrRuntime::request_quit(int code = 0) {
    quit_required = true;
    quit_code = code;
}