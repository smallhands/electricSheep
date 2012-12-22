//
//  Path_C_Interface.h
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_Path_C_Interface_h
#define electricSheep_Path_C_Interface_h

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma message("cross platform, switching is done by swapping implementations in the build")
    const char * pathForFile(const char *name, const char *extension);
    
#ifdef __cplusplus
}
#endif

#endif
