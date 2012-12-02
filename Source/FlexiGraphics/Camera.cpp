//
//  Camera.cpp
//  Flexigin
//
//  Created by Steven Bloemer on 11/23/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include <iostream>
#include "Camera.h"

OPEN_FLEXI_NAMESPACE1(graphics)

using namespace std;

Camera::Camera()
    : m_vertical_fov(50)
    , m_near_clip(1)
    , m_far_clip(500)
    , m_width(0)
    , m_height(0)
    , m_perspective_dirty(true)
{}

Camera::Camera(GLdouble fovy, GLdouble near_clip, GLdouble far_clip)
    : m_width(0)
    , m_height(0)
    , m_perspective_dirty(true)
{
    setVerticalFieldOfView(fovy);
    setNearClip(near_clip);
    setFarClip(far_clip);
}

void Camera::handleDimensionChange(unsigned width, unsigned height)
{
    if (!m_perspective_dirty) {
        if (width == m_width && height == m_height) {
            return;
        } else {
            m_width = width;
            m_height = height;
        }
    }

    const GLdouble aspect_ratio = width / (GLdouble)height;

    cout << __FUNCTION__ << '(' << width << ", " << height << ')' << endl
         << "  vertical fov " << m_vertical_fov << " near clip " << m_near_clip
         << " far clip " << m_far_clip << " aspect ratio " << aspect_ratio << endl;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_vertical_fov, aspect_ratio, m_near_clip, m_far_clip);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

CLOSE_FLEXI_NAMESPACE1()
