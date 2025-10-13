#include "rect_class.h"
#include "../../script_manager.h"
#include "../../event_manager.h"
#include "../../libruntime.h"
#include "rect_instance.h"

using namespace LibRuntime::TJSClasses;

tjs_uint32 RectClass::ClassID = -1;

RectClass::RectClass() : tTJSNativeClass(TJS_W("Rect")) {
    TJS_BEGIN_NATIVE_MEMBERS(Rect)
    {
        TJS_DECL_EMPTY_FINALIZE_METHOD

        //===== CONSTRUCTOR =====
        TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL(_this, RectInstance, Rect)
        {
            return TJS_S_OK;
        }
        TJS_END_NATIVE_CONSTRUCTOR_DECL(Rect)


        //===== METHODS =====
        TJS_BEGIN_NATIVE_METHOD_DECL(addOffset)
        {
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            if (param[0]->Type() != tvtInteger || param[1]->Type() != tvtInteger) return TJS_E_INVALIDPARAM;
            _this->add_offset(*param[0], *param[1]);
        }
        TJS_END_NATIVE_METHOD_DECL(addOffset)


        TJS_BEGIN_NATIVE_METHOD_DECL(clear)
        {
            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            _this->clear();
        }
        TJS_END_NATIVE_METHOD_DECL(clear)


        TJS_BEGIN_NATIVE_METHOD_DECL(clip)
        {
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            RectInstance *rect;
            auto param0Obj = param[0]->AsObjectNoAddRef();
            if (!param0Obj) return TJS_E_NATIVECLASSCRASH;
            tjs_error hr = param0Obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE, RectClass::ClassID, (iTJSNativeInstance **)&rect);
            if (TJS_FAILED(hr)) return TJS_E_NATIVECLASSCRASH;

            auto retval = _this->clip(*rect);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(clip)


        TJS_BEGIN_NATIVE_METHOD_DECL(equal)
        {
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            RectInstance *rect;
            auto param0Obj = param[0]->AsObjectNoAddRef();
            if (!param0Obj) return TJS_E_NATIVECLASSCRASH;
            tjs_error hr = param0Obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE, RectClass::ClassID, (iTJSNativeInstance **)&rect);
            if (TJS_FAILED(hr)) return TJS_E_NATIVECLASSCRASH;

            auto retval = _this->equal(*rect);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(equal)


        TJS_BEGIN_NATIVE_METHOD_DECL(included)
        {
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            RectInstance *rect;
            auto param0Obj = param[0]->AsObjectNoAddRef();
            if (!param0Obj) return TJS_E_NATIVECLASSCRASH;
            tjs_error hr = param0Obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE, RectClass::ClassID, (iTJSNativeInstance **)&rect);
            if (TJS_FAILED(hr)) return TJS_E_NATIVECLASSCRASH;

            auto retval = _this->included(*rect);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(included)


        TJS_BEGIN_NATIVE_METHOD_DECL(includedPos)
        {
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            if (param[0]->Type() != tvtInteger || param[1]->Type() != tvtInteger) return TJS_E_INVALIDPARAM;

            auto retval = _this->included_position(*param[0], *param[1]);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(includedPos)


        TJS_BEGIN_NATIVE_METHOD_DECL(intersects)
        {
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            RectInstance *rect;
            auto param0Obj = param[0]->AsObjectNoAddRef();
            if (!param0Obj) return TJS_E_NATIVECLASSCRASH;
            tjs_error hr = param0Obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE, RectClass::ClassID, (iTJSNativeInstance **)&rect);
            if (TJS_FAILED(hr)) return TJS_E_NATIVECLASSCRASH;

            auto retval = _this->intersects(*rect);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(intersects)


        TJS_BEGIN_NATIVE_METHOD_DECL(isEmpty)
        {
            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            auto retval = _this->is_empty();

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(isEmpty)


        TJS_BEGIN_NATIVE_METHOD_DECL(set)
        {
            if (numparams < 4) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            if (param[0]->Type() != tvtInteger || param[1]->Type() != tvtInteger || param[2]->Type() != tvtInteger || param[3]->Type() != tvtInteger) return TJS_E_INVALIDPARAM;

            _this->set(*param[0], *param[1], *param[2], *param[3]);

            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(set)


        TJS_BEGIN_NATIVE_METHOD_DECL(setOffset)
        {
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            if (param[0]->Type() != tvtInteger || param[1]->Type() != tvtInteger) return TJS_E_INVALIDPARAM;

            _this->set_offset(*param[0], *param[1]);

            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(setOffset)


        TJS_BEGIN_NATIVE_METHOD_DECL(setSize)
        {
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
            if (param[0]->Type() != tvtInteger || param[1]->Type() != tvtInteger) return TJS_E_INVALIDPARAM;

            _this->set_size(*param[0], *param[1]);

            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(setSize)


        TJS_BEGIN_NATIVE_METHOD_DECL(union)
        {
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;

            TJS_GET_NATIVE_INSTANCE(_this, RectInstance);

            RectInstance *rect;
            auto param0Obj = param[0]->AsObjectNoAddRef();
            if (!param0Obj) return TJS_E_NATIVECLASSCRASH;
            tjs_error hr = param0Obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE, RectClass::ClassID, (iTJSNativeInstance **)&rect);
            if (TJS_FAILED(hr)) return TJS_E_NATIVECLASSCRASH;

            auto retval = _this->union_rect(*rect);

            if (result != nullptr) *result = retval;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_METHOD_DECL(union)


        //===== PROPERTIES =====
        TJS_BEGIN_NATIVE_PROP_DECL(left)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.left;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->rect_.left = *param;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(left)


        TJS_BEGIN_NATIVE_PROP_DECL(right)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.right;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->rect_.right = *param;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(right)


        TJS_BEGIN_NATIVE_PROP_DECL(top)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.top;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->rect_.top = *param;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(top)


        TJS_BEGIN_NATIVE_PROP_DECL(bottom)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.bottom;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->rect_.bottom = *param;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(bottom)


        TJS_BEGIN_NATIVE_PROP_DECL(width)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.right - _this->rect_.left;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->set_size(*param, _this->rect_.bottom - _this->rect_.top);
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(width)


        TJS_BEGIN_NATIVE_PROP_DECL(height)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = _this->rect_.bottom - _this->rect_.top;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                _this->set_size(_this->rect_.right - _this->rect_.left, *param);
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(height)


        TJS_BEGIN_NATIVE_PROP_DECL(nativeArray)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                TJS_GET_NATIVE_INSTANCE(_this, RectInstance);
                *result = tTJSVariant(reinterpret_cast<tTVInteger>(&_this->rect_));
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(nativeArray)

    }
    TJS_END_NATIVE_MEMBERS
}

tTJSNativeInstance *RectClass::CreateNativeInstance() {
    return new RectInstance();
}

