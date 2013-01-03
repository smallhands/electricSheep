//	
//  GLIncludes.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_GLIncludes_h
#define electricSheep_GLIncludes_h

#ifdef __APPLE__

    #if (TARGET_OS_IPHONE==1)
        // iOS
        #import <OpenGLES/ES2/gl.h>
        #import <OpenGLES/ES2/glext.h>
        #else
        // MacOSX
        #include "glew.h"
        #include "glfw.h"
    #endif

    #import <QuartzCore/QuartzCore.h>

#endif

#ifdef _WIN32
	#include <Windows.h>
    #include <GL/glew.h>
	#include <GL/glfw.h>
	#define _USE_MATH_DEFINES
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#endif
