/**
 * @file
 * @brief Definitions for the utilities declared in MathUtil.h
 * @author   Steven Bloemer
 * @date     12/16/2010
 * @lastedit 12/30/2010
 */
#include "MathUtil.h"

namespace flexi {
namespace math {

const float PI = 3.141592653589793f;
const float TWO_PI = 6.283185307179586f;
const float HALF_PI = 1.5707963267948966f;

const float FLOAT_TOLERANCE = 0.0001f;

bool areEqual(const float f1, const float f2, const float tolerance)
{
    return !( (f1 + tolerance) < f2 || (f1 - tolerance) > f2 );
}

} // namespace math
} // namespace flexi
