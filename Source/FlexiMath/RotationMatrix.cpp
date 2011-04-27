/**
 * @file
 * @brief Definitions for RotationMatrix class.
 * @author   Steven Bloemer
 * @date     12/14/2010
 * @lastedit 12/30/2010
 */
#include <cmath>
#include "MathUtil.h"
#include "DebugDefs.h"
#include "Quaternion.h"
#include "RotationMatrix.h"

namespace flexi {
namespace math {
namespace fpu_math {

////////////////////////////////////////////////////////////////////////////////
// Construction

const RotationMatrix RotationMatrix::IDENTITY;

RotationMatrix::RotationMatrix(const Vector3f& xAxis,
                               const Vector3f& yAxis,
                               const Vector3f& zAxis )
    : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis)
{ }

RotationMatrix::RotationMatrix()
    : xAxis(1.0f, 0.0f, 0.0f)
    , yAxis(0.0f, 1.0f, 0.0f)
    , zAxis(0.0f, 0.0f, 1.0f)
{ }

RotationMatrix::RotationMatrix(const RotationMatrix& R)
    : xAxis(R.xAxis), yAxis(R.yAxis), zAxis(R.zAxis)
{ }

RotationMatrix::RotationMatrix(const Quaternion& q)
{
    // Temporaries. All of these are used multiple times, so we pre-compute them
    const float dblXsqr = 2*sqr(q.v.x), dblYsqr = 2*sqr(q.v.y), dblZsqr = 2*sqr(q.v.z);
    const float dblxy = 2*q.v.x*q.v.y, dblxz = 2*q.v.x*q.v.z, dblxw = 2*q.v.x*q.w;
    const float dblyz = 2*q.v.y*q.v.z, dblyw = 2*q.v.y*q.w;
    const float dblzw = 2*q.v.z*q.w;

    xAxis.set(1.0f - dblYsqr - dblZsqr,  dblxy + dblzw,              dblxz - dblyw);
    yAxis.set(dblxy - dblzw,             1.0f - dblXsqr - dblZsqr,   dblyz + dblxw);
    zAxis.set(dblxz + dblyw,             dblyz - dblxw,              1.0f - dblXsqr - dblYsqr);
}

RotationMatrix::RotationMatrix(const float xRad,
                               const float yRad,
                               const float zRad)
{
    const float sX = sinf(xRad), cX = cosf(xRad);
    const float sY = sinf(yRad), cY = cosf(yRad);
    const float sZ = sinf(zRad), cZ = cosf(zRad);

    xAxis.set(cY*cZ + sY*sX*sZ, sZ*cX, -sY*cZ + cY*sX*sZ);
    yAxis.set(-cY*sZ + sY*sX*cZ, cZ*cX, sZ*sY + cY*sX*cZ);
    zAxis.set(sY*cX, -sX, cY*cX);
}

RotationMatrix::RotationMatrix(const Vector3f& axis, const float angle)
{
    const float sine   = sinf(angle);
    const float cosine = cosf(angle);
    const float oneMinusCos = 1 - cosine;

    const float xy1mCos = axis.x * axis.y * oneMinusCos;
    const float xz1mCos = axis.x * axis.z * oneMinusCos;
    const float yz1mCos = axis.y * axis.z * oneMinusCos;
    const float xSin = axis.x * sine;
    const float ySin = axis.y * sine;
    const float zSin = axis.z * sine;

    xAxis.set(axis.x * axis.x * oneMinusCos + cosine,
              xy1mCos + zSin, xz1mCos - ySin);
    yAxis.set(xy1mCos - zSin,
              axis.y * axis.y * oneMinusCos + cosine,
              yz1mCos + xSin);
    zAxis.set(xz1mCos + ySin, yz1mCos - xSin,
              axis.z * axis.z * oneMinusCos + cosine);
} // RotationMatrix::RotationMatrix(axis, angle)

RotationMatrix::RotationMatrix(const RotationAxis axis, const float angle)
{
    const float sine = sinf(angle);
    const float cosine = cosf(angle);
  
    switch (axis) {
    case X_AXIS:
        xAxis.set(1.0f, 0.0f, 0.0f);
        yAxis.set(0.0f, cosine, sine);
        zAxis.set(0.0f, -sine, cosine);
        break;
    case Y_AXIS:
        xAxis.set(cosine, 0.0f, -sine);
        yAxis.set(0.0f, 1.0f, 0.0f);
        zAxis.set(sine, 0.0f, cosine);
        break;
    case Z_AXIS:
        xAxis.set(cosine, sine, 0.0f);
        yAxis.set(-sine, cosine, 0.0f);
        zAxis.set(0.0f, 0.0f, 1.0f);
        break;
    default: flexiAssert(false);
	}
} // RotationMatrix::RotationMatrix(RotationAxis, angle)

RotationMatrix& RotationMatrix::operator=(const RotationMatrix& that)
{
    this->xAxis = that.xAxis;
    this->yAxis = that.yAxis;
    this->zAxis = that.zAxis;
    return *this;
}

const Vector3f& RotationMatrix::getXAxis() const { return xAxis; }
const Vector3f& RotationMatrix::getYAxis() const { return yAxis; }
const Vector3f& RotationMatrix::getZAxis() const { return zAxis; }

RotationMatrix RotationMatrix::operator*(const RotationMatrix& that) const
{
    // A rotation matrix's transpose is its inverse
    const RotationMatrix thatInv = that.getInverse();

    const Vector3f outXAxis(this->xAxis.dot(thatInv.xAxis),
                            this->xAxis.dot(thatInv.yAxis),
                            this->xAxis.dot(thatInv.zAxis) );
    const Vector3f outYAxis(this->yAxis.dot(thatInv.xAxis),
                            this->yAxis.dot(thatInv.yAxis),
                            this->yAxis.dot(thatInv.zAxis) );
    const Vector3f outZAxis(this->zAxis.dot(thatInv.xAxis),
                            this->zAxis.dot(thatInv.yAxis),
                            this->zAxis.dot(thatInv.zAxis) );

    return RotationMatrix(outXAxis, outYAxis, outZAxis);
} // RotationMatrix::operator*(RotationMatrix)

RotationMatrix& RotationMatrix::operator*=(const RotationMatrix& that)
{
    // A rotation matrix's transpose is its inverse
    const RotationMatrix thatInv = that.getInverse();

    xAxis.set(this->xAxis.dot(thatInv.xAxis),
              this->xAxis.dot(thatInv.yAxis),
              this->xAxis.dot(thatInv.zAxis) );
    yAxis.set(this->yAxis.dot(thatInv.xAxis),
              this->yAxis.dot(thatInv.yAxis),
              this->yAxis.dot(thatInv.zAxis) );
    zAxis.set(this->zAxis.dot(thatInv.xAxis),
              this->zAxis.dot(thatInv.yAxis),
              this->zAxis.dot(thatInv.zAxis) );
    return *this;
} // RotationMatrix::operator*=(RotationMatrix)

Vector3f operator*(const Vector3f& v, const RotationMatrix& R)
{
    const RotationMatrix RT(R.getInverse());

    return Vector3f(v.dot(RT.xAxis), v.dot(RT.yAxis), v.dot(RT.zAxis));
} // operator*(Vector3f, RotationMatrix)

Vector3f& operator*=(Vector3f& v, const RotationMatrix& R)
{
    const RotationMatrix RT(R.getInverse());
    
    v.set(v.dot(RT.xAxis), v.dot(RT.yAxis), v.dot(RT.zAxis));
    return v;
}

RotationMatrix RotationMatrix::getInverse() const
{
    return RotationMatrix(Vector3f(xAxis.x, yAxis.x, zAxis.x),
                          Vector3f(xAxis.y, yAxis.y, zAxis.y),
                          Vector3f(xAxis.z, yAxis.z, zAxis.z) );
}

RotationMatrix& RotationMatrix::inverted()
{
    float tmp;
    
    tmp = xAxis.y;
    xAxis.y = yAxis.x; yAxis.x = tmp;

    tmp = xAxis.z;
    xAxis.z = zAxis.x; zAxis.x = tmp;

    tmp = yAxis.z;
    yAxis.z = zAxis.y; zAxis.y = tmp;

    return *this;
}

float RotationMatrix::measureMatrixCreep() const
{
    return   xAxis.lenSquared() + yAxis.lenSquared() + zAxis.lenSquared()
           + xAxis.dot(yAxis)   + xAxis.dot(zAxis)   + yAxis.dot(zAxis)
           - 3.0f;
}

void RotationMatrix::orthogonalize()
{
    const float incr = 0.25f;
    const unsigned REPS = 10u;

    for (unsigned curr = 0; curr < REPS; ++curr) {
        const Vector3f i(xAxis);
        const Vector3f j(yAxis);
        const Vector3f k(zAxis);
        const float iDotJ = i.dot(j);
        const float iDotK = i.dot(k);
        const float jDotK = j.dot(k);
        const float iInvMagSqrd = 1.0f / i.lenSquared();
        const float jInvMagSqrd = 1.0f / j.lenSquared();
        const float kInvMagSqrd = 1.0f / k.lenSquared();
        
        xAxis =   i
                - incr * iDotJ * jInvMagSqrd * j
                - incr * iDotK * kInvMagSqrd * k;
        yAxis =   j
                - incr * iDotJ * iInvMagSqrd * i
                - incr * jDotK * kInvMagSqrd * k;
        zAxis =   k
                - incr * iDotK * iInvMagSqrd * i
                - incr * jDotK * jInvMagSqrd * j;
    }
} // RotationMatrix::orthogonalize()

} // namespace fpu_math
} // namespace math
} // namespace flexi
