#ifndef Vector3f_H__
#define Vector3f_H__
/**
 * @file
 * @brief Header for Vector3f class.
 * @author   Steven Bloemer
 * @date     12/5/2010
 * @lastedit 12/26/2010
 */
#include "MathUtil.h"

namespace flexi {
namespace math {
namespace fpu_math {

// Forward Declare
class Vector4f;

class Vector3f
{
public: /*********************** Fields and constants *************************/
    float x, y, z;

    /// The zero vector, having all three components set to zero.
    static const Vector3f ZERO;

public: /*************************** Construction *****************************/

    /**
     * @brief Constructs a new Vector3f without initializing fields.
     * 
     * Optimizes the frequent case of creating an array of Vector3fs which will
     * be initialized later, and therefore do not require default
     * initialization. If a vector initialized to the zero vector is required,
     * use the class field Vector3f::ZERO.
     */
    Vector3f();

    /// Copy Constructor
    Vector3f(const Vector3f&);

    /// Copy-construct from Vector4f.
    explicit Vector3f(const Vector4f&);

    /// Component-wise initialization constructor.
    Vector3f(const float x, const float y, const float z);


public: /**************************** Operators *******************************/
    /**
     * @brief Negate a Vector3f, returning by value.
     * 
     * Example:
     * @code
     * Vector3f v(1,2,3);
     * Vector3f negV = -v;           // Unary minus operator called
     * printf("(%d, %d, %d)", v);    // Prints "(1, 2, 3)"
     * printf("(%d, %d, %d)", negV); // Prints "(-1, -2, -3)"
     * @endcode
     */
    Vector3f operator-() const;

    /**
     * @brief Adds two vectors, returning the result by value.
     * 
     * Example:
     * @code
     * Vector3f v1(1,2,3);
     * Vector3f v2(3,2,1);
     * Vector3f v1AddV2 = v1 + v2       // Calls v1.operator+(v2)
     * printf("(%d, %d, %d)", v1AddV2); // Prints "(4, 4, 4)"
     * @endcode
     */
    Vector3f operator+(const Vector3f&) const;

    /**
     * @brief Adds the specified Vector3f to this one, storing the result in
     *  this Vector3f.
     *  
     * Example:
     * @code
     * Vector3f v1(1,2,3);
     * Vector3f v2(3,2,1);
     * v1 += v2                    // Calls v1.operator+=(v2)
     * printf("(%d, %d, %d)", v1); // Prints "(4, 4, 4)"
     * @endcode
     * 
     * @return A mutable reference to this Vector3f, enabling multiple
     *  assignment.
     */
    Vector3f& operator+=(const Vector3f&);

    /**
     * @brief Subtracts the specified Vector3f from this one, returning the
     *  result by value.
     *  
     * Example:
     * @code
     * Vector3f v1(1,2,3);
     * Vector3f v2(3,2,1);
     * Vector3f v1SubV2 = v1 - v2       // Calls v1.operator-(v2)
     * printf("(%d, %d, %d)", v1SubV2); // Prints "(-2, 0, 2)"
     * @endcode
     */
    Vector3f operator-(const Vector3f&) const;
    
    /**
     * @brief Subtracts the specified Vector3f from this one, storing the
     *  result in this Vector3f.
     *  
     * Example:
     * @code
     * Vector3f v1(1,2,3);
     * Vector3f v2(3,2,1);
     * v1 -= v2                    // Calls v1.operator-=(v2)
     * printf("(%d, %d, %d)", v1); // Prints "(-2, 0, 2)"
     * @endcode
     * 
     * @return A mutable reference to this Vector3f, enabling multiple
     *  assignment.
     */
    Vector3f& operator-=(const Vector3f&);

    /**
     * @brief Returns a Vector3f which is the result of scaling this Vector3f by
     *  the specified scalar value.
     * 
     * Example:
     * @code
     * Vector3f v(1,2,3);
     * Vector3f result = v * 3.0f;     // Calls v.operator*(3.0f)
     * printf("(%d, %d, %d)", result); // Prints "(1, 6, 9)"
     * @endcode
     */
    Vector3f operator*(const float s) const;

    /**
     * @brief Scales this Vector3f by the specified scalar value, storing the
     *  result in this Vector3f.
     * 
     * Example:
     * @code
     * Vector3f v(1,2,3);
     * v *= 3.0f;                 // Calls v.operator*=(3.0f)
     * printf("(%d, %d, %d)", v); // Prints "(1, 6, 9)"
     * @endcode
     * 
     * @return A mutable reference to this Vector3f, enabling multiple
     *  assignment.
     */
    Vector3f& operator*=(const float s);

public: /***************************** Methods ********************************/

    /**
     * @brief Returns the dot product of this Vector3f with that specified.
     * 
     * The dot product of two vectors v and v' is defined as
     * <code>x*x' + y*y' + z*z'</code>.
     * 
     * Example:
     * @code
     * Vector3f v1(1,2,3);
     * Vector3f v2(0,0,1);
     * float dotProduct = v1.dot(v2);
     * printf("%d", dotProduct);      // Prints "3"
     * @endcode
     */
    float dot(const Vector3f&) const;

    /**
     * @brief Returns the cross product of this Vector3f with that specified.
     * 
     * The cross product of two vectors @c v and @c v' is defined as
     * <code>(y*z' - z*y', z*x' - x*z', x*y' - y*x')</code>.
     * 
     * Example:
     * @code
     * Vector3f v1(2,1,0);
     * Vector3f v2(1,2,0);
     * 
     * Vector3f v1CrossV2 = v1.cross(v2);
     * printf("(%d, %d, %d)", v1CrossV2); // Prints "(0, 0, 3)"
     * @endcode
     */
    Vector3f cross(const Vector3f&) const;

    /**
     * @brief Returns the length of this Vector3f.
     * 
     * The length of a vector is defined as <code>sqrt(x*x + y*y + z*z)</code>,
     * where @c sqrt computes the square root of its argument.
     */
    float len() const;

    /**
     * @brief Returns the squared length of this Vector3f.
     * 
     * As it does not have compute a square root, this method is more efficient
     * in situations where only the relative lengths of two vectors is
     * interesting. <code>v1.len() > v2.len()</code> is always true if and only
     * if <code>v1.lenSquared() > v2.lenSquared()</code>.
     */
    float lenSquared() const;

    /**
     * @brief Normalizes this Vector3f in place.
     * 
     * Normalizing a vector renders it unit-length without changing its
     * direction. A vector is normalized by dividing each of its components by
     * its length.
     * 
     * @b IMPORTANT: The zero vector cannot be normalized. If @c normalize is
     * called on the zero vector, it is left unchanged (still the zero vector).
     * Callers must check for themselves whether the vector they are normalizing
     * can successfully be normalized.
     * 
     * @returns This Vector3f, enabling use in expressions requiring a unit-
     *  length vector.
     */
    Vector3f& normalized();

    /**
     * @brief Returns a Vector3f equal to the normalization of this Vector3f.
     * 
     * Normalizing a vector renders it unit-length without changing its
     * direction. A vector is normalized by dividing each of its components by
     * the its length.
     * 
     * @b IMPORTANT: The zero vector cannot be normalized. If @c normalize is
     * called on the zero vector, the zero vector is returned. Callers must
     * check for themselves whether the vector they are normalizing can
     * successfully be normalized.
     */
    Vector3f getNormalized() const;

    /// Sets all three components of this Vector3f to the specified values
    void set(const float x, const float y, const float z);

    /**
     * @brief Provides a view of this Vector3f as an immutable float array.
     * 
     * Useful for interacting with APIs which use arrays to represent vectors.
     */
    const float* adr() const;

    /**
     * @brief Checks whether this Vector3f is equal to that specified within a
     *  specified tolerance.
     * 
     * @returns @c true if and only if the absolute values of the component-wise
     * differences (x - x', y - y', z - z') are each less than @a tolerance.
     * @a tolerance defaults to math::FLOAT_TOLERANCE, defined in
     * MathConstants.h.
     */
    bool equals(const Vector3f&, const float tolerance = FLOAT_TOLERANCE) const;

    /**
     * @brief Returns @c true if and only if this Vector3f is equal to the zero
     *  vector within the specified tolerance.
     *  
     * @param tolerance The difference between two floats within which they are
     *  considered equal. Defaults to math::FLOAT_TOLERANCE.
     * @see equals() for how equality within a tolerance is computed.
     */
    bool isZeroVec(const float tolerance = FLOAT_TOLERANCE) const;

    /**
     * @brief Returns @c true if and only if this Vector3f is of unit length.
     *
     * @param tolerance The difference between two floats within which they are
     *  considered equal. Defaults to math::FLOAT_TOLERANCE.
     */
    bool isUnitVec(const float tolerance = FLOAT_TOLERANCE) const;
}; // class Vector3f


/**
 * @brief Scales @a v by @a s, returning the result by value
 * 
 * Example:
 * @code
 * Vector3f v(1,2,3);
 * Vector3f result = 3.0f * v; // Calls flexi::math::operator*(3.0f, v)
 * printf("(%d, %d, %d)", v);  // Prints "(1, 6, 9)"
 * @endcode
 */
Vector3f operator*(const float s, const Vector3f& v);

} // namespace fpu_math
} // namespace math
} // namespace flexi

#endif // Vector3f_H__
