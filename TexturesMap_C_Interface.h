//
//  TexturesMap_C_Interface.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_TexturesMap_C_Interface_h
#define electricSheep_TexturesMap_C_Interface_h

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma message("To keep it truly cross platform, some sort of switching should be done here to swap in implementations")
GLuint textureForName(const char *name);
    
#ifdef __cplusplus
}
#endif

#endif
