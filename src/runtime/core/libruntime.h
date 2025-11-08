#pragma once

#include <map>
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
        static bool get_argument(const ttstr &name, ttstr &result);
        static void set_argument(const ttstr &name, const ttstr &value);
        static void get_runtime_version(ttstr &verstr);
        static void get_runtime_version_full(ttstr &verstr);
        static ttstr get_about_text();

        static void request_quit(int code);

        static Interfaces::IFileSystem *filesystem;
        static Interfaces::IConsole *console;
        static Interfaces::ISysFunc *sysfunc;
        static Interfaces::ISystemUI *system_ui;
        static Interfaces::IEnvironment *environment;

    private:
        static bool interpreter();
        static void parse_args(int argc, char *argv[]);
        static std::map<ttstr, ttstr> arguments;
        static bool quit_required;
        static int quit_code;
    };
}
