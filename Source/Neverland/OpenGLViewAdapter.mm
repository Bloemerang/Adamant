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
    // Enable vsync
    GLint swap_interval = 1;
    [[self openGLContext] setValues:&swap_interval forParameter:NSOpenGLCPSwapInterval];

    // Setup the actual GL class
    gl_view = new Neverland;
    gl_view->setClearColor(Color4f(1.0f, 1.0f, 1.0f));

    NSLog(@"%s %p: Exit with gl_view %p", __FUNCTION__, self, gl_view);
}

- (void)drawRect:(NSRect)dirty_rect
{
    NSLog(@"dirty_rect [%f %f] %fx%f",
        dirty_rect.origin.x, dirty_rect.origin.y,
        dirty_rect.size.width, dirty_rect.size.height);

    // FIXME: We need to sync the slider values with the GL view before the first draw.
    // I'm not sure whether there is a method we can override for first-time initialization
    // that has the sliders available. We could just read the clear color every time we
    // draw, but 99% of the time it would be redundant work.
    gl_view->draw(dirty_rect.size.width, dirty_rect.size.height);

    [[self openGLContext] flushBuffer];
}

- (IBAction)redSliderChanged:(id)slider
{
    NSLog(@"%s %p: Red slider changed value to %f", __FUNCTION__, self, [slider floatValue]);

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
