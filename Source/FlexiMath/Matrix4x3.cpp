/**
 * @file
 * @brief Definitions for Matrix4x3 class.
 * @author   Steven Bloemer
 * @date     12/11/2010
 * @lastedit 12/26/2010
 */
#include "DebugDefs.h"
#include "RotationMatrix.h"
#include "Matrix4x3.h"
#include "Matrix4x4.h"

namespace flexi {
namespace math {
namespace fpu_math {

const Matrix4x3 Matrix4x3::IDENTITY;

const Vector3f& Matrix4x3::getTranslation() const
{
    return this->translation;
}


Matrix4x3& Matrix4x3::operator=(const Matrix4x3& that)
{
    this->rot[0] = that.rot[0];
    this->rot[1] = that.rot[1];
    this->rot[2] = that.rot[2];
    this->translation = that.translation;
    return *this;
}

void Matrix4x3::setIdentity()
{
    rot[0].set(1.0f, 0.0f, 0.0f);
    rot[1].set(0.0f, 1.0f, 0.0f);
    rot[2].set(0.0f, 0.0f, 1.0f);
    translation = Vector3f::ZERO;
}

void Matrix4x3::zeroTranslation()
{
    translation = Vector3f::ZERO;
}

void Matrix4x3::setTranslation(const Vector3f& t)
{
    translation = t;
}

void Matrix4x3::setupTranslation(const Vector3f& t)
{
    setTranslation(t);
    rot[0].set(1.0f, 0.0f, 0.0f);
    rot[1].set(0.0f, 1.0f, 0.0f);
    rot[2].set(0.0f, 0.0f, 1.0f);
}

void Matrix4x3::build(const RotationMatrix& R, const float uniformScale)
{
    if (uniformScale != 1.0f) {
        rot[0] = R.getXAxis() * uniformScale;
        rot[1] = R.getYAxis() * uniformScale;
        rot[2] = R.getZAxis() * uniformScale;
    } else {
        rot[0] = R.getXAxis();
        rot[1] = R.getYAxis();
        rot[2] = R.getZAxis();
    }
    setTranslation(Vector3f::ZERO);
}

void Matrix4x3::build(const RotationMatrix& R, const Vector3f& scale,
                      const Vector3f& pos)
{
    rot[0] = R.getXAxis() * scale.x;
    rot[1] = R.getYAxis() * scale.y;
    rot[2] = R.getZAxis() * scale.z;
    setTranslation(pos);
}

Matrix4x3::Matrix4x3() { }

Matrix4x3::Matrix4x3(const Matrix4x3& other)
{
    rot[0] = other.rot[0];
    rot[1] = other.rot[1];
    rot[2] = other.rot[2];
    translation = other.translation;
}

Matrix4x3::Matrix4x3(const Matrix4x4& other)
{
    rot[0] = other.i;
    rot[1] = other.j;
    rot[2] = other.k;
    translation = other.translation;
}

Matrix4x3::Matrix4x3(const RotationMatrix& R, const float uniformScale)
    : translation(Vector3f::ZERO)
{
    if (uniformScale != 1.0f) {
        rot[0] = R.getXAxis() * uniformScale;
        rot[1] = R.getYAxis() * uniformScale;
        rot[2] = R.getZAxis() * uniformScale;
    } else {
        rot[0] = R.getXAxis();
        rot[1] = R.getYAxis();
        rot[2] = R.getZAxis();
    }
}

Matrix4x3::Matrix4x3(const RotationMatrix& R, const Vector3f& scale,
                     const Vector3f& pos)
    : translation(pos)
{
    rot[0] = R.getXAxis() * scale.x;
    rot[1] = R.getYAxis() * scale.y;
    rot[2] = R.getZAxis() * scale.z;
}

Matrix4x3::Matrix4x3(const Vector3f& xAxis, const Vector3f& yAxis,
                     const Vector3f& zAxis, const Vector3f& pos)
    : translation(pos)
{
    rot[0] = xAxis;
    rot[1] = yAxis;
    rot[2] = zAxis;
}

///////////////////////////////////////////////////////////////////////////
// Operations

Matrix4x3 Matrix4x3::operator*(const Matrix4x3& M) const
{
    return Matrix4x3(
        Vector3f(rot[0].x*M.rot[0].x + rot[0].y*M.rot[1].x + rot[0].z*M.rot[2].x,
                 rot[0].x*M.rot[0].y + rot[0].y*M.rot[1].y + rot[0].z*M.rot[2].y,
                 rot[0].x*M.rot[0].z + rot[0].y*M.rot[1].z + rot[0].z*M.rot[2].z ),
        Vector3f(rot[1].x*M.rot[0].x + rot[1].y*M.rot[1].x + rot[1].z*M.rot[2].x,
                 rot[1].x*M.rot[0].y + rot[1].y*M.rot[1].y + rot[1].z*M.rot[2].y,
                 rot[1].x*M.rot[0].z + rot[1].y*M.rot[1].z + rot[1].z*M.rot[2].z ),
        Vector3f(rot[2].x*M.rot[0].x + rot[2].y*M.rot[1].x + rot[2].z*M.rot[2].x,
                 rot[2].x*M.rot[0].y + rot[2].y*M.rot[1].y + rot[2].z*M.rot[2].y,
                 rot[2].x*M.rot[0].z + rot[2].y*M.rot[1].z + rot[2].z*M.rot[2].z ),
        Vector3f(translation.x*M.rot[0].x + translation.y*M.rot[1].x
                 + translation.z*M.rot[2].x + M.translation.x,
                 translation.x*M.rot[0].y + translation.y* M.rot[1].y
                 + translation.z*M.rot[2].y + M.translation.y,
                 translation.x*M.rot[0].z + translation.y*M.rot[1].z
                 + translation.z*M.rot[2].z + M.translation.z)
    );
}

Matrix4x3& Matrix4x3::operator*=(const Matrix4x3& M)
{
    rot[0].set(rot[0].x*M.rot[0].x + rot[0].y*M.rot[1].x + rot[0].z*M.rot[2].x,
               rot[0].x*M.rot[0].y + rot[0].y*M.rot[1].y + rot[0].z*M.rot[2].y,
               rot[0].x*M.rot[0].z + rot[0].y*M.rot[1].z + rot[0].z*M.rot[2].z );
    rot[1].set(rot[1].x*M.rot[0].x + rot[1].y*M.rot[1].x + rot[1].z*M.rot[2].x,
               rot[1].x*M.rot[0].y + rot[1].y*M.rot[1].y + rot[1].z*M.rot[2].y,
               rot[1].x*M.rot[0].z + rot[1].y*M.rot[1].z + rot[1].z*M.rot[2].z );
    rot[2].set(rot[2].x*M.rot[0].x + rot[2].y*M.rot[1].x + rot[2].z*M.rot[2].x,
               rot[2].x*M.rot[0].y + rot[2].y*M.rot[1].y + rot[2].z*M.rot[2].y,
               rot[2].x*M.rot[0].z + rot[2].y*M.rot[1].z + rot[2].z*M.rot[2].z );
    translation.set(translation.x*M.rot[0].x + translation.y*M.rot[1].x
                    + translation.z*M.rot[2].x + M.translation.x,
                    translation.x*M.rot[0].y + translation.y* M.rot[1].y
                    + translation.z*M.rot[2].y + M.translation.y,
                    translation.x*M.rot[0].z + translation.y*M.rot[1].z
                    + translation.z*M.rot[2].z + M.translation.z);
    return *this;
}

float Matrix4x3::determinant() const
{
    // The translation row doesn't matter because column 4 is [0 0 0 1]
    return (  rot[0].x * (rot[1].y * rot[2].z - rot[1].z * rot[2].y)
            + rot[0].y * (rot[1].x * rot[2].z - rot[1].z * rot[2].x)
            + rot[0].z * (rot[1].x * rot[2].y - rot[1].y * rot[2].x) );
}

Matrix4x3 Matrix4x3::inverse() const
{
    const float det = this->determinant();
    flexiAssertM(!areEqual(det, 0.0f), "Attempted to invert an uninvertable matrix");
    const float invDet = 1.0f / det;

    return Matrix4x3( Vector3f((rot[1].y*rot[2].z - rot[1].z*rot[2].y) * invDet,
                               (rot[0].y*rot[2].z - rot[0].z*rot[2].y) * invDet,
                               (rot[0].y*rot[1].z - rot[0].z*rot[1].y) * invDet ),
                      Vector3f((rot[1].x*rot[2].z - rot[1].z*rot[2].x) * invDet,
                               (rot[0].x*rot[2].z - rot[0].z*rot[2].x) * invDet,
                               (rot[0].x*rot[1].z - rot[0].z*rot[1].x) * invDet ),
                      Vector3f((rot[1].x*rot[2].y - rot[1].y*rot[2].x) * invDet,
                               (rot[0].x*rot[2].y - rot[0].y*rot[2].x) * invDet,
                               (rot[0].x*rot[1].y - rot[0].y*rot[1].x) * invDet ),
                      Vector3f((  translation.x * (rot[1].y*rot[2].z - rot[1].z*rot[2].y)
                                + translation.y * (rot[1].x*rot[2].z - rot[1].z*rot[2].x)
                                + translation.z * (rot[1].x*rot[2].y - rot[1].y*rot[2].x))
                               * invDet,
                               (  translation.x * (rot[0].y*rot[2].z - rot[0].z*rot[2].y)
                                + translation.y * (rot[0].x*rot[2].z - rot[0].z*rot[2].x)
                                + translation.z * (rot[0].x*rot[2].y - rot[0].y*rot[2].x))
                               * invDet,
                               (  translation.x * (rot[0].y*rot[1].z - rot[0].z*rot[1].y)
                                + translation.y * (rot[0].x*rot[1].z - rot[0].z*rot[1].x)
                                + translation.z * (rot[0].x*rot[1].y - rot[0].y*rot[1].x))
                               * invDet ) );
}

Vector3f operator*(const Vector3f& v, const Matrix4x3& M)
{
    return Vector3f(v.x*M.rot[0].x + v.y*M.rot[1].x + v.z*M.rot[2].x + M.translation.x,
                    v.x*M.rot[0].y + v.y*M.rot[1].y + v.z*M.rot[2].y + M.translation.y,
                    v.x*M.rot[0].z + v.y*M.rot[1].z + v.z*M.rot[2].z + M.translation.z );
}

Vector3f& operator*=(Vector3f& v, const Matrix4x3& M)
{
    v.set(v.x*M.rot[0].x + v.y*M.rot[1].x + v.z*M.rot[2].x + M.translation.x,
          v.x*M.rot[0].y + v.y*M.rot[1].y + v.z*M.rot[2].y + M.translation.y,
          v.x*M.rot[0].z + v.y*M.rot[1].z + v.z*M.rot[2].z + M.translation.z );
    return v;
}

} // namespace fpu_math
} // namespace math
} // namespace flexi
