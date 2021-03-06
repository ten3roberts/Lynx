#pragma once

#include <functional>
#include <string>

#include "Core.h"
#include "Events/Event.h"
//#include "glad/glad.h"

struct GLFWwindow;

namespace Lynx
{
	enum class WindowStyle
	{
		// Creates a decorated window. Uses set width and height
		Windowed,
		// Creates an undercorated window. Uses set width and height
		Borderless,
		// Creates a fullscreen undecorated window covering kde panels. width and
		// height are overridden to the displays resulution
		Fullscreen
	};

	// Represents a crossplatform window class. Stores vSync, resoulution, style,
	// title. Set width and height to -1 to use native resolution
	// TODO : Handle events
	class LYNX_API Window
	{
	  public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(std::string title = APPNAME, int width = 800, int height = 600,
			   WindowStyle style = WindowStyle::Windowed);
		~Window() { Close(); }
		void Update();

		void Close();

		void setVSync(bool enable);
		bool getVSync() const { return m_data.vSync; }

		std::string getTitle() const { return m_data.title; }
		void setTitle(const std::string title);

		bool inFocus() const { return m_data.inFocus; }

		void setEventCallback(const EventCallbackFn& callback);

		GLFWwindow* getRawWindow() { return m_window; }

		int GetWidth() const {return m_data.width; }
		int GetHeight() const {return m_data.height; }

		void Init();
	  private:

		struct WindowData
		{
			std::string title;
			int width, height;
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
} // namespace Lynx