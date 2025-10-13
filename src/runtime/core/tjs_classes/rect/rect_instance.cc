#include "rect_instance.h"
#include "rect_class.h"

using namespace LibRuntime::TJSClasses;

RectInstance::RectInstance()
{
    rect_ = {};
}

tjs_error RectInstance::Construct(tjs_int numparams, tTJSVariant** param, iTJSDispatch2* tjs_obj)
{
    RectInstance* old_instance = nullptr;

    switch (numparams)
    {
    case 0:
        // 引数が空なので，初期化だけする．
        clear();
        return TJS_S_OK;

    case 1:
        // 引数が1つのときは，その引数を RectInstance のオブジェクトと見なす．
        // そのオブジェクトの rect_ 変数を，このオブジェクトの変数にコピーする
        old_instance = dynamic_cast<RectInstance*>(TJSGetNativeInstance(RectClass::ClassID, param[0]));
        if (old_instance == nullptr)
        {
            return TJS_E_INVALIDPARAM;
        }

        set(old_instance->rect_.left, old_instance->rect_.top, old_instance->rect_.right, old_instance->rect_.bottom);
        return TJS_S_OK;

    case 4:
        // 引数が4つのときは，数値型かつ left, top, right, bottom の順番で指定されているはず．
        set(*param[0], *param[1], *param[2], *param[3]);
        return TJS_S_OK;

    default:
        return TJS_E_INVALIDPARAM;
    }

    // ここに来るのはおかしいぞ
    return TJS_E_FAIL;
}

void RectInstance::Invalidate()
{
    // 開放するものはないはず．
}

void RectInstance::add_offset(tjs_int x, tjs_int y)
{
    rect_.left += x;
    rect_.right += x;
    rect_.top += y;
    rect_.bottom += y;
}

void RectInstance::clear()
{
    set(0, 0, 0, 0);
}

bool RectInstance::clip(RectInstance& rect)
{
    tjs_int left = std::max(rect_.left, rect.rect_.left);
    tjs_int top = std::max(rect_.top, rect.rect_.top);
    tjs_int right = std::min(rect_.right, rect.rect_.right);
    tjs_int bottom = std::min(rect_.bottom, rect.rect_.bottom);

    if (left < right && top < bottom)
    {
        set(left, top, right, bottom);
        return true;
    }
    else
    {
        return false;
    }
}

bool RectInstance::equal(const RectInstance& target) const
{
    return rect_.left == target.rect_.left && rect_.top == target.rect_.top && rect_.right == target.rect_.right && rect_.bottom == target.rect_.bottom;
}

bool RectInstance::included(RectInstance& target)
{
    return target.rect_.left >= rect_.left && target.rect_.top >= rect_.top && target.rect_.right <= rect_.right && target.rect_.bottom <= rect_.bottom;
}

bool RectInstance::included_position(tjs_int x, tjs_int y)
{
    return (x >= rect_.left && x < rect_.right) && (y >= rect_.top && y < rect_.bottom);
}

bool RectInstance::intersects(RectInstance& target)
{
    return target.rect_.left < rect_.right && target.rect_.right > rect_.left && target.rect_.top < rect_.bottom && target.rect_.bottom > rect_.top;
}

bool RectInstance::is_empty()
{
    return rect_.left >= rect_.right || rect_.top >= rect_.bottom;
}

void RectInstance::set(tjs_int left, tjs_int top, tjs_int right, tjs_int bottom)
{
    rect_.left = left;
    rect_.top = top;
    rect_.right = right;
    rect_.bottom = bottom;
}

void RectInstance::set_offset(tjs_int x, tjs_int y)
{
    int width, height;
    get_size(width, height);

    rect_.right = width + x;
    rect_.bottom = height + y;
    rect_.left = x;
    rect_.top = y;
}

void RectInstance::set_size(tjs_int width, tjs_int height)
{
    rect_.right = width + rect_.left;
    rect_.bottom = height + rect_.top;
}

bool RectInstance::union_rect(RectInstance& target)
{
    if (target.is_empty()) return false;

    rect_.left = std::min(rect_.left, target.rect_.left);
    rect_.top = std::min(rect_.top, target.rect_.top);
    rect_.right = std::max(rect_.right, target.rect_.right);
    rect_.bottom = std::max(rect_.bottom, target.rect_.bottom);

    return true;
}

void RectInstance::get_size(int& width, int& height) const
{
    width = rect_.right - rect_.left;
    height = rect_.bottom - rect_.top;
}

