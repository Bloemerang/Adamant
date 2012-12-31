//
//  OSXResourceLoader.mm
//  Flexigin
//
//  Created by Steven Bloemer on 12/2/12.
//  Copyright (c) 2012 Steven Bloemer. All rights reserved.
//
#include <cstring>
#include <memory>
#include "OSXResourceLoader.h"
#include "Util.h"

using namespace flexi::assets;

flexi::assets::ResourcePtr
OSXResourceLoader::load(const char* path)
{
    NSString* ns_path = [NSString stringWithCString:path encoding:NSASCIIStringEncoding];
    NSString* file = [[NSBundle mainBundle] pathForResource:ns_path ofType:@""];
    if (file == nil) {
        // TODO: Add the path to the assert message
        assert(!"Could not find a path to the specified resource");
        return ResourcePtr();
    }

    NSString* ns_source = [NSString stringWithContentsOfFile:file encoding:NSASCIIStringEncoding error:nil];
    if (ns_source == nil) {
        // TODO: Add the path to the assert message
        assert(!"Could not read resource file");
        return ResourcePtr();
    }

    const char* ns_owned_cstr = [ns_source UTF8String];
    const auto byte_count = [ns_source length];

    // TODO: Avoid this copy
    uint8_t* source = reinterpret_cast<uint8_t*>(malloc(byte_count));
    RETURN_ON_ALLOC_FAILURE(source, ResourcePtr());

    memcpy(source, ns_owned_cstr, byte_count);

    printf("%s source is:\n%s\n", path, source);

    // The default Flexigin deallocator uses free(), so we don't have to specify our own
    return std::make_shared<Resource<>>(source, byte_count);
}
