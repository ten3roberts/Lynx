#pragma once

extern Lynx::Application* Lynx::CreateApplication();

int main(int argc, char** argv)
{
	//Sets the working directory
	Tools::setWorkingDir(argv[0]);

	auto application = Lynx::CreateApplication();
    application->Run();
    delete application;
}
