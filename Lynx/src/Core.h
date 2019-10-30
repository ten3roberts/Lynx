#if PL_LINUX
    #define SLASH  '/'
#elif PL_WINDOWS
    #define SLASH '\\'
#else
    #define SLASH '/'
#endif

#if PLAT_WINDOWS
    #if LX_EXPORT
        #define LYNX_API __declspec(dllexport)
    #endif
    #if LX_IMPORT
        #define LYNX_API __declspec(dllimport)
    #endif
#else
    #define LYNX_API
#endif