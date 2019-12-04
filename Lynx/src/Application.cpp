#include "pch.h"
#include "Renderer/Vulkan.h"
#include <Application.h>
#include <Events/ApplicationEvent.h>
#include <Events/Event.h>
#include <stdio.h>

#include "Input/Input.h"

namespace Lynx
{
	Application* Application::m_instance = nullptr;
	Application::Application() : m_name("Lynx"), m_running(false), m_renderer(nullptr)
	{
		m_instance = this;
	}

	Application::~Application()
	{
		LogS("Application", "Terminating");

		delete m_window;

		m_renderer->Terminate();
	}

	bool Application::Init()
	{
		Timer timer("Application::Init");
		Time::Init();

		m_window = new Window(m_name, 800, 600, WindowStyle::Windowed);
		m_window->setEventCallback(BIND(Application::onEvent));

		m_renderer = Vulkan::get();
		if (!m_renderer->Init())
		{
			LogE("Application", "Failed to initialize Vulkan");
			return false;
		}
		return true;
	}

	void Application::Run()
	{
		m_running = true;

		LogS("Application", "Entering main loop");

		while (m_running)
		{
			Time::Update();

			m_window->setTitle(format("%s fps : %d", m_name.c_str(), (int)Time::frameRate));

			for (Layer* layer : m_layerStack)
			{
				layer->Update();
			}

			Input::Update();
			m_window->Update();
			SLEEP(5ms);
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

		LogF("Application : onEvent", e.getString());
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