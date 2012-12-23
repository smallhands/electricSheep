#include "Path_C_Interface.h"
#include <string>

using namespace std;

const char * pathForFile(const char *name, const char *extension) {
	string nameStr = string(name);
	string extStr = string(extension);
	string path = nameStr + "." + extStr;

	return path.c_str();
}