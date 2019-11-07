-- premake5.lua
workspace "Lynx"
	-- Only x64 architecture is verifiably supported
	architecture "x64"
	configurations { "Debug", "Release"}
	startproject "Sandbox"
	
-- variable is required for GLFW's premake5 file
outputdir = ""

IncludeDir = {}
IncludeDir["GLFW"] = "Lynx/vendor/glfw/include"

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
	files {"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	-- Adds compiler include directories for Lynx and GLFW
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}
	
	-- Links GLFW and opengl32 to the Lynx
	links
	{
		"GLFW"
	}
	
	-- Specifies GCC options
	configuration {"linux", "gmake2"}
		buildoptions{"-std=c++17", "-pthread"}
	
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
	
	-- Specifies Windows and MSVC specific options and preprocessor definitions
	filter "system:windows"
		defines { "PL_WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "LX_EXPORT"}
		staticruntime "off"
		systemversion "latest"
		links "opengl32.lib"
	
	-- Specifies Linux specific preprocessor definitions
	filter "system:linux"
		defines{ "PL_LINUX=1" }
		links "GL"
	
	
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
		"%{IncludeDir.GLFW}"
	}
	
	-- Links the Lynx DLL to Sandbox - GLFW are statically linked to Lynx
	links("Lynx")
	
	-- Specifies GCC options
	configuration {"linux", "gmake2"}
		buildoptions{"-std=c++17", "-pthread"}
		
	-- Specifies debug symbols for different configurations
	filter "configurations:Debug"
		defines {"DEBUG=1", "RELEASE=0", "ERROR_DELAY=1"}
		symbols "on"
		
	filter "configurations:Release"
		defines {"DEBUG=0", "RELEASE=1", "ERROR_DELAY=0"}
		optimize "on"
		
	-- Specifies Windows and MSVC specific options and preprocessor definitions
	filter "system:windows"
		defines { "PL_WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "LX_IMPORT"}
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
		
	-- Specifies Linux specific preprocessor definitions
	filter "system:linux"
		defines{ "PL_LINUX=1" }