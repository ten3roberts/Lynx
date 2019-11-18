#include "pch.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "GLFW/glfw3.h"

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
	void Window::Update()
	{
		glfwPollEvents();
		// glfwSwapBuffers(m_window);
	}

	void Window::setTitle(const std::string title)
	{
		m_data.title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}

	void Window::setEventCallback(const EventCallbackFn& callback) { m_data.eventCallback = callback; }

	void Window::Init()
	{
		{
			std::string width_string = m_data.width > 0 ? STR(m_data.width) : "(native)";
			std::string height_string = m_data.height > 0 ? STR(m_data.height) : "(native)";
			LogS("Window : " + m_data.title, "Creating window [%S, %S]", width_string, height_string);
		}

		// Initialize GLFW once
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

		// Sets the resolution to native if res is set to -1
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primary);
		m_data.width = m_data.width > 0 ? m_data.width : mode->width;
		m_data.height = m_data.height > 0 ? m_data.height : mode->height;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		if (m_style == WindowStyle::Windowed)
		{
			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		}

		else if (m_style == WindowStyle::Borderless)
		{
			// const GLFWvidmode* mode = glfwGetVideoMode(primary);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwWindowHint(GLFW_DECORATED, GL_FALSE);

			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		}

		else if (m_style == WindowStyle::Fullscreen)
		{
			// const GLFWvidmode* mode = glfwGetVideoMode(primary);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwWindowHint(GLFW_DECORATED, GL_FALSE);
			m_data.width = mode->width;
			m_data.height = mode->height;
			m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), primary, nullptr);
		}

		// glfwMakeContextCurrent(m_window);
		// int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// if (!status)
		//	LogE("Window", "Failed to initialize glad");
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

#pragma region callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int key, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xScroll, double yScroll) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xScroll, (float)yScroll);

			data.eventCallback(event);
		});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.inFocus = focus;

			WindowFocusEvent event(focus);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.eventCallback(event);
		});
#pragma endregion
	}

	void Window::Close()
	{
		LogS("Window " + m_data.title, "Destroying window");
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	void Window::setVSync(bool enable)
	{
		// glfwSwapInterval(enable);
		m_data.vSync = enable;
	}
} // namespace Lynx