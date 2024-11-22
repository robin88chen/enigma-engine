/*********************************************************************
 * \file   Vector2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef VECTOR2_HPP
#define VECTOR2_HPP
#include <array>

namespace Math
{
    class Vector2
    {
    public:
        // construction
        Vector2();  // uninitialized
        Vector2(float x, float y);
        Vector2(const std::array<float, 2>& f);

        operator const float* () const;
        operator float* ();
        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);

        bool operator== (const Vector2& v) const;  ///< 浮點數值比較
        bool operator!= (const Vector2& v) const;  ///< 浮點數值比較

        Vector2 operator+ (const Vector2& v) const;
        Vector2 operator- (const Vector2& v) const;
        Vector2 operator* (float scalar) const;
        Vector2 operator/ (float scalar) const;
        Vector2 operator- () const;

        Vector2& operator+= (const Vector2& v);
        Vector2& operator-= (const Vector2& v);
        Vector2& operator*= (float scalar);
        Vector2& operator/= (float scalar);

        [[nodiscard]] float length() const;
        [[nodiscard]] float squaredLength() const;
        [[nodiscard]] float dot(const Vector2& v) const;
        [[nodiscard]] Vector2 normalize() const;
        void normalizeSelf();

        /// returns (y,-x)
        [[nodiscard]] Vector2 perp() const;

        /// returns (y,-x)/sqrt(x*x+y*y)
        [[nodiscard]] Vector2 unitPerp() const;

        /// returns dotPerp((x,y),(V.x,V.y)) = x*V.y - y*V.x
        [[nodiscard]] float dotPerp(const Vector2& v) const;

        static const Vector2 ZERO;
        static const Vector2 UNIT_X;
        static const Vector2 UNIT_Y;

    private:
        float m_x;
        float m_y;
    };

    Vector2 operator* (float scalar, const Vector2& v);
}


#endif // VECTOR2_HPP
