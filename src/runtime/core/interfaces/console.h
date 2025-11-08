#pragma once
#include <iostream>
#include "tjs.h"
#include "encodings/CharacterSet.h"

namespace LibRuntime::Interfaces {
    class IConsole {
    public:
        virtual void write(const ttstr &text) = 0;
        virtual void error(const ttstr &text) = 0;
        virtual size_t readline(ttstr &result) = 0;
    };

    class ConsoleFallbackImpl : public IConsole {
    public:
        void write(const ttstr &text) {
            std::string out;
            TVPUtf16ToUtf8(out, text.AsStdString());
            std::cout << out;
        }

        void error(const ttstr &text) {
            std::string out;
            TVPUtf16ToUtf8(out, text.AsStdString());
            std::cerr << out;
        }

        size_t readline(ttstr &result) {
#ifndef _MSC_VER
            std::string input_text;
            std::getline(std::cin, input_text);

            result = ttstr(input_text.c_str());

            return result.length();
#else
            return 0;
#endif
        }
    };
}
