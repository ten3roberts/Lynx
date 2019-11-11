#include <pch.h>
#include <Application.h>
#include <stdio.h>
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>

namespace Lynx
{
	Application::Application() : m_name("Lynx"), m_running(false)
	{
		m_window = new Window(APPNAME, 800, 600, WindowStyle::Windowed);
		m_window->setEventCallback(BIND(Application::onEvent));
		LogF(Tools::FindFile("/textures/sprite.png"));
	}

	Application::~Application()
	{
		LogS("Application", "Terminating");

		delete m_window;

		glfwTerminate();
	}

	

	void Application::Run()
	{
		Time::Init();
		m_running = true;
		while (m_running)
		{
			Time::Update();

			m_window->setTitle(format("%s fps : %d", APPNAME, (int)Time::frameRate));

			glClearColor(0.5, 0, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_layerStack)
			{
				layer->Update();
			}
			
			m_window->Update();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND(Application::onWindowClose));

	if(e.getEventType() == EventType::MouseMoved)
		return;
	//Goes through the layers backwards so the last rendered layer gets the event first
	for(auto it = m_layerStack.end(); it != m_layerStack.begin();)
	{
		(*--it)->onEvent(e);
		if(e.getHandled())
			break;
	}

		//LogS("Application : onEvent", e.getString());
	}



	// Adds a layer to the end of the stack
    void Application::AddLayer(Layer* layer)
	{
		m_layerStack.AddLayer(layer);
	}
    void Application::AddLayer(Layer* layer, size_t position)
	{
		m_layerStack.AddLayer(layer, position);
	}

	// Removes a layer from the stack and frees the memory
    void Application::RemoveLayer(size_t position)
	{
		m_layerStack.RemoveLayer(position);
	}

    void Application::RemoveLayer(Layer* layer)
	{
		m_layerStack.RemoveLayer(layer);
	}

	void Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		e.setHandled(true);
	}

}