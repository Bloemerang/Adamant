#ifndef FLEXI_MATH_H_
#define FLEXI_MATH_H_
/**
 * @file
 * @brief Header for the FlexiMath module.
 * 
 * Defines the public interface to the FlexiMath module. All
 * identifiers are defined in the flexi::math namespace.
 *
 * Switches between the math implementations depending on whether
 * the USE_SIMD macro is defined (use SIMD math) or not (use FPU
 * math).
 *
 * @author   Steven Bloemer
 * @date     12/26/2010
 * @lastedit 12/26/2010
 */

#include "MathUtil.h" ///< Scalar math functions and constants

#ifdef USE_SIMD
// TODO

namespace flexi {
namespace math {

using namespace simd_math;

} // namespace math
} // namespace flexi

#else // Use FPU math classes

#include "Vector3f.h"
#include "Vector4f.h"
#include "RotationMatrix.h"
#include "Quaternion.h"
#include "Matrix4x3.h"
#include "Matrix4x4.h"

namespace flexi {
namespace math {

using namespace fpu_math;

} // namespace math
} // namespace flexi

#endif // FLEXI_MATH_H_
