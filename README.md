# Sort-To-Folder
Simple C++ 17 program to sort items to folder (Current Version Windows).

## Deposition

I was getting really annoyed at how much space was using in my download folder with a bunch of files just everywhere so I made a program to sort the important types of data (PDF, JPG, MP3, MP4, Etc.), and any I didn't think of would sort themselves into their own folders. This is windows based since I use a windows PC, and I did this since a couple of hours ago (C++ 17 and Windows API do not exactly play along, and wstring whilst in C++ 17 and Windows 10 also did not play along quite well). I also was unable to use depreciated (or rather should not use) API calls to create folders (Possibly through mkdir, system calls, etc.). 

> This is designed to work only from the Downloads folder on someone's computer. (Whole purpose of using Windows API calls)

# Intentions  
* Ubuntu 16.04 Adaptation
* Reduce Redundancy
* Add more specific cases
* Try to integrate website download information to better sort data
* Potentially integrate method (Image recognition) to determine NSFW/SFW Data to sort appropriately. 
* Add GUI so users can request location to sort data, time limit, etc. [You can use numbers for reference-style link definitions][1]
* Maybe cross-code with python for more difficult tasks regarding image recognition. 

[Windows API to convert WString/String](https://docs.microsoft.com/en-us/windows/desktop/api/stringapiset/nf-stringapiset-widechartomultibyte)  
[Windows API to create folders](https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createdirectorya)    
[Windows WideCharToMultiByte Example](https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte)  
[1]: http://slashdot.org

