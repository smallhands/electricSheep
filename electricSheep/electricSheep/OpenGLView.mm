//
//  OpenGLView.m
//  electricSheep
//
//  Created by Ali Helmy on 23/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import "OpenGLView.h"

@interface OpenGLView ()

@property (strong, nonatomic) UIPanGestureRecognizer *panGestureRecognizer;
@property (strong, nonatomic) UIPinchGestureRecognizer *pinchGestureRecognizer;

- (void)setup;
- (void)setupLayer;
- (void)setupContext;
- (void)setupRenderBuffer;
- (void)setupDepthBuffer;
- (void)setupFrameBuffer;
- (void)setupDisplayLink;
- (void)render:(CADisplayLink *)displayLink;
- (void)viewPanned:(UIPanGestureRecognizer *)panGesture;
- (void)viewPinched:(UIPinchGestureRecognizer *)pinchGesture;

@end

@implementation OpenGLView

@synthesize panGestureRecognizer=_panGestureRecognizer;
@synthesize pinchGestureRecognizer=_pinchGestureRecognizer;

- (UIPanGestureRecognizer *)panGestureRecognizer {
    if (_panGestureRecognizer==nil) {
        _panGestureRecognizer=[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(viewPanned:)];
    }
    return _panGestureRecognizer;
}

- (UIPinchGestureRecognizer *)pinchGestureRecognizer {
    if (_pinchGestureRecognizer==nil) {
        _pinchGestureRecognizer=[[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(viewPinched:)];
    }
    return _pinchGestureRecognizer;
}

- (void)viewPanned:(UIPanGestureRecognizer *)panGesture {
    static CGPoint previousTranslation=CGPointMake(0, 0);
    if(panGesture.state==UIGestureRecognizerStateEnded) {
        previousTranslation=CGPointMake(0, 0);
    } else {
        CGPoint newTranslation=[panGesture translationInView:self];
        if (_electricSheepEngine) {
            _electricSheepEngine->panCamera(newTranslation.x-previousTranslation.x, newTranslation.y-previousTranslation.y);
        }
        previousTranslation=newTranslation;
    }
}

- (void)viewPinched:(UIPinchGestureRecognizer *)pinchGesture {
    static CGFloat previousScale=1.0;
    if (_electricSheepEngine) {
        _electricSheepEngine->zoomCamera(pinchGesture.scale/previousScale);
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

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

- (void)setupFrameBuffer {
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

- (void)setup {
    [self setupLayer];
    [self setupContext];
    [self setupDepthBuffer];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self addGestureRecognizer:self.panGestureRecognizer];
    [self addGestureRecognizer:self.pinchGestureRecognizer];
    
    //init the engine
    _electricSheepEngine=new ElectricSheepEngine(self.frame.size.width, self.frame.size.height);
    _electricSheepEngine->initWorld();
    
    //setup the main loop
    [self setupDisplayLink];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)render:(CADisplayLink *)displayLink {
    static GLfloat timeElapsed=0;
    timeElapsed+=(float)displayLink.duration * 1000;
    _electricSheepEngine->update(timeElapsed);
    _electricSheepEngine->render();
    [_eaglContext presentRenderbuffer:GL_RENDERBUFFER];
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
    [self removeGestureRecognizer:self.panGestureRecognizer];
}

@end
