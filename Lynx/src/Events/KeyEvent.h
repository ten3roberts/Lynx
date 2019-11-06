#pragma once
#include "Events/Event.h"
#include "Tools.h"

namespace Lynx
{
	class LYNX_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) : m_keyCode(keyCode) {}
		int m_keyCode;
	};

	class LYNX_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}
		EVENT_CLASS_TYPE(KeyPressed)

		std::string getString() const override 
		{
			return format("KeyPressedEvent : [%d %c] (%d repeats)", m_keyCode, std::string(1, (char)m_keyCode), m_repeatCount);
		}
	private:
		int m_repeatCount;
	};

	class LYNX_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
		EVENT_CLASS_TYPE(KeyReleased)

		std::string getString() const override 
		{
			return format("KeyReleasedEvent : [%d %s]", m_keyCode, std::string(1, (char)m_keyCode));
		}
	};
}