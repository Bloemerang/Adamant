/**
 * @file
 * @brief Definitions for Quaternion class.
 * @author   Steven Bloemer
 * @date     12/16/2010
 * @lastedit 12/26/2010
 */
#include <cmath>
#include "DebugDefs.h"
#include "MathUtil.h"
#include "RotationMatrix.h"
#include "Quaternion.h"

namespace flexi {
namespace math {
namespace fpu_math {

const Quaternion Quaternion::IDENTITY;

////////////////////////////////////////////////////////////////////////////////
// Construction

Quaternion::Quaternion(const float w, const Vector3f& v)
    : w(w), v(v)
{ }

Quaternion::Quaternion()
    : w(1.0f), v(Vector3f::ZERO)
{ }

Quaternion::Quaternion(const Quaternion& other)
    : w(other.w), v(other.v)
{ }

Quaternion::Quaternion(const RotationMatrix& R)
{
    float biggestTrace;
    unsigned char switchVal;

    if (R.yAxis.y < R.zAxis.z) {
        biggestTrace = R.xAxis.x - R.yAxis.y - R.zAxis.z;
        switchVal = 1;
    } else {
        biggestTrace = R.xAxis.x + R.yAxis.y + R.zAxis.z;
        switchVal = 0;
    }

    const float traceY = R.yAxis.y - R.xAxis.x - R.zAxis.z;
    if (biggestTrace < traceY) {
        biggestTrace = traceY;
        switchVal = 2;
    }

    const float traceZ = R.zAxis.z - R.xAxis.x - R.yAxis.y;
    if (biggestTrace < traceZ) {
        biggestTrace = traceZ;
        switchVal = 3;
    }

    const float biggestVal = sqrtf(biggestTrace + 1.0f) * 0.5f;
    const float multiplier = 0.25f / biggestVal;

    switch(switchVal) {
    case 0: // w is the biggest value
        w = biggestVal;
        v.set( (R.yAxis.z - R.zAxis.y) * multiplier,
               (R.zAxis.x - R.xAxis.z) * multiplier,
               (R.xAxis.y - R.yAxis.x) * multiplier );
        break;
    case 1: // x is the biggest value
        w = (R.yAxis.z - R.zAxis.y) * multiplier;
        v.set( biggestVal,
               (R.xAxis.y - R.yAxis.x) * multiplier,
               (R.zAxis.x - R.xAxis.z) * multiplier );
        break;
    case 2: // y is the biggest value
        w = (R.zAxis.x - R.xAxis.z) * multiplier;
        v.set( (R.xAxis.y - R.yAxis.x) * multiplier,
               biggestVal,
               (R.yAxis.z - R.zAxis.y) * multiplier );
        break;
    case 3: // z is the biggest value
        w = (R.xAxis.y - R.yAxis.x) * multiplier;
        v.set( (R.zAxis.x - R.xAxis.z) * multiplier,
               (R.yAxis.z - R.zAxis.y) * multiplier,
               biggestVal );
        break;
    default: flexiAssert(false);
    }
} // Quaternion::Quaternion(RotationMatrix)

Quaternion::Quaternion(const Vector3f& axis, const float angle)
{
    // Require unit axis
    flexiAssert(axis.isUnitVec());

    const float halfAngle = angle* 0.5f;
    const float s = sinf(halfAngle);
    
    w = cosf(halfAngle);
    v = s * axis;
} // Quaternion::Quaternion(axis, angle)


///////////////////////////////////////////////////////////////////////////////////
// Accessors

float Quaternion::rotationAngle() const
{
    return 2.0f * acosf(w);
}

Vector3f Quaternion::rotationAxis() const
{
    // sin^2 (angle/2)
    const float s = 1.0f - sqr(w);

    if (areEqual(s, 0.0f)) { // Identity Quaternion; return zero vector
        return Vector3f::ZERO;
    }

    // 1 / sin(angle/2)
    const float mult = 1.0f / sqrtf(s);

    // v = sin(angle/2) * axis
    return mult * v;
}

//////////////////////////////////////////////////////////////////////////////////
// Operations

Quaternion Quaternion::operator-(const Quaternion& that) const
{
    return -(*this) * that;
}

Quaternion& Quaternion::operator-=(const Quaternion& that)
{
    *this = -(*this) * that;
    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& that) const
{
    return Quaternion(this->w * that.w - this->v.dot(that.v),
                       (this->w * that.v) + (that.w * this->v) + this->v.cross(that.v) );
}

Quaternion& Quaternion::operator*=(const Quaternion& that)
{
    const float thisW = this->w;

    this->w = thisW * that.w - this->v.dot(that.v);
    this->v = (thisW * that.v) + (that.w * this->v) + this->v.cross(that.v);

    return *this;
}

Vector3f operator*(const Vector3f& v, const Quaternion& q)
{
    return ( -q * Quaternion(0.0f, v) * q ).v;
}

Vector3f& operator*=(Vector3f& v, const Quaternion& q)
{
    v = (-q * Quaternion(0.0f, v) * q).v;
    return v;
}

float Quaternion::dot(const Quaternion& that) const
{
    return this->w * that.w + this->v.dot(that.v);
}

Quaternion Quaternion::pow(const float exp) const
{
    if (!areEqual(w, 1.0f)) { // raising identity to power does nothing
        const float angle = acosf(w);
        const float newAngle = angle * exp;
        const float mult = sinf(newAngle) / sinf(angle);

        return Quaternion(cosf(newAngle), mult * v);
    } else {
        return Quaternion(*this);
    }
}

Quaternion& Quaternion::normalized()
{
    const float magSqrd = sqr(w) + v.lenSquared();

    if (magSqrd > 0.0f) { // protect against bogus quaternion
        const float mult = 1.0f / sqrtf(magSqrd);

        w *= mult;
        v *= mult;
    } else {
        flexiAssertM(false, "Tried to normalize zero Quaternion");
    }
    return *this;
}

Quaternion Quaternion::operator-() const
{
    return Quaternion(w, -v);
}

Quaternion slerp(const Quaternion& start, const Quaternion& end, const float t)
{
    // Clamp out of range values of t to the edge quaternions
    if (t <= 0.0f)      return start;
    else if (t >= 1.0f) return end;

    // Get the cosine of the angle between start and end
    float cosAngle = start.dot(end);

    // Choose the smallest arc between the two in which to interpolate
    const Quaternion correctedEnd = (cosAngle < 0.0f)
                                     ? (cosAngle = -cosAngle, -end)
                                     : end;

    // Interpolation factors
    float startMult, endMult;

    // Lerp between very similar quaternions to prevent / 0
    if (areEqual(cosAngle, 1.0f)) {
        startMult = 1.0f - t;
        endMult = t;
    } else { // Slerp
        const float sinAngle = sqrtf(1.0f - sqr(cosAngle));
        const float angle = atan2f(sinAngle, cosAngle);
        const float invSinAngle = 1.0f / sinAngle;

        startMult = sinf((1.0f - t) * angle) * invSinAngle;
        endMult   = sinf(t * angle) * invSinAngle;
    }
    return Quaternion( start.w * startMult + correctedEnd.w * endMult,
                        Vector3f(start.v * startMult + correctedEnd.v * endMult) );
}

} // namespace fpu_math
} // namespace math
} // namespace flexi
