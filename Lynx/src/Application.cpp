#include <src/Application.h>
#include <stdio.h>

namespace Lynx
{
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while(true)
        {
            printf("Running \n");
			SLEEP(1);
        }
    }
}