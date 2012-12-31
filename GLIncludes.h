//	
//  GLIncludes.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_GLIncludes_h
#define electricSheep_GLIncludes_h

#ifdef _WIN32
	#include <Windows.h>
    #include <GL/glew.h>
	#include <GL/glfw.h>
	#define _USE_MATH_DEFINES
#endif

#ifdef __APPLE__
    #import <QuartzCore/QuartzCore.h>

    #if (TARGET_OS_IPHONE==1)
        // iOS
        #import <OpenGLES/ES2/gl.h>
        #import <OpenGLES/ES2/glext.h>
    #else
        // MacOSX
        #include <OpenGL/gl.h>
        #include <Glut/glut.h>
    #endif

#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#endif
