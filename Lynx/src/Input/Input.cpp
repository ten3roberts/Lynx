#include "Input.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Lynx
{

	bool Input::m_keys[KEY_LAST] = {0};
	bool Input::m_prevKeys[KEY_LAST] = {0};

	bool Lynx::Input::getKeyHit(int keycode) { return m_keys[keycode] && !m_prevKeys[keycode]; }

	bool Lynx::Input::getKeyDown(int keycode) { return m_keys[keycode]; }

	bool Lynx::Input::getKeyReleased(int keycode) { return !m_keys[keycode] && m_prevKeys[keycode]; }

	void Lynx::Input::onEvent(Event& event)
	{
		if (event.getEventType() == EventType::KeyPressed)
		{
			KeyPressedEvent* e = (KeyPressedEvent*)&event;
			// Key will not be pressed when event gets handled, but will be released
			if (!e->getHandled())
				m_keys[e->getKeyCode()] = true;
		}
		else if (event.getEventType() == EventType::KeyReleased)
		{
			KeyReleasedEvent* e = (KeyReleasedEvent*)&event;
			m_keys[e->getKeyCode()] = false;
		}

		else if (event.getEventType() == EventType::MouseButtonPressed)
		{
			MouseButtonPressedEvent* e = (MouseButtonPressedEvent*)&event;
			// Key will not be pressed when event gets handled, but will be released
			if (!e->getHandled())
				m_keys[e->getMouseButton()] = true;
		}

		else if (event.getEventType() == EventType::MouseButtonReleased)
		{
			MouseButtonReleasedEvent* e = (MouseButtonReleasedEvent*)&event;
			m_keys[e->getMouseButton()] = false;
		}
	}
	void Lynx::Input::Update() { memcpy(m_prevKeys, m_keys, sizeof(bool) * KEY_LAST); }

	Lynx::Input::Input()
	{
		printf("Input\n");
		memset(m_keys, 0, sizeof(bool) * KEY_LAST);
		memset(m_prevKeys, 0, sizeof(bool) * KEY_LAST);
	}

} // namespace Lynx
