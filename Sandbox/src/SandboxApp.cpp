#include <Lynx.h>

#include <stdio.h>

class Sandbox : public Lynx::Application
{
public:
	Sandbox()
	{
		printf("Starting project Sandbox\n");
	}
	~Sandbox()
	{

	}
};


Lynx::Application* Lynx::CreateApplication()
{
	return new Sandbox();
}