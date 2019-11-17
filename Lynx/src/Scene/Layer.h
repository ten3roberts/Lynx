#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Input/keycodes.h"
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

		void Update() {}
		void onEvent(Event& event)
		{
			if (m_name == "2" && ((KeyPressedEvent*)&event)->getKeyCode() == KEY_B)
				event.setHandled(true);
		}

		inline const std::string getName() const { return m_name; }
		inline const bool getEnabled() const { return m_enabled; }
		inline void setEnabled(bool enabled) { m_enabled = enabled; }

	  private:
		std::string m_name;
		bool m_enabled;
	};
} // namespace Lynx
