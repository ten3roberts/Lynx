#pragma once
#include <src/Core.h>
namespace Lynx
{
	//Events block the whole event until they are handled

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowsFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum class EventCategory
	{
		None = 0,
		Application		= BIT(0),
		Input			= BIT(1),
		Keyboard		= BIT(2),
		Mouse			= BIT(3),
		MouseButton		= BIT(4)
	};
}