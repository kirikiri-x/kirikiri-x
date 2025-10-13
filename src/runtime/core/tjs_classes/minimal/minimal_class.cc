#include <tjsCommHead.h>
#include <tjsTypes.h>
#include "minimal_class.h"
#include "../../libruntime.h"

using namespace LibRuntime::TJSClasses;

tjs_uint32 MinimalClass::ClassID = -1;

MinimalClass::MinimalClass() : tTJSNativeClass(TJS_W("mini")) {
    TJS_BEGIN_NATIVE_MEMBERS(mini)
    TJS_DECL_EMPTY_FINALIZE_METHOD
        // constructor
        TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(mini)
            return TJS_S_OK;
        TJS_END_NATIVE_CONSTRUCTOR_DECL(mini)

        // methods
        TJS_BEGIN_NATIVE_METHOD_DECL(print)
            if (numparams < 1) {
                LibRuntime::KrkrRuntime::console->write(TJS_W("[empty]\n"));
            } else {
                LibRuntime::KrkrRuntime::console->write(param[0]->GetString());
                LibRuntime::KrkrRuntime::console->write(TJS_W("\n"));
            }

            return TJS_S_OK;
        TJS_END_NATIVE_STATIC_METHOD_DECL(print)

    TJS_END_NATIVE_MEMBERS
}

tTJSNativeInstance *MinimalClass::CreateNativeInstance() {
    return nullptr;
}
