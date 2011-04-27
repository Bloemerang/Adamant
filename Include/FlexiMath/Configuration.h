#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
/**
 * @file
 * @brief Configuration file for FlexiMath.
 *
 * Sets various policies used within FlexiMath, such as the handedness of
 * coordinate systems and which vector class is used for matrices.
 *
 * @author   Steven Bloemer
 * @date     12/11/2010
 * @lastedit 12/11/2010
 */
#include "Vector3f.h"
#include "RightHandednessPolicy.h"

namespace flexi {
namespace math {
namespace HandednessPolicy = math::RightHandednessPolicy;

} // namespace math
} // namespace flexi

#endif // CONFIGURATION_H_
