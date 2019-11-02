#pragma once

#include <Events/Event.h>

namespace Lynx {

	class LYNX_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int getWidth() const { return m_Width; }
		inline unsigned int getHeight() const { return m_Height; }

		EVENT_CLASS(WindowResize, EventCategoryWindow | EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class LYNX_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS(WindowClose, EventCategoryWindow | EventCategoryApplication)
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