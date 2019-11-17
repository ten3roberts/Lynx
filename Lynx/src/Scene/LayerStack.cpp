#include "LayerStack.h"

#include "pch.h"

namespace Lynx
{
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::AddLayer(Layer* layer) { m_layers.emplace_back(layer); }

	void LayerStack::AddLayer(Layer* layer, size_t position) { m_layers.emplace(m_layers.begin() + position, layer); }

	void LayerStack::RemoveLayer(size_t position) { m_layers.erase(m_layers.begin() + position); }

	void LayerStack::RemoveLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			delete *it;
		}
	}
} // namespace Lynx
