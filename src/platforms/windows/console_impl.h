#pragma once
#include "windows.h"
#include "interfaces/console.h"

class WindowsConsole: public LibRuntime::Interfaces::IConsole {
public:
    void write(const tjs_char *text) override;
    void error(const tjs_char *text) override;
    size_t readline(ttstr &result) override;
};
