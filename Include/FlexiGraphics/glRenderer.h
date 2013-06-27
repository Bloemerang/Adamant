//
//  glRenderer.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/31/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_glRenderer_h
#define Flexigin_glRenderer_h

#include "Util.h"
#include "glObject.h"
#include "glProgram.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

struct Renderer {
    Renderer() : m_program(Program::Ptr()) {}

    bool setProgram(Program::Ptr program) {
        bool success = program->activate();

        if (success) {
            m_program = std::move(program);
        }

        return success;
    }

    void renderMesh(Mesh::Ptr mesh);
private:
    Program::Ptr m_program;
};

CLOSE_FLEXI_NAMESPACE2()

#endif
