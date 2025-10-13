#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include <tjs.h>
#include <tjsError.h>
#include <tjsNative.h>

namespace LibRuntime {
    namespace Rendering {
        class LayerTree;
    }

    namespace TJSClasses {
        class WindowInstance : public tTJSNativeInstance {
        public:
            WindowInstance();
            tjs_error TJS_INTF_METHOD Construct(tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *tjs_obj) override;
            void TJS_INTF_METHOD Invalidate() override;

            void add_object(tTJSVariantClosure clo);
            void remove_object(tTJSVariantClosure clo);
            void update();
            void bring_to_front();

            std::shared_ptr<Rendering::LayerTree> get_layer_tree();
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;

            std::vector<tTJSVariantClosure> objects;
            std::shared_ptr<Rendering::LayerTree> layer_tree;
        };
    }

}

