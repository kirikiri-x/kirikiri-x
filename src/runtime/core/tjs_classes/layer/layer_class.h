#pragma once
#include <tjs.h>
#include <tjsNative.h>

namespace LibRuntime::TJSClasses {
    /**
     * Layerクラス - TJS2から使用可能なレイヤークラス
     */
    class LayerClass : public tTJSNativeClass {
    public:
        LayerClass();

        static tjs_uint32 ClassID;
        tTJSNativeInstance *CreateNativeInstance() override;
    };
}

