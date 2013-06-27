//
//  glVertexArray.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/31/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_glVertexArray_h
#define Flexigin_glVertexArray_h

#include "Util.h"
#include "OpenGLPlatform.h"
#include "FlexiMath.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

// Hardcode vertex attribute stuff for now
struct Vertex
{
    typedef flexi::math::Vector3f Vector3f;

    static const unsigned POSITION_OFFSET = 0;
    static const unsigned NORMAL_OFFSET   = sizeof(Vector3f);

    Vector3f position;
    Vector3f normal;

    Vertex(const Vector3f& position, const Vector3f& normal)
        : position(position), normal(normal)
    {}
};

typedef uint16_t VertexIndex;

// TODO: How do we actually draw with this???
struct VertexArray {
    VertexArray(const Vertex* vertices, unsigned vertex_count,
                const VertexIndex* indices, unsigned indices_count);
    ~VertexArray();
private:
    GLuint m_vao;

    struct { GLuint vbo; GLuint ibo; } m_buffers;
};

CLOSE_FLEXI_NAMESPACE2()

#endif
