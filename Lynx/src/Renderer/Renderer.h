#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Lynx
{
	// Represents a singleton renderer using vulkan
	// Is global to all threads
	// Need to be explicitely initialized before using
	class Renderer
	{
	  public:
		Renderer();

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
		// Creates a Vulkan instance
		bool CreateInstance();
		// Creates a debug message callback handle
		void CreateDebugMessenger();

	  private:
		static Renderer* m_instance;
		VkInstance m_vkInstance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
	};
} // namespace Lynx