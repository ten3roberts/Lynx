#pragma once
#include <pch.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdio.h>

#include <ostream>
#include <sstream>

#define max_loglength 512

// Logs a formatted message with frame stamp and author/source
extern void LYNX_API LogS(const std::string& author, std::string format, ...);
// extern void LogS(const char* format, ...);

// Logs a formatted message
extern void LYNX_API LogF(std::string format, ...);

// Logs a formatted error message with frame stamp and author/source
extern void LYNX_API LogE(const std::string& author, std::string format, ...);
// /Logs a formatted warning message with frame stamp and author/source
extern void LYNX_API LogW(const std::string& author, std::string format, ...);

#define LOG(x) LogS(std::string(__FILE__), std::string(x));
