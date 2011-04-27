#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H
/**
 * @file
 * @brief Header for Matrix4x4 class.
 * @author   Steven Bloemer
 * @date     12/12/2010
 * @lastedit 1/1/2011
 */
#include "Vector4f.h"
#include "Vector3f.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class Matrix4x4;
class RotationMatrix;
class Matrix4x3;

Vector4f  operator*(const Vector4f&, const Matrix4x4&);
Vector4f& operator*=(Vector4f&, const Matrix4x4&);

class Matrix4x4
{
    Vector4f i, j, k;
    Vector4f translation;

    friend Vector3f  operator*(const Vector3f&, const Matrix4x4&);
    friend Vector3f& operator*=(Vector3f&, const Matrix4x4&);
    friend class Matrix4x3;

    Matrix4x4(const Vector3f& xAxis, const Vector3f& yAxis,
              const Vector3f& zAxis, const Vector3f& pos);

public:  /***************************** Getters  ******************************/

    static const Matrix4x4 IDENTITY;

    const Vector3f& getTranslation() const;

    const float* adr() const;

public:  /***************************** Setters  ******************************/

    Matrix4x4& operator=(const Matrix4x4&);

    void setIdentity();
    void zeroTranslation();
    void setTranslation(const Vector3f&);
    void setupTranslation(const Vector3f&);
    void build(const RotationMatrix&, const float uniformScale = 1.0f);
    void build(const RotationMatrix&, const Vector3f& scale,
               const Vector3f& pos = Vector3f::ZERO);

public:  /*************************** Construction ****************************/

    Matrix4x4();
    Matrix4x4(const Matrix4x4&);
    explicit Matrix4x4(const Matrix4x3&);
    Matrix4x4(const Vector3f& translation);
    Matrix4x4(const RotationMatrix&, const float uniformScale = 1.0f);
    Matrix4x4(const RotationMatrix&, const Vector3f& scale,
              const Vector3f& translation = Vector3f::ZERO);
    
public:  /**************************** Operations *****************************/

    Matrix4x4 operator*(const Matrix4x4&) const;
    Matrix4x4& operator*=(const Matrix4x4&);

    float determinant() const;
    Matrix4x4 inverse() const;
}; // class Matrix4x4

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // MATRIX_4X4_H
