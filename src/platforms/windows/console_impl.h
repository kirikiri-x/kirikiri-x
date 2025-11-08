#pragma once
#include "windows.h"
#include "interfaces/console.h"
#include "tjs.h"

class WindowsConsole: public LibRuntime::Interfaces::IConsole {
public:
    void write(const ttstr &text) override;
    void error(const ttstr &text) override;
    size_t readline(ttstr &result) override;
};
