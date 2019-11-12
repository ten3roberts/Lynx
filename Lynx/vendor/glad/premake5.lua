project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin")
	objdir ("obj")

	files
	{
		"include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
	}
	
	includedirs
    {
        "include"
    }	
		

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
	filter "system:windows"
		systemversion "latest"
		
	filter "system:linux"
		defines{ "PL_LINUX=1" }
		buildoptions{"-fPIC"}
		links "GL"
