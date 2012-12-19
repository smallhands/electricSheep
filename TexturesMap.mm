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

/*quick hack for loading textures from pngs*/
- (GLuint)textureForName:(NSString *)textureName {
    GLuint textureID=0;
    id textureNameObject=[self.map objectForKey:textureName];
    if (textureNameObject && [textureNameObject isKindOfClass:[NSNumber class]]) {
        textureID=((NSNumber *)textureNameObject).unsignedIntValue;
    } else {
        CGImageRef spriteImage = [UIImage imageNamed:textureName].CGImage;
        
        // 2
        size_t width = CGImageGetWidth(spriteImage);
        size_t height = CGImageGetHeight(spriteImage);
        
        GLubyte * spriteData = (GLubyte *) calloc(width*height*4, sizeof(GLubyte));
        
        CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4,
                                                           CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
        
        // 3
        CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
        
        CGContextRelease(spriteContext);
        
        // 4
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
        
        free(spriteData);
        [self.map setObject:[NSNumber numberWithUnsignedInt:textureID] forKey:textureName];
    }
    return textureID;
}

@end
