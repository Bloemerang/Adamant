//
//  glProgram.cpp
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include <iostream>
#include <utility>
#include <cassert>
#include "glProgram.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

using namespace std;

static GLuint compile(GLenum type, const char* shader);
static GLuint link(GLuint* shader_handles, unsigned count);
static unique_ptr<GLchar[]> dumpProgramInfo(GLuint program);

#pragma mark Program Methods

Program::Program
(
    const char* vertex_shader,
    const char* fragment_shader
)
    : m_program_handle(0)
{
    if (!(vertex_shader || fragment_shader)) {
        assert(!"Cannot create a program with no shaders");
        return;
    }

    GLuint vertex_shader_handle = 0, fragment_shader_handle = 0;

    try {
        // Compile the shaders
        if (vertex_shader) {
            vertex_shader_handle = compile(GL_VERTEX_SHADER, vertex_shader);
        }

        if (fragment_shader) {
            fragment_shader_handle = compile(GL_FRAGMENT_SHADER, fragment_shader);
        }

        // Bail if we weren't successful. the compile() routine will already have asserted and
        // dumped error info.
        if (!(vertex_shader_handle || fragment_shader_handle)) {
            return;
        }

        // Assemble the program
        GLuint shader_handles[] = {vertex_shader_handle, fragment_shader_handle};
        m_program_handle = link(shader_handles, 2);

    } catch (unique_ptr<GLchar>& msg) {
        glDeleteShader(vertex_shader_handle);
        glDeleteShader(fragment_shader_handle);

        cout << __FUNCTION__ << " failed with message:\n"
             << msg.get() << endl;

        return;
    }
}


Program::Program(GLuint program_handle)
    : m_program_handle(program_handle)
{
    assert(m_program_handle);
}


bool
Program::activate()
{
    if (!m_program_handle) {
        assert(!"Cannot activate a program which failed to initialize");
        return false;
    }

    glValidateProgram(m_program_handle);

    GLint success;
    glGetProgramiv(m_program_handle, GL_VALIDATE_STATUS, &success);
    if (!success) {
        cout << __FUNCTION__ << " failed with error message:\n"
             << dumpProgramInfo(m_program_handle).get() << endl;

        return false;
    }

    // Log the action and elide redundant calls
    GLint program_to_replace;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program_to_replace);
    if (program_to_replace == m_program_handle) {
        cout << "Program " << this << " (#" << m_program_handle << ") is already activated" << endl;
        return true;
    } else if (program_to_replace == 0) {
        cout << "Activating Program " << this << " (#" << m_program_handle << endl;
    } else {
        cout << "Replacing program #" << program_to_replace
             << " with #" << m_program_handle << endl;
    }

    glUseProgram(m_program_handle);
    assert(glGetError() == GL_NO_ERROR);
    return true;
}

bool Program::deactivate()
{
    if (!m_program_handle) {
        assert(!"Cannot deactivate a program which failed to initialize");
        return false;
    }

    GLint current_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);

    if (current_program == m_program_handle) {
        glUseProgram(0);
    } else {
        cout << "Cannot deactivate " << this << " already inactive Program " << this << endl;
        return false;
    }

    return true;
}


Program::~Program()
{
    glDeleteProgram(m_program_handle);
}


#pragma mark ProgramBuilder Methods

ProgramBuilder::ProgramBuilder()
    : m_program_handle(0)
    , m_shader_handle{0,}
{}

unique_ptr<GLchar[]>
ProgramBuilder::SetShader(ShaderStage stage, const char* shader_text)
{
    if (m_shader_handle[(unsigned)stage]) {
        glDeleteShader(m_shader_handle[(unsigned)stage]);
    }

    GLuint gl_stage;
    switch (stage) {
    case ShaderStage::VERTEX: gl_stage = GL_VERTEX_SHADER;      break;
    case ShaderStage::FRAGMENT: gl_stage = GL_FRAGMENT_SHADER;  break;
    case ShaderStage::COUNT: assert(0);                         break;
    }

    try {
        m_shader_handle[(unsigned)stage] = compile(gl_stage, shader_text);
    } catch (unique_ptr<GLchar[]>& msg) {
        return move(msg);
    }

    return unique_ptr<char[]>();
}

unique_ptr<GLchar[]>
ProgramBuilder::Link()
{
    if (m_program_handle) {
        glDeleteProgram(m_program_handle);
    }

    try {
        m_program_handle = link(m_shader_handle, (unsigned)ShaderStage::COUNT);
    } catch (unique_ptr<GLchar[]>& msg) {
        return move(msg);
    }

    return unique_ptr<GLchar[]>();
}


unique_ptr<Program>
ProgramBuilder::Build()
{
    if (!m_program_handle)
    {
        auto error_msg = Link();
        if (error_msg) {
            cout << __FUNCTION__ << " failed with error message:\n"
                 << error_msg.get() << endl;
        }
    }

    return unique_ptr<Program>(new Program(m_program_handle));
}


#pragma mark Static Routines

static GLuint
compile(GLenum type, const char* shader)
{
    GLuint shader_handle = glCreateShader(type);
    glShaderSource(shader_handle, 1, &shader, 0);
    glCompileShader(shader_handle);

    GLint success;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint log_length;
        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* info_log = new GLchar[log_length];
        RETURN_ON_ALLOC_FAILURE(info_log, (glDeleteShader(shader_handle), 0));

        glGetShaderInfoLog(shader_handle, log_length, 0, info_log);

        glDeleteShader(shader_handle);
        throw unique_ptr<GLchar[]>(info_log);
    }

    return shader_handle;
}


static GLuint
link(GLuint* shader_handles, unsigned count)
{
    GLuint program_handle = glCreateProgram();
    assert(program_handle);

    for (unsigned i = 0; i < count; ++i)
    {
        if (shader_handles[i]) {
            glAttachShader(program_handle, shader_handles[i]);
        }
    }

    glLinkProgram(program_handle);

    GLint success;
    glGetProgramiv(program_handle, GL_LINK_STATUS, &success);
    if (!success) {
        unique_ptr<GLchar[]> info_log = dumpProgramInfo(program_handle);
        glDeleteProgram(program_handle);
        throw info_log;
    }

    return program_handle;
}


static unique_ptr<char[]>
dumpProgramInfo(GLuint program)
{
    GLint log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* info_log = new GLchar[log_length];
    RETURN_ON_ALLOC_FAILURE(info_log, unique_ptr<char[]>());

    glGetProgramInfoLog(program, log_length, 0, info_log);

    return unique_ptr<GLchar[]>(info_log);
}

CLOSE_FLEXI_NAMESPACE2()
