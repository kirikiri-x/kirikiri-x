#pragma once
#include <tjs.h>
#include <tjsNative.h>

namespace LibRuntime::TJSClasses {
    /**
     * Systemクラス - TJS2から使用可能なシステムクラス
     */
    class SystemClass : public tTJSNativeClass {
    public:
        SystemClass();

        static tjs_uint32 ClassID;
        tTJSNativeInstance *CreateNativeInstance() override;
    };
}

