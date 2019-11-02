#pragma once

#include <src/Core.h>
#include <src/Tools.h>
#include <string>
#include <src/Window.h>
namespace Lynx
{
    class LYNX_API Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
	protected:
		std::string m_name;
		Window* m_window;
		// Indicates if the update loop should continue. Set to true when entering update loop
		bool m_running;
    };

    // To be defined in client
	Application* CreateApplication();
}