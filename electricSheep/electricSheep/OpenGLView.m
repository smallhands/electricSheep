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
- (void)render;

@end

@implementation OpenGLView

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
