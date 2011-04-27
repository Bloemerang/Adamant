/**
 * @file
 * @brief Defines the assertion module.
 * @author   Steven Bloemer
 * @date     12/9/2010
 * @lastedit 1/2/2011
 */
#include <cassert>
#include "DebugDefs.h"

namespace flexi {
namespace util {

using std::function;

static AssertionCallback assertCallback;

inline void _flexi_assert(const bool expr,
                   const char *const file, const unsigned line,
                   const char *const message /* = 0 */)
{
    if (!expr) {
        if (assertCallback)
            assertCallback(file, line, message);
        assert(false);
    }
} // _flexi_assert()

void setAssertFunction(const AssertionCallback& callback)
{
    assertCallback = callback;
}

} // namespace util
} // namespace flexi