//
//  ProgramEditorWindow.m
//  Flexigin
//
//  Created by Steven Bloemer on 12/16/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#import "ProgramEditorWindow.h"
#include "glProgram.h"

using namespace flexi::graphics::gl;

@implementation ProgramEditorWindow

- (NSString*)addShaderSource:(NSTextView*)text_view
                    to_stage:(ShaderStage)stage
                  of_builder:(ProgramBuilder*)builder
{
    NSString* source = text_view.string;
    NSString* error_log = [NSString string];
    if (source.length)
    {
        const char* cstr_source = [source cStringUsingEncoding:NSASCIIStringEncoding];
        if (!cstr_source) {
            assert(!"Shader source was not ASCII?!?");
        }

        ProgramBuilder::ErrorMessagePtr compile_log = builder->SetShader(stage, cstr_source);

        if (compile_log)
        {
            // Failure
            error_log = [NSString stringWithCString:compile_log.get()
                                           encoding:NSASCIIStringEncoding];
        }
    }

    return error_log;
}

- (IBAction)build:(id)sender
{
    //NSLog(@"%s: vertex shader source:\n%@\n", __FUNCTION__, m_vertex_shader_view.string);
    //NSLog(@"%s: fragment shader source:\n%@\n", __FUNCTION__, m_fragment_shader_view.string);

    ProgramBuilder program_builder;

    NSString* error_log = [self addShaderSource:m_vertex_shader_view
                                       to_stage:ShaderStage::VERTEX
                                     of_builder:&program_builder];
    error_log = [error_log stringByAppendingString:
                 [self addShaderSource:m_fragment_shader_view
                              to_stage:ShaderStage::FRAGMENT
                            of_builder:&program_builder]];

    // Bail if we're already seeing errors
    if (error_log.length) {
        [m_output_view setString:error_log];
        return;
    }

    ProgramBuilder::ErrorMessagePtr cerror_log = program_builder.Link();
    if (cerror_log) {
        [m_output_view setString:[NSString stringWithCString:cerror_log.get()
                                                    encoding:NSASCIIStringEncoding]];
    } else {
        [m_output_view setString:@"Build Successful"];
    }
}

- (void)close
{
    // Don't actually close the window; just hide it
    [self orderOut:self];
}

@end
