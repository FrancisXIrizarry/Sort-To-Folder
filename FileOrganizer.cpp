// FileOrganizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream> 
#include <sys/types.h>
#include <sys/stat.h>
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 // Windows 10
#define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10
#include <windows.h>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <locale.h>
using namespace std;

namespace fs = std::filesystem;

//Determine what file type 
void checkTypeFunc(string fileName, const fs::path, const string pathDir);

//Check if directory exists (Depreciated)
bool dirExists(const char *path);

//Check if path location exists 
void checkPathExists(string path);

//Attempt to create folder, if exists do nothing
bool createFolder(string OutputFolder);

//Not within expected item type (File type)
void lastResort(string fileName, const fs::path pathFile, const string pathDir);

// Convert Wide Unicode String to UTF8 String
std::string ws2s(const std::wstring& s);

// Convert a wide Unicode String to UTF8 String
std::string utf8_encode(const std::wstring &wstr);

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str);

//Add to file (To reduce redundancy)
void addToFile(string fileName, const fs::path pathFile, const string pathDir, const string folderName);

int main()
{

	wchar_t* localAppData = 0;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &localAppData);
	string path = utf8_encode(localAppData);
	cout << path << endl;
	CoTaskMemFree(static_cast<void*>(localAppData));

	checkPathExists(path);
	for (const auto & entry : fs::directory_iterator(path))
		try {
			string pathStr = entry.path().u8string();
			string reducedName = pathStr.substr(25);
			//std::cout << reducedName << std::endl;
			checkTypeFunc(reducedName, entry, path);
		}
		catch (...) {
			cerr << "\n\n\n\n Wot \n\n\n\n" << endl;
		}
    return 0;
}

void checkTypeFunc(string fileName, const fs::path pathFile, const string pathDir) {
	transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
	if (fileName.find("pdf") != string::npos && fileName != "pdffolder") {
		string folderName = "/pdfFolder/";
		addToFile(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("png") != string::npos || fileName.find("jpg") != string::npos || fileName.find("tiff") != string::npos || fileName.find("jpeg") != string::npos) { 
		
		string folderName = "/picFolder/";
		addToFile(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("mp4") != string::npos || fileName.find("mov") != string::npos || fileName.find("avi") != string::npos || fileName.find(".ts") != string::npos) {

		string folderName = "/vidFolder/";
		addToFile(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("zip") != string::npos || fileName.find("rar") != string::npos  && fileName != "zipfolder") {

		string folderName = "/zipFolder/";
		addToFile(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find(".txt") != string::npos || fileName.find(".doc") != string::npos || fileName.find(".readme") != string::npos
			|| fileName.find(".text") != string::npos&& fileName != "textfolder") {

		string folderName = "/textFolder/";
		addToFile(fileName, pathFile, pathDir, folderName);
	}
	else {
		lastResort(fileName, pathFile, pathDir);
		//if (!strstr(fileName.c_str(), "folder")) {cout << fileName << endl;}
	}

}

void lastResort(string fileName, const fs::path pathFile, const string pathDir) {
	size_t found = fileName.find_last_of(".");
	string fileType = fileName.substr(found+1);
	string folderName = "/" + fileType + "Folder";
	if (!strstr(fileName.c_str(), "folder")) {
		if (createFolder(pathDir + folderName)) {
			cout << "created folder : " << folderName << endl;
		}
		try {
			filesystem::rename(pathFile, pathDir + folderName + "/" + fileName); //"/picFolder"
		}
		catch (std::filesystem::filesystem_error& e) {
			std::cout << e.what() << '\n';
		}
	}
}

//Depreciated
bool dirExists(const char *path)
{
	struct stat info;

	if (stat(path, &info) != 0)
		return 0;
	else if (info.st_mode & S_IFDIR)
		return 1;
	else
		return 0;
}

void checkPathExists(string path)
{
	string pdfStr = path + "/pdfFolder";
	string picStr = path + "/picFolder";
	string vidStr = path + "/vidFolder";
	string zipStr = path + "/zipFolder";
	string textStr = path + "/textFolder";

	cout << pdfStr << endl;
	if (createFolder(pdfStr)) {
		cout << "Created Folder at:	" << pdfStr << endl;
	}
	if (createFolder(picStr)) {
		cout << "Created Folder at:	" << picStr << endl;
	}
	if (createFolder(vidStr)) {
		cout << "Created Folder at:	" << vidStr << endl;
	}
	if (createFolder(zipStr)) {
		cout << "Created Folder at:	" << zipStr << endl;
	}
	if (createFolder(textStr)) {
		cout << "Created Folder at:	" << zipStr << endl;
	}


}

bool createFolder(string OutputFolder) {
	if (CreateDirectoryA(OutputFolder.c_str(), NULL))
	{
		return true;
	}
	else
	{
		//ERROR_ALREADY_EXISTS == GetLastError()
		return false;
	}
}

std::string ws2s(const std::wstring& s)
{
	int slength = (int)s.length() + 1;
	int len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

std::string utf8_encode(const std::wstring &wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL); //Finds out what size is required (NULL, 0) <-- 0 informs API to figure it out
																										//Basically Null (No string to go to), 0 (Returns required buffer size for potential new string)
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL); //Type, 0(after vista to use func), (Orig string (wstring in this case), 
																									 // size of original string, pointer to buffer for new string (of type X), size required, N/A, N/A
	return strTo;
}

std::wstring utf8_decode(const std::string &str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

void addToFile(string fileName, const fs::path pathFile, const string pathDir, const string folderName) {

	cout << "FileName: \t" << fileName << endl;
	try {
		cout << pathDir + "/" + fileName << endl;
		filesystem::rename(pathFile, pathDir + folderName + fileName); //"/textFolder"
	}
	catch (std::filesystem::filesystem_error& e) {
		std::cout << e.what() << '\n';
	}
}
