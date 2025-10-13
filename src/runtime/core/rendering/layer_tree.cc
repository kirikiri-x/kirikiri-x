#include "layer_tree.h"
#include "../tjs_classes/layer/layer_instance.h"

using namespace LibRuntime::Rendering;

void LayerTree::add_primary_layer(TJSClasses::LayerInstance *layer) {
    if (primary_layers.size() == 0) {
        primary_layers.push_back(layer);
        return;
    }
}

void LayerTree::remove_primary_layer(TJSClasses::LayerInstance *layer) {
    std::erase(primary_layers, layer);
}

void LayerTree::render(SDL_Renderer *renderer) {
    for (auto layer : primary_layers) {
        auto texture = layer->render(renderer);
        auto rect = layer->get_render_rect();
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}