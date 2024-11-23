/*********************************************************************
 * \file   Vector4.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef VECTOR4_HPP
#define VECTOR4_HPP
#include <array>

namespace Math
{
    class Vector3;
    class Vector4
    {
    public:
        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector3& vec, float w);
        Vector4(const std::array<float, 4>& f);

        operator const float* () const;
        operator float* ();
        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);
        [[nodiscard]] float z() const;
        void z(float z);
        [[nodiscard]] float w() const;
        void w(float w);

        bool operator== (const Vector4& v) const;   ///< 浮點數值比較
        bool operator!= (const Vector4& v) const;   ///< 浮點數值比較

        Vector4 operator+ (const Vector4& v) const;
        Vector4 operator- (const Vector4& v) const;
        Vector4 operator* (float scalar) const;
        Vector4 operator/ (float scalar) const;
        Vector4 operator- () const;

        Vector4& operator+= (const Vector4& v);
        Vector4& operator-= (const Vector4& v);
        Vector4& operator*= (float scalar);
        Vector4& operator/= (float scalar);

        [[nodiscard]] float length() const;
        [[nodiscard]] float squaredLength() const;
        [[nodiscard]] float dot(const Vector4& v) const;
        void normalizeSelf();
        [[nodiscard]] Vector4 normalize() const;

        static const Vector4 ZERO;
        static const Vector4 UNIT_X;
        static const Vector4 UNIT_Y;
        static const Vector4 UNIT_Z;
        static const Vector4 UNIT_W;

    private:
        float m_x;
        float m_y;
        float m_z;
        float m_w;
    };

    Vector4 operator* (float scalar, const Vector4& v);
}

#endif // VECTOR4_HPP
