//
//  Textures.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PVRTexture.h"

@interface TexturesMap : NSObject

+ (TexturesMap *)sharedInstance;
- (GLuint)textureForName:(NSString *)textureName;

@end
