#include "Renderer.h"
#include "Application.h"
#include "pch.h"

namespace Lynx
{
#if DEBUG
	const bool enableValidationLayers = true;
	const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
#else
	const std::vector<const char*> validationLayers = {};
	const bool enableValidationLayers = false;
#endif
#pragma region helper functions
	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
												 VkDebugUtilsMessageTypeFlagsEXT messageType,
												 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
												 void* pUserData)
	{

		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			// Important (error) message
			LogE("Renderer", pCallbackData->pMessage);
		}

		return VK_FALSE;
	}

	bool checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	std::vector<const char*> getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
										  const VkAllocationCallbacks* pAllocator,
										  VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func =
			(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
									 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
									 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
									   const VkAllocationCallbacks* pAllocator)
	{
		auto func =
			(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			func(instance, debugMessenger, pAllocator);
		}
	}
#pragma endregion

	Renderer* Renderer::m_instance = nullptr;
	Renderer::Renderer()
		: m_vkInstance(VK_NULL_HANDLE), m_debugMessenger(VK_NULL_HANDLE), m_physicalDevice(VK_NULL_HANDLE)

	{
	}

	bool Renderer::Init()
	{
		LogS("Renderer", "Initializing");
		if (!CreateInstance())
			return false;

		CreateDebugMessenger();

		if (!CreatePhysicalDevice())
			return false;

		if (!CreateLogicalDevice())
			return false;
		// No errors occurred
		return true;
	}

	bool Renderer::CreateInstance()
	{
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
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		LogF("Renderer", "GLFW needs %d extensions", glfwExtensionCount);

		// Getting required extension count
		std::vector<const char*> extensions = getRequiredExtensions();

		// Enables GLFW required extensions*
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		LogF("Renderer", "Extensions used (%d) : ", extensions.size());
		for (const char* extension : extensions)
		{
			printf("\t%s\n", extension);
		}

		// Validation layers for debugging
		// In release these are disabled
		LogF("Renderer", "Validation layers used (%d) : ", validationLayers.size());
		for (const char* validationLayer : validationLayers)
		{
			printf("\t%s\n", validationLayer);
		}
		if (validationLayers.size() && !checkValidationLayerSupport())
		{
			LogE("Renderer", "Some of the requested validation layers are not supported");
			return false;
		}

		// Enabling temporary debug messager before vkInstance creation
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();

			populateDebugMessengerCreateInfo(debugCreateInfo);
			// createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		// Create the Vulkan instance
		LogS("Renderer", "Creating Vulkan instance");

		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_vkInstance);
		if (result != VK_SUCCESS)
		{
			LogE("Renderer", "Failed to create Vulkan instance - error code : %d", result);
			return false;
		}
		return true;
	}

	// Returns a score of how suitable or favorable one GPU is to Another
	int Renderer::getDeviceSuitability(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = getQueueFamilies(device);
		if (!indices.getComplete())
			return -1;

		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// Device passed all required steps
		// Rate GPU to pick the best one - useful for laptops to use discrete GPU
		int score = 0;

		// Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		// Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;

		// Application can't function without geometry shaders
		if (!deviceFeatures.geometryShader)
		{
			return 0;
		}

		return score;
	}

	bool Renderer::CreatePhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			LogE("Renderer", "Failed to find GPUs with Vulkan support");
			return false;
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, devices.data());

		// Use an ordered map to automatically sort candidates by increasing score
		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : devices)
		{
			int score = getDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}

		if (candidates.rbegin()->first > 0)
		{
			m_physicalDevice = candidates.rbegin()->second;
		}
		else
		{
			LogE("Renderer", "Failed to find suitable GPU");
			return false;
		}

		return true;
	}

	bool Renderer::CreateLogicalDevice()
	{
		// Specifying the queues to be created
		QueueFamilyIndices indices = getQueueFamilies(m_physicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		// Setting the logical device features
		VkPhysicalDeviceFeatures deviceFeatures = {};

		// Specifying the create info for the device itself
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;

		createInfo.pEnabledFeatures = &deviceFeatures;

		// For now, we don't need any device specific extensions
		createInfo.enabledExtensionCount = 0;

		// Use validation layers even though they're deprecated for compatability with older implementations
		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
		{
			LogE("Renderer", "Failed to create logical device");
			return false;
		}

		// Get queue handles
		vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		return true;
	}

	QueueFamilyIndices Renderer::getQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;
		// Assign index to queue families that could be found

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			i++;
		}
		return indices;
	}

	void Renderer::Terminate()
	{
		if (enableValidationLayers)
		{
			DestroyDebugUtilsMessengerEXT(m_vkInstance, m_debugMessenger, nullptr);
		}
		vkDestroyDevice(m_device, nullptr);
		vkDestroyInstance(m_vkInstance, nullptr);
		glfwTerminate();
	}

} // namespace Lynx
void Lynx::Renderer::CreateDebugMessenger()
{
	if (!enableValidationLayers)
		return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(m_vkInstance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
	{
		LogE("Renderer", "Failed to set up debug messenger!");
	}
}
