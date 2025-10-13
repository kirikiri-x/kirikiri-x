#pragma once
#include "tjs.h"
#include "tjsNative.h"

namespace LibRuntime::TJSClasses {
    /**
     * Windowクラス - TJS2から使用可能なウィンドウクラス
     */
    class WindowClass : public tTJSNativeClass {
    public:
        WindowClass();

        static tjs_uint32 ClassID;
        tTJSNativeInstance *CreateNativeInstance() override;
    };
}

