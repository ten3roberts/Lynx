#pragma once

#include "Time/Time.h"

extern Lynx::Application* Lynx::CreateApplication();

int main(int argc, char** argv)
{
	// Sets the working directory
	Tools::setWorkingDir(Tools::DirUp(argv[0]));

	auto application = Lynx::CreateApplication();
	if (!application->Init())
	{
		LogE("EntryPoint", "Could not initialize application. See above errors for details - aborting");
		return 1;
	}
	application->Run();
	delete application;
}
