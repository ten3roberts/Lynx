#include <pch.h>
#include <src/Application.h>
#include <stdio.h>

namespace Lynx
{
    Application::Application() : m_name("Lynx"), m_workingDir(CURR_DIR)
    {
		Time::Init();
		setWorkingDir(m_workingDir);
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
			LogS(m_name, "Running frame %d", Time::frameCount);
			SLEEP(1s);
			
        }
    }
}