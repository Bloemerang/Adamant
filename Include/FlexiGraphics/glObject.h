//
//  glObject.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/31/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_glObject_h
#define Flexigin_glObject_h

#include <cstdint>
#include <memory>
#include "Util.h"
#include "FlexiMath.h"
#include "glVertexArray.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

// TODO: This should be a base class for triangle meshes, points, lines, etc.
// For now, just implement the Mesh (eventual) subclass, which should be moved to its own
// file eventually.
// TODO: enable_shared_from_this
// TODO: We need an abstraction for a GL vertex array and its associated state. That
// abstraction will probably replace this one.
struct Mesh {
    typedef std::shared_ptr<Mesh> Ptr;

    Mesh(const Vertex* vertices, unsigned vertex_count,
         const VertexIndex* indices, unsigned indices_count)
        : vertices(vertices), vertex_count(vertex_count)
        , indices(indices),   indices_count(indices_count)
    {}

    const Vertex*      vertices;
    unsigned           vertex_count;
    const VertexIndex* indices;
    unsigned           indices_count;
};

CLOSE_FLEXI_NAMESPACE2()

#endif
