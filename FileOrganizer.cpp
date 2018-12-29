// FileOrganizer.cpp : Defines the entry point for the console application.
//


#include <string>
#include <iostream>
#include "WindowsVer.h"
#include "LinuxVer.h"

#ifdef _WIN32
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

    cout << getSystemType() << endl;
	if (getSystemType().find("Windows") != string::npos) {
        #ifdef _WIN32 
		mainWindowFunc(getSystemType());
        #endif
	}
	else if (getSystemType().find("Unix") != string::npos) {
        #ifdef __unix 
		mainLinuxFunc(getSystemType());
        #endif
	}


	
    return 0;
}

