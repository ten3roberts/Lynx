#pragma once

#include <src/Core.h>

namespace Lynx
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
    };

    //To be defined in client
    Application* CreateApplication();
}