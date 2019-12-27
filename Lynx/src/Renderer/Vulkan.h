#pragma once
#include "Core.h"
//#define GLFW_EXPOSE_NATIVE_X11
//#define VK_USE_PLATFORM_XLIB_KHR
//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

namespace Lynx
{

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool getComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	// Represents a singleton Vulkan using vulkan
	// Is global to all threads
	// Need to be explicitely initialized before using
	class LYNX_API Vulkan
	{
	  public:
		// Initializes Vulkan and all other required components
		// Returns true on success
		bool Init();

		// Terminates and frees all graphic
		void Terminate();

		static Vulkan* get()
		{
			if (!m_instance)
				m_instance = new Vulkan;
			return m_instance;
		}

	  private:
		Vulkan();
		// Creates a Vulkan instance
		bool CreateInstance();

		int getDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface);

		bool CreatePhysicalDevice();

		bool CreateLogicalDevice();

		bool CreateSwapChain();

		// Creates a debug message callback handle
		void CreateDebugMessenger();

	  private:
		static Vulkan* m_instance;
		VkInstance m_vkInstance;
		VkSurfaceKHR m_surface;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkSwapchainKHR m_swapchain;

		VkDebugUtilsMessengerEXT m_debugMessenger;

		// Queues
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
	};
} // namespace Lynx