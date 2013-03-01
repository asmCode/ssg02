#include <Windows.h>

bool Path::IsFileExists(const char *fileName)
{
	if (GetFileAttributes(fileName) != INVALID_FILE_ATTRIBUTES)
		return true;
	else
		return false;
}

void Path::GetAllFiles(std::vector<std::string> &files,
					   const std::string &path,
					   const std::string &filter)
{
	WIN32_FIND_DATA fd;

	HANDLE hfile = FindFirstFile((path + filter).c_str(), &fd);
	if (hfile != INVALID_HANDLE_VALUE)
	{
		BOOL doSearch = true;
		while (doSearch)
		{
			files.push_back(fd.cFileName);
			doSearch = FindNextFile(hfile, &fd);
		}

		FindClose(hfile);
	}
}

