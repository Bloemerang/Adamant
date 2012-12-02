//
//  Neverland.h
//  Flexigin
//
//  Created by Steven Bloemer on 11/22/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#ifndef __Flexigin__Neverland__
#define __Flexigin__Neverland__

#include "Camera.h"
#include "glLight.h"

using namespace flexi;
using namespace flexi::graphics;

struct Color4f {
    float r,g,b,a;

    Color4f(float r, float g, float b, float a=1.0f)
        : r(r), g(g), b(b), a(a)
    {}
};

struct Neverland
{
    Neverland();
    void draw(unsigned width, unsigned height);

    const Color4f& clearColor() const { return m_clear_color; }
    void setClearColor(const Color4f& color) {
        m_clear_color = color;
        m_dirty_state.clear_color = true;
    }

protected:
    void updateDrawState();
    void drawStuff();

private:
    Camera m_camera;
    gl::Light m_light;
    Color4f m_clear_color;

    union DirtyState{
        struct {
            bool clear_color  : 1;
            bool depth_test   : 1;
            bool vertex_array : 1;
            bool lighting     : 1;
        };

        uint32_t dirty;
    } m_dirty_state;
};

#endif /* defined(__Flexigin__Neverland__) */
