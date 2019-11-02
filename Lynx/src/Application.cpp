#include <pch.h>
#include <src/Application.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <Events/Event.h>'
#include <Events/AppicationEvent.h>

namespace Lynx
{
    Application::Application() : m_name("Lynx")
    {
		glfwInit();
    }

    Application::~Application()
    {
		glfwTerminate();
    }

    void Application::Run()
    {
		Time::Init();
        while(true)
        {
			Time::Update();

			LogS(m_name, "Running frame %d", Time::frameCount);
			SLEEP(1s);
			
        }
    }
}