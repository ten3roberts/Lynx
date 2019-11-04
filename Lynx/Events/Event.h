#pragma once
#include <src/Core.h>
#include <functional>
#include <string>

namespace Lynx
{
	// Events block the whole event until they are handled

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowsFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory
	{
		EventCategoryNone = 0,
		EventCategoryApplication		= BIT(0),
		EventCategoryWindow				= BIT(1),
		EventCategoryInput				= BIT(2),
		EventCategoryKeyboard			= BIT(3),
		EventCategoryMouse				= BIT(4),
		EventCategoryMouseButton		= BIT(5)
	};

#define EVENT_CLASS_TYPE(type)			static EventType getStaticType() { return EventType::type; }\
										virtual EventType getEventType() const override { return getStaticType(); }\
										virtual std::string getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int getCategories() const override { return category; }

#define EVENT_CLASS(type, category)		static EventType getStaticType() { return EventType::type; }\
										virtual EventType getEventType() const override { return getStaticType(); }\
										virtual std::string getName() const override { return #type; }\
										virtual int getCategories() const override { return category; }


	class LYNX_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		// Returns the bitfield of the catagories of the event
		virtual int getCategories() const = 0;
		virtual std::string getName() const = 0;
		
		// Returns true if event is in the given category
		inline bool CheckCategory(EventCategory category) { return getCategories() & category; }

		void setHandled(bool handled) { m_handled = handled; }
	protected:
		bool m_handled = false;
	};

	class LYNX_API EventDispatcher
	{
	public:
		template <typename T>
		using EventFn = std::function<void(T&)>;
		EventDispatcher(Event& event) : m_event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			//  If current event matches template event, run the func with event
			if(m_event.getEventType() == T::getStaticType())
			{
				//  The function sets if the event have been handled
				func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};
}