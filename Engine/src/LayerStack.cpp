#include "LayerStack.h"
#define _CRTDBG_MAP_ALLOC

#include <algorithm>

namespace Azazel
{
    LayerStack::LayerStack()
    {
        this->layerInsert = this->layers.begin();
    }
    
    LayerStack::~LayerStack()
    {
        for (auto layer : layers)
        {
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        layerInsert = layers.emplace(layerInsert, layer);
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
    }
    
    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end())
        {
            layers.erase(it);
            layerInsert--;
        }
    }
    
    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end())
        {
            layers.erase(it);
        }
    }
}