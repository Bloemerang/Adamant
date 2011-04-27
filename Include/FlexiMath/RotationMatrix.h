#ifndef ROTATION_MATRIX_H_
#define ROTATION_MATRIX_H_
/**
 * @file
 * @brief Header for RotationMatrix class.
 * @author   Steven Bloemer
 * @date     12/14/2010
 * @lastedit 12/30/2010
 */
#include "Vector3f.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class RotationMatrix;

Vector3f  operator*(const Vector3f&, const RotationMatrix&);
Vector3f& operator*=(Vector3f&, const RotationMatrix&);

class RotationMatrix
{
    Vector3f xAxis,
             yAxis,
             zAxis;

    friend class Quaternion;
    friend Vector3f operator*(const Vector3f&, const RotationMatrix&);
    friend Vector3f& operator*=(Vector3f&, const RotationMatrix&);

    RotationMatrix(const Vector3f&, const Vector3f&, const Vector3f&);

public: /**************************** Construction ****************************/

    enum RotationAxis {
        X_AXIS, Y_AXIS, Z_AXIS
    };

    static const RotationMatrix IDENTITY;

    RotationMatrix();
    RotationMatrix(const RotationMatrix&);
    explicit RotationMatrix(const Quaternion&);
    RotationMatrix(const float xRad, const float yRad, const float zRad);
    RotationMatrix(const Vector3f& axis, const float angle);
    RotationMatrix(const RotationAxis axis, const float angle);

    RotationMatrix& operator=(const RotationMatrix&);

public: /****************************** Accessors *****************************/

    const Vector3f& getXAxis() const;
    const Vector3f& getYAxis() const;
    const Vector3f& getZAxis() const;

public: /****************************** Operations ****************************/

    RotationMatrix  operator*(const RotationMatrix&) const;
    RotationMatrix& operator*=(const RotationMatrix&);

    RotationMatrix  getInverse() const;
    RotationMatrix& inverted();

    float measureMatrixCreep() const;
    void orthogonalize();
};

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // ROTATION_MATRIX_H_
