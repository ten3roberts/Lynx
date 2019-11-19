#include <Lynx.h>

#include <stdio.h>
Lynx::Application* Lynx::Application::m_instance = nullptr;
class Sandbox : public Lynx::Application
{
public:
	Sandbox()
	{
		m_name = "Sandbox";
		AddLayer(new Lynx::Layer("1"));
		AddLayer(new Lynx::Layer("2"));
		AddLayer(new Lynx::Layer("3"));
	}
	~Sandbox()
	{

	}
};

Lynx::Application* Lynx::CreateApplication()
{
	return new Sandbox();
}