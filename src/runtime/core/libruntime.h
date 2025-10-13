#pragma once

#include <map>
#include <vector>
#include "interfaces/filesystem.h"
#include "interfaces/console.h"
#include "interfaces/sysfunc.h"
#include "interfaces/system_ui.h"
#include "interfaces/environment.h"

namespace LibRuntime {
    typedef struct RuntimeConfig {
        bool verbose;
        bool enable_console_output;
    } RuntimeConfig;

    class KrkrRuntime {
    public:
        constexpr static int LIBRUNTIME_VERSION_MAJOR = 0;
        constexpr static int LIBRUNTIME_VERSION_MINOR = 0;
        constexpr static int LIBRUNTIME_VERSION_PATCH = 1;

        static int start_runtime(int argc, char *argv[]);
        static bool get_argument(const tjs_string &name, tjs_string &result);
        static void set_argument(const tjs_string &name, const tjs_string &value);
        static void get_runtime_version(tjs_string &verstr);
        static void get_runtime_version_full(tjs_string &verstr);
        static ttstr get_about_text();

        static void request_quit(int code);

        static Interfaces::IFileSystem *filesystem;
        static Interfaces::IConsole *console;
        static Interfaces::ISysFunc *sysfunc;
        static Interfaces::ISystemUI *system_ui;
        static Interfaces::IEnvironment *environment;

        static std::vector<ttstr> auto_paths;

    private:
        static bool interpreter();
        static void parse_args(int argc, char *argv[]);
        static std::map<tjs_string, tjs_string> arguments;
        static bool quit_required;
        static int quit_code;
    };
}
