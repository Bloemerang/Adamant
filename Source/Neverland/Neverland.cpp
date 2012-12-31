//
//  Neverland.cpp
//  Flexigin
//
//  Created by Steven Bloemer on 11/22/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include <iostream>
#include <cstdint>

#include "FlexiMath.h"
#include "Neverland.h"

using namespace std;
using namespace flexi::math;

struct Vertex
{
    static const unsigned POSITION_OFFSET = 0;
    static const unsigned NORMAL_OFFSET   = sizeof(Vector3f);
    
    Vector3f normal;
    Vector3f position;

    Vertex(const Vector3f& position, const Vector3f& normal)
        : position(position), normal(normal)
    {}
};

#define array_size(arr) sizeof(arr)/sizeof((arr)[0])

static const Vector3f g_triangle[3] = {
    Vector3f(-10, -10, -30),
    Vector3f( 10, -10, -20),
    Vector3f( 10,  10,  0)
};

static const Vertex g_cube_vertices[] = {
    Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f( 0,  0, -1)), // 0
    Vertex(Vector3f(-0.5f,  0.5f, -0.5f), Vector3f( 0,  0, -1)), // 1
    Vertex(Vector3f( 0.5f,  0.5f, -0.5f), Vector3f( 0,  0, -1)), // 2
    Vertex(Vector3f( 0.5f, -0.5f, -0.5f), Vector3f( 0,  0, -1)), // 3
    Vertex(Vector3f(-0.5f, -0.5f,  0.5f), Vector3f( 0,  0,  1)), // 4
    Vertex(Vector3f( 0.5f, -0.5f,  0.5f), Vector3f( 0,  0,  1)), // 5
    Vertex(Vector3f( 0.5f,  0.5f,  0.5f), Vector3f( 0,  0,  1)), // 6
    Vertex(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f( 0,  0,  1)), // 7
    Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1,  0,  0)), // 8
    Vertex(Vector3f(-0.5f, -0.5f,  0.5f), Vector3f(-1,  0,  0)), // 9
    Vertex(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f(-1,  0,  0)), // 10
    Vertex(Vector3f(-0.5f,  0.5f, -0.5f), Vector3f(-1,  0,  0)), // 11
    Vertex(Vector3f( 0.5f, -0.5f,  0.5f), Vector3f( 1,  0,  0)), // 12
    Vertex(Vector3f( 0.5f, -0.5f, -0.5f), Vector3f( 1,  0,  0)), // 13
    Vertex(Vector3f( 0.5f,  0.5f, -0.5f), Vector3f( 1,  0,  0)), // 14
    Vertex(Vector3f( 0.5f,  0.5f,  0.5f), Vector3f( 1,  0,  0)), // 15
    Vertex(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f( 0,  1,  0)), // 16
    Vertex(Vector3f( 0.5f,  0.5f,  0.5f), Vector3f( 0,  1,  0)), // 17
    Vertex(Vector3f( 0.5f,  0.5f, -0.5f), Vector3f( 0,  1,  0)), // 18
    Vertex(Vector3f(-0.5f,  0.5f, -0.5f), Vector3f( 0,  1,  0)), // 19
    Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f( 0, -1,  0)), // 20
    Vertex(Vector3f( 0.5f, -0.5f, -0.5f), Vector3f( 0, -1,  0)), // 21
    Vertex(Vector3f( 0.5f, -0.5f,  0.5f), Vector3f( 0, -1,  0)), // 22
    Vertex(Vector3f(-0.5f, -0.5f,  0.5f), Vector3f( 0, -1,  0)), // 23
};

static const Vector3f g_old_cube_vertices[] = {
    Vector3f(-0.5f, -0.5f, -0.5f), // 0
    Vector3f(-0.5f,  0.5f, -0.5f), // 1
    Vector3f( 0.5f,  0.5f, -0.5f), // 2
    Vector3f( 0.5f, -0.5f, -0.5f), // 3
    Vector3f(-0.5f, -0.5f,  0.5f), // 4
    Vector3f( 0.5f, -0.5f,  0.5f), // 5
    Vector3f( 0.5f,  0.5f,  0.5f), // 6
    Vector3f(-0.5f,  0.5f,  0.5f)  // 7
};

static const uint16_t g_cube_indices[] = {
    0,  1,  2,   0,  2,  3,  // Back
    4,  5,  6,   4,  6,  7,  // Front
    8,  9,  10,  8,  10, 11, // Left
    12, 13, 14,  12, 14, 15, // Right
    16, 17, 18,  16, 18, 19, // Top
    20, 21, 22,  20, 22, 23, // Bottom
};

Neverland::Neverland()
    : m_clear_color(Color4f(0,0,0))
    , m_light(Vector4f(-1, -1, 1, 0),       // Position
              Vector4f(0.3f, 0.3, 0.3f),    // Ambient color
              Vector4f(0.7f, 0.7f, 0.7f),   // Diffuse color
              Vector4f(1, 1, 1))            // Specular color
{
    m_dirty_state.dirty = ~0;
}

void Neverland::draw(unsigned width, unsigned height)
{
    cout << __FUNCTION__ << '(' << width << ", " << height << ')' << endl ;

    updateDrawState();

    m_camera.handleDimensionChange(width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawStuff();

    glFlush();
}

#define UPDATE_STATE(STATE, code...) if (m_dirty_state.STATE) { \
    cout << "Updating " #STATE << endl;                         \
    code;                                                       \
    m_dirty_state.STATE = false;                                \
}

void Neverland::updateDrawState()
{
    if (!m_dirty_state.dirty) {
        return;
    }

    UPDATE_STATE(clear_color,
        glClearColor(clearColor().r, clearColor().g, clearColor().b, clearColor().a))
    UPDATE_STATE(depth_test, glEnable(GL_DEPTH_TEST))
    UPDATE_STATE(vertex_array, glEnableClientState(GL_VERTEX_ARRAY))
    UPDATE_STATE(lighting, {

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        GLfloat ambient_material[4] = { 0.3f, 0, 0, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_material);

        GLfloat diffuse_material[4] = { 0.6, 0, 0, 1.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_material);
    
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    })
}

#define IMMEDIATE     0
#define DRAW_ARRAYS   1
#define DRAW_ELEMENTS 2
#define TECHNIQUE DRAW_ELEMENTS

void Neverland::drawStuff()
{
    static unsigned angle = 0;

    cout << __FUNCTION__ << "()" << endl;

    m_light.turnOn();

#if TECHNIQUE == DRAW_ARRAYS
    glVertexPointer(3, GL_FLOAT, sizeof(g_triangle[0]), g_triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif TECHNIQUE == DRAW_ELEMENTS
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glRotatef(angle++, 0.5f, 0.5f, 0.3f);

    glInterleavedArrays(GL_N3F_V3F, 0, g_cube_vertices);
    glDrawElements(GL_TRIANGLES,
                   array_size(g_cube_indices),
                   GL_UNSIGNED_SHORT,
                   g_cube_indices);

    glPopMatrix();
#elif TECHNIQUE == IMMEDIATE
    glPushMatrix();
    glTranslatef(0, 0, -70);
    glRotatef(angle++, 0, 1, 0);
    glBegin(GL_TRIANGLES);
        glNormal3f(-0.3333333f, -0.66666667f, 0.666666667f);
        glVertex3fv(g_triangle[0].adr());
        glVertex3fv(g_triangle[1].adr());
        glVertex3fv(g_triangle[2].adr());
    glEnd();
    glPopMatrix();
#else
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glRotatef(angle++, 0.5f, 0.5f, 0.3f);

    glBegin(GL_TRIANGLES);
    for (unsigned i = 0; i < array_size(g_cube_indices); ++i) {
        const auto vertex = g_cube_vertices[g_cube_indices[i]];
        glNormal3fv(vertex.normal.adr());
        glVertex3fv(vertex.position.adr());
    }
    glEnd();

    glPopMatrix();
#endif

    assert(glGetError() == GL_NO_ERROR);
}
