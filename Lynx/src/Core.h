#if PL_LINUX
#define SLASH  '/'
#elif PL_WINDOWS
#define SLASH '\\'
#else
#define SLASH '/'
#endif

#if PL_WINDOWS
#if LX_EXPORT
#define LYNX_API __declspec(dllexport)
#else
#define LYNX_API __declspec(dllimport)
#endif
#else
#define LYNX_API
#endif

#if PL_WINDOWS
	#define ASSERT __debugbreak();
#endif

#include <thread>
#include <chrono>

#define APPNAME "Lynx"

using namespace std::chrono_literals;
#define STR(x) std::to_string(x)
#define SLEEP(t) std::this_thread::sleep_for(t)
#define SLEEPFOR(s) std::this_thread::sleep_for(std::chrono::milliseconds((long long)(s*1000)))