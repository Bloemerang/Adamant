//
//  glLight.cpp
//  Flexigin
//
//  Created by Steven Bloemer on 12/1/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include "glLight.h"

OPEN_FLEXI_NAMESPACE1(gl)

Light::Light
(
    Vector4f position,
    Vector4f ambient_color,
    Vector4f diffuse_color,
    Vector4f specular_color
)
    : m_position(position)
    , m_ambient_color(ambient_color)
    , m_diffuse_color(diffuse_color)
    , m_specular_color(specular_color)
    , m_enabled(false)
{}

void
Light::turnOn()
{
    glLightfv(GL_LIGHT0, GL_POSITION, m_position.adr());
    glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambient_color.adr());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuse_color.adr());
    glLightfv(GL_LIGHT0, GL_SPECULAR, m_specular_color.adr());

    glEnable(GL_LIGHT0);
}

void
Light::turnOff()
{
    glDisable(GL_LIGHT0);
}

CLOSE_FLEXI_NAMESPACE1()
