#pragma once
#include <Events/Event.h>

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
	private:
		int m_repeatCount;
	};

	class LYNX_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode) {}
		EVENT_CLASS_TYPE(KeyReleased)
	};
}