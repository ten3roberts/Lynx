#pragma once

#include "Core.h"
#include "string"
#include "GLFW/glfw3.h"
#include "Events/Event.h"
#include <functional>

namespace Lynx
{
	enum class WindowStyle
	{
		Windowed, Borderless, Fullscreen
	};

	//Represents a crossplatform window class. Stores vSync, resoulution, style, title. Set width and height to -1 to use native resolution
	//TODO : Handle events
	class LYNX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(std::string title = APPNAME, int width = 800, int height = 600, WindowStyle style = WindowStyle::Windowed);
		~Window() { Close(); }
		void onUpdate();

		void Close();

		void setVSync(bool enable);
		bool getVSync() const { return m_data.vSync; }

		std::string getTitle() const { return m_data.title; }
		void setTitle(const std::string title);

		bool inFocus() const { return m_data.inFocus; }

		void setEventCallback(const EventCallbackFn& callback);
	private:
		void Init();

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			bool inFocus;
			EventCallbackFn eventCallback;
		};
	private:
		WindowData m_data;
		GLFWwindow* m_window;
		WindowStyle m_style;
		bool m_nativeSize;
	};
}