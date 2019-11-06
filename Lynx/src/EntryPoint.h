#pragma once

#include "Time/Time.h"

extern Lynx::Application* Lynx::CreateApplication();

int main(int argc, char** argv)
{
	Time::Init();
	// Sets the working directory
	Tools::setWorkingDir(Tools::DirUp(argv[0]));

	auto application = Lynx::CreateApplication();
    application->Run();
    delete application;
}
