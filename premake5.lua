-- premake5.lua
workspace "Lynx"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = ""

IncludeDir = {}
IncludeDir["GLFW"] = "Lynx/vendor/GLFW/include"

-- Includes the premake5 file in glfw
include "Lynx/vendor/GLFW"

project "Lynx"
	location "Lynx"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	targetdir "bin"
	pchheader "pch.h"
	pchsource "Lynx/pch.cpp"
	
	files {"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	includedirs
	{
		"%{prj.name}",
		"%{IncludeDir.GLFW}"
	}
	links
	{
		"GLFW",
		"opengl32.lib"
	}
	
	configuration {"linux", "gmake2"}
		buildoptions{"-std=c++17"}
		
	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "on"
		
	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "on"
	
	filter "system:windows"
		defines { "PL_WINDOWS=1", "LX_EXPORT"}
		buildoptions "/MDd"

	
	filter "system:linux"
		defines{ "PL_LINUX=1" }
	
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	targetdir "bin"
	
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	
	links("Lynx")
	
	includedirs("Lynx", "Sandbox")
	
	configuration {"linux", "gmake2"}
		buildoptions{"-std=c++17"}
		
	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "on"
		
	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "on"
	
	filter "system:windows"
		defines { "PL_WINDOWS=1", "LX_IMPORT"}
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		buildoptions "/MDd"
	
	filter "system:linux"
		defines{ "PL_LINUX=1" }