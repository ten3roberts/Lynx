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

		bool getComplete() { return graphicsFamily.has_value(); }
	};

	// Represents a singleton renderer using vulkan
	// Is global to all threads
	// Need to be explicitely initialized before using
	class LYNX_API Renderer
	{
	  public:
		// Initializes Vulkan and all other required components
		// Returns true on success
		bool Init();

		// Terminates and frees all graphic
		void Terminate();

		static Renderer* get()
		{
			if (!m_instance)
				m_instance = new Renderer;
			return m_instance;
		}

	  private:
		Renderer();
		// Creates a Vulkan instance
		bool CreateInstance();

		int getDeviceSuitability(VkPhysicalDevice device);

		bool CreatePhysicalDevice();

		bool CreateLogicalDevice();

		// Creats a presentable surface
		bool CreateSurface();
		

		QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
		// Creates a debug message callback handle
		void CreateDebugMessenger();


	  private:
		static Renderer* m_instance;
		VkInstance m_vkInstance;
		VkSurfaceKHR m_surface;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkDebugUtilsMessengerEXT m_debugMessenger;

		// Queues
		VkQueue m_graphicsQueue;
	};
} // namespace Lynx