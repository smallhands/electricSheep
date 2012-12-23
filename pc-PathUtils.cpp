#include "Path_C_Interface.h"
#include <string>

using namespace std;

const char * pathForFile(const char *name, const char *extension, const char *inDir) {
	string nameStr = string(name);
	string extStr = string(extension);
	string dirStr = string(inDir);
	string path = "";
	if (inDir != nullptr) {
		path += inDir;
	}
	path += "/";
	path += name;
	path += ".";
	path += extension;

	return path.c_str();
}