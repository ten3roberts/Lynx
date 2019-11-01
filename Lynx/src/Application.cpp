#include <pch.h>
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
		Time::Init();
        while(true)
        {
			Time::Update();
			LogS("Application", "Running frame %d", Time::frameCount);
			SLEEP(1s);
			
        }
    }
}