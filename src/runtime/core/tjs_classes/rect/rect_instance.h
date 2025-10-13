#pragma once
#include <tjs.h>
#include <tjsNative.h>

#include "rect_class.h"
#include "../../types/rect.h"

namespace LibRuntime {
    namespace Rendering {
        class LayerTree;
    }

    namespace TJSClasses {
        class RectInstance : public tTJSNativeInstance {
            friend class RectClass;

        public:
            RectInstance();
            tjs_error TJS_INTF_METHOD Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) override;
            void TJS_INTF_METHOD Invalidate() override;

            void add_offset(tjs_int x, tjs_int y);
            void clear();
            bool clip(RectInstance &rect);
            bool equal(const RectInstance &rect) const;
            bool included(RectInstance &rect);
            bool included_position(tjs_int x, tjs_int y);
            bool intersects(RectInstance &rect);
            bool is_empty();
            void set(tjs_int left, tjs_int top, tjs_int right, tjs_int bottom);
            void set_offset(tjs_int x, tjs_int y);
            void set_size(tjs_int width, tjs_int height);
            bool union_rect(RectInstance &rect);

            void get_size(int &width, int &height) const;
        protected:
            Types::Rect rect_;

            void calc_size();
        };
    }

}

