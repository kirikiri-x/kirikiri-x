#include <SDL.h>
#include <SDL_main.h>
#include "filesystem_impl.h"
#include "console_impl.h"
#include "libruntime.h"
#include <windows.h>
#include <fcntl.h>
#include "environment_impl.h"
#include "sysfunc_impl.h"
#include "system_ui_impl.h"

void alloc_console() {
#if DEBUG

#endif
    AllocConsole();
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
}

int main(int argv, char* args[]) {
    alloc_console();
    setlocale(LC_ALL,"");
    UINT sav = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);


    LibRuntime::KrkrRuntime::filesystem = new WindowsFileSystem();
    LibRuntime::KrkrRuntime::console = new WindowsConsole();
    LibRuntime::KrkrRuntime::system_ui = new WindowsSystemUI();
    LibRuntime::KrkrRuntime::sysfunc = new WindowsSysFunc();
    LibRuntime::KrkrRuntime::environment = new WindowsEnvironment();
    LibRuntime::KrkrRuntime::start_runtime(argv, args);

    SetConsoleOutputCP(sav);

#if DEBUG
    FreeConsole();
#endif
    return 0;
}