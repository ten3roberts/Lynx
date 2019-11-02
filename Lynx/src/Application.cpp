#include <pch.h>
#include <src/Application.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

namespace Lynx
{
    Application::Application() : m_name("Lynx"), m_workingDir(CURR_DIR)
    {
		Time::Init();
		setWorkingDir(m_workingDir);
		glfwInit();
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
		Time::Init();
        while(true)
        {
			Time::Update();
			LogS(m_name, "Running frame %d. FPS : %g %c my full name %g", Time::frameCount, Time::frameRate, "HEllo my name is Time roberts", (float)time(NULL));
			SLEEP(1s);
			
        }
    }
}