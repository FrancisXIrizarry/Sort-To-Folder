# Sort-To-Folder
Simple C++ 17 program to sort items to folder (Current Version Windows).

## Deposition

I was getting really annoyed at how much space was using in my download folder, just a bunch of files just everywhere so I made a program to sort the important file types (PDF, JPG, MP3, MP4, Etc.), and any I didn't think of. The ones that I can't predict would sort themselves into their own folders based on the name of the file after the last period in the file name. This is Windows (And now Unix) based since I use a Windows PC. I started this 12/28/18 at 12:30AM, issues arose as C++ 17 and Windows API do not exactly play along, and Wstring whilst in C++ 17 combined with Windows 10 also did not play along quite well. I also was unable to use depreciated (or rather became aware that I should not use them); furthermore, API calls to create folders (Possibly through mkdir, system calls, etc.) were utilized to help with the process. As for the Multi-Platform aspect I refused to use any third party/functionality (This took a while to think through and a lot of searching of the costs and benefits). I wanted my application to run on the systems I choose, with the license I choose, the way I wanted it too. If I needed more functionality, and more support then I would use one (Examples in the links below). 

> This is designed to work only from the Downloads folder on someone's computer. (Whole purpose of using Windows API calls)

# Intentions  
* ~~Ubuntu 16.04 Adaptation~~ (Can run on Windows 10 (Windows 7 & Later) & Ubuntu 16.04 (Unix Systems that can run C++17 should be fine & Later than Ubuntu 12.04))
* Reduce Redundancy [XXXXXXXXOOOOOOOO] 46%
* Add more specific cases
* Try to integrate website download information to better sort data
* Potentially integrate method (Image recognition) to determine NSFW/SFW Data to sort appropriately. 
* Add GUI so users can request location to sort data, time limit, etc. [C++ GUI](https://stackoverflow.com/questions/1186017/how-do-i-build-a-graphical-user-interface-in-c)  
* Maybe cross-code with python for more difficult tasks regarding image recognition. 

[Windows API to convert WString/String](https://docs.microsoft.com/en-us/windows/desktop/api/stringapiset/nf-stringapiset-widechartomultibyte)  
[Windows API to create folders](https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createdirectorya)    
[Windows WideCharToMultiByte Example](https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte)  
[Cross Platform Link 1 (Easiest Way to Cross Platform)](https://stackoverflow.com/questions/4780316/easiest-way-to-build-a-cross-platform-application)  
[Cross Platform Link 2 (Learning Cross Platform C)](https://stackoverflow.com/questions/1558194/learning-and-cross-platform-development-c)  
[Cross Platform Link 3 (C App Cross Platformed?)](https://stackoverflow.com/questions/33238345/are-c-applications-cross-platform)  

