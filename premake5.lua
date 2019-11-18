-- premake5.lua
workspace "Lynx"
	-- Only x64 architecture is verifiably supported
	architecture "x64"
	configurations { "Debug", "Release"}
	startproject "Sandbox"
	
-- variable is required for GLFW's premake5 file
outputdir = ""

includeDir = {}
includeDir["glfw"] = "Lynx/vendor/glfw/include"

-- Includes the premake5 file from glfw
include "Lynx/vendor/glfw"

project "Lynx"
	-- Sets type, language, and output directory for binaries and intermediates
	objdir "obj/%{prj.name}"
	location "Lynx"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin"
	
	-- Sets the working directory to bin when using integrated debugger
	-- Determines where files are read and written to when using debuggers
	debugdir "bin"
	
	-- Precompiled headers
	pchheader "pch.h"
	pchsource "Lynx/src/pch.cpp"
	
	-- Adds all files inside Lynx recursively to project
	files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}
	
	-- Adds compiler include directories for Lynx and GLFW
	includedirs
	{
		"%{prj.name}/src",
		"%{includeDir.glfw}"
	}
	
	-- Links GLFW and opengl32 to the Lynx
	links
	{
		"GLFW"
	}
	
	-- Specifies GCC options and Linux specific options
	filter "system:linux"
		buildoptions {"-std=c++17", "-pthread", "-fPIC"}
		--linkoptions {"-lvulkan"}
		defines{ "PL_LINUX=1" }
		links { "GL", "vulkan"}
	
	-- Specifies Windows and MSVC specific options and preprocessor definitions
	filter "system:windows"
		defines { "PL_WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "LX_EXPORT"}
		staticruntime "off"
		systemversion "latest"
		links "opengl32.lib"
		-- Vulkan
		includedirs "C:/VulkanSDK/1.1.126.0/Include"
		links 		"C:/VulkanSDK/1.1.126.0/Lib/vulkan-1.lib"
	
	-- Specifies options for different configurations
	-- Debug includes debug symbols and disables optimization
	filter "configurations:Debug"
		defines {"DEBUG=1", "RELEASE=0", "ERROR_DELAY=1"}
		optimize "off"
		symbols "on"
	
	-- Release does not include debug symbols and enables optimization
	filter "configurations:Release"
		defines {"DEBUG=0", "RELEASE=1", "ERROR_DELAY=0"}
		optimize "on"
		symbols "off"
	

	
	
project "Sandbox"
	-- Sets type, language, and output directory for binaries and intermediates
	objdir "obj/%{prj.name}"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin"
	
	-- Sets the working directory to bin when using integrated debugger
	-- Determines where files are read/write to when using IDE debuggers
	debugdir "bin"
	
	files { "%{prj.name}/**.h", "%{prj.name}/**.cpp" }
	
	-- Adds compiler include directories for Lynx and GLFW
	includedirs
	{
		"Lynx/src",
		"%{prj.name}/src",
		"%{includeDir.glfw}"
	}
	
	-- Links the Lynx DLL to Sandbox - GLFW are statically linked to Lynx
	links("Lynx")
	
	-- Specifies GCC options and Linux specific options
	filter "system:linux"
		buildoptions {"-std=c++17", "-pthread", "-fPIC"}
		defines{ "PL_LINUX=1" }
		links "GL"
	
	-- Specifies Windows and MSVC specific options and preprocessor definitions
	filter "system:windows"
		defines { "PL_WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "LX_EXPORT"}
		staticruntime "off"
		systemversion "latest"
		
	-- Specifies debug symbols for different configurations
	filter "configurations:Debug"
		defines {"DEBUG=1", "RELEASE=0", "ERROR_DELAY=1"}
		symbols "on"
		
	filter "configurations:Release"
		defines {"DEBUG=0", "RELEASE=1", "ERROR_DELAY=0"}
		optimize "on"