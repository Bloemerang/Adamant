//
//  Resource.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_Resource_h
#define Flexigin_Resource_h

#include <cstdlib>
#include "Util.h"

OPEN_FLEXI_NAMESPACE1(assets)

template<typename Deallocate = flexi::util::Deallocate>
struct Resource {
    uint8_t *const data;
    const uint32_t byte_count;

    Resource(uint8_t* data, uint8_t byte_count)
        : data(data), byte_count(byte_count)
    {
        assert(this->data);
        assert(this->byte_count);
    }

    ~Resource()
    {
        assert(this->data);
        m_deallocate(this->data);
    }

    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;

private:
    Deallocate m_deallocate;
};

CLOSE_FLEXI_NAMESPACE1()

#endif
