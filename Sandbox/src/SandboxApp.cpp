#include <Lynx.h>

#include <stdio.h>
class Sandbox : public Lynx::Application
{
public:
	Sandbox()
	{
		m_name = "Sandbox";
	}
	~Sandbox()
	{

	}
};

Lynx::Application* Lynx::CreateApplication()
{
	return new Sandbox();
}