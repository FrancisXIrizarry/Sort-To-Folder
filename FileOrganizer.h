// FileOrganizer.cpp : Defines the entry point for the console application.
//

#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H
#include <string>
#include <iostream>
#include <vector>
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


int mainFunc(bool permission,  string * currStringArr, int sizeOfArr)
{	
	if (permission) {
		try {
			//cout << "currStringArr:  " << currStringArr[0] << endl;
		}
		catch (exception except) {
			cout << except.what() << endl;
		}
		vector<string> currentLocations;
		
		for (int loc = 0; loc < sizeOfArr; loc++) {
			currentLocations.push_back(currStringArr[loc]);
		}
		for (int loc = 0; loc < currentLocations.size(); loc++) {
			cout << currentLocations.at(loc) << endl;
		}
		cout << getSystemType() << endl;
		if (getSystemType().find("Windows") != string::npos) {
		#ifdef _WIN32 
			mainWindowFunc(getSystemType(), currentLocations);
		#endif
		}
		else if (getSystemType().find("Unix") != string::npos) {
		#ifdef __unix 
			mainLinuxFunc(getSystemType());
		#endif
		}
	}


	
    return 0;
}

#else

#endif