#include <pch.h>
#include <src/Application.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>

namespace Lynx
{
	Application::Application() : m_name("Lynx"), m_running(false)
	{
		m_window = new Window(APPNAME, 800, 600, WindowStyle::Windowed);
		m_window->setEventCallback(BIND(Application::onEvent));
	}

	Application::~Application()
	{
		LogS("Application", "Terminating");
		glfwTerminate();
	}

	

	void Application::Run()
	{
		Time::Init();
		m_running = true;
		while (m_running)
		{
			Time::Update();


			m_window->setTitle(format("%c fps : %d", APPNAME, (int)Time::frameRate));

			glClearColor(0.5, 0, 1, 0);

			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND(Application::onWindowClose));
		//LogS("Application : onEvent", e.getString());
	}

	void Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		e.setHandled(true);
	}

}