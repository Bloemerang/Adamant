//
//  glProgram.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_glProgram_h
#define Flexigin_glProgram_h

#include <cstdint>
#include <memory>
#include "OpenGLPlatform.h"
#include "Util.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

enum class ShaderStage {
    VERTEX,
    FRAGMENT,
    COUNT
};

struct Program {
    typedef std::unique_ptr<Program> Ptr;

    // TODO: Support the other shader types and allow mixing and matching between programs
    // if it makes sense in practice.
    static inline Ptr make(const char* vertex_shader,
                           const char* fragment_shader)
    {
        Ptr program = Ptr(new Program(vertex_shader, fragment_shader));

        if (!program && !program->m_program_handle) {
            program.reset();
        }

        return program;
    }

    bool activate();
    bool deactivate();

    ~Program();

private:
    friend class ProgramBuilder;
    Program(GLuint program_handle);
    Program(const char* vertex_shader, const char* fragment_shader);

private:
    GLuint m_program_handle;
};


struct ProgramBuilder {
    typedef std::unique_ptr<GLchar[]> ErrorMessagePtr;

    ProgramBuilder();

    ErrorMessagePtr SetShader(ShaderStage stage, const char* shader_text);
    ErrorMessagePtr Link();

    Program::Ptr Build();

private:
    GLuint m_program_handle;
    GLuint m_shader_handle[static_cast<unsigned>(ShaderStage::COUNT)];
};

CLOSE_FLEXI_NAMESPACE2()

#endif
