//
//  Textures.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TexturesMap_C_Interface.h"

@interface TexturesMap : NSObject

+ (TexturesMap *)sharedInstance;
- (GLuint)textureForName:(NSString *)textureName;

@end
