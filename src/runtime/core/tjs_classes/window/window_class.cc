#include "window_class.h"
#include "window_instance.h"

using namespace LibRuntime::TJSClasses;

tjs_uint32 WindowClass::ClassID = -1;

WindowClass::WindowClass() : tTJSNativeClass(TJS_W("Window")) {
    TJS_BEGIN_NATIVE_MEMBERS(Window)
    {
        TJS_DECL_EMPTY_FINALIZE_METHOD

        TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL(/*this name*/_this, /*type*/WindowInstance, /*TJS class name*/Window)
        {
            return TJS_S_OK;
        }
        TJS_END_NATIVE_CONSTRUCTOR_DECL(Window)


        TJS_BEGIN_NATIVE_METHOD_DECL(add) {
            TJS_GET_NATIVE_INSTANCE(_this, WindowInstance)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            auto clo = param[0]->AsObjectClosureNoAddRef();
            _this->add_object(clo);
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(add)

        TJS_BEGIN_NATIVE_METHOD_DECL(remove) {
            TJS_GET_NATIVE_INSTANCE(_this, WindowInstance)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            auto clo = param[0]->AsObjectClosureNoAddRef();
            _this->remove_object(clo);
        }
        TJS_END_NATIVE_METHOD_DECL(remove)

        TJS_BEGIN_NATIVE_METHOD_DECL(bringToFront)
        {
            TJS_GET_NATIVE_INSTANCE(_this, WindowInstance)
            _this->bring_to_front();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(bringToFront)
    }
    TJS_END_NATIVE_MEMBERS
}

tTJSNativeInstance *WindowClass::CreateNativeInstance() {
    return new WindowInstance();
}

