#include "pch.h"
#include "Renderer.h"
#include "Application.h"

namespace Lynx
{
	Renderer* Renderer::m_instance = nullptr;
	Renderer::Renderer() : m_vkInstance(nullptr) {}

	bool Renderer::Init()
	{
		LogS("Renderer", "Initializing");
		if (!CreateInstance())
			return false;

		// No errors occurred
		return true;
	}

	bool Renderer::CreateInstance()
	{
		LogS("Renderer", "Creating Vulkan instance");
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = Application::get()->getName().c_str();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Lynx";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// GLFW extensions

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		LogS("Vulkan", "GLFW needs %d extensions", glfwExtensionCount);
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		// The validation layers to enable. For now, 0
		createInfo.enabledLayerCount = 0;

		// Create the Vulkan instance
		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_vkInstance);
		if (result != VK_SUCCESS)
		{
			LogE("Renderer", "Could not create Vulkan instance - error code : %d", result);
			return false;
		}
		return true;
	}
} // namespace Lynx