#pragma once

#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Scene/LayerStack.h"

class Renderer;

namespace Lynx
{
	class LYNX_API Application
	{
	  public:
		Application();
		virtual ~Application();

		bool Init();

		void Run();

		void onEvent(Event& e);

		// Adds a layer to the end of the stack
		void AddLayer(Layer* layer);
		void AddLayer(Layer* layer, size_t position);

		// Removes a layer from the stack and frees the memory
		void RemoveLayer(size_t position);
		void RemoveLayer(Layer* layer);

		std::string getName() const { return m_name; }

		static Application* get() { return m_instance; }

	  private:
		static Application* m_instance;
		void onWindowClose(WindowCloseEvent& e);
		LayerStack m_layerStack;

		// The renderer is a singleton and this is not the only reference pointer to it
		Renderer* m_renderer;

	  protected:
		std::string m_name;
		Window* m_window;
		// Indicates if the update loop should continue. Set to true when entering
		// update loop
		bool m_running;
	};

	// To be defined in client
	Application* CreateApplication();
} // namespace Lynx