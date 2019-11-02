#include <Lynx.h>

#include <stdio.h>
class Sandbox : public Lynx::Application
{
public:
	Sandbox()
	{
		m_name = "Sandbox";
		//LogF("Starting project Sandbox\n");
		//std::string str = Tools::strPadLeft("Hello", 10, '-');
		std::string str = "Hello";
		Test(str);
	}
	~Sandbox()
	{

	}
};

Lynx::Application* Lynx::CreateApplication()
{
	return new Sandbox();
}