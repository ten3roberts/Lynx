#pragma once

extern Lynx::Application* Lynx::CreateApplication();

int main(int argc, char** argv)
{
	auto application = Lynx::CreateApplication();
    application->Run();
    delete application;
}
