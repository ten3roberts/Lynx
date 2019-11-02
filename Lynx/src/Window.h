#pragma once

#include <src/Core.h>
#include <string>
#include <GLFW/glfw3.h>
#include <Events/Event.h>
#include <functional>

namespace Lynx
{
	enum class WindowStyle
	{
		Windowed, Borderless, Fullscreen
	};

	class LYNX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(std::string title = APPNAME, unsigned int width = 800, unsigned int height = 600, WindowStyle style = WindowStyle::Windowed);
		~Window() { Close(); }
		void onUpdate();

		void Close();

		void enableVSync(bool enable);
		bool isVSync() const { return m_data.vSync; }
	private:
		void Init();

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFn eventCallback;
		};
		WindowData m_data;
		GLFWwindow* m_window;
		WindowStyle m_style;
	};
}