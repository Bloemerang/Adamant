/**
 * @file
 * @brief Definitions for Matrix4x4 class.
 * @author   Steven Bloemer
 * @date     12/24/2010
 * @lastedit 12/26/2010
 */
#include <cmath>
#include "Matrix4x4.h"
#include "RotationMatrix.h"
#include "Matrix4x3.h"
#include "DebugDefs.h"

namespace flexi {
namespace math {
namespace fpu_math {

const Matrix4x4 Matrix4x4::IDENTITY;

const Vector3f& Matrix4x4::getTranslation() const
{
    return this->translation;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& that)
{
    this->i = that.i;
    this->j = that.j;
    this->k = that.k;
    this->translation = that.translation;
    return *this;
}

void Matrix4x4::setIdentity()
{
    i.set(1.0f, 0.0f, 0.0f);
    j.set(0.0f, 1.0f, 0.0f);
    k.set(0.0f, 0.0f, 1.0f);
    translation = Vector4f::ZERO;
    translation.w = 1.0f;
}

void Matrix4x4::zeroTranslation()
{
    translation = Vector4f::ZERO;
    translation.w = 1.0f;
}

void Matrix4x4::setTranslation(const Vector3f& t)
{
    translation = t;
    translation.w = 1.0f;
}

void Matrix4x4::setupTranslation(const Vector3f& t)
{
    setTranslation(t);
    i.set(1.0f, 0.0f, 0.0f);
    j.set(0.0f, 1.0f, 0.0f);
    k.set(0.0f, 0.0f, 1.0f);
}

void Matrix4x4::build(const RotationMatrix& R, const float uniformScale)
{
    if (uniformScale != 1.0f) {
        i = R.getXAxis() * uniformScale;
        j = R.getYAxis() * uniformScale;
        k = R.getZAxis() * uniformScale;
    } else {
        i = R.getXAxis();
        j = R.getYAxis();
        k = R.getZAxis();
    }
    setTranslation(Vector3f::ZERO);
}

void Matrix4x4::build(const RotationMatrix& R, const Vector3f& scale,
                      const Vector3f& pos)
{
    i = R.getXAxis() * scale.x;
    j = R.getYAxis() * scale.y;
    k = R.getZAxis() * scale.z;
    setTranslation(pos);
    i.w = j.w = k.w = 0.0f;
}

Matrix4x4::Matrix4x4()
{
    i.w = j.w = k.w = 0.0f;
    translation.w = 1.0f;
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
{
    i = other.i;
    j = other.j;
    k = other.k;
    translation = other.translation;
    translation.w = 1.0f;
    i.w = j.w = k.w = 0.0f;
}

Matrix4x4::Matrix4x4(const Matrix4x3& other)
{
    i = other.rot[0];
    j = other.rot[1];
    k = other.rot[2];
    translation = other.translation;
    translation.w = 1.0f;
    i.w = j.w = k.w = 0.0f;
}

Matrix4x4::Matrix4x4(const RotationMatrix& R, const float uniformScale)
    : translation(Vector4f::ZERO)
{
    translation.w = 1.0f;
    if (uniformScale != 1.0f) {
        i = R.getXAxis() * uniformScale;
        j = R.getYAxis() * uniformScale;
        k = R.getZAxis() * uniformScale;
    } else {
        i = R.getXAxis();
        j = R.getYAxis();
        k = R.getZAxis();
    }
    i.w = j.w = k.w = 0.0f;
}

Matrix4x4::Matrix4x4(const RotationMatrix& R, const Vector3f& scale,
                     const Vector3f& pos)
    : translation(pos)
{
    translation.w = 1.0f;
    i = R.getXAxis() * scale.x;
    j = R.getYAxis() * scale.y;
    k = R.getZAxis() * scale.z;
    i.w = j.w = k.w = 0.0f;
}

Matrix4x4::Matrix4x4(const Vector3f& xAxis, const Vector3f& yAxis,
                     const Vector3f& zAxis, const Vector3f& pos)
    : translation(pos)
{
    translation.w = 1.0f;
    i = xAxis;
    j = yAxis;
    k = zAxis;
    i.w = j.w = k.w = 0.0f;
}

///////////////////////////////////////////////////////////////////////////
// Operations

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& M) const
{
    return Matrix4x4(
        Vector3f(i.x*M.i.x + i.y*M.j.x + i.z*M.k.x,
                 i.x*M.i.y + i.y*M.j.y + i.z*M.k.y,
                 i.x*M.i.z + i.y*M.j.z + i.z*M.k.z ),
        Vector3f(j.x*M.i.x + j.y*M.j.x + j.z*M.k.x,
                 j.x*M.i.y + j.y*M.j.y + j.z*M.k.y,
                 j.x*M.i.z + j.y*M.j.z + j.z*M.k.z ),
        Vector3f(k.x*M.i.x + k.y*M.j.x + k.z*M.k.x,
                 k.x*M.i.y + k.y*M.j.y + k.z*M.k.y,
                 k.x*M.i.z + k.y*M.j.z + k.z*M.k.z ),
        Vector3f(translation.x*M.i.x + translation.y*M.j.x
                 + translation.z*M.k.x + M.translation.x,
                 translation.x*M.i.y + translation.y* M.j.y
                 + translation.z*M.k.y + M.translation.y,
                 translation.x*M.i.z + translation.y*M.j.z
                 + translation.z*M.k.z + M.translation.z)
    );
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& M)
{
    i.set(i.x*M.i.x + i.y*M.j.x + i.z*M.k.x,
          i.x*M.i.y + i.y*M.j.y + i.z*M.k.y,
          i.x*M.i.z + i.y*M.j.z + i.z*M.k.z );
    j.set(j.x*M.i.x + j.y*M.j.x + j.z*M.k.x,
          j.x*M.i.y + j.y*M.j.y + j.z*M.k.y,
          j.x*M.i.z + j.y*M.j.z + j.z*M.k.z );
    k.set(k.x*M.i.x + k.y*M.j.x + k.z*M.k.x,
          k.x*M.i.y + k.y*M.j.y + k.z*M.k.y,
          k.x*M.i.z + k.y*M.j.z + k.z*M.k.z );
    translation.set(  translation.x*M.i.x + translation.y*M.j.x
                    + translation.z*M.k.x + M.translation.x,
                      translation.x*M.i.y + translation.y* M.j.y
                    + translation.z*M.k.y + M.translation.y,
                      translation.x*M.i.z + translation.y*M.j.z
                    + translation.z*M.k.z + M.translation.z);
    return *this;
}

float Matrix4x4::determinant() const
{
    // The translation row doesn't matter because column 4 is [0 0 0 1]
    return (  i.x * (j.y * k.z - j.z * k.y)
            + i.y * (j.x * k.z - j.z * k.x)
            + i.z * (j.x * k.y - j.y * k.x) );
}

Matrix4x4 Matrix4x4::inverse() const
{
    const float det = this->determinant();
    flexiAssertM(!areEqual(det, 0.0f), "Attempted to invert an uninvertable matrix");
    const float invDet = 1.0f / det;

    return Matrix4x4( Vector3f((j.y*k.z - j.z*k.y) * invDet,
                               (i.y*k.z - i.z*k.y) * invDet,
                               (i.y*j.z - i.z*j.y) * invDet ),
                      Vector3f((j.x*k.z - j.z*k.x) * invDet,
                               (i.x*k.z - i.z*k.x) * invDet,
                               (i.x*j.z - i.z*j.x) * invDet ),
                      Vector3f((j.x*k.y - j.y*k.x) * invDet,
                               (i.x*k.y - i.y*k.x) * invDet,
                               (i.x*j.y - i.y*j.x) * invDet ),
                      Vector3f((  translation.x * (j.y*k.z - j.z*k.y)
                                + translation.y * (j.x*k.z - j.z*k.x)
                                + translation.z * (j.x*k.y - j.y*k.x))
                               * invDet,
                               (  translation.x * (i.y*k.z - i.z*k.y)
                                + translation.y * (i.x*k.z - i.z*k.x)
                                + translation.z * (i.x*k.y - i.y*k.x))
                               * invDet,
                               (  translation.x * (i.y*j.z - i.z*j.y)
                                + translation.y * (i.x*j.z - i.z*j.x)
                                + translation.z * (i.x*j.y - i.y*j.x))
                               * invDet ) );
}

Vector3f operator*(const Vector3f& v, const Matrix4x4& M)
{
    return Vector3f(v.x*M.i.x + v.y*M.j.x + v.z*M.k.x + M.translation.x,
                    v.x*M.i.y + v.y*M.j.y + v.z*M.k.y + M.translation.y,
                    v.x*M.i.z + v.y*M.j.z + v.z*M.k.z + M.translation.z );
}

Vector3f& operator*=(Vector3f& v, const Matrix4x4& M)
{
    v.set(v.x*M.i.x + v.y*M.j.x + v.z*M.k.x + M.translation.x,
          v.x*M.i.y + v.y*M.j.y + v.z*M.k.y + M.translation.y,
          v.x*M.i.z + v.y*M.j.z + v.z*M.k.z + M.translation.z );
    return v;
}

const float* Matrix4x4::adr() const
{
    return reinterpret_cast<const float*>(this);
}

} // namespace fpu_math
} // namespace math
} // namespace flexi
