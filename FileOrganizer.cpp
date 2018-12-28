// FileOrganizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "WindowsVer.h"

#ifdef _WIN32 || _WIN64
#define PLATFORM_NAME  "Windows 32-bit"
#elif defined __unix || __unix__
#define PLATFORM_NAME "Unix"
#elif defined __APPLE__ || __MACH__
#define PLATFORM_NAME "Mac OSX"
#elif defined __linux__
#define PLATFORM_NAME "Linux"
#elif defined __FreeBSD__
#define PLATFORM_NAME "FreeBSD"
#else
#define PLATFORM_NAME "Other"
#endif

using namespace std;

string getSystemType() {
	return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}



int main()
{
	if (getSystemType().find("Windows") != string::npos) {
		mainWindowFunc(getSystemType());
	}
	else if (getSystemType().find("Linux") != string::npos) {

	}	
    return 0;
}
