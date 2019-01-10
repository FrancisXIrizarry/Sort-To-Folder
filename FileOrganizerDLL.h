#pragma once

#ifdef FILEORGANIZERDLL_EXPORTS
#define FILEORGANIZERDLL_API __declspec(dllexport)
#else
#define FILEORGANIZERDLL_API __declspec(dllimport)
#endif

#include <iostream>
#include "FileOrganizer.h"
extern "C" FILEORGANIZERDLL_API void startApplication(bool perm, char ** array, int sizeOfArr);

//extern "C" FILEORGANIZERDLL_API std::string getSystemType();