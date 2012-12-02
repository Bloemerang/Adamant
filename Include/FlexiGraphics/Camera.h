//
//  Camera.h
//  Flexigin
//
//  Created by Steven Bloemer on 11/23/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_Camera_h
#define Flexigin_Camera_h

#include "OpenGLPlatform.h"
#include "DebugDefs.h"
#include "Util.h"

OPEN_FLEXI_NAMESPACE1(graphics)

struct Camera {
    Camera();
    Camera(GLdouble fovy, GLdouble near_clip, GLdouble far_clip);

    void handleDimensionChange(unsigned width, unsigned height);

    GLdouble verticalFieldOfView() const { return m_vertical_fov; }
    void setVerticalFieldOfView(GLdouble fovy) {
        if (fovy >= 180.0 || fovy <= 0) {
            assert(!"Vertical field of view must be in (0,180)");
        }

        m_vertical_fov = fovy;
        m_perspective_dirty = true;
    }
    
    GLdouble nearClip() const { return m_near_clip; }
    void setNearClip(GLdouble near_clip) {
        if (near_clip > 0) {
            assert(!"Near clip must be positive");
        }
        
        m_near_clip = near_clip;
        m_perspective_dirty = true;
    }
    
    GLdouble farClip() const { return m_far_clip; }
    void setFarClip(GLdouble far_clip) {
        if (far_clip > 0) {
            assert(!"Far clip must be positive");
        }
        
        m_far_clip = far_clip;
        m_perspective_dirty = true;
    }

private:
    GLdouble m_vertical_fov;
    GLdouble m_near_clip, m_far_clip;
    unsigned m_width, m_height;
    bool m_perspective_dirty;
};

CLOSE_FLEXI_NAMESPACE1()

#endif
