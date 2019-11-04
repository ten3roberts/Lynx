#pragma once

#include <Events/Event.h>

namespace Lynx {

	class LYNX_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		EVENT_CLASS(WindowResize, EventCategoryWindow | EventCategoryApplication)

		std::string getString() const override 
		{
			return format("WindowResizeEvent : [%d %d]", m_width, m_height);
		}
	private:
		unsigned int m_width, m_height;
	};

	class LYNX_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS(WindowClose, EventCategoryWindow | EventCategoryApplication)

		std::string getString() const override 
		{
			return format("WindowCloseEvent");
		}
	};

	class LYNX_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool inFocus) : m_inFocus(inFocus) {}

		bool getFocus() const { return m_inFocus; }

		EVENT_CLASS(WindowFocus, EventCategoryWindow | EventCategoryApplication)

		std::string getString() const override 
		{
			return format("WindowFocusEvent : %s", FormatBool(m_inFocus));
		}
	private:
		bool m_inFocus;
	};

	class LYNX_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		EVENT_CLASS(AppTick, EventCategoryApplication)
	};

	class LYNX_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS(AppUpdate, EventCategoryApplication)
	};

	class LYNX_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS(AppRender, EventCategoryApplication)
	};
}