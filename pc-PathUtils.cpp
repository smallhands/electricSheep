#include "Path_C_Interface.h"
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const char * pathForFile(const char *name, const char *extension) {
    string pathPrefix = string("");
    
#ifdef _WIN32
    char executablePath[1024] = {'\0'};
    DWORD charsCopied = GetModuleFileName(NULL, executablePath, 1024);
    if(charsCopied > 0 && charsCopied < 1024) {
        pathPrefix = string(string(executablePath) + "\\..\\");
    }
#endif
    
    string nameStr = string(name);
	string extStr = string(extension);
	string *path = new string(pathPrefix + nameStr + "." + extStr);

	return path->c_str();
}