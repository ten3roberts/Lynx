#include <pch.h>
#include <src/Window.h>

namespace Lynx
{
	Window::Window(std::string title, unsigned int width, unsigned int height, WindowStyle style) 
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
		}

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
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