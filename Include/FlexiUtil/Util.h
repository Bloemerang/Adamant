//
//  Util.h
//  Flexigin
//
//  Created by Steven Bloemer on 12/1/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//

#ifndef Flexigin_Util_h
#define Flexigin_Util_h

#include <cstdlib>

#define OPEN_FLEXI_NAMESPACE                            \
    namespace flexi {
#define OPEN_FLEXI_NAMESPACE1(first)                    \
    OPEN_FLEXI_NAMESPACE namespace first {
#define OPEN_FLEXI_NAMESPACE2(first, second)            \
    OPEN_FLEXI_NAMESPACE1(first) namespace second {
#define OPEN_FLEXI_NAMESPACE3(first, second, third)     \
    OPEN_FLEXI_NAMESPACE2(first, second) namespace third {

#define CLOSE_FLEXI_NAMESPACE           }
#define CLOSE_FLEXI_NAMESPACE1()        }}
#define CLOSE_FLEXI_NAMESPACE2()        }}}
#define CLOSE_FLEXI_NAMESPACE3()        }}}}

#define RETURN_ON_ALLOC_FAILURE(new_memory, failure_value) do {                          \
    if ((new_memory) == nullptr) {                                                       \
        assert(!"Memory allocation failure");                                            \
        return failure_value;                                                            \
    }                                                                                    \
} while (false)

#define countof(ar) ( sizeof(ar) / sizeof((ar)[0]) )

OPEN_FLEXI_NAMESPACE1(util)

struct Deallocate {
    void operator()(void* memory) { free(memory); }
};

CLOSE_FLEXI_NAMESPACE1()

#endif
