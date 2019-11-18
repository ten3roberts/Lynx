#include "pch.h"
#include "Renderer/Renderer.h"
#include <Application.h>
#include <Events/ApplicationEvent.h>
#include <Events/Event.h>
#include <stdio.h>

#include "Input/Input.h"

namespace Lynx
{
	Application* Application::m_instance = nullptr;
	Application::Application() : m_name("Lynx"), m_running(false)
	{
		// StartVulkan();
		m_instance = this;
		m_window = new Window(APPNAME, 800, 600, WindowStyle::Windowed);
		m_window->setEventCallback(BIND(Application::onEvent));

		m_renderer = Renderer::get();
		LogF("%b", m_renderer->Init());

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

			for (Layer* layer : m_layerStack)
			{
				layer->Update();
			}

			Input::Update();
			m_window->Update();
			SLEEP(2ms);
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND(Application::onWindowClose));

		if (e.getEventType() == EventType::MouseMoved)
			return;
		// Goes through the layers backwards so the last rendered layer gets the event
		// first
		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.getHandled())
				break;
		}

		// If input event has not been handled, send it to input to receive
		if (e.CheckCategory(EventCategoryInput))
			Input::onEvent(e);

		LogS("Application : onEvent", e.getString());
	}

	// Adds a layer to the end of the stack
	void Application::AddLayer(Layer* layer) { m_layerStack.AddLayer(layer); }
	void Application::AddLayer(Layer* layer, size_t position) { m_layerStack.AddLayer(layer, position); }

	// Removes a layer from the stack and frees the memory
	void Application::RemoveLayer(size_t position) { m_layerStack.RemoveLayer(position); }

	void Application::RemoveLayer(Layer* layer) { m_layerStack.RemoveLayer(layer); }

	void Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		e.setHandled(true);
	}

} // namespace Lynx