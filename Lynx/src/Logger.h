#pragma once
#include "pch.h"
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdio.h>

#include <ostream>
#include <sstream>

#define max_loglength 512

// Logs a formatted message with time stamp (white)
extern void LYNX_API Log(std::string format, ...);

// Logs a formatted status message with time stamp and author/source (white)
extern void LYNX_API LogF(const std::string& author, std::string format, ...);

// Logs a formatted status message with time stamp and author/source (green)
extern void LYNX_API LogS(const std::string& author, std::string format, ...);

// /Logs a formatted warning message with time stamp and author/source (yellow)
extern void LYNX_API LogW(const std::string& author, std::string format, ...);

// Logs a formatted error message with time stamp and author/source (red)
extern void LYNX_API LogE(const std::string& author, std::string format, ...);


#define LOG(x) LogS(std::string(__FILE__), std::string(x));
