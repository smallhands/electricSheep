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
- (void)clear;
- (void)render;

@end

@implementation OpenGLView

- (void)setupShaders {
#pragma message("TODO: should be an engine call with loaded shader sources")
    NSString *vertexShaderPath=[[NSBundle mainBundle] pathForResource:@"ios-vertex" ofType:@"glsl"];
    NSError *error;
    NSString *vertexShaderSource=[NSString stringWithContentsOfFile:vertexShaderPath encoding:NSUTF8StringEncoding error:&error];
    if (!vertexShaderSource) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    GLuint vertexShaderHandle=createShader([vertexShaderSource UTF8String], GL_VERTEX_SHADER);
    
    NSString *fragmentShaderPath=[[NSBundle mainBundle] pathForResource:@"ios-fragment" ofType:@"glsl"];
    NSString *fragmentShaderSource=[NSString stringWithContentsOfFile:fragmentShaderPath encoding:NSUTF8StringEncoding error:&error];
    if (!fragmentShaderSource) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    GLuint fragmentShaderHandle=createShader([fragmentShaderSource UTF8String], GL_FRAGMENT_SHADER);
    
    GLuint shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderHandle);
    glAttachShader(shaderProgram, fragmentShaderHandle);
    glLinkProgram(shaderProgram);
    GLint linkSuccess=GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
    if(linkSuccess==GL_FALSE){
        NSLog(@"Failed to link program");
        exit(1);
    }
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
    [self setupLayer];
    [self setupContext];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self setupShaders];
    [self render];
}

- (void)clear {
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

- (void)render {
#pragma message("TODO: should be a call to the engine")
    [self clear];
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
