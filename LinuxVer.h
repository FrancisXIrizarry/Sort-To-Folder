#pragma once

#ifndef LINUXVER_H
#define LINUXVER_H

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

bool createFolder(std::string outputFolder){
    //std::cout << "outputFolder: " <<  outputFolder << std::endl;
    DIR* tempDir = opendir(outputFolder.c_str());
    if(tempDir){
        closedir (tempDir);
        return true;
    }
    else{
        const int dir_err = mkdir(outputFolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            printf("Error creating directory!!!N\n");
            return false;
        }
        return true;
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
		createFolder(pdfStr);
		createFolder(picStr);
		createFolder(vidStr);
		createFolder(zipStr);
		createFolder(textStr);
	}
	catch (...) {
		std::cerr << "Something broke in Pre-Set Folder Creation Function (checkPathExists)" << std::endl;
	}
}

void addToFolder(std::string fileNVar, std::string pathDirVar, std::string srcpath , std::string folderName){
        std::string destpath = pathDirVar + folderName + "/" + fileNVar;
        //std::cout << " \n\n destPath :: " << destpath << std::endl;
        //std::cout << " \n\n srcpath :: " << srcpath << std::endl;
        if (rename (srcpath.c_str(), destpath.c_str())) {
            // something went wrong
            if (errno == EXDEV) {
            // copy data and meta data 
            } 
            else { perror("rename"); exit(EXIT_FAILURE); };
            } 
        else { // the rename succeeded
        }
}

void lastResort(std::string fileName, const std::string srcpath, const std::string pathDir) {
	size_t found = fileName.find_last_of(".");
	std::string fileType = fileName.substr(found + 1);
	std::string folderName = "/" + fileType + "Folder";
    std::string strLoc = pathDir + folderName + "/" + fileName;
    std::string strFold = pathDir + folderName;
    //std::cout << strLoc << "        and         " << strFold << std::endl;
    if(createFolder(strFold)){
        addToFolder(fileName, pathDir, srcpath, folderName);
    }
}

void checkTypeFunc(std::string fileName, const std::string pathDir, const std::string fullPath){
    std::cout << " Filename: " << fileName << "\n pathDir: " << pathDir << "\n fullPath: " << fullPath << std::endl;
    transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
    if (fileName.find("pdf") != std::string::npos && fileName != "pdffolder") {
		std::string folderName = "/pdfFolder/";
		addToFolder(fileName, pathDir, fullPath, folderName);
	}
	else if (fileName.find("png") != std::string::npos || fileName.find("jpg") != std::string::npos || fileName.find("tiff") != std::string::npos || fileName.find("jpeg") != std::string::npos) {

		std::string folderName = "/picFolder/";
		addToFolder(fileName, pathDir, fullPath, folderName);
	}
	else if (fileName.find("mp4") != std::string::npos || fileName.find("mov") != std::string::npos || fileName.find("avi") != std::string::npos || fileName.find(".ts") != std::string::npos) {

		std::string folderName = "/vidFolder/";
		addToFolder(fileName, pathDir, fullPath, folderName);
	}
	else if ((fileName.find("zip") != std::string::npos || fileName.find("rar") != std::string::npos)  && fileName != "zipfolder") {

		std::string folderName = "/zipFolder/";
  
		addToFolder(fileName, pathDir, fullPath, folderName);
	}
	else if ((fileName.find(".txt") != std::string::npos || fileName.find(".doc") != std::string::npos || fileName.find(".readme") != std::string::npos
		|| fileName.find(".text") != std::string::npos) && fileName != "textfolder") {

		std::string folderName = "/textFolder/";
		addToFolder(fileName, pathDir, fullPath, folderName);
	}
	else {
		lastResort(fileName, fullPath, pathDir);
		//if (!strstr(fileName.c_str(), "folder")) {cout << fileName << endl;}
	}
}






/*void checkType(DIR * testVar){
    std::cout << typeid(testVar).name() << '\n';
}*/
int mainLinuxFunc(std::string PLAT_FORM)
{
    std::cout << "Works (Linux)" << std::endl;
    struct passwd *pw = getpwuid(getuid());
    std::string homedir = pw->pw_dir;
    homedir = homedir + "/Downloads";
    std::cout << homedir << std::endl;


    DIR *dir;
    //checkType(dir);
    defaultFolderSetup(homedir);
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
                std::string fullPathVar = homedir + "/" + entity->d_name;
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
    return 0;
}




#endif
#endif