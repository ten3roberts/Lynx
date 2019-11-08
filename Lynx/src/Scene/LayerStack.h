#pragma once

#include "Core.h"

#include "Layer.h"
#include "pch.h"

namespace Lynx
{
    class LYNX_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        // Adds a layer to the end of the stack
        void AddLayer(Layer* layer);
        void AddLayer(Layer* layer, size_t position);

        // Removes a layer from the stack and frees the memory
        void RemoveLayer(size_t position);
        void RemoveLayer(Layer* layer);

        std::vector<Layer*>::iterator begin() {return m_layers.begin(); }
        std::vector<Layer*>::iterator end() {return m_layers.end(); }

    private:
        std::vector<Layer*> m_layers;
    };

} // namespace Lynx
