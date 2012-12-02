//
//  OpenGLViewAdapter.h
//  Flexigin
//
//  Created by Steven Bloemer on 11/22/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#import <Cocoa/Cocoa.h>

#include "Neverland.h"

@interface OpenGLViewAdapter : NSOpenGLView
{
    Neverland *gl_view;

    IBOutlet NSSlider *red_slider;
    IBOutlet NSSlider *green_slider;
    IBOutlet NSSlider *blue_slider;
}

- (IBAction)redSliderChanged:(id)slider;
- (IBAction)greenSliderChanged:(id)slider;
- (IBAction)blueSliderChanged:(id)slider;

@end
