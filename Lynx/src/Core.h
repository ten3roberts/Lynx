#if PL_LINUX
    #define SLASH  '/'
#elif PL_WINDOWS
    #define SLASH '\\'
#else
    #define SLASH '/'
#endif
#define PLAT_WINDOWS 1
#if PLAT_WINDOWS
    #if LX_EXPORT
        #define LYNX_API __declspec(dllexport)
    #else
        #define LYNX_API __declspec(dllimport)
    #endif
#else
    #define LYNX_API
#endif

#include <thread>
#include <chrono>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::seconds(x));