/*********************************************************************
 * \file   Vector3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include <array>

namespace Math
{
    class Vector4;

    class Vector3
    {
    public:
        // construction
        Vector3();  // uninitialized
        Vector3(float x, float y, float z);
        Vector3(const std::array<float, 3>& f);

        operator const float* () const;
        operator float* ();
        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);
        [[nodiscard]] float z() const;
        void z(float z);

        Vector3& operator= (const Vector4& v);

        bool operator== (const Vector3& v) const;  ///< 浮點數值比較
        bool operator!= (const Vector3& v) const;   ///< 浮點數值比較

        Vector3 operator+ (const Vector3& v) const;
        Vector3 operator- (const Vector3& v) const;
        Vector3 operator* (float scalar) const;
        Vector3 operator/ (float scalar) const;
        Vector3 operator- () const;

        Vector3& operator+= (const Vector3& v);
        Vector3& operator-= (const Vector3& v);
        Vector3& operator*= (float scalar);
        Vector3& operator/= (float scalar);

        [[nodiscard]] float length() const;
        [[nodiscard]] float squaredLength() const;
        [[nodiscard]] float dot(const Vector3& v) const;
        void normalizeSelf();
        [[nodiscard]] Vector3 normalize() const;
        /// The cross products are computed using the left-handed rule.
        [[nodiscard]] Vector3 cross(const Vector3& v) const;
        /// The cross products are computed using the left-handed rule.
        [[nodiscard]] Vector3 unitCross(const Vector3& v) const;

        static const Vector3 ZERO;
        static const Vector3 UNIT_X;
        static const Vector3 UNIT_Y;
        static const Vector3 UNIT_Z;

    private:
        float m_x;
        float m_y;
        float m_z;
    };
    /** scalar * vector3 */
    Vector3 operator* (float scalar, const Vector3& v);
}

#endif // VECTOR3_HPP
