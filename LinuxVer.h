#pragma once

#ifdef __unix


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include <typeinfo>
#include <algorithm>


void checkTypeFunc(std::string fileName, const std::string pathDir, const std::string fullPath){
    //std::cout << " Filename: " << fileName << "\n pathDir: " << pathDir << "\n fullPath: " << fullPath << std::endl;
    transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
    if (fileName.find("pdf") != std::string::npos && fileName != "pdffolder") {
		std::string folderName = "/pdfFolder/";
		//addToFolder(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("png") != std::string::npos || fileName.find("jpg") != std::string::npos || fileName.find("tiff") != std::string::npos || fileName.find("jpeg") != std::string::npos) {

		std::string folderName = "/picFolder/";
		//addToFolder(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("mp4") != std::string::npos || fileName.find("mov") != std::string::npos || fileName.find("avi") != std::string::npos || fileName.find(".ts") != std::string::npos) {

		std::string folderName = "/vidFolder/";
		//addToFolder(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find("zip") != std::string::npos || fileName.find("rar") != std::string::npos  && fileName != "zipfolder") {

		std::string folderName = "/zipFolder/";
		//addToFolder(fileName, pathFile, pathDir, folderName);
	}
	else if (fileName.find(".txt") != std::string::npos || fileName.find(".doc") != std::string::npos || fileName.find(".readme") != std::string::npos
		|| fileName.find(".text") != std::string::npos&& fileName != "textfolder") {

		std::string folderName = "/textFolder/";
		//addToFolder(fileName, pathFile, pathDir, folderName);
	}
	else {
		//lastResort(fileName, pathFile, pathDir);
		//if (!strstr(fileName.c_str(), "folder")) {cout << fileName << endl;}
	}
}

void defaultFolderSetup(std::string path)
{
	std::string pdfStr = path + "/pdfFolder";
	std::string picStr = path + "/picFolder";
	std::string vidStr = path + "/vidFolder";
	std::string zipStr = path + "/zipFolder";
	std::string textStr = path + "/textFolder";

	std::cout << pdfStr << std::endl;
	try {
		/*createFolder(pdfStr);
		createFolder(picStr);
		createFolder(vidStr);
		createFolder(zipStr);
		createFolder(zipStr);*/
	}
	catch (...) {
		std::cerr << "Something broke in Pre-Set Folder Creation Function (checkPathExists)" << std::endl;
	}
}

void addToFolder(std::string fileNVar, std::string pathDirVar, std::string folderName){
        std::string fullPathAddit = pathDirVar + folderName + "/" + fileNVar;
        const int dir_err = mkdir(fullPathAddit.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            printf("Error creating directory!n");
            exit(1);
        }
}

void createFolder(std::string outputFolder){
    
}



/*void checkType(DIR * testVar){
    std::cout << typeid(testVar).name() << '\n';
}*/
int mainLinuxFunc(std::string PLAT_FORM)
{
    std::cout << "Works (Linux)" << std::endl;
    struct passwd *pw = getpwuid(getuid());
    std::string homedir = pw->pw_dir;
    homedir = homedir + "/Downloads/";
    std::cout << homedir << std::endl;


    DIR *dir;
    //checkType(dir);
    
    struct dirent *entity;
    if ((dir = opendir (homedir.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((entity = readdir (dir)) != NULL) {
            //std::cout << entity->d_name << std::endl;
            DIR* tempDir = opendir((homedir + "/" + entity->d_name).c_str());
            if(tempDir){
                //std::cout << "Folder: " << entity->d_name << std::endl;
                closedir (tempDir);
            }
            else{
                //std::cout << entity->d_name << std::endl;
                std::string fullPathVar = homedir +  entity->d_name;
                checkTypeFunc(entity->d_name, homedir, fullPathVar);
                
            }
            
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
