//
//  OpenGLViewAdapter.mm
//  Flexigin
//
//  Created by Steven Bloemer on 11/22/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#import "OpenGLViewAdapter.h"

@implementation OpenGLViewAdapter

- (void)prepareOpenGL
{
    [red_slider   setMaxValue:1.0];
    [red_slider   setFloatValue:1.0];
    [green_slider setMaxValue:1.0];
    [green_slider setFloatValue:1.0];
    [blue_slider  setMaxValue:1.0];
    [blue_slider  setFloatValue:1.0];

    // Enable vsync
    GLint swap_interval = 1;
    [[self openGLContext] setValues:&swap_interval forParameter:NSOpenGLCPSwapInterval];

    // Setup the actual GL class
    gl_view = new Neverland;
    gl_view->setClearColor(Color4f(1.0f, 1.0f, 1.0f));
}

- (void)drawRect:(NSRect)dirty_rect
{
    NSLog(@"dirty_rect [%f %f] %fx%f",
        dirty_rect.origin.x, dirty_rect.origin.y,
        dirty_rect.size.width, dirty_rect.size.height);

    assert(gl_view);

    gl_view->draw(dirty_rect.size.width, dirty_rect.size.height);

    [[self openGLContext] flushBuffer];
}

- (IBAction)redSliderChanged:(id)slider
{
    NSLog(@"Red slider changed value to %f", [slider floatValue]);

    auto clear_color = gl_view->clearColor();
    clear_color.r = [slider floatValue];
    gl_view->setClearColor(clear_color);

    [self setNeedsDisplay:YES];
}

- (IBAction)greenSliderChanged:(id)slider
{
    NSLog(@"Green slider changed value to %f", [slider floatValue]);

    auto clear_color = gl_view->clearColor();
    clear_color.g = [slider floatValue];
    gl_view->setClearColor(clear_color);

    [self setNeedsDisplay:YES];
}

- (IBAction)blueSliderChanged:(id)slider
{
    NSLog(@"Blue slider changed value to %f", [slider floatValue]);

    auto clear_color = gl_view->clearColor();
    clear_color.b = [slider floatValue];
    gl_view->setClearColor(clear_color);

    [self setNeedsDisplay:YES];
}

@end
