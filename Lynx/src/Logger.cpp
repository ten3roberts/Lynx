#include "pch.h"
#include "Logger.h"
#include <iostream>

#if PL_WINDOWS
#include <Windows.h>
#endif

static std::ofstream logFile;
#if PL_LINUX
#define CONSOLE_WHITE "\u001b[37m"
#define CONSOLE_GREEN "\u001b[32m"
#define CONSOLE_YELLOW "\u001b[33m"
#define CONSOLE_RED "\u001b[31m"
#elif PL_WINDOWS
#define CONSOLE_WHITE 15
#define CONSOLE_GREEN 2
#define CONSOLE_YELLOW 6
#define CONSOLE_RED 12
#endif

#if PL_LINUX
void writeColor(const std::string& msg, const char* color_code)
{
	printf("%s%s\u001b[0m", color_code, msg.c_str());
}
#elif PL_WINDOWS
void writeColor(const std::string& msg, int color)
{
	static HANDLE hConsole;
	if (!hConsole)
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	printf(msg.c_str());
	SetConsoleTextAttribute(hConsole, 15);
}
#endif

#define TIME_STAMP Time::getDateAndTime(Time::startPoint, "%H.%M")

// Checks to see if the frame changes to put a divider between log calls on different frames
static int frame;
void LogS(const std::string& author, std::string format, ...)
{
	enum Flag
	{
		None, Long
	};

	va_list vl;
	va_start(vl, format);

	std::string fullMsg = '(' + (author == "" ? "Log" : author) + " @ " +
		TIME_STAMP + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		// Creates one logfile for each minute
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		
		Tools::GenerateFile(logfile_name, "");
		
		logFile.open(logfile_name);
		LogW("Logger", "Creating new logfile %S", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';

	writeColor(fullMsg, CONSOLE_GREEN);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
}

void LogF(std::string format, ...)
{
	va_list vl;
	va_start(vl, format);

	std::string fullMsg = "(Log @ " + TIME_STAMP + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogW("Logger", "Creating new logfile %S", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}

	fullMsg += '\n';
	writeColor(fullMsg, CONSOLE_GREEN);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
}

void LogE(const std::string& author, std::string format, ...)
{
	enum Flag
	{
		None, Long
	};

	va_list vl;
	va_start(vl, format);

	std::string fullMsg = '(' + (author == "" ? "Log" : author) + " @ " +
		TIME_STAMP + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogW("Logger", "Creating new logfile %S", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';
	writeColor(fullMsg, CONSOLE_RED);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
	#if ERROR_DELAY
		SLEEPFOR(ERROR_DELAY);
	#endif
}

void LogW(const std::string& author, std::string format, ...)
{
	enum Flag
	{
		None, Long
	};

	va_list vl;
	va_start(vl, format);

	std::string fullMsg = '(' + (author == "" ? "Log" : author) + " @ " +
		TIME_STAMP + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogW("Logger", "Creating new logfile %S", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';
	writeColor(fullMsg, CONSOLE_YELLOW);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
}
