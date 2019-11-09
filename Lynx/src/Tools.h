#pragma once
#include <pch.h>

// Shortcuts
// #define Util Tools

// Macro definitions
#define WORKDIR CURR_DIR
#define ASSETS "./Assets" + SLASH

#define APPDATA getAppdata()

// Normal defines
#define ENABLE_CONSOLE true 
#define INVALID_ERROR -1
#define APPEND_CODE -2

std::string format(std::string format, ...);
std::string vformat(std::string format, va_list vl);

namespace Tools
{
	// Sets the working directory, I.e; "./"
	void LYNX_API setWorkingDir(const std::string& dir);

	std::string LYNX_API getAppdata();

#pragma region "string utilities"
	std::string LYNX_API Capitalize(const std::string& str);

	std::string LYNX_API Uncapitalize(const std::string& str);

	std::string LYNX_API Title(const std::string& str);

	// Will return a list of all indices of keyW in str
	std::vector<size_t> LYNX_API strFind(const std::string& str, const std::string& keyW);

	// Will return a list of all indices of c
	std::vector<size_t> LYNX_API strFind(const std::string& str, char c);

	// Will divide the string at every keyW(default space)
	std::vector<std::string> LYNX_API strSplit(const std::string& str, const std::string& keyW, bool ignore_quotes = false);
	std::vector<std::string> LYNX_API strSplit(const std::string& str, char keyW, bool ignore_quotes = false);

	std::string LYNX_API strClamp(const std::string& str, size_t size);

	// Will return a string to the keyW
	std::string LYNX_API strStop(const std::string& str, std::string keyW);

	std::string LYNX_API strPurge(const std::string& str, const std::string& keyW);
	std::string LYNX_API strPurge(const std::string& str, char chr);

	// Removes all characters from str that exist in pattern
	std::string LYNX_API strPurgeAll(const std::string& str, const std::string& pattern);

	// Will add $lead to string if it doesn't already end with $lead. Good for trailing slashes
	inline std::string LYNX_API strLead(const std::string& str, char lead)
	{
		if (str.back() == lead)
			return str;
		return str + lead;
	}

	// Will add $lead to string if it doesn't already end with $lead. Good for trailing slashes
	inline std::string LYNX_API strLead(const std::string& str, const std::string& lead)
	{
		if (lead.size() <= str.size() && str.substr(str.size() - lead.size()) == lead)
			return str;
		return str + lead;
	}

	// Pads a string to a constant size by inserting characters to the left
	inline std::string LYNX_API strPadLeft(const std::string& str, size_t size, char paddingChar = ' ');
	// Pads a string to a constant size by inserting characters to the right
	inline std::string LYNX_API strPadRight(const std::string& str, size_t size, char paddingChar = ' ');

	// Will return a string vector of all folder in a specified directory
	std::string LYNX_API ListTostring(float* list, size_t size, const std::string& separator = ", ");
	std::string LYNX_API ListTostring(float* list, size_t size, char separator);


	std::string LYNX_API ListTostring(const std::vector<std::string>& list, const std::string& separator = ", ");
	std::string LYNX_API ListTostring(const std::vector<std::string>& list, char separator);
	int LYNX_API ParseTime(const std::string& str);

	std::string LYNX_API FormatTime(int seconds);

	// Will format seconds into either seconds, milliseconds or nanoseconds
	std::string LYNX_API FormatSeconds(float seconds);

	bool LYNX_API Contains(std::vector<std::string> list, const std::string& item);

	// Returns true if $item occurs in $list
	template <typename T>
	bool in(T item, std::vector<T> list);

	template <typename N>
	std::vector<int> Search(std::vector<N> list, N query);

	std::string LYNX_API digits(int value, size_t nDigits);
#pragma endregion
#pragma region "File Utilities"
	// Will return true if the given path is a file and return false if the given path is a directory
	inline bool LYNX_API IsFile(const std::string& path) { return std::filesystem::is_directory(path); }
	// Will return false if the given path is a file and return true if the given path is a directory
	inline bool LYNX_API IsDir(const std::string& path) { return std::filesystem::is_regular_file(path); }

	// Will list all files with full path and sub-directories in specified directory
	std::vector<std::string> LYNX_API ListDir(const std::string& directory = ASSETS);


	std::vector<std::string> LYNX_API ListDirectories(const std::string& directory = ASSETS);


	// Will return a string vector of all files with full path in a specified directory	
	std::vector<std::string> LYNX_API ListFiles(const std::string& directory = ASSETS);

	// Will return a string vector of all files with full path in a specified directory including all sub directories
	std::vector<std::string> LYNX_API ListAllFiles(const std::string& directory = ASSETS);
	// Will return a string vector of all sub directories recursively with full path
	std::vector<std::string> LYNX_API ListAllDirectories(const std::string& directory = ASSETS);

	// Will return a string vector of all directories and files recursively with full path
	std::vector<std::string> LYNX_API ListAll(const std::string& directory = ASSETS);


	// Will go through all files in the directory and all of it's subfolder searching for a specified file and return the path for it
	std::string LYNX_API FindFile(const std::string& filename, const std::string& directory = ASSETS);
	// Will go through all files in the directory and all of it's subfolder searching for a specified file and return the path for it optionally ignore extension
	std::string LYNX_API FindFile(const std::string& filename, bool useExtension, const std::string& directory = ASSETS);


	// Will return the file as a string
	std::string LYNX_API ReadFile(const std::string& filePath, bool create = false);

	// Will return the file as a string vector with each element being a separate line
	std::vector<std::string> LYNX_API ReadFileLines(const std::string& filepath, bool create = false);


	// Will create the specified path with all directories leading to up
	void LYNX_API GeneratePath(const std::string& path);
	// Will create a file, and if append is false, it will truncate the file if it already exists
	void LYNX_API GenerateFile(const std::string& path, const std::string& contents, bool append = true);

	bool LYNX_API Copy(const std::string& oldPath, const std::string& newPath);
	bool LYNX_API Rename(const std::string& oldPath, const std::string& newPath);
	// Will return the extension of a file
	std::string LYNX_API getExtension(const std::string& path);

	// Will return the filename of a path
	std::string LYNX_API getFilename(const std::string& path, bool keepExtension = true);

	// Will return the path of folders leading up to the file with a leading '\\'
	std::string LYNX_API getPath(const std::string& path);

	// Will only display the $depth directories back
	std::string LYNX_API ShortenPath(const std::string& path, int depth = 3, bool omitIndicator = false);

	// Will strClamp the string preserving the end to a set size and add "..." to the beginning
	std::string LYNX_API ShortenString(const std::string& str, size_t size, bool omitIndicator = false);

	// Will return the file path moved up one directory
	std::string LYNX_API DirUp(const std::string& path, size_t steps = 1);
};

/*std::ostream& operator<<(std::ostream& os, std::vector<std::string> in)
{
	for (std::string& str : in)
		os << str << std::endl;;
	return os;
}
// For shortcuts in writing*/
namespace Util = Tools;

template<typename T>
inline bool Tools::in(T item, std::vector<T> list)
{
	for (T i : list)
	{
		if (i == item)
			return true;
	}
	return false;
}

template<typename N>
inline std::vector<int> Tools::Search(std::vector<N> list, N query)
{
	std::vector<N> result;
	for (N i : list)
	{
		if (i == query)
			result.push_back(i);
	}
	return result;
}

static bool parseBool(const std::string& str)
{
	return Tools::Uncapitalize(str) == "true" ? true : str == "1" ? 1 : 0;
}

static std::string FormatBool(bool boolean)
{
	return boolean ? "true" : "false";
}


inline int LYNX_API numi(const std::string& str) { return atoi(str.c_str()); }
inline float LYNX_API numf(const std::string& str) { return (float)atof(str.c_str()); }


inline float LYNX_API min(float a, float b) { return a < b ? a : b; };
// inline int LYNX_API min(int a, int b) { return a < b ? a : b; };
inline size_t LYNX_API min(size_t a, size_t b) { return a < b ? a : b; };
// inline float LYNX_API min(float a, float b) { return a < b ? a : b; };
// inline unsigned int min(unsigned int a, unsigned int b) { return a < b ? a : b; };

inline float LYNX_API max(float a, float b) { return a > b ? a : b; };
inline int LYNX_API max(int a, int b) { return a > b ? a : b; };
// inline unsigned int max(unsigned int a, unsigned int b) { return a > b ? a : b; };
