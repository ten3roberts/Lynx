-- premake5.lua
workspace "Lynx"
   configurations { "Debug", "Release" }

project "Lynx"
   kind "SharedLib"
   language "C++"
   targetdir "bin"

   files {"Lynx/**.h", "Lynx/**.cpp"}
      
   includedirs("Lynx")

   configuration {"linux", "gmake2"}
       buildoptions{"-std=c++17"}
       
   filter "configurations:Debug"
       defines {"DEBUG", "COMPILE_DLL"}
       flags {"Symbols"}
       
   filter "configurations:Release"
       defines {"NDEBUG", "COMPILE_DLL"}
       optimize "On"
    defines{"LX_EXPORT"}

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    files { "Sandbox/**.h", "Sandbox/**.cpp" }

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
        defines { "PL_WINDOWS=1" }

    filter "system:linux"
        defines{ "PL_LINUX=1" }

    defines{"LX_IMPORT"}