#include "Tools.h"

#include <limits.h>

#include <filesystem>
#include <fstream>

#include "pch.h"

#if PL_LINUX
#include <unistd.h>
#elif PL_WINDOWS
#include <Windows.h>
#include <direct.h>
#include <shlobj_core.h>
#include <stdio.h>
#include <sys/types.h>
#endif

using namespace Math;

#if PL_LINUX
void Tools::setWorkingDir(const std::string& dir)
{
	char old_dir[PATH_MAX];
	getcwd(old_dir, PATH_MAX);
	chdir(dir.c_str());
	LogS("Tools", "Working directory changed from \"%s\" to \"%S\"", old_dir, dir);
}
#elif PL_WINDOWS
void Tools::setWorkingDir(const std::string& dir)
{
	char old_dir[250];
	_getcwd(old_dir, 250);
	_chdir(dir.c_str());
	LogS("Tools", "Working directory changed from \"%s\" to \"%S\"", old_dir, dir);
}
#endif

std::string Tools::getAppdata()
{
	// Automatically use Windows appdata or Linux home directory accordingly
#ifdef CSIDL_APPDATA
	TCHAR szPath[MAX_PATH];

	SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath));

	return std::string((char*)szPath) + "\\" + "APPNAME + \\";
#else
	GeneratePath("~/." + std::string(APPNAME));
	return "~/." + std::string(APPNAME);
#endif
}

std::string Tools::Capitalize(const std::string& str)
{
	std::string result(str.size(), ' ');
	for (size_t i = 0; i < str.size(); i++)
	{
		result[i] = toupper(str[i]);
	}
	return result;
}

std::string Tools::Uncapitalize(const std::string& str)
{
	std::string result(str.size(), ' ');
	for (size_t i = 0; i < str.size(); i++)
	{
		result[i] = tolower(str[i]);
	}
	return result;
}

std::string Tools::Title(const std::string& str)
{
	std::string result = str;
	result[0] = toupper(str[0]);
	return result;
}

std::vector<size_t> Tools::strFind(const std::string& str, const std::string& keyW)
{
	std::vector<size_t> results;

	for (size_t i = 0; i < str.size() - (keyW.size() - 1); i++)
	{
		if (str.substr(i, keyW.size()) == keyW)
		{
			results.push_back(i);
		}
	}
	return results;
}

std::vector<size_t> Tools::strFind(const std::string& str, char c)
{
	std::vector<size_t> results;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
		{
			results.push_back(i);
		}
	}
	return results;
}

std::vector<std::string> Tools::strSplit(const std::string& str, const std::string& keyW, bool ignore_quotes)
{
	std::vector<std::string> results;
	bool in_quote = false;
	int c = 0;
	for (size_t i = 0, c = 0; i < str.size(); i++)
	{
		// Checks if current part is in an opening or closing quote that is not
		// escaped
		if (str[i] == '"' && !(i > 0 && str[i - 1] == '\\'))
			in_quote = !in_quote;

		if (str.substr(i, keyW.size()) == keyW && !(in_quote && ignore_quotes)) // Cursor att keyword
		{
			results.push_back(str.substr(c, i)); // Push left bit to results
			c = i + 1;							 // Forward the left iterator to what i was
			i = 0;
		}
	}
	if (c < str.size())
		results.push_back(str.substr(c));
	return results;
}

std::vector<std::string> Tools::strSplit(const std::string& str, char keyW, bool ignore_quotes)
{
	std::vector<std::string> results;
	bool in_quote = false;
	int c = 0;
	for (size_t i = 0, c = 0; i < str.size(); i++)
	{
		// Checks if current part is in an opening or closing quote that is not
		// escaped
		if (str[i] == '"' && !(i > 0 && str[i - 1] == '\\'))
			in_quote = !in_quote;

		if (str[i] == keyW && !(in_quote && ignore_quotes)) // Cursor att keyword
		{
			results.push_back(str.substr(c, i)); // Push left bit to results
			c = i + 1;							 // Forward the left iterator to what i was
			i = 0;
		}
	}
	if (c < str.size())
		results.push_back(str.substr(c));
	return results;
}

std::string Tools::strClamp(const std::string& str, size_t size) { return str.substr(0, size); }

std::string Tools::strStop(const std::string& str, std::string keyW) { return str.substr(str.find_first_of(keyW)); }

std::string Tools::strPurge(const std::string& str, const std::string& keyW)
{
	std::string result;
	// Left part iterator
	size_t c = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str.substr(i, keyW.size()) == keyW) // Adding left part of string
		{
			result += str.substr(c, i - c);

			// Cathing up with left iterator
			c = i + 1;
		}
	}
	return result + str.substr(c);
}

std::string Tools::strPurge(const std::string& str, char chr)
{
	std::string result;
	// Left part iterator
	size_t c = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == chr) // Adding left part of string
		{
			result += str.substr(c, i - c);

			// Cathing up with left iterator
			c = i + 1;
		}
	}
	return result + str.substr(c);
}

std::string Tools::strPurgeAll(const std::string& str, const std::string& pattern)
{
	std::string result;
	// Left part iterator
	size_t c = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		for (size_t j = 0; j < pattern.size(); j++)
		{
			if (str[i] == pattern[j])
			{
				result += str.substr(c, i - c);

				// Cathing up with left iterator
				c = i + 1;
				break;
			}
		}
	}
	return result + str.substr(c);
}

std::string Tools::strPadLeft(const std::string& str, size_t size, char paddingChar)
{
	std::string result;
	result.insert(0, size - str.size(), paddingChar);
	return result + str;
}

std::string Tools::strPadRight(const std::string& str, size_t size, char paddingChar)
{
	std::string result = str;
	result.insert(result.size() - 1, size - str.size(), paddingChar);
	return result;
}

std::string Tools::ListTostring(float* list, size_t size, const std::string& separator)
{
	std::string result;
	for (size_t i = 0; i < size; i++)
	{
		result += STR((list[i]));
		if (i != size - 1) // Putting carriage return on all entries except the last
			result += separator;
	}
	return result;
}

std::string Tools::ListTostring(float* list, size_t size, char separator)
{
	std::string result;
	for (size_t i = 0; i < size; i++)
	{
		result += STR(list[i]);
		if (i != size - 1) // Putting carriage return on all entries except the last
			result += separator;
	}
	return result;
}

std::string Tools::ListTostring(const std::vector<std::string>& list, const std::string& separator)
{
	std::string result;
	for (size_t i = 0; i < list.size(); i++)
	{
		result += (list[i]);
		if (i != list.size() - 1) // Putting carriage return on all entries except the last
			result += separator;
	}
	return result;
}

std::string Tools::ListTostring(const std::vector<std::string>& list, char separator)
{
	std::string result;
	for (size_t i = 0; i < list.size(); i++)
	{
		result += (list[i]);
		if (i != list.size() - 1) // Putting carriage return on all entries except the last
			result += separator;
	}
	return result;
}

int Tools::ParseTime(const std::string& str)
{
	int seconds = 0;

	std::vector<std::string> parts = strSplit(Uncapitalize(str), " ");

	for (size_t i = 1; i < parts.size(); i++)
	{
		// Removes plural 's'
		if (parts[i].back() == 's')
			parts[i].pop_back();

		if (parts[i] == "second")
		{
			seconds += numi(parts[i - 1]);
		}

		else if (parts[i] == "minute")
		{
			seconds += numi(parts[i - 1]) * 60;
		}

		else if (parts[i] == "hour")
		{
			seconds += numi(parts[i - 1]) * 3600;
		}

		else if (parts[i] == "day")
		{
			seconds += numi(parts[i - 1]) * 86400;
		}
	}
	return seconds;
}

std::string Tools::FormatTime(int seconds)
{
	int times[4] = {0, 0, 0, 0}; // Days, Hours, Minutes, Seconds

	const std::string timesDef[] = {"day", "hour", "minute", "second"};

	times[0] = seconds / 86400;
	seconds = seconds % 86400;

	times[1] = seconds / 3600;
	seconds = seconds % 3600;

	times[2] = seconds / 60;
	seconds = seconds % 60;

	times[3] = seconds;

	std::string result;

	// Indicates whetger the gor loop has yet encountered a nonzero time value
	bool beginned = false;
	for (size_t i = 0; i < 4; i++)
	{
		if (times[i] > 0)
			beginned = true;

		result += (times[i] > 0 ? std::to_string(times[i]) + " " + timesDef[i] : "") + (times[i] > 1 ? "s" : "");
		if (beginned && i < 3 && times[i + 1] > 0) // Not last filled
			result += ", ";
	}

	return result;
}

std::string Tools::FormatSeconds(float seconds)
{
	if (seconds > 0.1)
		return std::to_string(seconds) + "s";
	else if (seconds > 0.0001)
		return std::to_string(seconds * 1000) + "ms";
	else if (seconds > 0.0000001)
		return std::to_string(seconds * 1000000) + "us";
	else
		return std::to_string(seconds * 1000000000) + "ns";
}

bool Tools::Contains(std::vector<std::string> list, const std::string& item)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i] == item)
			return true;
	}
	return false;
}

std::string Tools::digits(int value, size_t nDigits)
{
	std::string result = std::to_string(value);
	if (result.size() < nDigits)
	{
		result.insert(0, nDigits - result.size(), '0');
	}
	else if (result.size() > nDigits)
	{
		result = result.substr(0, nDigits);
	}
	return result;
}

std::vector<std::string> Tools::ListDir(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::regular)
			r.push_back(p.path().string());
		else if (p.status().type() == std::filesystem::file_type::directory)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

// Will list all sub-directories in specified directory
std::vector<std::string> Tools::ListDirectories(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::directory)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

std::vector<std::string> Tools::ListFiles(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::regular)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

std::vector<std::string> Tools::ListAllFiles(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::regular)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

std::vector<std::string> Tools::ListAllDirectories(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::directory)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

std::vector<std::string> Tools::ListAll(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(directory))
		if (p.status().type() == std::filesystem::file_type::regular)
			r.push_back(p.path().string());
		else if (p.status().type() == std::filesystem::file_type::directory)
		{
#if PL_LINUX
			r.push_back(p.path().string());
#elif PL_WINDOWS
			std::string path = p.path().string();
			std::replace(path.begin(), path.end(), '\\', '/');
			r.push_back(path);
#endif
		}
	return r;
}

std::string Tools::FindFile(const std::string& file, const std::string& directory)
{
	std::vector<std::string> files = ListAllFiles(directory);

	for (std::string& curr_file : files)
	{
		if (curr_file.size() < file.size())
			continue;

		// If the filename and the paths leding up to the file matches
		if (curr_file.substr(curr_file.size() - file.size()) == file)
			return file;
	}
	LogW("FindFile", "No file found with name: %S", file);

	return "";
}

std::string Tools::ReadFile(const std::string& filepath, bool create)
{
	if (create)
		GenerateFile(filepath, "");

	std::ifstream file(filepath);
	std::string tmp, file_cont = "";
	if (file.is_open())
		while (std::getline(file, tmp))
		{
			file_cont += tmp;
		}
	else
		LogW("Unable to open file: %S", ShortenString(filepath, 35));

	file.close();

	return file_cont;
}

std::vector<std::string> Tools::ReadFileLines(const std::string& filepath, bool create)
{
	if (create)
		GenerateFile(filepath, "");

	std::ifstream file(filepath);
	std::string tmp;
	std::vector<std::string> file_cont;
	if (file.is_open())
		while (std::getline(file, tmp))
		{
			file_cont.push_back(tmp);
		}
	else
		LogW("Unable to open file: %S", ShortenString(filepath, 35));

	file.close();

	return file_cont;
}

void Tools::GeneratePath(const std::string& path)
{
	// path is to long
	if (path.size() >= 248)
	{
		LogE("Tools", "Couldn't generate directory; path is too long");
		return;
	}

	std::filesystem::create_directories(path);
}

void Tools::GenerateFile(const std::string& path, const std::string& contents, bool append)
{
	// Path is to long
	if (path.size() >= 248)
	{
		LogE("Tools", "Couldn't generate file; path is too long");
		return;
	}

	std::filesystem::create_directories(path.substr(0, path.find_last_of(SLASH)));

	// Creates the file at the end and pushing optional data into it
	std::ofstream fstream(path, (append ? std::ios::app : std::ios::trunc));
	fstream.write(contents.c_str(), contents.size());
	fstream.close();
}

bool Tools::Copy(const std::string& oldPath, const std::string& newPath)
{
	if (IsFile(oldPath))
	{
		std::ifstream oldFile(oldPath, std::ios::binary);
		std::ofstream newFile(newPath, std::ios::binary);
		if (!oldFile.is_open())
		{
			LogS("CopyFile", "Couldn't open file: %S", oldPath);
			return true;
		}
		newFile << oldFile.rdbuf();
		oldFile.close();
		newFile.close();
	}
	else // Copying entire directories
	{
		// Retrieves all subdirs in oldPath recursively
		std::vector<std::string> dirs = ListAllDirectories(oldPath);
		std::vector<std::string> files = ListAllFiles(oldPath);

		// Copies the directory structure
		for (std::string& dir : dirs)
			// Cuts off parent path and adds new parent path
			GeneratePath(strLead(newPath, SLASH) + dir.substr(oldPath.size()));

		for (std::string& file : files)
			Copy(file, strLead(newPath, SLASH) + file.substr(oldPath.size()));
	}
	return true;
}

bool Tools::Rename(const std::string& oldPath, const std::string& newPath)
{
	return std::rename(oldPath.c_str(), newPath.c_str());
}

std::string Tools::getExtension(const std::string& path)
{
	size_t dotIndex = path.find_last_of(".");
	return path.substr(dotIndex == std::string::npos ? path.size() : dotIndex);
}

std::string Tools::getFilename(const std::string& path, bool keepExtension)
{
	size_t slashIndex = path.find_last_of(SLASH);
	return path.substr(slashIndex == std::string::npos ? 0 : slashIndex + 1,
					   keepExtension ? path.size() : path.find_last_of(".") - slashIndex - 1);
}

std::string Tools::getPath(const std::string& path) { return path.substr(0, path.find_last_of(SLASH) + 1); }

std::string Tools::ShortenPath(const std::string& path, int depth, bool omitIndicator)
{
	std::vector<size_t> pos = strFind(path, SLASH);
	if (depth >= pos.size())
		return path;
	return (omitIndicator ? "" : "...") + path.substr(pos[pos.size() - depth]);
}

std::string Tools::ShortenString(const std::string& str, size_t size, bool omitIndicator)
{
	// Making space for "..."
	size -= 3;
	size_t start = (str.size() - size);
	if (start > 0)
		return (omitIndicator ? "" : "...") + str.substr(start);
	return str;
}

std::string Tools::DirUp(const std::string& path, size_t steps)
{
	std::string text = getPath(path);
	std::vector<size_t> folders = strFind(text, SLASH);

	size_t lastFolder = *(folders.end() - steps - 1);

	// Edge case for relative path
	if (text == CURR_DIR)
		return PREV_DIR;

	// There are no folder names; only ../../
	if (text.find_first_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos)
		return "../" + text;

	return strLead(text.substr(0, lastFolder), SLASH);
}

std::string vformat(std::string format, va_list vl)
{
	enum class Flag
	{
		None,
		Long
	};
	std::string result;
	Flag flag = Flag::None;
	for (size_t i = 0; i < format.size(); i += 2)
	{
		std::string a;
		// Is a two wide substr of fmt
		if (format[i] == '%' && !(i > 0 && format[i - 1] == SLASH) || flag != Flag::None) // Format expected
			switch (format[i + 1])														  // Checks next
			{
			case 'd': // Signed decimal integer
				result += std::to_string(flag == Flag::None ? va_arg(vl, long int) : va_arg(vl, int));
				break;

			case 'i': // Signed decimal integer
				result += std::to_string(flag == Flag::None ? va_arg(vl, long int) : va_arg(vl, int));
				break;

			case 'u': // Unsigned decimal integer
				result += std::to_string(flag == Flag::None ? va_arg(vl, unsigned long int) : va_arg(vl, unsigned int));
				break;
			case 't': // size_t
				result += std::to_string(va_arg(vl, size_t));
				break;
			case 'v':
				switch (format[i + 2])
				{
				case '2':
					result += va_arg(vl, Vector2).str();
					break;
				case '3':
					result += va_arg(vl, Vector3).str();
					break;
				case '4':
					result += va_arg(vl, Vector4).str();
					break;
				case 'n':
					result += va_arg(vl, Vector).str();
					break;
				default:
					break;
				}
				i++; // Skipping vector size indicator
				break;
			case 'V':
				switch (format[i + 2])
				{
				case '2':
					result += va_arg(vl, Vector2).str_d();
					break;
				case '3':
					result += va_arg(vl, Vector3).str_d();
					break;
				case '4':
					result += va_arg(vl, Vector4).str_d();
					break;
				default:
					result += va_arg(vl, Vector).str_d();
					break;
				}
				break;
			case 'm':
				switch (format[i + 2])
				{
				case 4:
					result += va_arg(vl, Matrix4).str();
				default:
					result += va_arg(vl, Matrix).str();
					break;
				}
				break;
			case 'M':
				switch (format[i + 2])
				{
				case 4:
					result += va_arg(vl, Matrix4).str();
				default:
					result += va_arg(vl, Matrix).str();
					break;
				}
			case 'o': // Unsigned octal
				result += Math::ToOctal(flag == Flag::None ? va_arg(vl, unsigned long int) : va_arg(vl, unsigned int));
				break;

			case 'x': // Unsigned hexadecimal integer (lowercase)
				result +=
					Math::ToHex(flag == Flag::None ? va_arg(vl, unsigned long int) : va_arg(vl, unsigned int), false);
				break;
			case 'X': // Unsigned hexadecimal integer (uppercase)
				result +=
					Math::ToHex(flag == Flag::None ? va_arg(vl, unsigned long int) : va_arg(vl, unsigned int), true);
				break;
			case 'f': // Decimal double (lowercase)
				result += std::to_string(va_arg(vl, double));
				break;
			case 'F': // Decimal double (uppercase)
				result += std::to_string(va_arg(vl, double));
				break;
			case 'b':
				result += (va_arg(vl, int) ? "true" : "false");
				break;
			case 'e': // Scientific notation lowercase
			{
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%e", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'E': // Scientific notation uppercase
			{
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%E", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'g': {
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%g", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'G': {
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%G", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'a': {
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%a", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'A': {
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%A", va_arg(vl, double));
				result.append(buffer);
				break;
			}
			case 'c': // Character
				result += va_arg(vl, int);
			case 's': // C String
			{
				char* tmp = va_arg(vl, char*);
				result += (tmp ? tmp : "(null)");
				break;
			}
			case 'S': // C++ std::string
				result += va_arg(vl, std::string);
				break;
			case 'p': {
				char buffer[max_loglength];
				snprintf(buffer, max_loglength, "%p", va_arg(vl, void*));
				result.append(buffer);
				break;
			}
			case '%': // String
				result += "%";
				break;
			default:
				i--;
				break;
			}

		else
		{
			result += format[i];
			i--;
		}
	}
	return result;
}

std::string format(std::string format, ...)
{
	va_list vl;
	va_start(vl, format);

	return vformat(format, vl);
}