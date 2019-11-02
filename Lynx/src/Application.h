#pragma once

#include <src/Core.h>
#include <src/Tools.h>
#include <string>
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
    };

    // To be defined in client
	Application* CreateApplication();
}