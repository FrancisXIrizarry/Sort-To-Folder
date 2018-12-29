#pragma once

#ifdef __unix


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int mainLinuxFunc(std::string PLAT_FORM)
{
    std::cout << "Works (Linux)" << std::endl;
    struct passwd *pw = getpwuid(getuid());
    std::string homedir = pw->pw_dir;
    homedir = homedir + "/Downloads/";
    std::cout << homedir << std::endl;


    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (homedir.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    }   
    else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    
}


#endif
