#include <pch.h>
#include <src/Application.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <Events/Event.h>
#include <Events/AppicationEvent.h>

namespace Lynx
{
    Application::Application() : m_name("Lynx")
    {
		m_window = new Window();
    }

    Application::~Application()
    {
		delete m_window;
		glfwTerminate();
    }

    void Application::Run()
    {
		Time::Init();
		m_running = true;
        while(m_running)
        {
			glClearColor(0.5, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			Time::Update();
			m_window->onUpdate();			
        }
    }
}