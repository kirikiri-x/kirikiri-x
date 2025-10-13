#pragma once
#include <tjs.h>
#include <tjsNative.h>

namespace LibRuntime::TJSClasses {
    /**
     * Rectクラス - TJS2から使用可能な矩形情報クラス
     */
    class RectClass : public tTJSNativeClass {
    public:
        RectClass();

        static tjs_uint32 ClassID;
        tTJSNativeInstance *CreateNativeInstance() override;
    };
}

