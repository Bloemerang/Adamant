//
//  glVertexArray.cpp
//  Flexigin
//
//  Created by Steven Bloemer on 12/31/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include <cassert>
#include "glVertexArray.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

VertexArray::VertexArray
(
    const Vertex* vertices, unsigned vertex_count,
    const VertexIndex* indices, unsigned indices_count
)
{
    assert(vertex_count > 0);
    assert(indices_count > 0);

    // FIXME: Switch this over to the core profile call ASAP
    glGenVertexArraysAPPLE(1, &m_vao);
    glBindVertexArrayAPPLE(m_vao);

    glGenBuffers(2, reinterpret_cast<GLuint*>(&m_buffers));
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION_OFFSET);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL_OFFSET);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(VertexIndex), indices, GL_STATIC_DRAW);

    // FIXME: Switch this over to the core profile call ASAP
    glBindVertexArrayAPPLE(0);
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(2, reinterpret_cast<GLuint*>(&m_buffers));
    // TODO

    // FIXME: Switch this over to the core profile call ASAP
    glDeleteVertexArraysAPPLE(1, &m_vao);
}

CLOSE_FLEXI_NAMESPACE2()
