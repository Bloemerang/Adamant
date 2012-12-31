//
//  ProgramEditorWindow.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/16/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ProgramEditorWindow : NSWindow
{
    IBOutlet NSTextView *m_vertex_shader_view;
    IBOutlet NSTextView *m_fragment_shader_view;
    IBOutlet NSTextView *m_output_view;
}

- (IBAction)build:(id)sender;

- (void)close;

@end
