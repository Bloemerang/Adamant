#ifndef MathUtil_H__
#define MathUtil_H__
/**
 * @file
 * @brief Contains constants and utility functions used in FlexiMath.
 * 
 * @author   Steven Bloemer
 * @date     12/5/2010
 * @lastedit 12/30/2010
 */

namespace flexi {
namespace math {

#ifndef PI
extern const float PI;      ///< 3.14...
#endif
extern const float TWO_PI;  ///< 6.28...
extern const float HALF_PI; ///< 1.57...

/// The maximum delta within which two floats are considered equal.
extern const float FLOAT_TOLERANCE;

bool areEqual(const float f1, const float f2,
              const float tolerance = FLOAT_TOLERANCE);

template<typename Val>
Val sqr(Val v) { return v * v; }

} // namespace math
} // namespace flexi

#endif // MathUtil_H__
