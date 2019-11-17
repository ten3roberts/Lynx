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

		static Renderer* get()
		{
			if (!m_instance)
				m_instance = new Renderer;
			return m_instance;
		}

	  private:
		bool CreateInstance();

	  private:
		static Renderer* m_instance;
		VkInstance m_vkInstance;
	};
} // namespace Lynx