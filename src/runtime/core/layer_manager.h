#pragma once
#include "./tjs_classes/layer/layer_instance.h"

using namespace LibRuntime::TJSClasses;

namespace LibRuntime {
    class LayerManager {
    public:
        LayerManager(LayerInstance *primary_layer) {};
        void add_child_layer(LayerInstance *layer) {};
        void remove_child_layer(LayerInstance *layer) {};

    private:
        LayerInstance *primary_layer;
        std::vector<LayerInstance*> layers;
    };
}