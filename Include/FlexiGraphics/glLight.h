//
//  glLight.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/1/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_glLight_h
#define Flexigin_glLight_h

#include "OpenGLPlatform.h"
#include "Util.h"
#include "FlexiMath.h"

OPEN_FLEXI_NAMESPACE2(graphics, gl)

using namespace flexi::math;

struct Light {
    Light(Vector4f position,
          Vector4f ambient_color,
          Vector4f diffuse_color,
          Vector4f specular_color);

    void turnOn();
    void turnOff();
private:
    Vector4f m_position;
    Vector4f m_ambient_color;
    Vector4f m_diffuse_color;
    Vector4f m_specular_color;
    bool m_enabled;
};

CLOSE_FLEXI_NAMESPACE2()

#endif
