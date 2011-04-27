#ifndef Matrix4x3_H__
#define Matrix4x3_H__
/**
 * @file
 * @brief Header for Matrix4x3 class.
 * @author   Steven Bloemer
 * @date     12/10/2010
 * @lastedit 12/26/2010
 */
#include "Vector3f.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class RotationMatrix;
class Matrix4x3;

Vector3f  operator*(const Vector3f&, const Matrix4x3&);
Vector3f& operator*=(Vector3f&, const Matrix4x3&);

class Matrix4x3
{
    Vector3f rot[3];
    Vector3f translation;

    friend Vector3f  operator*(const Vector3f&, const Matrix4x3&);
    friend Vector3f& operator*=(Vector3f&, const Matrix4x3&);
    friend class Matrix4x4;

    Matrix4x3(const Vector3f& xAxis, const Vector3f& yAxis,
              const Vector3f& zAxis, const Vector3f& pos);

public:  /***************************** Getters  ******************************/

    static const Matrix4x3 IDENTITY;

    const Vector3f& getTranslation() const;

public:  /***************************** Setters  ******************************/

    Matrix4x3& operator=(const Matrix4x3&);

    void setIdentity();
    void zeroTranslation();
    void setTranslation(const Vector3f&);
    void setupTranslation(const Vector3f&);
    void build(const RotationMatrix&, const float uniformScale = 1.0f);
    void build(const RotationMatrix&, const Vector3f& scale,
               const Vector3f& pos = Vector3f::ZERO);

public:  /*************************** Construction ****************************/

    Matrix4x3();
    Matrix4x3(const Matrix4x3&);
    explicit Matrix4x3(const Matrix4x4&);
    Matrix4x3(const Vector3f& translation);
    Matrix4x3(const RotationMatrix&, const float uniformScale = 1.0f);
    Matrix4x3(const RotationMatrix&, const Vector3f& scale,
              const Vector3f& translation = Vector3f::ZERO);
    
public:  /**************************** Operations *****************************/

    Matrix4x3 operator*(const Matrix4x3&) const;
    Matrix4x3& operator*=(const Matrix4x3&);

    float determinant() const;
    Matrix4x3 inverse() const;
}; // class Matrix4x3

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // Matrix4x3_H__
