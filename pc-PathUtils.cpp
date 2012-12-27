#include "Path_C_Interface.h"
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const char * pathForFile(const char *name, const char *extension) {
    string pathPrefix = string("");
    
#ifdef _WIN32
    short pathSize = 1024;
    char executablePath[pathSize] = {'\0'};
    DWORD charsCopied = GetModuleFileName(NULL, executablePath, pathSize);
    if(charsCopied > 0 && charsCopied < pathSize) {
        pathPrefix = string(string(executablePath) + "\\..\\");
    }
#endif
    
    string nameStr = string(name);
	string extStr = string(extension);
	string *path = new string(pathPrefix + nameStr + "." + extStr);

	return path->c_str();
}