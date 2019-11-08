#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Lynx
{
    class LYNX_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        ~Layer();

        // When the layer is added to the layer stack
        void onAttach() {}

        // When the layer is removed from the layer stack
        void onDetach() {}

        void onUpdate() { }
        void onEvent(Event& event) { LogS("Layer : " + m_name, "Event %S", event.getString()); event.setHandled(m_name == "2" && event.getEventType() == EventType::MouseButtonPressed); }

        inline const std::string getName() const { return m_name; }
        inline const bool getEnabled() const { return m_enabled; }
        inline void setEnabled(bool enabled) { m_enabled = enabled; }
    private:
        std::string m_name;
        bool m_enabled;
    };
}
