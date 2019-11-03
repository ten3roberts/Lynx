#include <pch.h>
#include <src/Window.h>

namespace Lynx
{
	Window::Window(std::string title, int width, int height, WindowStyle style) : m_style(style)
	{
		m_data.title = title;
		m_data.width = width;
		m_data.height = height;
		
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

	void Window::Init()
	{
		// Initialize GLFW if it's not already done
		LogS("Window : " + m_data.title, "Creating window [%u, %u]", m_data.width, m_data.height);

		if (!s_GLFWInitialized)
		{
			LogS("Window : " + m_data.title, "Initializing GLFW");

			int success = glfwInit();
			const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
			const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
			//printf("%s\n", vendor);
			LogS("Window : " + m_data.title, "Vendor %c, Graphics card %c", (char*)vendor, (char*)renderer);

			// Set to true even if initialization failed
			s_GLFWInitialized = true;

			if (!success)
			{
				LogE("Window : " + m_data.title, "Could not initialize GLFW");
				return;
			}
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
	}

	void Window::Close()
	{
		glfwDestroyWindow(m_window);
	}
	void Window::enableVSync(bool enable)
	{
		glfwSwapInterval(enable);
		m_data.vSync = enable;
	}
}