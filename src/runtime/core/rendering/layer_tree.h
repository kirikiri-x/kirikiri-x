#pragma once
#include <vector>
#include <SDL.h>

namespace LibRuntime {
    namespace TJSClasses {
        class LayerInstance;
    }

    namespace Rendering {
        class LayerTree {
        public:
            void add_primary_layer(TJSClasses::LayerInstance *layer);
            void remove_primary_layer(TJSClasses::LayerInstance *layer);
            void render(SDL_Renderer *renderer);
        private:
            std::vector<TJSClasses::LayerInstance *> primary_layers;
        };
    }
}