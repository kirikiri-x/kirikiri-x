#pragma once
#include <tjs.h>
#include <tjsNative.h>
#include <SDL.h>

namespace LibRuntime::TJSClasses {
    class LayerInstance : public tTJSNativeInstance {
    public:
        LayerInstance();
        tjs_error TJS_INTF_METHOD Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj);
        void TJS_INTF_METHOD Invalidate();

        void add_children(LayerInstance *child);
        void remove_children(LayerInstance *child);
        void set_position(tjs_int x, tjs_int y);
        void set_size(tjs_int width, tjs_int height);
        void set_visible(bool visible);

        SDL_Texture *render(SDL_Renderer *renderer);

        SDL_Rect get_render_rect() { return _renderRect; }

    private:
        tTJSVariantClosure _owner_window;
        tTJSVariantClosure _parent_layer;
        std::vector<LayerInstance *> _children;

        SDL_Rect _renderRect;
    };
}

