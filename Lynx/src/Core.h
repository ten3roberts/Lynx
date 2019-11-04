#if PL_WINDOWS
#define SLASH '\\'
#define CURR_DIR ".\\"
#define PREV_DIR "..\\"
#else
#define SLASH '/'
#define CURR_DIR "./"
#define PREV_DIR "../"
#endif

#if PL_WINDOWS
	#if LX_EXPORT
		#define LYNX_API __declspec(dllexport)
	#elif LX_IMPORT
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
#include <cstdlib>

#define APPNAME "Lynx"

using namespace std::chrono_literals;
#define STR(x) std::to_string(x)
#define SLEEP(t) std::this_thread::sleep_for(t)
// Pauses the current thread for (float)x seconds
#define SLEEPFOR(s) std::this_thread::sleep_for(std::chrono::milliseconds((long long)(s*1000)))

#define BIT(x) (1 << x)

#define ASSERT(x) if (!(x)) abort();

#define BIND(func) std::bind(&func, this, std::placeholders::_1)