#include <pch.h>
#include "Logger.h"
#include "Tools.h"
#include <iostream>
#include "Time.h"

#if PL_WINDOWS
#include <Windows.h>
#endif

static std::ofstream logFile;

void writeColor(const std::string& msg, int color)
{
#if PL_WINDOWS
	static HANDLE hConsole;
	if (!hConsole)
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	printf(msg.c_str());
	SetConsoleTextAttribute(hConsole, 15);
#else
	printf("\x1B[36m%s\033[0m\t\t", msg.c_str());
#endif
}


//Checks to see if the frame changes to put a divider between log calls on different frames
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
		std::to_string(Time::frameCount) + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		//Creates one logfile for each minute
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		
		Tools::GenerateFile(logfile_name, "");
		
		logFile.open(logfile_name);
		LogS("Logger", "Creating new logfile %s", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';

	writeColor(fullMsg, 2);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
}

void LogF(std::string format, ...)
{
	va_list vl;
	va_start(vl, format);

	std::string fullMsg = "(Log @ " + std::to_string(Time::frameCount) + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogS("Logger", "Creating new logfile %s", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}

	fullMsg += '\n';
	writeColor(fullMsg, 2);
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
		std::to_string(Time::frameCount) + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogS("Logger", "Creating new logfile %s", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';
	writeColor(fullMsg, 12);
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
		std::to_string(Time::frameCount) + "): " + vformat(format, vl);

	if (!logFile.is_open())
	{
		std::string logfile_name = WORKDIR + "Logs" + SLASH + Time::getDateAndTime(Time::startPoint, "%F_%H.%M") + ".log";
		Tools::GenerateFile(logfile_name, "");
		logFile.open(logfile_name);
		LogS("Logger", "Creating new logfile %s", logfile_name);
	}

	if (frame != Time::frameCount)
	{
		frame = Time::frameCount;
		std::string divider(fullMsg.size(), '-');
		divider += "\n";
		fullMsg.insert(fullMsg.begin(), divider.begin(), divider.end());
	}
	fullMsg += '\n';
	writeColor(fullMsg, 6);
	logFile.write(fullMsg.c_str(), fullMsg.size());
	logFile.flush();
	va_end(vl);
}
