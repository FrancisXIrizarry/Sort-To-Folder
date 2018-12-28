# Sort-To-Folder
Simple C++ 17 program to sort items to folder (Current Version Windows).

## Intentions

I was getting really annoyed at how much space was using in my download folder with a bunch of files just everywhere so I made a program to sort the important types of data (PDF, JPG, MP3, MP4, Etc.), and any I didn't think of would sort themselves into their own folders. This is windows based since I use a windows PC, and I did this since a couple of hours ago (C++ 17 and Windows API do not exactly play along, and wstring whilst in C++ 17 and Windows 10 also did not play along quite well). I also was unable to use depreciated (or rather should not use) API calls to create folders (Possibly through mkdir, system calls, etc.). 

[Windows API to convert WString/String](https://docs.microsoft.com/en-us/windows/desktop/api/stringapiset/nf-stringapiset-widechartomultibyte)  
[Windows API to create folders](https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createdirectorya)  
[Windows WideCharToMultiByte Example](https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte)  
