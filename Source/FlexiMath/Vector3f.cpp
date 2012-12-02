/**
 * @file
 * @brief Definitions for Vector3f class.
 * @author   Steven Bloemer
 * @date     12/5/2010
 * @lastedit 1/1/2011
 */
#include <cmath>
#include "MathUtil.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Static member initialization
const Vector3f Vector3f::ZERO(0.0f, 0.0f, 0.0f);

////////////////////////////////////////////////////////////////////////////////
// Construction

Vector3f::Vector3f() { }

Vector3f::Vector3f(const Vector3f& other)
    : x(other.x), y(other.y), z(other.z)
{ }

Vector3f::Vector3f(const Vector4f& other)
    : x(other.x), y(other.y), z(other.z)
{ }

Vector3f::Vector3f(const float x, const float y, const float z)
    : x(x), y(y), z(z)
{ }

////////////////////////////////////////////////////////////////////////////////
// Operators

Vector3f Vector3f::operator-() const
{
    return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator+(const Vector3f& that) const
{
    return Vector3f(this->x + that.x, this->y + that.y, this->z + that.z);
}

Vector3f& Vector3f::operator+=(const Vector3f& that)
{
    this->x += that.x;
    this->y += that.y;
    this->z += that.z;

    return *this;
}

Vector3f Vector3f::operator-(const Vector3f& that) const
{
    return Vector3f(this->x - that.x, this->y - that.y, this->z - that.z);
}

Vector3f& Vector3f::operator-=(const Vector3f& that)
{
    this->x -= that.x;
    this->y -= that.y;
    this->z -= that.z;

    return *this;
}

Vector3f Vector3f::operator*(const float s) const
{
    return Vector3f(x * s, y * s, z * s);
}

Vector3f operator*(const float s, const Vector3f& v)
{
    return Vector3f(v.x * s, v.y * s, v.z * s);
}

Vector3f& Vector3f::operator*=(const float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Methods

float Vector3f::dot(const Vector3f& that) const
{
    return this->x * that.x + this->y * that.y + this->z * that.z;
}

Vector3f Vector3f::cross(const Vector3f& that) const
{
    return Vector3f(this->y * that.z - this->z * that.y,
                    this->z * that.x - this->x * that.z,
                    this->x * that.y - this->y * that.x );
}

float Vector3f::len() const
{
    return sqrtf(lenSquared());
}

float Vector3f::lenSquared() const
{
    return sqr(x) + sqr(y) + sqr(z);
}

Vector3f& Vector3f::normalized()
{
    
    const float length = len();

    if (length != 0) {
        const float invLen = 1.0f / length;

        x *= invLen;
        y *= invLen;
        z *= invLen;
    }
    return *this;
}

Vector3f Vector3f::getNormalized() const
{
    const float length = len();
    const float invLen = (length != 0)
                          ? 1.0f / length
                          : 0;

    return Vector3f(x * invLen, y * invLen, z * invLen);
}

void Vector3f::set(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Vector3f::equals(const Vector3f& that, const float tolerance) const
{
    return !(   !areEqual(this->x, that.x, tolerance)
             || !areEqual(this->y, that.y, tolerance)
             || !areEqual(this->z, that.z, tolerance));
}

bool Vector3f::isZeroVec(const float tolerance /* = FLOAT_TOLERANCE */) const
{
    return !(   !areEqual(x, 0.0f, tolerance)
             || !areEqual(y, 0.0f, tolerance)
             || !areEqual(z, 0.0f, tolerance) );
}

bool Vector3f::isUnitVec(const float tolerance) const
{
    return areEqual(lenSquared(), 1.0f, tolerance);
}

} // namespace fpu_math
} // namespace math
} // namespace flexi
