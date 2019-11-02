#pragma once
#include <Events/Event.h>

namespace Lynx
{
	class LYNX_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		EVENT_CLASS(MouseMoved, EventCategoryMouse | EventCategoryInput);

	private:
		//The new absolute position of the mouse
		float m_mouseX, m_mouseY;
	};

	class LYNX_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xScroll, float yScroll) : m_xScroll(xScroll), m_yScroll(yScroll) {}

		inline float getXScroll() const { return m_xScroll; }
		inline float getYScroll() const { return m_yScroll; }

		EVENT_CLASS(MouseScrolled, EventCategoryMouse | EventCategoryInput)

	private:
		//The position of the scroll wheel
		float m_xScroll, m_yScroll;
	};

	class LYNX_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_button(button) {}
		int m_button;
	};

	class LYNX_API MouseButtonPressedEvent : public MouseButtonEvent
		{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class LYNX_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}