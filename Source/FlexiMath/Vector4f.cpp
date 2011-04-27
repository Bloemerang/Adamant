/**
 * @file
 * @brief Definitions for Vector4f class.
 * @author   Steven Bloemer
 * @date     12/24/2010
 * @lastedit 1/1/2011
 */
#include "Vector3f.h"
#include "Vector4f.h"

namespace flexi {
namespace math {
namespace fpu_math {

const Vector4f Vector4f::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

Vector4f::Vector4f() { }
Vector4f::Vector4f(const Vector4f& o) : x(o.x), y(o.y), z(o.z), w(o.w) { }
Vector4f::Vector4f(const Vector3f& o) : x(o.x), y(o.y), z(o.z), w(1.0f) { }
Vector4f::Vector4f(const float x, const float y, const float z, const float w)
    : x(x), y(y), z(z), w(w)
{ }

Vector4f::operator const Vector3f&() const {
    return *reinterpret_cast<const Vector3f*>(this);
}

void Vector4f::set(const float x, const float y, const float z, const float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4f Vector4f::operator+(const Vector4f& o) const {
    return Vector4f(x + o.x, y + o.y, z + o.z);
}

Vector4f& Vector4f::operator+=(const Vector4f& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}

Vector4f Vector4f::operator-() const {
    return Vector4f(-x, -y, -z);
}

Vector4f Vector4f::operator-(const Vector4f& o) const {
    return Vector4f(x - o.x, y - o.y, z - o.z);
}

Vector4f& Vector4f::operator-=(const Vector4f& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}

Vector4f Vector4f::operator*(const float s) const {
    return Vector4f(x * s, y * s, z * s);
}

Vector4f& Vector4f::operator*=(const float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

float Vector4f::dot(const Vector4f& o) const {
    return x * o.x + y * o.y + z * o.z;
}

Vector4f Vector4f::cross(const Vector4f& o) const {
  return Vector4f(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x);
}


} // namespace fpu_math
} // namespace math
} // namespace flexi
