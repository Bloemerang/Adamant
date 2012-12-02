#ifndef VECTOR4F_H_
#define VECTOR4F_H_
/**
 * @file
 * @brief Header for Vector4f class.
 * @author   Steven Bloemer
 * @date     12/12/2010
 * @lastedit 12/26/2010
 */
#include "MathUtil.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class Vector3f;

class Vector4f
{
public: // Fields
    float x, y, z, w;

    static const Vector4f ZERO;

public: // Construction

    Vector4f();
    Vector4f(const Vector4f&);
    Vector4f(const Vector3f&);
    Vector4f(const float x, const float y, const float z, const float w = 1.0f);
    
    operator const Vector3f&() const;

public: // Methods

    void set(const float x, const float y, const float z, const float w = 1.0f);

    Vector4f  operator+(const Vector4f&) const;
    Vector4f& operator+=(const Vector4f&);
    Vector4f  operator-() const;
    Vector4f  operator-(const Vector4f&) const;
    Vector4f& operator-=(const Vector4f&);
    Vector4f  operator*(const float s) const;
    Vector4f& operator*=(const float s);

public:

    float dot(const Vector4f&) const;
    Vector4f cross(const Vector4f&) const;
    float len() const;
    float lenSquared() const;
    Vector4f& normalized();
    Vector4f getNormalized() const;

    const float* adr() const { return reinterpret_cast<const float*>(this); }
    
    bool equals(const Vector4f&, const float tolerance = FLOAT_TOLERANCE) const;
    bool isZeroVec(const float tolerance = FLOAT_TOLERANCE) const;
    bool isUnitVec(const float tolerance = FLOAT_TOLERANCE) const;
};

Vector4f operator*(const float s, const Vector4f& v);

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // VECTOR4F_H_
