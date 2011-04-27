#ifndef Quaternion_H__
#define Quaternion_H__
/**
 * @file
 * @brief Header for Quaternion class.
 * @author   Steven Bloemer
 * @date     12/14/2010
 * @lastedit 12/26/2010
 */
#include "Vector3f.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class Vector3f;
class RotationMatrix;
class Quaternion;

Vector3f  operator*(const Vector3f&, const Quaternion&);
Vector3f& operator*=(Vector3f&, const Quaternion&);

Quaternion slerp(const Quaternion&, const Quaternion&, const float);

class Quaternion
{
    float w;
    Vector3f v;

    friend class RotationMatrix;
    friend Vector3f  operator*(const Vector3f&, const Quaternion&);
    friend Vector3f& operator*=(Vector3f&, const Quaternion&);
    friend Quaternion slerp(const Quaternion& start, const Quaternion& end, const float);

    Quaternion(const float w, const Vector3f& v);

public:  /**************************** Construction ***************************/

    static const Quaternion IDENTITY;

    Quaternion();
    Quaternion(const Quaternion&);
    explicit Quaternion(const RotationMatrix&);
    Quaternion(const float xRad, const float yRad, const float zRad);
    Quaternion(const Vector3f& axis, const float angle);

public:  /****************************** Accessors ****************************/

    float rotationAngle() const;
    Vector3f rotationAxis() const;

public:  /****************************** Operations ***************************/

    Quaternion operator-() const;

    Quaternion  operator-(const Quaternion&) const;
    Quaternion& operator-=(const Quaternion&);

    Quaternion  operator*(const Quaternion&) const;
    Quaternion& operator*=(const Quaternion&);

    float dot(const Quaternion&) const;
    Quaternion pow(const float) const;

    Quaternion& normalized();
}; // class Quaternion

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // Quaternion_H__
