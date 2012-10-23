//
//  OpenGLView.m
//  electricSheep
//
//  Created by Ali Helmy on 23/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import "OpenGLView.h"

@interface OpenGLView ()

- (void)setup;
- (void)setupLayer;
- (void)setupContext;
- (void)setupRenderBuffer;
- (void)setupFrameBuffer;
- (void)setupShaders;
- (void)render;

@end

@implementation OpenGLView

- (void)setupShaders {
    NSString *vertexShaderPath=[[NSBundle mainBundle] pathForResource:@"vertex" ofType:@"glsl"];
    NSError *error;
    NSString *vertexShaderSource=[NSString stringWithContentsOfFile:vertexShaderPath encoding:NSUTF8StringEncoding error:&error];
    if (!vertexShaderSource) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    NSString *fragmentShaderPath=[[NSBundle mainBundle] pathForResource:@"fragment" ofType:@"glsl"];
    NSString *fragmentShaderSource=[NSString stringWithContentsOfFile:fragmentShaderPath encoding:NSUTF8StringEncoding error:&error];
    if (!fragmentShaderSource) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    _electricSheepEngine.initShaders([vertexShaderSource UTF8String], [fragmentShaderSource UTF8String]);
}

- (void)setupLayer {
    _eaglLayer=(CAEAGLLayer *)self.layer;
    _eaglLayer.opaque=YES;
}

- (void)setupContext {
    EAGLRenderingAPI api=kEAGLRenderingAPIOpenGLES2;
    _eaglContext=[[EAGLContext alloc] initWithAPI:api];
    [EAGLContext setCurrentContext:_eaglContext];
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_eaglContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupFrameBuffer {
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
}

- (void)setup {
    _electricSheepEngine=ElectricSheepEngine();
    [self setupLayer];
    [self setupContext];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self setupShaders];
    [self render];
}

- (void)render {
    _electricSheepEngine.render();
    [_eaglContext presentRenderbuffer:_colorRenderBuffer];
}

- (void)awakeFromNib {
    [self setup];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)dealloc {
    _eaglContext=nil;
    _eaglLayer=nil;
}

@end
