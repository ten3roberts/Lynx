#include "pch.h"
#include "Layer.h"


namespace Lynx
{
	Layer::Layer(const std::string& name) : m_name(name) { LogS("Layer", "Creating layer %S", m_name); }

	Layer::~Layer() {}
} // namespace Lynx
