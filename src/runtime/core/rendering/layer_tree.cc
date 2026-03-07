#include "layer_tree.h"
#include "../native_instances/layer_instance.h"

using namespace LibRuntime::Rendering;
using namespace LibRuntime::Interfaces;

void LayerTree::add_primary_layer(NativeInstances::LayerNativeInstance *layer) {
    if (primary_layers.size() == 0) {
        primary_layers.push_back(layer);
        return;
    }
}

void LayerTree::remove_primary_layer(NativeInstances::LayerNativeInstance *layer) {
    std::erase(primary_layers, layer);
}

void LayerTree::render(IGraphicsWindow *gfx) {
    gfx->begin_frame();
    for (auto* layer : primary_layers) {
        auto* texture = layer->render(gfx);
        if (texture == nullptr) continue;
        gfx->draw_texture(texture, layer->get_render_rect());
    }
    gfx->end_frame();
}
