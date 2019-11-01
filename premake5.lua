-- premake5.lua
workspace "Lynx"
   configurations { "Debug", "Release" }

project "Lynx"
   kind "SharedLib"
   language "C++"
   targetdir "bin"
   
   pchheader "pch.h"
   pchsource "Lynx/pch.cpp"

   files {"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
      
   includedirs("Lynx")

   configuration {"linux", "gmake2"}
       buildoptions{"-std=c++17"}
       
   filter "configurations:Debug"
       defines {"DEBUG", "COMPILE_DLL"}
       flags {"Symbols"}
       
   filter "configurations:Release"
       defines {"NDEBUG", "COMPILE_DLL"}
       optimize "On"

    filter "system:windows"
        defines { "PL_WINDOWS=1", "LX_EXPORT" }
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "system:linux"
        defines{ "PL_LINUX=1" }


project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    links("Lynx")

    includedirs("Lynx", "Sandbox")

    configuration {"linux", "gmake2"}
		buildoptions{"-std=c++17", "-pthread"}

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    
    filter "system:windows"
      defines { "PL_WINDOWS=1", "LX_IMPORT"}
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"

    filter "system:linux"
      defines{ "PL_LINUX=1" }