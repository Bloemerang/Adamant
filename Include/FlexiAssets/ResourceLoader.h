//
//  ResourceLoader.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_ResourceLoader_h
#define Flexigin_ResourceLoader_h

#include <memory>
#include "Util.h"
#include "Resource.h"

OPEN_FLEXI_NAMESPACE1(assets)

typedef std::shared_ptr<Resource<>> ResourcePtr;

struct ResourceLoader {
    /// Load the resource at the specified path and return a ResourcePtr to it
    virtual ResourcePtr load(const char* path) = 0;

    virtual ~ResourceLoader() {}
};

CLOSE_FLEXI_NAMESPACE1()

#endif
