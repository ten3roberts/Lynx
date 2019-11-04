#include <pch.h>
#include <src/Window.h>
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Lynx
{

	static void GLFWError(int code, const char* description)
	{
		LogE("GLFW Error", "Error : %d, %s", code, description);
	}

	Window::Window(std::string title, int width, int height, WindowStyle style) : m_style(style)
	{
		m_data.title = title;
		m_data.width = width;
		m_data.height = height;
		m_data.vSync = false;
		m_data.inFocus = false;
		
		Init();
	}
	static bool s_GLFWInitialized = false;
	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Window::setTitle(const std::string title)
	{
		m_data.title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}

	void Window::setEventCallback(const EventCallbackFn& callback)
	{
		m_data.eventCallback = callback;
	}

	void Window::Init()
	{
		// Initialize GLFW if it's not already done
		LogS("Window : " + m_data.title, "Creating window [%u, %u]", m_data.width, m_data.height);

		if (!s_GLFWInitialized)
		{
			LogS("Window : " + m_data.title, "Initializing GLFW");

			int success = glfwInit();

			// Set to true even if initialization failed
			s_GLFWInitialized = true;

			if (!success)
			{
				LogE("Window : " + m_data.title, "Could not initialize GLFW");
				return;
			}

			glfwSetErrorCallback(GLFWError);
		}

		GLFWmonitor* primary = glfwGetPrimaryMonitor();

		if (m_style == WindowStyle::Windowed)
		{
			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);			
		}

		else if (m_style == WindowStyle::Borderless)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(primary);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwWindowHint(GLFW_DECORATED, GL_FALSE);
			
			m_window = glfwCreateWindow(mode->width, mode->height, m_data.title.c_str(), nullptr, nullptr);

		}

		else if (m_style == WindowStyle::Fullscreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(primary);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwWindowHint(GLFW_DECORATED, GL_FALSE);

			m_window = glfwCreateWindow(mode->width, mode->height, m_data.title.c_str(), primary, nullptr);

		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS :
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE :
			{
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT :
			{	
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int key, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS :
			{
				MouseButtonPressedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE :
			{
				MouseButtonReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xScroll, double yScroll)
		{
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xScroll, (float)yScroll);

			data.eventCallback(event);
		});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus)
		{
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.inFocus = focus;

			WindowFocusEvent event(focus);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y)
		{
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.eventCallback(event);
		});
	}

	void Window::Close()
	{
		LogS("Window " + m_data.title, "Destroying window");
		glfwDestroyWindow(m_window);
	}
	void Window::setVSync(bool enable)
	{
		glfwSwapInterval(enable);
		m_data.vSync = enable;
	}
}