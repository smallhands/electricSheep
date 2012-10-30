//
//  Textures.m
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import "TexturesMap.h"

GLuint textureForName(const char *name) {
    return [[TexturesMap sharedInstance] textureForName:[NSString stringWithUTF8String:name]];
}

@interface TexturesMap ()

@property NSMutableDictionary *map;

@end

@implementation TexturesMap

@synthesize map=_map;

- (NSMutableDictionary *)map {
    if (_map==nil) {
        _map=[[NSMutableDictionary alloc] init];
    }
    return _map;
}

+ (TexturesMap *)sharedInstance {
    static TexturesMap *_sharedInstance;
    if (_sharedInstance==nil) {
        _sharedInstance=[[TexturesMap alloc] init];
    }
    return _sharedInstance;
}

- (GLuint)textureForName:(NSString *)textureName {
    GLuint textureID=0;
    id textureNameObject=[self.map objectForKey:textureName];
    if (textureNameObject && [textureNameObject isKindOfClass:[PVRTexture class]]) {
        textureID=((PVRTexture *)textureNameObject).name;
    } else {
        PVRTexture *texture=[PVRTexture pvrTextureWithContentsOfFile:[[NSBundle mainBundle] pathForResource:textureName ofType:@"pvr"]];
        if (texture) {
            textureID=texture.name;
        }
        [self.map setObject:texture forKey:textureName];
    }
    return textureID;
}

@end
