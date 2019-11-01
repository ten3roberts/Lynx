#pragma once

#include <src/Core.h>
#include <src/Tools.h>
#include <string>
namespace Lynx
{
    class LYNX_API Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
			std::string getWorkingDir() { return m_workingDir; }
			void setWorkingDir(const std::string& workingDir) { m_workingDir = workingDir; Tools::setWorkingDir(m_workingDir); }
	protected:
		std::string m_name;
		std::string m_workingDir;
    };

    //To be defined in client
	Application* CreateApplication();
}