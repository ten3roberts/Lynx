#if PL_LINUX
    #define SLASH  '/'
#elif PL_WINDOWS
    #define SLASH '\\'
#else
    #define SLASH '/'
#endif