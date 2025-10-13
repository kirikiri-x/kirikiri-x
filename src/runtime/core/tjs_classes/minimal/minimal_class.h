#pragma once
#include "tjsNative.h"

namespace LibRuntime::TJSClasses {
    /**
     * Minimalクラス - 動作確認に必要な最小限の機能を実装したクラス
     */
    class MinimalClass : public tTJSNativeClass {
    public:
        MinimalClass();

        static tjs_uint32 ClassID;
        tTJSNativeInstance *CreateNativeInstance() override;
    };
}

