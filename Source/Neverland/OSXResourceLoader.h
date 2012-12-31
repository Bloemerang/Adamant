//
//  OSXResourceLoader.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_Header_h
#define Flexigin_Header_h

#include "ResourceLoader.h"

struct OSXResourceLoader: public flexi::assets::ResourceLoader
{
    virtual flexi::assets::ResourcePtr load(const char* path) override;
};

#endif
