//
//  OpenGLView.h
//  electricSheep
//
//  Created by Ali Helmy on 23/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "electricSheep.h"

@interface OpenGLView : UIView {
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_eaglContext;
    GLuint _colorRenderBuffer;
    GLuint _depthRenderBuffer;
    ElectricSheepEngine *_electricSheepEngine;
}

@end
